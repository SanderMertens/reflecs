
#include "flecs.h"

#ifdef FLECS_SYSTEM
#ifdef FLECS_DBG

#include "system.h"

int ecs_dbg_system(
    const ecs_world_t *world,
    ecs_entity_t system,
    ecs_dbg_system_t *dbg_out)
{
    const EcsSystem *system_data = ecs_get(world, system, EcsSystem);
    if (!system_data) {
        return -1;
    }

    *dbg_out = (ecs_dbg_system_t){.system = system};
    dbg_out->active_table_count = ecs_vector_count(system_data->query->tables);
    dbg_out->inactive_table_count = ecs_vector_count(system_data->query->empty_tables);
    dbg_out->enabled = !ecs_has_id(world, system, EcsDisabled);

    ecs_vector_each(system_data->query->tables, ecs_cached_table_t, mt, {
        ecs_table_t *table = mt->table;
        if (table) {
            dbg_out->entities_matched_count += ecs_table_count(table);
        }        
    });

    /* Inactive tables are inactive because they are empty, so no need to 
     * iterate them */

    return 0;
}

bool ecs_dbg_match_entity(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_entity_t system,
    ecs_match_failure_t *failure_info_out)
{
    ecs_dbg_entity_t dbg;
    ecs_dbg_entity(world, entity, &dbg);

    const EcsSystem *system_data = ecs_get(world, system, EcsSystem);
    if (!system_data) {
        failure_info_out->reason = EcsMatchNotASystem;
        failure_info_out->column = -1;
        return false;
    }

    return ecs_filter_match_entity(world, &system_data->query->filter, entity);
}

ecs_type_t ecs_dbg_get_column_type(
    ecs_world_t *world,
    ecs_entity_t system,
    int32_t column_index)
{
    const EcsSystem *system_data = ecs_get(world, system, EcsSystem);
    if (!system_data) {
        return NULL;
    }
    
    ecs_term_t *terms = system_data->query->filter.terms;
    int32_t count = system_data->query->filter.term_count;

    if (count < column_index) {
        return NULL;
    }

    ecs_term_t *term = &terms[column_index - 1];
    
    return ecs_type_from_id(world, term->id);
}

#endif
#endif
