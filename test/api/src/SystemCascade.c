#include <api.h>

static
void Iter(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);
    Position *p_parent = ecs_term(it, Position, 2);

    test_assert(!p_parent || !ecs_is_owned(it, 2));

    probe_system(it);

    int i;
    for (i = 0; i < it->count; i ++) {
        p[i].x ++;
        p[i].y ++;

        if (p_parent) {
            p[i].x += p_parent->x;
            p[i].y += p_parent->y;
        }
    }
}

void SystemCascade_cascade_depth_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, CASCADE:Position);

    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e2, Position, {1, 2});
    ecs_set(world, e3, Position, {1, 2});
    ecs_set(world, e4, Position, {1, 2});

    ecs_add_pair(world, e3, EcsChildOf, e1);
    ecs_add_pair(world, e4, EcsChildOf, e2);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 4);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    probe_has_entity(&ctx, e1);
    probe_has_entity(&ctx, e2);
    probe_has_entity(&ctx, e3);
    probe_has_entity(&ctx, e4);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    ecs_fini(world);
}

void SystemCascade_cascade_depth_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Position);
    ECS_ENTITY(world, e5, Position);
    ECS_ENTITY(world, e6, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, CASCADE:Position);

    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e2, Position, {1, 2});
    ecs_set(world, e3, Position, {1, 2});
    ecs_set(world, e4, Position, {1, 2});
    ecs_set(world, e5, Position, {1, 2});
    ecs_set(world, e6, Position, {1, 2});

    ecs_add_pair(world, e3, EcsChildOf, e1); /* depth 1 */
    ecs_add_pair(world, e4, EcsChildOf, e2); /* depth 1 */
    ecs_add_pair(world, e5, EcsChildOf, e3); /* depth 2 */
    ecs_add_pair(world, e6, EcsChildOf, e4); /* depth 2 */

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 6);
    test_int(ctx.invoked, 5);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_assert((ctx.e[0] == e1 && ctx.e[1] == e2) || (ctx.e[0] == e2 && ctx.e[1] == e1));
    test_assert((ctx.e[2] == e3 && ctx.e[3] == e4) || (ctx.e[2] == e4 && ctx.e[3] == e3));
    test_assert((ctx.e[4] == e5 && ctx.e[5] == e6) || (ctx.e[4] == e6 && ctx.e[5] == e5));

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    p = ecs_get(world, e5, Position);
    test_assert(p != NULL);
    test_int(p->x, 6);
    test_int(p->y, 9);

    p = ecs_get(world, e6, Position);
    test_assert(p != NULL);
    test_int(p->x, 6);
    test_int(p->y, 9);

    ecs_fini(world);
}

void SystemCascade_cascade_depth_2_new_syntax() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Position);
    ECS_ENTITY(world, e5, Position);
    ECS_ENTITY(world, e6, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, ?Position(cascade(ChildOf)));

    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e2, Position, {1, 2});
    ecs_set(world, e3, Position, {1, 2});
    ecs_set(world, e4, Position, {1, 2});
    ecs_set(world, e5, Position, {1, 2});
    ecs_set(world, e6, Position, {1, 2});

    ecs_add_pair(world, e3, EcsChildOf, e1); /* depth 1 */
    ecs_add_pair(world, e4, EcsChildOf, e2); /* depth 1 */
    ecs_add_pair(world, e5, EcsChildOf, e3); /* depth 2 */
    ecs_add_pair(world, e6, EcsChildOf, e4); /* depth 2 */

    Probe ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 6);
    test_int(ctx.invoked, 5);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_assert((ctx.e[0] == e1 && ctx.e[1] == e2) || (ctx.e[0] == e2 && ctx.e[1] == e1));
    test_assert((ctx.e[2] == e3 && ctx.e[3] == e4) || (ctx.e[2] == e4 && ctx.e[3] == e3));
    test_assert((ctx.e[4] == e5 && ctx.e[5] == e6) || (ctx.e[4] == e6 && ctx.e[5] == e5));

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    p = ecs_get(world, e5, Position);
    test_assert(p != NULL);
    test_int(p->x, 6);
    test_int(p->y, 9);

    p = ecs_get(world, e6, Position);
    test_assert(p != NULL);
    test_int(p->x, 6);
    test_int(p->y, 9);

    ecs_fini(world);
}

static
void AddParent(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);
    Position *p_parent = ecs_term(it, Position, 2);

    test_assert(!p_parent || !ecs_is_owned(it, 2));

    probe_system(it);

    int i;
    for (i = 0; i < it->count; i ++) {
        if (p_parent) {
            p[i].x += p_parent->x;
            p[i].y += p_parent->y;
        }
    }
}

