#include <api.h>

static
void OnPosition(ecs_iter_t *it) {
    probe_system(it);
}

static
void Add_to_current(ecs_iter_t *it) {
    IterData *ctx = ecs_get_ctx(it->world);

    int i;
    for (i = 0; i < it->count; i ++) {
        if (ctx->component) {
            ecs_add_id(it->world, it->entities[i], ctx->component);

            test_assert( !!ecs_get_type(it->world, it->entities[i]));
        }

        if (ctx->component_2) {
            ecs_add_id(it->world, it->entities[i], ctx->component_2);
        }

        ctx->entity_count ++;
    }
}

static
void Remove_from_current(ecs_iter_t *it) {
    IterData *ctx = ecs_get_ctx(it->world);

    int i;
    for (i = 0; i < it->count; i ++) {
        ecs_entity_t e = it->entities[i];

        if (ctx->component) {
            ecs_remove_id(it->world, e, ctx->component);
        }

        if (ctx->component_2) {
            ecs_remove_id(it->world, e, ctx->component_2);
        }

        ctx->entity_count ++;
    }
}

static Probe pv_probe;

static
void On_PV(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);
    ECS_COLUMN(it, Velocity, v, 2);

    probe_system_w_ctx(it, &pv_probe);

    int i;
    for (i = 0; i < it->count; i ++) {
        p[i].x += v[i].x;
        p[i].y += v[i].y;
    }
}

void SystemOnSet_set_1_of_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
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

    ecs_set(world, e, Velocity, {10, 20});
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void SystemOnSet_set_1_of_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 0);

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Velocity, {10, 20});
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

    ecs_set(world, e, Position, {10, 20});
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

void SystemOnSet_set_1_of_3() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position, Velocity, Mass);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 0);

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Mass);
    test_int(ctx.invoked, 0);

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Velocity, {10, 20});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);

    ctx = (Probe){ 0 };

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);
    
    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);

    ctx = (Probe){ 0 };

    ecs_set(world, e, Mass, {10});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);
    
    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);

    ecs_fini(world);
}

void SystemOnSet_bulk_new_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    const ecs_entity_t *ids = ecs_bulk_new_w_data(world, 3,
        &(ecs_ids_t){
            .array = (ecs_entity_t[]){ecs_typeid(Position)}, 
            .count = 1
        },
        (void*[]){
            (Position[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            }
        });

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 3);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], ids[0]);
    test_int(ctx.e[1], ids[1]);
    test_int(ctx.e[2], ids[2]);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void SystemOnSet_bulk_new_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    const ecs_entity_t *ids = ecs_bulk_new_w_data(world, 3,
        &(ecs_ids_t){
            .array = (ecs_entity_t[]){
                ecs_typeid(Position),
                ecs_typeid(Velocity)
            }, 
            .count = 2
        },
        (void*[]){
            (Position[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            },
            (Velocity[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            }
        });

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 3);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], ids[0]);
    test_int(ctx.e[1], ids[1]);
    test_int(ctx.e[2], ids[2]);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    ecs_fini(world);
}

void SystemOnSet_bulk_new_2_of_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    const ecs_entity_t *ids = ecs_bulk_new_w_data(world, 3,
        &(ecs_ids_t){
            .array = (ecs_entity_t[]){
                ecs_typeid(Position),
                ecs_typeid(Velocity)
            }, 
            .count = 2
        },
        (void*[]){
            (Position[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            },
            (Velocity[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            }
        });

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 3);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], ids[0]);
    test_int(ctx.e[1], ids[1]);
    test_int(ctx.e[2], ids[2]);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void SystemOnSet_bulk_new_3() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, Type, Position, Velocity, Mass);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position, Velocity, Mass);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    const ecs_entity_t *ids = ecs_bulk_new_w_data(world, 3,
        &(ecs_ids_t){
            .array = (ecs_entity_t[]){
                ecs_typeid(Position),
                ecs_typeid(Velocity),
                ecs_typeid(Mass)
            }, 
            .count = 3
        },
        (void*[]){
            (Position[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            },
            (Velocity[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            },
            (Mass[]) {
                10,
                20,
                30
            }
        });

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 3);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], ids[0]);
    test_int(ctx.e[1], ids[1]);
    test_int(ctx.e[2], ids[2]);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);

    ecs_fini(world);
}

