#include <api.h>

void Deinit(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);

    Velocity *v = NULL;
    if (it->term_count >= 2) {
        v = ecs_term(it, Velocity, 2);
    }

    probe_system(it);

    /* Write to validate columns point to valid memory */
    int i;
    for (i = 0; i < it->count; i ++) {
        p[i].x = 0;
        p[i].y = 0;

        if (v) {
            v[i].x = 0;
            v[i].y = 0;
        }
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

void TriggerOnRemove_remove_match_1_of_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TRIGGER(world, Deinit, EcsOnRemove, Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    test_int(ctx.count, 0);

    ecs_remove(world, e, Position);

    test_int(ctx.count, 1);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void TriggerOnRemove_remove_match_1_of_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);
    ECS_TRIGGER(world, Deinit, EcsOnRemove, Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Type);
    test_assert(e != 0);

    test_int(ctx.count, 0);

    ecs_remove(world, e, Type);

    test_int(ctx.count, 1);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void TriggerOnRemove_remove_no_match_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TRIGGER(world, Deinit, EcsOnRemove, Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    test_int(ctx.count, 0);

    ecs_remove(world, e, Velocity);

    test_int(ctx.count, 0);

    ecs_fini(world);
}

void TriggerOnRemove_delete_match_1_of_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TRIGGER(world, Deinit, EcsOnRemove, Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    test_int(ctx.count, 0);

    ecs_delete(world, e);

    test_int(ctx.count, 1);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void TriggerOnRemove_delete_match_1_of_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);
    ECS_TRIGGER(world, Deinit, EcsOnRemove, Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Type);
    test_assert(e != 0);

    test_int(ctx.count, 0);

    ecs_delete(world, e);

    test_int(ctx.count, 1);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ecs_fini(world);
}

void TriggerOnRemove_delete_no_match_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TRIGGER(world, Deinit, EcsOnRemove, Position);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Velocity);
    test_assert(e != 0);

    test_int(ctx.count, 0);

    ecs_delete(world, e);

    test_int(ctx.count, 0); 

    ecs_fini(world);
}

static Position old_position = {0};

static
void RemovePosition(ecs_iter_t *it) {
    ECS_COLUMN(it, Position, p, 1);

    test_assert(it->count == 1);

    old_position = p[0];
}

void TriggerOnRemove_remove_watched() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_TRIGGER(world, RemovePosition, EcsOnRemove, Position);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    test_assert(e != 0);

    /* Make parent entity watched */
    ecs_new_w_pair(world, EcsChildOf, e);

    ecs_remove(world, e, Position);

    test_int(old_position.x, 10);
    test_int(old_position.y, 20);

    ecs_fini(world);
}


void TriggerOnRemove_delete_watched() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_TRIGGER(world, RemovePosition, EcsOnRemove, Position);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    test_assert(e != 0);

    /* Make parent entity watched */
    ecs_new_w_pair(world, EcsChildOf, e);

    ecs_delete(world, e);

    test_int(old_position.x, 10);
    test_int(old_position.y, 20);

    ecs_fini(world);
}

static bool dummy_called = false;

static
void Dummy(ecs_iter_t *it) {
    dummy_called = true;
}

void TriggerOnRemove_on_remove_in_on_update() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ECS_SYSTEM(world, Remove_from_current, EcsOnUpdate, Position);
    ECS_TRIGGER(world, Dummy, EcsOnRemove, Velocity);

    IterData ctx = {.component = ecs_typeid(Velocity)};
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e1 = ecs_new(world, Type);
    ecs_entity_t e2 = ecs_new(world, Type);
    ecs_entity_t e3 = ecs_new(world, Type);

    ecs_progress(world, 1);

    test_assert( ecs_has(world, e1, Position));
    test_assert( ecs_has(world, e2, Position));
    test_assert( ecs_has(world, e3, Position));

    test_assert( !ecs_has(world, e1, Velocity));
    test_assert( !ecs_has(world, e2, Velocity));
    test_assert( !ecs_has(world, e3, Velocity));

    test_assert(dummy_called);

    ecs_fini(world);
}

static int dummy_dtor_invoked = 0;

typedef struct DummyComp {
    int value;
} DummyComp;

static
void RemoveDummyComp(ecs_iter_t *it) { 
    int i;
    for (i = 0; i < it->count; i ++) {
        test_assert(ecs_is_valid(it->world, it->entities[i]));
        test_assert(ecs_is_alive(it->world, it->entities[i]));
    }

    dummy_dtor_invoked ++;
}

void TriggerOnRemove_valid_entity_after_delete() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, DummyComp);
    ECS_TRIGGER(world, RemoveDummyComp, EcsOnRemove, DummyComp);

    ecs_entity_t e = ecs_new(world, DummyComp);
    test_assert(e != 0);

    ecs_delete(world, e);
    test_assert(!ecs_is_valid(world, e));
    test_assert(!ecs_is_alive(world, e));

    test_int(dummy_dtor_invoked, 1);

    ecs_fini(world); 
}

void TriggerOnRemove_remove_after_delete_trigger() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t trigger = ecs_trigger_init(world, &(ecs_trigger_desc_t){
        .term.id = ecs_id(Position),
        .events = {EcsOnRemove},
        .callback = Dummy
    });

    ecs_entity_t e1 = ecs_new(world, Position);
    test_assert(e1 != 0);
    test_assert(ecs_has(world, e1, Position));
    test_int(dummy_called, 0);

    ecs_remove(world, e1, Position);
    test_int(dummy_called, 1);

    dummy_called = 0;

    ecs_delete(world, trigger);
    test_int(dummy_called, 0);

    ecs_entity_t e2 = ecs_new(world, Position);
    test_assert(e2 != 0);
    test_assert(ecs_has(world, e2, Position));
    test_int(dummy_called, 0);

    ecs_remove(world, e2, Position);
    test_int(dummy_called, 0);

    ecs_fini(world);
}

void TriggerOnRemove_remove_after_delete_wildcard_id_trigger() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t trigger = ecs_trigger_init(world, &(ecs_trigger_desc_t){
        .term.id = EcsWildcard,
        .events = {EcsOnRemove},
        .callback = Dummy
    });

    ecs_entity_t e1 = ecs_new(world, Position);
    test_assert(e1 != 0);
    test_assert(ecs_has(world, e1, Position));
    test_int(dummy_called, 0);

    ecs_remove(world, e1, Position);
    test_int(dummy_called, 1);

    dummy_called = 0;

    ecs_delete(world, trigger);
    test_int(dummy_called, 1);

    dummy_called = 0;

    ecs_entity_t e2 = ecs_new(world, Position);
    test_assert(e2 != 0);
    test_assert(ecs_has(world, e2, Position));
    test_int(dummy_called, 0);

    ecs_remove(world, e2, Position);
    test_int(dummy_called, 0);

    ecs_fini(world);
}
