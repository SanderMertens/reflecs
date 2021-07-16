#include <api.h>

void Query_query_changed_after_new() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_new(world, Position);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_fini(world);
}

void Query_query_changed_after_delete() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_entity_t e1 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_delete(world, e1);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_fini(world);
}

void Query_query_changed_after_add() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_entity_t e1 = ecs_new(world, 0);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_add(world, e1, Position);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_fini(world);
}

void Query_query_changed_after_remove() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_entity_t e1 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_remove(world, e1, Position);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_fini(world);
}

void Query_query_changed_after_set() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_entity_t e1 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_set(world, e1, Position, {10, 20});
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_fini(world);
}

void Query_query_change_after_modified() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_entity_t e1 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_modified(world, e1, Position);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_fini(world);
}

void Sys(ecs_iter_t *it) { }

void Query_query_change_after_out_system() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, Sys, EcsOnUpdate, [out] Position);
    
    ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_progress(world, 0);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_fini(world);
}

void Query_query_change_after_in_system() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, Sys, EcsOnUpdate, [in] Position);
    
    ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);
    test_assert(ecs_query_changed(q) == true);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_progress(world, 0);
    test_assert(ecs_query_changed(q) == false);

    ecs_query_iter(q);
    test_assert(ecs_query_changed(q) == false);

    ecs_fini(world);
}

void Query_subquery_match_existing() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_bulk_new(world, Position, 3);
    ecs_bulk_new(world, Velocity, 3);
    ecs_bulk_new(world, Type, 3);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);

    ecs_query_t *sq = ecs_subquery_new(world, q, "Velocity");
    test_assert(sq != NULL);

    int32_t table_count = 0, entity_count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        table_count ++;
        entity_count += it.count;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_has(world, it.entities[i], Position));
        }
    }

    test_int(table_count, 2);
    test_int(entity_count, 6);

    table_count = 0, entity_count = 0;
    it = ecs_query_iter(sq);
    while (ecs_query_next(&it)) {
        table_count ++;
        entity_count += it.count;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_has(world, it.entities[i], Position));
            test_assert(ecs_has(world, it.entities[i], Velocity));
        }
    } 

    test_int(table_count, 1);
    test_int(entity_count, 3); 

    ecs_query_free(sq); 

    ecs_fini(world);
}

void Query_subquery_match_new() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);

    ecs_query_t *sq = ecs_subquery_new(world, q, "Velocity");
    test_assert(sq != NULL);

    ECS_TYPE(world, Type, Position, Velocity);
    ecs_bulk_new(world, Position, 3);
    ecs_bulk_new(world, Velocity, 3);
    ecs_bulk_new(world, Type, 3);

    int32_t table_count = 0, entity_count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        table_count ++;
        entity_count += it.count;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_has(world, it.entities[i], Position));
        }
    }

    test_int(table_count, 2);
    test_int(entity_count, 6);

    table_count = 0, entity_count = 0;
    it = ecs_query_iter(sq);
    while (ecs_query_next(&it)) {
        table_count ++;
        entity_count += it.count;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_has(world, it.entities[i], Position));
            test_assert(ecs_has(world, it.entities[i], Velocity));
        }
    } 

    test_int(table_count, 1);
    test_int(entity_count, 3);  

    ecs_query_free(sq);

    ecs_fini(world);
}

void Query_subquery_inactive() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_TYPE(world, Type, Position, Velocity);
    ecs_bulk_new(world, Position, 3);
    ecs_bulk_new(world, Velocity, 3);
    ecs_entity_t e = ecs_new(world, Type);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);

    ecs_query_t *sq = ecs_subquery_new(world, q, "Velocity");
    test_assert(sq != NULL);
    
    /* Create an empty table which should deactivate it for both queries */
    ecs_delete(world, e);

    int32_t table_count = 0, entity_count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        table_count ++;
        entity_count += it.count;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_has(world, it.entities[i], Position));
        }
    }

    test_int(table_count, 1);
    test_int(entity_count, 3);

    table_count = 0, entity_count = 0;
    it = ecs_query_iter(sq);
    test_int(it.table_count, 0);

    table_count = 0, entity_count = 0;
    it = ecs_query_iter(sq);
    while (ecs_query_next(&it)) {
        table_count ++;
    }

    test_int(table_count, 0);

    ecs_query_free(sq);

    ecs_fini(world);
}

