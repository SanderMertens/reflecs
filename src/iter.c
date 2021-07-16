#include "private_api.h"

void ecs_iter_init_from(
    ecs_iter_t *dst, 
    ecs_iter_t *src)
{
    /* Copy all fields except the storage arrays */
    dst->entities = src->entities;
    dst->count = src->count;
    dst->offset = src->offset;
    dst->columns = src->columns;
    dst->type_map = src->type_map;
    dst->table = src->table;
    dst->type = src->type;
    dst->terms = src->terms;
    dst->ids = src->ids;
    dst->subjects = src->subjects;
    dst->sizes = src->sizes;
    dst->types = src->types;
    dst->world = src->world;
    dst->real_world = src->real_world;
    dst->term_count = src->term_count;
    dst->system = src->system;
    dst->event = src->event;
    dst->param = src->param;
    dst->ctx = src->ctx;
    dst->binding_ctx = src->binding_ctx;
    dst->delta_time = src->delta_time;
    dst->delta_system_time = src->delta_system_time;
    dst->world_time = src->world_time;
    dst->interrupted_by = src->interrupted_by;
    dst->frame_offset = src->frame_offset;
    dst->private.total_count = src->private.total_count;
}

void ecs_iter_init_from_cached_type(
    ecs_iter_t *it, 
    ecs_cached_type_t *type)
{
    it->ids = type->ids;
    it->subjects = type->subjects;
    it->sizes = type->sizes;
    it->types = type->types;
    it->type_map = type->type_map;
}

void ecs_iter_init_from_storage(
    ecs_iter_t *it)
{
    it->ids = it->private.ids_storage;
    it->subjects = it->private.subjects_storage;
    it->sizes = it->private.sizes_storage;
    it->types = it->private.types_storage;
    it->type_map = it->private.type_map_storage;
    it->columns = it->private.columns_storage;
}


/* --- Public API --- */

void* ecs_term_w_size(
    const ecs_iter_t *it,
    size_t size,
    int32_t term_index)
{
    ecs_assert(term_index <= it->term_count, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(term_index > 0, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_term_size(it, term_index) == size, ECS_INVALID_PARAMETER, NULL);
    return it->columns[term_index - 1];
}

bool ecs_term_is_owned(
    const ecs_iter_t *it,
    int32_t term_index)
{
    ecs_assert(term_index <= it->term_count, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(term_index > 0, ECS_INVALID_PARAMETER, NULL);
    return !it->subjects || !it->subjects[term_index];
}

bool ecs_term_is_readonly(
    const ecs_iter_t *it,
    int32_t term_index)
{
    ecs_assert(term_index <= it->term_count, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(term_index > 0, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(it->terms != NULL, ECS_INVALID_PARAMETER, NULL);

    ecs_term_t *term = &it->terms[term_index - 1];
    
    if (term->inout == EcsIn) {
        return true;
    } else {
        ecs_term_id_t *subj = &term->args[0];

        if (term->inout == EcsInOutDefault) {
            if (subj->entity != EcsThis) {
                return true;
            }

            if ((subj->set.mask != EcsSelf) && 
                (subj->set.mask != EcsDefaultSet)) 
            {
                return true;
            }
        }
    }
    
    return false;
}

ecs_entity_t ecs_term_subject(
    const ecs_iter_t *it,
    int32_t term_index)
{
    ecs_assert(term_index <= it->term_count, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(term_index > 0, ECS_INVALID_PARAMETER, NULL);
    return it->subjects ? it->subjects[term_index - 1] : 0;
}

ecs_id_t ecs_term_id(
    const ecs_iter_t *it,
    int32_t term_index)
{
    ecs_assert(term_index <= it->term_count, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(term_index > 0, ECS_INVALID_PARAMETER, NULL);
    return it->ids[term_index - 1];
}

size_t ecs_term_size(
    const ecs_iter_t *it,
    int32_t term_index)
{
    ecs_assert(term_index <= it->term_count, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(term_index > 0, ECS_INVALID_PARAMETER, NULL);
    return ecs_to_size_t(it->sizes[term_index - 1]);
}

ecs_table_t* ecs_iter_table(
    const ecs_iter_t *it)
{
    return it->table;
}

ecs_type_t ecs_iter_type(
    const ecs_iter_t *it)
{
    return it->type;
}

int32_t ecs_iter_find_column(
    const ecs_iter_t *it,
    ecs_id_t id)
{
    return ecs_type_index_of(it->type, id);
}

void* ecs_iter_column_w_size(
    const ecs_iter_t *it,
    size_t size,
    int32_t column_index)
{
    ecs_assert(it->table != NULL, ECS_INVALID_PARAMETER, NULL);
    (void)size;
    
    ecs_table_t *table = it->table;
    ecs_assert(column_index < ecs_vector_count(table->type), 
        ECS_INVALID_PARAMETER, NULL);
    
    if (table->column_count <= column_index) {
        return NULL;
    }

    ecs_data_t *data = ecs_table_get_data(table);
    ecs_column_t *column = &data->columns[column_index];
    ecs_assert(!size || (ecs_size_t)size == column->size, 
        ECS_INVALID_PARAMETER, NULL);

    return ecs_vector_first_t(column->data, column->size, column->alignment);
}

size_t ecs_iter_column_size(
    const ecs_iter_t *it,
    int32_t column_index)
{
    ecs_assert(it->table != NULL, ECS_INVALID_PARAMETER, NULL);
    
    ecs_table_t *table = it->table;
    ecs_assert(column_index < ecs_vector_count(table->type), 
        ECS_INVALID_PARAMETER, NULL);

    if (table->column_count <= column_index) {
        return 0;
    }

    ecs_data_t *data = ecs_table_get_data(table);
    ecs_column_t *column = &data->columns[column_index];
    
    return ecs_to_size_t(column->size);
}

// DEPRECATED
void* ecs_element_w_size(
    const ecs_iter_t *it, 
    size_t size,
    int32_t column,
    int32_t row)
{
    return ECS_OFFSET(ecs_term_w_size(it, size, column), 
        ecs_from_size_t(size) * row);
}