void SystemCascade_add_after_match() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Position);

    ECS_SYSTEM(world, AddParent, EcsOnUpdate, Position, CASCADE:Position);

    ecs_entity_t parent = ecs_new(world, 0);
    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e2, Position, {1, 2});
    ecs_set(world, e3, Position, {1, 2});
    ecs_set(world, e4, Position, {1, 2});

    ecs_add_pair(world, e3, EcsChildOf, parent); /* depth 1 */
    ecs_add_pair(world, e4, EcsChildOf, parent); /* depth 1 */

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    /* Before adding Position to parent, it wasn't being considered for the
     * CASCADE column, so tables could have been ordered randomly. Make sure
     * that queries can handle changes to depth after all tables are matched */
    ecs_set(world, parent, Position, {1, 2});

    ctx = (Probe){0};

    ecs_progress(world, 1);

    test_int(ctx.count, 5);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, AddParent);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_assert(ctx.e[0] == e1 || ctx.e[1] == e1 || ctx.e[2] == e1);
    test_assert(ctx.e[0] == e2 || ctx.e[1] == e2 || ctx.e[2] == e2);
    test_assert(ctx.e[0] == parent || ctx.e[1] == parent || ctx.e[2] == parent);
    test_assert(ctx.e[3] == e3 || ctx.e[4] == e3);
    test_assert(ctx.e[3] == e4 || ctx.e[4] == e4);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 4);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 4);

    ecs_fini(world);
}

void SystemCascade_adopt_after_match() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Position);

    ECS_SYSTEM(world, AddParent, EcsOnUpdate, Position, CASCADE:Position);

    ecs_entity_t parent = ecs_set(world, 0, Position, {1, 2});
    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e2, Position, {1, 2});
    ecs_set(world, e3, Position, {1, 2});
    ecs_set(world, e4, Position, {1, 2});

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 1);

    ecs_add_pair(world, e3, EcsChildOf, parent);
    ecs_add_pair(world, e4, EcsChildOf, parent);

    ctx = (Probe){0};

    ecs_progress(world, 1);

    test_int(ctx.count, 5);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, AddParent);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], parent);
    test_int(ctx.e[3], e3);
    test_int(ctx.e[4], e4);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 4);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 4);

    ecs_fini(world);
}

void SystemCascade_rematch_w_empty_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *q = ecs_query_new(world, "CASCADE:Position, Velocity");
    test_assert(q != NULL);

    ecs_entity_t parent = ecs_new(world, Position);
    ecs_add(world, parent, Velocity);

    ecs_entity_t child = ecs_new(world, Velocity);
    ecs_add_pair(world, child, EcsChildOf, parent);

    ecs_iter_t it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], parent);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], child);
    test_assert(!ecs_query_next(&it));

    // Change parent, trigger rematch
    ecs_remove(world, parent, Position);

    it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], parent);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], child);
    test_assert(!ecs_query_next(&it));    

    ecs_fini(world);
}

void SystemCascade_query_w_only_cascade() {
    ecs_world_t *world = ecs_mini();

    ecs_query_t *q = ecs_query_new(world, "CASCADE:Name");;
    test_assert(q != NULL);

    int32_t count = 0;

    /* Should match everything (since everything is a root without further 
     * qualifications). Since no other entities have been created, all entities
     * must be builtin ones. */
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        for (int i = 0; i < it.count; i ++) {
            ecs_entity_t e = it.entities[i];
            test_assert(
                e == EcsFlecs ||
                ecs_has_pair(world, e, EcsChildOf, EcsFlecs) ||
                ecs_has_pair(world, e, EcsChildOf, EcsFlecsCore)
            );

            count ++;
        }
    }

    test_assert(count != 0);

    ecs_fini(world);
}

void SystemCascade_custom_relation_cascade_depth_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Rel);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, ?Position(cascade(Rel)));

    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e2, Position, {1, 2});
    ecs_set(world, e3, Position, {1, 2});
    ecs_set(world, e4, Position, {1, 2});

    ecs_add_pair(world, e3, Rel, e1);
    ecs_add_pair(world, e4, Rel, e2);

    Probe ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 4);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    probe_has_entity(&ctx, e1);
    probe_has_entity(&ctx, e2);
    probe_has_entity(&ctx, e3);
    probe_has_entity(&ctx, e4);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    ecs_fini(world);
}

