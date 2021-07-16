/**
 * @file api_defines.h
 * @brief Supporting defines for the public API.
 *
 * This file contains constants / macro's that are typically not used by an
 * application but support the public API, and therefore must be exposed. This
 * header should not be included by itself.
 */

#ifndef FLECS_API_DEFINES_H
#define FLECS_API_DEFINES_H

/* Standard library dependencies */
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

/* Non-standard but required. If not provided by platform, add manually. */
#include <stdint.h>

/* Contains macro's for importing / exporting symbols */
#include "../bake_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __BAKE_LEGACY__
#define FLECS_LEGACY
#endif

/* Some symbols are only exported when building in debug build, to enable
 * whitebox testing of internal datastructures */
#ifndef NDEBUG
#define FLECS_DBG_API FLECS_API
#else
#define FLECS_DBG_API
#endif

////////////////////////////////////////////////////////////////////////////////
//// Language support defines
////////////////////////////////////////////////////////////////////////////////

#ifndef FLECS_LEGACY
#include <stdbool.h>
#endif

/* The API uses the native bool type in C++, or a custom one in C */
#if !defined(__cplusplus) && !defined(__bool_true_false_are_defined)
#undef bool
#undef true
#undef false
typedef char bool;
#define false 0
#define true !false
#endif

typedef uint32_t ecs_flags32_t;
typedef uint64_t ecs_flags64_t;

/* Keep unsigned integers out of the codebase as they do more harm than good */
typedef int32_t ecs_size_t;

/* Abstraction on top of C-style casts so that C functions can be used in C++
 * code without generating warnings */
#ifndef __cplusplus
#define ECS_CAST(T, V) ((T)(V))
#else
#define ECS_CAST(T, V) (static_cast<T>(V))
#endif

/* Versions of sizeof and offsetof that use ecs_size_t */
#define ECS_SIZEOF(T) ECS_CAST(ecs_size_t, sizeof(T))
#define ECS_OFFSETOF(T, M), ECS_CAST(ecs_size_t, offsetof(T))

/* Use alignof in C++, or a trick in C. */
#ifdef __cplusplus
#define ECS_ALIGNOF(T) static_cast<int64_t>(alignof(T))
#elif defined(_MSC_VER)
#define ECS_ALIGNOF(T) (int64_t)__alignof(T)
#elif defined(__GNUC__)
#define ECS_ALIGNOF(T) (int64_t)__alignof__(T)
#else
#define ECS_ALIGNOF(T) ((int64_t)&((struct { char c; T d; } *)0)->d)
#endif

#if defined(__GNUC__)
#define ECS_UNUSED __attribute__((unused))
#else
#define ECS_UNUSED
#endif

#ifndef FLECS_NO_DEPRECATED_WARNINGS
#if defined(__GNUC__)
#define ECS_DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
#define ECS_DEPRECATED(msg) __declspec(deprecated(msg))
#else
#define ECS_DEPRECATED(msg)
#endif
#else
#define ECS_DEPRECATED(msg)
#endif

#define ECS_ALIGN(size, alignment) (ecs_size_t)((((((size_t)size) - 1) / ((size_t)alignment)) + 1) * ((size_t)alignment))

/* Simple utility for determining the max of two values */
#define ECS_MAX(a, b) ((a > b) ? a : b)

////////////////////////////////////////////////////////////////////////////////
//// Reserved component ids
////////////////////////////////////////////////////////////////////////////////

/** Builtin component ids */
#define FLECS__EEcsComponent (1)
#define FLECS__EEcsComponentLifecycle (2)
#define FLECS__EEcsType (3)
#define FLECS__EEcsName (4)
#define FLECS__EEcsTrigger (5)
#define FLECS__EEcsQuery (6)
#define FLECS__EEcsObserver (7)
#define FLECS__EEcsIterable (8)

/* System module component ids */
#define FLECS__EEcsSystem (10)
#define FLECS__EEcsTickSource (11)

/** Pipeline module component ids */
#define FLECS__EEcsPipelineQuery (12)

/** Timer module component ids */
#define FLECS__EEcsTimer (13)
#define FLECS__EEcsRateFilter (14)


////////////////////////////////////////////////////////////////////////////////
//// Entity id macro's
////////////////////////////////////////////////////////////////////////////////

#define ECS_ROLE_MASK         (0xFFull << 56)
#define ECS_ENTITY_MASK       (0xFFFFFFFFull)
#define ECS_GENERATION_MASK   (0xFFFFull << 32)
#define ECS_GENERATION(e)     ((e & ECS_GENERATION_MASK) >> 32)
#define ECS_GENERATION_INC(e) ((e & ~ECS_GENERATION_MASK) | ((ECS_GENERATION(e) + 1) << 32))
#define ECS_COMPONENT_MASK    (~ECS_ROLE_MASK)
#define ECS_HAS_ROLE(e, role) ((e & ECS_ROLE_MASK) == ECS_##role)
#define ECS_PAIR_RELATION(e)  (ECS_HAS_ROLE(e, PAIR) ? ecs_entity_t_hi(e & ECS_COMPONENT_MASK) :\
    (((e & ECS_ROLE_MASK) == ECS_CHILDOF) ? EcsChildOf :\
        ((e & ECS_ROLE_MASK) == ECS_INSTANCEOF) ? EcsIsA : (e & ECS_ROLE_MASK)))
