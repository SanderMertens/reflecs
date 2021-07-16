#include <api.h>

static
void Iter(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);
    Velocity *v = NULL;
    Mass *m = NULL;

    if (it->term_count >= 2) {
        v = ecs_term(it, Velocity, 2);
    }

    if (it->term_count >= 3) {
        m = ecs_term(it, Mass, 3);
    }

    probe_system(it);

    int i;
    for (i = 0; i < it->count; i ++) {
        p[i].x = 10;
        p[i].y = 20;

        if (v) {
            v[i].x = 30;
            v[i].y = 40;
        }

        if (m) {
            m[i] = 50;
        }
    }
}

void SystemPeriodic_1_type_1_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void SystemPeriodic_1_type_3_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, e1, Position, Velocity, Mass);
    ECS_ENTITY(world, e2, Position, Velocity, Mass);
    ECS_ENTITY(world, e3, Position, Velocity, Mass);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, Velocity, Mass);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    
    const Velocity *v = ecs_get(world, e1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e3, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);


    const Mass *m = ecs_get(world, e1, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    m = ecs_get(world, e2, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    m = ecs_get(world, e3, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    ecs_fini(world);
}

void SystemPeriodic_3_type_1_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position, Velocity);
    ECS_ENTITY(world, e3, Position, Mass);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[1][0], ecs_typeid(Position));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[2][0], ecs_typeid(Position));
    test_int(ctx.s[2][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void SystemPeriodic_2_type_3_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Rotation);

    ECS_ENTITY(world, e1, Position, Velocity, Mass);
    ECS_ENTITY(world, e2, Position, Velocity, Mass);
    ECS_ENTITY(world, e3, Position, Velocity, Mass, Rotation);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, Velocity, Mass);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);
    test_int(ctx.c[1][0], ecs_typeid(Position));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[1][1], ecs_typeid(Velocity));
    test_int(ctx.s[1][1], 0);
    test_int(ctx.c[1][2], ecs_typeid(Mass));
    test_int(ctx.s[1][2], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    
    const Velocity *v = ecs_get(world, e1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e3, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);


    const Mass *m = ecs_get(world, e1, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    m = ecs_get(world, e2, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    m = ecs_get(world, e3, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    ecs_fini(world);
}

void SystemPeriodic_1_type_1_component_1_tag() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Tag, 0);
    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e1, Position, Tag);
    ECS_ENTITY(world, e2, Position, Tag);
    ECS_ENTITY(world, e3, Position, Tag);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, Tag);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], Tag);
    test_int(ctx.s[0][1], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void SystemPeriodic_2_type_1_component_1_tag() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Tag, 0);
    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e1, Position, Tag);
    ECS_ENTITY(world, e2, Position, Tag);
    ECS_ENTITY(world, e3, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, Tag);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], Tag);
    test_int(ctx.s[0][1], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}


void SystemPeriodic_2_type_1_and_1_not() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position, Velocity);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, !Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void SystemPeriodic_2_type_2_and_1_not() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, Velocity);
    ECS_ENTITY(world, e3, Position, Velocity, Mass);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, Velocity, !Mass);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);
    
    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    const Velocity *v = ecs_get(world, e1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    ecs_fini(world);
}

