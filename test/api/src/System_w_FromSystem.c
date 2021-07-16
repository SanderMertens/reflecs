#include <api.h>

void InitVelocity(ecs_iter_t *it) {
    ECS_COLUMN(it, Velocity, v, 1);

    int i;
    for (i = 0; i < it->count; i ++) {
        v[i].x = 10;
        v[i].y = 20;
    }
}

void InitMass(ecs_iter_t *it) {
    ECS_COLUMN(it, Mass, m, 1);    
    int i;
    for (i = 0; i < it->count; i ++) {
        m[i] = 3;
    }
}

void Iter(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);

    Velocity *v = NULL;
    Mass *m = NULL;

    if (it->term_count >= 2) {
        v = ecs_term(it, Velocity, 2);
        test_assert(!ecs_is_owned(it, 2));
    }

    if (it->term_count >= 3) {
        m = ecs_term(it, Mass, 3);
        test_assert(!m || !ecs_is_owned(it, 3));
    }

    probe_system(it);

    int i;
    for (i = 0; i < it->count; i ++) {
        p[i].x += v->x;
        p[i].y += v->y;

        if (m) {
            p[i].x += *m;
            p[i].y += *m;
        }
    }
}

void System_w_FromSystem_2_column_1_from_system() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_TRIGGER(world, InitVelocity, EcsOnAdd, Velocity);
    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, SYSTEM:Velocity);

    test_assert( ecs_has(world, Iter, Velocity));
    const Velocity *v = ecs_get(world, Iter, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 10);
    test_int(v->y, 20);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_set(world, 0, Position, {0, 0});

    ecs_progress(world, 1);
    
    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], Iter);

    const Position *p = ecs_get(world, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_progress(world, 1);

    test_int(p->x, 20);
    test_int(p->y, 40);

    ecs_fini(world);
}

void System_w_FromSystem_3_column_2_from_system() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_TRIGGER(world, InitVelocity, EcsOnAdd, Velocity);
    ECS_TRIGGER(world, InitMass, EcsOnAdd, Mass);
    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, SYSTEM:Velocity, SYSTEM:Mass);

    test_assert( ecs_has(world, Iter, Velocity));
    const Velocity *v = ecs_get(world, Iter, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 10);
    test_int(v->y, 20);

    test_assert( ecs_has(world, Iter, Mass));
    const Mass *m = ecs_get(world, Iter, Mass);
    test_assert(m != NULL);
    test_int(*m, 3);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_set(world, 0, Position, {0, 0});

    ecs_progress(world, 1);
    
    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], Iter);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], Iter);

    const Position *p = ecs_get(world, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 13);
    test_int(p->y, 23);

    ecs_progress(world, 1);

    test_int(p->x, 26);
    test_int(p->y, 46);

    ecs_fini(world);
}

void Iter_reactive(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);

    Velocity *v = it->param;
    Mass *m = NULL;

    if (it->term_count >= 2) {
        v = ecs_term(it, Velocity, 2);
        test_assert(!ecs_is_owned(it, 2));
    }

    probe_system(it);

    int i;
    for (i = 0; i < it->count; i ++) {
        p[i].x = v->x;
        p[i].y = v->y;

        if (m) {
            p[i].x = *m;
            p[i].y = *m;
        }
    }
}

void Dummy_1(ecs_iter_t *it) { }
void Dummy_2(ecs_iter_t *it) { }

void System_w_FromSystem_auto_add_tag() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, Dummy_1, EcsOnUpdate, Position, SYSTEM:Hidden);
    ECS_SYSTEM(world, Dummy_2, 0, Position, SYSTEM:Hidden);

    test_assert( ecs_has_entity(world, Dummy_1, EcsHidden));
    test_assert( ecs_has_entity(world, Dummy_2, EcsHidden));

    ecs_fini(world);
}
