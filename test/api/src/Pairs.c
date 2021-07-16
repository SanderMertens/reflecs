#include <api.h>

typedef struct Rel {
    float value;
} Rel;

typedef struct RelA {
    float value;
} RelA;

typedef struct RelB {
    float value;
} RelB;

typedef struct Obj {
    float value;
} Obj;

void ProcessPairs(ecs_iter_t *it) {
    Rel *tr = ecs_term(it, Rel, 1);

    probe_system(it);

    if (tr) {
        int32_t i;
        for (i = 0; i < it->count; i ++) {
            tr[i].value ++;
        }
    }
}

void Pairs_type_w_one_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_SYSTEM(world, ProcessPairs, EcsOnUpdate, PAIR | Rel);

    /* Ensure that pair is matched against different components */
    ecs_entity_t e1 = ecs_set_pair(world, 0, Rel, ecs_typeid(Position), {
        .value = 10
    });

    test_assert(e1 != 0);
    test_assert( ecs_has_pair(world, e1, ecs_typeid(Rel), ecs_typeid(Position)));

    ecs_entity_t e2 = ecs_set_pair(world, 0, Rel, ecs_typeid(Velocity), {
        .value = 20
    });
    test_assert(e2 != 0);
    test_assert( ecs_has_pair(world, e2, ecs_typeid(Rel), ecs_typeid(Velocity)));

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 0);

    const Rel* tr = ecs_get_pair(world, e1, Rel, ecs_typeid(Position));
    test_assert(tr != NULL);
    test_int(tr->value, 11);

    tr = ecs_get_pair(world, e2, Rel, ecs_typeid(Velocity));
    test_assert(tr != NULL);
    test_int(tr->value, 21); 

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, ProcessPairs);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Position));

    c = ctx.c[1][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Velocity));

    test_int(ctx.s[0][0], 0);
    test_int(ctx.s[1][0], 0);

    ecs_fini(world);
}

void Pairs_type_w_two_pairs() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_SYSTEM(world, ProcessPairs, EcsOnUpdate, PAIR | Rel);

    /* Ensure that pair is matched against different components on same entity */
    ecs_entity_t e1 = ecs_new(world, 0);
    ecs_set_pair(world, e1, Rel, ecs_typeid(Position), {
        .value = 10
    });  
    test_assert( ecs_has_pair(world, e1, ecs_typeid(Rel), ecs_typeid(Position)));

    ecs_set_pair(world, e1, Rel, ecs_typeid(Velocity), {
        .value = 20
    });      
    test_assert( ecs_has_pair(world, e1, ecs_typeid(Rel), ecs_typeid(Velocity)));

    ecs_entity_t e2 = ecs_new(world, 0);
    ecs_set_pair(world, e2, Rel, ecs_typeid(Position), {
        .value = 30
    });
    test_assert( ecs_has_pair(world, e2, ecs_typeid(Rel), ecs_typeid(Position)));

    ecs_set_pair(world, e2, Rel, ecs_typeid(Velocity), {
        .value = 40
    });
    test_assert( ecs_has_pair(world, e2, ecs_typeid(Rel), ecs_typeid(Position)));

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 0);

    const Rel* tr = ecs_get_pair(world, e1, Rel, ecs_typeid(Position));
    test_assert(tr != NULL);
    test_int(tr->value, 11);

    tr = ecs_get_pair(world, e1, Rel, ecs_typeid(Velocity));
    test_assert(tr != NULL);
    test_int(tr->value, 21);

    tr = ecs_get_pair(world, e2, Rel, ecs_typeid(Position));
    test_assert(tr != NULL);
    test_int(tr->value, 31);

    tr = ecs_get_pair(world, e2, Rel, ecs_typeid(Velocity));
    test_assert(tr != NULL);
    test_int(tr->value, 41); 

    test_int(ctx.count, 4);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, ProcessPairs);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e1);
    test_int(ctx.e[3], e2);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Velocity));

    c = ctx.c[1][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Position));

    test_int(ctx.s[0][0], 0);
    test_int(ctx.s[1][0], 0);
    test_int(ctx.s[2][0], 0);
    test_int(ctx.s[3][0], 0);

    ecs_fini(world);
}

void Pairs_add_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_SYSTEM(world, ProcessPairs, EcsOnUpdate, PAIR | Rel);

    ecs_entity_t e1 = ecs_new(world, 0);
    test_assert(e1 != 0);

    ecs_add_pair(world, e1, ecs_typeid(Rel), ecs_typeid(Position));
    test_assert( ecs_has_pair(world, e1, ecs_typeid(Rel), ecs_typeid(Position)));

    ecs_fini(world);
}

