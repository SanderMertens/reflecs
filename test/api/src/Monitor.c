#include <api.h>

static
void OnPosition(ecs_iter_t *it) {
    probe_system(it);
}

void Monitor_1_comp() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsMonitor, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ctx = (Probe){ 0 };

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}

void Monitor_2_comps() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsMonitor, Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);    

    ctx = (Probe){ 0 };

    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Position);
    test_int(ctx.invoked, 1);    
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0); 

    ecs_fini(world);
}

void Monitor_1_comp_1_not() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsMonitor, Position, !Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);    

    ctx = (Probe){ 0 };

    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Velocity);
    test_int(ctx.invoked, 1);    
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0); 

    ecs_fini(world);
}

void Monitor_1_parent() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsMonitor, PARENT:Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t parent = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_entity_t e = ecs_new(world, 0);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsChildOf, parent);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], parent); 

    ecs_fini(world);
}

void Monitor_1_comp_1_parent() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsMonitor, Position, PARENT:Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t parent = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsChildOf, parent);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Position));
    test_int(ctx.s[0][1], parent);    

    ctx = (Probe){ 0 };

    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Position);
    test_int(ctx.invoked, 1);    
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Position));
    test_int(ctx.s[0][1], parent);

    ecs_fini(world);
}

void Monitor_1_comp_prefab_new() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsMonitor, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ECS_PREFAB(world, Prefab, Position);

    test_int(ctx.invoked, 0);

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_add(world, Prefab, Velocity);
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}

void Monitor_1_comp_prefab_add() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsMonitor, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new_w_entity(world, EcsPrefab);
    ecs_add(world, e, Position);
    test_int(ctx.invoked, 0);

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}
