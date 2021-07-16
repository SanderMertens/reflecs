
#include "private_api.h"

static
const ecs_entity_t* new_w_data(
    ecs_world_t *world,
    ecs_table_t *table,
    ecs_ids_t *component_ids,
    int32_t count,
    void **c_info,
    int32_t *row_out);

static
void* get_component_w_index(
    ecs_table_t *table,
    int32_t column_index,
    int32_t row)
{
    ecs_assert(column_index < table->column_count, ECS_NOT_A_COMPONENT, NULL);

    ecs_data_t *data = ecs_table_get_data(table);
    ecs_column_t *column = &data->columns[column_index];

    /* If size is 0, component does not have a value. This is likely caused by
    * an application trying to call ecs_get with a tag. */
    int32_t size = column->size;    
    ecs_assert(size != 0, ECS_INVALID_PARAMETER, NULL);

    void *ptr = ecs_vector_first_t(column->data, size, column->alignment); 
    return ECS_OFFSET(ptr, size * row);  
}

static
void* get_component(
    const ecs_world_t *world,
    ecs_table_t *table,
    int32_t row,
    ecs_id_t id)
{
    ecs_id_record_t *idr = ecs_get_id_record(world, id);
    if (!idr) {
        return NULL;
    }

    ecs_table_record_t *tr = ecs_map_get(idr->table_index, 
        ecs_table_record_t, table->id);
    if (!tr) {
       return NULL;
    }

    return get_component_w_index(table, tr->column, row);
}

static
void* get_base_component(
    const ecs_world_t *world,
    ecs_table_t *table,
    ecs_id_t id,
    ecs_map_t *table_index,
    ecs_map_t *table_index_isa,
    int32_t recur_depth)
{
    /* Cycle detected in IsA relation */
    ecs_assert(recur_depth < ECS_MAX_RECURSION, ECS_INVALID_PARAMETER, NULL);

    /* Table (and thus entity) does not have component, look for base */
    if (!(table->flags & EcsTableHasIsA)) {
        return NULL;
    }

    /* Exclude Name */
    if (id == ecs_id(EcsName)) {
        return NULL;
    }

    /* Should always be an id record for IsA, otherwise a table with a 
     * HasBase flag set should not exist. */
    if (!table_index_isa) {
        ecs_id_record_t *idr = ecs_get_id_record(world, ecs_pair(EcsIsA, EcsWildcard));
        ecs_assert(idr != NULL, ECS_INTERNAL_ERROR, NULL);
        table_index_isa = idr->table_index;
    }

    /* Table should always be in the table index for (IsA, *), otherwise the
     * HasBase flag should not have been set */
    ecs_table_record_t *tr_isa = ecs_map_get(
        table_index_isa, ecs_table_record_t, table->id);
    ecs_assert(tr_isa != NULL, ECS_INTERNAL_ERROR, NULL);

    ecs_type_t type = table->type;
    ecs_id_t *ids = ecs_vector_first(type, ecs_id_t);
    int32_t i = tr_isa->column, count = tr_isa->count;
    void *ptr = NULL;

    do {
        ecs_id_t pair = ids[i];

        ecs_entity_t base = ecs_pair_object(world, pair);
        ecs_record_t *r = ecs_eis_get(world, base);
        if (!r) {
            continue;
        }

        table = r->table;
        if (!table) {
            continue;
        }

        ecs_table_record_t *tr = ecs_map_get(table_index, 
            ecs_table_record_t, table->id);
        if (!tr) {
            ptr = get_base_component(world, table, id, table_index, 
                table_index_isa, recur_depth + 1);
        } else {
            bool is_monitored;
            int32_t row = ecs_record_to_row(r->row, &is_monitored);
            ptr = get_component_w_index(table, tr->column, row);
        }
        i ++;
    } while (!ptr && (i < count));

    return ptr;
}

/* Utility to compute actual row from row in record */
static
int32_t set_row_info(
    ecs_entity_info_t *info,
    int32_t row)
{
    return info->row = ecs_record_to_row(row, &info->is_watched);
}

/* Utility to set info from main stage record */
static
void set_info_from_record(
    ecs_entity_info_t * info,
    ecs_record_t * record)
{
    ecs_assert(record != NULL, ECS_INTERNAL_ERROR, NULL);

    info->record = record;

    ecs_table_t *table = record->table;

    set_row_info(info, record->row);

    info->table = table;
    if (!info->table) {
        return;
    }

    ecs_data_t *data = ecs_table_get_data(table);
    ecs_assert(data != NULL, ECS_INTERNAL_ERROR, NULL);

    info->data = data;

    ecs_assert(ecs_vector_count(data->entities) > info->row, 
        ECS_INTERNAL_ERROR, NULL);
}

/* Get info from main stage */
bool ecs_get_info(
    const ecs_world_t * world,
    ecs_entity_t entity,
    ecs_entity_info_t * info)
{
    info->table = NULL;
    info->record = NULL;
    info->data = NULL;
    info->is_watched = false;

    if (entity & ECS_ROLE) {
        return false;
    }
    
    ecs_record_t *record = ecs_eis_get(world, entity);

    if (!record) {
        return false;
    }

    set_info_from_record(info, record);

    return true;
}

static
const ecs_type_info_t *get_c_info(
    ecs_world_t *world,
    ecs_entity_t component)
{
    ecs_entity_t real_id = ecs_get_typeid(world, component);
    if (real_id) {
        return ecs_get_c_info(world, real_id);
    } else {
        return NULL;
    }
}

int ecs_get_column_info(
    ecs_world_t * world,
    ecs_table_t * table,
    ecs_ids_t * components,
    ecs_column_info_t * cinfo,
    bool get_all)
{
    int32_t column_count = table->column_count;
    ecs_entity_t *type_array = ecs_vector_first(table->type, ecs_entity_t);

    if (get_all) {
        int32_t i, count = ecs_vector_count(table->type);
        for (i = 0; i < count; i ++) {
            ecs_entity_t id = type_array[i];
            cinfo[i].id = id;
            cinfo[i].ci = get_c_info(world, id);
            cinfo[i].column = i;            
        }

        return count;
    } else {
        ecs_entity_t *array = components->array;
        int32_t i, cur, count = components->count;
        for (i = 0; i < count; i ++) {
            ecs_entity_t id = array[i];
            cinfo[i].id = id;
            cinfo[i].ci = get_c_info(world, id);
            cinfo[i].column = -1;

            for (cur = 0; cur < column_count; cur ++) {
                if (type_array[cur] == id) {
                    cinfo[i].column = cur;
                    break;
                }
            }
        }

        return count;
    }
}

static
void instantiate(
    ecs_world_t *world,
    ecs_entity_t base,
    ecs_table_t *table,
    ecs_data_t *data,
    int32_t row,
    int32_t count);

static
void instantiate_children(
    ecs_world_t * world,
    ecs_entity_t base,
    ecs_table_t * table,
    ecs_data_t * data,
    int32_t row,
    int32_t count,
    ecs_table_t * child_table)
{
    ecs_type_t type = child_table->type;
    ecs_data_t *child_data = ecs_table_get_data(child_table);
    if (!child_data || !ecs_table_data_count(child_data)) {
        return;
    }

    int32_t column_count = child_table->column_count;
    ecs_entity_t *type_array = ecs_vector_first(type, ecs_entity_t);
    int32_t type_count = ecs_vector_count(type);   

    /* Instantiate child table for each instance */

    /* Create component array for creating the table */
    ecs_ids_t components = {
        .array = ecs_os_alloca(ECS_SIZEOF(ecs_entity_t) * type_count + 1)
    };

    void **c_info = ecs_os_alloca(ECS_SIZEOF(void*) * column_count);

    /* Copy in component identifiers. Find the base index in the component
     * array, since we'll need this to replace the base with the instance id */
    int i, base_index = -1, pos = 0;

    for (i = 0; i < type_count; i ++) {
        ecs_entity_t c = type_array[i];
        
        /* Make sure instances don't have EcsPrefab */
        if (c == EcsPrefab) {
            continue;
        }

        /* Keep track of the element that creates the ChildOf relationship with
        * the prefab parent. We need to replace this element to make sure the
        * created children point to the instance and not the prefab */ 
        if (ECS_HAS_RELATION(c, EcsChildOf) && (ecs_entity_t_lo(c) == base)) {
            base_index = pos;
        }        

        /* Store pointer to component array. We'll use this component array to
        * create our new entities in bulk with new_w_data */
        if (i < column_count) {
            ecs_column_t *column = &child_data->columns[i];
            c_info[pos] = ecs_vector_first_t(
                column->data, column->size, column->alignment);
        }

        components.array[pos] = c;
        pos ++;
    }

    ecs_assert(base_index != -1, ECS_INTERNAL_ERROR, NULL);

    /* If children are added to a prefab, make sure they are prefabs too */
    if (table->flags & EcsTableIsPrefab) {
        components.array[pos] = EcsPrefab;
        pos ++;
    }

    components.count = pos;

    /* Instantiate the prefab child table for each new instance */
    ecs_entity_t *entities = ecs_vector_first(data->entities, ecs_entity_t);
    int32_t child_count = ecs_vector_count(child_data->entities);

    for (i = row; i < count + row; i ++) {
        ecs_entity_t instance = entities[i];

        /* Replace ChildOf element in the component array with instance id */
        components.array[base_index] = ecs_pair(EcsChildOf, instance);

        /* Find or create table */
        ecs_table_t *i_table = ecs_table_find_or_create(world, &components);
        ecs_assert(i_table != NULL, ECS_INTERNAL_ERROR, NULL); 

        /* The instance is trying to instantiate from a base that is also
         * its parent. This would cause the hierarchy to instantiate itself
         * which would cause infinite recursion. */
        int j;
        ecs_entity_t *children = ecs_vector_first(
            child_data->entities, ecs_entity_t);
#ifndef NDEBUG
        for (j = 0; j < child_count; j ++) {
            ecs_entity_t child = children[j];        
            ecs_assert(child != instance, ECS_INVALID_PARAMETER, NULL);
        }
#endif

        /* Create children */
        int32_t child_row; 
        new_w_data(world, i_table, NULL, child_count, c_info, &child_row);       

        /* If prefab child table has children itself, recursively instantiate */
        ecs_data_t *i_data = ecs_table_get_data(i_table);
        for (j = 0; j < child_count; j ++) {
            ecs_entity_t child = children[j];
            instantiate(world, child, i_table, i_data, child_row + j, 1);
        }
    }       
}

static
void instantiate(
    ecs_world_t * world,
    ecs_entity_t base,
    ecs_table_t * table,
    ecs_data_t * data,
    int32_t row,
    int32_t count)
{    
    /* If base is a parent, instantiate children of base for instances */
    const ecs_id_record_t *r = ecs_get_id_record(
        world, ecs_pair(EcsChildOf, base));

    if (r && r->table_index) {
        ecs_table_record_t *tr;
        ecs_map_iter_t it = ecs_map_iter(r->table_index);
        while ((tr = ecs_map_next(&it, ecs_table_record_t, NULL))) {
            instantiate_children(
                world, base, table, data, row, count, tr->table);
        }
    }
}

static
bool override_component(
    ecs_world_t *world,
    ecs_entity_t component,
    ecs_type_t type,
    ecs_data_t *data,
    ecs_column_t *column,
    int32_t row,
    int32_t count);

static
bool override_from_base(
    ecs_world_t *world,
    ecs_entity_t base,
    ecs_entity_t component,
    ecs_data_t *data,
    ecs_column_t *column,
    int32_t row,
    int32_t count)
{
    ecs_assert(component != 0, ECS_INTERNAL_ERROR, NULL);

    ecs_entity_info_t base_info;
    ecs_assert(component != 0, ECS_INTERNAL_ERROR, NULL);

    if (!ecs_get_info(world, base, &base_info) || !base_info.table) {
        return false;
    }

    void *base_ptr = get_component(
        world, base_info.table, base_info.row, component);
    if (base_ptr) {
        int16_t data_size = column->size;
        void *data_array = ecs_vector_first_t(
            column->data, column->size, column->alignment);
        void *data_ptr = ECS_OFFSET(data_array, data_size * row);

        component = ecs_get_typeid(world, component);
        const ecs_type_info_t *cdata = ecs_get_c_info(world, component);
        int32_t index;

        ecs_copy_t copy = cdata ? cdata->lifecycle.copy : NULL;
        if (copy) {
            ecs_entity_t *entities = ecs_vector_first(
                data->entities, ecs_entity_t);

            void *ctx = cdata->lifecycle.ctx;
            for (index = 0; index < count; index ++) {
                copy(world, component, &entities[row], &base,
                    data_ptr, base_ptr, ecs_to_size_t(data_size), 1, ctx);
                data_ptr = ECS_OFFSET(data_ptr, data_size);
            }
        } else {
            for (index = 0; index < count; index ++) {
                ecs_os_memcpy(data_ptr, base_ptr, data_size);
                data_ptr = ECS_OFFSET(data_ptr, data_size);
            }                    
        }

        return true;
    } else {
        /* If component not found on base, check if base itself inherits */
        ecs_type_t base_type = base_info.table->type;
        return override_component(world, component, base_type, data, column, 
            row, count);
    }
}

