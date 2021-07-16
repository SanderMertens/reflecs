#include <api.h>

void Hierarchies_setup() {
    ecs_tracing_enable(-2);
}

void Hierarchies_empty_scope() {
    ecs_world_t *world = ecs_init();

    test_assert(ecs_get_scope(world) == 0);

    ecs_fini(world);
}

void Hierarchies_get_parent() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Child, 0);

    ecs_entity_t e = ecs_get_parent_w_entity(world, Child, 0);
    test_assert(e == 0);

    ecs_fini(world);
}

void Hierarchies_get_parent_from_nested() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);
    ECS_ENTITY(world, Child, CHILDOF | Scope);

    ecs_entity_t e = ecs_get_parent_w_entity(world, Child, 0);
    test_assert(e == Scope);

    ecs_fini(world);
}

void Hierarchies_get_parent_from_nested_2() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);
    ECS_ENTITY(world, ChildScope, CHILDOF | Scope);
    ECS_ENTITY(world, Child, CHILDOF | Scope.ChildScope);

    ecs_entity_t e = ecs_get_parent_w_entity(world, Child, 0);
    test_assert(e == ChildScope);

    ecs_fini(world);
}

void Hierarchies_get_parent_from_root() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);
    ECS_ENTITY(world, Child, CHILDOF | Scope);

    ecs_entity_t e = ecs_get_parent_w_entity(world, 0, 0);
    test_assert(e == 0);

    ecs_fini(world);
}

void Hierarchies_delete_children() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);

    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(child != 0);

    ecs_delete(world, parent);

    test_bool(ecs_exists(world, child), true);
    test_bool(ecs_is_alive(world, child), false);

    ecs_fini(world);
}

void Hierarchies_tree_iter_empty() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);

    ecs_iter_t it = ecs_scope_iter(world, Parent);
    test_assert( !ecs_scope_next(&it));

    ecs_fini(world);
}

void Hierarchies_tree_iter_1_table() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);

    ECS_ENTITY(world, Child1, CHILDOF | Parent);
    ECS_ENTITY(world, Child2, CHILDOF | Parent);
    ECS_ENTITY(world, Child3, CHILDOF | Parent);

    ecs_iter_t it = ecs_scope_iter(world, Parent);
    test_assert( ecs_scope_next(&it) == true);
    test_int( it.count, 3);

    test_assert(it.entities[0] == Child1);
    test_assert(it.entities[1] == Child2);
    test_assert(it.entities[2] == Child3);

    test_assert( !ecs_scope_next(&it));

    ecs_fini(world);
}

void Hierarchies_tree_iter_2_tables() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Parent, 0);

    ECS_ENTITY(world, Child1, CHILDOF | Parent);
    ECS_ENTITY(world, Child2, CHILDOF | Parent);
    ECS_ENTITY(world, Child3, CHILDOF | Parent, Position);
    ECS_ENTITY(world, Child4, CHILDOF | Parent, Position);

    ecs_iter_t it = ecs_scope_iter(world, Parent);
    test_assert( ecs_scope_next(&it) == true);
    test_int( it.count, 2);
     test_int(it.entities[0], Child1);
    test_int(it.entities[1], Child2);

    test_assert( ecs_scope_next(&it) == true);
    test_int( it.count, 2);
    test_int(it.entities[0], Child3);
    test_int(it.entities[1], Child4);       

    test_assert( !ecs_scope_next(&it));

    ecs_fini(world);
}

void Hierarchies_tree_iter_w_filter() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, Parent, 0);

    ECS_ENTITY(world, Child1, CHILDOF | Parent, Position);
    ECS_ENTITY(world, Child2, CHILDOF | Parent, Position);
    ECS_ENTITY(world, Child3, CHILDOF | Parent, Position);
    ECS_ENTITY(world, Child4, CHILDOF | Parent, Velocity);

    ecs_iter_t it = ecs_scope_iter_w_filter(world, Parent, &(ecs_filter_t){
        .include = ecs_type(Position)
    });

    test_assert( ecs_scope_next(&it) == true);
    test_int( it.count, 3);

    test_assert(it.entities[0] == Child1);
    test_assert(it.entities[1] == Child2);
    test_assert(it.entities[2] == Child3);

    test_assert( !ecs_scope_next(&it));

    ecs_fini(world);
}


void Hierarchies_path_depth_0() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);

    char *path = ecs_get_fullpath(world, Parent);
    test_str(path, "Parent");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_depth_1() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    char *path = ecs_get_fullpath(world, Child);
    test_str(path, "Parent.Child");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_depth_2() {
   ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);
    ECS_ENTITY(world, GrandChild, CHILDOF | Parent.Child);

    char *path = ecs_get_fullpath(world, GrandChild);
    test_str(path, "Parent.Child.GrandChild");
    free(path);

    ecs_fini(world);
}

void Hierarchies_rel_path_from_root() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);

    char *path = ecs_get_path(world, 0, Parent);
    test_str(path, "Parent");
    free(path);

    ecs_fini(world);
}

void Hierarchies_rel_path_from_self() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);

    char *path = ecs_get_path(world, Parent, Parent);
    test_str(path, "");
    free(path);

    ecs_fini(world);
}

