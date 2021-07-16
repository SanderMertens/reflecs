/**
 * @file sparse.h
 * @brief Sparse set datastructure.
 *
 * This is an implementation of a paged sparse set that stores the payload in
 * the sparse array.
 *
 * A sparse set has a dense and a sparse array. The sparse array is directly
 * indexed by a 64 bit identifier. The sparse element is linked with a dense
 * element, which allows for liveliness checking. The liveliness check itself
 * can be performed by doing (psuedo code):
 *  dense[sparse[sparse_id].dense] == sparse_id
 *
 * To ensure that the sparse array doesn't have to grow to a large size when
 * using large sparse_id's, the sparse set uses paging. This cuts up the array
 * into several pages of 4096 elements. When an element is set, the sparse set
 * ensures that the corresponding page is created. The page associated with an
 * id is determined by shifting a bit 12 bits to the right.
 *
 * The sparse set keeps track of a generation count per id, which is increased
 * each time an id is deleted. The generation is encoded in the returned id.
 *
 * This sparse set implementation stores payload in the sparse array, which is
 * not typical. The reason for this is to guarantee that (in combination with
 * paging) the returned payload pointers are stable. This allows for various
 * optimizations in the parts of the framework that uses the sparse set.
 *
 * The sparse set has been designed so that new ids can be generated in bulk, in
 * an O(1) operation. The way this works is that once a dense-sparse pair is
 * created, it is never unpaired. Instead it is moved to the end of the dense
 * array, and the sparse set stores an additional count to keep track of the
 * last alive id in the sparse set. To generate new ids in bulk, the sparse set
 * only needs to increase this count by the number of requested ids.
 */

#ifndef FLECS_SPARSE_H
#define FLECS_SPARSE_H

#include "flecs/private/api_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Create new sparse set */
FLECS_DBG_API
ecs_sparse_t* _ecs_sparse_new(
    ecs_size_t elem_size);

#define ecs_sparse_new(type)\
    _ecs_sparse_new(sizeof(type))

/** Set id source. This allows the sparse set to use an external variable for
 * issuing and increasing new ids. */
FLECS_DBG_API
void ecs_sparse_set_id_source(
    ecs_sparse_t *sparse,
    uint64_t *id_source);

/** Free sparse set */
FLECS_DBG_API
void ecs_sparse_free(
    ecs_sparse_t *sparse);

/** Remove all elements from sparse set */
FLECS_DBG_API
void ecs_sparse_clear(
    ecs_sparse_t *sparse);

/** Add element to sparse set, this generates or recycles an id */
FLECS_DBG_API
void* _ecs_sparse_add(
    ecs_sparse_t *sparse,
    ecs_size_t elem_size);

#define ecs_sparse_add(sparse, type)\
    ((type*)_ecs_sparse_add(sparse, sizeof(type)))

/** Get last issued id. */
FLECS_DBG_API
uint64_t ecs_sparse_last_id(
    ecs_sparse_t *sparse);

/** Generate or recycle a new id. */
FLECS_DBG_API
uint64_t ecs_sparse_new_id(
    ecs_sparse_t *sparse);

/** Generate or recycle new ids in bulk. The returned pointer points directly to
 * the internal dense array vector with sparse ids. Operations on the sparse set
 * can (and likely will) modify the contents of the buffer. */
FLECS_DBG_API
const uint64_t* ecs_sparse_new_ids(
    ecs_sparse_t *sparse,
    int32_t count);

/** Remove an element */
FLECS_DBG_API
void ecs_sparse_remove(
    ecs_sparse_t *sparse,
    uint64_t index);

/** Remove an element, return pointer to the value in the sparse array */
FLECS_DBG_API
void* _ecs_sparse_remove_get(
    ecs_sparse_t *sparse,
    ecs_size_t elem_size,
    uint64_t index);    

#define ecs_sparse_remove_get(sparse, type, index)\
    ((type*)_ecs_sparse_remove_get(sparse, sizeof(type), index))

/** Override the generation count for a specific id */
FLECS_DBG_API
void ecs_sparse_set_generation(
    ecs_sparse_t *sparse,
    uint64_t index);    

/** Check whether an id has ever been issued. */
FLECS_DBG_API
bool ecs_sparse_exists(
    const ecs_sparse_t *sparse,
    uint64_t index);