static
bool override_component(
    ecs_world_t * world,
    ecs_entity_t component,
    ecs_type_t type,
    ecs_data_t * data,
    ecs_column_t * column,
    int32_t row,
    int32_t count)
{
    ecs_entity_t *type_array = ecs_vector_first(type, ecs_entity_t);
    int32_t i, type_count = ecs_vector_count(type);

    /* Walk prefabs */
    i = type_count - 1;
    do {
        ecs_entity_t e = type_array[i];

        if (!(e & ECS_ROLE_MASK)) {
            break;
        }

        if (ECS_HAS_RELATION(e, EcsIsA)) {
            if (override_from_base(world, ecs_pair_object(world, e), component,
                data, column, row, count))
            {
                return true;
            }
        }
    } while (--i >= 0);

    return false;
}

static
void ecs_components_override(
    ecs_world_t * world,
    ecs_table_t * table,
    ecs_data_t * data,
    int32_t row,
    int32_t count,
    ecs_column_info_t * component_info,
    int32_t component_count,
    bool run_on_set)
{
    ecs_assert(data != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(component_count != 0, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(component_info != NULL, ECS_INTERNAL_ERROR, NULL);

    ecs_table_t *table_without_base = table;
    ecs_column_t *columns = data->columns;
    ecs_type_t type = table->type;
    int32_t column_count = table->column_count;

    int i;
    for (i = 0; i < component_count; i ++) {
        ecs_entity_t component = component_info[i].id;

        if (component >= ECS_HI_COMPONENT_ID) {
            if (ECS_HAS_RELATION(component, EcsIsA)) {
                ecs_entity_t base = ECS_PAIR_OBJECT(component);

                /* Illegal to create an instance of 0 */
                ecs_assert(base != 0, ECS_INVALID_PARAMETER, NULL);
                instantiate(world, base, table, data, row, count);

                /* If table has on_set systems, get table without the base
                 * entity that was just added. This is needed to determine the
                 * diff between the on_set systems of the current table and the
                 * table without the base, as these are the systems that need to
                 * be invoked */
                ecs_ids_t to_remove = {
                    .array = &component,
                    .count = 1
                };

                table_without_base = ecs_table_traverse_remove(world, 
                    table_without_base, &to_remove, NULL);
            }
        }

        int32_t column_index = component_info[i].column;
        if (column_index == -1 || column_index >= column_count) {
            continue;
        }

        /* column_index is lower than column count, which means we must have
         * data columns */
        ecs_assert(data->columns != NULL, ECS_INTERNAL_ERROR, NULL);

        if (!data->columns[column_index].size) {
            continue;
        }

        ecs_column_t *column = &columns[column_index];
        if (override_component(world, component, type, data, column, 
            row, count)) 
        {
            ecs_ids_t to_remove = {
                .array = &component,
                .count = 1
            };
            table_without_base = ecs_table_traverse_remove(world, 
                table_without_base, &to_remove, NULL);
        }
    }

    /* Run OnSet actions when a base entity is added to the entity for 
     * components not overridden by the entity. */
    if (run_on_set && table_without_base != table) {
        /* TODO */
    }
}

static
void set_switch(
    ecs_world_t *world,
    ecs_table_t *table,
    ecs_data_t * data,
    int32_t row,
    int32_t count,    
    ecs_ids_t *entities,
    bool reset)
{
    ecs_entity_t *array = entities->array;
    int32_t i, comp_count = entities->count;

    for (i = 0; i < comp_count; i ++) {
        ecs_entity_t e = array[i];

        if (ECS_HAS_ROLE(e, CASE)) {
            e = e & ECS_COMPONENT_MASK;

            ecs_entity_t sw_case = 0;
            if (!reset) {
                sw_case = e;
                ecs_assert(sw_case != 0, ECS_INTERNAL_ERROR, NULL);
            }

            int32_t sw_index = ecs_table_switch_from_case(world, table, e);
            ecs_assert(sw_index != -1, ECS_INTERNAL_ERROR, NULL);
            ecs_switch_t *sw = data->sw_columns[sw_index].data;
            ecs_assert(sw != NULL, ECS_INTERNAL_ERROR, NULL);
            
            int32_t r;
            for (r = 0; r < count; r ++) {
                ecs_switch_set(sw, row + r, sw_case);
            }
        }
    }
}

static
void ecs_components_switch(
    ecs_world_t *world,
    ecs_table_t *table,
    ecs_data_t *data,
    int32_t row,
    int32_t count,
    ecs_ids_t *added,
    ecs_ids_t *removed)
{
    if (added) {
        set_switch(world, table, data, row, count, added, false);
    }
    if (removed) {
        set_switch(world, table, data, row, count, removed, true);
    } 
}

void ecs_run_add_actions(
    ecs_world_t * world,
    ecs_table_t * table,
    ecs_data_t * data,
    int32_t row,
    int32_t count,
    ecs_ids_t * added,
    bool get_all,
    bool run_on_set)
{
    ecs_assert(added != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(added->count < ECS_MAX_ADD_REMOVE, ECS_INVALID_PARAMETER, NULL);

    if (table->flags & EcsTableHasIsA) {
        ecs_column_info_t cinfo[ECS_MAX_ADD_REMOVE];
        int added_count = ecs_get_column_info(
            world, table, added, cinfo, get_all);

        ecs_components_override(
            world, table, data, row, count, cinfo, 
            added_count, run_on_set);
    }

    if (table->flags & EcsTableHasSwitch) {
        ecs_components_switch(world, table, data, row, count, added, NULL);
    }

    if (table->flags & EcsTableHasOnAdd) {
        ecs_emit(world, &(ecs_event_desc_t){EcsOnAdd, added, 
            EcsPayloadTable, .payload.table = {table, row, count} });
    }
}

void ecs_run_remove_actions(
    ecs_world_t * world,
    ecs_table_t * table,
    int32_t row,
    int32_t count,
    ecs_ids_t * removed)
{
    ecs_assert(removed != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(removed->count < ECS_MAX_ADD_REMOVE, ECS_INVALID_PARAMETER, NULL);

    if (count) {
        if (table->flags & EcsTableHasUnSet) {
            ecs_emit(world, &(ecs_event_desc_t){EcsUnSet, removed, 
                EcsPayloadTable, .payload.table = {table, row, count} });
        } 

        if (table->flags & EcsTableHasOnRemove) {
            ecs_emit(world, &(ecs_event_desc_t){EcsOnRemove, removed, 
                EcsPayloadTable, .payload.table = {table, row, count} });
        }
    }
}

static
int32_t new_entity(
    ecs_world_t * world,
    ecs_entity_t entity,
    ecs_entity_info_t * info,
    ecs_table_t * new_table,
    ecs_ids_t * added,
    bool construct)
{
    ecs_record_t *record = info->record;
    ecs_data_t *new_data = ecs_table_get_or_create_data(new_table);
    int32_t new_row;

    ecs_assert(added != NULL, ECS_INTERNAL_ERROR, NULL);

    if (!record) {
        record = ecs_eis_ensure(world, entity);
    }

    new_row = ecs_table_append(
        world, new_table, new_data, entity, record, construct);

    record->table = new_table;
    record->row = ecs_row_to_record(new_row, info->is_watched);

    ecs_assert(
        ecs_vector_count(new_data[0].entities) > new_row, 
        ECS_INTERNAL_ERROR, NULL);

    if (new_table->flags & EcsTableHasAddActions) {
        ecs_run_add_actions(
            world, new_table, new_data, new_row, 1, added, true, true);       
    }

    info->data = new_data;
    
    return new_row;
}

static
int32_t move_entity(
    ecs_world_t * world,
    ecs_entity_t entity,
    ecs_entity_info_t * info,
    ecs_table_t * src_table,
    ecs_data_t * src_data,
    int32_t src_row,
    ecs_table_t * dst_table,
    ecs_ids_t * added,
    ecs_ids_t * removed,
    bool construct)
{    
    ecs_data_t *dst_data = ecs_table_get_or_create_data(dst_table);
    ecs_assert(src_data != dst_data, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ecs_is_alive(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(src_table != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(src_data != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(src_row >= 0, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ecs_vector_count(src_data->entities) > src_row, 
        ECS_INTERNAL_ERROR, NULL);

    ecs_record_t *record = info->record;
    ecs_assert(!record || record == ecs_eis_get(world, entity), 
        ECS_INTERNAL_ERROR, NULL);

    int32_t dst_row = ecs_table_append(world, dst_table, dst_data, entity, 
        record, false);

    record->table = dst_table;
    record->row = ecs_row_to_record(dst_row, info->is_watched);

    ecs_assert(ecs_vector_count(src_data->entities) > src_row, 
        ECS_INTERNAL_ERROR, NULL);

    /* Copy entity & components from src_table to dst_table */
    if (src_table->type) {
        /* If components were removed, invoke remove actions before deleting */
        if (removed && (src_table->flags & EcsTableHasRemoveActions)) {
            /* If entity was moved, invoke UnSet monitors for each component  
             * that the entity no longer has */
            ecs_run_remove_actions(
                world, src_table, src_row, 1, removed);
        }

        ecs_table_move(world, entity, entity, dst_table, dst_data, dst_row, 
            src_table, src_data, src_row, construct);                
    }

    ecs_table_delete(world, src_table, src_data, src_row, false);

    /* If components were added, invoke add actions */
    if (src_table != dst_table || (added && added->count)) {
        if (added && (dst_table->flags & EcsTableHasAddActions)) {
            ecs_run_add_actions(
                world, dst_table, dst_data, dst_row, 1, added, false, true);
        }

        /* If removed components were overrides, run OnSet systems for those, as 
         * the value of those components changed from the removed component to 
         * the value of component on the base entity */
        if (removed && dst_table->flags & EcsTableHasIsA) {
            /* TODO */      
        }
    }

    info->data = dst_data;

    return dst_row;
}

static
void delete_entity(
    ecs_world_t * world,
    ecs_table_t * src_table,
    ecs_data_t * src_data,
    int32_t src_row,
    ecs_ids_t * removed)
{
    if (removed) {
        /* Invoke remove actions before deleting */
        if (src_table->flags & EcsTableHasRemoveActions) {   
            ecs_run_remove_actions(
                world, src_table, src_row, 1, removed);
        } 
    }

    ecs_table_delete(world, src_table, src_data, src_row, true);
}

/* Updating component monitors is a relatively expensive operation that only
 * happens for entities that are monitored. The approach balances the amount of
 * processing between the operation on the entity vs the amount of work that
 * needs to be done to rematch queries, as a simple brute force approach does
 * not scale when there are many tables / queries. Therefore we need to do a bit
 * of bookkeeping that is more intelligent than simply flipping a flag */
static
void update_component_monitor_w_array(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_entity_t relation,
    ecs_ids_t * entities)
{
    if (!entities) {
        return;
    }

    int i;
    for (i = 0; i < entities->count; i ++) {
        ecs_entity_t id = entities->array[i];
        if (ECS_HAS_ROLE(id, PAIR)) {
            ecs_entity_t rel = ECS_PAIR_RELATION(id);
            
            /* If a relationship has changed, check if it could have impacted
             * the shape of the graph for that relationship. If so, mark the
             * relationship as dirty */        
            if (rel != relation && ecs_get_id_record(world, ecs_pair(rel, entity))) {
                update_component_monitor_w_array(world, entity, rel, entities);
            }

        }
        
        if (ECS_HAS_RELATION(id, EcsIsA)) {
            /* If an IsA relationship is added to a monitored entity (can
             * be either a parent or a base) component monitors need to be
             * evaluated for the components of the prefab. */
            ecs_entity_t base = ecs_pair_object(world, id);
            ecs_type_t type = ecs_get_type(world, base);
            ecs_ids_t base_entities = ecs_type_to_entities(type);

            /* This evaluates the component monitor for all components of the
             * base entity. If the base entity contains IsA relationships
             * these will be evaluated recursively as well. */
            update_component_monitor_w_array(
                world, entity, relation, &base_entities);               
        } else {
            ecs_monitor_mark_dirty(world, relation, id);
        }
    }
}

static
void update_component_monitors(
    ecs_world_t * world,
    ecs_entity_t entity,
    ecs_ids_t * added,
    ecs_ids_t * removed)
{
    update_component_monitor_w_array(world, entity, 0, added);
    update_component_monitor_w_array(world, entity, 0, removed);
}

static
void commit(
    ecs_world_t * world,
    ecs_entity_t entity,
    ecs_entity_info_t * info,
    ecs_table_t * dst_table,   
    ecs_ids_t * added,
    ecs_ids_t * removed,
    bool construct)
{
    ecs_assert(!world->is_readonly, ECS_INTERNAL_ERROR, NULL);
    
    ecs_table_t *src_table = info->table;
    if (src_table == dst_table) {
        /* If source and destination table are the same no action is needed *
         * However, if a component was added in the process of traversing a
         * table, this suggests that a case switch could have occured. */
        if (((added && added->count) || (removed && removed->count)) && 
             src_table && src_table->flags & EcsTableHasSwitch) 
        {
            ecs_components_switch(
                world, src_table, info->data, info->row, 1, added, removed);
        }

        return;
    }

    if (src_table) {
        ecs_data_t *src_data = info->data;
        ecs_assert(dst_table != NULL, ECS_INTERNAL_ERROR, NULL);

        if (dst_table->type) { 
            info->row = move_entity(world, entity, info, src_table, 
                src_data, info->row, dst_table, added, removed, construct);
            info->table = dst_table;
        } else {
            delete_entity(world, src_table, src_data, info->row, removed);

            ecs_eis_set(world, entity, &(ecs_record_t){
                NULL, (info->is_watched == true) * -1
            });
        }      
    } else {        
        if (dst_table->type) {
            info->row = new_entity(
                world, entity, info, dst_table, added, construct);
            info->table = dst_table;
        }        
    }

    /* If the entity is being watched, it is being monitored for changes and
     * requires rematching systems when components are added or removed. This
     * ensures that systems that rely on components from containers or prefabs
     * update the matched tables when the application adds or removes a 
     * component from, for example, a container. */
    if (info->is_watched) {
        update_component_monitors(world, entity, added, removed);
    }

    if ((!src_table || !src_table->type) && world->range_check_enabled) {
        ecs_assert(!world->stats.max_id || entity <= world->stats.max_id, ECS_OUT_OF_RANGE, 0);
        ecs_assert(entity >= world->stats.min_id, ECS_OUT_OF_RANGE, 0);
    } 
}

static
void new(
    ecs_world_t * world,
    ecs_entity_t entity,
    ecs_ids_t * to_add)
{
    ecs_entity_info_t info = {0};
    ecs_table_t *table = ecs_table_traverse_add(
        world, &world->store.root, to_add, NULL);
    new_entity(world, entity, &info, table, to_add, true);
}

static
const ecs_entity_t* new_w_data(
    ecs_world_t * world,
    ecs_table_t * table,
    ecs_ids_t * component_ids,
    int32_t count,
    void ** component_data,
    int32_t * row_out)
{
    ecs_assert(world != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(table != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(count != 0, ECS_INTERNAL_ERROR, NULL);
    
    int32_t sparse_count = ecs_eis_count(world);
    const ecs_entity_t *ids = ecs_sparse_new_ids(world->store.entity_index, count);
    ecs_assert(ids != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_type_t type = table->type;   

    if (!type) {
        return ids;        
    }

    ecs_ids_t component_array = { 0 };
    if (!component_ids) {
        component_ids = &component_array;
        component_array.array = ecs_vector_first(type, ecs_entity_t);
        component_array.count = ecs_vector_count(type);
    }

    ecs_data_t *data = ecs_table_get_or_create_data(table);
    int32_t row = ecs_table_appendn(world, table, data, count, ids);
    ecs_ids_t added = ecs_type_to_entities(type);
    
    /* Update entity index. */
    int i;
    ecs_record_t **record_ptrs = ecs_vector_first(data->record_ptrs, ecs_record_t*);
    for (i = 0; i < count; i ++) { 
        record_ptrs[row + i] = ecs_eis_set(world, ids[i], 
        &(ecs_record_t){
            .table = table,
            .row = row + i + 1
        });
    }

    ecs_defer_none(world, &world->stage);

    ecs_run_add_actions(world, table, data, row, count, &added, 
        true, component_data == NULL);

    if (component_data) {
        /* Set components that we're setting in the component mask so the init
         * actions won't call OnSet triggers for them. This ensures we won't
         * call OnSet triggers multiple times for the same component */
        int32_t c_i;
        for (c_i = 0; c_i < component_ids->count; c_i ++) {
            ecs_entity_t c = component_ids->array[c_i];
            
            /* Bulk copy column data into new table */
            int32_t table_index = ecs_type_index_of(type, c);
            ecs_assert(table_index >= 0, ECS_INTERNAL_ERROR, NULL);
            if (table_index >= table->column_count) {
                continue;
            }

            ecs_column_t *column = &data->columns[table_index];
            int16_t size = column->size;
            int16_t alignment = column->alignment;
            void *ptr = ecs_vector_first_t(column->data, size, alignment);
            ptr = ECS_OFFSET(ptr, size * row);

            /* Copy component data */
            void *src_ptr = component_data[c_i];
            if (!src_ptr) {
                continue;
            }

            const ecs_type_info_t *cdata = get_c_info(world, c);
            ecs_copy_t copy;
            if (cdata && (copy = cdata->lifecycle.copy)) {
                ecs_entity_t *entities = ecs_vector_first(data->entities, ecs_entity_t);
                copy(world, c, entities, entities, ptr, src_ptr, 
                    ecs_to_size_t(size), count, cdata->lifecycle.ctx);
            } else {
                ecs_os_memcpy(ptr, src_ptr, size * count);
            }
        };

        ecs_emit(world, &(ecs_event_desc_t){EcsOnSet, NULL,
            EcsPayloadTable, .payload.table = {table, row, count} });
    }

    ecs_defer_flush(world, &world->stage);

    if (row_out) {
        *row_out = row;
    }

    ids = ecs_sparse_ids(world->store.entity_index);

    return &ids[sparse_count];
}

static
bool has_type(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_type_t type,
    bool match_any,
    bool match_prefabs)    
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    if (!entity) {
        return false;
    }

    if (!type) {
        return true;
    }

    ecs_type_t entity_type = ecs_get_type(world, entity);

    return ecs_type_contains(
        world, entity_type, type, match_any, match_prefabs) != 0;
}

static
void add_remove(
    ecs_world_t * world,
    ecs_entity_t entity,
    ecs_ids_t * to_add,
    ecs_ids_t * to_remove)
{
    ecs_object_assert(world, ecs_world_t);
    ecs_assert(to_add->count < ECS_MAX_ADD_REMOVE, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(to_remove->count < ECS_MAX_ADD_REMOVE, ECS_INVALID_PARAMETER, NULL);

    ecs_entity_info_t info;
    ecs_get_info(world, entity, &info);

    ecs_entity_t add_buffer[ECS_MAX_ADD_REMOVE];
    ecs_entity_t remove_buffer[ECS_MAX_ADD_REMOVE];
    ecs_ids_t added = { .array = add_buffer };
    ecs_ids_t removed = { .array = remove_buffer };

    ecs_table_t *src_table = info.table;

    ecs_table_t *dst_table = ecs_table_traverse_remove(
        world, src_table, to_remove, &removed);

    dst_table = ecs_table_traverse_add(
        world, dst_table, to_add, &added);    

    commit(world, entity, &info, dst_table, &added, &removed, true);
}

static
void add_ids_w_info(
    ecs_world_t * world,
    ecs_entity_t entity,
    ecs_entity_info_t * info,
    ecs_ids_t * components,
    bool construct)
{
    ecs_assert(components->count < ECS_MAX_ADD_REMOVE, ECS_INVALID_PARAMETER, NULL);
    ecs_entity_t buffer[ECS_MAX_ADD_REMOVE];
    ecs_ids_t added = { .array = buffer };

    ecs_table_t *src_table = info->table;
    ecs_table_t *dst_table = ecs_table_traverse_add(
        world, src_table, components, &added);

    commit(world, entity, info, dst_table, &added, NULL, construct);
}

static
void remove_ids_w_info(
    ecs_world_t * world,
    ecs_entity_t entity,
    ecs_entity_info_t * info,
    ecs_ids_t * components)
{
    ecs_assert(components->count < ECS_MAX_ADD_REMOVE, ECS_INVALID_PARAMETER, NULL);
    ecs_entity_t buffer[ECS_MAX_ADD_REMOVE];
    ecs_ids_t removed = { .array = buffer };

    ecs_table_t *src_table = info->table;
    ecs_table_t *dst_table = ecs_table_traverse_remove(
        world, src_table, components, &removed);

    commit(world, entity, info, dst_table, NULL, &removed, true);
}

static
void add_ids(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_ids_t * components)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(components->count < ECS_MAX_ADD_REMOVE, ECS_INVALID_PARAMETER, NULL);
    ecs_stage_t *stage = ecs_stage_from_world(&world);

    if (ecs_defer_add(world, stage, entity, components)) {
        return;
    }

    ecs_entity_info_t info;
    ecs_get_info(world, entity, &info);

    ecs_entity_t buffer[ECS_MAX_ADD_REMOVE];
    ecs_ids_t added = { .array = buffer };

    ecs_table_t *src_table = info.table;
    ecs_table_t *dst_table = ecs_table_traverse_add(
        world, src_table, components, &added);

    commit(world, entity, &info, dst_table, &added, NULL, true);

    ecs_defer_flush(world, stage);
}

static
void remove_ids(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_ids_t * components)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(components->count < ECS_MAX_ADD_REMOVE, ECS_INVALID_PARAMETER, NULL);    
    ecs_stage_t *stage = ecs_stage_from_world(&world);

    if (ecs_defer_remove(world, stage, entity, components)) {
        return;
    }

    ecs_entity_info_t info;
    ecs_get_info(world, entity, &info);

    ecs_entity_t buffer[ECS_MAX_ADD_REMOVE];
    ecs_ids_t removed = { .array = buffer };

    ecs_table_t *src_table = info.table;
    ecs_table_t *dst_table = ecs_table_traverse_remove(
        world, src_table, components, &removed);

    commit(world, entity, &info, dst_table, NULL, &removed, true);

    ecs_defer_flush(world, stage);
}

static
void *get_mutable(
    ecs_world_t * world,
    ecs_entity_t entity,
    ecs_entity_t component,
    ecs_entity_info_t * info,
    bool * is_added)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(component != 0, ECS_INVALID_PARAMETER, NULL);
    ecs_assert((component & ECS_COMPONENT_MASK) == component || 
        ECS_HAS_ROLE(component, PAIR), ECS_INVALID_PARAMETER, NULL);

    void *dst = NULL;
    if (ecs_get_info(world, entity, info) && info->table) {
        dst = get_component(world, info->table, info->row, component);
    }

    if (!dst) {
        ecs_table_t *table = info->table;

        ecs_ids_t to_add = {
            .array = &component,
            .count = 1
        };

        add_ids_w_info(world, entity, info, &to_add, true);

        ecs_get_info(world, entity, info);
        ecs_assert(info->table != NULL, ECS_INTERNAL_ERROR, NULL);

        dst = get_component(world, info->table, info->row, component);

        if (is_added) {
            *is_added = table != info->table;
        }

        return dst;
    } else {
        if (is_added) {
            *is_added = false;
        }

        return dst;
    }
}

/* -- Private functions -- */

int32_t ecs_record_to_row(
    int32_t row, 
    bool *is_watched_out) 
{
    bool is_watched = row < 0;
    row = row * -(is_watched * 2 - 1) - 1 * (row != 0);
    *is_watched_out = is_watched;
    return row;
}

int32_t ecs_row_to_record(
    int32_t row, 
    bool is_watched) 
{
    return (row + 1) * -(is_watched * 2 - 1);
}

ecs_ids_t ecs_type_to_entities(
    ecs_type_t type)
{
    return (ecs_ids_t){
        .array = ecs_vector_first(type, ecs_entity_t),
        .count = ecs_vector_count(type)
    };
}

void ecs_set_watch(
    ecs_world_t *world,
    ecs_entity_t entity)
{    
    (void)world;

    ecs_record_t *record = ecs_eis_get(world, entity);
    if (!record) {
        ecs_record_t new_record = {.row = -1, .table = NULL};
        ecs_eis_set(world, entity, &new_record);
    } else {
        if (record->row > 0) {
            record->row *= -1;

        } else if (record->row == 0) {
            /* If entity is empty, there is no index to change the sign of. In
             * this case, set the index to -1, and assign an empty type. */
            record->row = -1;
            record->table = NULL;
        }
    }
}


/* -- Public functions -- */

bool ecs_commit(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_record_t *record,
    ecs_table_t *table,
    ecs_entities_t *added,
    ecs_entities_t *removed)
{
    ecs_assert(world != NULL, ECS_INTERNAL_ERROR, NULL);

    ecs_table_t *src_table = NULL;
    if (!record) {
        record = ecs_eis_get(world, entity);
        src_table = record->table;
    }

    ecs_entity_info_t info = {0};
    if (record) {
        set_info_from_record(&info, record);
    }

    commit(world, entity, &info, table, added, removed, true);

    return src_table != table;
}

ecs_entity_t ecs_new_id(
    ecs_world_t *world)
{
    ecs_assert(world != NULL, ECS_INTERNAL_ERROR, NULL);

    const ecs_stage_t *stage = ecs_stage_from_readonly_world(world);

    /* It is possible that the world passed to this function is a stage, so
     * make sure we have the actual world. Cast away const since this is one of
     * the few functions that may modify the world while it is in readonly mode,
     * since it is thread safe (uses atomic inc when in threading mode) */
    ecs_world_t *unsafe_world = (ecs_world_t*)ecs_get_world(world);

    ecs_entity_t entity;

    int32_t stage_count = ecs_get_stage_count(unsafe_world);
    if (stage->asynchronous || (ecs_os_has_threading() && stage_count > 1)) {
        /* Can't atomically increase number above max int */
        ecs_assert(
            unsafe_world->stats.last_id < UINT_MAX, ECS_INTERNAL_ERROR, NULL);

        entity = (ecs_entity_t)ecs_os_ainc(
            (int32_t*)&unsafe_world->stats.last_id);
    } else {
        entity = ecs_eis_recycle(unsafe_world);
    }

    ecs_assert(!unsafe_world->stats.max_id || 
        entity <= unsafe_world->stats.max_id, 
        ECS_OUT_OF_RANGE, NULL);

    return entity;
}

ecs_entity_t ecs_set_with(
    ecs_world_t *world,
    ecs_id_t id)
{
    ecs_stage_t *stage = ecs_stage_from_world(&world);
    ecs_id_t prev = stage->with;
    stage->with = id;
    return prev;
}

ecs_entity_t ecs_get_with(
    const ecs_world_t *world)
{
    const ecs_stage_t *stage = ecs_stage_from_readonly_world(world);
    return stage->with;
}

ecs_entity_t ecs_new_component_id(
    ecs_world_t *world)
{
    ecs_assert(world != NULL, ECS_INTERNAL_ERROR, NULL);

    /* It is possible that the world passed to this function is a stage, so
     * make sure we have the actual world. Cast away const since this is one of
     * the few functions that may modify the world while it is in readonly mode,
     * but only if single threaded. */
    ecs_world_t *unsafe_world = (ecs_world_t*)ecs_get_world(world);

    if (unsafe_world->is_readonly) {
        /* Can't issue new comp id while iterating when in multithreaded mode */
        ecs_assert(ecs_get_stage_count(world) <= 1, 
            ECS_INVALID_WHILE_ITERATING, NULL);
    }

    ecs_entity_t id;

    if (unsafe_world->stats.last_component_id < ECS_HI_COMPONENT_ID) {
        do {
            id = unsafe_world->stats.last_component_id ++;
        } while (ecs_exists(unsafe_world, id) && id < ECS_HI_COMPONENT_ID);        
    }
    
    if (unsafe_world->stats.last_component_id >= ECS_HI_COMPONENT_ID) {
        /* If the low component ids are depleted, return a regular entity id */
        id = ecs_new_id(unsafe_world);
    }

    return id;
}

ecs_entity_t ecs_new_w_type(
    ecs_world_t *world,
    ecs_type_t type)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    if (!type) {
        return ecs_new_w_id(world, 0);
    }

    ecs_stage_t *stage = ecs_stage_from_world(&world);    
    ecs_entity_t entity = ecs_new_id(world);
    ecs_id_t with = stage->with;
    ecs_entity_t scope = stage->scope;

    ecs_ids_t to_add = ecs_type_to_entities(type);
    if (ecs_defer_new(world, stage, entity, &to_add)) {
        if (with) {
            ecs_add_id(world, entity, with);
        }
        if (scope) {
            ecs_add_id(world, entity, ecs_pair(EcsChildOf, scope));
        }
        return entity;
    }

    new(world, entity, &to_add);

    ecs_id_t ids[2];
    to_add = (ecs_entities_t){ .array = ids, .count = 0 };

    if (with) {
        ids[to_add.count ++] = with;
    }

    if (scope) {
        ids[to_add.count ++] = ecs_pair(EcsChildOf, scope);
    }

    if (to_add.count) {
        add_ids(world, entity, &to_add);
    }

    ecs_defer_flush(world, stage);    

    return entity;
}

ecs_entity_t ecs_new_w_id(
    ecs_world_t *world,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);    
    ecs_entity_t entity = ecs_new_id(world);

    ecs_id_t ids[3];
    ecs_entities_t to_add = { .array = ids, .count = 0 };

    if (id) {
        ids[to_add.count ++] = id;
    }

    ecs_id_t with = stage->with;
    if (with) {
        ids[to_add.count ++] = with;
    }

    ecs_entity_t scope = stage->scope;
    if (scope) {
        if (!id || !ECS_HAS_RELATION(id, EcsChildOf)) {
            ids[to_add.count ++] = ecs_pair(EcsChildOf, scope);
        }
    }

    if (ecs_defer_new(world, stage, entity, &to_add)) {
        return entity;
    } 

    if (to_add.count) {
        new(world, entity, &to_add);
    } else {
        ecs_eis_set(world, entity, &(ecs_record_t){ 0 });
    }

    ecs_defer_flush(world, stage);

    return entity;
}

#ifdef FLECS_PARSER

/* Traverse table graph by either adding or removing identifiers parsed from the
 * passed in expression. */
static
ecs_table_t *traverse_from_expr(
    ecs_world_t *world,
    ecs_table_t *table,
    const char *name,
    const char *expr,
    ecs_ids_t *modified,
    bool is_add,
    bool replace_and)
{
    int32_t size = modified->count;
    if (size < ECS_MAX_ADD_REMOVE) {
        size = ECS_MAX_ADD_REMOVE;
    }

    const char *ptr = expr;
    if (ptr) {
        ecs_term_t term = {0};
        while (ptr[0] && (ptr = ecs_parse_term(world, name, expr, ptr, &term))){
            if (!ecs_term_is_set(&term)) {
                break;
            }

            if (ecs_term_finalize(world, name, expr, &term)) {
                return NULL;
            }

            if (!ecs_term_is_trivial(&term)) {
                ecs_parser_error(name, expr, (ptr - expr), 
                    "invalid non-trivial term in add expression");
                return NULL;
            }

            if (modified->count == size) {
                size *= 2;
                ecs_id_t *arr = ecs_os_malloc(size * ECS_SIZEOF(ecs_id_t));
                ecs_os_memcpy(arr, modified->array, 
                    modified->count * ECS_SIZEOF(ecs_id_t));

                if (modified->count != ECS_MAX_ADD_REMOVE) {
                    ecs_os_free(modified->array);
                }
                
                modified->array = arr;
            }

            if (term.oper == EcsAnd || !replace_and) {
                /* Regular AND expression */
                ecs_ids_t arr = { .array = &term.id, .count = 1 };
                if (is_add) {
                    table = ecs_table_traverse_add(
                        world, table, &arr, modified);
                } else {
                    table = ecs_table_traverse_remove(
                        world, table, &arr, modified);
                }

                ecs_assert(table != NULL, ECS_INVALID_PARAMETER, NULL);
            } else if (term.oper == EcsAndFrom) {
                /* Add all components from the specified type */
                const EcsType *t = ecs_get(world, term.id, EcsType);
                if (!t) {
                    ecs_parser_error(name, expr, (ptr - expr), 
                        "expected type for AND role");
                    return NULL;
                }
                
                ecs_id_t *ids = ecs_vector_first(t->normalized, ecs_id_t);
                int32_t i, count = ecs_vector_count(t->normalized);
                for (i = 0; i < count; i ++) {
                    ecs_ids_t arr = { .array = &ids[i], .count = 1 };
                    if (is_add) {
                        table = ecs_table_traverse_add(
                            world, table, &arr, modified);
                    } else {
                        table = ecs_table_traverse_remove(
                            world, table, &arr, modified);
                    }
                    
                    ecs_assert(table != NULL, ECS_INVALID_PARAMETER, NULL);
                }
            }

            ecs_term_fini(&term);
        }
    }

    return table;
}

/* Add/remove components based on the parsed expression. This operation is 
 * slower than traverse_from_expr, but safe to use from a deferred context. */
static
void defer_from_expr(
    ecs_world_t *world,
    ecs_entity_t entity,
    const char *name,
    const char *expr,
    bool is_add,
    bool replace_and)
{
    const char *ptr = expr;
    if (ptr) {
        ecs_term_t term = {0};
        while (ptr[0] && (ptr = ecs_parse_term(world, name, expr, ptr, &term))) {
            if (!ecs_term_is_set(&term)) {
                break;
            }

            if (ecs_term_finalize(world, name, expr, &term)) {
                return;
            }

            if (!ecs_term_is_trivial(&term)) {
                ecs_parser_error(name, expr, (ptr - expr), 
                    "invalid non-trivial term in add expression");
                return;
            }

            if (term.oper == EcsAnd || !replace_and) {
                /* Regular AND expression */
                if (is_add) {
                    ecs_add_id(world, entity, term.id);
                } else {
                    ecs_remove_id(world, entity, term.id);
                }
            } else if (term.oper == EcsAndFrom) {
                /* Add all components from the specified type */
                const EcsType *t = ecs_get(world, term.id, EcsType);
                if (!t) {
                    ecs_parser_error(name, expr, (ptr - expr), 
                        "expected type for AND role");
                    return;
                }
                
                ecs_id_t *ids = ecs_vector_first(t->normalized, ecs_id_t);
                int32_t i, count = ecs_vector_count(t->normalized);
                for (i = 0; i < count; i ++) {
                    if (is_add) {
                        ecs_add_id(world, entity, ids[i]);
                    } else {
                        ecs_remove_id(world, entity, ids[i]);
                    }
                }
            }

            ecs_term_fini(&term);
        }
    }
}
#endif

/* If operation is not deferred, add/remove components by finding the target
 * table and moving the entity towards it. */
static 
void traverse_add_remove(
    ecs_world_t *world,
    ecs_entity_t result,
    const char *name,
    const ecs_entity_desc_t *desc,
    ecs_entity_t scope,
    ecs_id_t with,
    bool new_entity,
    bool name_assigned)
{
    const char *sep = desc->sep;

    /* Find existing table */
    ecs_entity_info_t info = {0};
    ecs_table_t *src_table = NULL, *table = NULL;
    if (!new_entity) {
        if (ecs_get_info(world, result, &info)) {
            table = info.table;
        }
    }

    ecs_entity_t added_buffer[ECS_MAX_ADD_REMOVE];
    ecs_ids_t added = { .array = added_buffer };

    ecs_entity_t removed_buffer[ECS_MAX_ADD_REMOVE];
    ecs_ids_t removed = { .array = removed_buffer };

    /* Find destination table */

    /* If this is a new entity without a name, add the scope. If a name is
     * provided, the scope will be added by the add_path_w_sep function */
    if (new_entity) {
        if (new_entity && scope && !name && !name_assigned) {
            ecs_entity_t id = ecs_pair(EcsChildOf, scope);
            ecs_entities_t arr = { .array = &id, .count = 1 };
            table = ecs_table_traverse_add(world, table, &arr, &added);
            ecs_assert(table != NULL, ECS_INVALID_PARAMETER, NULL);
        }

        if (with) {
            ecs_entities_t arr = { .array = &with, .count = 1 };
            table = ecs_table_traverse_add(world, table, &arr, &added);
            ecs_assert(table != NULL, ECS_INVALID_PARAMETER, NULL);            
        }
    }

    /* If a name is provided but not yet assigned, add the Name component */
    if (name && !name_assigned) {
        ecs_entity_t id = ecs_id(EcsName);
        ecs_ids_t arr = { .array = &id, .count = 1 };
        table = ecs_table_traverse_add(world, table, &arr, &added);
        ecs_assert(table != NULL, ECS_INVALID_PARAMETER, NULL);            
    }

    /* Add components from the 'add' id array */
    int32_t i = 0;
    ecs_id_t id;
    const ecs_id_t *ids = desc->add;
    while ((i < ECS_MAX_ADD_REMOVE) && (id = ids[i ++])) {
        ecs_ids_t arr = { .array = &id, .count = 1 };
        table = ecs_table_traverse_add(world, table, &arr, &added);
        ecs_assert(table != NULL, ECS_INVALID_PARAMETER, NULL);
    }

    /* Add components from the 'remove' id array */
    i = 0;
    ids = desc->remove;
    while ((i < ECS_MAX_ADD_REMOVE) && (id = ids[i ++])) {
        ecs_entities_t arr = { .array = &id, .count = 1 };
        table = ecs_table_traverse_remove(world, table, &arr, &removed);
        ecs_assert(table != NULL, ECS_INVALID_PARAMETER, NULL);
    }

    /* Add components from the 'add_expr' expression */
    if (desc->add_expr) {
#ifdef FLECS_PARSER
        table = traverse_from_expr(
            world, table, name, desc->add_expr, &added, true, true);
#else
        ecs_abort(ECS_UNSUPPORTED, "parser addon is not available");
#endif
    }

    /* Remove components from the 'remove_expr' expression */
    if (desc->remove_expr) {
#ifdef FLECS_PARSER
    table = traverse_from_expr(
        world, table, name, desc->remove_expr, &removed, false, true);
#else
        ecs_abort(ECS_UNSUPPORTED, "parser addon is not available");
#endif
    }

    /* Commit entity to destination table */
    if (src_table != table) {
        commit(world, result, &info, table, &added, &removed, true);
    }

    /* Set name */
    if (name && !name_assigned) {
        ecs_add_path_w_sep(world, result, scope, name, sep, NULL);   
    }

    if (desc->symbol) {
        EcsName *name_ptr = ecs_get_mut(world, result, EcsName, NULL);
        if (name_ptr->symbol) {
            ecs_assert(!ecs_os_strcmp(desc->symbol, name_ptr->symbol),
                ECS_INCONSISTENT_NAME, desc->symbol);
        } else {
            name_ptr->symbol = ecs_os_strdup(desc->symbol);
        }
    }

    if (added.count > ECS_MAX_ADD_REMOVE) {
        ecs_os_free(added.array);
    }
    if (removed.count > ECS_MAX_ADD_REMOVE) {
        ecs_os_free(removed.array);
    }
}

/* When in deferred mode, we need to add/remove components one by one using
 * the regular operations. */
static 
void deferred_add_remove(
    ecs_world_t *world,
    ecs_entity_t entity,
    const char *name,
    const ecs_entity_desc_t *desc,
    ecs_entity_t scope,
    ecs_id_t with,
    bool new_entity,
    bool name_assigned)
{
    const char *sep = desc->sep;

    /* If this is a new entity without a name, add the scope. If a name is
     * provided, the scope will be added by the add_path_w_sep function */
    if (new_entity) {
        if (new_entity && scope && !name && !name_assigned) {
            ecs_add_id(world, entity, ecs_pair(EcsChildOf, scope));
        }

        if (with) {
            ecs_add_id(world, entity, with);
        }
    }

    /* Add components from the 'add' id array */
    int32_t i = 0;
    ecs_id_t id;
    const ecs_id_t *ids = desc->add;
    while ((i < ECS_MAX_ADD_REMOVE) && (id = ids[i ++])) {
        ecs_add_id(world, entity, id);
    }

    /* Add components from the 'remove' id array */
    i = 0;
    ids = desc->remove;
    while ((i < ECS_MAX_ADD_REMOVE) && (id = ids[i ++])) {
        ecs_remove_id(world, entity, id);
    }

    /* Add components from the 'add_expr' expression */
    if (desc->add_expr) {
#ifdef FLECS_PARSER
        defer_from_expr(world, entity, name, desc->add_expr, true, true);
#else
        ecs_abort(ECS_UNSUPPORTED, "parser addon is not available");
#endif
    }

    /* Remove components from the 'remove_expr' expression */
    if (desc->remove_expr) {
#ifdef FLECS_PARSER
        defer_from_expr(world, entity, name, desc->remove_expr, true, false);
#else
        ecs_abort(ECS_UNSUPPORTED, "parser addon is not available");
#endif
    }

    /* Set name */
    if (name && !name_assigned) {
        ecs_add_path_w_sep(world, entity, scope, name, sep, NULL);   
    }

    /* Currently it's not supported to set the symbol from a deferred context */
    if (desc->symbol) {
        const EcsName *ptr = ecs_get(world, entity, EcsName);
        (void)ptr;
        
        ecs_assert(ptr != NULL, ECS_UNSUPPORTED, NULL);
        ecs_assert(!ecs_os_strcmp(ptr->symbol, desc->symbol), 
            ECS_UNSUPPORTED, NULL);
    }
}

ecs_entity_t ecs_entity_init(
    ecs_world_t *world,
    const ecs_entity_desc_t *desc)
{
    ecs_assert(world != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(desc != NULL, ECS_INTERNAL_ERROR, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);
    ecs_entity_t scope = ecs_get_scope(world);
    ecs_id_t with = ecs_get_with(world);

    const char *name = desc->name;
    const char *sep = desc->sep;
    if (!sep) {
        sep = ".";
    }

    bool new_entity = false;
    bool name_assigned = false;

    /* Remove optional prefix from name. Entity names can be derived from 
     * language identifiers, such as components (typenames) and systems
     * function names). Because C does not have namespaces, such identifiers
     * often encode the namespace as a prefix.
     * To ensure interoperability between C and C++ (and potentially other 
     * languages with namespacing) the entity must be stored without this prefix
     * and with the proper namespace, which is what the name_prefix is for */
    const char *prefix = world->name_prefix;
    if (name && prefix) {
        ecs_size_t len = ecs_os_strlen(prefix);
        if (!ecs_os_strncmp(name, prefix, len) && 
           (isupper(name[len]) || name[len] == '_')) 
        {
            if (name[len] == '_') {
                name = name + len + 1;
            } else {
                name = name + len;
            }
        }
    }

    /* Find or create entity */
    ecs_entity_t result = desc->entity;
    if (!result) {
        if (name) {
            result = ecs_lookup_path_w_sep(world, 0, name, sep, NULL, false);
            if (result) {
                name_assigned = true;
            }
        }

        if (!result) {
            if (desc->use_low_id) {
                result = ecs_new_component_id(world);
            } else {
                result = ecs_new_id(world);
            }
            new_entity = true;
            ecs_assert(ecs_get_type(world, result) == NULL, 
                ECS_INTERNAL_ERROR, NULL);
        }
    } else {
        ecs_assert(ecs_is_valid(world, result), ECS_INVALID_PARAMETER, NULL);

        name_assigned = ecs_has(world, result, EcsName);
        if (name && name_assigned) {
            /* If entity has name, verify that name matches */
            char *path = ecs_get_path_w_sep(world, scope, result, 0, sep, NULL);
            if (path) {
                if (ecs_os_strcmp(path, name)) {
                    /* Mismatching name */
                    ecs_os_free(path);
                    return 0;
                }
                ecs_os_free(path);
            }
        }
    }

    if (stage->defer) {
        deferred_add_remove(world, result, name, desc, 
            scope, with, new_entity, name_assigned);
    } else {
        traverse_add_remove(world, result, name, desc,
            scope, with, new_entity, name_assigned);
    }

    return result;
}

ecs_entity_t ecs_component_init(
    ecs_world_t *world,
    const ecs_component_desc_t *desc)
{
    ecs_assert(world != NULL, ECS_INTERNAL_ERROR, NULL);
    world = (ecs_world_t*)ecs_get_world(world);

    bool is_readonly = world->is_readonly;
    bool is_deferred = ecs_is_deferred(world);
    int32_t defer_count = 0;
    ecs_vector_t *defer_queue = NULL;
    ecs_stage_t *stage = NULL;

    /* If world is readonly or deferring is enabled, component registration can
     * still happen directly on the main storage, but only if the application
     * is singlethreaded. */
    if (is_readonly || is_deferred) {
        ecs_assert(ecs_get_stage_count(world) <= 1, 
            ECS_INVALID_WHILE_ITERATING, NULL);

        /* Silence readonly warnings */
        world->is_readonly = false;

        /* Hack around safety checks (this ought to look ugly) */
        ecs_world_t *temp_world = world;
        stage = ecs_stage_from_world(&temp_world);
        defer_count = stage->defer;
        defer_queue = stage->defer_queue;
        stage->defer = 0;
        stage->defer_queue = NULL;
    }

    ecs_entity_desc_t entity_desc = desc->entity;
    entity_desc.use_low_id = true;
    if (!entity_desc.symbol) {
        entity_desc.symbol = entity_desc.name;
    }

    ecs_entity_t e = desc->entity.entity;
    ecs_entity_t result = ecs_entity_init(world, &entity_desc);
    if (!result) {
        return 0;
    }

    bool added = false;
    EcsComponent *ptr = ecs_get_mut(world, result, EcsComponent, &added);

    if (added) {
        ptr->size = ecs_from_size_t(desc->size);
        ptr->alignment = ecs_from_size_t(desc->alignment);
    } else {
        if (ptr->size != ecs_from_size_t(desc->size)) {
            ecs_abort(ECS_INVALID_COMPONENT_SIZE, desc->entity.name);
        }
        if (ptr->alignment != ecs_from_size_t(desc->alignment)) {
            ecs_abort(ECS_INVALID_COMPONENT_ALIGNMENT, desc->entity.name);
        }
    }

    ecs_modified(world, result, EcsComponent);

    if (e > world->stats.last_component_id && e < ECS_HI_COMPONENT_ID) {
        world->stats.last_component_id = e + 1;
    }

    /* Ensure components cannot be deleted */
    ecs_add_pair(world, result, EcsOnDelete, EcsThrow);    

    if (is_readonly || is_deferred) {
        /* Restore readonly state / defer count */
        world->is_readonly = is_readonly;
        stage->defer = defer_count;
        stage->defer_queue = defer_queue;
    }

    ecs_assert(result != 0, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ecs_has(world, result, EcsComponent), ECS_INTERNAL_ERROR, NULL);

    return result;
}

ecs_entity_t ecs_type_init(
    ecs_world_t *world,
    const ecs_type_desc_t *desc)
{
    ecs_entity_t result = ecs_entity_init(world, &desc->entity);
    if (!result) {
        return 0;
    }

    ecs_table_t *table = NULL, *normalized = NULL;

    ecs_entity_t added_buffer[ECS_MAX_ADD_REMOVE];
    ecs_ids_t added = { .array = added_buffer };

    /* Find destination table (and type) */

    /* Add components from the 'add' id array */
    int32_t i = 0;
    ecs_id_t id;
    const ecs_id_t *ids = desc->ids;
    while ((i < ECS_MAX_ADD_REMOVE) && (id = ids[i ++])) {
        ecs_ids_t arr = { .array = &id, .count = 1 };
        normalized = ecs_table_traverse_add(world, normalized, &arr, &added);
        table = ecs_table_traverse_add(world, table, &arr, &added);
        ecs_assert(table != NULL, ECS_INVALID_PARAMETER, NULL);
    }

    /* If expression is set, add it to the table */
    if (desc->ids_expr) {
#ifdef FLECS_PARSER
        normalized = traverse_from_expr(
            world, normalized, desc->entity.name, desc->ids_expr, &added, 
            true, true);

        table = traverse_from_expr(
            world, table, desc->entity.name, desc->ids_expr, &added, 
            true, false);
#else
        ecs_abort(ECS_UNSUPPORTED, "parser addon is not available");
#endif
    }

    if (added.count > ECS_MAX_ADD_REMOVE) {
        ecs_os_free(added.array);
    }

    ecs_type_t type = NULL;
    ecs_type_t normalized_type = NULL;
    
    if (table) {
        type = table->type;
    }
    if (normalized) {
        normalized_type = normalized->type;
    }

    bool add = false;
    EcsType *type_ptr = ecs_get_mut(world, result, EcsType, &add);
    if (add) {
        type_ptr->type = type;
        type_ptr->normalized = normalized_type;

        /* This will allow the type to show up in debug tools */
        if (type) {
            ecs_map_set(world->type_handles, (uintptr_t)type, &result);
        }

        ecs_modified(world, result, EcsType);
    } else {
        if (type_ptr->type != type) {
            ecs_abort(ECS_ALREADY_DEFINED, desc->entity.name);
        }
        if (type_ptr->normalized != normalized_type) {
            ecs_abort(ECS_ALREADY_DEFINED, desc->entity.name);
        }        
    }

    return result;
}

const ecs_entity_t* ecs_bulk_new_w_data(
    ecs_world_t *world,
    int32_t count,
    const ecs_ids_t *components,
    void * data)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);
    const ecs_entity_t *ids;
    if (ecs_defer_bulk_new(world, stage, count, components, data, &ids)) {
        return ids;
    }
    ecs_type_t type = ecs_type_find(world, components->array, components->count);
    ecs_table_t *table = ecs_table_from_type(world, type);    
    ids = new_w_data(world, table, NULL, count, data, NULL);
    ecs_defer_flush(world, stage);
    return ids;
}

const ecs_entity_t* ecs_bulk_new_w_type(
    ecs_world_t *world,
    ecs_type_t type,
    int32_t count)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);
    const ecs_entity_t *ids;
    ecs_ids_t components = ecs_type_to_entities(type);
    if (ecs_defer_bulk_new(world, stage, count, &components, NULL, &ids)) {
        return ids;
    }
    ecs_table_t *table = ecs_table_from_type(world, type);
    ids = new_w_data(world, table, NULL, count, NULL, NULL);
    ecs_defer_flush(world, stage);
    return ids;
}

const ecs_entity_t* ecs_bulk_new_w_id(
    ecs_world_t *world,
    ecs_id_t id,
    int32_t count)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);
    ecs_ids_t components = {
        .array = &id,
        .count = 1
    };
    const ecs_entity_t *ids;
    if (ecs_defer_bulk_new(world, stage, count, &components, NULL, &ids)) {
        return ids;
    }
    ecs_table_t *table = ecs_table_find_or_create(world, &components);
    ids = new_w_data(world, table, NULL, count, NULL, NULL);
    ecs_defer_flush(world, stage);
    return ids;
}

void ecs_clear(
    ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);
    if (ecs_defer_clear(world, stage, entity)) {
        return;
    }

    ecs_entity_info_t info;
    info.table = NULL;

    ecs_get_info(world, entity, &info);

    ecs_table_t *table = info.table;
    if (table) {
        ecs_type_t type = table->type;

        /* Remove all components */
        ecs_entities_t to_remove = ecs_type_to_entities(type);
        remove_ids_w_info(world, entity, &info, &to_remove);
    }    

    ecs_defer_flush(world, stage);
}