void Query_subquery_unmatch() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t parent = ecs_new(world, 0);
    ecs_add(world, parent, Position);

    ecs_entity_t e1 = ecs_new(world, 0);
    ecs_add(world, e1, Position);
    ecs_add(world, e1, Velocity);
    ecs_add_pair(world, e1, EcsChildOf, parent);

    ecs_entity_t e2 = ecs_new(world, 0);
    ecs_add(world, e2, Position);
    ecs_add_pair(world, e2, EcsChildOf, parent);

    ecs_query_t *q = ecs_query_new(world, "Position, PARENT:Position");
    test_assert(q != NULL);

    ecs_query_t *sq = ecs_subquery_new(world, q, "Velocity");
    test_assert(sq != NULL);

    int32_t table_count = 0, entity_count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        table_count ++;
        entity_count += it.count;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_has(world, it.entities[i], Position));
        }
    }

    test_int(table_count, 2);  
    test_int(entity_count, 2);

    table_count = 0, entity_count = 0;
    it = ecs_query_iter(sq);
    while (ecs_query_next(&it)) {
        table_count ++;
        entity_count += it.count;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_has(world, it.entities[i], Position));
            test_assert(ecs_has(world, it.entities[i], Velocity));
        }
    }

    test_int(table_count, 1);
    test_int(entity_count, 1);

    /* Query now no longer match */
    ecs_remove(world, parent, Position);

    /* Force rematching */
    ecs_progress(world, 0);

    /* Test if tables have been unmatched */
    it = ecs_query_iter(q);
    test_int(it.table_count, 0);

    it = ecs_query_iter(sq);
    test_int(it.table_count, 0);

    ecs_query_free(sq);

    ecs_fini(world);
}

void Query_subquery_rematch() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t parent = ecs_new(world, 0);
    ecs_add(world, parent, Position);

    ecs_entity_t e1 = ecs_new(world, 0);
    ecs_add(world, e1, Position);
    ecs_add(world, e1, Velocity);
    ecs_add_pair(world, e1, EcsChildOf, parent);

    ecs_entity_t e2 = ecs_new(world, 0);
    ecs_add(world, e2, Position);
    ecs_add_pair(world, e2, EcsChildOf, parent);

    ecs_query_t *q = ecs_query_new(world, "Position, PARENT:Position");
    test_assert(q != NULL);

    ecs_query_t *sq = ecs_subquery_new(world, q, "Velocity");
    test_assert(sq != NULL);

    int32_t table_count = 0, entity_count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        table_count ++;
        entity_count += it.count;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_has(world, it.entities[i], Position));
        }
    }

    test_int(table_count, 2);  
    test_int(entity_count, 2);

    table_count = 0, entity_count = 0;
    it = ecs_query_iter(sq);
    while (ecs_query_next(&it)) {
        table_count ++;
        entity_count += it.count;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_has(world, it.entities[i], Position));
            test_assert(ecs_has(world, it.entities[i], Velocity));
        }
    }

    test_int(table_count, 1);
    test_int(entity_count, 1);

    /* Query now no longer match */
    ecs_remove(world, parent, Position);

    /* Force unmatching */
    ecs_progress(world, 0);

    /* Test if tables have been unmatched */
    it = ecs_query_iter(q);
    test_int(it.table_count, 0);

    it = ecs_query_iter(sq);
    test_int(it.table_count, 0);

    /* Rematch queries */
    ecs_add(world, parent, Position);    

    /* Force rematching */
    ecs_progress(world, 0);

    /* Test if tables have been rematched */
    it = ecs_query_iter(q);
    test_int(it.table_count, 2);

    it = ecs_query_iter(sq);
    test_int(it.table_count, 1);    

    ecs_query_free(sq);

    ecs_fini(world);
}

