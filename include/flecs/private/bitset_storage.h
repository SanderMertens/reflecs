/**
 * @file bitset.h
 * @brief Bitset storage.
 *
 * Storage implementation for bitset storage.
 */

#ifndef FLECS_BITSET_STORAGE_H
#define FLECS_BITSET_STORAGE_H

#include "flecs/private/api_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

ecs_storage_t* ecs_bitset_storage_init(
    ecs_world_t *world,
    ecs_size_t size,
    ecs_size_t alignment);

void ecs_bitset_storage_fini(
    ecs_storage_t *storage);

void* ecs_bitset_storage_push(
    ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    uint64_t id);

void ecs_bitset_storage_erase(
    ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index,
    uint64_t id);

void ecs_bitset_storage_swap(
    ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index_a,
    int32_t index_b,
    uint64_t id_a,
    uint64_t id_b);

void* ecs_bitset_storage_get(
    const ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index,
    uint64_t id);

bool ecs_bitset_storage_has(
    const ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment,
    int32_t index,
    uint64_t id);

ecs_storage_iter_t ecs_bitset_storage_iter(
    const ecs_storage_t *storage,
    ecs_size_t size,
    ecs_size_t alignment);

bool ecs_bitset_storage_next(
    const ecs_storage_t *storage,
    ecs_storage_iter_t *iter);

ecs_storage_plugin_t ecs_bitset_storage_plugin(void);

#ifdef __cplusplus
}
#endif

#endif