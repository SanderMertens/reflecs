
#include <api.h>
#include <flecs/type.h>

void DirectAccess_get_table_from_str() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *table = ecs_table_from_str(world, "Position, Velocity");
    test_assert(table != NULL);

    ecs_type_t type = ecs_table_get_type(table);
    test_assert(type != NULL);

    test_int(ecs_vector_count(type), 2);
    test_assert(ecs_type_owns_entity(world, type, ecs_typeid(Position), true));
    test_assert(ecs_type_owns_entity(world, type, ecs_typeid(Velocity), true));

    ecs_fini(world);
}

void DirectAccess_get_table_from_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_type_t type = ecs_type_from_str(world, "Position, Velocity");
    test_assert(type != NULL);

    ecs_table_t *table = ecs_table_from_type(world, type);
    test_assert(table != NULL);
    test_assert(type == ecs_table_get_type(table));

    ecs_fini(world);
}

void DirectAccess_insert_record() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *table = ecs_table_from_str(world, "Position, Velocity");
    test_assert(table != NULL);

    ecs_record_t r = ecs_table_insert(world, table, 0, NULL);
    test_assert(r.table == table);
    test_int(r.row, 1);

    test_int(ecs_table_count(table), 1);

    ecs_query_t *q = ecs_query_new(world, "Position, Velocity");
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_assert(it.table == table);
    test_int(it.count, 1);
    test_int(it.entities[0], 0);

    ecs_fini(world);
}

void DirectAccess_insert_record_w_entity() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *table = ecs_table_from_str(world, "Position, Velocity");
    test_assert(table != NULL);

    ecs_entity_t e = ecs_new_id(world);
    test_assert(e != 0);

    ecs_record_t *r_ptr = ecs_record_find(world, e);
    test_assert(r_ptr != NULL);
    test_assert(r_ptr->table == NULL);
    test_int(r_ptr->row, 0);

    ecs_record_t r = ecs_table_insert(world, table, e, r_ptr);
    test_assert(r.table == table);
    test_int(r.row, 1);
    test_assert(r_ptr->table == table);
    test_int(r_ptr->row, 1);

    test_int(ecs_table_count(table), 1);
    test_assert(ecs_has(world, e, Position));
    test_assert(ecs_has(world, e, Velocity));

    ecs_query_t *q = ecs_query_new(world, "Position, Velocity");
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_assert(it.table == table);
    test_int(it.count, 1);
    test_int(it.entities[0], e);

    ecs_fini(world);
}

void DirectAccess_table_count() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_new(world, Type);
    ecs_new(world, Type);
    ecs_new(world, Type);

    ecs_table_t *t = ecs_table_from_type(world, ecs_type(Type));
    test_assert(t != NULL);
    test_assert(ecs_table_get_type(t) == ecs_type(Type));
    test_int(ecs_table_count(t), 3);

    ecs_fini(world);
}

void DirectAccess_find_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_fini(world);
}

void DirectAccess_get_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_set(world, ecs_set(world, 0, 
        Position, {10, 20}),
        Velocity, {1, 2});

    ecs_set(world, ecs_set(world, 0, 
        Position, {30, 40}),
        Velocity, {3, 4});

    ecs_set(world, ecs_set(world, 0, 
        Position, {50, 60}),
        Velocity, {5, 6});

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_vector_t *v_p = ecs_table_get_column(t, 0);
    test_assert(v_p != NULL);

    Position *p = ecs_vector_first(v_p, Position);
    test_assert(p != NULL);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);

    test_int(p[1].x, 30);
    test_int(p[1].y, 40);

    test_int(p[2].x, 50);
    test_int(p[2].y, 60);

    ecs_vector_t *v_v = ecs_table_get_column(t, 1);
    test_assert(v_v != NULL);

    Velocity *v = ecs_vector_first(v_v, Velocity);
    test_assert(v != NULL);
    test_int(v[0].x, 1);
    test_int(v[0].y, 2);

    test_int(v[1].x, 3);
    test_int(v[1].y, 4);

    test_int(v[2].x, 5);
    test_int(v[2].y, 6);

    ecs_fini(world);
}

void DirectAccess_get_empty_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    test_assert(ecs_table_get_column(t, 0) == NULL);
    test_assert(ecs_table_get_column(t, 1) == NULL);

    ecs_fini(world);
}

void DirectAccess_set_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *t = ecs_table_from_str(world, "Position");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);

    ecs_vector_t *v_e = ecs_vector_new(ecs_entity_t, 3);
    ecs_vector_add(&v_e, ecs_entity_t)[0] = 0;
    ecs_vector_add(&v_e, ecs_entity_t)[0] = 0;
    ecs_vector_add(&v_e, ecs_entity_t)[0] = 0;

    ecs_vector_t *v_r = ecs_vector_new(ecs_record_t*, 3);
    ecs_vector_set_count(&v_r, ecs_record_t*, 3);
    ecs_vector_zero(v_r, ecs_record_t*);

    ecs_table_set_entities(t, v_e, v_r);

    ecs_vector_t *v_p = ecs_vector_new(Position, 3);
    ecs_vector_add(&v_p, Position)[0] = (Position){10, 20};
    ecs_vector_add(&v_p, Position)[0] = (Position){30, 40};
    ecs_vector_add(&v_p, Position)[0] = (Position){50, 60};
    ecs_table_set_column(world, t, 0, v_p);

    test_int(ecs_table_count(t), 3);
    test_assert(ecs_table_get_entities(t) == v_e);
    test_assert(ecs_table_get_records(t) == v_r);
    test_assert(ecs_table_get_column(t, 0) == v_p);

    ecs_fini(world);
}