void Pairs_remove_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_SYSTEM(world, ProcessPairs, EcsOnUpdate, PAIR | Rel);

    ecs_entity_t e1 = ecs_set_pair(world, 0, Rel, ecs_typeid(Position), {
        .value = 10
    });  
    test_assert(e1 != 0);
    test_assert( ecs_has_pair(world, e1, ecs_typeid(Rel), ecs_typeid(Position)));

    ecs_remove_pair(world, e1, ecs_typeid(Rel), ecs_typeid(Position));
    test_assert( !ecs_has_pair(world, e1, ecs_typeid(Rel), ecs_typeid(Position)));

    ecs_fini(world);
}

void ProcessPairTags(ecs_iter_t *it) {
    probe_system(it);
}

void Pairs_add_tag_pair_for_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag1);
    ECS_TAG(world, Tag2);
    ECS_TAG(world, Rel);

    ECS_SYSTEM(world, ProcessPairTags, EcsOnUpdate, PAIR | Rel);

    /* Ensure that pair is matched against different components */
    ecs_entity_t e1 = ecs_new(world, 0);
    ecs_add_pair(world, e1, Rel, Tag1);
    test_assert(e1 != 0);
    test_assert( ecs_has_pair(world, e1, Rel, Tag1));

    ecs_entity_t e2 = ecs_new(world, 0);
    ecs_add_pair(world, e2, Rel, Tag2);
    test_assert(e2 != 0);
    test_assert( ecs_has_pair(world, e2, Rel, Tag2));

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 0);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, ProcessPairTags);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);

    ecs_entity_t c = ctx.c[0][0];

    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, Rel);
    test_int(lo, Tag1);

    c = ctx.c[1][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, Rel);
    test_int(lo, Tag2);

    test_int(ctx.s[0][0], 0);
    test_int(ctx.s[1][0], 0);

    ecs_fini(world);
}

void ProcessValuePairs(ecs_iter_t *it) {
    /* Strictly speaking this can be either Position or Velocity, but they have
     * the same layout. */
    Position *p = ecs_term(it, Position, 1);

    probe_system(it);

    if (p) {
        int32_t i;
        for (i = 0; i < it->count; i ++) {
            p[i].x += 10;
            p[i].y += 20;
        }
    }
}

void Pairs_add_tag_pair_for_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TAG(world, Rel);

    ECS_SYSTEM(world, ProcessValuePairs, EcsOnUpdate, PAIR | Rel);

    ecs_entity_t e1 = ecs_set_pair_object(world, 0, Rel, Position, {
        .x = 1,
        .y = 2
    });
    test_assert( ecs_has_pair(world, e1, Rel, ecs_typeid(Position)));

    ecs_entity_t e2 = ecs_set_pair_object(world, 0, Rel, Velocity, {
        .x = 3,
        .y = 4
    });
    test_assert( ecs_has_pair(world, e2, Rel, ecs_typeid(Velocity)));

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 0);

    const Position* tr_p = ecs_get_pair_object(world, e1, Rel, Position);
    test_assert(tr_p != NULL);
    test_int(tr_p->x, 11);
    test_int(tr_p->y, 22);

    const Velocity* tr_v = ecs_get_pair_object(world, e2, Rel, Velocity);
    test_assert(tr_v != NULL);
    test_int(tr_v->x, 13);
    test_int(tr_v->y, 24);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, ProcessValuePairs);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, Rel);
    test_int(lo, ecs_typeid(Position));

    c = ctx.c[1][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, Rel);
    test_int(lo, ecs_typeid(Velocity));

    test_int(ctx.s[0][0], 0);
    test_int(ctx.s[1][0], 0);

    ecs_fini(world);
}

void ProcessTwoPairs(ecs_iter_t *it) {
    RelA *tr_a = ecs_term(it, RelA, 1);
    RelB *tr_b = ecs_term(it, RelB, 2);

    probe_system(it);

    int32_t i;
    for (i = 0; i < it->count; i ++) {
        tr_a[i].value ++;
        tr_b[i].value ++;
    }
}

void Pairs_query_2_pairs() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, RelA);
    ECS_COMPONENT(world, RelB);

    ECS_SYSTEM(world, ProcessTwoPairs, EcsOnUpdate, PAIR | RelA, PAIR | RelB);

    /* Create entity with both RelA and RelB */
    ecs_entity_t e1 = ecs_set_pair(world, 0, RelA, ecs_typeid(Position), {
        .value = 1
    });

    ecs_set_pair(world, e1, RelB, ecs_typeid(Position), {
        .value = 2
    });

    test_assert( ecs_has_pair(world, e1, ecs_typeid(RelA), ecs_typeid(Position)));
    test_assert( ecs_has_pair(world, e1, ecs_typeid(RelB), ecs_typeid(Position)));

    /* Create entity with only RelA. Should not be matched with system */
    ecs_entity_t e2 = ecs_set_pair(world, 0, RelA, ecs_typeid(Position), {
        .value = 3
    });
    test_assert( ecs_has_pair(world, e2, ecs_typeid(RelA), ecs_typeid(Position)));

    /* Run system */
    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);
    ecs_progress(world, 0);

    const RelA *tr_a = ecs_get_pair(world, e1, RelA, ecs_typeid(Position));
    test_int(tr_a->value, 2);

    const RelB *tr_b = ecs_get_pair(world, e1, RelB, ecs_typeid(Position));
    test_int(tr_b->value, 3);

    tr_a = ecs_get_pair(world, e2, RelA, ecs_typeid(Position));
    test_int(tr_a->value, 3);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, ProcessTwoPairs);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(RelA));
    test_int(lo, ecs_typeid(Position));

    c = ctx.c[0][1];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(RelB));
    test_int(lo, ecs_typeid(Position));    

    ecs_fini(world);
}

