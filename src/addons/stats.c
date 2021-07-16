
#include "../private_api.h"

#ifdef FLECS_STATS

#ifdef FLECS_SYSTEM
#include "../modules/system/system.h"
#endif

#ifdef FLECS_PIPELINE
#include "../modules/pipeline/pipeline.h"
#endif

static
int32_t t_next(
    int32_t t)
{
    return (t + 1) % ECS_STAT_WINDOW;
}

static
int32_t t_prev(
    int32_t t)
{
    return (t - 1 + ECS_STAT_WINDOW) % ECS_STAT_WINDOW;
}

static
void _record_gauge(
    ecs_gauge_t *m,
    int32_t t,
    float value)
{
    m->avg[t] = value;
    m->min[t] = value;
    m->max[t] = value;
}

static
float _record_counter(
    ecs_counter_t *m,
    int32_t t,
    float value)
{
    int32_t tp = t_prev(t);
    float prev = m->value[tp];
    m->value[t] = value;
    _record_gauge((ecs_gauge_t*)m, t, value - prev);
    return value - prev;
}

/* Macro's to silence conversion warnings without adding casts everywhere */
#define record_gauge(m, t, value)\
    _record_gauge(m, t, (float)value)

#define record_counter(m, t, value)\
    _record_counter(m, t, (float)value)

static
void print_value(
    const char *name,
    float value)
{
    ecs_size_t len = ecs_os_strlen(name);
    printf("%s: %*s %.2f\n", name, 32 - len, "", (double)value);
}

static
void print_gauge(
    const char *name,
    int32_t t,
    const ecs_gauge_t *m)
{
    print_value(name, m->avg[t]);
}

static
void print_counter(
    const char *name,
    int32_t t,
    const ecs_counter_t *m)
{
    print_value(name, m->rate.avg[t]);
}

void ecs_gauge_reduce(
    ecs_gauge_t *dst,
    int32_t t_dst,
    ecs_gauge_t *src,
    int32_t t_src)
{
    ecs_assert(dst != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(src != NULL, ECS_INVALID_PARAMETER, NULL);

    bool min_set = false;
    dst->min[t_dst] = 0;
    dst->avg[t_dst] = 0;
    dst->max[t_dst] = 0;

    int32_t i;
    for (i = 0; i < ECS_STAT_WINDOW; i ++) {
        int32_t t = (t_src + i) % ECS_STAT_WINDOW;
        dst->avg[t_dst] += src->avg[t] / (float)ECS_STAT_WINDOW;
        if (!min_set || (src->min[t] < dst->min[t_dst])) {
            dst->min[t_dst] = src->min[t];
            min_set = true;
        }
        if ((src->max[t] > dst->max[t_dst])) {
            dst->max[t_dst] = src->max[t];
        }
    }
}

void ecs_get_world_stats(
    const ecs_world_t *world,
    ecs_world_stats_t *s)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(s != NULL, ECS_INVALID_PARAMETER, NULL);

    world = ecs_get_world(world);

    int32_t t = s->t = t_next(s->t);

    float delta_world_time = record_counter(&s->world_time_total_raw, t, world->stats.world_time_total_raw);
    record_counter(&s->world_time_total, t, world->stats.world_time_total);
    record_counter(&s->frame_time_total, t, world->stats.frame_time_total);
    record_counter(&s->system_time_total, t, world->stats.system_time_total);
    record_counter(&s->merge_time_total, t, world->stats.merge_time_total);

    float delta_frame_count = record_counter(&s->frame_count_total, t, world->stats.frame_count_total);
    record_counter(&s->merge_count_total, t, world->stats.merge_count_total);
    record_counter(&s->pipeline_build_count_total, t, world->stats.pipeline_build_count_total);
    record_counter(&s->systems_ran_frame, t, world->stats.systems_ran_frame);

    if (delta_world_time != 0.0f && delta_frame_count != 0.0f) {
        record_gauge(
            &s->fps, t, 1.0f / (delta_world_time / (float)delta_frame_count));
    } else {
        record_gauge(&s->fps, t, 0);
    }

    record_gauge(&s->entity_count, t, ecs_sparse_count(world->store.entity_index));
    record_gauge(&s->component_count, t, ecs_count_id(world, ecs_id(EcsComponent)));
    record_gauge(&s->query_count, t, ecs_sparse_count(world->queries));
    record_gauge(&s->system_count, t, ecs_count_id(world, ecs_id(EcsSystem)));

    record_counter(&s->new_count, t, world->new_count);
    record_counter(&s->bulk_new_count, t, world->bulk_new_count);
    record_counter(&s->delete_count, t, world->delete_count);
    record_counter(&s->clear_count, t, world->clear_count);
    record_counter(&s->add_count, t, world->add_count);
    record_counter(&s->remove_count, t, world->remove_count);
    record_counter(&s->set_count, t, world->set_count);
    record_counter(&s->discard_count, t, world->discard_count);

    /* Compute table statistics */
    int32_t empty_table_count = 0;
    int32_t singleton_table_count = 0;

    int32_t i, count = ecs_sparse_count(world->store.tables);
    for (i = 0; i < count; i ++) {
        ecs_table_t *table = ecs_sparse_get_dense(world->store.tables, ecs_table_t, i);
        int32_t entity_count = ecs_table_count(table);

        if (!entity_count) {
            empty_table_count ++;
        }

        /* Singleton tables are tables that have just one entity that also has
         * itself in the table type. */
        if (entity_count == 1) {
            ecs_data_t *data = ecs_table_get_data(table);
            ecs_entity_t *entities = ecs_vector_first(data->entities, ecs_entity_t);
            if (ecs_type_has_id(world, table->type, entities[0])) {
                singleton_table_count ++;
            }
        }
    }
    
    record_gauge(&s->table_count, t, count);
    record_gauge(&s->empty_table_count, t, empty_table_count);
    record_gauge(&s->singleton_table_count, t, singleton_table_count);
}

