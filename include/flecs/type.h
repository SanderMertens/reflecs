/**
 * @file type.h
 * @brief Type API.
 *
 * This API contains utilities for working with types. Types are vectors of
 * component ids, and are used most prominently in the API to construct filters.
 */

#ifndef FLECS_TYPE_H
#define FLECS_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

FLECS_API
ecs_type_t ecs_type_from_id(
    ecs_world_t *world,
    ecs_entity_t entity);

FLECS_API
ecs_entity_t ecs_type_to_id(
    const ecs_world_t *world,
    ecs_type_t type);

FLECS_API
char* ecs_type_str(
    const ecs_world_t *world,
    ecs_type_t type);  

FLECS_API
ecs_type_t ecs_type_from_str(
    ecs_world_t *world,
    const char *expr);    

FLECS_API
ecs_type_t ecs_type_find(
    ecs_world_t *world,
    ecs_entity_t *array,
    int32_t count);

FLECS_API
ecs_type_t ecs_type_merge(
    ecs_world_t *world,
    ecs_type_t type,
    ecs_type_t type_add,
    ecs_type_t type_remove);

FLECS_API
ecs_type_t ecs_type_add(
    ecs_world_t *world,
    ecs_type_t type,
    ecs_entity_t entity);

FLECS_API
ecs_type_t ecs_type_remove(
    ecs_world_t *world,
    ecs_type_t type,
    ecs_entity_t entity);

FLECS_API
bool ecs_type_has_id(
    const ecs_world_t *world,
    ecs_type_t type,
    ecs_entity_t entity);

FLECS_API
bool ecs_type_has_type(
    const ecs_world_t *world,
    ecs_type_t type,
    ecs_type_t has);

FLECS_API
bool ecs_type_owns_id(
    const ecs_world_t *world,
    ecs_type_t type,
    ecs_entity_t entity,
    bool owned);

FLECS_API
bool ecs_type_owns_type(
    const ecs_world_t *world,
    ecs_type_t type,
    ecs_type_t has,
    bool owned);

FLECS_API
int32_t ecs_type_find_id(
    const ecs_world_t *world,
    ecs_type_t type,
    int32_t offset,
    ecs_entity_t id,
    ecs_entity_t rel,
    int32_t min_depth,
    int32_t max_depth,
    ecs_entity_t *out);

FLECS_API
ecs_entity_t ecs_type_get_entity_for_xor(
    ecs_world_t *world,
    ecs_type_t type,
    ecs_entity_t xor_tag);

FLECS_API
int32_t ecs_type_index_of(
    ecs_type_t type,
    ecs_entity_t component);

FLECS_API
int32_t ecs_type_match(
    ecs_type_t type, 
    int32_t start_index, 
    ecs_entity_t pair);

#ifdef __cplusplus
}
#endif

#endif
