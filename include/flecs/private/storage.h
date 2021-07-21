/**
 * @file storage_plugin.h
 * @brief Storage plugin interface
 *
 * Allows for integration of pluggable storage types.
 */

#ifndef FLECS_STORAGE_H
#define FLECS_STORAGE_H

#include "flecs/private/api_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ecs_storage_t ecs_storage_t;

typedef struct ecs_storage_iter_t {
    void *data;
    ecs_size_t size;
    ecs_size_t alignment;
    int32_t offset;
    int32_t count;
} ecs_storage_iter_t;

typedef ecs_storage_t* (*ecs_storage_init_action_t)(
    ecs_world_t *world,
    ecs_size_t size,
    ecs_size_t alignment);

typedef void (*ecs_storage_fini_action_t)(
    ecs_storage_t *storage);

typedef void* (*ecs_storage_push_action_t)(
    ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    uint64_t id);

typedef void (*ecs_storage_erase_action_t)(
    ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index,
    uint64_t id);

typedef void (*ecs_storage_swap_action_t)(
    ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index_a,
    int32_t index_b,
    uint64_t id_a,
    uint64_t id_b);

typedef void* (*ecs_storage_get_action_t)(
    const ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index,
    uint64_t id);

typedef bool (*ecs_storage_has_action_t)(
    const ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index,
    uint64_t id);    

typedef void* (*ecs_storage_count_action_t)(
    ecs_storage_t *storage);   

typedef ecs_storage_iter_t (*ecs_storage_iter_action_t)(
    const ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment);

typedef bool (*ecs_storage_next_action_t)(
    const ecs_storage_t *storage,
    ecs_storage_iter_t *iter);

typedef struct ecs_storage_plugin_t {
    ecs_storage_init_action_t init;
    ecs_storage_fini_action_t fini;
    ecs_storage_push_action_t push;
    ecs_storage_erase_action_t erase;
    ecs_storage_swap_action_t swap;
    ecs_storage_has_action_t has;
    ecs_storage_get_action_t get;
    ecs_storage_count_action_t count;
    ecs_storage_iter_action_t iter;
    ecs_storage_next_action_t next;
} ecs_storage_plugin_t;

#ifdef __cplusplus
}
#endif

#endif // FLECS_STORAGE_H