void DirectAccess_delete_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_set(world, ecs_set(world, 0, 
        Position, {10, 20}),
        Velocity, {1, 2});

    ecs_set(world, ecs_set(world, 0, 
        Position, {30, 40}),
        Velocity, {3, 4});

    ecs_set(world, ecs_set(world, 0, 
        Position, {50, 60}),
        Velocity, {5, 6});

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_vector_t *v_p = ecs_table_get_column(t, 0);
    test_assert(v_p != NULL);

    ecs_table_delete_column(world, t, 0, NULL);

    test_assert(ecs_table_get_column(t, 0) == NULL);
    test_assert(ecs_table_get_column(t, 1) != NULL);

    ecs_fini(world);
}

void DirectAccess_delete_column_explicit() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_set(world, ecs_set(world, 0, 
        Position, {10, 20}),
        Velocity, {1, 2});

    ecs_set(world, ecs_set(world, 0, 
        Position, {30, 40}),
        Velocity, {3, 4});

    ecs_set(world, ecs_set(world, 0, 
        Position, {50, 60}),
        Velocity, {5, 6});

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_vector_t *v_p = ecs_table_get_column(t, 0);
    test_assert(v_p != NULL);

    ecs_table_delete_column(world, t, 0, v_p);

    ecs_fini(world);
}

static int ctor_position = 0;
static int dtor_position = 0;
static int copy_position = 0;
static int move_position = 0;

ECS_CTOR(Position, ptr, {
    ctor_position ++;
    *ptr = (Position){0, 0};
});

ECS_DTOR(Position, ptr, {
    dtor_position ++;
    *ptr = (Position){0, 0};
});

ECS_COPY(Position, dst, src, {
    copy_position ++;
    *dst = *src;
});

ECS_MOVE(Position, dst, src, {
    move_position ++;
    *dst = *src;
});

void DirectAccess_delete_column_w_dtor() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_set(world, ecs_set(world, 0, 
        Position, {10, 20}),
        Velocity, {1, 2});

    ecs_set(world, ecs_set(world, 0, 
        Position, {30, 40}),
        Velocity, {3, 4});

    ecs_set(world, ecs_set(world, 0, 
        Position, {50, 60}),
        Velocity, {5, 6});

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_vector_t *v_p = ecs_table_get_column(t, 0);
    test_assert(v_p != NULL);

    ecs_set_component_actions(world, Position, {
        .ctor = ecs_ctor(Position),
        .dtor = ecs_dtor(Position),
        .copy = ecs_copy(Position),
        .move = ecs_move(Position)
    });    

    ecs_table_delete_column(world, t, 0, NULL);
    test_int(ctor_position, 0);
    test_int(dtor_position, 3);
    test_int(copy_position, 0);
    test_int(move_position, 0);

    /* Column was deleted, also reset entities & records */
    ecs_vector_free(ecs_table_get_entities(t));
    ecs_vector_free(ecs_table_get_records(t));
    ecs_table_set_entities(t, NULL, NULL);

    test_assert(ecs_table_get_column(t, 0) == NULL);
    test_assert(ecs_table_get_column(t, 1) != NULL);

    ecs_fini(world);
}