void SystemPeriodic_2_type_2_and_2_not() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Rotation);

    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, Velocity, Rotation);
    ECS_ENTITY(world, e3, Position, Velocity, Mass);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, Velocity, !Mass, !Rotation);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 4);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);
    test_int(ctx.c[0][3], ecs_typeid(Rotation));
    test_int(ctx.s[0][3], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    const Velocity *v = ecs_get(world, e1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    ecs_fini(world);
}

typedef Position Position_1;
typedef Position Position_2;

void SystemPeriodic_4_type_1_and_1_or() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Position_1);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position_1, Velocity);
    ECS_ENTITY(world, e3, Position, Position_1, Velocity);
    ECS_ENTITY(world, e4, Velocity);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position || Position_1, Velocity);

    ecs_set(world, e3, Position_1, {0, 0});
    ecs_set(world, e4, Velocity, {0, 0});

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[1][0], ecs_typeid(Position_1));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[1][1], ecs_typeid(Velocity));
    test_int(ctx.s[1][1], 0);
    test_int(ctx.c[2][0], ecs_typeid(Position));
    test_int(ctx.s[2][0], 0);
    test_int(ctx.c[2][1], ecs_typeid(Velocity));
    test_int(ctx.s[2][1], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position_1);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position_1);
    test_assert(p != NULL);
    test_int(p->x, 0);
    test_int(p->y, 0);

    const Velocity *v = ecs_get(world, e1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e3, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e4, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 0);
    test_int(v->y, 0);

    ecs_fini(world);
}

void SystemPeriodic_4_type_1_and_1_or_of_3() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Position_1);
    ECS_COMPONENT(world, Position_2);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position_2, Velocity);
    ECS_ENTITY(world, e3, Position_1, Position_2, Velocity);
    ECS_ENTITY(world, e4, Velocity);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position || Position_1 || Position_2, Velocity);

    ecs_set(world, e3, Position_2, {0, 0});
    ecs_set(world, e4, Velocity, {0, 0});

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[1][0], ecs_typeid(Position_2));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[1][1], ecs_typeid(Velocity));
    test_int(ctx.s[1][1], 0);
    test_int(ctx.c[2][0], ecs_typeid(Position_1));
    test_int(ctx.s[2][0], 0);
    test_int(ctx.c[2][1], ecs_typeid(Velocity));
    test_int(ctx.s[2][1], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position_2);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position_1);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position_2);
    test_assert(p != NULL);
    test_int(p->x, 0);
    test_int(p->y, 0);

    const Velocity *v = ecs_get(world, e1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e3, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e4, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 0);
    test_int(v->y, 0);

    ecs_fini(world);
}

void SystemPeriodic_1_type_1_and_1_or() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Position_1);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, Velocity);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position || Position_1, Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    /* Now repeat test, with entities that have Position_1 */
    ctx = (Probe){0};

    ecs_delete(world, e1);
    ecs_delete(world, e2);

    ECS_ENTITY(world, e3, Position_1, Velocity);
    ECS_ENTITY(world, e4, Position_1, Velocity);
    
    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e3);
    test_int(ctx.e[1], e4);
    test_int(ctx.c[0][0], ecs_typeid(Position_1));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    ecs_fini(world);
}