void Query_subquery_rematch_w_parent_optional() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_entity_t parent = ecs_new(world, 0);

    ecs_entity_t e1 = ecs_new(world, 0);
    ecs_add(world, e1, Position);
    ecs_add(world, e1, Velocity);
    ecs_add_pair(world, e1, EcsChildOf, parent);

    ecs_entity_t e2 = ecs_new(world, 0);
    ecs_add(world, e2, Position);
    ecs_add_pair(world, e2, EcsChildOf, parent);

    ecs_query_t *q = ecs_query_new(world, "Position, ?PARENT:Position");
    test_assert(q != NULL);

    ecs_query_t *sq = ecs_subquery_new(world, q, "Velocity");
    test_assert(sq != NULL);

    ecs_iter_t it = ecs_query_iter(q);
    test_int(it.table_count, 2);

    it = ecs_query_iter(sq);
    test_int(it.table_count, 1);

    /* Trigger rematch */
    ecs_add(world, parent, Position);
    ecs_progress(world, 0);

    /* Tables should be matched */
    it = ecs_query_iter(q);
    test_int(it.table_count, 3);

    it = ecs_query_iter(sq);
    test_int(it.table_count, 1);

    ecs_query_free(sq);

    ecs_fini(world);
}

void Query_subquery_rematch_w_sub_optional() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_entity_t parent = ecs_new(world, 0);
    // ecs_add(world, parent, Position);

    ecs_entity_t e1 = ecs_new(world, 0);
    ecs_add(world, e1, Position);
    ecs_add(world, e1, Velocity);
    ecs_add_pair(world, e1, EcsChildOf, parent);

    ecs_entity_t e2 = ecs_new(world, 0);
    ecs_add(world, e2, Position);
    ecs_add_pair(world, e2, EcsChildOf, parent);

    ecs_query_t *q = ecs_query_new(world, "Position, ?PARENT:Position");
    test_assert(q != NULL);

    ecs_query_t *sq = ecs_subquery_new(world, q, "Velocity, ?Mass");
    test_assert(sq != NULL);

    ecs_iter_t it = ecs_query_iter(q);
    test_int(it.table_count, 2);

    it = ecs_query_iter(sq);
    test_int(it.table_count, 1);

    /* Trigger rematch */
    ecs_add(world, parent, Position);
    ecs_progress(world, 0);

    /* Tables should be matched */
    it = ecs_query_iter(q);
    test_int(it.table_count, 3);

    it = ecs_query_iter(sq);
    test_int(it.table_count, 1);

    ecs_query_free(sq);

    ecs_fini(world);
}

void Query_query_single_pairs() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TAG(world, Pair);

    ECS_ENTITY(world, e1, PAIR|Pair>Position);
    ECS_ENTITY(world, e2, PAIR|Pair>Velocity);
    ECS_ENTITY(world, e3, Position);
    ECS_ENTITY(world, e4, Velocity);

    int32_t table_count = 0, entity_count = 0;

    ecs_query_t *q = ecs_query_new(world, "PAIR | Pair > Velocity");
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        table_count ++;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] == e2);
            entity_count ++;
        }
    }

    test_int(table_count, 1);
    test_int(entity_count, 1);

    ecs_fini(world);
}

void Query_query_single_instanceof() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, BaseA, 0);
    ECS_ENTITY(world, BaseB, 0);
    ECS_ENTITY(world, e1, INSTANCEOF | BaseB);
    ECS_ENTITY(world, e2, INSTANCEOF | BaseA);

    int32_t table_count = 0, entity_count = 0;

    ecs_query_t *q = ecs_query_new(world, "INSTANCEOF | BaseA");
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        table_count ++;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] == e2);
            entity_count ++;
        }
    }

    test_int(table_count, 1);
    test_int(entity_count, 1);

    ecs_fini(world);
}

void Query_query_single_childof() {
    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, BaseA, 0);
    ECS_ENTITY(world, BaseB, 0);
    ECS_ENTITY(world, e1, CHILDOF | BaseB);
    ECS_ENTITY(world, e2, CHILDOF | BaseA);

    int32_t table_count = 0, entity_count = 0;

    ecs_query_t *q = ecs_query_new(world, "CHILDOF | BaseA");
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        table_count ++;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] == e2);
            entity_count ++;
        }
    }

    test_int(table_count, 1);
    test_int(entity_count, 1);

    ecs_fini(world);
}

void Query_query_w_filter() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_new(world, Position);
    ecs_add(world, ecs_new(world, 
        Position), 
        Velocity);

    ecs_query_t *q = ecs_query_new(world, "Position");
    ecs_filter_t f = {
        .include = ecs_type(Velocity)
    };

    ecs_iter_t it = ecs_query_iter(q);
    int32_t table_count = 0, entity_count = 0;
    while (ecs_query_next_w_filter(&it, &f)) {
        table_count ++;

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            ecs_entity_t e = it.entities[i];
            test_assert(ecs_has(world, e, Position));
            test_assert(ecs_has(world, e, Velocity));
            entity_count ++;
        }
    }

    test_int(table_count, 1);
    test_int(entity_count, 1);

    ecs_fini(world);
}