void SystemOnSet_bulk_new_3_of_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, Type, Position, Velocity, Mass);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    const ecs_entity_t *ids = ecs_bulk_new_w_data(world, 3,
        &(ecs_ids_t){
            .array = (ecs_entity_t[]){
                ecs_typeid(Position),
                ecs_typeid(Velocity),
                ecs_typeid(Mass)
            }, 
            .count = 3
        },
        (void*[]){
            (Position[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            },
            (Velocity[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            },
            (Mass[]) {
                10,
                20,
                30
            }
        });

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 3);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], ids[0]);
    test_int(ctx.e[1], ids[1]);
    test_int(ctx.e[2], ids[2]);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    ecs_fini(world);
}

void SystemOnSet_bulk_new_1_from_base() {
     ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_ENTITY(world, Base, Position);
    ECS_TYPE(world, Type, INSTANCEOF | Base, Velocity, Mass);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, ANY:Position, Velocity, Mass);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    const ecs_entity_t *ids = ecs_bulk_new_w_data(world, 3,
        &(ecs_ids_t){
            .array = (ecs_entity_t[]){
                ecs_typeid(Velocity),
                ecs_typeid(Mass),
                ecs_pair(EcsIsA, Base)
            }, 
            .count = 3
        },
        (void*[]){
            (Velocity[]) {
                {10, 20},
                {30, 40},
                {50, 60}
            },
            (Mass[]) {
                10,
                20,
                30
            }
        });

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 3);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], ids[0]);
    test_int(ctx.e[1], ids[1]);
    test_int(ctx.e[2], ids[2]);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], Base);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);

    ecs_fini(world);
}

void SystemOnSet_set_1_of_2_1_from_base() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, Base, Position);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, ANY:Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, Base);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Velocity, {10, 20});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], Base);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    ecs_fini(world);
}

void SystemOnSet_set_1_of_3_1_from_base() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_ENTITY(world, Base, Position);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, ANY:Position, Velocity, Mass);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, Base);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Mass);
    test_int(ctx.invoked, 0);

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Velocity, {10, 20});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], Base);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);

    ctx = (Probe){ 0 };

    ecs_set(world, e, Mass, {10});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);
    
    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], Base);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);

    ecs_fini(world);
}

void SystemOnSet_add_base() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, Base, Position);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, ANY:Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Velocity);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsIsA, Base);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], Base);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    ecs_fini(world);
}

void SystemOnSet_add_base_to_1_overridden() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_ENTITY(world, Base, Position);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, ANY:Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsIsA, Base);
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}

void SystemOnSet_add_base_to_2_overridden() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, Base, Position, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, ANY:Position, ANY:Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsIsA, Base);
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}

void SystemOnSet_add_base_to_1_of_2_overridden() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, Base, Position, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, ANY:Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Velocity);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsIsA, Base);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], Base);

    ctx = (Probe){ 0 };

    e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsIsA, Base);
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}

void SystemOnSet_on_set_after_remove_override() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, Base, Position);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsIsA, Base);
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void SystemOnSet_no_set_after_remove_base() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, Base, Position);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, ANY:Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsIsA, Base);
    test_int(ctx.invoked, 0);

    ecs_remove_id(world, e, ecs_pair(EcsIsA, Base));
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}

void SystemOnSet_un_set_after_remove() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, OnPosition, EcsUnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 1);

    ecs_fini(world);
}

void SystemOnSet_un_set_after_remove_base() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_ENTITY(world, Base, Position);
    ECS_SYSTEM(world, OnPosition, EcsUnSet, ANY:Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, 0);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, EcsIsA, Base);
    test_int(ctx.invoked, 0);

    ecs_remove_id(world, e, ecs_pair(EcsIsA, Base));
    test_int(ctx.invoked, 1);

    ecs_fini(world);
}

void SystemOnSet_add_to_current_in_on_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, Add_to_current, EcsOnSet, Position);

    IterData ctx = {.component = ecs_typeid(Velocity)};
    ecs_set_ctx(world, &ctx);

    /* Create entities from scratch so they don't have the EcsName component */
    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {11, 21});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {12, 22});

    test_assert( ecs_has(world, e1, Position));
    test_assert( ecs_has(world, e2, Position));
    test_assert( ecs_has(world, e3, Position));

    test_assert( ecs_has(world, e1, Velocity));
    test_assert( ecs_has(world, e2, Velocity));
    test_assert( ecs_has(world, e3, Velocity));

    const Position *p = ecs_get(world, e1, Position);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_int(p->x, 11);
    test_int(p->y, 21);

    p = ecs_get(world, e3, Position);
    test_int(p->x, 12);
    test_int(p->y, 22);

    ecs_fini(world);
}

