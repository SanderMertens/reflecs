#include "flecs.h"

#ifdef FLECS_DBG

#include "../private_api.h"

ecs_table_t *ecs_dbg_find_table(
    ecs_world_t *world,
    ecs_type_t type)
{
    ecs_table_t *table = ecs_table_from_type(world, type);
    ecs_assert(table != NULL, ECS_INTERNAL_ERROR, NULL);
    return table;
}

void ecs_dbg_table(
    ecs_world_t *world, 
    ecs_table_t *table, 
    ecs_dbg_table_t *dbg_out)
{
    ecs_assert(dbg_out != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(table != NULL, ECS_INVALID_PARAMETER, NULL);

    *dbg_out = (ecs_dbg_table_t){.table = table};

    dbg_out->type = table->type;

    /* Determine components from parent/base entities */
    ecs_entity_t *entities = ecs_vector_first(table->type, ecs_entity_t);
    int32_t i, count = ecs_vector_count(table->type);

    for (i = 0; i < count; i ++) {
        ecs_entity_t e = entities[i];

        if (ECS_HAS_RELATION(e, EcsChildOf)) {
            ecs_dbg_entity_t parent_dbg;
            ecs_dbg_entity(world, ECS_PAIR_OBJECT(e), &parent_dbg);

            ecs_dbg_table_t parent_table_dbg;
            ecs_dbg_table(world, parent_dbg.table, &parent_table_dbg);

            /* Owned and shared components are available from container */
            dbg_out->container = ecs_type_merge(
                world, dbg_out->container, parent_dbg.type, NULL);
            dbg_out->container = ecs_type_merge(
                world, dbg_out->container, parent_table_dbg.shared, NULL);

            /* Add entity to list of parent entities */
            dbg_out->parent_entities = ecs_type_add(
                world, dbg_out->parent_entities, ECS_PAIR_OBJECT(e));
        }

        if (ECS_HAS_RELATION(e, EcsIsA)) {
            ecs_dbg_entity_t base_dbg;
            ecs_dbg_entity(world, ECS_PAIR_OBJECT(e), &base_dbg);

            ecs_dbg_table_t base_table_dbg;
            ecs_dbg_table(world, base_dbg.table, &base_table_dbg);            

            /* Owned and shared components are available from base */
            dbg_out->shared = ecs_type_merge(
                world, dbg_out->shared, base_dbg.type, NULL);
            dbg_out->shared = ecs_type_merge(
                world, dbg_out->shared, base_table_dbg.shared, NULL);

            /* Never inherit EcsName or EcsPrefab */
            dbg_out->shared = ecs_type_merge(
                world, dbg_out->shared, NULL, ecs_type(EcsName));
            dbg_out->shared = ecs_type_merge(
                world, dbg_out->shared, NULL, ecs_type_from_id(world, EcsPrefab));

            /* Shared components are always masked by owned components */
            dbg_out->shared = ecs_type_merge(
                world, dbg_out->shared, NULL, table->type);

            /* Add entity to list of base entities */
            dbg_out->base_entities = ecs_type_add(
                world, dbg_out->base_entities, ECS_PAIR_OBJECT(e));

            /* Add base entities of entity to list of base entities */
            dbg_out->base_entities = ecs_type_add(
                world, base_table_dbg.base_entities, ECS_PAIR_OBJECT(e));
        }
    }

    ecs_data_t *data = ecs_table_get_data(table);
    if (data) {
        dbg_out->entities = ecs_vector_first(data->entities, ecs_entity_t);
        dbg_out->entities_count = ecs_vector_count(data->entities);
    }
}

ecs_table_t* ecs_dbg_get_table(
    const ecs_world_t *world,
    int32_t index)
{
    if (ecs_sparse_count(world->store.tables) <= index) {
        return NULL;
    }

    return ecs_sparse_get_dense(
        world->store.tables, ecs_table_t, index);
}

bool ecs_dbg_filter_table(
    const ecs_world_t *world,
    const ecs_table_t *table,
    const ecs_filter_t *filter)
{
    return ecs_table_match_filter(world, table, filter);
}

void ecs_dbg_entity(
    const ecs_world_t *world, 
    ecs_entity_t entity, 
    ecs_dbg_entity_t *dbg_out)
{
    *dbg_out = (ecs_dbg_entity_t){.entity = entity};
    
    ecs_entity_info_t info = { 0 };
    if (ecs_get_info(world, entity, &info)) {
        dbg_out->table = info.table;
        dbg_out->row = info.row;
        dbg_out->is_watched = info.is_watched;
        dbg_out->type = info.table ? info.table->type : NULL;
    }
}

#endif