void SystemPeriodic_2_type_1_and_1_optional() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, Velocity);
    ECS_ENTITY(world, e3, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, ?Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e3);
    test_int(ctx.e[1], e1);
    test_int(ctx.e[2], e2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[1][0], ecs_typeid(Position));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[1][1], ecs_typeid(Velocity));
    test_int(ctx.s[1][1], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    const Velocity *v = ecs_get(world, e1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    ecs_fini(world);
}

void SystemPeriodic_2_type_2_and_1_optional() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, e1, Position, Velocity, Mass);
    ECS_ENTITY(world, e2, Position, Velocity, Mass);
    ECS_ENTITY(world, e3, Position, Velocity);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, Velocity, ?Mass);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    probe_has_entity(&ctx, e1);
    probe_has_entity(&ctx, e2);
    probe_has_entity(&ctx, e3);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);
    test_int(ctx.c[1][0], ecs_typeid(Position));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[1][1], ecs_typeid(Velocity));
    test_int(ctx.s[1][1], 0);
    test_int(ctx.c[1][2], ecs_typeid(Mass));
    test_int(ctx.s[1][2], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    const Velocity *v = ecs_get(world, e1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e3, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    const Mass *m = ecs_get(world, e1, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    ecs_fini(world);
}

void SystemPeriodic_6_type_1_and_2_optional() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, Velocity, Mass);
    ECS_ENTITY(world, e3, Position, Mass);
    ECS_ENTITY(world, e4, Position);
    ECS_ENTITY(world, e5, Velocity);
    ECS_ENTITY(world, e6, Mass);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, ?Velocity, ?Mass);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 4);
    test_int(ctx.invoked, 4);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    probe_has_entity(&ctx, e1);
    probe_has_entity(&ctx, e2);
    probe_has_entity(&ctx, e3);
    probe_has_entity(&ctx, e4);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);
    test_int(ctx.c[1][0], ecs_typeid(Position));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[1][1], ecs_typeid(Velocity));
    test_int(ctx.s[1][1], 0);
    test_int(ctx.c[1][2], ecs_typeid(Mass));
    test_int(ctx.s[1][2], 0);    
    test_int(ctx.c[2][0], ecs_typeid(Position));
    test_int(ctx.s[2][0], 0);
    test_int(ctx.c[2][1], ecs_typeid(Velocity));
    test_int(ctx.s[2][1], 0);
    test_int(ctx.c[2][2], ecs_typeid(Mass));
    test_int(ctx.s[2][2], 0);   
    test_int(ctx.c[3][0], ecs_typeid(Position));
    test_int(ctx.s[3][0], 0);
    test_int(ctx.c[3][1], ecs_typeid(Velocity));
    test_int(ctx.s[3][1], 0);
    test_int(ctx.c[3][2], ecs_typeid(Mass));
    test_int(ctx.s[3][2], 0);   

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    const Velocity *v = ecs_get(world, e1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get(world, e2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    const Mass *m = ecs_get(world, e2, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    m = ecs_get(world, e3, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    ecs_fini(world);
}

void Use_field(ecs_iter_t *it) {
    int i;
    for (i = 0; i < it->count; i ++) {
        Position *p = ecs_element(it, Position, 1, i);
        Velocity *v = ecs_element(it, Velocity, 2, i);

        p->x += v->x;
        p->y += v->y;
    }
}

void SystemPeriodic_use_fields_2_owned() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e1, Position, Velocity);

    ECS_SYSTEM(world, Use_field, EcsOnUpdate, Position, Velocity);

    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e1, Velocity, {10, 20});

    ecs_progress(world, 1);

    const Position *p = ecs_get(world, e1, Position);
    const Velocity *v = ecs_get(world, e1, Velocity);
    test_int(p->x, 11);
    test_int(p->y, 22);
    test_int(v->x, 10);
    test_int(v->y, 20);

    ecs_fini(world);
}

void SystemPeriodic_use_fields_1_owned_1_shared() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_SYSTEM(world, Use_field, EcsOnUpdate, Position, PARENT:Velocity);

    ecs_entity_t e1 = ecs_set(world, 0, Position, {1, 2});
    ecs_entity_t parent = ecs_set(world, 0, Velocity, {10, 20});
    ecs_add_pair(world, e1, EcsChildOf, parent);

    ecs_progress(world, 1);

    const Position *p = ecs_get(world, e1, Position);
    const Velocity *v = ecs_get(world, parent, Velocity);
    test_int(p->x, 11);
    test_int(p->y, 22);
    test_int(v->x, 10);
    test_int(v->y, 20);

    ecs_fini(world);
}

static void Dummy_1(ecs_iter_t *it) { probe_system(it); }
static void Dummy_2(ecs_iter_t *it) { probe_system(it); }

void SystemPeriodic_match_2_systems_w_populated_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, Dummy_1, EcsOnUpdate, Position);
    ECS_SYSTEM(world, Dummy_2, EcsOnUpdate, Position);
    
    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.column_count, 1);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    test_int(ctx.e[0], e);
    test_int(ctx.e[1], e);

    ecs_fini(world);
}

void TestOptional_w_column(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);
    ECS_COLUMN(it, Velocity, v, 2);

    test_assert(p != NULL);
    test_assert(v == NULL);

    probe_system(it);
}

void TestOptional_w_shared(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);
    ECS_COLUMN(it, Velocity, v, 2);

    test_assert(p != NULL);
    test_assert(v == NULL);

    probe_system(it);
}

