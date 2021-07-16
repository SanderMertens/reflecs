#include "private_api.h"

/** Initialize observable.
 */
void ecs_observable_init(
    ecs_observable_t *observable)
{
    observable->triggers = ecs_sparse_new(ecs_event_triggers_t);
}

/** Deinitialize observable.
 */
void ecs_observable_fini(
    ecs_observable_t *observable)
{
    ecs_sparse_t *triggers = observable->triggers;
    int32_t i, count = ecs_sparse_count(triggers);

    for (i = 0; i < count; i ++) {
        ecs_event_triggers_t *et = 
            ecs_sparse_get_dense(triggers, ecs_event_triggers_t, i);
        ecs_assert(et != NULL, ECS_INTERNAL_ERROR, NULL);

        ecs_map_iter_t it = ecs_map_iter(et->triggers);
        ecs_id_triggers_t *idt;
        while ((idt = ecs_map_next(&it, ecs_id_triggers_t, NULL))) {
            ecs_map_free(idt->triggers);
        }
        ecs_map_free(et->triggers);
    }

    ecs_sparse_free(observable->triggers);
}

void ecs_emit(
    ecs_world_t *world,
    ecs_event_desc_t *desc)
{
    ecs_object_assert(world, ecs_world_t);
    ecs_assert(desc != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(desc->event != 0, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(desc->event != EcsWildcard, ECS_INVALID_PARAMETER, NULL);

    ecs_ids_t ids_storage, *ids = desc->ids;
    ecs_table_t *table = NULL;
    int32_t row = 0;
    int32_t count = 0;
    ecs_entity_t event = desc->event;
    ecs_entity_t entity = 0;

    if (desc->payload_kind == EcsPayloadEntity) {
        entity = desc->payload.entity;
        ecs_assert(entity != 0, ECS_INTERNAL_ERROR, NULL);
        ecs_record_t *r = ecs_eis_get(world, entity);
        if (r) {
            bool is_watched;
            table = r->table;
            row = ecs_record_to_row(r->row, &is_watched);
        }
        count = 1;

    } else if (desc->payload_kind == EcsPayloadTable) {
        ecs_assert(desc->payload.table.table != NULL, ECS_INTERNAL_ERROR, NULL);
        table = desc->payload.table.table;
        row = desc->payload.table.offset;
        int32_t payload_count = desc->payload.table.count;
        if (!payload_count) {
            count = ecs_table_count(table) - row;
        } else {
            count = payload_count;
        }
    }

    if (table) {
        if (!ids) {
            ids = &ids_storage;
            ids_storage.array = ecs_vector_first(table->type, ecs_id_t);
            ids_storage.count = ecs_vector_count(table->type);
        }
    }

    ecs_triggers_notify(world, desc->observable, ids, event, 
        entity, table, row, count, desc->param);
}