static
void on_delete_action(
    ecs_world_t *world,
    ecs_entity_t entity);

static
void throw_invalid_delete(
    ecs_world_t *world,
    ecs_id_t id)
{
    char buff[256];
    ecs_entity_str(world, id, buff, 256);
    ecs_abort(ECS_INVALID_DELETE, buff);    
}

static
void remove_from_table(
    ecs_world_t *world,
    ecs_table_t *src_table,
    ecs_id_t id,
    int32_t column)
{
    ecs_entity_t removed_buffer[ECS_MAX_ADD_REMOVE];
    ecs_ids_t removed = { .array = removed_buffer };    
    ecs_table_t *dst_table = src_table;
    bool is_pair = ECS_HAS_ROLE(id, PAIR);

    /* If id is pair, ensure dst_table has no instances of the relation */
    if (is_pair && ECS_PAIR_RELATION(id) != EcsWildcard) {
        int32_t i, count = ecs_vector_count(src_table->type);
        ecs_id_t *ids = ecs_vector_first(src_table->type, ecs_id_t);
        for (i = column; i < count; i ++) {
            ecs_id_t e = ids[i];
            if (ECS_PAIR_RELATION(id) != ECS_PAIR_RELATION(e)) {
                break;
            }

            ecs_ids_t to_remove = { .array = &e, .count = 1 };
            dst_table = ecs_table_traverse_remove(
                world, dst_table, &to_remove, &removed);
        }
    } else {
        /* If pair has a relationship wildcard, this removes a relationship for
         * a specific object. Get the relation + object to delete */
        if (is_pair) {
            ecs_id_t *ids = ecs_vector_first(src_table->type, ecs_id_t);
            id = ids[column];
        }
        ecs_ids_t to_remove = { .array = &id, .count = 1 };
        dst_table = ecs_table_traverse_remove(
            world, dst_table, &to_remove, &removed);
    }

    ecs_assert(dst_table != NULL, ECS_INTERNAL_ERROR, NULL);

    if (!dst_table->type) {
        /* If this removes all components, clear table */
        ecs_table_clear_entities(world, src_table);
    } else {
        /* Otherwise, merge table into dst_table */
        if (dst_table != src_table) {
            ecs_data_t *src_data = ecs_table_get_data(src_table);
            int32_t src_count = ecs_table_count(src_table);
            if (removed.count && src_data) {
                ecs_run_remove_actions(world, src_table, 
                    0, src_count, &removed);
            }

            ecs_data_t *dst_data = ecs_table_get_data(dst_table);
            ecs_table_merge(world, dst_table, src_table, dst_data, src_data);
        }
    }
}

