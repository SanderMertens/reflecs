#include <api.h>

static
void Observer(ecs_iter_t *it) {
    probe_system_w_ctx(it, it->ctx);
}

static
void Observer_w_value(ecs_iter_t *it) {
    probe_system_w_ctx(it, it->ctx);

    test_int(it->count, 1);
    test_int(it->term_count, 2);
    test_assert(it->entities != NULL);
    test_assert(it->entities[0] != 0);

    Position *p = ecs_term(it, Position, 1);
    Velocity *v = ecs_term(it, Velocity, 2);
    
    test_int(p->x, 10);
    test_int(p->y, 20);

    test_int(v->x, 1);
    test_int(v->y, 2);
}

static bool dummy_called = false;

static
void Dummy(ecs_iter_t *it) {
    dummy_called = true;
}

void Observer_2_terms_w_on_add() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], TagA);
    test_int(ctx.c[0][1], TagB);

    ecs_fini(world);
}

void Observer_2_terms_w_on_remove() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB}},
        .events = {EcsOnRemove},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_remove_id(world, e, TagA);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnRemove);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], TagA);
    test_int(ctx.c[0][1], TagB);

    ecs_fini(world);
}

void Observer_2_terms_w_on_set_value() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{ecs_id(Position)}, {ecs_id(Velocity)}},
        .events = {EcsOnSet},
        .callback = Observer_w_value,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_set(world, e, Velocity, {1, 2});
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnSet);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_id(Position));
    test_int(ctx.c[0][1], ecs_id(Velocity));

    ecs_fini(world);
}

void Observer_2_terms_w_on_remove_value() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{ecs_id(Position)}, {ecs_id(Velocity)}},
        .events = {EcsOnRemove},
        .callback = Observer_w_value,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_set(world, e, Velocity, {1, 2});
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnRemove);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_id(Position));
    test_int(ctx.c[0][1], ecs_id(Velocity));

    ecs_fini(world);
}


void Observer_2_terms_w_on_add_2nd() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], TagA);
    test_int(ctx.c[0][1], TagB);

    ecs_fini(world);
}

void Observer_2_terms_w_on_remove_2nd() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB}},
        .events = {EcsOnRemove},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_remove_id(world, e, TagB);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnRemove);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], TagA);
    test_int(ctx.c[0][1], TagB);

    ecs_fini(world);
}

void Observer_2_pair_terms_w_on_add() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);

    ecs_id_t pair_a = ecs_pair(RelA, ObjA);
    ecs_id_t pair_b = ecs_pair(RelB, ObjB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{pair_a}, {pair_b}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_pair(world, e, RelA, ObjA);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, RelB, ObjB);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], pair_a);
    test_int(ctx.c[0][1], pair_b);

    ecs_fini(world);
}

void Observer_2_pair_terms_w_on_remove() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);

    ecs_id_t pair_a = ecs_pair(RelA, ObjA);
    ecs_id_t pair_b = ecs_pair(RelB, ObjB);    

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{pair_a}, {pair_b}},
        .events = {EcsOnRemove},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_pair(world, e, RelA, ObjA);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, RelB, ObjB);
    test_int(ctx.invoked, 0);

    ecs_remove_pair(world, e, RelB, ObjB);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnRemove);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], pair_a);
    test_int(ctx.c[0][1], pair_b);

    ecs_fini(world);
}

void Observer_2_wildcard_pair_terms_w_on_add() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{ecs_pair(RelA, ObjA)}, {ecs_pair(RelB, EcsWildcard)}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_pair(world, e, RelA, ObjA);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, RelB, ObjB);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_pair(RelA, ObjA));
    test_int(ctx.c[0][1], ecs_pair(RelB, ObjB));

    ecs_fini(world);
}

void Observer_2_wildcard_pair_terms_w_on_add_2_matching() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{ecs_pair(RelA, ObjA)}, {ecs_pair(RelB, EcsWildcard)}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_pair(world, e, RelA, ObjA);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, RelB, ObjA);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_pair(RelA, ObjA));
    test_int(ctx.c[0][1], ecs_pair(RelB, ObjA));

    ctx = (Probe){ 0 };
    ecs_add_pair(world, e, RelB, ObjB);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_pair(RelA, ObjA));
    test_int(ctx.c[0][1], ecs_pair(RelB, ObjB));

    ecs_fini(world);
}

void Observer_2_wildcard_pair_terms_w_on_add_3_matching() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);
    ECS_TAG(world, ObjC);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{ecs_pair(RelA, ObjA)}, {ecs_pair(RelB, EcsWildcard)}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_pair(world, e, RelA, ObjA);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, RelB, ObjA);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_pair(RelA, ObjA));
    test_int(ctx.c[0][1], ecs_pair(RelB, ObjA));

    ctx = (Probe){ 0 };
    ecs_add_pair(world, e, RelB, ObjC);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_pair(RelA, ObjA));
    test_int(ctx.c[0][1], ecs_pair(RelB, ObjC));

    ctx = (Probe){ 0 };
    ecs_add_pair(world, e, RelB, ObjB);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_pair(RelA, ObjA));
    test_int(ctx.c[0][1], ecs_pair(RelB, ObjB));

    ecs_fini(world);
}


void Observer_2_wildcard_pair_terms_w_on_remove() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{ecs_pair(RelA, ObjA)}, {ecs_pair(RelB, EcsWildcard)}},
        .events = {EcsOnRemove},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_pair(world, e, RelA, ObjA);
    test_int(ctx.invoked, 0);

    ecs_add_pair(world, e, RelB, ObjB);
    test_int(ctx.invoked, 0);

    ecs_remove_pair(world, e, RelB, ObjB);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnRemove);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_pair(RelA, ObjA));
    test_int(ctx.c[0][1], ecs_pair(RelB, ObjB));

    ecs_fini(world);
}

