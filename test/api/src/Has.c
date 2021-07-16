#include <api.h>
#include <flecs/type.h>

void Has_zero() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);

    test_assert(ecs_has(world, e, 0));
    
    ecs_fini(world);
}

void Has_zero_from_nonzero() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    test_assert(ecs_has(world, e, 0));
    
    ecs_fini(world);
}

void Has_1_of_0() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);

    test_assert(!ecs_has(world, e, Position));
    
    ecs_fini(world);
}

void Has_2_of_0() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);

    test_assert(!ecs_has(world, e, Type));
    
    ecs_fini(world);
}


void Has_1_of_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    test_assert(ecs_has(world, e, Position));
    
    ecs_fini(world);
}

void Has_1_of_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_new(world, Type);
    test_assert(e != 0);

    test_assert(ecs_has(world, e, Position));
    test_assert(ecs_has(world, e, Velocity));
    
    ecs_fini(world);
}

void Has_2_of_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_new(world, Type);
    test_assert(e != 0);

    test_assert(ecs_has(world, e, Type));
    
    ecs_fini(world);
}

void Has_3_of_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, Type_1, Position, Velocity);
    ECS_TYPE(world, Type_2, Position, Velocity, Mass);

    ecs_entity_t e = ecs_new(world, Type_1);
    test_assert(e != 0);

    test_assert(!ecs_has(world, e, Type_2));
    
    ecs_fini(world);
}

void Has_2_of_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    test_assert(!ecs_has(world, e, Type));
    
    ecs_fini(world);
}

void Has_1_of_empty() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);

    test_assert(!ecs_has(world, e, Position));
    
    ecs_fini(world);
}

void TestHas(ecs_iter_t *it) {
    ecs_type_t ecs_type(Position) = ecs_column_type(it, 1);

    int i;
    for (i = 0; i < it->count; i ++) {
        test_assert( ecs_has(it->world, it->entities[i], Position));
    }
}

void Has_has_in_progress() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, TestHas, EcsOnUpdate, Position);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);
    test_assert( ecs_has(world, e, Position));

    ecs_progress(world, 1);
    
    ecs_fini(world);
}

void Has_has_of_zero() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    test_expect_abort();

    ecs_has(world, 0, 0);
}

void Has_owns() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, Position);    
    test_assert(e != 0);
    test_assert( ecs_has(world, e, Position));
    test_assert( ecs_owns(world, e, Position, true));

    ecs_entity_t base = ecs_new(world, Velocity);
    test_assert( ecs_has(world, base, Velocity));
    test_assert( ecs_owns(world, base, Velocity, true));

    ecs_add_pair(world, e, EcsIsA, base);
    test_assert( ecs_has(world, e, Velocity));
    test_assert( !ecs_owns(world, e, Velocity, true));
 
    ecs_fini(world);
}

void Has_has_entity() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);

    ecs_entity_t base = ecs_new(world, 0);
    test_assert(base != 0);

    ecs_add_pair(world, e, EcsIsA, base);
    test_assert( !ecs_has_entity(world, e, base));
    test_assert( ecs_has_pair(world, e, EcsIsA, base));
 
    ecs_fini(world);
}

void Has_has_entity_0() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ecs_entity_t base = ecs_new(world, 0);
    test_assert(base != 0);

    test_expect_abort();

    ecs_has_entity(world, 0, base);
}

void Has_has_entity_0_component() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);

    test_assert( !ecs_has_entity(world, e, 0));
 
    ecs_fini(world);
}

void Has_has_entity_owned() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);
    
    ecs_entity_t f = ecs_new(world, 0);
    test_assert(f != 0);

    ecs_entity_t g = ecs_new(world, 0);
    test_assert(g != 0);

    ecs_entity_t base = ecs_new(world, 0);
    test_assert(base != 0);

    ecs_add_id(world, e, f);
    ecs_add_id(world, base, g);
    ecs_add_pair(world, e, EcsIsA, base);

    test_assert( ecs_has_entity(world, e, f));
    test_assert( ecs_has_entity(world, e, g));
    test_assert( !ecs_has_entity(world, e, base));
    test_assert( ecs_has_pair(world, e, EcsIsA, base));
    test_assert( ecs_owns_entity(world, e, f, true));
    test_assert( !ecs_owns_entity(world, e, g, true));
    test_assert( !ecs_owns_entity(world, e, base, true));

    test_assert( ecs_owns_entity(world, e, ecs_pair(EcsIsA, base), true));
 
    ecs_fini(world);
}

void Has_has_entity_owned_0() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);

    test_expect_abort();
    ecs_owns_entity(world, 0, e, true);
}

void Has_has_entity_owned_0_component() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);

    test_assert( ecs_owns_entity(world, e, 0, true) == false);

    ecs_fini(world);
}

void Has_has_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag_1);
    ECS_TAG(world, Tag_2);

    ecs_entity_t e1 = ecs_new_id(world);
    test_assert(e1 != 0);

    ecs_entity_t e2 = ecs_new_id(world);
    test_assert(e2 != 0);    

    ecs_add_id(world, e1, Tag_1);

    test_bool(ecs_has_id(world, e1, Tag_1), true);
    test_bool(ecs_has_id(world, e1, Tag_2), false);
    test_bool(ecs_has_id(world, e1, EcsWildcard), true);
 
    test_bool(ecs_has_id(world, e2, Tag_1), false);
    test_bool(ecs_has_id(world, e2, Tag_2), false);
    test_bool(ecs_has_id(world, e2, EcsWildcard), false);

    ecs_fini(world);
}

void Has_has_wildcard_pair() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Obj_1);
    ECS_TAG(world, Obj_2);

    ecs_entity_t e = ecs_new_id(world);
    test_assert(e != 0);

    ecs_add_pair(world, e, Rel, Obj_1);

    test_bool(ecs_has_pair(world, e, Rel, Obj_1), true);
    test_bool(ecs_has_pair(world, e, Rel, Obj_2), false);
    test_bool(ecs_has_pair(world, e, Rel, EcsWildcard), true);
    test_bool(ecs_has_pair(world, e, EcsWildcard, Obj_1), true);
    test_bool(ecs_has_pair(world, e, EcsWildcard, Obj_2), false);
    test_bool(ecs_has_pair(world, e, EcsWildcard, EcsWildcard), true);
 
    ecs_fini(world);
}
