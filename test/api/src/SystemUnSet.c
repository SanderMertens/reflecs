#include <api.h>

static
void UnSet(ecs_iter_t *it) {
    probe_system(it);
}

static
void UnSetA(ecs_iter_t *it) {

}

static
void UnSetB(ecs_iter_t *it) {

}

void SystemUnSet_unset_1_of_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Velocity, {1, 2});
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Velocity);
    test_int(ctx.invoked, 0);
    
    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    ctx = (Probe){ 0 };

    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 0);

    ctx = (Probe){ 0 };

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}

void SystemUnSet_unset_1_of_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Velocity, {1, 2});
    test_int(ctx.invoked, 0);
    
    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);    

    ctx = (Probe){ 0 };

    ecs_remove(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ctx = (Probe){ 0 };

    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 0);

    ctx = (Probe){ 0 };

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_fini(world);

    test_int(ctx.invoked, 0);
}

void SystemUnSet_unset_1_of_3() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position, Velocity, Mass);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Position, {10, 20});
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Velocity, {1, 2});
    test_int(ctx.invoked, 0);

    ecs_set(world, e, Mass, {1});
    test_int(ctx.invoked, 0);    
    
    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e);
    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);  
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);        

    ctx = (Probe){ 0 };

    ecs_remove(world, e, Mass);
    test_int(ctx.invoked, 0);

    ctx = (Probe){ 0 };

    ecs_remove(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ctx = (Probe){ 0 };

    ecs_remove(world, e, Position);
    test_int(ctx.invoked, 0);

    ctx = (Probe){ 0 };

    ecs_progress(world, 0);
    test_int(ctx.invoked, 0);

    ecs_fini(world);

    test_int(ctx.invoked, 0);
}

void SystemUnSet_unset_on_delete_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);    

    ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_entity_t e = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_delete(world, e);

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0); 

    ecs_fini(world);
}

void SystemUnSet_unset_on_delete_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);    

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add(world, e1, Velocity);
    test_int(ctx.invoked, 0);

    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);
    test_int(ctx.invoked, 0);

    ecs_entity_t e3 = ecs_new(world, Position);
    ecs_add(world, e3, Velocity);
    test_int(ctx.invoked, 0);

    ecs_delete(world, e3);

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e3);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0); 
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);  

    ecs_fini(world);   
}

void SystemUnSet_unset_on_delete_3() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position, Velocity, Mass);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);    

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add(world, e1, Velocity);
    ecs_add(world, e1, Mass);
    test_int(ctx.invoked, 0);

    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);
    ecs_add(world, e2, Mass);
    test_int(ctx.invoked, 0);

    ecs_entity_t e3 = ecs_new(world, Position);
    ecs_add(world, e3, Velocity);
    ecs_add(world, e3, Mass);
    test_int(ctx.invoked, 0);

    ecs_delete(world, e3);

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e3);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0); 
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0); 
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);  
    
    ecs_fini(world);
}

void SystemUnSet_unset_on_fini_1() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);    

    ecs_entity_t e1 = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_entity_t e2 = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_entity_t e3 = ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_new(world, Velocity);
    test_int(ctx.invoked, 0);

    ecs_fini(world);

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 3);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);      
}

void SystemUnSet_unset_on_fini_2() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);    

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add(world, e1, Velocity);
    test_int(ctx.invoked, 0);

    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);
    test_int(ctx.invoked, 0);

    ecs_entity_t e3 = ecs_new(world, Position);
    ecs_add(world, e3, Velocity);
    test_int(ctx.invoked, 0);

    ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_new(world, Velocity);
    test_int(ctx.invoked, 0);    

    ecs_fini(world);

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 3);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0); 
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);  
}

void SystemUnSet_unset_on_fini_3() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position, Velocity, Mass);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);    

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add(world, e1, Velocity);
    ecs_add(world, e1, Mass);
    test_int(ctx.invoked, 0);

    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);
    ecs_add(world, e2, Mass);
    test_int(ctx.invoked, 0);

    ecs_entity_t e3 = ecs_new(world, Position);
    ecs_add(world, e3, Velocity);
    ecs_add(world, e3, Mass);
    test_int(ctx.invoked, 0);

    ecs_new(world, Position);
    test_int(ctx.invoked, 0);

    ecs_new(world, Velocity);
    test_int(ctx.invoked, 0); 

    ecs_new(world, Mass);
    test_int(ctx.invoked, 0);        

    ecs_fini(world);

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 3);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0); 
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0); 
    test_int(ctx.c[0][2], ecs_typeid(Mass));
    test_int(ctx.s[0][2], 0);         
}

void SystemUnSet_overlapping_unset_systems() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_SYSTEM(world, UnSetA, EcsUnSet, Position);
    ECS_SYSTEM(world, UnSetB, EcsUnSet, Position, Velocity);
    ECS_SYSTEM(world, UnSet, EcsUnSet, Position, Velocity);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);  

    ecs_entity_t e = ecs_new(world, Position);
    ecs_add(world, e, Velocity);
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Velocity);

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, UnSet);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0); 
    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);   

    ecs_fini(world);
}

static
void UnSet_TestComp(ecs_iter_t *it) {
    if (!ecs_get_ctx(it->world)) {
        return;
    }

    probe_system(it);

    test_int(it->count, 1);

    Position *p = ecs_term(it, Position, 1);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);
}

void SystemUnSet_unset_move_to_nonempty_table() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ECS_SYSTEM(world, UnSet_TestComp, EcsUnSet, Position);

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);  

    ecs_new(world, Type);
    test_int(ctx.invoked, 0);

    ecs_new(world, Type);
    test_int(ctx.invoked, 0);

    ecs_entity_t e = ecs_new(world, Type);
    ecs_set(world, e, Position, {10, 20});
    ecs_set(world, e, Velocity, {20, 10});
    test_int(ctx.invoked, 0);

    ecs_entity_t e2 = ecs_new(world, Velocity);
    ecs_set(world, e2, Velocity, {30, 40});
    test_int(ctx.invoked, 0);

    ecs_remove(world, e, Position);

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, UnSet_TestComp);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    /* Prevent system from getting called by fini */
    ecs_set_ctx(world, NULL);

    ecs_fini(world);
}

static
void UnSet_WriteComp(ecs_iter_t *it) {
    if (!ecs_get_ctx(it->world)) {
        return;
    }

    probe_system(it);

    test_int(it->count, 1);

    Position *p = ecs_term(it, Position, 1);
    test_assert(p != NULL);

    Velocity *v = ecs_term(it, Velocity, 2);

    test_int(p->x, 10);
    test_int(p->y, 20);

    test_int(v->x, 1);
    test_int(v->y, 2);

    v->x = 2;
    v->y = 3;
}

void SystemUnSet_write_in_unset() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_SYSTEM(world, UnSet_WriteComp, EcsUnSet, Position, Velocity);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    ecs_set(world, e, Velocity, {1, 2});

    Probe ctx = { 0 };
    ecs_set_ctx(world, &ctx);

    ecs_remove(world, e, Position);

    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.system, UnSet_WriteComp);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e);

    test_int(ctx.c[0][0], ecs_typeid(Position));
    test_int(ctx.s[0][0], 0);

    test_int(ctx.c[0][1], ecs_typeid(Velocity));
    test_int(ctx.s[0][1], 0);    

    /* Prevent system from getting called by fini */
    ecs_set_ctx(world, NULL);    

    const Velocity *v = ecs_get(world, e, Velocity);
    test_int(v->x, 2);
    test_int(v->y, 3);

    ecs_fini(world);
}