void ecs_get_query_stats(
    const ecs_world_t *world,
    const ecs_query_t *query,
    ecs_query_stats_t *s)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(query != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(s != NULL, ECS_INVALID_PARAMETER, NULL);
    (void)world;

    int32_t t = s->t = t_next(s->t);

    int32_t i, entity_count = 0, count = ecs_vector_count(query->tables);
    ecs_cached_table_t *matched_tables = ecs_vector_first(
        query->tables, ecs_cached_table_t);
    for (i = 0; i < count; i ++) {
        ecs_cached_table_t *matched = &matched_tables[i];
        if (matched->table) {
            entity_count += ecs_table_count(matched->table);
        }
    }

    record_gauge(&s->matched_table_count, t, count);
    record_gauge(&s->matched_empty_table_count, t, 
        ecs_vector_count(query->empty_tables));
    record_gauge(&s->matched_entity_count, t, entity_count);
}

#ifdef FLECS_SYSTEM
bool ecs_get_system_stats(
    const ecs_world_t *world,
    ecs_entity_t system,
    ecs_system_stats_t *s)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(s != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(system != 0, ECS_INVALID_PARAMETER, NULL);

    world = ecs_get_world(world);

    const EcsSystem *ptr = ecs_get(world, system, EcsSystem);
    if (!ptr) {
        return false;
    }

    ecs_get_query_stats(world, ptr->query, &s->query_stats);
    int32_t t = s->query_stats.t;

    record_counter(&s->time_spent, t, ptr->time_spent);
    record_counter(&s->invoke_count, t, ptr->invoke_count);
    record_gauge(&s->active, t, !ecs_has_id(world, system, EcsInactive));
    record_gauge(&s->enabled, t, !ecs_has_id(world, system, EcsDisabled));

    return true;
}
#endif


#ifdef FLECS_PIPELINE