void Query_query_optional_owned() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t base = ecs_new(world, Velocity);
    
    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add_pair(world, e1, EcsIsA, base);

    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);

    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position, ?Velocity");
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(q);
    int32_t count = 0;
    
    while (ecs_query_next(&it)) {
        Position *p = ecs_term(&it, Position, 1);
        Velocity *v = ecs_term(&it, Velocity, 2);
        
        test_int(it.count, 1);
        test_assert(p != NULL);

        if (it.entities[0] == e1) {
            test_assert(v == NULL);
        } else if (it.entities[0] == e2) {
            test_assert(v != NULL);
        } else if (it.entities[0] == e3) {
            test_assert(v == NULL);
        }

        count ++;
    }

    test_int(count, 3);

    ecs_fini(world);
}

void Query_query_optional_shared() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t base = ecs_new(world, Velocity);
    
    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add_pair(world, e1, EcsIsA, base);

    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);

    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position, ?SHARED:Velocity");
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(q);
    int32_t count = 0;
    
    while (ecs_query_next(&it)) {
        Position *p = ecs_term(&it, Position, 1);
        Velocity *v = ecs_term(&it, Velocity, 2);
        
        test_int(it.count, 1);
        test_assert(p != NULL);
        
        if (it.entities[0] == e1) {
            test_assert(v != NULL);
        } else if (it.entities[0] == e2) {
            test_assert(v == NULL);
        } else if (it.entities[0] == e3) {
            test_assert(v == NULL);
        }

        count ++;
    }

    test_int(count, 3);

    ecs_fini(world);
}

void Query_query_optional_shared_nested() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t base_base = ecs_new(world, Velocity);
    ecs_entity_t base = ecs_new(world, 0);
    ecs_add_pair(world, base, EcsIsA, base_base);
    
    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add_pair(world, e1, EcsIsA, base);

    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);

    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position, ?SHARED:Velocity");
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(q);
    int32_t count = 0;
    
    while (ecs_query_next(&it)) {
        Position *p = ecs_term(&it, Position, 1);
        Velocity *v = ecs_term(&it, Velocity, 2);
        
        test_int(it.count, 1);
        test_assert(p != NULL);
        
        if (it.entities[0] == e1) {
            test_assert(v != NULL);
        } else if (it.entities[0] == e2) {
            test_assert(v == NULL);
        } else if (it.entities[0] == e3) {
            test_assert(v == NULL);
        }

        count ++;
    }

    test_int(count, 3);

    ecs_fini(world);
}

void Query_query_optional_any() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t base = ecs_new(world, Velocity);
    
    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add_pair(world, e1, EcsIsA, base);

    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);

    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position, ?ANY:Velocity");
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(q);
    int32_t count = 0;
    
    while (ecs_query_next(&it)) {
        Position *p = ecs_term(&it, Position, 1);
        Velocity *v = ecs_term(&it, Velocity, 2);
        
        test_int(it.count, 1);
        test_assert(p != NULL);
        
        if (it.entities[0] == e1) {
            test_assert(v != NULL);
            test_assert(!ecs_is_owned(&it, 2));
        } else if (it.entities[0] == e2) {
            test_assert(v != NULL);
            test_assert(ecs_is_owned(&it, 2));
        } else if (it.entities[0] == e3) {
            test_assert(v == NULL);
        }

        count ++;
    }

    test_int(count, 3);

    ecs_fini(world);
}