#define ECS_PAIR_OBJECT(e)    (ecs_entity_t_lo(e))
#define ECS_HAS_PAIR(e, rel)  (ECS_HAS_ROLE(e, PAIR) && (ECS_PAIR_RELATION(e) == rel))

#define ECS_HAS_RELATION(e, rel) (\
    (((rel == ECS_CHILDOF) || (rel == EcsChildOf)) &&\
        (ECS_HAS_ROLE(e, CHILDOF) || ECS_HAS_PAIR(e, EcsChildOf))) ||\
    (((rel == ECS_INSTANCEOF) || (rel == EcsIsA)) &&\
        (ECS_HAS_ROLE(e, INSTANCEOF) || ECS_HAS_PAIR(e, EcsIsA))) ||\
    ECS_HAS_PAIR(e, rel))

#define ECS_HAS_PAIR_OBJECT(e, rel, obj)\
    (ECS_HAS_RELATION(e, rel) && ECS_PAIR_OBJECT(e) == obj)

#define ECS_HAS(id, has_id)(\
    (id == has_id) ||\
    (ECS_HAS_PAIR_OBJECT(id, ECS_PAIR_RELATION(has_id), ECS_PAIR_OBJECT(has_id))))


////////////////////////////////////////////////////////////////////////////////
//// Convert between C typenames and variables
////////////////////////////////////////////////////////////////////////////////

/** Translate C type to ecs_type_t variable. */
#define ecs_type(T) FLECS__T##T

/** Translate C type to id. */
#define ecs_id(T) FLECS__E##T

/** Translate C type to module struct. */
#define ecs_module(T) FLECS__M##T

/** Translate C type to module struct. */
#define ecs_module_ptr(T) FLECS__M##T##_ptr

/** Translate C type to module struct. */
#define ecs_iter_action(T) FLECS__F##T


////////////////////////////////////////////////////////////////////////////////
//// Utilities for working with pair identifiers
////////////////////////////////////////////////////////////////////////////////

#define ecs_entity_t_lo(value) ECS_CAST(uint32_t, value)
#define ecs_entity_t_hi(value) ECS_CAST(uint32_t, (value) >> 32)
#define ecs_entity_t_comb(lo, hi) ((ECS_CAST(uint64_t, hi) << 32) + ECS_CAST(uint32_t, lo))

#define ecs_pair(pred, obj) (ECS_PAIR | ecs_entity_t_comb(obj, pred))

/* Get object from pair with the correct (current) generation count */
#define ecs_pair_relation(world, pair) ecs_get_alive(world, ECS_PAIR_RELATION(pair))
#define ecs_pair_object(world, pair) ecs_get_alive(world, ECS_PAIR_OBJECT(pair))


////////////////////////////////////////////////////////////////////////////////
//// Convenience macro's for ctor, dtor, move and copy
////////////////////////////////////////////////////////////////////////////////

#ifndef FLECS_LEGACY

/* Constructor / destructor convenience macro */
#define ECS_XTOR_IMPL(type, postfix, var, ...)\
    void type##_##postfix(\
        ecs_world_t *world,\
        ecs_entity_t component,\
        const ecs_entity_t *entity_ptr,\
        void *_ptr,\
        size_t _size,\
        int32_t _count,\
        void *ctx)\
    {\
        (void)world;\
        (void)component;\
        (void)entity_ptr;\
        (void)_ptr;\
        (void)_size;\
        (void)_count;\
        (void)ctx;\
        for (int32_t i = 0; i < _count; i ++) {\
            ecs_entity_t entity = entity_ptr[i];\
            type *var = &((type*)_ptr)[i];\
            (void)entity;\
            (void)var;\
            __VA_ARGS__\
        }\
    }

/* Copy convenience macro */
#define ECS_COPY_IMPL(type, dst_var, src_var, ...)\
    void type##_##copy(\
        ecs_world_t *world,\
        ecs_entity_t component,\
        const ecs_entity_t *dst_entities,\
        const ecs_entity_t *src_entities,\
        void *_dst_ptr,\
        const void *_src_ptr,\
        size_t _size,\
        int32_t _count,\
        void *ctx)\
    {\
        (void)world;\
        (void)component;\
        (void)dst_entities;\
        (void)src_entities;\
        (void)_dst_ptr;\
        (void)_src_ptr;\
        (void)_size;\
        (void)_count;\
        (void)ctx;\
        for (int32_t i = 0; i < _count; i ++) {\
            ecs_entity_t dst_entity = dst_entities[i];\
            ecs_entity_t src_entity = src_entities[i];\
            type *dst_var = &((type*)_dst_ptr)[i];\
            type *src_var = &((type*)_src_ptr)[i];\
            (void)dst_entity;\
            (void)src_entity;\
            (void)dst_var;\
            (void)src_var;\
            __VA_ARGS__\
        }\
    }