void Pairs_query_2_pairs_2_instances_per_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, RelA);
    ECS_COMPONENT(world, RelB);

    ECS_SYSTEM(world, ProcessTwoPairs, EcsOnUpdate, PAIR | RelA, PAIR | RelB);

    /* Create entity with both RelA and RelB, applied to two components*/
    ecs_entity_t e1 = ecs_set_pair(world, 0, RelA, ecs_typeid(Position), {
        .value = 1
    });

    ecs_set_pair(world, e1, RelB, ecs_typeid(Position), {
        .value = 2
    });

    ecs_set_pair(world, e1, RelA, ecs_typeid(Velocity), {
        .value = 3
    });

    ecs_set_pair(world, e1, RelB, ecs_typeid(Velocity), {
        .value = 4
    });        

    test_assert( ecs_has_pair(world, e1, ecs_typeid(RelA), ecs_typeid(Position)));
    test_assert( ecs_has_pair(world, e1, ecs_typeid(RelB), ecs_typeid(Position)));
    test_assert( ecs_has_pair(world, e1, ecs_typeid(RelA), ecs_typeid(Velocity)));
    test_assert( ecs_has_pair(world, e1, ecs_typeid(RelB), ecs_typeid(Velocity)));

    /* Run system */
    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);
    ecs_progress(world, 0);

    const RelA *tr_a = ecs_get_pair(world, e1, RelA, ecs_typeid(Position));
    test_int(tr_a->value, 2);

    tr_a = ecs_get_pair(world, e1, RelA, ecs_typeid(Velocity));
    test_int(tr_a->value, 4);

    const RelB *tr_b = ecs_get_pair(world, e1, RelB, ecs_typeid(Position));
    test_int(tr_b->value, 3);

    tr_b = ecs_get_pair(world, e1, RelB, ecs_typeid(Velocity));
    test_int(tr_b->value, 5);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, ProcessTwoPairs);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e1);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(RelA));
    test_int(lo, ecs_typeid(Position));

    c = ctx.c[0][1];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(RelB));
    test_int(lo, ecs_typeid(Position));    

    c = ctx.c[1][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(RelA));
    test_int(lo, ecs_typeid(Velocity));

    c = ctx.c[1][1];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(RelB));
    test_int(lo, ecs_typeid(Velocity));  

    ecs_fini(world);
}

void Pairs_override_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Rel);

    ecs_entity_t base = ecs_new(world, 0);
    ecs_set_pair(world, base, Rel, ecs_typeid(Position), {.value = 10});

    ecs_entity_t instance = ecs_new_w_pair(world, EcsIsA, base);
    test_assert(ecs_has_pair(world, instance, ecs_typeid(Rel), ecs_typeid(Position)));

    const Rel *t = ecs_get_pair(world, instance, Rel, ecs_typeid(Position));
    test_assert(t != NULL);
    test_int(t->value, 10);

    const Rel *t_2 = ecs_get_pair(world, base, Rel, ecs_typeid(Position));
    test_assert(t_2 != NULL);
    test_assert(t == t_2);

    ecs_add_pair(world, instance, ecs_typeid(Rel), ecs_typeid(Position));
    t = ecs_get_pair(world, instance, Rel, ecs_typeid(Position));
    test_assert(t != NULL);
    test_int(t->value, 10);
    test_assert(t != t_2);

    ecs_fini(world);
}

void Pairs_override_tag_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Rel);

    ecs_entity_t base = ecs_new(world, 0);
    ecs_set_pair_object(world, base, Rel, Position, {.x = 10, .y = 20});

    ecs_entity_t instance = ecs_new_w_pair(world, EcsIsA, base);
    test_assert(ecs_has_pair(world, instance, Rel, ecs_typeid(Position)));

    const Position *t = ecs_get_pair_object(world, instance, Rel, Position);
    test_assert(t != NULL);
    test_int(t->x, 10);
    test_int(t->y, 20);

    const Position *t_2 = ecs_get_pair_object(world, base, Rel, Position);
    test_assert(t_2 != NULL);
    test_assert(t == t_2);

    ecs_add_pair(world, instance, Rel, ecs_typeid(Position));
    t = ecs_get_pair_object(world, instance, Rel, Position);
    test_assert(t != NULL);
    test_int(t->x, 10);
    test_int(t->y, 20);
    test_assert(t != t_2);

    ecs_fini(world);
}

