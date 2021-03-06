#include "private_api.h"

static
void populate_columns(
    ecs_world_t *world,
    ecs_observer_t *o,
    ecs_table_t *table,
    ecs_data_t *data,
    ecs_id_t *ids,
    int32_t *columns,
    ecs_type_t *types,
    ecs_id_t event_id,
    int32_t term_index)
{
    int32_t i, count = o->filter.term_count;

    ids[0] = 0;
    columns[0] = 0;
    types[0] = NULL;

    for (i = 0; i < count; i ++) {
        ecs_type_t type = table->type;
        ecs_term_t *t = &o->filter.terms[i];
        int32_t index, ti = t->index;

        ecs_id_t id = t->id;
        if (t->args[0].entity != EcsThis) {
            columns[ti] = 0;
            ids[ti] = id;
            types[ti] = ecs_type_from_id(world, id);
            continue;
        
        } else if (i == term_index) {
            /* If current term is the one that triggered the event, use its
             * id to populate the iterator */
            id = event_id;
            index = ecs_type_match(type, 0, id);

        } else {
            index = ecs_type_match(type, 0, id);

            /* If id was not found, this must be an Or/Not expression */
            if (index == -1) {
                if (t->oper == EcsNot) {
                    ids[ti] = id;
                    types[ti] = ecs_type_from_id(world, id);
                    columns[ti] = 0;
                } else {
                    /* If id is not found and operator isn't Not, must be Or */
                    ecs_assert(t->oper == EcsOr, ECS_INTERNAL_ERROR, NULL);
                }

                continue;
            }
        }

        columns[ti] = index + 1;
        types[ti] = ecs_type_from_id(world, id);

        /* If id is wildcard, find a matching id in the table type */
        if (ecs_id_is_wildcard(id)) {
            ecs_assert(index < ecs_vector_count(type), 
                ECS_INTERNAL_ERROR, NULL);

            /* Get actual id from type */
            id = ecs_vector_get(type, ecs_id_t, index)[0];
        }

        ids[ti] = id;

        if (table->column_count <= index) {
            /* If index is larger than column_count (the number of table columns
             * that can contain data) set index to 0, so iter functions know
             * no data is associated with term */
            columns[ti] = 0;
        } else {
            ecs_column_t *column = &data->columns[index];
            if (!column->size) {
                /* If table column has o size, term has no data */
                columns[ti] = 0;
            }
        }
    } 
}

