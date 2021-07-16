#include <api.h>

void Stresstests_setup() {
    bake_set_os_api();
    ecs_tracing_enable(-3);
}

static
void add_random(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_entity_t component)
{
    if (rand() % 2) {
        if (!entity) {
            entity = ecs_new_w_entity(world, component);
        } else {
            ecs_add_id(world, entity, component);
        }
    }    
}

static
void set_random(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_entity_t component,
    void *ptr,
    void *expect,
    int32_t size)
{
    if (rand() % 2) {
        ecs_set_ptr_w_entity(world, entity, component, size, ptr);
    }  
}

static
void Delete_above_1000(ecs_iter_t *it) {
    int i;

    for (i = 0; i < it->count; i ++) {
        if ((i + it->frame_offset) > 1000) {
            ecs_delete(it->world, it->entities[i]);
        }
    }
}

static
void Add_random(ecs_iter_t *it) {
    IterData *ctx = ecs_get_ctx(it->world);

    int i;
    for (i = 0; i < it->count; i ++) {
        add_random(it->world, 0, ctx->component);
        add_random(it->world, it->entities[i], ctx->component_2);
        add_random(it->world, it->entities[i], ctx->component_3);
    }
}

static
void Set_velocity_callback(ecs_iter_t *it) {
    ECS_COLUMN(it, Velocity, v, 1);

    int i;
    for (i = 0; i < it->count; i ++) {
        v->x ++;
        v->y ++;
    }
}

static
void Set_random(ecs_iter_t *it) {
    IterData *ctx = ecs_get_ctx(it->world);     

    int i;
    for (i = 0; i < it->count; i ++) {
        Position pos = {10, 20};
        set_random(it->world, 0, ctx->component, &pos, &pos, sizeof(Position));

        Velocity vel = {30, 40};
        Velocity vel_expect = {31, 41};
        set_random(it->world, it->entities[i], ctx->component_2, &vel, &vel_expect,
            sizeof(Velocity));

        Rotation rot = {50};
        set_random(it->world, it->entities[i], ctx->component_3, &rot, &rot,
            sizeof(Rotation));
    }
}

static
void create_delete_entity_random_components_staged(
    int32_t threads)
{
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);
    ECS_TYPE(world, Type, Position, Velocity);

    ECS_SYSTEM(world, Add_random, EcsOnUpdate, Position);
    ECS_SYSTEM(world, Delete_above_1000, EcsPostUpdate, Position);

    IterData ctx = {.component = ecs_typeid(Position), .component_2 = ecs_typeid(Velocity), .component_3 = ecs_typeid(Rotation)};
    ecs_set_ctx(world, &ctx);

    ecs_bulk_new(world, Position, 500);
    ecs_bulk_new(world, Type, 500);

    if (threads) {
        ecs_set_threads(world, threads);
    }

    uint64_t i;
    for (i = 0; i < 100; i ++) {
        ecs_progress(world, 1);
    }

    test_assert(true);

    ecs_fini(world);
}

static
void set_entity_random_components(
    int32_t threads)
{
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);
    ECS_TYPE(world, Type, Position, Velocity);

    ECS_SYSTEM(world, Set_random, EcsOnUpdate, Position);
    ECS_SYSTEM(world, Set_velocity_callback, EcsOnSet, Velocity);
    ECS_SYSTEM(world, Delete_above_1000, EcsPostUpdate, Position);

    IterData ctx = {.component = ecs_typeid(Position), .component_2 = ecs_typeid(Velocity), .component_3 = ecs_typeid(Rotation)};
    ecs_set_ctx(world, &ctx);

    const ecs_entity_t *ids = ecs_bulk_new(world, Position, 5);
    test_assert(ids != NULL);

    ids = ecs_bulk_new(world, Type, 5);
    test_assert(ids != NULL);

    if (threads) {
        ecs_set_threads(world, threads);
    }

    int i;
    for (i = 0; i < 100; i ++) {
        ecs_progress(world, 1);
    }

    ecs_fini(world);
}

void Stresstests_create_delete_entity_random_components() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);

    const ecs_entity_t *ids = ecs_bulk_new(world, 0, 1000);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 1000; i ++) {
        add_random(world, ids[i], ecs_typeid(Position));
        add_random(world, ids[i], ecs_typeid(Velocity));
        add_random(world, ids[i], ecs_typeid(Rotation));
    }

    ecs_fini(world);
}

void Stresstests_set_entity_random_components() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);

    ECS_SYSTEM(world, Set_velocity_callback, EcsOnSet, Velocity);

    const ecs_entity_t *ids = ecs_bulk_new(world, 0, 1000);
    test_assert(ids != NULL);

    int i;
    for (i = 0; i < 1000; i ++) {
        Position pos = {10, 20};
        set_random(world, ids[i], ecs_typeid(Position), &pos, &pos, sizeof(Position));

        Velocity vel = {30, 40};
        Velocity vel_expect = {31, 41};
        set_random(world, ids[i], ecs_typeid(Velocity), &vel, &vel_expect, sizeof(Velocity));

        Rotation rot = {50};
        set_random(world, ids[i], ecs_typeid(Rotation), &rot, &rot, sizeof(Rotation));
    }

    ecs_fini(world);
}

void Stresstests_create_delete_entity_random_components_staged() {
    create_delete_entity_random_components_staged(0);
}

void Stresstests_set_entity_random_components_staged() {
    set_entity_random_components(0);
}

void Stresstests_create_delete_entity_random_components_2_threads() {
    create_delete_entity_random_components_staged(2);
}

void Stresstests_set_entity_random_components_2_threads() {
    set_entity_random_components(2);
}

void Stresstests_create_delete_entity_random_components_6_threads() {
    create_delete_entity_random_components_staged(6);
}

void Stresstests_set_entity_random_components_6_threads() {
    set_entity_random_components(6);
}

void Stresstests_create_delete_entity_random_components_12_threads() {
    create_delete_entity_random_components_staged(12);
}

void Stresstests_set_entity_random_components_12_threads() {
    set_entity_random_components(12);
}

void Stresstests_create_2m_entities_1_comp() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);

    int32_t i;
    for (i = 0; i < 2000 * 1000; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        test_assert(e != 0);
        test_assert(ecs_has(world, e, Position));
    }

    ecs_fini(world);
}

void Stresstests_create_2m_entities_bulk_1_comp() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);

    const ecs_entity_t *ids = ecs_bulk_new(world, Position, 2000 * 1000);
    test_assert(ids != NULL);

    int32_t i;
    for (i = 0; i < 2000 * 1000; i ++) {
        test_assert(ecs_has(world, ids[i], Position));
    }

    ecs_fini(world);
}

void Stresstests_add_1k_tags() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new(world, 0);

    int i;
    for (i = 0; i < 1000; i ++) {
        ecs_add_id(world, e, i + 1000);
        test_assert(ecs_has_entity(world, e, i + 1000));
    }

    ecs_type_t type = ecs_get_type(world, e);
    test_assert(type != NULL);
    test_int(ecs_vector_count(type), 1000);

    ecs_fini(world);
}

void Stresstests_create_1m_set_two_components() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_entity_t i, j;
    for (i = e; i < 1000000 + e; i ++) {
        ecs_set(world, i, Position, {10, 20});
    }

    for (j = e; j < 1000000 + e; j ++) {
        test_assert(ecs_get_type(world, j) != NULL);
    }    

    for (i = e; i < e + 1000000 + e; i ++) {
        ecs_set(world, i, Velocity, {1, 2});
    }    

    ecs_fini(world);
}