void Pairs_pair_wildcard_system() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_SYSTEM(world, ProcessPairs, EcsOnUpdate, PAIR | Rel, PAIR | Rel > *);

    /* Ensure that pair is matched against different components */
    ecs_entity_t e1 = 
    ecs_set_pair(world, 0, Rel, ecs_typeid(Position), {
        .value = 10
    });
    ecs_add(world, e1, Position);

    ecs_entity_t e2 = 
    ecs_set_pair(world, 0, Rel, ecs_typeid(Velocity), {
        .value = 20
    });
    ecs_add(world, e2, Velocity);

    /* This entity should not be matched as it doesn't have Position */
    ecs_set_pair(world, 0, Rel, ecs_typeid(Position), {
        .value = 20
    });

    /* This entity should not be matched as it doesn't have the pair */
    ecs_set(world, 0, Position, { 10, 20 });

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 0);

    const Rel* tr = ecs_get_pair(world, e1, Rel, ecs_typeid(Position));
    test_assert(tr != NULL);
    test_int(tr->value, 11);

    tr = ecs_get_pair(world, e2, Rel, ecs_typeid(Velocity));
    test_assert(tr != NULL);
    test_int(tr->value, 21); 

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, ProcessPairs);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Position));
    test_int(ctx.c[0][1], ecs_typeid(Position));

    c = ctx.c[1][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Velocity));
    test_int(ctx.c[1][1], ecs_typeid(Velocity));

    test_int(ctx.s[0][0], 0);
    test_int(ctx.s[1][0], 0);

    ecs_fini(world);
}

static
void IterPairWildcard(ecs_iter_t *it) {
    probe_system(it);
}

void Pairs_pair_only_wildcard_system() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_SYSTEM(world, IterPairWildcard, EcsOnUpdate, PAIR | Rel > *);

    /* Ensure that pair is matched against different components */
    ecs_entity_t e1 = 
    ecs_set_pair(world, 0, Rel, ecs_typeid(Position), {
        .value = 10
    });
    ecs_add(world, e1, Position);

    ecs_entity_t e2 = 
    ecs_set_pair(world, 0, Rel, ecs_typeid(Velocity), {
        .value = 20
    });
    ecs_add(world, e2, Velocity);

    /* This entity should not be matched as it doesn't have Position */
    ecs_set_pair(world, 0, Rel, ecs_typeid(Position), {
        .value = 20
    });

    /* This entity should not be matched as it doesn't have the pair */
    ecs_set(world, 0, Position, { 10, 20 });

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx);

    ecs_progress(world, 0);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, IterPairWildcard);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.c[1][0], ecs_typeid(Velocity));

    test_int(ctx.s[0][0], 0);
    test_int(ctx.s[1][0], 0);

    ecs_fini(world);
}

static int set_pair_invoked = 0;

static
void SetPair(ecs_iter_t *it) {
    set_pair_invoked ++;
    probe_system(it);
}

void Pairs_pair_wildcard_on_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_SYSTEM(world, SetPair, EcsOnSet, PAIR | Rel > *);

    /* Ensure that pair is matched against different components */
    ecs_entity_t e1 = 
    ecs_set_pair(world, 0, Rel, ecs_typeid(Position), { .value = 10 });
    ecs_add(world, e1, Position);
    test_int(set_pair_invoked, 0);

    ecs_entity_t e2 = 
    ecs_set_pair(world, 0, Rel, ecs_typeid(Velocity), { .value = 20 });
    ecs_add(world, e2, Velocity);
    test_int(set_pair_invoked, 0);

    /* This entity should not trigger as it doesn't have the pair */
    ecs_set(world, 0, Position, { 10, 20 });
    test_int(set_pair_invoked, 0);

    /* Set Position on e1, should trigger OnSet */
    ecs_set(world, e1, Position, {10, 20});
    test_int(set_pair_invoked, 1);

    ecs_set(world, e2, Position, {10, 20});
    test_int(set_pair_invoked, 1);

    ecs_set(world, e2, Velocity, {10, 20});
    test_int(set_pair_invoked, 2);

    ecs_fini(world);
}

static
void PairTrigger(ecs_iter_t *it) {
    probe_system(it);
}

void Pairs_on_add_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_TRIGGER(world, PairTrigger, EcsOnAdd, (Rel, *));

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_add_pair(world, e, ecs_typeid(Rel), ecs_typeid(Position));

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, PairTrigger);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);
    test_int(ctx.e[0], e);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Position));  

    ctx = (Probe){ 0 };
    ecs_add_pair(world, e, ecs_typeid(Rel), ecs_typeid(Velocity));

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, PairTrigger);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);
    test_int(ctx.e[0], e);

    c = ctx.c[0][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Velocity));

    ecs_fini(world);
}