void TestOptional_w_field(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);

    test_assert(p != NULL);

    probe_system(it);

    for (int i = 0; i < it->count; i ++) {
        Velocity *v = ecs_element(it, Velocity, 2, i);
        test_assert(v == NULL);
    }
}

void SystemPeriodic_ensure_optional_is_unset_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, TestOptional_w_column, EcsOnUpdate, Position, ?Velocity);
    
    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    test_int(ctx.e[0], e);

    ecs_fini(world);
}

void SystemPeriodic_ensure_optional_is_null_shared() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, TestOptional_w_shared, EcsOnUpdate, Position, ?PARENT:Velocity);
    
    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    test_int(ctx.e[0], e);

    ecs_fini(world);
}

void SystemPeriodic_ensure_optional_is_null_field_owned() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, TestOptional_w_field, EcsOnUpdate, Position, ?Velocity);
    
    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    test_int(ctx.e[0], e);

    ecs_fini(world);
}

void SystemPeriodic_ensure_optional_is_null_field_shared() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, TestOptional_w_field, EcsOnUpdate, Position, ?PARENT:Velocity);
    
    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);

    test_int(ctx.e[0], e);

    ecs_fini(world);
}

static int on_period_count;
static int normal_count;
static int normal_count_2;
static int normal_count_3;

static
void OnPeriodSystem(ecs_iter_t *it) {
    on_period_count ++;
}

static
void NormalSystem(ecs_iter_t *it) {
    normal_count ++;
}

static
void NormalSystem2(ecs_iter_t *it) {
    normal_count_2 ++;
}

static
void NormalSystem3(ecs_iter_t *it) {
    normal_count_3 ++;
}

void SystemPeriodic_on_period() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, OnPeriodSystem, EcsOnUpdate, Position);
    ECS_SYSTEM(world, NormalSystem, EcsOnUpdate, Position);

    ecs_set_interval(world, OnPeriodSystem, 0.5);

    ecs_set_target_fps(world, 60);

    const ecs_world_info_t *stats = ecs_get_world_info(world);

    double start, now = 0;

    /* Run for one second */
    int count = 0;
    do {    
        ecs_progress(world, 0);
        if (!count) {
            start = stats->delta_time;
        }

        now += stats->delta_time;
        count ++;
    } while ((now - start) < 1.0);

    test_int(count, normal_count);
    test_int(on_period_count, 2);

    ecs_fini(world);
}

void SystemPeriodic_on_period_long_delta() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, OnPeriodSystem, EcsOnUpdate, Position);
    ECS_SYSTEM(world, NormalSystem, EcsOnUpdate, Position);

    ecs_set_interval(world, OnPeriodSystem, 0.5);

    ecs_progress(world, 0);

    test_int(on_period_count, 0);

    ecs_sleepf(1.2);

    ecs_progress(world, 0);

    test_int(on_period_count, 1);

    ecs_sleepf(0.5);

    ecs_progress(world, 0);

    test_int(on_period_count, 2);    

    ecs_fini(world);
}

void SystemPeriodic_disabled() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, NormalSystem, EcsOnUpdate, Position);

    ecs_progress(world, 0);

    test_int(normal_count, 1);

    ecs_enable(world, NormalSystem, false);

    ecs_progress(world, 0);

    test_int(normal_count, 1);

    ecs_enable(world, NormalSystem, true);

    ecs_progress(world, 0);

    test_int(normal_count, 2);

    ecs_fini(world);
}

void SystemPeriodic_disabled_feature() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, NormalSystem, EcsOnUpdate, Position);
    ECS_SYSTEM(world, NormalSystem2, EcsOnUpdate, Position);

    ECS_TYPE(world, Type, NormalSystem, NormalSystem2);

    ecs_progress(world, 0);

    test_int(normal_count, 1);
    test_int(normal_count_2, 1);

    ecs_enable(world, Type, false);

    ecs_progress(world, 0);

    test_int(normal_count, 1);
    test_int(normal_count_2, 1);

    ecs_enable(world, Type, true);

    ecs_progress(world, 0);

    test_int(normal_count, 2);
    test_int(normal_count_2, 2);

    ecs_fini(world);
}

