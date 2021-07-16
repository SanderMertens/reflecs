/**
 * @file api_types.h
 * @brief Supporting types for the public API.
 *
 * This file contains types that are typically not used by an application but 
 * support the public API, and therefore must be exposed. This header should not
 * be included by itself.
 */

#ifndef FLECS_API_TYPES_H
#define FLECS_API_TYPES_H

#include "api_defines.h"

#ifdef __cplusplus
extern "C" {
#endif


////////////////////////////////////////////////////////////////////////////////
//// Opaque types
////////////////////////////////////////////////////////////////////////////////

/** A stage enables modification while iterating and from multiple threads */
typedef struct ecs_stage_t ecs_stage_t;

/** A table is where entities and components are stored */
typedef struct ecs_table_t ecs_table_t;

/** A record stores data to map an entity id to a location in a table */
typedef struct ecs_record_t ecs_record_t;

/** Table column */
typedef struct ecs_column_t ecs_column_t;

/** Table data */
typedef struct ecs_data_t ecs_data_t;

/* Sparse set */
typedef struct ecs_sparse_t ecs_sparse_t;

/* Switch list */
typedef struct ecs_switch_t ecs_switch_t;

/* Mixins */
typedef struct ecs_mixins_t ecs_mixins_t;

////////////////////////////////////////////////////////////////////////////////
//// Non-opaque types
////////////////////////////////////////////////////////////////////////////////

/* Object header */
typedef struct ecs_header_t {
    int32_t magic; /* Magic number verifying it's a flecs object */
    int32_t type;  /* Magic number indicating which type of flecs object */
    ecs_mixins_t *mixins; /* Offset table to optional mixins */
} ecs_header_t;

/** Mixin for emitting events to triggers/observers */
struct ecs_observable_t {
    ecs_sparse_t *triggers;  /* sparse<event, ecs_event_triggers_t> */
};

/** Mixin for iteratable objects */
typedef struct ecs_iterable_t {
    ecs_iter_create_action_t iter;
    ecs_iter_next_action_t next;
} ecs_iterable_t;

/* Entity record */
struct ecs_record_t {
    ecs_table_t *table;  /* Identifies a type (and table) in world */
    int32_t row;         /* Table row of the entity */
};

/** Cached reference. */
struct ecs_ref_t {
    ecs_entity_t entity;    /**< Entity of the reference */
    ecs_entity_t component; /**< Component of the reference */
    void *table;            /**< Last known table */
    int32_t row;            /**< Last known location in table */
    int32_t alloc_count;    /**< Last known alloc count of table */
    ecs_record_t *record;   /**< Pointer to record, if in main stage */
    const void *ptr;        /**< Cached ptr */
};

/** Array of entity ids that, other than a type, can live on the stack */
typedef struct ecs_ids_t {
    ecs_entity_t *array;    /**< An array with entity ids */
    int32_t count;          /**< The number of entities in the array */
} ecs_ids_t;

typedef struct ecs_page_cursor_t {
    int32_t first;
    int32_t count;
} ecs_page_cursor_t;

typedef struct ecs_page_iter_t {
    int32_t offset;
    int32_t limit;
    int32_t remaining;
} ecs_page_iter_t;

/** Scope-iterator specific data */
typedef struct ecs_scope_iter_t {
    ecs_filter_t filter;
    ecs_map_iter_t tables;
    int32_t index;
} ecs_scope_iter_t;

typedef enum ecs_filter_iter_kind_t {
    EcsFilterIterEvalAll,
    EcsFilterIterEvalIndex,
    EcsFilterIterEvalNone,
    EcsFilterIterNoData
} ecs_filter_iter_kind_t;

/** Filter-iterator specific data */
typedef struct ecs_filter_iter_t {
    const ecs_filter_t *filter;
    ecs_filter_iter_kind_t kind;

    /* For EcsFilterIterEvalIndex */ 
    ecs_map_t *table_index;
    ecs_map_t *substitution_index;
    ecs_map_iter_t table_index_iter;
    int32_t table_index_term;

    /* For EcsFilterIterEvalAll */
    ecs_sparse_t *tables;
    int32_t tables_iter;
    int32_t count;
} ecs_filter_iter_t;

/** Query-iterator specific data */
typedef struct ecs_query_iter_t {
    ecs_page_iter_t page_iter;
    ecs_query_t *query;
    int32_t index;
    int32_t sparse_smallest;
    int32_t sparse_first;
    int32_t bitset_first;
} ecs_query_iter_t;  

/** Snapshot-iterator specific data */
typedef struct ecs_snapshot_iter_t {
    ecs_filter_t filter;
    ecs_vector_t *tables; /* ecs_table_leaf_t */
    int32_t index;
} ecs_snapshot_iter_t;

/** Type used for iterating ecs_sparse_t */
typedef struct ecs_sparse_iter_t {
    ecs_sparse_t *sparse;
    const uint64_t *ids;
    ecs_size_t size;
    int32_t i;
    int32_t count;
} ecs_sparse_iter_t;

/* Number of terms for which iterator can store data without allocations */
#define ECS_ITER_TERM_STORAGE_SIZE (8)

typedef struct ecs_iter_private_t {
    int32_t total_count;

    union {
        ecs_scope_iter_t parent;
        ecs_filter_iter_t filter;
        ecs_query_iter_t query;
        ecs_snapshot_iter_t snapshot;
        ecs_map_iter_t map;
        ecs_sparse_iter_t sparse;
    } iter;

    /* Arrays for avoiding allocations below ITER_TERM_STORAGE_SIZE terms */
    ecs_id_t ids_storage[ECS_ITER_TERM_STORAGE_SIZE];
    ecs_entity_t subjects_storage[ECS_ITER_TERM_STORAGE_SIZE];
    ecs_size_t sizes_storage[ECS_ITER_TERM_STORAGE_SIZE];
    ecs_type_t types_storage[ECS_ITER_TERM_STORAGE_SIZE];
    int32_t type_map_storage[ECS_ITER_TERM_STORAGE_SIZE];
    void *columns_storage[ECS_ITER_TERM_STORAGE_SIZE];
} ecs_iter_private_t;

typedef enum EcsMatchFailureReason {
    EcsMatchOk,
    EcsMatchNotASystem,
    EcsMatchSystemIsATask,
    EcsMatchEntityIsDisabled,
    EcsMatchEntityIsPrefab,
    EcsMatchFromSelf,
    EcsMatchFromOwned,
    EcsMatchFromShared,
    EcsMatchFromContainer,
    EcsMatchFromEntity,
    EcsMatchOrFromSelf,
    EcsMatchOrFromOwned,
    EcsMatchOrFromShared,
    EcsMatchOrFromContainer,
    EcsMatchNotFromSelf,
    EcsMatchNotFromOwned,
    EcsMatchNotFromShared,
    EcsMatchNotFromContainer,
} EcsMatchFailureReason;

typedef struct ecs_match_failure_t {
    EcsMatchFailureReason reason;
    int32_t column;
} ecs_match_failure_t;

////////////////////////////////////////////////////////////////////////////////
//// Function types
////////////////////////////////////////////////////////////////////////////////

typedef struct EcsComponentLifecycle EcsComponentLifecycle;

/** Constructor/destructor. Used for initializing / deinitializing components. */
typedef void (*ecs_xtor_t)(
    ecs_world_t *world,
    ecs_entity_t component,
    const ecs_entity_t *entity_ptr,
    void *ptr,
    size_t size,
    int32_t count,
    void *ctx);

/** Copy is invoked when a component is copied into another component. */
typedef void (*ecs_copy_t)(
    ecs_world_t *world,
    ecs_entity_t component,    
    const ecs_entity_t *dst_entity,
    const ecs_entity_t *src_entity,
    void *dst_ptr,
    const void *src_ptr,
    size_t size,
    int32_t count,
    void *ctx);

/** Move is invoked when a component is moved to another component. */
typedef void (*ecs_move_t)(
    ecs_world_t *world,
    ecs_entity_t component,
    const ecs_entity_t *dst_entity,
    const ecs_entity_t *src_entity,
    void *dst_ptr,
    void *src_ptr,
    size_t size,
    int32_t count,
    void *ctx);

/** Copy ctor */
typedef void (*ecs_copy_ctor_t)(
    ecs_world_t *world,
    ecs_entity_t component,
    const EcsComponentLifecycle *callbacks,
    const ecs_entity_t *dst_entity,
    const ecs_entity_t *src_entity,
    void *dst_ptr,
    const void *src_ptr,
    size_t size,
    int32_t count,
    void *ctx);

/** Move ctor */
typedef void (*ecs_move_ctor_t)(
    ecs_world_t *world,
    ecs_entity_t component,
    const EcsComponentLifecycle *callbacks,
    const ecs_entity_t *dst_entity,
    const ecs_entity_t *src_entity,
    void *dst_ptr,
    void *src_ptr,
    size_t size,
    int32_t count,
    void *ctx);


#ifdef __cplusplus
}
#endif

#endif