void Pairs_on_add_pair_tag() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Rel);

    ECS_TRIGGER(world, PairTrigger, EcsOnAdd, (Rel, Position));

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_add_pair(world, e, Rel, ecs_typeid(Position));

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, PairTrigger);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);
    test_int(ctx.e[0], e);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, Rel);
    test_int(lo, ecs_typeid(Position));  

    ecs_fini(world);
}

void Pairs_on_remove_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_TRIGGER(world, PairTrigger, EcsOnRemove, (Rel, *));

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_add_pair(world, e, ecs_typeid(Rel), ecs_typeid(Position));
    ecs_add_pair(world, e, ecs_typeid(Rel), ecs_typeid(Velocity));
    test_int(ctx.count, 0);

    ecs_remove_pair(world, e, ecs_typeid(Rel), ecs_typeid(Position));
    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, PairTrigger);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);
    test_int(ctx.e[0], e);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Position));  

    ctx = (Probe){ 0 };
    ecs_remove_pair(world, e, ecs_typeid(Rel), ecs_typeid(Velocity));
    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, PairTrigger);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);
    test_int(ctx.e[0], e);

    c = ctx.c[0][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Velocity));

    ecs_fini(world);
}

void Pairs_on_remove_pair_tag() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Rel);

    ECS_TRIGGER(world, PairTrigger, EcsOnRemove, (Rel, Position));

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_add_pair(world, e, Rel, ecs_typeid(Position));
    test_int(ctx.count, 0);

    ecs_remove_pair(world, e, Rel, ecs_typeid(Position));
    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, PairTrigger);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);
    test_int(ctx.e[0], e);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, Rel);
    test_int(lo, ecs_typeid(Position));  

    ecs_fini(world);
}

void Pairs_on_remove_pair_on_delete() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rel);

    ECS_TRIGGER(world, PairTrigger, EcsOnRemove, (Rel, *));

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_add_pair(world, e, ecs_typeid(Rel), ecs_typeid(Position));
    ecs_add_pair(world, e, ecs_typeid(Rel), ecs_typeid(Velocity));
    test_int(ctx.count, 0);

    ecs_delete(world, e);
    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, PairTrigger);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);
    test_int(ctx.e[0], e);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Position));  

    test_int(ctx.e[1], e);

    c = ctx.c[1][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, ecs_typeid(Rel));
    test_int(lo, ecs_typeid(Velocity));

    ecs_fini(world);
}

static
void PairTriggerPosition(ecs_iter_t *it) {
    PairTrigger(it);
}

static
void PairTriggerVelocity(ecs_iter_t *it) {
    PairTrigger(it);
}

void Pairs_on_remove_pair_tag_on_delete() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TAG(world, Rel);

    ECS_TRIGGER(world, PairTriggerPosition, EcsOnRemove, (Rel, Position));
    ECS_TRIGGER(world, PairTriggerVelocity, EcsOnRemove, (Rel, Velocity));

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_add_pair(world, e, Rel, ecs_typeid(Position));
    ecs_add_pair(world, e, Rel, ecs_typeid(Velocity));
    test_int(ctx.count, 0);

    ecs_delete(world, e);
    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, PairTriggerVelocity);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);
    test_int(ctx.e[0], e);

    ecs_entity_t c = ctx.c[0][0];
    ecs_entity_t hi = ECS_PAIR_RELATION(c);
    ecs_entity_t lo = ECS_PAIR_OBJECT(c);
    test_int(hi, Rel);
    test_int(lo, ecs_typeid(Position));  

    test_int(ctx.e[1], e);

    c = ctx.c[1][0];
    hi = ECS_PAIR_RELATION(c);
    lo = ECS_PAIR_OBJECT(c);
    test_int(hi, Rel);
    test_int(lo, ecs_typeid(Velocity));

    ecs_fini(world);
}

void Pairs_pair_from_shared() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Rel);

    ecs_entity_t base = ecs_new(world, 0);
    ecs_add_pair(world, base, ecs_typeid(Rel), ecs_typeid(Position));

    ecs_entity_t e = ecs_new(world, 0);
    ecs_add_pair(world, e, EcsIsA, base);

    ecs_query_t *q = ecs_query_new(world, "SHARED:PAIR|Rel>Position"); // ew
    
    int32_t count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        Rel *t = ecs_term(&it, Rel, 1);
        test_assert(t != NULL);

        int i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] == e);
        }
        count += it.count;
    }

    test_assert(count == 1);

    ecs_fini(world);
}

void Pairs_simple_pair_syntax() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Rel);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_add_pair(world, e, ecs_typeid(Rel), ecs_typeid(Position));

    ecs_query_t *q = ecs_query_new(world, "Rel FOR Position"); // not ew
    
    int32_t count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        int i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] == e);
        }
        count += it.count;
    }

    test_assert(count == 1);

    ecs_fini(world);
}

void Pairs_pair_w_component_query() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Rel);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_add_pair(world, e, ecs_typeid(Rel), ecs_typeid(Position));

    ecs_query_t *q = ecs_query_new(world, "PAIR | Rel > Position");
    
    int32_t count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        Rel *t = ecs_term(&it, Rel, 1);
        test_assert(t != NULL);

        int i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] == e);
        }
        count += it.count;
    }

    test_assert(count == 1);

    ecs_fini(world);
}