void Observer_2_terms_1_not_w_on_add() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB, .oper = EcsNot}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_clear(world, e);
    test_assert(!ecs_has(world, e, TagB));

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], TagA);
    test_int(ctx.c[0][1], TagB);

    ecs_fini(world);
}

void Observer_2_terms_1_not_w_on_remove() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB, .oper = EcsNot}},
        .events = {EcsOnRemove},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_remove_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_clear(world, e);
    test_assert(!ecs_has(world, e, TagB));

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0); 

    ecs_remove_id(world, e, TagA);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnRemove);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], TagA);
    test_int(ctx.c[0][1], TagB);

    ecs_fini(world);
}

void Observer_2_terms_w_on_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{ecs_id(Position)}, {TagB}},
        .events = {EcsOnSet},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Position);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnSet);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_id(Position));
    test_int(ctx.c[0][1], TagB);

    ecs_fini(world);
}

void Observer_2_terms_w_un_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{ecs_id(Position)}, {TagB}},
        .events = {EcsUnSet},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_add(world, e, Position);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsUnSet);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_id(Position));
    test_int(ctx.c[0][1], TagB);

    ecs_fini(world);
}

void Observer_3_terms_2_or_on_add() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB, .oper = EcsOr}, {TagC, .oper = EcsOr}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], TagA);
    test_int(ctx.c[0][1], TagB);

    ctx = (Probe){0};

    ecs_add_id(world, e, TagC);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, o);
    test_int(ctx.event, EcsOnAdd);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], TagA);
    test_int(ctx.c[0][1], TagC);

    ecs_fini(world);
}

void Observer_3_terms_2_or_on_remove() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB, .oper = EcsOr}, {TagC, .oper = EcsOr}},
        .events = {EcsOnRemove},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagC);
    test_int(ctx.invoked, 0);

    ecs_remove_id(world, e, TagC);
    test_int(ctx.invoked, 1);

    ecs_remove_id(world, e, TagB);
    test_int(ctx.invoked, 2);

    ecs_remove_id(world, e, TagA);
    test_int(ctx.invoked, 2);

    ecs_fini(world);
}

void Observer_2_terms_w_from_entity_on_add() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    
    ecs_entity_t x = ecs_new_id(world);
    
    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB, .oper = EcsOr, .args[0].entity = x}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_clear(world, e);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, x, TagB);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 1);

    ecs_fini(world);
}

void Observer_2_terms_on_remove_on_clear() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB}},
        .events = {EcsOnRemove},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_clear(world, e);
    test_int(ctx.invoked, 2);    

    ecs_fini(world);
}

void Observer_2_terms_on_remove_on_delete() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{TagA}, {TagB}},
        .events = {EcsOnRemove},
        .callback = Observer,
        .ctx = &ctx
    });
    test_assert(o != 0);

    ecs_entity_t e = ecs_new_id(world);

    ecs_add_id(world, e, TagA);
    test_int(ctx.invoked, 0);

    ecs_add_id(world, e, TagB);
    test_int(ctx.invoked, 0);

    ecs_delete(world, e);
    test_int(ctx.invoked, 2);    

    ecs_fini(world);
}

void Observer_observer_w_self() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t self = ecs_new_id(world);

    Probe ctx = {0};
    ecs_entity_t system = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{Tag}},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx,
        .self = self
    });

    ecs_entity_t e = ecs_new_id(world);
    ecs_add_id(world, e, Tag);

    test_int(ctx.count, 1);
    test_assert(ctx.system == system);
    test_assert(ctx.self == self);

    ecs_fini(world);
}

void Observer_add_after_delete_observer() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t observer = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{.id = ecs_id(Position) }},
        .events = {EcsOnAdd},
        .callback = Dummy
    });

    ecs_entity_t e1 = ecs_new(world, Position);
    test_assert(e1 != 0);
    test_assert(ecs_has(world, e1, Position));
    test_int(dummy_called, 1);

    dummy_called = 0;

    ecs_delete(world, observer);
    test_int(dummy_called, 0);

    ecs_entity_t e2 = ecs_new(world, Position);
    test_assert(e2 != 0);
    test_assert(ecs_has(world, e2, Position));
    test_int(dummy_called, 0);

    ecs_fini(world);
}

void Observer_remove_after_delete_observer() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t observer = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{.id = ecs_id(Position) }},
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

    ecs_delete(world, observer);
    test_int(dummy_called, 0);

    ecs_entity_t e2 = ecs_new(world, Position);
    test_assert(e2 != 0);
    test_assert(ecs_has(world, e2, Position));
    test_int(dummy_called, 0);

    ecs_remove(world, e2, Position);
    test_int(dummy_called, 0);

    ecs_fini(world);
}

static int ctx_value;
static
void ctx_free(void *ctx) {
    test_assert(&ctx_value == ctx);
    ctx_value ++;
}

static int binding_ctx_value;
static
void binding_ctx_free(void *ctx) {
    test_assert(&binding_ctx_value == ctx);
    binding_ctx_value ++;
}

void Observer_delete_observer_w_ctx() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t o = ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms =  {{ Tag }},
        .events = {EcsOnAdd},
        .callback = Observer,
        .ctx = &ctx_value,
        .ctx_free = ctx_free,
        .binding_ctx = &binding_ctx_value,
        .binding_ctx_free = binding_ctx_free
    });
    test_assert(o != 0);

    test_assert(ecs_get_observer_ctx(world, o) == &ctx_value);
    test_assert(ecs_get_observer_binding_ctx(world, o) == &binding_ctx_value);

    ecs_delete(world, o);

    test_int(ctx_value, 1);
    test_int(binding_ctx_value, 1);

    ecs_fini(world);
}