void Hierarchies_rel_path_depth_1() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    char *path = ecs_get_path(world, Parent, Child);
    test_str(path, "Child");
    free(path);

    ecs_fini(world);
}

void Hierarchies_rel_path_depth_2() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);
    ECS_ENTITY(world, GrandChild, CHILDOF | Parent.Child);

    char *path = ecs_get_path(world, Parent, GrandChild);
    test_str(path, "Child.GrandChild");
    free(path);

    ecs_fini(world);
}

void Hierarchies_rel_path_no_match() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Parent2, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    char *path = ecs_get_path(world, Parent2, Child);
    test_str(path, "Parent.Child");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_for_component_0() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Parent, 0);

    char *path = ecs_get_path_w_sep(world, 0, Parent, ecs_typeid(Position), ".", NULL);
    test_str(path, "Parent");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_for_component_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Parent2, Position);
    ECS_ENTITY(world, Child, CHILDOF | Parent, CHILDOF | Parent2);

    char *path = ecs_get_path_w_sep(world, 0, Child, ecs_typeid(Position), ".", NULL);
    test_str(path, "Parent2.Child");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_for_component_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Parent2, Position);
    ECS_ENTITY(world, Child1, CHILDOF | Parent);
    ECS_ENTITY(world, Child2, Position, CHILDOF | Parent2);
    ECS_ENTITY(world, GrandChild, CHILDOF | Parent.Child1, CHILDOF | Parent2.Child2);

    char *path = ecs_get_path_w_sep(world, 0, GrandChild, ecs_typeid(Position), ".", NULL);
    test_str(path, "Parent2.Child2.GrandChild");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_custom_sep() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    char *path = ecs_get_path_w_sep(world, 0, Child, 0, "::", NULL);
    test_str(path, "Parent::Child");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_custom_prefix() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    char *path = ecs_get_path_w_sep(world, 0, Child, 0,  "::", "::");
    test_str(path, "::Parent::Child");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_prefix_rel_match() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);
    ECS_ENTITY(world, GrandChild, CHILDOF | Parent.Child);

    char *path = ecs_get_path_w_sep(world, Parent, GrandChild, 0, "::", "::");
    test_str(path, "Child::GrandChild");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_prefix_rel_no_match() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Parent2, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);
    ECS_ENTITY(world, GrandChild, CHILDOF | Parent.Child);

    char *path = ecs_get_path_w_sep(world, Parent2, GrandChild, 0, "::", "::");
    test_str(path, "::Parent::Child::GrandChild");
    free(path);

    ecs_fini(world);
}

void Hierarchies_path_w_number() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_w_pair(world, EcsChildOf, 1000);
    ecs_set(world, e, EcsName, {"Foo"});

    char *path = ecs_get_fullpath(world, e);
    test_str(path, "1000.Foo");
    free(path);

    ecs_fini(world);
}


void Hierarchies_lookup_depth_0() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);

    ecs_entity_t e = ecs_lookup_fullpath(world, "Parent");
    test_assert(e == Parent);

    ecs_fini(world);
}

void Hierarchies_lookup_depth_1() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    ecs_entity_t e = ecs_lookup_fullpath(world, "Parent.Child");
    test_assert(e == Child);

    ecs_fini(world);
}

void Hierarchies_lookup_depth_2() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);
    ECS_ENTITY(world, GrandChild, CHILDOF | Parent.Child);

    ecs_entity_t e = ecs_lookup_fullpath(world, "Parent.Child.GrandChild");
    test_assert(e == GrandChild);

    ecs_fini(world);
}

void Hierarchies_lookup_rel_0() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    ecs_entity_t e = ecs_lookup_path(world, Parent, "Child");
    test_assert(e == Child);

    ecs_fini(world);
}

void Hierarchies_lookup_rel_1() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);
    ECS_ENTITY(world, GrandChild, CHILDOF | Parent.Child);

    ecs_entity_t e = ecs_lookup_path(world, Parent, "Child.GrandChild");
    test_assert(e == GrandChild);

    ecs_fini(world);
}

void Hierarchies_lookup_rel_2() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);
    ECS_ENTITY(world, GrandChild, CHILDOF | Parent.Child);
    ECS_ENTITY(world, GrandGrandChild, CHILDOF | Parent.Child.GrandChild);

    ecs_entity_t e = ecs_lookup_path(world, Parent, "Child.GrandChild.GrandGrandChild");
    test_assert(e == GrandGrandChild);

    ecs_fini(world);
}

void Hierarchies_lookup_custom_sep() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    ecs_entity_t e = ecs_lookup_path_w_sep(world, 0, "Parent::Child", "::", NULL, true);
    test_assert(e == Child);

    ecs_fini(world);
}

void Hierarchies_lookup_custom_prefix() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    ecs_entity_t e = ecs_lookup_path_w_sep(world, 0, "::Parent::Child", "::", "::", true);
    test_assert(e == Child);

    ecs_fini(world);
}

void Hierarchies_lookup_custom_prefix_from_root() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    ecs_entity_t e = ecs_lookup_path_w_sep(world, Parent, "::Parent::Child", "::", "::", true);
    test_assert(e == Child);

    ecs_fini(world);
}

