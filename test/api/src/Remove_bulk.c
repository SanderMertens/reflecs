#include <api.h>

void Remove_bulk_remove_comp_from_comp_to_empty() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    const ecs_entity_t *ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Position));
        test_assert( ecs_has(world, ids[i], Velocity));
        ecs_set(world, ids[i], Position, {i, i * 2});
    }

    ecs_bulk_remove(world, Velocity, &(ecs_filter_t){
        .include = ecs_type(Position)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Position));
        test_assert( !ecs_has(world, ids[i], Velocity));

        const Position *p = ecs_get(world, ids[i], Position);
        test_assert(p != NULL);
        test_int(p->x, i);
        test_int(p->y, i * 2);
    }

    test_int( ecs_count(world, Position), 10);
    test_int( ecs_count(world, Velocity), 0);

    ecs_fini(world);
}

void Remove_bulk_remove_comp_from_comp_to_existing() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t existing[10];
    const ecs_entity_t *ids = ecs_bulk_new(world, Position, 10);
    test_assert(ids != NULL);
    memcpy(existing, ids, sizeof(ecs_entity_t) * 10);

    ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, existing[i], Position));
        ecs_set(world, existing[i], Position, {i * 3, i * 4});
    }   

    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Position));
        test_assert( ecs_has(world, ids[i], Velocity));
        ecs_set(world, ids[i], Position, {i, i * 2});
    }

    ecs_bulk_remove(world, Velocity, &(ecs_filter_t){
        .include = ecs_type(Position)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Position));
        test_assert( !ecs_has(world, ids[i], Velocity));

        const Position *p = ecs_get(world, ids[i], Position);
        test_assert(p != NULL);
        test_int(p->x, i);
        test_int(p->y, i * 2);
    }

    test_int( ecs_count(world, Position), 20);
    test_int( ecs_count(world, Velocity), 0);

    ecs_fini(world);
}

void Remove_bulk_remove_comp_from_tag_to_empty() {
    ecs_world_t *world = ecs_init();
    
    ECS_TAG(world, Tag);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Tag, Velocity);

    const ecs_entity_t *ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Tag));
        test_assert( ecs_has(world, ids[i], Velocity));
    }

    ecs_bulk_remove(world, Velocity, &(ecs_filter_t){
        .include = ecs_type(Tag)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Tag));
        test_assert( !ecs_has(world, ids[i], Velocity));
    }

    test_int( ecs_count(world, Tag), 10);
    test_int( ecs_count(world, Velocity), 0);

    ecs_fini(world);
}

void Remove_bulk_remove_comp_from_tag_to_existing() {
    ecs_world_t *world = ecs_init();
    
    ECS_TAG(world, Tag);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Tag, Velocity);

    ecs_entity_t existing[10];
    const ecs_entity_t *ids = ecs_bulk_new(world, Tag, 10);
    test_assert(ids != NULL);
    memcpy(existing, ids, sizeof(ecs_entity_t) * 10);

    ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != 0);

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Tag));
        test_assert( ecs_has(world, ids[i], Velocity));
    }

    ecs_bulk_remove(world, Velocity, &(ecs_filter_t){
        .include = ecs_type(Tag)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Tag));
        test_assert( !ecs_has(world, ids[i], Velocity));
    }

    test_int( ecs_count(world, Tag), 20);
    test_int( ecs_count(world, Velocity), 0);

    ecs_fini(world);
}

void Remove_bulk_remove_tag_from_tag_to_empty() {
    ecs_world_t *world = ecs_init();
    
    ECS_TAG(world, Tag);
    ECS_TAG(world, Tag2);
    ECS_TYPE(world, Type, Tag, Tag2);

    const ecs_entity_t *ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Tag));
        test_assert( ecs_has(world, ids[i], Tag2));
    }

    ecs_bulk_remove(world, Tag2, &(ecs_filter_t){
        .include = ecs_type(Tag)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Tag));
        test_assert( !ecs_has(world, ids[i], Tag2));
    }

    test_int( ecs_count(world, Tag), 10);
    test_int( ecs_count(world, Tag2), 0);

    ecs_fini(world);
}

