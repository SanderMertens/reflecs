#include <api.h>

void Singleton_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_set(world, EcsSingleton, Position, {10, 20});

    test_assert( ecs_has(world, EcsSingleton, Position));

    const Position *p = ecs_get(world, EcsSingleton, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);
    
    ecs_fini(world);
}

void Singleton_set_ptr() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    Position p_value = {10, 20};

    ecs_set_ptr(world, EcsSingleton, Position, &p_value);

    test_assert( ecs_has(world, EcsSingleton, Position));

    const Position *p = ecs_get(world, EcsSingleton, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);
    
    ecs_fini(world);
}

void Iter_w_singleton(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);
    ECS_COLUMN(it, Velocity, v, 2);
    test_assert(!v || !ecs_is_owned(it, 2));

    probe_system(it);

    if (v) {
        int i;
        for (i = 0; i < it->count; i ++) {
            p[i].x += v->x;
            p[i].y += v->y;
        }
    }
}

void Singleton_system_w_singleton() {    
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, Iter_w_singleton, EcsOnUpdate, Position, $:Velocity);

    ecs_set(world, EcsSingleton, Velocity, {1, 2});
    test_assert( ecs_has(world, EcsSingleton, Velocity));

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    test_assert( !ecs_has(world, EcsSingleton, Position));

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);
    
    ecs_progress(world, 1);

    test_int(ctx.count, 1);

    const Position *p = ecs_get(world, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 11);
    test_int(p->y, 22);
    
    ecs_fini(world);
}

void Singleton_system_w_singleton_no_match() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, Iter_w_singleton, EcsOnUpdate, Position, $:Velocity);

    ecs_set(world, 0, Position, {10, 20});
    test_assert( !ecs_has(world, EcsSingleton, Position));

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 0);
    
    ecs_fini(world);
}

void Singleton_system_w_not_singleton() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, Iter_w_singleton, EcsOnUpdate, Position, !$:Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 0);
    
    ecs_fini(world);
}

void Singleton_lookup_singleton() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_lookup_fullpath(world, "$");
    test_assert(e == EcsSingleton);

    ecs_fini(world);
}

void Singleton_get_singleton_id() {
    ecs_world_t *world = ecs_init();

    test_str( ecs_get_name(world, EcsSingleton), "$");

    ecs_fini(world);
}

void Singleton_set_get_singleton() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_singleton_set(world, Position, {10, 20});
    
    const Position *p = ecs_singleton_get(world, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void Singleton_get_mut_singleton() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    Position *p_mut = ecs_singleton_get_mut(world, Position);
    p_mut->x = 10;
    p_mut->y = 20;
    
    const Position *p = ecs_singleton_get(world, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

static
void IncSingleton(ecs_iter_t *it) {
    Position *p = ecs_term(it, Position, 1);
    p->x ++;
    p->y ++;
}

void Singleton_singleton_system() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, IncSingleton, EcsOnUpdate, $Position);

    ecs_singleton_set(world, Position, {10, 20});

    ecs_progress(world, 0);

    const Position *p = ecs_singleton_get(world, Position);
    test_assert(p != NULL);
    test_int(p->x, 11);
    test_int(p->y, 21);

    ecs_fini(world);    
}