void Hierarchies_lookup_self() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);

    ecs_entity_t e = ecs_lookup_path(world, Parent, "");
    test_assert(e == Parent);

    ecs_fini(world);
}

void Hierarchies_lookup_number() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Parent2, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);
    ECS_ENTITY(world, GrandChild, CHILDOF | Parent.Child);

    ecs_entity_t e = ecs_new_w_pair(world, EcsChildOf, 1000);
    ecs_set(world, e, EcsName, {"Foo"});

    ecs_entity_t c = ecs_lookup_path(world, 0, "1000.Foo");
    test_assert(e == c);

    ecs_fini(world);
}

void Hierarchies_scope_set() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);

    ecs_entity_t old_scope = ecs_set_scope(world, Scope);
    test_assert(old_scope == 0);

    ecs_entity_t scope = ecs_get_scope(world);
    test_assert(scope == Scope);

    ecs_fini(world);
}

void Hierarchies_scope_set_w_new() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);

    ecs_entity_t old_scope = ecs_set_scope(world, Scope);
    test_assert(old_scope == 0);

    ecs_entity_t e = ecs_new(world, 0);
    test_assert(e != 0);
    test_assert(ecs_has_pair(world, e, EcsChildOf, Scope));

    old_scope = ecs_set_scope(world, 0);
    test_assert(old_scope == Scope);

    e = ecs_new(world, 0);
    test_assert(e != 0);
    test_assert(ecs_get_type(world, e) == NULL);

    ecs_fini(world);
}

void Hierarchies_scope_set_w_new_staged() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);

    ecs_defer_begin(world);

    ecs_entity_t old_scope = ecs_set_scope(world, Scope);
    test_assert(old_scope == 0);

    ecs_entity_t e1 = ecs_new(world, 0);
    test_assert(e1 != 0);

    old_scope = ecs_set_scope(world, 0);
    test_assert(old_scope == Scope);

    ecs_entity_t e2 = ecs_new(world, 0);
    test_assert(e2 != 0);

    ecs_defer_end(world);

    test_assert(ecs_has_pair(world, e1, EcsChildOf, Scope));
    test_assert(ecs_get_type(world, e2) == NULL);

    ecs_fini(world);
}

void Hierarchies_scope_set_again() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);
    ECS_ENTITY(world, ChildScope, 0);

    ecs_entity_t old_scope = ecs_set_scope(world, Scope);
    test_assert(old_scope == 0);

    old_scope = ecs_set_scope(world, ChildScope);
    test_assert(old_scope == Scope);

    ecs_fini(world);
}

void Hierarchies_scope_set_w_lookup() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);
    ECS_ENTITY(world, Child, CHILDOF | Scope);

    test_assert( ecs_lookup_fullpath(world, "Child") == 0);

    ecs_entity_t old_scope = ecs_set_scope(world, Scope);
    test_assert(old_scope == 0);

    ecs_entity_t e = ecs_lookup_fullpath(world, "Child");
    test_assert(e != 0);
    test_assert(e == Child);

    old_scope = ecs_set_scope(world, 0);
    test_assert(old_scope == Scope);

    test_assert( ecs_lookup_fullpath(world, "Child") == 0);

    ecs_fini(world);
}

void Hierarchies_lookup_in_parent_from_scope() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);
    ECS_ENTITY(world, ChildScope, CHILDOF | Scope);
    ECS_ENTITY(world, Child, CHILDOF | Scope);

    test_assert( ecs_lookup_fullpath(world, "Child") == 0);

    ecs_entity_t old_scope = ecs_set_scope(world, ChildScope);
    test_assert(old_scope == 0);

    ecs_entity_t e = ecs_lookup_fullpath(world, "Child");
    test_assert(e != 0);
    test_assert(e == Child);

    old_scope = ecs_set_scope(world, 0);
    test_assert(old_scope == ChildScope);

    test_assert( ecs_lookup_fullpath(world, "Child") == 0);

    ecs_fini(world);
}

void Hierarchies_lookup_in_root_from_scope() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);
    ECS_ENTITY(world, ChildScope, CHILDOF | Scope);
    ECS_ENTITY(world, Child, 0);

    ecs_entity_t old_scope = ecs_set_scope(world, ChildScope);
    test_assert(old_scope == 0);

    ecs_entity_t e = ecs_lookup_fullpath(world, "Child");
    test_assert(e != 0);
    test_assert(e == Child);

    old_scope = ecs_set_scope(world, 0);
    test_assert(old_scope == ChildScope);

    ecs_fini(world);
}

void Hierarchies_scope_component() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Scope, 0);

    ecs_entity_t old_scope = ecs_set_scope(world, Scope);
    test_assert(old_scope == 0);

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_lookup_fullpath(world, "Position");
    test_assert(e != 0);
    test_assert(e == ecs_id(Position));

    old_scope = ecs_set_scope(world, 0);
    test_assert(old_scope == Scope);

    e = ecs_lookup_fullpath(world, "Position");
    test_assert(e == 0);

    e = ecs_lookup_fullpath(world, "Scope.Position");
    test_assert(e == ecs_id(Position));

    ecs_fini(world);
}

