#include <collections.h>
#include <flecs/private/sparse.h>

void Sparse_setup() {
    ecs_os_set_api_defaults();
}

static
void populate(ecs_sparse_t *sp, int count) {
    int prev_count = ecs_sparse_count(sp);
    int i;
    for (i = 0; i < count; i ++) {
        int *elem = ecs_sparse_add(sp, int);
        test_assert(elem != NULL);
        *elem = i;
    }

    test_int(ecs_sparse_count(sp), count + prev_count);
}

void Sparse_add_1() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    int* elem = ecs_sparse_add(sp, int);
    test_assert(elem != NULL);
    test_int(ecs_sparse_count(sp), 1);
    
    int *ptr = ecs_sparse_get_dense(sp, int, 0);
    test_assert(ptr != NULL);
    test_assert(elem == ptr);

    ecs_sparse_free(sp);
}

void Sparse_add_1_to_empty() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    int* elem = ecs_sparse_add(sp, int);
    test_assert(elem != NULL);
    test_int(ecs_sparse_count(sp), 1);
    
    int *ptr = ecs_sparse_get_dense(sp, int, 0);
    test_assert(ptr != NULL);
    test_assert(elem == ptr);

    ecs_sparse_free(sp);
}

void Sparse_add_1_chunk_size_1() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    int* elem = ecs_sparse_add(sp, int);
    test_assert(elem != NULL);
    test_int(ecs_sparse_count(sp), 1);
    
    int *ptr = ecs_sparse_get_dense(sp, int, 0);
    test_assert(ptr != NULL);
    test_assert(elem == ptr);

    ecs_sparse_free(sp);
}

void Sparse_add_n() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    int* elem1 = ecs_sparse_add(sp, int);
    test_assert(elem1 != NULL);
    test_int(ecs_sparse_count(sp), 1);

    int* elem2 = ecs_sparse_add(sp, int);
    test_assert(elem2 != NULL);
    test_int(ecs_sparse_count(sp), 2);    
    
    int *ptr = ecs_sparse_get_dense(sp, int, 0);
    test_assert(ptr != NULL);
    test_assert(elem1 == ptr);

    ptr = ecs_sparse_get_dense(sp, int, 1);
    test_assert(ptr != NULL);
    test_assert(elem2 == ptr);

    ecs_sparse_free(sp);
}

void Sparse_add_n_chunk_size_1() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    int* elem1 = ecs_sparse_add(sp, int);
    test_assert(elem1 != NULL);
    test_int(ecs_sparse_count(sp), 1);

    int* elem2 = ecs_sparse_add(sp, int);
    test_assert(elem2 != NULL);
    test_int(ecs_sparse_count(sp), 2);    
    
    int *ptr = ecs_sparse_get_dense(sp, int, 0);
    test_assert(ptr != NULL);
    test_assert(elem1 == ptr);

    ptr = ecs_sparse_get_dense(sp, int, 1);
    test_assert(ptr != NULL);
    test_assert(elem2 == ptr);

    ecs_sparse_free(sp);
}

void Sparse_remove() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 3);
    
    const uint64_t *indices = ecs_sparse_ids(sp);
    uint64_t i0 = indices[0];
    uint64_t i1 = indices[2];

    ecs_sparse_remove(sp, 1);
    test_int(ecs_sparse_count(sp), 2);

    test_assert(ecs_sparse_get_dense(sp, int, 0) == ecs_sparse_get(sp, int, i0));
    test_assert(ecs_sparse_get_dense(sp, int, 1) == ecs_sparse_get(sp, int, i1));

    ecs_sparse_free(sp);
}

void Sparse_remove_first() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 3);

    const uint64_t *indices = ecs_sparse_ids(sp);
    uint64_t i0 = indices[1];
    uint64_t i1 = indices[2];

    ecs_sparse_remove(sp, 0);
    test_int(ecs_sparse_count(sp), 2);

    test_assert(ecs_sparse_get_dense(sp, int, 0) == ecs_sparse_get(sp, int, i1));
    test_assert(ecs_sparse_get_dense(sp, int, 1) == ecs_sparse_get(sp, int, i0));

    ecs_sparse_free(sp);
}

void Sparse_remove_last() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 3);
    
    const uint64_t *indices = ecs_sparse_ids(sp);
    uint64_t i0 = indices[0];
    uint64_t i1 = indices[1];

    ecs_sparse_remove(sp, 2);
    test_int(ecs_sparse_count(sp), 2);

    test_assert(ecs_sparse_get_dense(sp, int, 0) == ecs_sparse_get(sp, int, i0));
    test_assert(ecs_sparse_get_dense(sp, int, 1) == ecs_sparse_get(sp, int, i1));

    ecs_sparse_free(sp);
}