void Pairs_query_pair_or_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Rel);

    ecs_entity_t e1 = ecs_new(world, 0);
    ecs_add_pair(world, e1, Rel, ecs_typeid(Position));
    ecs_entity_t e2 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "PAIR | Rel > Position || Position");
    
    int32_t count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        Position *t = ecs_term(&it, Position, 1);
        test_assert(t != NULL);

        int i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] == e1 || it.entities[i] == e2);
        }
        count += it.count;
    }

    test_assert(count == 2);

    ecs_fini(world);
}

void Pairs_query_pair_or_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t e1 = ecs_new(world, 0);
    ecs_add_pair(world, e1, RelA, ecs_typeid(Position));
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add_pair(world, e2, RelB, ecs_typeid(Position));

    ecs_query_t *q = ecs_query_new(world, "PAIR | RelA > Position || PAIR | RelB > Position");
    
    int32_t count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        Position *t = ecs_term(&it, Position, 1);
        test_assert(t != NULL);

        int i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] == e1 || it.entities[i] == e2);
        }
        count += it.count;
    }

    test_int(count, 2);

    ecs_fini(world);
}

void Pairs_query_not_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Rel);

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add_pair(world, e2, Rel, ecs_typeid(Position));

    ecs_query_t *q = ecs_query_new(world, "!PAIR | Rel > Position, Position");
    
    int32_t count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        Position *t = ecs_term(&it, Position, 1);
        test_assert(t == NULL);
        Position *p = ecs_term(&it, Position, 2);
        test_assert(p != NULL);

        int i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] == e1);
        }
        count += it.count;
    }

    test_assert(count == 1);

    ecs_fini(world);
}

void Pairs_get_typeid_w_recycled_rel() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t o = ecs_new_id(world);
    test_assert(o != 0);

    ecs_entity_t dummy = ecs_new_id(world);
    ecs_delete(world, dummy); // force recycle

    // don't use ECS_COMPONENT, because it will try to get low ids first
    ecs_entity_t pos = ecs_set(world, 0, EcsComponent, {4});
    test_assert(pos != 0);
    test_assert((uint32_t)pos != pos); // ensure recycled

    ecs_id_t pair = ecs_pair(pos, o);
    ecs_entity_t tid = ecs_get_typeid(world, pair);
    test_assert(tid != 0);
    test_assert(tid == pos);

    ecs_fini(world);
}

void Pairs_get_typeid_w_recycled_obj() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t r = ecs_new_id(world);
    test_assert(r != 0);

    ecs_entity_t dummy = ecs_new_id(world);
    ecs_delete(world, dummy); // force recycle

    // don't use ECS_COMPONENT, because it will try to get low ids first
    ecs_entity_t pos = ecs_set(world, 0, EcsComponent, {4});
    test_assert(pos != 0);
    test_assert((uint32_t)pos != pos); // ensure recycled

    ecs_id_t pair = ecs_pair(r, pos);
    ecs_entity_t tid = ecs_get_typeid(world, pair);
    test_assert(tid != 0);
    test_assert(tid == pos);

    ecs_fini(world);
}

void Pairs_id_str_w_recycled_rel() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t o = ecs_set(world, 0, EcsName, {"o"});
    test_assert(o != 0);

    ecs_entity_t dummy = ecs_new_id(world);
    ecs_delete(world, dummy); // force recycle

    ecs_entity_t r = ecs_set(world, 0, EcsName, {"r"});
    test_assert(r != 0);
    test_assert((uint32_t)r != r); // ensure recycled

    ecs_id_t pair = ecs_pair(r, o);
    char buff[64];
    ecs_id_str(world, pair, buff, sizeof(buff));

    test_str(buff, "(r,o)");

    ecs_fini(world);
}

void Pairs_id_str_w_recycled_obj() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t r = ecs_set(world, 0, EcsName, {"r"});
    test_assert(r != 0);

    ecs_entity_t dummy = ecs_new_id(world);
    ecs_delete(world, dummy); // force recycle

    ecs_entity_t o = ecs_set(world, 0, EcsName, {"o"});
    test_assert(o != 0);
    test_assert((uint32_t)o != o); // ensure recycled

    ecs_id_t pair = ecs_pair(r, o);
    char buff[64];
    ecs_id_str(world, pair, buff, sizeof(buff));

    test_str(buff, "(r,o)");

    ecs_fini(world);
}