void SystemCascade_custom_relation_cascade_depth_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Rel);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Position);
    ECS_ENTITY(world, e5, Position);
    ECS_ENTITY(world, e6, Position);

    ECS_SYSTEM(world, Iter, EcsOnUpdate, Position, ?Position(cascade(Rel)));

    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e2, Position, {1, 2});
    ecs_set(world, e3, Position, {1, 2});
    ecs_set(world, e4, Position, {1, 2});
    ecs_set(world, e5, Position, {1, 2});
    ecs_set(world, e6, Position, {1, 2});

    ecs_add_pair(world, e3, Rel, e1); /* depth 1 */
    ecs_add_pair(world, e4, Rel, e2); /* depth 1 */
    ecs_add_pair(world, e5, Rel, e3); /* depth 2 */
    ecs_add_pair(world, e6, Rel, e4); /* depth 2 */

    Probe ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 6);
    test_int(ctx.invoked, 5);
    test_int(ctx.system, Iter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_assert((ctx.e[0] == e1 && ctx.e[1] == e2) || (ctx.e[0] == e2 && ctx.e[1] == e1));
    test_assert((ctx.e[2] == e3 && ctx.e[3] == e4) || (ctx.e[2] == e4 && ctx.e[3] == e3));
    test_assert((ctx.e[4] == e5 && ctx.e[5] == e6) || (ctx.e[4] == e6 && ctx.e[5] == e5));

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 3);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 6);

    p = ecs_get(world, e5, Position);
    test_assert(p != NULL);
    test_int(p->x, 6);
    test_int(p->y, 9);

    p = ecs_get(world, e6, Position);
    test_assert(p != NULL);
    test_int(p->x, 6);
    test_int(p->y, 9);

    ecs_fini(world);
}

void SystemCascade_custom_relation_add_after_match() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Rel);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Position);

    ECS_SYSTEM(world, AddParent, EcsOnUpdate, Position, ?Position(cascade(Rel)));

    ecs_entity_t parent = ecs_new(world, 0);
    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e2, Position, {1, 2});
    ecs_set(world, e3, Position, {1, 2});
    ecs_set(world, e4, Position, {1, 2});

    ecs_add_pair(world, e3, Rel, parent); /* depth 1 */
    ecs_add_pair(world, e4, Rel, parent); /* depth 1 */

    Probe ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    /* Before adding Position to parent, it wasn't being considered for the
     * CASCADE column, so tables could have been ordered randomly. Make sure
     * that queries can handle changes to depth after all tables are matched */
    ecs_set(world, parent, Position, {1, 2});

    ctx = (Probe){0};

    ecs_progress(world, 1);

    test_int(ctx.count, 5);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, AddParent);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_assert(ctx.e[0] == e1 || ctx.e[1] == e1 || ctx.e[2] == e1);
    test_assert(ctx.e[0] == e2 || ctx.e[1] == e2 || ctx.e[2] == e2);
    test_assert(ctx.e[0] == parent || ctx.e[1] == parent || ctx.e[2] == parent);
    test_assert(ctx.e[3] == e3 || ctx.e[4] == e3);
    test_assert(ctx.e[3] == e4 || ctx.e[4] == e4);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 4);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 4);

    ecs_fini(world);
}

void SystemCascade_custom_relation_adopt_after_match() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Rel);

    ECS_ENTITY(world, e1, Position);
    ECS_ENTITY(world, e2, Position);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Position);

    ECS_SYSTEM(world, AddParent, EcsOnUpdate, Position, ?Position(cascade(Rel)));

    ecs_entity_t parent = ecs_set(world, 0, Position, {1, 2});
    ecs_set(world, e1, Position, {1, 2});
    ecs_set(world, e2, Position, {1, 2});
    ecs_set(world, e3, Position, {1, 2});
    ecs_set(world, e4, Position, {1, 2});

    Probe ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    ecs_add_pair(world, e3, Rel, parent);
    ecs_add_pair(world, e4, Rel, parent);

    ctx = (Probe){0};

    ecs_progress(world, 1);

    test_int(ctx.count, 5);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, AddParent);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], parent);
    test_int(ctx.e[3], e3);
    test_int(ctx.e[4], e4);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    const Position *p = ecs_get(world, e1, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    p = ecs_get(world, e2, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    p = ecs_get(world, e3, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 4);

    p = ecs_get(world, e4, Position);
    test_assert(p != NULL);
    test_int(p->x, 2);
    test_int(p->y, 4);

    ecs_fini(world);
}

void SystemCascade_custom_relation_rematch_w_empty_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TAG(world, Rel);

    ecs_query_t *q = ecs_query_new(world, "?Position(cascade(Rel)), Velocity");
    test_assert(q != NULL);

    ecs_entity_t parent = ecs_new(world, Position);
    ecs_add(world, parent, Velocity);

    ecs_entity_t child = ecs_new(world, Velocity);
    ecs_add_pair(world, child, Rel, parent);

    ecs_iter_t it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], parent);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], child);
    test_assert(!ecs_query_next(&it));

    // Change parent, trigger rematch
    ecs_remove(world, parent, Position);

    it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], parent);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], child);
    test_assert(!ecs_query_next(&it));    

    ecs_fini(world);
}