void Remove_bulk_remove_tag_from_tag_to_existing() {
    ecs_world_t *world = ecs_init();
    
    ECS_TAG(world, Tag);
    ECS_TAG(world, Tag2);
    ECS_TYPE(world, Type, Tag, Tag2);

    ecs_entity_t existing[10];
    const ecs_entity_t *ids = ecs_bulk_new(world, Tag, 10);
    test_assert(ids != NULL);
    memcpy(existing, ids, sizeof(ecs_entity_t) * 10);

    ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Tag));
        test_assert( ecs_has(world, ids[i], Tag2));
    }

    ecs_bulk_remove(world, Tag2, &(ecs_filter_t){
        .include = ecs_type(Tag)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Tag));
        test_assert( !ecs_has(world, ids[i], Tag2));
    }

    test_int( ecs_count(world, Tag), 20);
    test_int( ecs_count(world, Tag2), 0);

    ecs_fini(world);
}

void Remove_bulk_remove_all_comp() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);

    const ecs_entity_t *tmp_ids = ecs_bulk_new(world, Position, 10);
    test_assert(tmp_ids != NULL);

    ecs_entity_t ids[10];
    memcpy(ids, tmp_ids, sizeof(ids));

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Position));
    }

    ecs_bulk_remove(world, Position, &(ecs_filter_t){
        .include = ecs_type(Position)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( !ecs_has(world, ids[i], Position));
    }

    test_int( ecs_count(world, Position), 0);

    ecs_fini(world);
}

void Remove_bulk_remove_all_tag() {
    ecs_world_t *world = ecs_init();
    
    ECS_TAG(world, Tag);

    const ecs_entity_t *ids = ecs_bulk_new(world, Tag, 10);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Tag));
    }

    ecs_bulk_remove(world, Tag, &(ecs_filter_t){
        .include = ecs_type(Tag)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( !ecs_has(world, ids[i], Tag));
    }

    test_int( ecs_count(world, Tag), 0);

    ecs_fini(world);
}

void RemoveVelocity(ecs_iter_t *it) {
    probe_system(it);
}

void Remove_bulk_on_remove() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ECS_TRIGGER(world, RemoveVelocity, EcsOnRemove, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    const ecs_entity_t *ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != NULL);

    ecs_bulk_remove(world, Velocity, &(ecs_filter_t){
        .include = ecs_type(Position)
    });

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 10);
    test_int(ctx.system, RemoveVelocity);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    int i;
    for (i = 0; i < 10; i ++) {
        test_int(ctx.e[i], ids[i]);
    }

    test_int(ctx.c[0][0], ecs_typeid(Velocity));

    ecs_fini(world);
}

void Remove_bulk_remove_entity_comp() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    const ecs_entity_t *ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Position));
        test_assert( ecs_has(world, ids[i], Velocity));
        ecs_set(world, ids[i], Position, {i, i * 2});
    }

    ecs_bulk_remove_entity(world, ecs_typeid(Velocity), &(ecs_filter_t){
        .include = ecs_type(Position)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Position));
        test_assert( !ecs_has(world, ids[i], Velocity));

        const Position *p = ecs_get(world, ids[i], Position);
        test_assert(p != NULL);
        test_int(p->x, i);
        test_int(p->y, i * 2);
    }

    test_int( ecs_count(world, Position), 10);
    test_int( ecs_count(world, Velocity), 0);

    ecs_fini(world);
}

void Remove_bulk_remove_entity_tag() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Tag);
    ECS_TYPE(world, Type, Position, Tag);

    const ecs_entity_t *ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Position));
        test_assert( ecs_has_entity(world, ids[i], Tag));
        ecs_set(world, ids[i], Position, {i, i * 2});
    }

    ecs_bulk_remove_entity(world, Tag, &(ecs_filter_t){
        .include = ecs_type(Position)
    });

    for (i = 0; i < 10; i ++) {
        test_assert( ecs_has(world, ids[i], Position));
        test_assert( !ecs_has_entity(world, ids[i], Tag));

        const Position *p = ecs_get(world, ids[i], Position);
        test_assert(p != NULL);
        test_int(p->x, i);
        test_int(p->y, i * 2);
    }

    test_int( ecs_count(world, Position), 10);
    test_int( ecs_count_entity(world, Tag), 0);

    ecs_fini(world);
}

void Remove_bulk_remove_entity_on_remove() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ECS_TRIGGER(world, RemoveVelocity, EcsOnRemove, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    const ecs_entity_t *ids = ecs_bulk_new(world, Type, 10);
    test_assert(ids != NULL);

    ecs_bulk_remove_entity(world, ecs_typeid(Velocity), &(ecs_filter_t){
        .include = ecs_type(Position)
    });

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 10);
    test_int(ctx.system, RemoveVelocity);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    int i;
    for (i = 0; i < 10; i ++) {
        test_int(ctx.e[i], ids[i]);
    }

    test_int(ctx.c[0][0], ecs_typeid(Velocity));

    ecs_fini(world);
}