/** Test if id is alive, which requires the generation count tp match. */
FLECS_DBG_API
bool ecs_sparse_is_alive(
    const ecs_sparse_t *sparse,
    uint64_t index);

/** Return identifier with current generation set. */
FLECS_DBG_API
uint64_t ecs_sparse_get_current(
    const ecs_sparse_t *sparse,
    uint64_t index);

/** Get value from sparse set by dense id. This function is useful in 
 * combination with ecs_sparse_count for iterating all values in the set. */
FLECS_DBG_API
void* _ecs_sparse_get_dense(
    const ecs_sparse_t *sparse,
    ecs_size_t elem_size,
    int32_t index);

#define ecs_sparse_get_dense(sparse, type, index)\
    ((type*)_ecs_sparse_get_dense(sparse, sizeof(type), index))

/** Get the number of alive elements in the sparse set. */
FLECS_DBG_API
int32_t ecs_sparse_count(
    const ecs_sparse_t *sparse);

/** Return total number of allocated elements in the dense array */
FLECS_DBG_API
int32_t ecs_sparse_size(
    const ecs_sparse_t *sparse);

/** Get element by (sparse) id. The returned pointer is stable for the duration
 * of the sparse set, as it is stored in the sparse array. */
FLECS_DBG_API
void* _ecs_sparse_get(
    const ecs_sparse_t *sparse,
    ecs_size_t elem_size,
    uint64_t index);

#define ecs_sparse_get(sparse, type, index)\
    ((type*)_ecs_sparse_get(sparse, sizeof(type), index))

/** Like get_sparse, but don't care whether element is alive or not. */
FLECS_DBG_API
void* _ecs_sparse_get_any(
    ecs_sparse_t *sparse,
    ecs_size_t elem_size,
    uint64_t index);

#define ecs_sparse_get_any(sparse, type, index)\
    ((type*)_ecs_sparse_get_any(sparse, sizeof(type), index))

/** Get or create element by (sparse) id. */
FLECS_DBG_API
void* _ecs_sparse_ensure(
    ecs_sparse_t *sparse,
    ecs_size_t elem_size,
    uint64_t index);

#define ecs_sparse_ensure(sparse, type, index)\
    ((type*)_ecs_sparse_ensure(sparse, sizeof(type), index))

/** Set value. */
FLECS_DBG_API
void* _ecs_sparse_set(
    ecs_sparse_t *sparse,
    ecs_size_t elem_size,
    uint64_t index,
    void *value);

#define ecs_sparse_set(sparse, type, index, value)\
    ((type*)_ecs_sparse_set(sparse, sizeof(type), index, value))

/** Get pointer to ids (alive and not alive). Use with count() or size(). */
FLECS_DBG_API
const uint64_t* ecs_sparse_ids(
    const ecs_sparse_t *sparse);

/** Set size of the dense array. */
FLECS_DBG_API
void ecs_sparse_set_size(
    ecs_sparse_t *sparse,
    int32_t elem_count);

/** Copy sparse set into a new sparse set. */
FLECS_DBG_API
ecs_sparse_t* ecs_sparse_copy(
    const ecs_sparse_t *src);    

/** Restore sparse set into destination sparse set. */
FLECS_DBG_API
void ecs_sparse_restore(
    ecs_sparse_t *dst,
    const ecs_sparse_t *src);

/** Get memory usage of sparse set. */
FLECS_DBG_API
void ecs_sparse_memory(
    ecs_sparse_t *sparse,
    int32_t *allocd,
    int32_t *used);

FLECS_DBG_API
ecs_sparse_iter_t _ecs_sparse_iter(
    ecs_sparse_t *sparse,
    ecs_size_t elem_size);

#define ecs_sparse_iter(sparse, T)\
    _ecs_sparse_iter(sparse, ECS_SIZEOF(T))

#ifndef FLECS_LEGACY
#define ecs_sparse_each(sparse, T, var, ...)\
    {\
        int var##_i, var##_count = ecs_sparse_count(sparse);\
        for (var##_i = 0; var##_i < var##_count; var##_i ++) {\
            T* var = ecs_sparse_get_dense(sparse, T, var##_i);\
            __VA_ARGS__\
        }\
    }
#endif

#ifdef __cplusplus
}
#endif

#endif