static
void delete_objects(
    ecs_world_t *world,
    ecs_table_t *table)
{
    ecs_data_t *data = ecs_table_get_data(table);
    if (data) {
        ecs_entity_t *entities = ecs_vector_first(
            data->entities, ecs_entity_t);

        int32_t i, count = ecs_vector_count(data->entities);
        for (i = 0; i < count; i ++) {
            ecs_entity_t e = entities[i];
            ecs_record_t *r = ecs_sparse_get(
                world->store.entity_index, ecs_record_t, e);
            
            /* If row is negative, it means the entity is being monitored. Only
             * monitored entities can have delete actions */
            if (r && r->row < 0) {
                /* Make row positive which prevents infinite recursion in case
                 * of cyclic delete actions */
                r->row = (-r->row);

                /* Run delete actions for objects */
                on_delete_action(world, entities[i]);
            }        
        }

        /* Clear components from table (invokes destructors, OnRemove) */
        ecs_table_delete_entities(world, table);            
    } 
}

static
void delete_tables_for_id_record(
    ecs_world_t *world,
    ecs_id_t id,
    ecs_id_record_t *idr)
{
    /* Delete tables in id record. Because deleting the table updates the
     * map, remove the map pointer from the id record. This will prevent the
     * table from removing itself from the map as it is deleted, which
     * allows for iterating the map without changing it. */
    
    if (!world->is_fini) {
        ecs_map_t *table_index = idr->table_index;
        idr->table_index = NULL;
        ecs_map_iter_t it = ecs_map_iter(table_index);
        ecs_table_record_t *tr;
        while ((tr = ecs_map_next(&it, ecs_table_record_t, NULL))) {
            ecs_delete_table(world, tr->table);
        }
        ecs_map_free(table_index);

        ecs_clear_id_record(world, id);
    }
}

