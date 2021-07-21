#include "private_api.h"

typedef struct ecs_bitset_storage_t {
    ecs_bitset_t bitset;
    ecs_vector_t *data;
} ecs_bitset_storage_t;

ecs_storage_plugin_t ecs_bitset_storage_plugin(void) 
{
    return (ecs_storage_plugin_t) {
        .init = ecs_bitset_storage_init,
        .fini = ecs_bitset_storage_fini,
        .push = ecs_bitset_storage_push,
        .erase = ecs_bitset_storage_erase,
        .swap = ecs_bitset_storage_swap,
        .get = ecs_bitset_storage_get,
        .has = ecs_bitset_storage_has,
        .iter = ecs_bitset_storage_iter,
        .next = ecs_bitset_storage_next
    };
}

ecs_storage_t* ecs_bitset_storage_init(
    ecs_world_t *world,
    ecs_size_t size,
    ecs_size_t alignment)
{
    (void)world;
    
    ecs_bitset_storage_t *result = ecs_os_calloc_t(ecs_bitset_storage_t);
    ecs_assert(result != NULL, ECS_OUT_OF_MEMORY, NULL);

    ecs_bitset_init(&result->bitset);

    if (size) {
        result->data = ecs_vector_new_t(size, alignment, 0);
    }

    return (ecs_storage_t*)result;
}

void ecs_bitset_storage_fini(
    ecs_storage_t *storage)
{
    ecs_bitset_storage_t *ptr = (ecs_bitset_storage_t*)storage;
    ecs_bitset_fini(&ptr->bitset);
    ecs_vector_free(ptr->data);
    ecs_os_free(ptr);
}

void* ecs_bitset_storage_push(
    ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    uint64_t id)
{
    (void)id;

    ecs_bitset_storage_t *ptr = (ecs_bitset_storage_t*)storage;
    ecs_bitset_addn(&ptr->bitset, 1);
    
    if (size) {
        return ecs_vector_add_t(&ptr->data, size, alignment);
    }

    return NULL;
}

void ecs_bitset_storage_erase(
    ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index,
    uint64_t id)
{
    (void)id;

    ecs_bitset_storage_t *ptr = (ecs_bitset_storage_t*)storage;
    ecs_bitset_remove(&ptr->bitset, index);
    
    if (size) {
        ecs_vector_remove_t(ptr->data, size, alignment, index);
    }
}

void ecs_bitset_storage_swap(
    ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index_a,
    int32_t index_b,
    uint64_t id_a,
    uint64_t id_b)
{
    (void)id_a;
    (void)id_b;

    ecs_bitset_storage_t *ptr = (ecs_bitset_storage_t*)storage;
    ecs_bitset_swap(&ptr->bitset, index_a, index_b);

    if (size) {
        void *tmp = ecs_os_alloca(size);
        void *arr = ecs_vector_first_t(ptr->data, size, alignment);
        void *el_a = ECS_OFFSET(arr, size * index_a);
        void *el_b = ECS_OFFSET(arr, size * index_b);

        ecs_os_memcpy(tmp, el_a, size);
        ecs_os_memcpy(el_a, el_b, size);
        ecs_os_memcpy(el_b, tmp, size);
    }
}

void* ecs_bitset_storage_get(
    const ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index,
    uint64_t id)
{
    (void)id;

    ecs_assert(size != 0, ECS_INVALID_PARAMETER, NULL);

    ecs_bitset_storage_t *ptr = (ecs_bitset_storage_t*)storage;
    if (ecs_bitset_get(&ptr->bitset, index)) {
        return ecs_vector_get_t(ptr->data, size, alignment, index);
    }

    return NULL;
}

bool ecs_bitset_storage_has(
    const ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index,
    uint64_t id)
{
    (void)id;
    (void)size;
    (void)alignment;

    ecs_bitset_storage_t *ptr = (ecs_bitset_storage_t*)storage;
    return ecs_bitset_get(&ptr->bitset, index);
}

ecs_storage_iter_t ecs_bitset_storage_iter(
    const ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment)
{
    ecs_bitset_storage_t *ptr = (ecs_bitset_storage_t*)storage;

    return (ecs_storage_iter_t){
        .size = size,
        .alignment = alignment,
        .data = ecs_vector_first_t(ptr->data, size, alignment)
    };
}