void Hierarchies_scope_component_no_macro() {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t Scope = ecs_new_id(world);

    ecs_entity_t old_scope = ecs_set_scope(world, Scope);
    test_assert(old_scope == 0);

    ecs_entity_t e2 = ecs_entity_init(world, &(ecs_entity_desc_t) {
        .use_low_id = true
    });

    test_assert(e2 != 0);
    test_assert(ecs_has_pair(world, e2, EcsChildOf, Scope));


    ecs_fini(world);
    
    /* The real purpose of this test is to catch an issue where a component was
     * added to multiple tables, which caused a crash during ecs_fini */
}

void Hierarchies_fullpath_for_core() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, CHILDOF | Parent);

    char *path = ecs_get_fullpath(world, ecs_typeid(EcsComponent));
    test_str(path, "Component");
    free(path);

    ecs_fini(world);
}

void Hierarchies_new_from_path_depth_0() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "foo");

    ecs_type_t type = ecs_get_type(world, e);
    test_assert(type != NULL);
    test_int(ecs_vector_count(type), 1);

    char *path = ecs_get_fullpath(world, e);
    test_str(path, "foo");
    free(path);

    ecs_fini(world);
}

void Hierarchies_new_from_path_depth_1() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo.bar");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "bar");

    ecs_type_t type = ecs_get_type(world, e);
    test_assert(type != NULL);
    test_int(ecs_vector_count(type), 2);

    char *path = ecs_get_fullpath(world, e);
    test_str(path, "foo.bar");
    free(path);

    ecs_fini(world);
}

void Hierarchies_new_from_path_depth_2() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo.bar.hello");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "hello");

    ecs_type_t type = ecs_get_type(world, e);
    test_assert(type != NULL);
    test_int(ecs_vector_count(type), 2);

    char *path = ecs_get_fullpath(world, e);
    test_str(path, "foo.bar.hello");
    free(path);

    ecs_fini(world);
}


void Hierarchies_new_from_path_existing_depth_0() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "foo");

    ecs_entity_t f = ecs_new_from_path(world, 0, "foo");
    test_assert(f != 0);
    test_assert(f == e);
    test_str(ecs_get_name(world, e), "foo");

    ecs_fini(world);
}

void Hierarchies_new_from_path_existing_depth_1() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo.bar");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "bar");

    ecs_entity_t f = ecs_new_from_path(world, 0, "foo.bar");
    test_assert(f != 0);
    test_assert(f == e);
    test_str(ecs_get_name(world, e), "bar");

    ecs_fini(world);
}

void Hierarchies_new_from_path_existing_depth_2() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo.bar.hello");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "hello");

    ecs_entity_t f = ecs_new_from_path(world, 0, "foo.bar.hello");
    test_assert(f != 0);
    test_assert(f == e);
    test_str(ecs_get_name(world, e), "hello");

    ecs_fini(world);
}

void Hierarchies_add_path_depth_0() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t id = ecs_new(world, 0);
    test_assert(id != 0);

    ecs_entity_t e = ecs_add_path(world, id, 0, "foo");
    test_assert(e != 0);
    test_assert(e == id);
    test_str(ecs_get_name(world, e), "foo");

    ecs_type_t type = ecs_get_type(world, e);
    test_assert(type != NULL);
    test_int(ecs_vector_count(type), 1);

    char *path = ecs_get_fullpath(world, e);
    test_str(path, "foo");
    free(path);

    ecs_fini(world);
}

void Hierarchies_add_path_depth_1() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t id = ecs_new(world, 0);
    test_assert(id != 0);

    ecs_entity_t e = ecs_add_path(world, id, 0, "foo.bar");
    test_assert(e != 0);
    test_assert(e == id);
    test_str(ecs_get_name(world, e), "bar");

    ecs_type_t type = ecs_get_type(world, e);
    test_assert(type != NULL);
    test_int(ecs_vector_count(type), 2);

    char *path = ecs_get_fullpath(world, e);
    test_str(path, "foo.bar");
    free(path);

    ecs_fini(world);
}

void Hierarchies_add_path_depth_2() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t id = ecs_new(world, 0);
    test_assert(id != 0);

    ecs_entity_t e = ecs_add_path(world, id, 0, "foo.bar.hello");
    test_assert(e != 0);
    test_assert(e == id);
    test_str(ecs_get_name(world, e), "hello");

    ecs_type_t type = ecs_get_type(world, e);
    test_assert(type != NULL);
    test_int(ecs_vector_count(type), 2);

    char *path = ecs_get_fullpath(world, e);
    test_str(path, "foo.bar.hello");
    free(path);

    ecs_fini(world);
}

void Hierarchies_add_path_existing_depth_0() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "foo");    

    ecs_entity_t id = ecs_new(world, 0);
    test_assert(id != 0);

    ecs_entity_t f = ecs_add_path(world, id, 0, "foo");
    test_assert(f != 0);
    test_assert(f != id);
    test_assert(f == e);
    test_str(ecs_get_name(world, e), "foo");

    ecs_fini(world);
}