void SystemPeriodic_disabled_nested_feature() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, NormalSystem, EcsOnUpdate, Position);
    ECS_SYSTEM(world, NormalSystem2, EcsOnUpdate, Position);
    ECS_SYSTEM(world, NormalSystem3, EcsOnUpdate, Position);

    ECS_TYPE(world, NestedType, NormalSystem2, NormalSystem3);
    ECS_TYPE(world, Type, NormalSystem, NestedType);

    ecs_progress(world, 0);

    test_int(normal_count, 1);
    test_int(normal_count_2, 1);
    test_int(normal_count_3, 1);

    ecs_enable(world, Type, false);

    ecs_progress(world, 0);

    test_int(normal_count, 1);
    test_int(normal_count_2, 1);
    test_int(normal_count_3, 1);

    ecs_enable(world, Type, true);

    ecs_progress(world, 0);

    test_int(normal_count, 2);
    test_int(normal_count_2, 2);
    test_int(normal_count_3, 2);

    ecs_fini(world);
}

void TwoRefs(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);
    ECS_COLUMN(it, Velocity, v, 2);

    test_assert(!ecs_is_owned(it, 1));
    test_assert(!ecs_is_owned(it, 2));

    (void)p;
    (void)v;

    probe_system(it);
}

void SystemPeriodic_two_refs() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, e, Position, Velocity);
    ECS_ENTITY(world, E2, Mass);

    ECS_SYSTEM(world, TwoRefs, EcsOnUpdate, e:Position, e:Velocity, :e, Mass);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 4);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], e);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], e);
    test_int(ctx.c[0][2], e);
    test_int(ctx.s[0][2], 0);
    test_int(ctx.c[0][3], ecs_typeid(Mass));
    test_int(ctx.s[0][3], 0);

    test_int(ctx.e[0], E2);

    ecs_fini(world);
}

void SystemPeriodic_filter_disabled() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Entity1, Position);
    ECS_ENTITY(world, Entity2, Position, Disabled);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 1);
    test_int(ctx.e[0], Entity1);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void SystemPeriodic_match_disabled() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Entity1, Position);
    ECS_ENTITY(world, Entity2, Position, Disabled);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, Disabled);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.e[0], Entity2);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], EcsDisabled);
    test_int(ctx.s[0][1], 0);

    ecs_fini(world);
}

void SystemPeriodic_match_disabled_and_enabled() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Entity1, Position);
    ECS_ENTITY(world, Entity2, Position, Disabled);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, ?Disabled);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.e[0], Entity1);
    test_int(ctx.e[1], Entity2);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], EcsDisabled);
    test_int(ctx.s[0][1], 0);

    ecs_fini(world);
}

void SystemPeriodic_match_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Entity1, Position);
    ECS_ENTITY(world, Entity2, Position, Prefab);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, Prefab);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.e[0], Entity2);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], EcsPrefab);
    test_int(ctx.s[0][1], 0);

    ecs_fini(world);
}

void SystemPeriodic_match_prefab_and_normal() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Entity1, Position);
    ECS_ENTITY(world, Entity2, Position, Prefab);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, ?Prefab);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.e[0], Entity1);
    test_int(ctx.e[1], Entity2);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], EcsPrefab);
    test_int(ctx.s[0][1], 0);

    ecs_fini(world);
}

static
void TestIsSharedOnNotSet(ecs_iter_t *it) {
    test_assert(ecs_is_owned(it, 2) != false);
}

void SystemPeriodic_is_shared_on_column_not_set() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, Entity, Position);

    ECS_SYSTEM(world, TestIsSharedOnNotSet, EcsOnUpdate, Position, ?Velocity);

    ecs_progress(world, 0);

    ecs_fini(world);
}