#define BS_MAX ((uint64_t)0xFFFFFFFFFFFFFFFF)

bool ecs_bitset_storage_next(
    const ecs_storage_t *storage,
    ecs_storage_iter_t *iter)
{
    ecs_bitset_storage_t *ptr = (ecs_bitset_storage_t*)storage;

    /* Precomputed single-bit test */
    static const uint64_t bitmask[64] = {
    (uint64_t)1 << 0, (uint64_t)1 << 1, (uint64_t)1 << 2, (uint64_t)1 << 3,
    (uint64_t)1 << 4, (uint64_t)1 << 5, (uint64_t)1 << 6, (uint64_t)1 << 7,
    (uint64_t)1 << 8, (uint64_t)1 << 9, (uint64_t)1 << 10, (uint64_t)1 << 11,
    (uint64_t)1 << 12, (uint64_t)1 << 13, (uint64_t)1 << 14, (uint64_t)1 << 15,
    (uint64_t)1 << 16, (uint64_t)1 << 17, (uint64_t)1 << 18, (uint64_t)1 << 19,
    (uint64_t)1 << 20, (uint64_t)1 << 21, (uint64_t)1 << 22, (uint64_t)1 << 23,
    (uint64_t)1 << 24, (uint64_t)1 << 25, (uint64_t)1 << 26, (uint64_t)1 << 27,  
    (uint64_t)1 << 28, (uint64_t)1 << 29, (uint64_t)1 << 30, (uint64_t)1 << 31,
    (uint64_t)1 << 32, (uint64_t)1 << 33, (uint64_t)1 << 34, (uint64_t)1 << 35,  
    (uint64_t)1 << 36, (uint64_t)1 << 37, (uint64_t)1 << 38, (uint64_t)1 << 39,
    (uint64_t)1 << 40, (uint64_t)1 << 41, (uint64_t)1 << 42, (uint64_t)1 << 43,
    (uint64_t)1 << 44, (uint64_t)1 << 45, (uint64_t)1 << 46, (uint64_t)1 << 47,  
    (uint64_t)1 << 48, (uint64_t)1 << 49, (uint64_t)1 << 50, (uint64_t)1 << 51,
    (uint64_t)1 << 52, (uint64_t)1 << 53, (uint64_t)1 << 54, (uint64_t)1 << 55,  
    (uint64_t)1 << 56, (uint64_t)1 << 57, (uint64_t)1 << 58, (uint64_t)1 << 59,
    (uint64_t)1 << 60, (uint64_t)1 << 61, (uint64_t)1 << 62, (uint64_t)1 << 63
    };

    /* Precomputed test to verify if remainder of block is set (or not) */
    static const uint64_t bitmask_remain[64] = {
    BS_MAX, BS_MAX - (BS_MAX >> 63), BS_MAX - (BS_MAX >> 62),
    BS_MAX - (BS_MAX >> 61), BS_MAX - (BS_MAX >> 60), BS_MAX - (BS_MAX >> 59),
    BS_MAX - (BS_MAX >> 58), BS_MAX - (BS_MAX >> 57), BS_MAX - (BS_MAX >> 56), 
    BS_MAX - (BS_MAX >> 55), BS_MAX - (BS_MAX >> 54), BS_MAX - (BS_MAX >> 53), 
    BS_MAX - (BS_MAX >> 52), BS_MAX - (BS_MAX >> 51), BS_MAX - (BS_MAX >> 50), 
    BS_MAX - (BS_MAX >> 49), BS_MAX - (BS_MAX >> 48), BS_MAX - (BS_MAX >> 47), 
    BS_MAX - (BS_MAX >> 46), BS_MAX - (BS_MAX >> 45), BS_MAX - (BS_MAX >> 44), 
    BS_MAX - (BS_MAX >> 43), BS_MAX - (BS_MAX >> 42), BS_MAX - (BS_MAX >> 41), 
    BS_MAX - (BS_MAX >> 40), BS_MAX - (BS_MAX >> 39), BS_MAX - (BS_MAX >> 38), 
    BS_MAX - (BS_MAX >> 37), BS_MAX - (BS_MAX >> 36), BS_MAX - (BS_MAX >> 35), 
    BS_MAX - (BS_MAX >> 34), BS_MAX - (BS_MAX >> 33), BS_MAX - (BS_MAX >> 32), 
    BS_MAX - (BS_MAX >> 31), BS_MAX - (BS_MAX >> 30), BS_MAX - (BS_MAX >> 29), 
    BS_MAX - (BS_MAX >> 28), BS_MAX - (BS_MAX >> 27), BS_MAX - (BS_MAX >> 26), 
    BS_MAX - (BS_MAX >> 25), BS_MAX - (BS_MAX >> 24), BS_MAX - (BS_MAX >> 23), 
    BS_MAX - (BS_MAX >> 22), BS_MAX - (BS_MAX >> 21), BS_MAX - (BS_MAX >> 20), 
    BS_MAX - (BS_MAX >> 19), BS_MAX - (BS_MAX >> 18), BS_MAX - (BS_MAX >> 17), 
    BS_MAX - (BS_MAX >> 16), BS_MAX - (BS_MAX >> 15), BS_MAX - (BS_MAX >> 14), 
    BS_MAX - (BS_MAX >> 13), BS_MAX - (BS_MAX >> 12), BS_MAX - (BS_MAX >> 11), 
    BS_MAX - (BS_MAX >> 10), BS_MAX - (BS_MAX >> 9), BS_MAX - (BS_MAX >> 8), 
    BS_MAX - (BS_MAX >> 7), BS_MAX - (BS_MAX >> 6), BS_MAX - (BS_MAX >> 5), 
    BS_MAX - (BS_MAX >> 4), BS_MAX - (BS_MAX >> 3), BS_MAX - (BS_MAX >> 2),
    BS_MAX - (BS_MAX >> 1)
    };

    int32_t first = iter->offset;
    int32_t last = 0;
    ecs_bitset_t *bs = &ptr->bitset;

    int32_t bs_count = bs->count;
    int32_t bs_block = first >> 6;
    int32_t bs_block_count = ((bs_count - 1) >> 6) + 1;

    if (bs_block >= bs_block_count) {
        goto done;
    }

    uint64_t *bs_data = bs->data;
    int32_t bs_start = first & 0x3F;

    /* Step 1: find the first non-empty block */
    uint64_t v = bs_data[bs_block];
    uint64_t remain = bitmask_remain[bs_start];
    while (!(v & remain)) {
        /* If no elements are remaining, move to next block */
        if ((++bs_block) >= bs_block_count) {
            /* No non-empty blocks left */
            goto done;
        }

        bs_start = 0;
        remain = BS_MAX; /* Test the full block */
        v = bs_data[bs_block];
    }

    /* Step 2: find the first non-empty element in the block */
    while (!(v & bitmask[bs_start])) {
        bs_start ++;

        /* Block was not empty, so bs_start must be smaller than 64 */
        ecs_assert(bs_start < 64, ECS_INTERNAL_ERROR, NULL);
    }
    
    /* Step 3: Find number of contiguous enabled elements after start */
    int32_t bs_end = bs_start, bs_block_end = bs_block;
    
    remain = bitmask_remain[bs_end];
    while ((v & remain) == remain) {
        bs_end = 0;
        bs_block_end ++;

        if (bs_block_end == bs_block_count) {
            break;
        }

        v = bs_data[bs_block_end];
        remain = BS_MAX; /* Test the full block */
    }

    /* Step 4: find remainder of enabled elements in current block */
    if (bs_block_end != bs_block_count) {
        while ((v & bitmask[bs_end])) {
            bs_end ++;
        }
    }

    /* Block was not 100% occupied, so bs_start must be smaller than 64 */
    ecs_assert(bs_end < 64, ECS_INTERNAL_ERROR, NULL);

    /* Step 5: translate to element start/end and make sure that each column
        * range is a subset of the previous one. */
    first = bs_block * 64 + bs_start;
    int32_t cur_last = bs_block_end * 64 + bs_end;
    
    /* No enabled elements found in table */
    if (first == cur_last) {
        goto done;
    }
    
    last = cur_last;
    int32_t elem_count = last - first;

    /* Make sure last element doesn't exceed total number of elements in 
        * the table */
    if (elem_count > bs_count) {
        elem_count = bs_count;
    }
    
    iter->offset = first;
    iter->count = elem_count;

    return true;
done:
    return false;
}