void Hierarchies_add_path_existing_depth_1() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo.bar");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "bar");    

    ecs_entity_t id = ecs_new(world, 0);
    test_assert(id != 0);

    ecs_entity_t f = ecs_add_path(world, id, 0, "foo.bar");
    test_assert(f != 0);
    test_assert(f != id);
    test_assert(f == e);
    test_str(ecs_get_name(world, e), "bar");

    ecs_fini(world);
}

void Hierarchies_add_path_existing_depth_2() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo.bar.hello");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "hello");    

    ecs_entity_t id = ecs_new(world, 0);
    test_assert(id != 0);

    ecs_entity_t f = ecs_add_path(world, id, 0, "foo.bar.hello");
    test_assert(f != 0);
    test_assert(f != id);
    test_assert(f == e);
    test_str(ecs_get_name(world, e), "hello");

    ecs_fini(world);
}

void Hierarchies_add_path_from_scope() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo.bar");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "bar");    

    ecs_set_scope(world, e);

    ecs_entity_t id = ecs_new_id(world);
    test_assert(id != 0);

    ecs_entity_t f = ecs_add_path(world, id, 0, "hello.world");
    test_assert(f != 0);
    test_str(ecs_get_name(world, f), "world");

    char *path = ecs_get_fullpath(world, f);
    test_str(path, "hello.world");
    ecs_os_free(path);

    ecs_set_scope(world, 0);

    ecs_fini(world);
}

void Hierarchies_add_path_from_scope_new_entity() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_new_from_path(world, 0, "foo.bar");
    test_assert(e != 0);
    test_str(ecs_get_name(world, e), "bar");    

    ecs_set_scope(world, e);

    ecs_entity_t id = ecs_add_path(world, 0, 0, "hello.world");
    test_assert(id != 0);
    test_str(ecs_get_name(world, id), "world");

    char *path = ecs_get_fullpath(world, id);
    test_str(path, "foo.bar.hello.world");
    ecs_os_free(path);

    ecs_set_scope(world, 0);

    ecs_fini(world);
}

void Hierarchies_new_w_child_in_root() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t scope = ecs_new(world, 0);
    ecs_entity_t parent = ecs_new(world, 0);
    
    ecs_set_scope(world, scope);

    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert( ecs_has_pair(world, child, EcsChildOf, parent));
    test_assert( !ecs_has_pair(world, child, EcsChildOf, scope));

    ecs_entity_t child_2 = ecs_new(world, 0);
    test_assert( !ecs_has_pair(world, child_2, EcsChildOf, parent));
    test_assert( ecs_has_pair(world, child_2, EcsChildOf, scope));

    ecs_fini(world);
}

void Hierarchies_delete_child() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);

    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(ecs_get_type(world, child) != NULL);

    ecs_delete(world, parent);
    
    test_bool(ecs_exists(world, parent), true);
    test_bool(ecs_exists(world, child), true);    
    test_bool(ecs_is_alive(world, parent), false);
    test_bool(ecs_is_alive(world, child), false);
    
    ecs_fini(world);
}

void Hierarchies_delete_2_children() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);

    ecs_entity_t child_1 = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(child_1 != 0);
    test_assert(ecs_get_type(world, child_1) != NULL);

    ecs_entity_t child_2 = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(child_2 != 0);
    test_assert(ecs_get_type(world, child_2) != NULL);

    ecs_delete(world, parent);
    
    test_bool(ecs_is_alive(world, parent), false);
    test_bool(ecs_is_alive(world, child_1), false);
    test_bool(ecs_is_alive(world, child_2), false);

    ecs_fini(world);
}

void Hierarchies_delete_2_children_different_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);

    ecs_entity_t child_1 = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(child_1 != 0);
    test_assert(ecs_get_type(world, child_1) != NULL);
    ecs_add(world, child_1, Position);

    ecs_entity_t child_2 = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(child_2 != 0);
    test_assert(ecs_get_type(world, child_2) != NULL);
    ecs_add(world, child_2, Velocity);

    ecs_delete(world, parent);
    
    test_bool(ecs_is_alive(world, parent), false);
    test_bool(ecs_is_alive(world, child_1), false);
    test_bool(ecs_is_alive(world, child_2), false);

    ecs_fini(world);
}

void Hierarchies_delete_tree_2_levels() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);

    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(ecs_get_type(world, child) != NULL);

    ecs_entity_t grand_child = ecs_new_w_pair(world, EcsChildOf, child);
    test_assert(ecs_get_type(world, grand_child) != NULL);

    ecs_delete(world, parent);
    
    test_bool(ecs_is_alive(world, parent), false);
    test_bool(ecs_is_alive(world, child), false);
    test_bool(ecs_is_alive(world, grand_child), false);

    ecs_fini(world);
}

void Hierarchies_delete_tree_3_levels() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);

    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(ecs_get_type(world, child) != NULL);

    ecs_entity_t grand_child = ecs_new_w_pair(world, EcsChildOf, child);
    test_assert(ecs_get_type(world, grand_child) != NULL);

    ecs_entity_t great_grand_child = ecs_new_w_pair(world, EcsChildOf, grand_child);
    test_assert(ecs_get_type(world, great_grand_child) != NULL);    

    ecs_delete(world, parent);
    
    test_bool(ecs_is_alive(world, parent), false);
    test_bool(ecs_is_alive(world, child), false);
    test_bool(ecs_is_alive(world, grand_child), false);
    test_bool(ecs_is_alive(world, great_grand_child), false);

    ecs_fini(world);
}