void Query_query_rematch_optional_after_add() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t base = ecs_new(world, 0);
    
    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add_pair(world, e1, EcsIsA, base);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);
    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position, ?SHARED:Velocity");
    test_assert(q != NULL);

    /* First iteration, base doesn't have Velocity but query should match with
     * entity anyway since the component is optional */
    ecs_iter_t it = ecs_query_iter(q);
    int32_t count = 0;
    
    while (ecs_query_next(&it)) {
        Position *p = ecs_term(&it, Position, 1);
        Velocity *v = ecs_term(&it, Velocity, 2);
        
        test_int(it.count, 1);
        test_assert(p != NULL);
        
        if (it.entities[0] == e1) {
            test_assert(v == NULL);
        } else if (it.entities[0] == e2) {
            test_assert(v == NULL);
        } else if (it.entities[0] == e3) {
            test_assert(v == NULL);
        }

        count ++;
    }
    test_int(count, 3);

    /* Add Velocity to base, should trigger rematch */
    ecs_add(world, base, Velocity);

    /* Trigger a merge, which triggers the rematch */
    ecs_staging_begin(world);
    ecs_staging_end(world);

    /* Second iteration, base has Velocity and entity should be able to access
     * the shared component. */
    it = ecs_query_iter(q);
    count = 0;
    
    while (ecs_query_next(&it)) {
        Position *p = ecs_term(&it, Position, 1);
        Velocity *v = ecs_term(&it, Velocity, 2);
        
        test_int(it.count, 1);
        test_assert(p != NULL);
        
        if (it.entities[0] == e1) {
            test_assert(v != NULL);
        } else if (it.entities[0] == e2) {
            test_assert(v == NULL);
        } else if (it.entities[0] == e3) {
            test_assert(v == NULL);
        }

        count ++;
    }
    test_int(count, 3);    

    ecs_fini(world);    
}

void Query_get_owned_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_new(world, Tag);

    ecs_query_t *q = ecs_query_new(world, "Tag");

    int count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        test_assert(ecs_term_w_size(&it, 0, 1) == NULL);
        test_int(it.count, 1);
        test_int(it.entities[0], e);
        count += it.count;
    }

    test_int(count, 1);

    ecs_fini(world);
}

void Query_get_shared_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t instance = ecs_new_w_pair(world, EcsIsA, base);

    ecs_query_t *q = ecs_query_new(world, "SHARED:Tag");

    int count = 0;
    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        test_assert(ecs_term_w_size(&it, 0, 1) == NULL);
        test_int(it.count, 1);
        test_int(it.entities[0], instance);
        count += it.count;
    }

    test_int(count, 1);

    ecs_fini(world);
}

void Query_explicit_delete() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);

    /* Ensure query isn't deleted twice when deleting world */
    ecs_query_free(q);

    ecs_fini(world);
}

void Query_get_column_size() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_int(ecs_term_size(&it, 1), sizeof(Position));

    ecs_fini(world);    
}

void Query_orphaned_query() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);

    /* Nonsense subquery, doesn't matter, this is just for orphan testing */
    ecs_query_t *sq = ecs_subquery_new(world, q, "Position");
    test_assert(sq != NULL);

    test_assert(!ecs_query_orphaned(sq));

    ecs_query_free(q);

    test_assert(ecs_query_orphaned(sq));
    
    ecs_query_free(sq);

    ecs_fini(world);
}

void Query_nested_orphaned_query() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);

    /* Nonsense subquery, doesn't matter, this is just for orphan testing */
    ecs_query_t *sq = ecs_subquery_new(world, q, "Position");
    test_assert(sq != NULL);

    ecs_query_t *nsq = ecs_subquery_new(world, sq, "Position");
    test_assert(nsq != NULL);    

    test_assert(!ecs_query_orphaned(sq));
    test_assert(!ecs_query_orphaned(nsq));

    ecs_query_free(q);

    test_assert(ecs_query_orphaned(sq));
    test_assert(ecs_query_orphaned(nsq));
    
    ecs_query_free(sq);
    ecs_query_free(nsq);

    ecs_fini(world);
}

void Query_invalid_access_orphaned_query() {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    
    ecs_new(world, Position);

    ecs_query_t *q = ecs_query_new(world, "Position");
    test_assert(q != NULL);

    /* Nonsense subquery, doesn't matter, this is just for orphan testing */
    ecs_query_t *sq = ecs_subquery_new(world, q, "Position");
    test_assert(sq != NULL);

    test_assert(!ecs_query_orphaned(sq));

    ecs_query_free(q);

    test_expect_abort();

    ecs_query_iter(sq);  
}