static
void on_delete_object_action(
    ecs_world_t *world,
    ecs_id_t id)
{
    ecs_id_record_t *idr = ecs_get_id_record(world, id);
    if (idr) {
        ecs_map_t *table_index = idr->table_index;
        ecs_map_iter_t it = ecs_map_iter(table_index);
        ecs_table_record_t *tr;

        /* Execute the on delete action */
        while ((tr = ecs_map_next(&it, ecs_table_record_t, NULL))) {
            ecs_table_t *table = tr->table;
            if (!ecs_table_count(table)) {
                continue;
            }

            ecs_id_t *rel_id = ecs_vector_get(table->type, ecs_id_t, tr->column);
            ecs_assert(rel_id != NULL, ECS_INTERNAL_ERROR, NULL);

            ecs_entity_t rel = ECS_PAIR_RELATION(*rel_id);
            /* delete_object_action should be invoked for relations */
            ecs_assert(rel != 0, ECS_INTERNAL_ERROR,  NULL);

            /* Get the record for the relation, to find the delete action */
            ecs_id_record_t *idrr = ecs_get_id_record(world, rel);
            if (idrr) {
                ecs_entity_t action = idrr->on_delete_object;
                if (!action || action == EcsRemove) {
                    remove_from_table(world, table, id, tr->column);
                } else if (action == EcsDelete) {
                    delete_objects(world, table);
                } else if (action == EcsThrow) {
                    throw_invalid_delete(world, id);
                }
            } else {
                /* If no record was found for the relation, assume the default
                 * action which is to remove the relationship */
                remove_from_table(world, table, id, tr->column);
            }
        }

        delete_tables_for_id_record(world, id, idr);
    }
}