/* Move convenience macro */
#define ECS_MOVE_IMPL(type, dst_var, src_var, ...)\
    void type##_##move(\
        ecs_world_t *world,\
        ecs_entity_t component,\
        const ecs_entity_t *dst_entities,\
        const ecs_entity_t *src_entities,\
        void *_dst_ptr,\
        void *_src_ptr,\
        size_t _size,\
        int32_t _count,\
        void *ctx)\
    {\
        (void)world;\
        (void)component;\
        (void)dst_entities;\
        (void)src_entities;\
        (void)_dst_ptr;\
        (void)_src_ptr;\
        (void)_size;\
        (void)_count;\
        (void)ctx;\
        for (int32_t i = 0; i < _count; i ++) {\
            ecs_entity_t dst_entity = dst_entities[i];\
            ecs_entity_t src_entity = src_entities[i];\
            type *dst_var = &((type*)_dst_ptr)[i];\
            type *src_var = &((type*)_src_ptr)[i];\
            (void)dst_entity;\
            (void)src_entity;\
            (void)dst_var;\
            (void)src_var;\
            __VA_ARGS__\
        }\
    }
    
#endif


////////////////////////////////////////////////////////////////////////////////
//// Error codes
////////////////////////////////////////////////////////////////////////////////

#define ECS_INVALID_OPERATION (1)
#define ECS_INVALID_PARAMETER (2)
#define ECS_INVALID_DELETE (3)
#define ECS_OUT_OF_MEMORY (4)
#define ECS_OUT_OF_RANGE (5)
#define ECS_UNSUPPORTED (6)
#define ECS_INTERNAL_ERROR (7)
#define ECS_ALREADY_DEFINED (8)
#define ECS_MISSING_OS_API (9)
#define ECS_THREAD_ERROR (10)
#define ECS_CYCLE_DETECTED (11)
#define ECS_RETRIGGER_UNSUPPORTED (12)

#define ECS_INCONSISTENT_NAME (20)
#define ECS_NAME_IN_USE (21)
#define ECS_NOT_A_COMPONENT (22)
#define ECS_INVALID_COMPONENT_SIZE (23)
#define ECS_INVALID_COMPONENT_ALIGNMENT (24)
#define ECS_COMPONENT_NOT_REGISTERED (25)
#define ECS_INCONSISTENT_COMPONENT_ID (26)
#define ECS_INCONSISTENT_COMPONENT_ACTION (27)
#define ECS_MODULE_UNDEFINED (28)

#define ECS_COLUMN_ACCESS_VIOLATION (40)
#define ECS_COLUMN_INDEX_OUT_OF_RANGE (41)
#define ECS_COLUMN_IS_NOT_SHARED (42)
#define ECS_COLUMN_IS_SHARED (43)
#define ECS_COLUMN_HAS_NO_DATA (44)
#define ECS_COLUMN_TYPE_MISMATCH (45)
#define ECS_NO_OUT_COLUMNS (46)

#define ECS_TYPE_NOT_AN_ENTITY (60)
#define ECS_TYPE_CONSTRAINT_VIOLATION (61)
#define ECS_TYPE_INVALID_CASE (62)

#define ECS_INVALID_WHILE_ITERATING (70)
#define ECS_LOCKED_STORAGE (71)
#define ECS_INVALID_FROM_WORKER (72)

#define ECS_DESERIALIZE_FORMAT_ERROR (80)


////////////////////////////////////////////////////////////////////////////////
//// Deprecated constants
////////////////////////////////////////////////////////////////////////////////

/* These constants should no longer be used, but are required by the core to
 * guarantee backwards compatibility */
#define ECS_INSTANCEOF (ECS_ROLE | (0x7Eull << 56))
#define ECS_CHILDOF    (ECS_ROLE | (0x7Dull << 56))
#define ECS_AND (ECS_ROLE | (0x79ull << 56))
#define ECS_OR (ECS_ROLE | (0x78ull << 56))
#define ECS_XOR (ECS_ROLE | (0x77ull << 56))
#define ECS_NOT (ECS_ROLE | (0x76ull << 56))
#define ECS_TRAIT ECS_PAIR

#define EcsSingleton   (ECS_HI_COMPONENT_ID + 37)

#ifdef __cplusplus
}
#endif

#endif