void Query_stresstest_query_free() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Hello);

    ecs_entity_t e = ecs_new_id(world);
    ecs_add(world, e, Foo);
    ecs_add(world, e, Bar);
    ecs_add(world, e, Hello);

    /* Create & delete query to test if query is properly unregistered with
     * the table */

    for (int i = 0; i < 10000; i ++) {
        ecs_query_t *q = ecs_query_new(world, "Foo, Bar, Hello");
        ecs_query_free(q);
    }

    /* If code did not crash, test passes */
    test_assert(true);

    ecs_fini(world);
}

void Query_only_from_entity() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_set(world, 0, EcsName, {"e"});

    ecs_query_t *q = ecs_query_new(world, "e:Tag");
    ecs_iter_t it = ecs_query_iter(q);
    test_assert(!ecs_query_next(&it));

    ecs_add(world, e, Tag);

    it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_assert(ecs_term_subject(&it, 1) == e);
    test_assert(ecs_term_id(&it, 1) == Tag);

    ecs_fini(world);
}

void Query_only_from_singleton() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_set(world, 0, EcsName, {"e"});

    ecs_query_t *q = ecs_query_new(world, "$e");
    ecs_iter_t it = ecs_query_iter(q);
    test_assert(!ecs_query_next(&it));

    ecs_add_id(world, e, e);

    it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_assert(ecs_term_subject(&it, 1) == e);
    test_assert(ecs_term_id(&it, 1) == e);

    ecs_fini(world);
}

void Query_only_not_from_entity() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_set(world, 0, EcsName, {"e"});

    ecs_query_t *q = ecs_query_new(world, "!e:Tag");
    ecs_iter_t it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_assert(ecs_term_subject(&it, 1) == e);
    test_assert(ecs_term_id(&it, 1) == Tag);

    ecs_add(world, e, Tag);

    it = ecs_query_iter(q);
    test_assert(!ecs_query_next(&it));

    ecs_fini(world);
}

void Query_only_not_from_singleton() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_set(world, 0, EcsName, {"e"});

    ecs_query_t *q = ecs_query_new(world, "!$e");
    ecs_iter_t it = ecs_query_iter(q);
    test_assert(ecs_query_next(&it));
    test_assert(ecs_term_subject(&it, 1) == e);
    test_assert(ecs_term_id(&it, 1) == e);

    ecs_add_id(world, e, e);

    it = ecs_query_iter(q);
    test_assert(!ecs_query_next(&it));

    ecs_fini(world);
}

void Query_get_filter() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *q = ecs_query_new(world, "Position, Velocity");
    test_assert(q != NULL);

    const ecs_filter_t *f = ecs_query_get_filter(q);
    test_assert(f != NULL);

    test_int(f->term_count, 2);
    test_int(f->terms[0].id, ecs_id(Position));
    test_int(f->terms[1].id, ecs_id(Velocity));

    ecs_fini(world);
}

static
int32_t group_by_first_id(
    ecs_world_t *world,
    ecs_type_t type,
    ecs_id_t id,
    void *ctx)
{
    ecs_id_t *second = ecs_vector_get(type, ecs_id_t, 1);
    if (!second) {
        return 0;
    }

    return second[0];
}

void Query_group_by() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);
    ECS_COMPONENT(world, Position);    

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t) {
        .filter.terms = {{ecs_id(Position)}},
        .group_by = group_by_first_id
    });

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_add_id(world, e1, TagC);
    ecs_add_id(world, e2, TagB);
    ecs_add_id(world, e3, TagA);

    ecs_iter_t it = ecs_query_iter(q);
    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e2);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);    

    test_bool(ecs_query_next(&it), false);

    ecs_fini(world);
}

static int ctx_value;
static int ctx_value_free_invoked = 0;
static
void ctx_value_free(void *ctx) {
    test_assert(ctx == &ctx_value);
    ctx_value_free_invoked ++;
}

void Query_group_by_w_ctx() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);
    ECS_COMPONENT(world, Position);    

    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t) {
        .filter.terms = {{ecs_id(Position)}},
        .group_by = group_by_first_id,
        .group_by_ctx = &ctx_value,
        .group_by_ctx_free = ctx_value_free
    });

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_add_id(world, e1, TagC);
    ecs_add_id(world, e2, TagB);
    ecs_add_id(world, e3, TagA);

    ecs_iter_t it = ecs_query_iter(q);
    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e2);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e1);    

    test_bool(ecs_query_next(&it), false);

    ecs_query_fini(q);

    test_int(ctx_value_free_invoked, 1);

    ecs_fini(world);
}