static ecs_system_stats_t* get_system_stats(
    ecs_map_t *systems,
    ecs_entity_t system)
{
    ecs_assert(systems != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(system != 0, ECS_INVALID_PARAMETER, NULL);

    ecs_system_stats_t *s = ecs_map_get(systems, ecs_system_stats_t, system);
    if (!s) {
        ecs_system_stats_t stats;
        memset(&stats, 0, sizeof(ecs_system_stats_t));
        ecs_map_set(systems, system, &stats);
        s = ecs_map_get(systems, ecs_system_stats_t, system);
        ecs_assert(s != NULL, ECS_INTERNAL_ERROR, NULL);
    }

    return s;
}

bool ecs_get_pipeline_stats(
    const ecs_world_t *world,
    ecs_entity_t pipeline,
    ecs_pipeline_stats_t *s)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(s != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(pipeline != 0, ECS_INVALID_PARAMETER, NULL);

    world = ecs_get_world(world);

    const EcsPipelineQuery *pq = ecs_get(world, pipeline, EcsPipelineQuery);
    if (!pq) {
        return false;
    }

    /* First find out how many systems are matched by the pipeline */
    ecs_iter_t it = ecs_query_iter(pq->query);
    int32_t count = 0;
    while (ecs_query_next(&it)) {
        count += it.count;
    }

    if (!s->system_stats) {
        s->system_stats = ecs_map_new(ecs_system_stats_t, count);
    }    

    /* Also count synchronization points */
    ecs_vector_t *ops = pq->ops;
    ecs_pipeline_op_t *op = ecs_vector_first(ops, ecs_pipeline_op_t);
    ecs_pipeline_op_t *op_last = ecs_vector_last(ops, ecs_pipeline_op_t);
    count += ecs_vector_count(ops);

    /* Make sure vector is large enough to store all systems & sync points */
    ecs_vector_set_count(&s->systems, ecs_entity_t, count - 1);
    ecs_entity_t *systems = ecs_vector_first(s->systems, ecs_entity_t);

    /* Populate systems vector, keep track of sync points */
    it = ecs_query_iter(pq->query);
    int32_t i_system = 0, ran_since_merge = 0;
    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            systems[i_system ++] = it.entities[i];
            ran_since_merge ++;
            if (op != op_last && ran_since_merge == op->count) {
                ran_since_merge = 0;
                op++;
                systems[i_system ++] = 0; /* 0 indicates a merge point */
            }

            ecs_system_stats_t *sys_stats = get_system_stats(
                s->system_stats, it.entities[i]);
            ecs_get_system_stats(world, it.entities[i], sys_stats);
        }
    }

    ecs_assert(i_system == (count - 1), ECS_INTERNAL_ERROR, NULL);

    return true;
}
#endif

void ecs_dump_world_stats(
    const ecs_world_t *world,
    const ecs_world_stats_t *s)
{
    int32_t t = s->t;

    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(s != NULL, ECS_INVALID_PARAMETER, NULL);

    world = ecs_get_world(world);    
    
    print_counter("Frame", t, &s->frame_count_total);
    printf("-------------------------------------\n");
    print_counter("pipeline rebuilds", t, &s->pipeline_build_count_total);
    print_counter("systems ran last frame", t, &s->systems_ran_frame);
    printf("\n");
    print_value("target FPS", world->stats.target_fps);
    print_value("time scale", world->stats.time_scale);
    printf("\n");
    print_gauge("actual FPS", t, &s->fps);
    print_counter("frame time", t, &s->frame_time_total);
    print_counter("system time", t, &s->system_time_total);
    print_counter("merge time", t, &s->merge_time_total);
    print_counter("simulation time elapsed", t, &s->world_time_total);
    printf("\n");
    print_gauge("entity count", t, &s->entity_count);
    print_gauge("component count", t, &s->component_count);
    print_gauge("query count", t, &s->query_count);
    print_gauge("system count", t, &s->system_count);
    print_gauge("table count", t, &s->table_count);
    print_gauge("singleton table count", t, &s->singleton_table_count);
    print_gauge("empty table count", t, &s->empty_table_count);
    printf("\n");
    print_counter("deferred new operations", t, &s->new_count);
    print_counter("deferred bulk_new operations", t, &s->bulk_new_count);
    print_counter("deferred delete operations", t, &s->delete_count);
    print_counter("deferred clear operations", t, &s->clear_count);
    print_counter("deferred add operations", t, &s->add_count);
    print_counter("deferred remove operations", t, &s->remove_count);
    print_counter("deferred set operations", t, &s->set_count);
    print_counter("discarded operations", t, &s->discard_count);
    printf("\n");
}

#endif