void Pairs_set_object_w_zero_sized_rel_comp() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t r = ecs_set(world, 0, EcsComponent, {0});

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_set_pair_object(world, 0, r, Position, {10, 20});
    
    const Position *p = ecs_get_pair_object(world, e, r, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void Pairs_dsl_pair() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.expr = "(Rel, Obj)"
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2)} });
    test_assert(e4 != 0);

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_dsl_pair_w_pred_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.expr = "(*, Obj)"
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2)} });
    test_assert(e4 != 0);    

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_dsl_pair_w_obj_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.expr = "(Rel_2, *)"
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2)} });
    test_assert(e4 != 0);    

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj_2));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_dsl_pair_w_both_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.expr = "(*, *), Tag" // add Tag or we'd match builtin entities
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj), Tag} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2), Tag} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj), Tag} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2), Tag} });
    test_assert(e4 != 0);    

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e2);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj_2));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj_2));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_dsl_pair_w_explicit_subj_this() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.expr = "Rel(This, Obj)"
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2)} });
    test_assert(e4 != 0);

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_dsl_pair_w_explicit_subj() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ECS_TAG(world, Tag);

    ecs_entity_t Subj = ecs_entity_init(world, &(ecs_entity_desc_t){
        .name = "Subj", .add = {ecs_pair(Rel, Obj)} });
    test_assert(Subj != 0);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.expr = "Rel(Subj, Obj), Tag"
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2), Tag} });
    test_assert(e4 != 0);

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));
    test_int(ecs_term_subject(&it, 1), Subj);

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_api_pair() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {{ecs_pair(Rel, Obj)}}
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2)} });
    test_assert(e4 != 0);

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_api_pair_w_pred_wildcard() {
   ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {{ecs_pair(EcsWildcard, Obj)}}
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2)} });
    test_assert(e4 != 0);    

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_api_pair_w_obj_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {{ecs_pair(Rel_2, EcsWildcard)}}
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2)} });
    test_assert(e4 != 0);    

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj_2));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_api_pair_w_both_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        // add Tag or we'd match builtin entities
        .filter.terms = {{ecs_pair(EcsWildcard, EcsWildcard)}, {Tag}} 
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj), Tag} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2), Tag} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj), Tag} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2), Tag} });
    test_assert(e4 != 0);    

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e2);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj_2));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel_2, Obj_2));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_api_pair_w_explicit_subj_this() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {{ecs_pair(Rel, Obj), .args[0].entity = EcsThis}}
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2)} });
    test_assert(e4 != 0);

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_api_pair_w_explicit_subj() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Rel_2);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Obj_2);

    ECS_TAG(world, Tag);

    ecs_entity_t Subj = ecs_entity_init(world, &(ecs_entity_desc_t){
        .name = "Subj", .add = {ecs_pair(Rel, Obj)} });
    test_assert(Subj != 0);

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {{ecs_pair(Rel, Obj), .args[0].entity = Subj}, {Tag}}
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj)} });
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel, Obj_2)} });
    test_assert(e2 != 0);

    ecs_entity_t e3 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj)} });
    test_assert(e3 != 0);

    ecs_entity_t e4 = ecs_entity_init(world, &(ecs_entity_desc_t){
        .add = {ecs_pair(Rel_2, Obj_2), Tag} });
    test_assert(e4 != 0);

    ecs_iter_t it = ecs_query_iter(q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_int(ecs_term_id(&it, 1), ecs_pair(Rel, Obj));
    test_int(ecs_term_subject(&it, 1), Subj);

    test_bool(ecs_query_next(&it), false); 

    ecs_fini(world);
}

void Pairs_typeid_from_tag() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t tag = ecs_new_id(world);
    test_assert(tag != 0);

    ecs_entity_t id = ecs_get_typeid(world, tag);
    test_assert(id != 0);
    test_assert(id == tag);

    ecs_fini(world);
}

void Pairs_typeid_from_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Rel);
    ecs_id_t rel_id = ecs_id(Rel);
    test_assert(rel_id != 0);

    ecs_entity_t id = ecs_get_typeid(world, rel_id);
    test_assert(id != 0);
    test_assert(id == rel_id);

    ecs_fini(world);
}

void Pairs_typeid_from_pair() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t rel_id = ecs_new_id(world);
    test_assert(rel_id != 0);

    ecs_entity_t obj_id = ecs_new_id(world);
    test_assert(obj_id != 0);

    ecs_id_t pair_id = ecs_pair(rel_id, obj_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id == 0);

    ecs_fini(world);
}

void Pairs_typeid_from_pair_w_rel_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Rel);
    ecs_id_t rel_id = ecs_id(Rel);
    test_assert(rel_id != 0);

    ecs_entity_t obj_id = ecs_new_id(world);
    test_assert(obj_id != 0);

    ecs_id_t pair_id = ecs_pair(rel_id, obj_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id != 0);
    test_assert(id == rel_id);

    ecs_fini(world);
}

void Pairs_typeid_from_pair_w_obj_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Obj);
    ecs_id_t obj_id = ecs_id(Obj);
    test_assert(obj_id != 0);

    ecs_entity_t rel_id = ecs_new_id(world);
    test_assert(rel_id != 0);

    ecs_id_t pair_id = ecs_pair(rel_id, obj_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id != 0);
    test_assert(id == obj_id);

    ecs_fini(world);
}