void Hierarchies_delete_tree_count_tables() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t parent = ecs_new(world, Position);
    test_assert(parent != 0);

    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(ecs_get_type(world, child) != NULL);
    ecs_add(world, child, Position);

    ecs_entity_t grand_child = ecs_new_w_pair(world, EcsChildOf, child);
    test_assert(ecs_get_type(world, grand_child) != NULL);
    ecs_add(world, grand_child, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    ecs_iter_t it = ecs_query_iter(q);
    test_int(it.table_count, 3);

    ecs_delete(world, parent);
    
    test_bool(ecs_is_alive(world, parent), false);
    test_bool(ecs_is_alive(world, child), false);
    test_bool(ecs_is_alive(world, grand_child), false);

    it = ecs_query_iter(q);
    test_int(it.table_count, 0);

    ecs_fini(world);
}

void Hierarchies_delete_tree_staged() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t parent = ecs_new(world, Position);
    test_assert(parent != 0);

    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(ecs_get_type(world, child) != NULL);
    ecs_add(world, child, Position);

    ecs_entity_t grand_child = ecs_new_w_pair(world, EcsChildOf, child);
    test_assert(ecs_get_type(world, grand_child) != NULL);
    ecs_add(world, grand_child, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    ecs_iter_t it = ecs_query_iter(q);
    test_int(it.table_count, 3);

    ecs_defer_begin(world);
    ecs_delete(world, parent);
    ecs_defer_end(world);
    
    test_bool(ecs_is_alive(world, parent), false);
    test_bool(ecs_is_alive(world, child), false);
    test_bool(ecs_is_alive(world, grand_child), false);

    it = ecs_query_iter(q);
    test_int(it.table_count, 0);

    ecs_fini(world);
}

void Hierarchies_delete_tree_empty_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child, Position, CHILDOF | Parent);

    ecs_delete(world, Parent);
    
    test_assert(!ecs_is_alive(world, Parent));
    test_assert(!ecs_is_alive(world, Child));

    ecs_fini(world);
}

void Hierarchies_delete_tree_recreate() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t parent = ecs_new(world, 0);
    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(parent != 0);
    test_assert(child != 0);
    test_assert(ecs_has_pair(world, child, EcsChildOf, parent));

    ecs_delete_children(world, parent);

    ecs_new(world, Position);

    ecs_entity_t child_2  = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(child_2 != 0);
    test_assert(ecs_has_pair(world, child_2, EcsChildOf, parent));

    ecs_fini(world);
}

void Hierarchies_get_child_count() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child1, CHILDOF | Parent, Position);
    ECS_ENTITY(world, Child2, CHILDOF | Parent, Position);
    ECS_ENTITY(world, Child3, CHILDOF | Parent, Position);

    test_int(ecs_get_child_count(world, Parent), 3);

    ecs_fini(world);
}

void Hierarchies_get_child_count_no_children() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Parent, 0);

    test_int(ecs_get_child_count(world, Parent), 0);

    ecs_fini(world);
}

void Hierarchies_get_child_count_2_tables() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, Parent, 0);
    ECS_ENTITY(world, Child1, CHILDOF | Parent, Position);
    ECS_ENTITY(world, Child2, CHILDOF | Parent, Position);
    ECS_ENTITY(world, Child3, CHILDOF | Parent, Position);
    ECS_ENTITY(world, Child4, CHILDOF | Parent, Velocity);

    test_int(ecs_get_child_count(world, Parent), 4);

    ecs_fini(world);
}

void Hierarchies_scope_iter_after_delete_tree() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t parent = ecs_new(world, 0);
    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(parent != 0);
    test_assert(child != 0);
    test_assert(ecs_has_pair(world, child, EcsChildOf, parent));

    ecs_delete_children(world, parent);

    ecs_iter_t it = ecs_scope_iter(world, parent);
    test_assert(!ecs_scope_next(&it));

    ecs_fini(world);
}

void Hierarchies_add_child_after_delete_tree() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t parent = ecs_new(world, 0);
    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(parent != 0);
    test_assert(child != 0);
    test_assert(ecs_has_pair(world, child, EcsChildOf, parent));

    ecs_delete_children(world, parent);

    child = ecs_new_w_pair(world, EcsChildOf, parent);

    ecs_fini(world);
}

static int on_remove_count = 0;

static
void RemovePosition(ecs_iter_t *it) {
    int i;
    for (i = 0; i < it->count; i ++) {
        on_remove_count ++;
    }
}

