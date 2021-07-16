#include "private_api.h"

static
int32_t count_events(
    const ecs_entity_t *events) 
{
    int32_t i;

    for (i = 0; i < ECS_TRIGGER_DESC_EVENT_COUNT_MAX; i ++) {
        if (!events[i]) {
            break;
        }
    }

    return i;
} 

static
void register_trigger(
    ecs_world_t *world,
    ecs_observable_t *observable,
    ecs_trigger_t *trigger)
{
    ecs_sparse_t *triggers = observable->triggers;
    ecs_assert(triggers != NULL, ECS_INTERNAL_ERROR, NULL);

    int i;
    for (i = 0; i < trigger->event_count; i ++) {
        ecs_entity_t event = trigger->events[i];

        /* Get triggers for event */
        ecs_event_triggers_t *evt = ecs_sparse_ensure(
            triggers, ecs_event_triggers_t, event);
        ecs_assert(evt != NULL, ECS_INTERNAL_ERROR, NULL);

        if (!evt->triggers) {
            evt->triggers = ecs_map_new(ecs_id_triggers_t, 1);
        }
        
        /* Get triggers for (component) id */
        ecs_id_triggers_t *idt = ecs_map_ensure(
            evt->triggers, ecs_id_triggers_t, trigger->term.id);
        ecs_assert(idt != NULL, ECS_INTERNAL_ERROR, NULL);

        if (!idt->triggers) {
            idt->triggers = ecs_map_new(ecs_trigger_t*, 1);
        }

        ecs_trigger_t **elem = ecs_map_ensure(
            idt->triggers, ecs_trigger_t*, trigger->id);
        *elem = trigger;
    }
}

static
void unregister_trigger(
    ecs_world_t *world,
    ecs_observable_t *observable,
    ecs_trigger_t *trigger)
{
    ecs_sparse_t *triggers = observable->triggers;
    ecs_assert(triggers != NULL, ECS_INTERNAL_ERROR, NULL);

    int i;
    for (i = 0; i < trigger->event_count; i ++) {
        ecs_entity_t event = trigger->events[i];

        /* Get triggers for event */
        ecs_event_triggers_t *evt = ecs_sparse_get(
            triggers, ecs_event_triggers_t, event);
        ecs_assert(evt != NULL, ECS_INTERNAL_ERROR, NULL);

        /* Get triggers for (component) id */
        ecs_id_triggers_t *idt = ecs_map_get(
            evt->triggers, ecs_id_triggers_t, trigger->term.id);
        ecs_assert(idt != NULL, ECS_INTERNAL_ERROR, NULL);

        ecs_map_remove(idt->triggers, trigger->id);
        
        if (!ecs_map_count(idt->triggers)) {
            ecs_map_free(idt->triggers);
            ecs_map_remove(evt->triggers, trigger->term.id);
            if (!ecs_map_count(evt->triggers)) {
                ecs_map_free(evt->triggers);
                evt->triggers = NULL;
            }
        }
    }
}

