#include <api.h>

void Get_component_setup() {
    ecs_tracing_enable(-3);
}

void Get_component_get_empty() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);

    test_assert(ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 0) == 0);
    
    ecs_fini(world);
}

void Get_component_get_1_from_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    test_assert(*ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 0) == ecs_typeid(Position));
    
    ecs_fini(world);
}

void Get_component_get_1_from_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_new(world, Type);
    test_assert(e != 0);

    test_assert(*ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 0) == ecs_typeid(Position));
    
    ecs_fini(world);
}

void Get_component_get_2_from_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_new(world, Type);
    test_assert(e != 0);

    test_assert(*ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 1) == ecs_typeid(Velocity));
    
    ecs_fini(world);
}

void Get_component_get_2_from_3() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, Type, Position, Velocity, Mass);

    ecs_entity_t e = ecs_new(world, Type);
    test_assert(e != 0);

    test_assert(*ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 1) == ecs_typeid(Velocity));
    
    ecs_fini(world);
}

static
void Test_main_stage(ecs_iter_t *it) {
    ECS_COLUMN_COMPONENT(it, Position, 1);

    for (int i = 0; i < it->count; i ++) {
        ecs_entity_t e = it->entities[i];
        test_assert(*ecs_vector_get(ecs_get_type(it->world, e), ecs_entity_t, 0) == ecs_typeid(Position));
    }
}

void Get_component_get_1_from_2_in_progress_from_main_stage() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    ECS_SYSTEM(world, Test_main_stage, EcsOnUpdate, Position);

    ecs_progress(world, 1);
    
    ecs_fini(world);
}

static
void Add_in_progress(ecs_iter_t *it) {
    ECS_COLUMN_COMPONENT(it, Position, 1);

    ecs_type_t ecs_type(Velocity) = NULL;

    if (it->term_count >= 2) {
        ecs_type(Velocity) = ecs_column_type(it, 2);
    }

    for (int i = 0; i < it->count; i ++) {
        ecs_entity_t e = it->entities[i];
        ecs_add(it->world, e, Velocity);
    }
}

void Get_component_get_1_from_2_add_in_progress() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    ECS_SYSTEM(world, Add_in_progress, EcsOnUpdate, Position, :Velocity);

    ecs_progress(world, 1);
    test_assert( ecs_has(world, e, Velocity));
    test_assert(*ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 1) == ecs_typeid(Velocity));

    ecs_fini(world);
}

static
void Add_in_progress_test_main(ecs_iter_t *it) {
    ECS_COLUMN_COMPONENT(it, Position, 1);
    ECS_COLUMN_COMPONENT(it, Velocity, 2);

    for (int i = 0; i < it->count; i ++) {
        ecs_entity_t e = it->entities[i];
        test_assert(*ecs_vector_get(ecs_get_type(it->world, e), ecs_entity_t, 0) == ecs_typeid(Position));
        ecs_add(it->world, e, Velocity);
    }
}

void Get_component_get_both_from_2_add_in_progress() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    ECS_SYSTEM(world, Add_in_progress_test_main, EcsOnUpdate, Position, :Velocity);

    ecs_progress(world, 1);
    
    test_assert( ecs_has(world, e, Velocity));
    test_assert(*ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 0) == ecs_typeid(Position));
    test_assert(*ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 1) == ecs_typeid(Velocity));

    ecs_fini(world);
}

static
void Add_remove_in_progress_test_main(ecs_iter_t *it) {
    ECS_COLUMN_COMPONENT(it, Position, 1);
    ECS_COLUMN_COMPONENT(it, Velocity, 2);

    for (int i = 0; i < it->count; i ++) {
        ecs_entity_t e = it->entities[i];
        test_assert(*ecs_vector_get(ecs_get_type(it->world, e), ecs_entity_t, 0) == ecs_typeid(Position));        
        ecs_add(it->world, e, Velocity);
        ecs_remove(it->world, e, Position);
    }
}

void Get_component_get_both_from_2_add_remove_in_progress() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, Position);
    test_assert(e != 0);

    ECS_SYSTEM(world, Add_remove_in_progress_test_main, EcsOnUpdate, Position, :Velocity);

    ecs_progress(world, 1);
    
    test_assert( !ecs_has(world, e, Position));
    test_assert( ecs_has(world, e, Velocity));

    test_assert(*ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 0) == ecs_typeid(Velocity));
    test_assert(ecs_vector_get(ecs_get_type(world, e), ecs_entity_t, 1) == 0);

    ecs_fini(world);
}

void Get_component_get_childof_component() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    const EcsComponent *ptr = ecs_get(world, ecs_typeid(Position), EcsComponent);
    test_assert(ptr != NULL);

    test_expect_abort();
    ecs_get(world, ECS_CHILDOF | ecs_typeid(Position), EcsComponent);
}