static
void on_delete_relation_action(
    ecs_world_t *world,
    ecs_id_t id)
{
    ecs_id_record_t *idr = ecs_get_id_record(world, id);

    if (idr) {
        ecs_entity_t on_delete = idr->on_delete;
        if (on_delete == EcsThrow) {
            throw_invalid_delete(world, id);
        }

        ecs_map_t *table_index = idr->table_index;
        ecs_map_iter_t it = ecs_map_iter(table_index);
        ecs_table_record_t *tr;
        while ((tr = ecs_map_next(&it, ecs_table_record_t, NULL))) {
            ecs_table_t *table = tr->table;
            ecs_entity_t action = idr->on_delete;

            if (!action || action == EcsRemove) {
                remove_from_table(world, table, id, tr->column);
            } else if (action == EcsDelete) {
                delete_objects(world, table);
            }
        }

        delete_tables_for_id_record(world, id, idr);
    }
}

static
void on_delete_action(
    ecs_world_t *world,
    ecs_entity_t entity)
{
    on_delete_relation_action(world, entity);
    on_delete_relation_action(world, ecs_pair(entity, EcsWildcard));
    on_delete_object_action(world, ecs_pair(EcsWildcard, entity));
}

void ecs_delete_children(
    ecs_world_t *world,
    ecs_entity_t parent)
{
    on_delete_action(world, parent);
}

void ecs_delete(
    ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(entity != 0, ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);
    if (ecs_defer_delete(world, stage, entity)) {
        return;
    }

    ecs_record_t *r = ecs_sparse_get(
        world->store.entity_index, ecs_record_t, entity);
    if (r) {
        ecs_entity_info_t info = {0};
        set_info_from_record(&info, r);

        ecs_table_t *table = info.table;
        uint64_t table_id = 0;
        if (table) {
            table_id = table->id;
        }

        if (info.is_watched) {
            /* Make row positive which prevents infinite recursion in case
             * of cyclic delete actions */
            r->row = (-r->row);

            /* Ensure that the store contains no dangling references to the
             * deleted entity (as a component, or as part of a relation) */
            on_delete_action(world, entity);

            /* Refetch data. In case of circular relations, the entity may have
             * moved to a different table. */
            set_info_from_record(&info, r);
            
            table = info.table;
            if (table) {
                table_id = table->id;
            } else {
                table_id = 0;
            }

            if (r->table) {
                ecs_ids_t to_remove = ecs_type_to_entities(r->table->type);
                update_component_monitors(world, entity, NULL, &to_remove);
            }
        }

        ecs_assert(!table_id || table, ECS_INTERNAL_ERROR, NULL);

        /* If entity has components, remove them. Check if table is still alive,
         * as delete actions could have deleted the table already. */
        if (table_id && ecs_sparse_is_alive(world->store.tables, table_id)) {
            ecs_type_t type = table->type;
            ecs_ids_t to_remove = ecs_type_to_entities(type);
            delete_entity(world, table, info.data, info.row, &to_remove);
            r->table = NULL;
        }

        r->row = 0;

        /* Remove (and invalidate) entity after executing handlers */
        ecs_sparse_remove(world->store.entity_index, entity);
    }

    ecs_defer_flush(world, stage);
}

void ecs_add_type(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_type_t type)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);

    ecs_entities_t components = ecs_type_to_entities(type);
    add_ids(world, entity, &components);
}

void ecs_add_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);

    ecs_entities_t components = { .array = &id, .count = 1 };
    add_ids(world, entity, &components);
}

void ecs_remove_type(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_type_t type)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);

    ecs_entities_t components = ecs_type_to_entities(type);
    remove_ids(world, entity, &components);
}

void ecs_remove_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);

    ecs_entities_t components = { .array = &id, .count = 1 };
    remove_ids(world, entity, &components);
}

// DEPRECATED
void ecs_add_remove_entity(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id_add,
    ecs_id_t id_remove)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id_add), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id_remove), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);

    ecs_ids_t components_add = { .array = &id_add, .count = 1 };      
    ecs_ids_t components_remove = { .array = &id_remove, .count = 1 };      
    add_remove(world, entity, &components_add, &components_remove);
}

void ecs_add_remove_type(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_type_t to_add,
    ecs_type_t to_remove)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);

    ecs_ids_t components_add = ecs_type_to_entities(to_add);
    ecs_ids_t components_remove = ecs_type_to_entities(to_remove);
    add_remove(world, entity, &components_add, &components_remove);
}

ecs_entity_t ecs_clone(
    ecs_world_t *world,
    ecs_entity_t dst,
    ecs_entity_t src,
    bool copy_value)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(src != 0, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, src), ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);
    
    if (!dst) {
        dst = ecs_new_id(world);
    }

    if (ecs_defer_clone(world, stage, dst, src, copy_value)) {
        return dst;
    }

    ecs_entity_info_t src_info;
    bool found = ecs_get_info(world, src, &src_info);
    ecs_table_t *src_table = src_info.table;

    if (!found || !src_table) {
        return dst;
    }

    ecs_type_t src_type = src_table->type;
    ecs_ids_t to_add = ecs_type_to_entities(src_type);

    ecs_entity_info_t dst_info = {0};
    dst_info.row = new_entity(world, dst, &dst_info, src_table, &to_add, true);

    if (copy_value) {
        ecs_table_move(world, dst, src, src_table, dst_info.data, 
            dst_info.row, src_table, src_info.data, src_info.row, true);

        int i;
        for (i = 0; i < to_add.count; i ++) {
            ecs_emit(world, &(ecs_event_desc_t){EcsOnSet, NULL, EcsPayloadTable, 
                .payload.table = {src_info.table, dst_info.row, 1} });
        }
    }

    ecs_defer_flush(world, stage);

    return dst;
}

const void* ecs_get_id(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_stage_from_readonly_world(world)->asynchronous == false, 
        ECS_INVALID_PARAMETER, NULL);

    world = ecs_get_world(world);
    ecs_object_assert(world, ecs_world_t);

    ecs_record_t *r = ecs_eis_get(world, entity);
    if (!r) {
        return NULL;
    }

    ecs_table_t *table = r->table;
    if (!table) {
        return NULL;
    }

    ecs_id_record_t *idr = ecs_get_id_record(world, id);
    if (!idr) {
        return NULL;
    }

    ecs_table_record_t *tr = ecs_map_get(idr->table_index, 
        ecs_table_record_t, table->id);
    if (!tr) {
       return get_base_component(world, table, id, idr->table_index, NULL, 0);
    }

    bool is_monitored;
    int32_t row = ecs_record_to_row(r->row, &is_monitored);
    return get_component_w_index(table, tr->column, row);
}

const void* ecs_get_ref_w_id(
    const ecs_world_t * world,
    ecs_ref_t * ref,
    ecs_entity_t entity,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ref != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(!entity || !ref->entity || entity == ref->entity, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(!id || !ref->component || id == ref->component, ECS_INVALID_PARAMETER, NULL);
    ecs_record_t *record = ref->record;

    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    entity |= ref->entity;

    if (!record) {
        record = ecs_eis_get(world, entity);
    }

    if (!record || !record->table) {
        return NULL;
    }

    ecs_table_t *table = record->table;

    if (ref->record == record &&
        ref->table == table &&
        ref->row == record->row &&
        ref->alloc_count == table->alloc_count)
    {
        return ref->ptr;
    }

    id |= ref->component;

    int32_t row = record->row;

    ref->entity = entity;
    ref->component = id;
    ref->table = table;
    ref->row = record->row;
    ref->alloc_count = table->alloc_count;

    if (table) {
        bool is_monitored;
        row = ecs_record_to_row(row, &is_monitored);
        ref->ptr = get_component(world, table, row, id);
    }

    ref->record = record;

    return ref->ptr;
}

void* ecs_get_mut_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id,
    bool * is_added)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);
    
    ecs_stage_t *stage = ecs_stage_from_world(&world);
    void *result;

    if (ecs_defer_set(
        world, stage, EcsOpMut, entity, id, 0, NULL, &result, is_added))
    {
        return result;
    }

    ecs_entity_info_t info;
    result = get_mutable(world, entity, id, &info, is_added);
    
    /* Store table so we can quickly check if returned pointer is still valid */
    ecs_table_t *table = info.record->table;
    ecs_assert(table != NULL, ECS_INTERNAL_ERROR, NULL);

    /* Keep track of alloc count of table, since even if the entity has not
     * moved, other entities could have been added to the table which could
     * reallocate arrays. Also store the row, as the entity could have 
     * reallocated. */
    int32_t alloc_count = table->alloc_count;
    int32_t row = info.record->row;
    
    ecs_defer_flush(world, stage);

    /* Ensure that after flushing, the pointer is still valid. Flushing may
     * trigger callbacks, which could do anything with the entity */
    if (table != info.record->table || 
        alloc_count != info.record->table->alloc_count ||
        row != info.record->row) 
    {
        if (ecs_get_info(world, entity, &info) && info.table) {
            result = get_component(world, info.table, info.row, id);
        } else {
            /* A trigger has removed the component we just added. This is not
             * allowed, an application should always be able to assume that
             * get_mut returns a valid pointer. */
            ecs_assert(false, ECS_INVALID_OPERATION, NULL);
        }
    }

    return result;
}