static
ecs_map_t* get_triggers_for_event(
    const ecs_object_t *object,
    ecs_entity_t event)
{
    ecs_assert(object != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(event != 0, ECS_INTERNAL_ERROR, NULL);

    /* Get triggers for event */
    ecs_observable_t *observable = ecs_get_observable(object);
    ecs_sparse_t *triggers = observable->triggers;
    ecs_assert(triggers != NULL, ECS_INTERNAL_ERROR, NULL);

    const ecs_event_triggers_t *evt = ecs_sparse_get(
        triggers, ecs_event_triggers_t, event);
    
    if (evt) {
        return evt->triggers;
    }

    return NULL;
}

static
ecs_map_t *get_triggers_for_id(
    const ecs_map_t *evt,
    ecs_id_t id)
{
    ecs_id_triggers_t *idt = ecs_map_get(evt, ecs_id_triggers_t, id);
    if (idt) {
        ecs_map_t *set = idt->triggers;
        if (ecs_map_count(set)) {
            return set;
        }
    }

    return NULL;
}

ecs_map_t* ecs_triggers_get(
    const ecs_object_t *object,
    ecs_id_t id,
    ecs_entity_t event)
{
    const ecs_map_t *evt = get_triggers_for_event(object, event);
    if (!evt) {
        return NULL;
    }

    return get_triggers_for_id(evt, id);
}

static
void init_iter(
    ecs_iter_t *it,
    ecs_id_t id,
    ecs_entity_t *entity,
    ecs_table_t *table,
    int32_t row,
    int32_t count,
    bool *iter_set)
{
    ecs_assert(it != NULL, ECS_INTERNAL_ERROR, NULL);
    
    if (*iter_set) {
        return;
    }

    *iter_set = true;

    it->ids = it->private.ids_storage;
    it->ids[0] = id;

    if (count) {
        if (table) {
            ecs_assert(table != NULL, ECS_INTERNAL_ERROR, NULL);
            ecs_assert(!it->world->is_readonly, ECS_INTERNAL_ERROR, NULL);
            ecs_data_t *data = ecs_table_get_data(table);
            ecs_assert(data != NULL, ECS_INTERNAL_ERROR, NULL);
            ecs_entity_t *entities = ecs_vector_first(data->entities, ecs_entity_t);        
            ecs_assert(entities != NULL, ECS_INTERNAL_ERROR, NULL);
            ecs_assert(count > 0, ECS_INTERNAL_ERROR, NULL);
            ecs_assert(row < ecs_vector_count(data->entities), 
                ECS_INTERNAL_ERROR, NULL);
            ecs_assert((row + count) <= ecs_vector_count(data->entities), 
                ECS_INTERNAL_ERROR, NULL);
            entities = ECS_OFFSET(entities, ECS_SIZEOF(ecs_entity_t) * row);

            int32_t index = ecs_type_index_of(table->type, id);
            ecs_assert(index >= 0, ECS_INTERNAL_ERROR, NULL);
            index ++;

            int32_t type_map[1] = { 0 };
            void *columns[1] = { NULL };
            ecs_size_t sizes[1] = { 0 };

            /* If there is no data, ensure that system won't try to get it */
            if (table->column_count < index) {
                type_map[0] = -1;
            } else {
                ecs_column_t *column = &data->columns[index - 1];
                if (!column->size) {
                    type_map[0] = -1;
                } else {
                    columns[0] = ecs_vector_first_t(
                        column->data, column->size, column->alignment);
                    sizes[0] = column->size;
                }
            }

            ECS_VECTOR_STACK(type, ecs_id_t, (ecs_id_t[]){ id }, 1);

            ecs_type_t types[1] = { type };

            it->type_map = type_map;
            it->columns = columns;
            it->sizes = sizes;
            it->types = types;
        } else {
            it->entities = entity;
        }
    }
}

typedef struct {
    ecs_sparse_iter_t event_iter;
    ecs_map_t *triggers;
    ecs_map_iter_t trigger_iter;
    ecs_id_t id;
} ecs_trigger_iter_t;

static
void iter_on_create_trigger(
    ecs_object_t *obj,
    ecs_iter_t *it,
    ecs_id_t filter)
{
    ecs_observable_t *observable = ecs_get_observable(obj);

    ecs_trigger_iter_t *iter = ecs_os_malloc(ECS_SIZEOF(ecs_trigger_iter_t));
    iter->event_iter = ecs_sparse_iter(observable->triggers, ecs_event_triggers_t);
    iter->triggers = NULL;
    iter->id = filter;
    it->world = (ecs_world_t*)ecs_get_world(obj);
    it->iter_ctx = iter;
}

static
bool next_on_create_trigger(
    ecs_iter_t *it)
{
    ecs_trigger_iter_t *iter = it->iter_ctx;
    ecs_sparse_iter_t *event_iter = &iter->event_iter;
    ecs_trigger_t *ptr = NULL;

    do {
        if (!iter->triggers) {
            int32_t i = event_iter->i;
            int32_t count = event_iter->count;
            ecs_event_triggers_t *evt;
            ecs_map_t *triggers;

            do {
                evt = ecs_sparse_get_dense(
                    event_iter->sparse, ecs_event_triggers_t, i);
                ecs_assert(evt != NULL, ECS_INTERNAL_ERROR, NULL);

                triggers = get_triggers_for_id(evt->triggers, iter->id);
                i ++;
            } while ((i < count) && !ecs_map_count(triggers));

            if (i == count) {
                goto done;
            }

            iter->trigger_iter = ecs_map_iter(triggers);
            event_iter->i = i;
        }
        
        ptr = ecs_map_next_ptr(&iter->trigger_iter, ecs_trigger_t*, NULL);
        if (!ptr) {
            iter->triggers = NULL;
        }
    } while (!ptr);

    bool iter_set = false;
    init_iter(it, iter->id, &ptr->entity, NULL, 0, 1, &iter_set);
    it->count = 1;
    it->param = ptr;

    return true;
done:
    ecs_os_free(it->iter_ctx);
    return false;
}

void ecs_bootstrap_trigger_iterables(
    ecs_world_t *world)
{
    ecs_set(world, EcsOnCreateTrigger, EcsIterable, {
        .iter = iter_on_create_trigger,
        .next = next_on_create_trigger
    });
}

static
void notify_trigger_set(
    ecs_iter_t *it,
    const ecs_map_t *triggers)
{
    ecs_assert(triggers != NULL, ECS_INTERNAL_ERROR, NULL);

    ecs_map_iter_t mit = ecs_map_iter(triggers);
    ecs_trigger_t *t;
    while ((t = ecs_map_next_ptr(&mit, ecs_trigger_t*, NULL))) {
        it->system = t->entity;
        it->self = t->self;
        it->ctx = t->ctx;
        it->binding_ctx = t->binding_ctx;
        it->term_index = t->term.index;
        t->action(it);                   
    }
}

static
void notify_triggers_for_id(
    const ecs_map_t *evt,
    ecs_id_t id,
    ecs_iter_t *it,
    ecs_entity_t *entity,
    ecs_table_t *table,
    int32_t row,
    int32_t count,
    bool *iter_set)
{
    const ecs_map_t *triggers = get_triggers_for_id(evt, id);
    if (triggers) {
        init_iter(it, id, entity, table, row, count, iter_set);
        notify_trigger_set(it, triggers);
    }
}

void ecs_triggers_notify(
    ecs_world_t *world,
    ecs_object_t *observable,
    ecs_ids_t *ids,
    ecs_entity_t event,
    ecs_entity_t entity,
    ecs_table_t *table,
    int32_t row,
    int32_t count,
    void *param)
{
    if (!observable) {
        observable = world;
    }

    const ecs_map_t *evt = get_triggers_for_event(observable, event);
    if (!evt) {
        return;
    }

    ecs_iter_t it;
    it.world = world;
    it.event = event;
    it.term_count = 1;
    it.term_count_actual = 1;
    it.table = table;
    it.offset = row;
    it.count = count;
    it.param = param;

    int32_t i, ids_count = ids->count;
    ecs_id_t *ids_array = ids->array;

    for (i = 0; i < ids_count; i ++) {
        ecs_id_t id = ids_array[i];
        bool iter_set = false;

        notify_triggers_for_id(
            evt, id, &it, &entity, table, row, count, &iter_set);

        if (ECS_HAS_ROLE(id, PAIR)) {
            ecs_entity_t pred = ECS_PAIR_RELATION(id);
            ecs_entity_t obj = ECS_PAIR_OBJECT(id);

            notify_triggers_for_id(evt, ecs_pair(pred, EcsWildcard), 
                &it, &entity, table, row, count, &iter_set);

            notify_triggers_for_id(evt, ecs_pair(EcsWildcard, obj), 
                &it, &entity, table, row, count, &iter_set);

            notify_triggers_for_id(evt, ecs_pair(EcsWildcard, EcsWildcard), 
                &it, &entity, table, row, count, &iter_set);
        } else {
            notify_triggers_for_id(evt, EcsWildcard, 
                &it, &entity, table, row, count, &iter_set);
        }
    }
}

ecs_entity_t ecs_trigger_init(
    ecs_world_t *world,
    const ecs_trigger_desc_t *desc)
{
    ecs_object_assert(world, ecs_world_t);
    ecs_assert(!world->is_readonly, ECS_INVALID_OPERATION, NULL);
    ecs_assert(desc != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(!world->is_fini, ECS_INVALID_OPERATION, NULL);

    char *name = NULL;
    const char *expr = desc->expr;
    
    ecs_observable_t *observable = desc->observable;
    if (!observable) {
        observable = ecs_get_observable(world);
    }

    /* If entity is provided, create it */
    ecs_entity_t existing = desc->entity.entity;
    ecs_entity_t entity = ecs_entity_init(world, &desc->entity);

    bool added = false;
    EcsTrigger *comp = ecs_get_mut(world, entity, EcsTrigger, &added);
    if (added) {
        ecs_assert(desc->callback != NULL, ECS_INVALID_PARAMETER, NULL);
        
        /* Something went wrong with the construction of the entity */
        ecs_assert(entity != 0, ECS_INVALID_PARAMETER, NULL);
        name = ecs_get_fullpath(world, entity);

        ecs_term_t term;
        if (expr) {
    #ifdef FLECS_PARSER
            const char *ptr = ecs_parse_term(world, name, expr, expr, &term);
            if (!ptr) {
                goto error;
            }

            if (!ecs_term_is_set(&term)) {
                ecs_parser_error(
                    name, expr, 0, "invalid empty trigger expression");
                goto error;
            }

            if (ptr[0]) {
                ecs_parser_error(name, expr, 0, 
                    "too many terms in trigger expression (expected 1)");
                goto error;
            }
    #else
            ecs_abort(ECS_UNSUPPORTED, "parser addon is not available");
    #endif
        } else {
            term = desc->term;
        }

        if (ecs_term_finalize(world, name, expr, &term)) {
            goto error;
        }

        /* Currently triggers are not supported for specific entities */
        ecs_assert(term.args[0].entity == EcsThis, ECS_UNSUPPORTED, NULL);

        ecs_trigger_t *trigger = ecs_sparse_add(world->triggers, ecs_trigger_t);
        trigger->id = ecs_sparse_last_id(world->triggers);
        trigger->term = ecs_term_move(&term);
        trigger->action = desc->callback;
        trigger->ctx = desc->ctx;
        trigger->binding_ctx = desc->binding_ctx;
        trigger->ctx_free = desc->ctx_free;
        trigger->binding_ctx_free = desc->binding_ctx_free;
        trigger->event_count = count_events(desc->events);
        ecs_os_memcpy(trigger->events, desc->events, 
            trigger->event_count * ECS_SIZEOF(ecs_entity_t));
        trigger->entity = entity;
        trigger->self = desc->self;
        trigger->observable = observable;

        comp->trigger = trigger;

        /* Trigger must have at least one event */
        ecs_assert(trigger->event_count != 0, ECS_INVALID_PARAMETER, NULL);

        register_trigger(world, observable, trigger);

        ecs_term_fini(&term);

        ecs_emit(world, &(ecs_event_desc_t){ .event = EcsOnCreateTrigger,
            .ids = &(ecs_ids_t){.array = &trigger->term.id, .count = 1},
            .param = trigger
        });

        /* Check if we need to retrigger previous events */
        if (desc->retrigger) {
            int32_t i, count = trigger->event_count;
            for (i = 0; i < count; i ++) {
                ecs_entity_t event = trigger->events[i];

                /* Can only retrigger iterable events */
                const EcsIterable *iter = ecs_get(world, event, EcsIterable);
                if (iter) {
                    ecs_iter_t it;
                    iter->iter(world, &it, trigger->term.id);
                    it.event = event;
                    it.ctx = desc->ctx;

                    while (iter->next(&it)) {
                        desc->callback(&it);
                    }
                }
            }
        }
    } else {
        ecs_assert(comp->trigger != NULL, ECS_INTERNAL_ERROR, NULL);

        /* If existing entity handle was provided, override existing params */
        if (existing) {
            if (desc->callback) {
                ((ecs_trigger_t*)comp->trigger)->action = desc->callback;
            }
            if (desc->ctx) {
                ((ecs_trigger_t*)comp->trigger)->ctx = desc->ctx;
            }
            if (desc->binding_ctx) {
                ((ecs_trigger_t*)comp->trigger)->binding_ctx = desc->binding_ctx;
            }
        }
    }

    ecs_os_free(name);
    return entity;
error:
    ecs_os_free(name);
    return 0;
}

void ecs_trigger_fini(
    ecs_world_t *world,
    ecs_trigger_t *trigger)
{
    unregister_trigger(world, trigger->observable, trigger);
    ecs_term_fini(&trigger->term);

    if (trigger->ctx_free) {
        trigger->ctx_free(trigger->ctx);
    }

    if (trigger->binding_ctx_free) {
        trigger->binding_ctx_free(trigger->binding_ctx);
    }

    ecs_sparse_remove(world->triggers, trigger->id);
}