void SystemPeriodic_owned_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, base, Velocity);
    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, INSTANCEOF | base);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, OWNED:Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.e[0], e1);

    ecs_fini(world);
}

void SystemPeriodic_owned_not_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, base, Velocity);
    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, INSTANCEOF | base);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, !OWNED:Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.e[0], e2);

    ecs_fini(world);
}

void OwnedOr(ecs_iter_t *it) {
    probe_system(it);
}

void SystemPeriodic_owned_or_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, base, Velocity);
    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, Mass);
    ECS_ENTITY(world, e3, Position, INSTANCEOF | base);

    ECS_SYSTEM(world, OwnedOr, EcsOnUpdate, Position, OWNED:Velocity || OWNED:Mass);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.e[0], e1);
    test_int(ctx.c[1][0], ecs_typeid(Position));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[1][1], ecs_typeid(Mass));
    test_int(ctx.s[1][1], 0);
    test_int(ctx.e[1], e2);

    ecs_fini(world);
}

void SystemPeriodic_shared_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, base, Velocity);
    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, INSTANCEOF | base);
    ECS_ENTITY(world, e3, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, SHARED:Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], base);
    test_int(ctx.e[0], e2);

    ecs_fini(world);
}

void SystemPeriodic_shared_not_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, base, Velocity);
    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, INSTANCEOF | base);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, !SHARED:Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.e[0], e1);

    ecs_fini(world);
}

void SharedOr(ecs_iter_t *it) {
    probe_system(it);
}

void SystemPeriodic_shared_or_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, base1, Velocity);
    ECS_ENTITY(world, base2, Mass);
    ECS_ENTITY(world, e1, Position, Velocity);
    ECS_ENTITY(world, e2, Position, Mass);
    ECS_ENTITY(world, e3, Position, INSTANCEOF | base1);
    ECS_ENTITY(world, e4, Position, INSTANCEOF | base2);

    ECS_SYSTEM(world, SharedOr, EcsOnUpdate, Position, SHARED:Velocity || SHARED:Mass);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], base1);
    test_int(ctx.e[0], e3);
    test_int(ctx.c[1][0], ecs_typeid(Position));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[1][1], ecs_typeid(Mass));
    test_int(ctx.s[1][1], base2);
    test_int(ctx.e[1], e4);

    ecs_fini(world);
}

void SystemPeriodic_container_dont_match_inheritance() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, base, Velocity);
    ECS_ENTITY(world, e1, Position, INSTANCEOF | base);
    ECS_ENTITY(world, e2, Position, CHILDOF | base);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, PARENT:Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], base);
    test_int(ctx.e[0], e2);

    ecs_fini(world);
}

void SystemPeriodic_cascade_dont_match_inheritance() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, base, Velocity);
    ECS_ENTITY(world, e1, Position, INSTANCEOF | base);
    ECS_ENTITY(world, e2, Position, CHILDOF | base);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, CASCADE:Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.column_count, 2);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);
    test_int(ctx.c[1][0], ecs_typeid(Position));
    test_int(ctx.s[1][0], 0);
    test_int(ctx.c[1][1], ecs_typeid(Velocity));
    test_int(ctx.s[1][1], base);    
    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);

    ecs_fini(world);
}

void SystemPeriodic_not_from_singleton() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, !$:Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);

    ecs_add(world, EcsSingleton, Velocity);

    ecs_progress(world, 1);
    
    test_int(ctx.count, 1);

    ecs_fini(world);
}

void SystemPeriodic_not_from_entity() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e, Position);
    ECS_ENTITY(world, e2, 0);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, !e2:Velocity);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);

    ecs_add(world, e2, Velocity);

    ecs_progress(world, 1);
    
    test_int(ctx.count, 1);

    ecs_fini(world);
}

static
void TestContext(ecs_iter_t *it) {
    void *world_ctx = ecs_get_ctx(it->world);
    test_assert(world_ctx == it->ctx);
    int32_t *ctx = it->ctx;
    (*ctx) ++;
}