void Sparse_remove_all() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 3);

    void *elem2 = ecs_sparse_get_dense(sp, int, 1);
    void *elem3 = ecs_sparse_get_dense(sp, int, 2);

    ecs_sparse_remove(sp, 0);
    test_int(ecs_sparse_count(sp), 2);
    test_assert(ecs_sparse_get(sp, int, 0) == NULL);
    test_assert(ecs_sparse_get(sp, int, 1) == elem2);
    test_assert(ecs_sparse_get(sp, int, 2) == elem3);

    ecs_sparse_remove(sp, 1);
    test_int(ecs_sparse_count(sp), 1);
    test_assert(ecs_sparse_get(sp, int, 0) == NULL);
    test_assert(ecs_sparse_get(sp, int, 1) == NULL);
    test_assert(ecs_sparse_get(sp, int, 2) == elem3);    

    ecs_sparse_remove(sp, 2);
    test_int(ecs_sparse_count(sp), 0);
    test_assert(ecs_sparse_get(sp, int, 0) == NULL);
    test_assert(ecs_sparse_get(sp, int, 1) == NULL);
    test_assert(ecs_sparse_get(sp, int, 2) == NULL);    

    ecs_sparse_free(sp);
}

void Sparse_remove_all_n_chunks() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 128);

    int i;
    for (i = 0; i < 128; i ++) {
        ecs_sparse_remove(sp, i);
        test_int(ecs_sparse_count(sp), 127 - i);
    }

    ecs_sparse_free(sp);
}

void Sparse_clear_1() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 1);

    ecs_sparse_clear(sp);
    test_int(ecs_sparse_count(sp), 0);

    ecs_sparse_free(sp);
}

void Sparse_clear_empty() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    ecs_sparse_clear(sp);
    test_int(ecs_sparse_count(sp), 0);

    ecs_sparse_free(sp);
}

void Sparse_clear_n() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 3);

    ecs_sparse_clear(sp);
    test_int(ecs_sparse_count(sp), 0);

    ecs_sparse_free(sp);
}

void Sparse_clear_n_chunks() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 128);

    ecs_sparse_clear(sp);
    test_int(ecs_sparse_count(sp), 0);

    ecs_sparse_free(sp);
}

void Sparse_memory_null() {
    int32_t allocd = 0, used = 0; 
    ecs_sparse_memory(NULL, &allocd, &used);
    test_int(allocd, 0);
    test_int(used, 0);
}

void Sparse_copy() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 128);
    test_int(ecs_sparse_count(sp), 128);

    ecs_sparse_t *sp2 = ecs_sparse_copy(sp);
    ecs_sparse_free(sp);
    test_int(ecs_sparse_count(sp2), 128);

    int i;
    for (i = 0; i < 128; i ++) {
        test_int(*ecs_sparse_get(sp2, int, i), i);
    }

    ecs_sparse_free(sp2);
}

void Sparse_restore() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 128);
    test_int(ecs_sparse_count(sp), 128);

    ecs_sparse_t *sp2 = ecs_sparse_copy(sp);
    test_int(ecs_sparse_count(sp2), 128);

    populate(sp, 128);
    test_int(ecs_sparse_count(sp), 256);

    ecs_sparse_restore(sp, sp2);
    test_int(ecs_sparse_count(sp), 128);

    int i;
    for (i = 0; i < 128; i ++) {
        test_int(*ecs_sparse_get(sp, int, i), i);
    }

    ecs_sparse_free(sp);
    ecs_sparse_free(sp2);
}

void Sparse_add_after_clear() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    populate(sp, 1);

    ecs_sparse_clear(sp);
    test_int(ecs_sparse_count(sp), 0);

    int* elem = ecs_sparse_add(sp, int);
    test_assert(elem != NULL);
    *elem = 10;

    const uint64_t *indices = ecs_sparse_ids(sp);
    test_assert(indices != NULL);

    int *ptr = ecs_sparse_get(sp, int, indices[0]);
    test_assert(ptr != NULL);
    test_assert(ptr == elem);
    test_int(*ptr, 10);

    ecs_sparse_free(sp);
}

void Sparse_create_delete() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    uint64_t id = ecs_sparse_new_id(sp);
    test_int(ecs_sparse_count(sp), 1);

    ecs_sparse_remove(sp, id);
    test_int(ecs_sparse_count(sp), 0);
    test_assert(!ecs_sparse_is_alive(sp, id));

    ecs_sparse_free(sp);
}

void Sparse_create_delete_2() {
    ecs_sparse_t *sp = ecs_sparse_new(int);
    test_assert(sp != NULL);
    test_int(ecs_sparse_count(sp), 0);

    uint64_t id_1 = ecs_sparse_new_id(sp);
    test_int(ecs_sparse_count(sp), 1);
    test_assert(ecs_sparse_is_alive(sp, id_1));
    
    uint64_t id_2 = ecs_sparse_new_id(sp);
    test_int(ecs_sparse_count(sp), 2);
    test_assert(ecs_sparse_is_alive(sp, id_2));

    ecs_sparse_remove(sp, id_1);
    test_int(ecs_sparse_count(sp), 1);
    test_assert(!ecs_sparse_is_alive(sp, id_1));

    ecs_sparse_remove(sp, id_2);
    test_int(ecs_sparse_count(sp), 0);
    test_assert(!ecs_sparse_is_alive(sp, id_2));

    ecs_sparse_free(sp);
}

void Sparse_count_of_null() {
    test_int(ecs_sparse_count(NULL), 0);
}

void Sparse_size_of_null() {
    test_int(ecs_sparse_size(NULL), 0);
}

void Sparse_copy_null() {
    test_assert(ecs_sparse_copy(NULL) == NULL);
}
