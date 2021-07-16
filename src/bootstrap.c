#include "private_api.h"


/* Component lifecycle actions */

/* EcsName */
static ECS_CTOR(EcsName, ptr, {
    ptr->value = NULL;
    ptr->alloc_value = NULL;
    ptr->symbol = NULL;
})

static ECS_DTOR(EcsName, ptr, {
    ecs_os_free(ptr->alloc_value);
    ecs_os_free(ptr->symbol);
    ptr->value = NULL;
    ptr->alloc_value = NULL;
    ptr->symbol = NULL;
})

static ECS_COPY(EcsName, dst, src, {
    if (dst->alloc_value) {
        ecs_os_free(dst->alloc_value);
        dst->alloc_value = NULL;
    }

    if (dst->symbol) {
        ecs_os_free(dst->symbol);
        dst->symbol = NULL;
    }
    
    if (src->alloc_value) {
        dst->alloc_value = ecs_os_strdup(src->alloc_value);
        dst->value = dst->alloc_value;
    } else {
        dst->alloc_value = NULL;
        dst->value = src->value;
    }

    if (src->symbol) {
        dst->symbol = ecs_os_strdup(src->symbol);
    }
})

static ECS_MOVE(EcsName, dst, src, {
    if (dst->alloc_value) {
        ecs_os_free(dst->alloc_value);
    }
    if (dst->symbol) {
        ecs_os_free(dst->symbol);
    }

    dst->value = src->value;
    dst->alloc_value = src->alloc_value;
    dst->symbol = src->symbol;

    src->value = NULL;
    src->alloc_value = NULL;
    src->symbol = NULL;
})


/* EcsTrigger */
static ECS_CTOR(EcsTrigger, ptr, {
    ptr->trigger = NULL;
})

static ECS_DTOR(EcsTrigger, ptr, {
    ecs_trigger_fini(world, (ecs_trigger_t*)ptr->trigger);
})

static ECS_COPY(EcsTrigger, dst, src, {
    ecs_abort(ECS_INVALID_OPERATION, "Trigger component cannot be copied");
})

static ECS_MOVE(EcsTrigger, dst, src, {
    if (dst->trigger) {
        ecs_trigger_fini(world, (ecs_trigger_t*)dst->trigger);
    }
    dst->trigger = src->trigger;
    src->trigger = NULL;
})


/* EcsObserver */
static ECS_CTOR(EcsObserver, ptr, {
    ptr->observer = NULL;
})

static ECS_DTOR(EcsObserver, ptr, {
    ecs_observer_fini(world, (ecs_observer_t*)ptr->observer);
})

static ECS_COPY(EcsObserver, dst, src, {
    ecs_abort(ECS_INVALID_OPERATION, "Observer component cannot be copied");
})

static ECS_MOVE(EcsObserver, dst, src, {
    if (dst->observer) {
        ecs_observer_fini(world, (ecs_observer_t*)dst->observer);
    }
    dst->observer = src->observer;
    src->observer = NULL;
})


/* Triggers */

static
void on_delete(ecs_iter_t *it) {
    ecs_id_t id = ecs_term_id(it, 1);
    int i;
    for (i = 0; i < it->count; i ++) {
        ecs_entity_t e = it->entities[i];
        ecs_id_record_t *r = ecs_ensure_id_record(it->world, e);
        ecs_assert(r != NULL, ECS_INTERNAL_ERROR, NULL);
        r->on_delete = ECS_PAIR_OBJECT(id);

        r = ecs_ensure_id_record(it->world, ecs_pair(e, EcsWildcard));
        ecs_assert(r != NULL, ECS_INTERNAL_ERROR, NULL);
        r->on_delete = ECS_PAIR_OBJECT(id);

        ecs_set_watch(it->world, e);
    }
}

static
void on_delete_object(ecs_iter_t *it) {
    ecs_id_t id = ecs_term_id(it, 1);
    int i;
    for (i = 0; i < it->count; i ++) {
        ecs_entity_t e = it->entities[i];
        ecs_id_record_t *r = ecs_ensure_id_record(it->world, e);
        ecs_assert(r != NULL, ECS_INTERNAL_ERROR, NULL);
        r->on_delete_object = ECS_PAIR_OBJECT(id);

        ecs_set_watch(it->world, e);
    }    
}


/* Iterables */

