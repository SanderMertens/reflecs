#include <api.h>

void Task(ecs_iter_t *it) {
    probe_system(it);
}

void Tasks_no_components() {
    ecs_world_t *world = ecs_init();

    ECS_SYSTEM(world, Task, EcsOnUpdate, 0);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 0);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 0);

    ecs_fini(world);
}

void Tasks_one_tag() {
    ecs_world_t *world = ecs_init();

    ECS_SYSTEM(world, Task, EcsOnUpdate, SYSTEM:Hidden);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 0);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 1);
    test_int(ctx.c[0][0], EcsHidden);

    ecs_fini(world);
}

void Tasks_from_system() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, Task, EcsOnUpdate, SYSTEM:Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 0);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 1);
    test_int(ctx.c[0][0], ecs_typeid(Position));

    ecs_fini(world);
}

static int phase_counter = 0;

static 
void OnLoadTask(ecs_iter_t *it) {
    test_assert(it->entities == NULL);
    test_int(it->count, 0);
    test_int(phase_counter, 0);
    phase_counter ++;
}

static 
void PostLoadTask(ecs_iter_t *it) {
    test_assert(it->entities == NULL);
    test_int(it->count, 0);
    test_int(phase_counter, 1);
    phase_counter ++;
}

static 
void PreUpdateTask(ecs_iter_t *it) {
    test_assert(it->entities == NULL);
    test_int(it->count, 0);
    test_int(phase_counter, 2);
    phase_counter ++;
}

static 
void OnUpdateTask(ecs_iter_t *it) {
    test_assert(it->entities == NULL);
    test_int(it->count, 0);
    test_int(phase_counter, 3);
    phase_counter ++;
}

static 
void OnValidateTask(ecs_iter_t *it) {
    test_assert(it->entities == NULL);
    test_int(it->count, 0);
    test_int(phase_counter, 4);
    phase_counter ++;
}

static 
void PostUpdateTask(ecs_iter_t *it) {
    test_assert(it->entities == NULL);
    test_int(it->count, 0);
    test_int(phase_counter, 5);
    phase_counter ++;
}

static 
void PreStoreTask(ecs_iter_t *it) {
    test_assert(it->entities == NULL);
    test_int(it->count, 0);
    test_int(phase_counter, 6);
    phase_counter ++;
}

static 
void OnStoreTask(ecs_iter_t *it) {
    test_assert(it->entities == NULL);
    test_int(it->count, 0);
    test_int(phase_counter, 7);
    phase_counter ++;
}

void Tasks_tasks_in_phases() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, OnLoadTask, EcsOnLoad, :Position);
    ECS_SYSTEM(world, PostLoadTask, EcsPostLoad, :Position);
    ECS_SYSTEM(world, PreUpdateTask, EcsPreUpdate, :Position);
    ECS_SYSTEM(world, OnUpdateTask, EcsOnUpdate, :Position);
    ECS_SYSTEM(world, OnValidateTask, EcsOnValidate, :Position);
    ECS_SYSTEM(world, PostUpdateTask, EcsPostUpdate, :Position);
    ECS_SYSTEM(world, PreStoreTask, EcsPreStore, :Position);
    ECS_SYSTEM(world, OnStoreTask, EcsOnStore, :Position);

    ecs_progress(world, 1);

    test_int(phase_counter, 8);

    ecs_fini(world);
}