void Hierarchies_delete_tree_w_onremove() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_TRIGGER(world, RemovePosition, EcsOnRemove, Position);

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);
    ecs_entity_t child_1 = ecs_new_w_pair(world, EcsChildOf, parent);
    ecs_entity_t child_2 = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(child_1 != 0);
    test_assert(child_2 != 0);
    test_assert(ecs_has_pair(world, child_1, EcsChildOf, parent));
    test_assert(ecs_has_pair(world, child_2, EcsChildOf, parent));

    ecs_add(world, parent, Position);
    ecs_add(world, child_1, Position);
    ecs_add(world, child_2, Position);

    ecs_delete(world, parent);

    test_assert( !ecs_is_alive(world, parent));
    test_assert( !ecs_is_alive(world, child_1));
    test_assert( !ecs_is_alive(world, child_2));

    test_int(on_remove_count, 3);

    ecs_fini(world);
}

static int dtor_count = 0;

static ECS_DTOR(Position, ptr, {
    dtor_count ++;
})

void Hierarchies_delete_tree_w_dtor() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_set_component_actions(world, Position, {
        .dtor = ecs_dtor(Position)
    });

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);
    ecs_entity_t child_1 = ecs_new_w_pair(world, EcsChildOf, parent);
    ecs_entity_t child_2 = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(child_1 != 0);
    test_assert(child_2 != 0);
    test_assert(ecs_has_pair(world, child_1, EcsChildOf, parent));
    test_assert(ecs_has_pair(world, child_2, EcsChildOf, parent));

    ecs_add(world, parent, Position);
    ecs_add(world, child_1, Position);
    ecs_add(world, child_2, Position);

    ecs_delete(world, parent);

    test_assert( !ecs_is_alive(world, parent));
    test_assert( !ecs_is_alive(world, child_1));
    test_assert( !ecs_is_alive(world, child_2));

    test_int(dtor_count, 3);

    ecs_fini(world);
}

void Hierarchies_add_child_to_recycled_parent() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);

    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(child != 0);
    test_assert(ecs_has_pair(world, child, EcsChildOf, parent));

    ecs_delete(world, parent);
    test_assert( !ecs_is_alive(world, parent));
    test_assert( !ecs_is_alive(world, child));

    ecs_entity_t new_parent = ecs_new(world, 0);
    test_assert(new_parent != 0);
    /* Make sure we have a recycled identifier */
    test_assert(ecs_entity_t_lo(new_parent) != new_parent);

    child = ecs_new_w_pair(world, EcsChildOf, new_parent);
    test_assert(child != 0);
    test_assert(ecs_has_pair(world, child, EcsChildOf, new_parent));
    test_assert( ecs_is_alive(world, child));
    test_assert( ecs_is_alive(world, child));

    ecs_fini(world);
}

void Hierarchies_get_type_after_recycled_parent_add() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);
    test_assert( ecs_get_type(world, parent) == NULL);

    ecs_delete(world, parent);
    test_assert( !ecs_is_alive(world, parent));

    parent = ecs_new(world, Position);
    test_assert(parent != 0);
    test_assert(ecs_entity_t_lo(parent) != parent); // Ensure recycled
    test_assert( ecs_get_type(world, parent) != NULL);

    ecs_entity_t e = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(e != 0);
    test_assert( ecs_get_type(world, parent) != NULL);

    ecs_fini(world);
}

void Hierarchies_rematch_after_add_to_recycled_parent() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query_new(world, "Tag, PARENT:Position");

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);

    ecs_delete(world, parent);
    test_assert( !ecs_is_alive(world, parent));

    parent = ecs_new(world, 0);
    test_assert(parent != 0);

    ecs_entity_t e = ecs_new_w_pair(world, EcsChildOf, parent);
    test_assert(e != 0);
    test_assert( ecs_has_pair(world, e, EcsChildOf, parent));
    ecs_add(world, e, Tag);

    ecs_iter_t it = ecs_query_iter(q);
    test_bool(ecs_query_next(&it), false);

    ecs_set(world, parent, Position, {10, 20});

    ecs_progress(world, 0);

    it = ecs_query_iter(q);
    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);

    const Position *p = ecs_term(&it, Position, 2);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    test_assert(ecs_term_subject(&it, 2) == parent);

    ecs_fini(world);
}