void* ecs_emplace_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(!ecs_has_id(world, entity, id), ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);
    void *result;

    if (ecs_defer_set(
        world, stage, EcsOpMut, entity, id, 0, NULL, &result, NULL))
    {
        return result;
    }

    ecs_entity_info_t info;
    ecs_get_info(world, entity, &info);

    ecs_ids_t to_add = {
        .array = &id,
        .count = 1
    };

    add_ids_w_info(world, entity, &info, &to_add, 
        false /* Add component without constructing it */ );

    void *ptr = get_component(world, info.table, info.row, id);

    ecs_defer_flush(world, stage);

    return ptr;
}

void ecs_modified_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);

    if (ecs_defer_modified(world, stage, entity, id)) {
        return;
    }

    /* If the entity does not have the component, calling ecs_modified is 
     * invalid. The assert needs to happen after the defer statement, as the
     * entity may not have the component when this function is called while
     * operations are being deferred. */
    ecs_assert(ecs_has_id(world, entity, id), 
        ECS_INVALID_PARAMETER, NULL);

    ecs_entity_info_t info = {0};
    if (ecs_get_info(world, entity, &info)) {
        ecs_ids_t added = {
            .array = &id,
            .count = 1
        };

        ecs_emit(world, &(ecs_event_desc_t){EcsOnSet, &added, EcsPayloadTable, 
            .payload.table = {info.table, info.row, 1} });
    }

    ecs_table_mark_dirty(info.table, id);
    
    ecs_defer_flush(world, stage);
}

static
ecs_entity_t assign_ptr_w_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id,
    size_t size,
    void * ptr,
    bool is_move,
    bool do_notify)
{
    ecs_stage_t *stage = ecs_stage_from_world(&world);
    ecs_object_assert(world, ecs_world_t);

    ecs_ids_t added = {
        .array = &id,
        .count = 1
    };

    if (!entity) {
        entity = ecs_new_id(world);
        ecs_entity_t scope = stage->scope;
        if (scope) {
            ecs_add_pair(world, entity, EcsChildOf, scope);
        }
    }

    if (ecs_defer_set(world, stage, EcsOpSet, entity, id, 
        ecs_from_size_t(size), ptr, NULL, NULL))
    {
        return entity;
    }

    ecs_entity_info_t info;

    void *dst = get_mutable(world, entity, id, &info, NULL);

    /* This can no longer happen since we defer operations */
    ecs_assert(dst != NULL, ECS_INTERNAL_ERROR, NULL);

    if (ptr) {
        ecs_entity_t real_id = ecs_get_typeid(world, id);
        const ecs_type_info_t *cdata = get_c_info(world, real_id);
        if (cdata) {
            if (is_move) {
                ecs_move_t move = cdata->lifecycle.move;
                if (move) {
                    move(world, real_id, &entity, &entity, dst, ptr, size, 1, 
                        cdata->lifecycle.ctx);
                } else {
                    ecs_os_memcpy(dst, ptr, ecs_from_size_t(size));
                }
            } else {
                ecs_copy_t copy = cdata->lifecycle.copy;
                if (copy) {
                    copy(world, real_id, &entity, &entity, dst, ptr, size, 1, 
                        cdata->lifecycle.ctx);
                } else {
                    ecs_os_memcpy(dst, ptr, ecs_from_size_t(size));
                }
            }
        } else {
            ecs_os_memcpy(dst, ptr, ecs_from_size_t(size));
        }
    } else {
        memset(dst, 0, size);
    }

    ecs_table_mark_dirty(info.table, id);

    if (do_notify) {
        ecs_emit(world, &(ecs_event_desc_t){EcsOnSet, &added, EcsPayloadTable, 
            .payload.table = {info.table, info.row, 1} });
    }

    ecs_defer_flush(world, stage);

    return entity;
}

ecs_entity_t ecs_set_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id,
    size_t size,
    const void *ptr)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(!entity || ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);

    /* Safe to cast away const: function won't modify if move arg is false */
    return assign_ptr_w_id(
        world, entity, id, size, (void*)ptr, false, true);
}

ecs_entity_t ecs_get_case(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_entity_t sw_id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, sw_id), ECS_INVALID_PARAMETER, NULL);

    ecs_entity_info_t info;
    ecs_table_t *table;
    if (!ecs_get_info(world, entity, &info) || !(table = info.table)) {
        return 0;
    }

    sw_id = sw_id | ECS_SWITCH;

    ecs_type_t type = table->type;
    int32_t index = ecs_type_index_of(type, sw_id);
    if (index == -1) {
        return 0;
    }

    index -= table->sw_column_offset;
    ecs_assert(index >= 0, ECS_INTERNAL_ERROR, NULL);

    /* Data cannot be NULl, since entity is stored in the table */
    ecs_assert(info.data != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_switch_t *sw = info.data->sw_columns[index].data;  
    return ecs_switch_get(sw, info.row);  
}

void ecs_enable_component_w_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id,
    bool enable)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);

    ecs_stage_t *stage = ecs_stage_from_world(&world);

    if (ecs_defer_enable(
        world, stage, entity, id, enable))
    {
        return;
    } else {
        /* Operations invoked by enable/disable should not be deferred */
        stage->defer --;
    }

    ecs_entity_info_t info;
    ecs_get_info(world, entity, &info);

    ecs_entity_t bs_id = (id & ECS_COMPONENT_MASK) | ECS_DISABLED;
    
    ecs_table_t *table = info.table;
    int32_t index = -1;
    if (table) {
        index = ecs_type_index_of(table->type, bs_id);
    }

    if (index == -1) {
        ecs_add_id(world, entity, bs_id);
        ecs_enable_component_w_id(world, entity, id, enable);
        return;
    }

    index -= table->bs_column_offset;
    ecs_assert(index >= 0, ECS_INTERNAL_ERROR, NULL);

    /* Data cannot be NULl, since entity is stored in the table */
    ecs_assert(info.data != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_bitset_t *bs = &info.data->bs_columns[index].data;
    ecs_assert(bs != NULL, ECS_INTERNAL_ERROR, NULL);

    ecs_bitset_set(bs, info.row, enable);
}

bool ecs_is_component_enabled_w_id(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);

    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    ecs_entity_info_t info;
    ecs_table_t *table;
    if (!ecs_get_info(world, entity, &info) || !(table = info.table)) {
        return false;
    }

    ecs_entity_t bs_id = (id & ECS_COMPONENT_MASK) | ECS_DISABLED;

    ecs_type_t type = table->type;
    int32_t index = ecs_type_index_of(type, bs_id);
    if (index == -1) {
        /* If table does not have DISABLED column for component, component is
         * always enabled, if the entity has it */
        return ecs_has_id(world, entity, id);
    }

    index -= table->bs_column_offset;
    ecs_assert(index >= 0, ECS_INTERNAL_ERROR, NULL);

    /* Data cannot be NULl, since entity is stored in the table */
    ecs_assert(info.data != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_bitset_t *bs = &info.data->bs_columns[index].data;  

    return ecs_bitset_get(bs, info.row);
}

bool ecs_has_id(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);

    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    if (ECS_HAS_ROLE(id, CASE)) {
        ecs_entity_info_t info;
        ecs_table_t *table;
        if (!ecs_get_info(world, entity, &info) || !(table = info.table)) {
            return false;
        }

        int32_t index = ecs_table_switch_from_case(world, table, id);
        ecs_assert(index < table->sw_column_count, ECS_INTERNAL_ERROR, NULL);
        
        ecs_data_t *data = info.data;
        ecs_switch_t *sw = data->sw_columns[index].data;
        ecs_entity_t value = ecs_switch_get(sw, info.row);

        return value == (id & ECS_COMPONENT_MASK);
    } else {
        ecs_type_t type = ecs_get_type(world, entity);
        return ecs_type_has_id(world, type, id);
    }
}

bool ecs_has_type(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_type_t type)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    return has_type(world, entity, type, true, true);
}

ecs_entity_t ecs_get_object_w_id(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_entity_t rel,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(!entity || ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    ecs_assert(!id || ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);

    if (!entity) {
        return 0;
    }

    ecs_type_t type = ecs_get_type(world, entity);    
    ecs_entity_t object;

    /* Find first object for relation */
    if (ecs_type_find_id(world, type, 0, id, rel, 1, 0, &object) != -1) {
        return ecs_get_alive(world, object);
    } else {
        return 0;
    }
}

const char* ecs_get_name(
    const ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);

    const EcsName *id = ecs_get(world, entity, EcsName);
    if (id) {
        return id->value;
    } else {
        return NULL;
    }
}

ecs_type_t ecs_type_from_id(
    ecs_world_t *world,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);

    if (!id) {
        return NULL;
    }

    if (!(id & ECS_ROLE_MASK)) {
        const EcsType *type = ecs_get(world, id, EcsType);
        if (type) {
            return type->normalized;
        }
    }

    return ecs_type_find(world, &id, 1);
}

ecs_id_t ecs_type_to_id(
    const ecs_world_t *world, 
    ecs_type_t type)
{
    (void)world;

    if (!type) {
        return 0;
    }
    
    /* If array contains n entities, it cannot be reduced to a single entity */
    if (ecs_vector_count(type) != 1) {
        ecs_abort(ECS_TYPE_NOT_AN_ENTITY, NULL);
    }

    return *(ecs_vector_first(type, ecs_id_t));
}

ecs_id_t ecs_make_pair(
    ecs_entity_t relation,
    ecs_entity_t object)
{
    return ecs_pair(relation, object);
}

bool ecs_is_valid(
    const ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    /* 0 is not a valid entity id */
    if (!entity) {
        return false;
    }
    
    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    /* When checking roles and/or pairs, the generation count may have been
     * stripped away. Just test if the entity is 0 or not. */
    if (ECS_HAS_ROLE(entity, PAIR)) {
        ecs_entity_t lo = ECS_PAIR_OBJECT(entity);
        ecs_entity_t hi = ECS_PAIR_RELATION(entity);
        return lo != 0 && hi != 0;
    } else
    if (entity & ECS_ROLE) {
        return ecs_entity_t_lo(entity) != 0;
    }

    /* An id may not yet exist in the world which does not mean it cannot be
     * used as an entity identifier. An example is when a hard-coded entity id
     * is used. However, if the entity id does exist in the world, it must be
     * alive. */
    return !ecs_exists(world, entity) || ecs_is_alive(world, entity);
}

bool ecs_is_alive(
    const ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(entity != 0, ECS_INVALID_PARAMETER, NULL);

    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    return ecs_eis_is_alive(world, entity);
}

ecs_entity_t ecs_get_alive(
    const ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(entity != 0, ECS_INVALID_PARAMETER, NULL);

    if (ecs_is_alive(world, entity)) {
        return entity;
    }

    /* Make sure id does not have generation. This guards against accidentally
     * "upcasting" a not alive identifier to a alive one. */
    ecs_assert((uint32_t)entity == entity, ECS_INVALID_PARAMETER, NULL);

    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    ecs_entity_t current = ecs_eis_get_current(world, entity);
    if (!current || !ecs_is_alive(world, current)) {
        return 0;
    }

    return current;
}

void ecs_ensure(
    ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_object_assert(world, ecs_world_t);
    ecs_assert(entity != 0, ECS_INVALID_PARAMETER, NULL);

    if (ecs_eis_is_alive(world, entity)) {
        /* Nothing to be done, already alive */
        return;
    }

    /* Ensure id exists. The underlying datastructure will verify that the
     * generation count matches the provided one. */
    ecs_eis_ensure(world, entity);
}

bool ecs_exists(
    const ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(entity != 0, ECS_INVALID_PARAMETER, NULL);

    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    return ecs_eis_exists(world, entity);
}

ecs_type_t ecs_get_type(
    const ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, entity), ECS_INVALID_PARAMETER, NULL);
    
    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    ecs_record_t *record = ecs_eis_get(world, entity);
    ecs_table_t *table;
    if (record && (table = record->table)) {
        return table->type;
    }
    
    return NULL;
}

ecs_id_t ecs_get_typeid(
    const ecs_world_t *world,
    ecs_id_t id)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_is_valid(world, id), ECS_INVALID_PARAMETER, NULL);

    if (ECS_HAS_ROLE(id, PAIR)) {
        /* Make sure we're not working with a stage */
        world = ecs_get_world(world);

        ecs_entity_t rel = ecs_get_alive(world, ECS_PAIR_RELATION(id));

        /* If relation is marked as a tag, it never has data. Return relation */
        if (ecs_has_id(world, rel, EcsTag)) {
            return 0;
        }

        const EcsComponent *ptr = ecs_get(world, rel, EcsComponent);
        if (ptr && ptr->size != 0) {
            return rel;
        } else {
            ecs_entity_t obj = ecs_get_alive(world, ECS_PAIR_OBJECT(id));
            ptr = ecs_get(world, obj, EcsComponent);
            
            if (ptr && ptr->size != 0) {
                return obj;
            }

            /* Neither relation nor object have data */
            return 0;
        }

    } else if (id & ECS_ROLE_MASK) {
        return 0;
    }

    return id;
}