/* OnComponentLifecycle */
static
void iter_on_component_lifecycle(
    ecs_object_t *obj,
    ecs_iter_t *it,
    ecs_id_t filter)
{
    ecs_object_assert(obj, ecs_world_t);
    ecs_world_t *world = obj;

    (void)filter;
    
    it->ids = it->private.ids_storage;
    it->world = world;
    it->term_count = 1;
    it->private.iter.sparse = 
        ecs_sparse_iter(world->type_info, ecs_type_info_t);
}

static
bool next_on_component_lifecycle(
    ecs_iter_t *it)
{
    ecs_assert(it != NULL, ECS_INTERNAL_ERROR, NULL);
    
    ecs_sparse_iter_t *iter = &it->private.iter.sparse;
    int32_t i = iter->i;
    int32_t count = iter->count;
    ecs_assert(i <= count, ECS_INTERNAL_ERROR, NULL);

    it->ids[0] = iter->ids[i];
    iter->i = ++ i;

    return i < count;
}


/* -- Bootstrap utilities -- */

#define bootstrap_component(world, table, name)\
    _bootstrap_component(world, table, ecs_id(name), #name, sizeof(name),\
        ECS_ALIGNOF(name))

static
void _bootstrap_component(
    ecs_world_t *world,
    ecs_table_t *table,
    ecs_entity_t entity,
    const char *name,
    ecs_size_t size,
    ecs_size_t alignment)
{
    ecs_object_assert(world, ecs_world_t);
    ecs_assert(table != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(entity != 0, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(name != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(size != 0, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(alignment != 0, ECS_INTERNAL_ERROR, NULL);

    /* Skip prefix */
    name = &name[ecs_os_strlen("Ecs")];

    ecs_data_t *data = ecs_table_get_or_create_data(table);
    ecs_assert(data != NULL, ECS_INTERNAL_ERROR, NULL);

    ecs_column_t *columns = data->columns;
    ecs_assert(columns != NULL, ECS_INTERNAL_ERROR, NULL);

    /* Create record in entity index */
    ecs_record_t *record = ecs_eis_ensure(world, entity);
    record->table = table;

    /* Insert row into table to store EcsComponent itself */
    int32_t index = ecs_table_append(world, table, data, entity, record, false);
    record->row = index + 1;

    /* Set size and id */
    EcsComponent *c_info = ecs_vector_first(columns[0].data, EcsComponent);
    EcsName *id_data = ecs_vector_first(columns[1].data, EcsName);
    
    c_info[index].size = size;
    c_info[index].alignment = alignment;
    id_data[index].value = name;
    id_data[index].symbol = ecs_os_strdup(name);
    id_data[index].alloc_value = NULL;

    /* Sanity check entity index, component storage */
    ecs_assert(ecs_eis_get(world, entity) != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ecs_has(world, entity, EcsName), ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ecs_get(world, entity, EcsName) != NULL, 
        ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ecs_get_name(world, entity) != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(!ecs_os_strcmp(ecs_get_name(world, entity), name), 
        ECS_INTERNAL_ERROR, NULL);    
}

/** Create type for component */
ecs_type_t ecs_bootstrap_type(
    ecs_world_t *world,
    ecs_entity_t entity)
{
    ecs_table_t *table = ecs_table_find_or_create(world, &(ecs_ids_t){
        .array = (ecs_entity_t[]){entity},
        .count = 1
    });

    ecs_assert(table != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(table->type != NULL, ECS_INTERNAL_ERROR, NULL);

    return table->type;
}

/** Bootstrap types for builtin components and tags */
static
void bootstrap_types(
    ecs_world_t *world)
{
    ecs_type(EcsComponent) = ecs_bootstrap_type(world, ecs_id(EcsComponent));
    ecs_type(EcsType) = ecs_bootstrap_type(world, ecs_id(EcsType));
    ecs_type(EcsName) = ecs_bootstrap_type(world, ecs_id(EcsName));
}

/** Initialize component table. This table is manually constructed to bootstrap
 * flecs. After this function has been called, the builtin components can be
 * created. 
 * The reason this table is constructed manually is because it requires the size
 * and alignment of the EcsComponent and EcsName components, which haven't been 
 * created yet */
static
ecs_table_t* bootstrap_component_table(
    ecs_world_t *world)
{
    ecs_entity_t entities[] = {ecs_id(EcsComponent), ecs_id(EcsName), ecs_pair(EcsChildOf, EcsFlecsCore)};
    ecs_ids_t array = {
        .array = entities,
        .count = 3
    };

    ecs_table_t *result = ecs_table_find_or_create(world, &array);
    ecs_data_t *data = ecs_table_get_or_create_data(result);

    /* Preallocate enough memory for initial components */
    data->entities = ecs_vector_new(ecs_entity_t, EcsFirstUserComponentId);
    data->record_ptrs = ecs_vector_new(ecs_record_t*, EcsFirstUserComponentId);

    data->columns = ecs_os_malloc(sizeof(ecs_column_t) * 2);
    ecs_assert(data->columns != NULL, ECS_OUT_OF_MEMORY, NULL);

    data->columns[0].data = ecs_vector_new(EcsComponent, EcsFirstUserComponentId);
    data->columns[0].size = sizeof(EcsComponent);
    data->columns[0].alignment = ECS_ALIGNOF(EcsComponent);
    data->columns[1].data = ecs_vector_new(EcsName, EcsFirstUserComponentId);
    data->columns[1].size = sizeof(EcsName);
    data->columns[1].alignment = ECS_ALIGNOF(EcsName);

    result->column_count = 2;
    
    return result;
}

static
void bootstrap_entity(
    ecs_world_t *world,
    ecs_entity_t entity,
    const char *name,
    ecs_entity_t parent)
{
    ecs_object_assert(world, ecs_world_t);
    ecs_assert(entity != 0, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(name != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(parent != 0, ECS_INTERNAL_ERROR, NULL);

    char symbol[256];
    ecs_os_strcpy(symbol, "flecs.core.");
    ecs_os_strcat(symbol, name);

    ecs_set(world, entity, EcsName, {.value = name, .symbol = symbol});

    /* Sanity check entity index, component storage */
    ecs_assert(ecs_eis_get(world, entity) != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ecs_has(world, entity, EcsName), ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ecs_get(world, entity, EcsName) != NULL, 
        ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ecs_get_name(world, entity) != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(!ecs_os_strcmp(ecs_get_name(world, entity), name), 
        ECS_INTERNAL_ERROR, NULL);

    ecs_add_pair(world, entity, EcsChildOf, parent);
    ecs_assert(ecs_has_pair(world, entity, EcsChildOf, parent), 
        ECS_INTERNAL_ERROR, NULL);

    if (parent == EcsFlecsCore) {
        ecs_assert(ecs_lookup_fullpath(world, name) == entity, 
            ECS_INTERNAL_ERROR, NULL);
    }

    /* All builtin entities are final */
    ecs_add_id(world, entity, EcsFinal);
}

void ecs_bootstrap(
    ecs_world_t *world)
{
    ecs_type(EcsComponent) = NULL;

    ecs_trace_1("bootstrap core components");
    ecs_log_push();

    /* Initialize component table */
    ecs_table_t *table = bootstrap_component_table(world);
    assert(table != NULL);

    /* Initialize builtin components */
    bootstrap_component(world, table, EcsName);
    bootstrap_component(world, table, EcsComponent);
    bootstrap_component(world, table, EcsType);
    bootstrap_component(world, table, EcsQuery);
    bootstrap_component(world, table, EcsTrigger);
    bootstrap_component(world, table, EcsObserver);
    bootstrap_component(world, table, EcsIterable);

    /* Initialize builtin component lifecycle actions */
    ecs_set_component_actions(world, EcsName, {
        .ctor = ecs_ctor(EcsName),
        .dtor = ecs_dtor(EcsName),
        .copy = ecs_copy(EcsName),
        .move = ecs_move(EcsName)
    });

    ecs_set_component_actions(world, EcsTrigger, {
        .ctor = ecs_ctor(EcsTrigger),
        .dtor = ecs_dtor(EcsTrigger),
        .copy = ecs_copy(EcsTrigger),
        .move = ecs_move(EcsTrigger)
    }); 

    ecs_set_component_actions(world, EcsObserver, {
        .ctor = ecs_ctor(EcsObserver),
        .dtor = ecs_dtor(EcsObserver),
        .copy = ecs_copy(EcsObserver),
        .move = ecs_move(EcsObserver)
    });

    /* Initialize entity id counters */
    world->stats.last_component_id = EcsFirstUserComponentId;
    world->stats.last_id = EcsFirstUserEntityId;
    world->stats.min_id = 0;
    world->stats.max_id = 0;

    /* Initialize builtin iterables */
    ecs_set(world, EcsOnComponentLifecycle, EcsIterable, {
        .iter = iter_on_component_lifecycle,
        .next = next_on_component_lifecycle
    });

    ecs_bootstrap_trigger_iterables(world);

    bootstrap_types(world);

    /* Everything from here is initialized in flecs.core */
    ecs_set_scope(world, EcsFlecsCore);

    /* Initialize builtin tags */
    ecs_bootstrap_tag(world, EcsModule);
    ecs_bootstrap_tag(world, EcsPrefab);
    ecs_bootstrap_tag(world, EcsHidden);
    ecs_bootstrap_tag(world, EcsDisabled);

    /* Initialize builtin modules */
    ecs_set(world, EcsFlecs, EcsName, {.value = "flecs"});
    ecs_add_id(world, EcsFlecs, EcsModule);

    ecs_set(world, EcsFlecsCore, EcsName, {.value = "core"});
    ecs_add_id(world, EcsFlecsCore, EcsModule);
    ecs_add_pair(world, EcsFlecsCore, EcsChildOf, EcsFlecs);

    /* Initialize builtin entities */
    bootstrap_entity(world, EcsWorld, "World", EcsFlecsCore);
    bootstrap_entity(world, EcsSingleton, "$", EcsFlecsCore);
    bootstrap_entity(world, EcsThis, "This", EcsFlecsCore);
    bootstrap_entity(world, EcsWildcard, "*", EcsFlecsCore);
    bootstrap_entity(world, EcsTransitive, "Transitive", EcsFlecsCore);
    bootstrap_entity(world, EcsFinal, "Final", EcsFlecsCore);
    bootstrap_entity(world, EcsTag, "Tag", EcsFlecsCore);

    bootstrap_entity(world, EcsIsA, "IsA", EcsFlecsCore);
    bootstrap_entity(world, EcsChildOf, "ChildOf", EcsFlecsCore);

    bootstrap_entity(world, EcsOnAdd, "OnAdd", EcsFlecsCore);
    bootstrap_entity(world, EcsOnRemove, "OnRemove", EcsFlecsCore);
    bootstrap_entity(world, EcsOnSet, "OnSet", EcsFlecsCore);
    bootstrap_entity(world, EcsUnSet, "UnSet", EcsFlecsCore);
    bootstrap_entity(world, EcsOnDelete, "OnDelete", EcsFlecsCore);
    bootstrap_entity(world, EcsOnCreateTable, "OnCreateTable", EcsFlecsCore);
    bootstrap_entity(world, EcsOnDeleteTable, "OnDeleteTable", EcsFlecsCore);
    bootstrap_entity(world, EcsOnTableEmpty, "OnTableEmpty", EcsFlecsCore);
    bootstrap_entity(world, EcsOnTableNonEmpty, "OnTableNonEmpty", EcsFlecsCore);
    bootstrap_entity(world, EcsOnCreateTrigger, "OnCreateTrigger", EcsFlecsCore);
    bootstrap_entity(world, EcsOnDeleteTrigger, "OnDeleteTrigger", EcsFlecsCore);
    bootstrap_entity(world, EcsOnDeleteObservable, "OnDeleteObservable", EcsFlecsCore);
    bootstrap_entity(world, EcsOnComponentLifecycle, "OnComponentLifecycle", EcsFlecsCore);
    bootstrap_entity(world, EcsOnDeleteObject, "OnDeleteObject", EcsFlecsCore);

    bootstrap_entity(world, EcsRemove, "Remove", EcsFlecsCore);
    bootstrap_entity(world, EcsDelete, "Delete", EcsFlecsCore);
    bootstrap_entity(world, EcsThrow, "Throw", EcsFlecsCore);

    /* Set builtin component/relation properties */
    ecs_add_id(world, EcsIsA, EcsTransitive);
    ecs_add_id(world, EcsIsA, EcsTag);
    ecs_add_id(world, EcsIsA, EcsFinal);

    ecs_add_id(world, EcsChildOf, EcsTag);
    ecs_add_pair(world, EcsChildOf, EcsOnDeleteObject, EcsDelete);

    /* Create builtin triggers */
    ecs_trigger_init(world, &(ecs_trigger_desc_t){
        .term = {.id = ecs_pair(EcsOnDelete, EcsWildcard)},
        .callback = on_delete,
        .events = {EcsOnAdd}
    });

    ecs_trigger_init(world, &(ecs_trigger_desc_t){
        .term = {.id = ecs_pair(EcsOnDeleteObject, EcsWildcard)},
        .callback = on_delete_object,
        .events = {EcsOnAdd}
    });

    ecs_set_scope(world, 0);

    ecs_log_pop();
}