void SystemPeriodic_sys_context() {
    ecs_world_t *world = ecs_init();
    int32_t param = 0;

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, TestContext, EcsOnUpdate, Position);

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = {TestContext}, .ctx = &param
    });

    test_assert(ecs_get_system_ctx(world, TestContext) == &param);

    ecs_fini(world);
}

void SystemPeriodic_get_sys_context_from_param() {
    ecs_world_t *world = ecs_init();
    int32_t param = 0;

    ECS_COMPONENT(world, Position);
    ECS_ENTITY(world, e, Position);

    ECS_SYSTEM(world, TestContext, EcsOnUpdate, Position);

    /* Set world context so system can compare if pointer is correct */
    ecs_set_ctx(world, &param);

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = {TestContext}, .ctx = &param
    });

    ecs_progress(world, 1);

    test_int(param, 1);

    ecs_fini(world);
}

static bool Test_feld_w_zero_size_invoked = false;

static
void Test_feld_w_zero_size(ecs_iter_t *it) {
    test_assert(ecs_element_w_size(it, 0, 1, 0) != ecs_element_w_size(it, 0, 1, 1));
    Test_feld_w_zero_size_invoked = true;
}

void SystemPeriodic_use_field_w_0_size() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);

    ECS_SYSTEM(world, Test_feld_w_zero_size, EcsOnUpdate, Position);

    ecs_progress(world, 1);

    test_assert(Test_feld_w_zero_size_invoked == true);

    ecs_fini(world);
}

static ecs_entity_t dummy_invoked = 0;

static void Dummy(ecs_iter_t *it) {
    test_assert(dummy_invoked == 0);
    dummy_invoked = it->entities[0];
}

void SystemPeriodic_owned_only() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, OWNED:Position);

    ecs_entity_t e = ecs_new(world, Position);

    ecs_progress(world, 0);

    test_assert(dummy_invoked == e);

    ecs_fini(world);
}

static void AssertReadonly(ecs_iter_t *it) {
    test_assert(dummy_invoked == 0);
    dummy_invoked = it->entities[0];

    test_assert( ecs_is_readonly(it, 1) == true);
}

void SystemPeriodic_shared_only() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, AssertReadonly, EcsOnUpdate, SHARED:Position);

    ecs_entity_t base = ecs_new(world, Position);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, base);

    ecs_progress(world, 0);

    test_assert(dummy_invoked == e);

    ecs_fini(world);
}

void SystemPeriodic_is_in_readonly() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, AssertReadonly, EcsOnUpdate, [in] Position);

    ecs_entity_t e = ecs_new(world, Position);

    ecs_progress(world, 0);

    test_assert(dummy_invoked == e);

    ecs_fini(world);
}

void SystemPeriodic_get_period() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, [in] Position);

    ecs_set_interval(world, Dummy, 10.0);

    test_flt( ecs_get_interval(world, Dummy), 10.0);

    ecs_fini(world);
}

void TypeSystem(ecs_iter_t *it) {
    probe_system(it);
}

void SystemPeriodic_and_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, MyType, Position, Velocity);

    ECS_SYSTEM(world, TypeSystem, EcsOnUpdate, AND | MyType);

    ecs_new(world, Position);
    ecs_new(world, Velocity);
    ecs_entity_t e3 = ecs_new(world, MyType);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, TypeSystem);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e3);
    test_int(ctx.c[0][0], MyType);
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void SystemPeriodic_or_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, MyType, Position, Velocity);

    ECS_SYSTEM(world, TypeSystem, EcsOnUpdate, OR | MyType);

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_entity_t e2 = ecs_new(world, Velocity);
    ecs_entity_t e3 = ecs_new(world, MyType);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, TypeSystem);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);
    test_int(ctx.c[0][0], MyType);
    test_int(ctx.c[1][0], MyType);
    test_int(ctx.c[2][0], MyType);
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}