void DirectAccess_copy_to() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_record_t r = ecs_table_insert(world, t, 0, NULL);
    test_assert(r.table == t);
    test_int(r.row, 1);

    test_int(ecs_table_count(t), 1);

    ecs_set_component_actions(world, Position, {
        .ctor = ecs_ctor(Position),
        .dtor = ecs_dtor(Position),
        .copy = ecs_copy(Position),
        .move = ecs_move(Position)
    });    

    ecs_record_copy_to(world, &r, 0, sizeof(Position), &(Position){10, 20}, 1);
    test_int(ctor_position, 0);
    test_int(dtor_position, 0);
    test_int(copy_position, 1);
    test_int(move_position, 0);

    Position *p = ecs_record_get_column(&r, 0, sizeof(Position));
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void DirectAccess_copy_pod_to() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_record_t r = ecs_table_insert(world, t, 0, NULL);
    test_assert(r.table == t);
    test_int(r.row, 1);

    test_int(ecs_table_count(t), 1);

    ecs_set_component_actions(world, Position, {
        .ctor = ecs_ctor(Position),
        .dtor = ecs_dtor(Position),
        .copy = ecs_copy(Position),
        .move = ecs_move(Position)
    });    

    /* This should not be done in a real application (copying a component with
     * lifecycle actions with copy_pod_to) but for the testcase it is useful to
     * verify that the copy/move actions are not being invoked when using this
     * function. */
    ecs_record_copy_pod_to(world, &r, 0, sizeof(Position), &(Position){10, 20}, 1);
    test_int(ctor_position, 0);
    test_int(dtor_position, 0);
    test_int(copy_position, 0);
    test_int(move_position, 0);

    Position *p = ecs_record_get_column(&r, 0, sizeof(Position));
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void DirectAccess_move_to() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_record_t r = ecs_table_insert(world, t, 0, NULL);
    test_assert(r.table == t);
    test_int(r.row, 1);

    test_int(ecs_table_count(t), 1);

    ecs_set_component_actions(world, Position, {
        .ctor = ecs_ctor(Position),
        .dtor = ecs_dtor(Position),
        .copy = ecs_copy(Position),
        .move = ecs_move(Position)
    });    

    ecs_record_move_to(world, &r, 0, sizeof(Position), &(Position){10, 20}, 1);
    test_int(ctor_position, 0);
    test_int(dtor_position, 0);
    test_int(copy_position, 0);
    test_int(move_position, 1);

    Position *p = ecs_record_get_column(&r, 0, sizeof(Position));
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void DirectAccess_copy_to_no_copy() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_record_t r = ecs_table_insert(world, t, 0, NULL);
    test_assert(r.table == t);
    test_int(r.row, 1);

    test_int(ecs_table_count(t), 1);   

    ecs_record_copy_to(world, &r, 0, sizeof(Position), &(Position){10, 20}, 1);

    Position *p = ecs_record_get_column(&r, 0, sizeof(Position));
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void DirectAccess_move_to_no_move() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_table_t *t = ecs_table_from_str(world, "Position, Velocity");
    test_assert(t != NULL);

    test_int(ecs_table_find_column(t, ecs_typeid(Position)), 0);
    test_int(ecs_table_find_column(t, ecs_typeid(Velocity)), 1);

    ecs_record_t r = ecs_table_insert(world, t, 0, NULL);
    test_assert(r.table == t);
    test_int(r.row, 1);

    test_int(ecs_table_count(t), 1);

    ecs_record_move_to(world, &r, 0, sizeof(Position), &(Position){10, 20}, 1);

    Position *p = ecs_record_get_column(&r, 0, sizeof(Position));
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void DirectAccess_find_record_not_exists() {
    ecs_world_t *world = ecs_init();

    ecs_record_t *r_ptr = ecs_record_find(world, 1000);
    test_assert(r_ptr == NULL);

    ecs_fini(world);
}

void DirectAccess_get_entities_empty_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_table_t *t = ecs_table_from_str(world, "Position");
    test_assert(t != NULL);

    test_assert(ecs_table_get_entities(t) == NULL);

    ecs_fini(world);
}

void DirectAccess_get_records_empty_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_table_t *t = ecs_table_from_str(world, "Position");
    test_assert(t != NULL);

    test_assert(ecs_table_get_records(t) == NULL);

    ecs_fini(world);
}

void DirectAccess_get_column_empty_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_table_t *t = ecs_table_from_str(world, "Position");
    test_assert(t != NULL);

    test_assert(ecs_table_get_column(t, 0) == NULL);

    ecs_fini(world);
}

void DirectAccess_delete_column_empty_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_table_t *t = ecs_table_from_str(world, "Position");
    test_assert(t != NULL);

    ecs_table_delete_column(world, t, 0, NULL);

    ecs_fini(world);
}

void DirectAccess_get_record_column_empty_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_table_t *t = ecs_table_from_str(world, "Position");
    test_assert(t != NULL);

    ecs_record_t r = {.table = t, .row = 0};

    test_assert(ecs_record_get_column(&r, 0, sizeof(Position)) == NULL);

    ecs_fini(world);
}

void DirectAccess_has_module() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);

    ecs_entity_t m = ecs_entity_init(world, &(ecs_entity_desc_t) {
        .add = {EcsModule}
    });

    ecs_entity_t m_e = ecs_entity_init(world, &(ecs_entity_desc_t) {
        .add = {ecs_pair(EcsChildOf, m)}
    });

    ecs_record_t *r = ecs_record_find(world, e);
    test_assert(r != NULL);
    test_assert(r->table != NULL);
    test_assert(ecs_table_has_module(r->table) == false);

    r = ecs_record_find(world, ecs_id(Position));
    test_assert(r != NULL);
    test_assert(r->table != NULL);
    test_assert(ecs_table_has_module(r->table) == false);

    r = ecs_record_find(world, m);
    test_assert(r != NULL);
    test_assert(r->table != NULL);
    test_assert(ecs_table_has_module(r->table) == true);

    r = ecs_record_find(world, m_e);
    test_assert(r != NULL);
    test_assert(r->table != NULL);
    test_assert(ecs_table_has_module(r->table) == true);

    ecs_fini(world);
}