void SystemOnSet_remove_from_current_in_on_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);
    ECS_SYSTEM(world, Remove_from_current, EcsOnSet, Position);

    IterData ctx = {.component = ecs_typeid(Velocity)};
    ecs_set_ctx(world, &ctx);

    /* Create entities from scratch so they don't have the EcsName component */
    ecs_entity_t e1 = ecs_new(world, Type);
    ecs_entity_t e2 = ecs_new(world, Type);
    ecs_entity_t e3 = ecs_new(world, Type);

    e1 = ecs_set(world, e1, Position, {10, 20});
    e2 = ecs_set(world, e2, Position, {11, 21});
    e3 = ecs_set(world, e3, Position, {12, 22});

    test_assert( ecs_has(world, e1, Position));
    test_assert( ecs_has(world, e2, Position));
    test_assert( ecs_has(world, e3, Position));

    test_assert( !ecs_has(world, e1, Velocity));
    test_assert( !ecs_has(world, e2, Velocity));
    test_assert( !ecs_has(world, e3, Velocity));

    const Position *p = ecs_get(world, e1, Position);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_int(p->x, 11);
    test_int(p->y, 21);

    p = ecs_get(world, e3, Position);
    test_int(p->x, 12);
    test_int(p->y, 22);

    ecs_fini(world);
}

void SystemOnSet_remove_set_component_in_on_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);
    ECS_SYSTEM(world, Remove_from_current, EcsOnSet, Position);

    IterData ctx = {.component = ecs_typeid(Position)};
    ecs_set_ctx(world, &ctx);

    /* Create entities from scratch so they don't have the EcsName component */
    ecs_entity_t e1 = ecs_new(world, Type);
    ecs_entity_t e2 = ecs_new(world, Type);
    ecs_entity_t e3 = ecs_new(world, Type);

    e1 = ecs_set(world, e1, Position, {10, 20});
    e2 = ecs_set(world, e2, Position, {11, 21});
    e3 = ecs_set(world, e3, Position, {12, 22});

    test_assert( !ecs_has(world, e1, Position));
    test_assert( !ecs_has(world, e2, Position));
    test_assert( !ecs_has(world, e3, Position));

    test_assert( ecs_has(world, e1, Velocity));
    test_assert( ecs_has(world, e2, Velocity));
    test_assert( ecs_has(world, e3, Velocity));

    ecs_fini(world);
}

void SystemOnSet_match_table_created_w_add_in_on_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_SYSTEM(world, Add_to_current, EcsOnSet, Position);
    ECS_SYSTEM(world, On_PV, EcsOnUpdate, Position, Velocity);

    IterData add_ctx = {.component = ecs_typeid(Velocity)};
    ecs_set_ctx(world, &add_ctx);

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {10, 20});

    ecs_progress(world, 1);

    test_int(pv_probe.count, 3);
    test_int(pv_probe.invoked, 1);
    test_int(pv_probe.system, On_PV);
    test_int(pv_probe.column_count, 2);
    test_null(pv_probe.param);

    test_int(pv_probe.e[0], e1);
    test_int(pv_probe.e[1], e2);
    test_int(pv_probe.e[2], e3);
    test_int(pv_probe.c[0][0], ecs_typeid(Position));
    test_int(pv_probe.s[0][0], 0);
    test_int(pv_probe.c[0][1], ecs_typeid(Velocity));
    test_int(pv_probe.s[0][1], 0);

    ecs_fini(world);
}

void SystemOnSet_set_optional() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position, ?Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, OnPosition);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ctx = (Probe){ 0 };

    ecs_set(world, e, Velocity, {10, 20});
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

void SystemOnSet_set_from_nothing() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, OnPosition, EcsOnSet, Position, :Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
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
    ecs_set(world, e, Velocity, {10, 20});
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}

static
void AddNull(ecs_iter_t *it) {
    probe_system(it);

    int i;
    for (i = 0; i < it->count; i ++) {
        ecs_add_type(it->world, it->entities[i], NULL);
    }
}

void SystemOnSet_add_null_type_in_on_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, AddNull, EcsOnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, AddNull);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    test_assert( ecs_has(world, e, Position));

    ecs_fini(world);
}

static
void Add0(ecs_iter_t *it) {
    probe_system(it);

    int i;
    for (i = 0; i < it->count; i ++) {
        ecs_add_id(it->world, it->entities[i], 0);
    }
}

void SystemOnSet_add_0_entity_in_on_set() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, Add0, EcsOnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    test_expect_abort();
    ecs_set(world, 0, Position, {10, 20});
}

static int dummy_invoked = 0;

static
void Dummy(ecs_iter_t *it) {
    dummy_invoked ++;
}

void SystemOnSet_on_set_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, Dummy, EcsOnSet, Position);

    ECS_PREFAB(world, Prefab, 0);
    ecs_set(world, Prefab, Position, {10, 20});

    test_int(dummy_invoked, 0);

    ecs_fini(world);
}