const EcsComponent* ecs_get_component(
    const ecs_world_t *world,
    ecs_entity_t e)
{
    ecs_entity_t pair = 0;

    /* If this is a pair, get the pair component from the identifier */
    if (ECS_HAS_ROLE(e, PAIR)) {
        pair = e;
        e = ecs_get_alive(world, ECS_PAIR_RELATION(e));

        if (ecs_has_id(world, e, EcsTag)) {
            return NULL;
        }
    }

    if (e & ECS_ROLE_MASK) {
        return NULL;
    }

    const EcsComponent *component = ecs_get(world, e, EcsComponent);
    if ((!component || !component->size) && pair) {
        /* If this is a pair column and the pair is not a component, use
         * the component type of the component the pair is applied to. */
        e = ECS_PAIR_OBJECT(pair);

        /* Because generations are not stored in the pair, get the currently
         * alive id */
        e = ecs_get_alive(world, e);

        /* If a pair is used with a not alive id, the pair is not valid */
        ecs_assert(e != 0, ECS_INTERNAL_ERROR, NULL);

        component = ecs_get(world, e, EcsComponent);
    }

    return component;
}

int32_t ecs_count_type(
    const ecs_world_t *world,
    ecs_type_t type)
{    
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    if (!type) {
        return 0;
    }

    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    return ecs_count_filter(world, &(ecs_filter_t){
        .include = type
    });
}

int32_t ecs_count_id(
    const ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    if (!entity) {
        return 0;
    }

    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    /* Get temporary type that just contains entity */
    ECS_VECTOR_STACK(type, ecs_entity_t, &entity, 1);

    return ecs_count_filter(world, &(ecs_filter_t){
        .include = type
    });
}

int32_t ecs_count_filter(
    const ecs_world_t *world,
    const ecs_filter_t *filter)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    /* Make sure we're not working with a stage */
    world = ecs_get_world(world);

    ecs_sparse_t *tables = world->store.tables;
    int32_t i, count = ecs_sparse_count(tables);
    int32_t result = 0;

    for (i = 0; i < count; i ++) {
        ecs_table_t *table = ecs_sparse_get_dense(tables, ecs_table_t, i);
        if (!filter || ecs_table_match_filter(world, table, filter)) {
            result += ecs_table_count(table);
        }
    }
    
    return result;
}

bool ecs_defer_begin(
    ecs_world_t *world)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_stage_t *stage = ecs_stage_from_world(&world);
    return ecs_defer_none(world, stage);
}

bool ecs_defer_end(
    ecs_world_t *world)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_stage_t *stage = ecs_stage_from_world(&world);
    return ecs_defer_flush(world, stage);
}

static
size_t append_to_str(
    char **buffer,
    const char *str,
    size_t bytes_left,
    size_t *required)
{
    char *ptr = NULL;
    if (buffer) {
        ptr = *buffer;
    }

    size_t len = strlen(str);
    size_t to_write;
    if (bytes_left < len) {
        to_write = bytes_left;
        bytes_left = 0;
    } else {
        to_write = len;
        bytes_left -= len;
    }
    
    if (to_write && ptr) {
        ecs_os_memcpy(ptr, str, to_write);
    }

    (*required) += len;

    if (buffer) {
        (*buffer) += to_write;
    }

    return bytes_left;
}

const char* ecs_role_str(
    ecs_entity_t entity)
{
    if (ECS_HAS_ROLE(entity, CHILDOF)) {
        return "CHILDOF";
    } else
    if (ECS_HAS_ROLE(entity, INSTANCEOF)) {
        return "INSTANCEOF";
    } else
    if (ECS_HAS_ROLE(entity, PAIR)) {
        return "PAIR";
    } else
    if (ECS_HAS_ROLE(entity, DISABLED)) {
        return "DISABLED";
    } else    
    if (ECS_HAS_ROLE(entity, XOR)) {
        return "XOR";
    } else
    if (ECS_HAS_ROLE(entity, OR)) {
        return "OR";
    } else
    if (ECS_HAS_ROLE(entity, AND)) {
        return "AND";
    } else
    if (ECS_HAS_ROLE(entity, NOT)) {
        return "NOT";
    } else
    if (ECS_HAS_ROLE(entity, SWITCH)) {
        return "SWITCH";
    } else
    if (ECS_HAS_ROLE(entity, CASE)) {
        return "CASE";
    } else
    if (ECS_HAS_ROLE(entity, OWNED)) {
        return "OWNED";
    } else {
        return "UNKNOWN";
    }
}

size_t ecs_id_str(
    const ecs_world_t *world,
    ecs_id_t id,
    char *buffer,
    size_t buffer_len)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    world = ecs_get_world(world);

    char *ptr = buffer;
    char **pptr = NULL;
    if (ptr) {
        pptr = &ptr;
    }

    size_t bytes_left = buffer_len - 1, required = 0;
    if (id & ECS_ROLE_MASK && !ECS_HAS_ROLE(id, PAIR)) {
        const char *role = ecs_role_str(id);
        bytes_left = append_to_str(pptr, role, bytes_left, &required);
        bytes_left = append_to_str(pptr, "|", bytes_left, &required);
    }

    ecs_entity_t e = id & ECS_COMPONENT_MASK;

    if (ECS_HAS_ROLE(id, PAIR)) {
        ecs_entity_t lo = ECS_PAIR_OBJECT(id);
        ecs_entity_t hi = ECS_PAIR_RELATION(id);

        if (lo) lo = ecs_get_alive(world, lo);
        if (hi) hi = ecs_get_alive(world, hi);

        if (hi) {
            char *hi_path = ecs_get_fullpath(world, hi);
            bytes_left = append_to_str(pptr, "(", bytes_left, &required);
            bytes_left = append_to_str(pptr, hi_path, bytes_left, &required);
            ecs_os_free(hi_path);
            bytes_left = append_to_str(pptr, ",", bytes_left, &required);
        }

        char *lo_path = ecs_get_fullpath(world, lo);
        bytes_left = append_to_str(pptr, lo_path, bytes_left, &required);
        ecs_os_free(lo_path);

        if (hi) {
            append_to_str(pptr, ")", bytes_left, &required);
        }
    } else {
        char *path = ecs_get_fullpath(world, e);
        append_to_str(pptr, path, bytes_left, &required);
        ecs_os_free(path);
    }

    if (ptr) {
        ptr[0] = '\0';
    }
    
    return required;
}

static
void flush_bulk_new(
    ecs_world_t * world,
    ecs_op_t * op)
{
    ecs_entity_t *ids = op->is._n.entities;
    void **bulk_data = op->is._n.bulk_data;
    if (bulk_data) {
        ecs_entity_t *components = op->components.array;
        int c, c_count = op->components.count;
        for (c = 0; c < c_count; c ++) {
            ecs_entity_t component = components[c];
            const EcsComponent *cptr = ecs_get_component(world, component);
            ecs_assert(cptr != NULL, ECS_INTERNAL_ERROR, NULL);
            size_t size = ecs_to_size_t(cptr->size);
            void *ptr, *data = bulk_data[c];
            int i, count = op->is._n.count;
            for (i = 0, ptr = data; i < count; i ++, ptr = ECS_OFFSET(ptr, size)) {
                assign_ptr_w_id(world, ids[i], component, size, ptr, 
                    true, true);
            }
            ecs_os_free(data);
        }
        ecs_os_free(bulk_data);
    } else {
        int i, count = op->is._n.count;
        for (i = 0; i < count; i ++) {
            add_ids(world, ids[i], &op->components);
        }
    }

    if (op->components.count > 1) {
        ecs_os_free(op->components.array);
    }

    ecs_os_free(ids);
}

static
void free_value(
    ecs_world_t *world,
    ecs_entity_t *entities,
    ecs_id_t id,
    void *value,
    int32_t count)
{
    ecs_entity_t real_id = ecs_get_typeid(world, id);
    const ecs_type_info_t *info = ecs_get_c_info(world, real_id);
    ecs_xtor_t dtor;
    
    if (info && (dtor = info->lifecycle.dtor)) {
        ecs_size_t size = info->size;
        void *ptr;
        int i;
        for (i = 0, ptr = value; i < count; i ++, ptr = ECS_OFFSET(ptr, size)) {
            dtor(world, id, &entities[i], ptr, ecs_to_size_t(size), 1, 
                info->lifecycle.ctx);
        }
    }
}

static
void discard_op(
    ecs_world_t *world,
    ecs_op_t * op)
{
    if (op->kind == EcsOpBulkNew) {
        void **bulk_data = op->is._n.bulk_data;
        if (bulk_data) {
            ecs_entity_t *entities = op->is._n.entities;
            ecs_entity_t *components = op->components.array;
            int c, c_count = op->components.count;
            for (c = 0; c < c_count; c ++) {
                free_value(world, entities, components[c], bulk_data[c], 
                    op->is._n.count);
                ecs_os_free(bulk_data[c]);
            }
        }
    } else {
        void *value = op->is._1.value;
        if (value) {
            free_value(world, &op->is._1.entity, op->component, op->is._1.value, 1);
            ecs_os_free(value);
        }
    }

    ecs_entity_t *components = op->components.array;
    if (components) {
        ecs_os_free(components);
    }    
}

static
bool valid_components(
    ecs_world_t * world,
    ecs_ids_t * entities)
{
    ecs_entity_t *array = entities->array;
    int32_t i, count = entities->count;
    for (i = 0; i < count; i ++) {
        ecs_entity_t e = array[i];
        if (ECS_HAS_RELATION(e, EcsChildOf)) {
            e = ecs_entity_t_lo(e);
            if (ecs_exists(world, e) && !ecs_is_alive(world, e)) {
                return false;
            }
        }
    }
    return true;
}

/* Leave safe section. Run all deferred commands. */
bool ecs_defer_flush(
    ecs_world_t *world,
    ecs_stage_t *stage)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(stage != NULL, ECS_INVALID_PARAMETER, NULL);

    if (!--stage->defer) {
        /* Set to NULL. Processing deferred commands can cause additional
         * commands to get enqueued (as result of reactive systems). Make sure
         * that the original array is not reallocated, as this would complicate
         * processing the queue. */
        ecs_vector_t *defer_queue = stage->defer_queue;
        stage->defer_queue = NULL;

        if (defer_queue) {
            ecs_op_t *ops = ecs_vector_first(defer_queue, ecs_op_t);
            int32_t i, count = ecs_vector_count(defer_queue);
            
            for (i = 0; i < count; i ++) {
                ecs_op_t *op = &ops[i];
                ecs_entity_t e = op->is._1.entity;
                if (op->kind == EcsOpBulkNew) {
                    e = 0;
                }

                /* If entity is no longer alive, this could be because the queue
                * contained both a delete and a subsequent add/remove/set which
                * should be ignored. */
                if (e && !ecs_is_alive(world, e) && ecs_eis_exists(world, e)) {
                    ecs_assert(op->kind != EcsOpNew && op->kind != EcsOpClone, 
                        ECS_INTERNAL_ERROR, NULL);
                    world->discard_count ++;
                    discard_op(world, op);
                    continue;
                }

                if (op->components.count == 1) {
                    op->components.array = &op->component;
                }

                switch(op->kind) {
                case EcsOpNew:
                case EcsOpAdd:
                    if (valid_components(world, &op->components)) {
                        world->add_count ++;
                        add_ids(world, e, &op->components);
                    } else {
                        ecs_delete(world, e);
                    }
                    break;
                case EcsOpRemove:
                    remove_ids(world, e, &op->components);
                    break;
                case EcsOpClone:
                    ecs_clone(world, e, op->component, op->is._1.clone_value);
                    break;
                case EcsOpSet:
                    assign_ptr_w_id(world, e, 
                        op->component, ecs_to_size_t(op->is._1.size), 
                        op->is._1.value, true, true);
                    break;
                case EcsOpMut:
                    assign_ptr_w_id(world, e, 
                        op->component, ecs_to_size_t(op->is._1.size), 
                        op->is._1.value, true, false);
                    break;
                case EcsOpModified:
                    ecs_modified_id(world, e, op->component);
                    break;
                case EcsOpDelete: {
                    ecs_delete(world, e);
                    break;
                }
                case EcsOpEnable:
                    ecs_enable_component_w_id(
                        world, e, op->component, true);
                    break;
                case EcsOpDisable:
                    ecs_enable_component_w_id(
                        world, e, op->component, false);
                    break;
                case EcsOpClear:
                    ecs_clear(world, e);
                    break;
                case EcsOpBulkNew:
                    flush_bulk_new(world, op);

                    /* Continue since flush_bulk_new is repsonsible for cleaning
                    * up resources. */
                    continue;
                }

                if (op->components.count > 1) {
                    ecs_os_free(op->components.array);
                }

                if (op->is._1.value) {
                    ecs_os_free(op->is._1.value);
                }                  
            }

            if (stage->defer_queue) {
                ecs_vector_free(stage->defer_queue);
            }

            /* Restore defer queue */
            ecs_vector_clear(defer_queue);
            stage->defer_queue = defer_queue;
        }

        return true;
    }

    return false;
}

/* Delete operations from queue without executing them. */
bool ecs_defer_purge(
    ecs_world_t *world,
    ecs_stage_t *stage)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(stage != NULL, ECS_INVALID_PARAMETER, NULL);

    if (!--stage->defer) {
        ecs_vector_t *defer_queue = stage->defer_queue;
        stage->defer_queue = NULL;

        if (defer_queue) {
            ecs_op_t *ops = ecs_vector_first(defer_queue, ecs_op_t);
            int32_t i, count = ecs_vector_count(defer_queue);
            for (i = 0; i < count; i ++) {
                discard_op(world, &ops[i]);
            }

            if (stage->defer_queue) {
                ecs_vector_free(stage->defer_queue);
            }

            /* Restore defer queue */
            ecs_vector_clear(defer_queue);
            stage->defer_queue = defer_queue;
        }

        return true;
    }

    return false;
}
