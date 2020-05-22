#include <get_children.h>

typedef int Foo;
typedef int Bar;

void GetChildren(ecs_rows_t *rows) {
    ecs_vector_t **children = rows->param;

    for (int i = 0; i < rows->count; i ++) {
        ecs_entity_t *elem = ecs_vector_add(
            children, 
            ecs_entity_t);
        
        *elem = rows->entities[i];
    }
}

void print_children(ecs_world_t *world, const char *parent_id, ecs_vector_t *children) {
    ecs_entity_t *array = ecs_vector_first(children, ecs_entity_t);

    for (int i = 0; i < ecs_vector_count(children); i ++) {
        printf("Child found: '%s.%s'\n", parent_id, ecs_get_name(world, array[i]));
    }
}

int main(int argc, char *argv[]) {
    /* Create the world, pass arguments for overriding the number of threads,fps
     * or for starting the admin dashboard (see flecs.h for details). */
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    ECS_COMPONENT(world, Foo);
    ECS_COMPONENT(world, Bar);

    ECS_SYSTEM(world, GetChildren, 0, EcsName);

    /* Create two parents */
    ecs_entity_t parent_1 = ecs_new(world, 0);
    ecs_entity_t parent_2 = ecs_new(world, 0);

    /* Get type variables for parents so they can be used as filter */
    ecs_type_t ecs_type(parent_1) = ecs_type_from_entity(world, parent_1);
    ecs_type_t ecs_type(parent_2) = ecs_type_from_entity(world, parent_2);

    /* Create two children for each parent */
    ECS_ENTITY(world, child_1_1, CHILDOF | parent_1, Foo);
    ECS_ENTITY(world, child_1_2, CHILDOF | parent_1, Bar);

    ECS_ENTITY(world, child_2_1, CHILDOF | parent_2, Foo);
    ECS_ENTITY(world, child_2_2, CHILDOF | parent_2, Bar);

    /* Set ids so it's easier to see which children were resolved */
    ecs_set(world, child_1_1, EcsName, {"child_1_1"});
    ecs_set(world, child_1_2, EcsName, {"child_1_2"});
    ecs_set(world, child_2_1, EcsName, {"child_2_1"});
    ecs_set(world, child_2_2, EcsName, {"child_2_2"});

    /* Create vector to store child entities */
    ecs_vector_t *children = ecs_vector_new(ecs_entity_t, 0);

    /* Collect children for parent_1 */
    ecs_run_w_filter(world, GetChildren, 0, 0, 0, 
        parent_1,
        &children);

    print_children(world, "parent_1", children);
    printf("---\n");

    ecs_vector_clear(children);

    /* Collect children for parent_2 */
    ecs_run_w_filter(world, GetChildren, 0, 0, 0, 
        parent_2,
        &children);

    print_children(world, "parent_2", children);

    /* Cleanup */
    ecs_vector_free(children);
    return ecs_fini(world);
}