static
void observer_callback(ecs_iter_t *it) {
    ecs_observer_t *o = it->ctx;
    ecs_world_t *world = it->world;
    
    ecs_assert(it->table != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(it->table->table != NULL, ECS_INTERNAL_ERROR, NULL);

    ecs_table_t *table = it->table->table;
    ecs_type_t type = table->type;
    if (ecs_filter_match_type(world, &o->filter, type)) {
        ecs_data_t *data = ecs_table_get_data(table);
        ecs_id_t ids[ECS_FILTER_DESC_TERM_ARRAY_MAX];
        int32_t columns[ECS_FILTER_DESC_TERM_ARRAY_MAX];
        ecs_type_t types[ECS_FILTER_DESC_TERM_ARRAY_MAX];
        ecs_iter_t user_it = *it;

        ecs_iter_table_t table_data = {
            .table = table,
            .columns = columns,
            .components = ids,
            .types = types
        };

        user_it.table = &table_data;

        populate_columns(world, o, table, data, ids, 
            columns, types, it->event_id, it->term_index);

        user_it.system = o->entity;
        user_it.term_index = it->term_index;
        user_it.self = o->self;
        user_it.ctx = o->ctx;
        user_it.column_count = o->filter.term_count_actual,
        user_it.table_columns = data->columns,
        o->action(&user_it);
    }
}

ecs_entity_t ecs_observer_init(
    ecs_world_t *world,
    const ecs_observer_desc_t *desc)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(desc != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(!world->is_fini, ECS_INVALID_OPERATION, NULL);

    /* If entity is provided, create it */
    ecs_entity_t existing = desc->entity.entity;
    ecs_entity_t entity = ecs_entity_init(world, &desc->entity);

    bool added = false;
    EcsObserver *comp = ecs_get_mut(world, entity, EcsObserver, &added);
    if (added) {
        ecs_observer_t *observer = ecs_sparse_add(
            world->observers, ecs_observer_t);
        ecs_assert(observer != NULL, ECS_INTERNAL_ERROR, NULL);
        observer->id = ecs_sparse_last_id(world->observers);

        /* Make writeable copy of filter desc so that we can set name. This will
         * make debugging easier, as any error messages related to creating the
         * filter will have the name of the observer. */
        ecs_filter_desc_t filter_desc = desc->filter;
        filter_desc.name = desc->entity.name;

        /* Parse filter */
        if (ecs_filter_init(world, &observer->filter, &filter_desc)) {
            ecs_observer_fini(world, observer);
            return 0;
        }

        ecs_filter_t *filter = &observer->filter;

        /* Create a trigger for each term in the filter */
        observer->triggers = ecs_os_malloc(ECS_SIZEOF(ecs_entity_t) * 
            observer->filter.term_count);
        
        int i;
        for (i = 0; i < filter->term_count; i ++) {
            const ecs_term_t *terms = filter->terms;
            const ecs_term_t *t = &terms[i];

            if (t->oper == EcsNot || terms[i].args[0].entity != EcsThis) {
                /* No need to trigger on components that the entity should not
                 * have, or on components that are not defined on the entity */
                observer->triggers[i] = 0;
                continue;
            }

            ecs_trigger_desc_t trigger_desc = {
                .term = *t,
                .callback = observer_callback,
                .ctx = observer,
                .binding_ctx = desc->binding_ctx
            };

            ecs_os_memcpy(trigger_desc.events, desc->events, 
                ECS_SIZEOF(ecs_entity_t) * ECS_TRIGGER_DESC_EVENT_COUNT_MAX);
            observer->triggers[i] = ecs_trigger_init(world, &trigger_desc);
        }

        observer->action = desc->callback;
        observer->self = desc->self;
        observer->ctx = desc->ctx;
        observer->binding_ctx = desc->binding_ctx;
        observer->ctx_free = desc->ctx_free;
        observer->binding_ctx_free = desc->binding_ctx_free;
        observer->event_count = 0;
        ecs_os_memcpy(observer->events, desc->events, 
            observer->event_count * ECS_SIZEOF(ecs_entity_t));
        observer->entity = entity;        

        comp->observer = observer;
    } else {
        ecs_assert(comp->observer != NULL, ECS_INTERNAL_ERROR, NULL);

        /* If existing entity handle was provided, override existing params */
        if (existing) {
            if (desc->callback) {
                ((ecs_observer_t*)comp->observer)->action = desc->callback;
            }
            if (desc->ctx) {
                ((ecs_observer_t*)comp->observer)->ctx = desc->ctx;
            }
            if (desc->binding_ctx) {
                ((ecs_observer_t*)comp->observer)->binding_ctx = 
                    desc->binding_ctx;
            }
        }        
    }

    return entity; 
}

void ecs_observer_fini(
    ecs_world_t *world,
    ecs_observer_t *observer)
{
    int i, count = observer->filter.term_count;
    for (i = 0; i < count; i ++) {
        ecs_entity_t trigger = observer->triggers[i];
        if (trigger) {
            ecs_delete(world, trigger);
        }
    }
    ecs_os_free(observer->triggers);

    ecs_filter_fini(&observer->filter);

    if (observer->ctx_free) {
        observer->ctx_free(observer->ctx);
    }

    if (observer->binding_ctx_free) {
        observer->binding_ctx_free(observer->binding_ctx);
    }

    ecs_sparse_remove(world->observers, observer->id);
}

void* ecs_get_observer_ctx(
    const ecs_world_t *world,
    ecs_entity_t observer)
{
    const EcsObserver *o = ecs_get(world, observer, EcsObserver);
    if (o) {
        return o->observer->ctx;
    } else {
        return NULL;
    }     
}

void* ecs_get_observer_binding_ctx(
    const ecs_world_t *world,
    ecs_entity_t observer)
{
    const EcsObserver *o = ecs_get(world, observer, EcsObserver);
    if (o) {
        return o->observer->binding_ctx;
    } else {
        return NULL;
    }      
}