void Pairs_typeid_from_pair_w_rel_obj_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Rel);
    ecs_id_t rel_id = ecs_id(Rel);
    test_assert(rel_id != 0);

    ECS_COMPONENT(world, Obj);
    ecs_id_t obj_id = ecs_id(Obj);
    test_assert(obj_id != 0);

    ecs_id_t pair_id = ecs_pair(rel_id, obj_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id != 0);
    test_assert(id == rel_id);

    ecs_fini(world);
}

void Pairs_typeid_from_pair_w_rel_0_obj_type() {
    ecs_world_t *world = ecs_init();

    ecs_id_t rel_id = ecs_set(world, 0, EcsComponent, {0});
    test_assert(rel_id != 0);

    ECS_COMPONENT(world, Obj);
    ecs_id_t obj_id = ecs_id(Obj);
    test_assert(obj_id != 0);

    ecs_id_t pair_id = ecs_pair(rel_id, obj_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id != 0);
    test_assert(id == obj_id);

    ecs_fini(world);
}

void Pairs_typeid_from_pair_w_rel_obj_0_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Rel);
    ecs_id_t rel_id = ecs_id(Rel);
    test_assert(rel_id != 0);

    ecs_id_t obj_id = ecs_set(world, 0, EcsComponent, {0});
    test_assert(obj_id != 0);

    ecs_id_t pair_id = ecs_pair(rel_id, obj_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id != 0);
    test_assert(id == rel_id);

    ecs_fini(world);
}

void Pairs_typeid_from_pair_w_rel_0_obj_0_type() {
    ecs_world_t *world = ecs_init();

    ecs_id_t rel_id = ecs_set(world, 0, EcsComponent, {0});
    test_assert(rel_id != 0);

    ecs_id_t obj_id = ecs_set(world, 0, EcsComponent, {0});
    test_assert(obj_id != 0);

    ecs_id_t pair_id = ecs_pair(rel_id, obj_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id == 0);

    ecs_fini(world);
}

void Pairs_tag_pair_w_rel_comp() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Obj);

    ecs_add_id(world, ecs_id(Position), EcsTag);

    ecs_entity_t e = ecs_new_id(world);
    ecs_id_t pair_id = ecs_pair(ecs_id(Position), Obj);

    ecs_add_id(world, e, pair_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id == 0);

    ecs_fini(world);
}

void Pairs_tag_pair_w_obj_comp() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_COMPONENT(world, Position);

    ecs_add_id(world, Rel, EcsTag);

    ecs_entity_t e = ecs_new_id(world);
    ecs_id_t pair_id = ecs_pair(Rel, ecs_id(Position));

    ecs_add_id(world, e, pair_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id == 0);

    ecs_fini(world);
}

void Pairs_tag_pair_w_rel_obj_comp() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_id(world, ecs_id(Position), EcsTag);

    ecs_entity_t e = ecs_new_id(world);
    ecs_id_t pair_id = ecs_pair(ecs_id(Position), ecs_id(Velocity));

    ecs_add_id(world, e, pair_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id == 0);

    ecs_fini(world);
}

void Pairs_get_tag_pair_w_rel_comp() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Obj);

    ecs_add_id(world, ecs_id(Position), EcsTag);

    ecs_entity_t e = ecs_new_id(world);
    ecs_id_t pair_id = ecs_pair(ecs_id(Position), Obj);

    ecs_add_id(world, e, pair_id);

    test_expect_abort();
    ecs_get_id(world, e, pair_id);
}

void Pairs_get_tag_pair_w_obj_comp() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_id(world, ecs_id(Position), EcsTag);

    ecs_entity_t e = ecs_new_id(world);
    ecs_id_t pair_id = ecs_pair(ecs_id(Position), ecs_id(Velocity));

    ecs_add_id(world, e, pair_id);

    test_expect_abort();
    ecs_get_id(world, e, pair_id);
}

void Pairs_get_tag_pair_w_rel_obj_comp() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_id(world, ecs_id(Position), EcsTag);

    ecs_entity_t e = ecs_new_id(world);
    ecs_id_t pair_id = ecs_pair(ecs_id(Position), ecs_id(Velocity));

    ecs_add_id(world, e, pair_id);

    test_expect_abort();
    ecs_get_id(world, e, pair_id);
}

void Pairs_tag_pair_w_childof_w_comp() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);
    ecs_id_t pair_id = ecs_pair(EcsChildOf, ecs_id(Position));

    ecs_add_id(world, e, pair_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id == 0);

    ecs_fini(world);
}

void Pairs_tag_pair_w_isa_w_comp() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);
    ecs_id_t pair_id = ecs_pair(EcsIsA, ecs_id(Position));

    ecs_add_id(world, e, pair_id);

    ecs_entity_t id = ecs_get_typeid(world, pair_id);
    test_assert(id == 0);

    ecs_fini(world);
}