void Hierarchies_cascade_after_recycled_parent_change() {
    ecs_world_t *world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query_new(world, "Tag, CASCADE:Position");

    ecs_entity_t parent = ecs_new(world, 0);
    test_assert(parent != 0);
    ecs_entity_t child = ecs_new(world, 0);
    test_assert(child != 0);

    ecs_delete(world, parent);
    test_assert( !ecs_is_alive(world, parent));
    ecs_delete(world, child);
    test_assert( !ecs_is_alive(world, child));

    parent = ecs_new_w_entity(world, Tag);
    test_assert(parent != 0);
    child = ecs_new_w_entity(world, Tag);
    test_assert(child != 0);
    ecs_add_pair(world, child, EcsChildOf, parent);

    ecs_entity_t e = ecs_new_w_entity(world, Tag);
    test_assert(e != 0);

    ecs_add_pair(world, e, EcsChildOf, child);
    test_assert( ecs_has_pair(world, e, EcsChildOf, child));

    ecs_iter_t it = ecs_query_iter(q);
    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_assert(it.entities[0] == parent);
    test_assert(ecs_term_subject(&it, 2) == 0);
    const Position *p = ecs_term(&it, Position, 2);
    test_assert(p == NULL);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_assert(it.entities[0] == child);
    test_assert(ecs_term_subject(&it, 2) == 0);
    p = ecs_term(&it, Position, 2);
    test_assert(p == NULL);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_assert(it.entities[0] == e);
    test_assert(ecs_term_subject(&it, 2) == 0);
    p = ecs_term(&it, Position, 2);
    test_assert(p == NULL);

    test_bool(ecs_query_next(&it), false);

    ecs_set(world, parent, Position, {10, 20});
    ecs_set(world, child, Position, {20, 30});

    ecs_progress(world, 0);

    it = ecs_query_iter(q);
    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_assert(it.entities[0] == parent);
    test_assert(ecs_term_subject(&it, 2) == 0);
    p = ecs_term(&it, Position, 2);
    test_assert(p == NULL);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_assert(it.entities[0] == child);
    test_assert(ecs_term_subject(&it, 2) == parent);
    p = ecs_term(&it, Position, 2);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_assert(it.entities[0] == e);
    test_assert(ecs_term_subject(&it, 2) == child);
    p = ecs_term(&it, Position, 2);
    test_assert(p != NULL);
    test_int(p->x, 20);
    test_int(p->y, 30);

    test_bool(ecs_query_next(&it), false);

    ecs_fini(world);
}

void Hierarchies_long_name_depth_0() {
    ecs_world_t *world = ecs_init();

    const char *parent_name = "a_parent_entity_with_an_identifier_longer_than_sixty_four_characters";
    test_assert(strlen(parent_name) >= 64);

    ecs_entity_t parent = ecs_entity_init(world, &(ecs_entity_desc_t) {
        .name = parent_name
    });

    test_str(ecs_get_name(world, parent), parent_name);

    ecs_entity_t e = ecs_lookup_fullpath(world, parent_name);
    test_assert(e == parent);

    char *path = ecs_get_fullpath(world, e);
    test_str(path, parent_name);
    ecs_os_free(path);

    ecs_fini(world);
}

void Hierarchies_long_name_depth_1() {
    ecs_world_t *world = ecs_init();

    const char *parent_name = 
        "a_parent_entity_with_an_identifier_longer_than_sixty_four_characters";
    test_assert(strlen(parent_name) >= 64);
    ecs_entity_t parent = ecs_entity_init(world, &(ecs_entity_desc_t) {
        .name = parent_name
    });
    test_str(ecs_get_name(world, parent), parent_name);

    const char *child_name = 
        "a_child_entity_with_an_identifier_longer_than_sixty_four_characters";
    test_assert(strlen(child_name) >= 64);
    ecs_entity_t child = ecs_entity_init(world, &(ecs_entity_desc_t) {
        .name = child_name,
        .add = { ecs_pair(EcsChildOf, parent) }
    });    
    test_str(ecs_get_name(world, child), child_name);

    const char *search_path = 
      "a_parent_entity_with_an_identifier_longer_than_sixty_four_characters."
      "a_child_entity_with_an_identifier_longer_than_sixty_four_characters";

    ecs_entity_t e = ecs_lookup_fullpath(world, search_path);
    test_assert(e == child);

    char *path = ecs_get_fullpath(world, e);
    test_str(path, search_path);
    ecs_os_free(path);

    ecs_fini(world);
}

void Hierarchies_long_name_depth_2() {
    ecs_world_t *world = ecs_init();

    const char *parent_name = 
        "a_parent_entity_with_an_identifier_longer_than_sixty_four_characters";
    test_assert(strlen(parent_name) >= 64);
    ecs_entity_t parent = ecs_entity_init(world, &(ecs_entity_desc_t) {
        .name = parent_name
    });
    test_str(ecs_get_name(world, parent), parent_name);

    const char *child_name = 
        "a_child_entity_with_an_identifier_longer_than_sixty_four_characters";
    test_assert(strlen(child_name) >= 64);
    ecs_entity_t child = ecs_entity_init(world, &(ecs_entity_desc_t) {
        .name = child_name,
        .add = { ecs_pair(EcsChildOf, parent) }
    });    
    test_str(ecs_get_name(world, child), child_name);

    const char *grand_child_name = 
        "a_grand_child_entity_with_an_identifier_longer_than_sixty_four_characters";
    test_assert(strlen(grand_child_name) >= 64);
    ecs_entity_t grand_child = ecs_entity_init(world, &(ecs_entity_desc_t) {
        .name = grand_child_name,
        .add = { ecs_pair(EcsChildOf, child) }
    });    
    test_str(ecs_get_name(world, grand_child), grand_child_name);

    const char *search_path = 
      "a_parent_entity_with_an_identifier_longer_than_sixty_four_characters."
      "a_child_entity_with_an_identifier_longer_than_sixty_four_characters."
      "a_grand_child_entity_with_an_identifier_longer_than_sixty_four_characters";

    ecs_entity_t e = ecs_lookup_fullpath(world, search_path);
    test_assert(e == grand_child);

    char *path = ecs_get_fullpath(world, e);
    test_str(path, search_path);
    ecs_os_free(path);

    ecs_fini(world);
}
