/**
 * @file deprecated.h
 * @brief The deprecated addon contains deprecated operations.
 */

#ifdef FLECS_DEPRECATED

#ifndef FLECS_DEPRECATED_H
#define FLECS_DEPRECATED_H

#ifdef __cplusplus
extern "C" {
#endif

#define ecs_typeid(T) FLECS__E##T

#define ecs_entity(T) ecs_typeid(T)

#define ecs_trait(comp, trait) (ECS_TRAIT | ecs_entity_t_comb(comp, trait))

#define ecs_add_trait(world, entity, component, trait)\
    ecs_add_entity(world, entity, ecs_trait(component, trait))

#define ecs_remove_trait(world, entity, component, trait)\
    ecs_remove_entity(world, entity, ecs_trait(component, trait))

#define ecs_has_trait(world, entity, component, trait)\
    ecs_has_entity(world, entity, ecs_trait(component, trait))

#ifndef FLECS_LEGACY

#define ecs_set_trait(world, entity, component, trait, ...)\
    ecs_set_ptr_w_entity(world, entity, ecs_trait(ecs_typeid(component), ecs_typeid(trait)), sizeof(trait), &(trait)__VA_ARGS__)

#define ecs_set_trait_tag(world, entity, trait, component, ...)\
    ecs_set_ptr_w_entity(world, entity, ecs_trait(ecs_typeid(component), trait), sizeof(component), &(component)__VA_ARGS__)

#endif

#define ecs_get_trait(world, entity, component, trait)\
    ((trait*)ecs_get_id(world, entity, ecs_trait(ecs_typeid(component), ecs_typeid(trait))))

#define ecs_get_trait_tag(world, entity, trait, component)\
    ((component*)ecs_get_id(world, entity, ecs_trait(ecs_typeid(component), trait)))

#define ECS_PREFAB(world, id, ...) \
    ecs_entity_t id = ecs_entity_init(world, &(ecs_entity_desc_t){\
        .name = #id,\
        .add_expr = #__VA_ARGS__,\
        .add = {EcsPrefab}\
    });\
    (void)id

#define ECS_ENTITY_EXTERN(id)\
    extern ecs_entity_t id

#define ECS_ENTITY_DECLARE(id)\
    ecs_entity_t id

#define ECS_ENTITY_DEFINE(world, id, ...)\
    id = ecs_entity_init(world, &(ecs_entity_desc_t){\
        .name = #id,\
        .add_expr = #__VA_ARGS__\
    });\

#define ECS_ENTITY(world, id, ...)\
    ecs_entity_t id = ecs_entity_init(world, &(ecs_entity_desc_t){\
        .name = #id,\
        .add_expr = #__VA_ARGS__\
    });\
    (void)id

#define ECS_COMPONENT(world, id) \
    ecs_id_t ecs_id(id) = ecs_component_init(world, &(ecs_component_desc_t){\
        .entity = {\
            .name = #id,\
            .symbol = #id\
        },\
        .size = sizeof(id),\
        .alignment = ECS_ALIGNOF(id)\
    });\
    ECS_VECTOR_STACK(FLECS__T##id, ecs_entity_t, &FLECS__E##id, 1);\
    (void)ecs_id(id);\
    (void)ecs_type(id)

#define ECS_COMPONENT_EXTERN(id)\
    extern ecs_id_t ecs_id(id);\
    extern ecs_type_t ecs_type(id)

#define ECS_COMPONENT_DECLARE(id)\
    ecs_id_t ecs_id(id);\
    ecs_type_t ecs_type(id)

#define ECS_COMPONENT_DEFINE(world, id)\
    ecs_id(id) = ecs_component_init(world, &(ecs_component_desc_t){\
        .entity = {\
            .entity = ecs_id(id),\
            .name = #id,\
            .symbol = #id\
        },\
        .size = sizeof(id),\
        .alignment = ECS_ALIGNOF(id)\
    });\
    ecs_type(id) = ecs_type_from_entity(world, ecs_id(id))

#define ECS_TAG(world, id)\
    ecs_entity_t id = ecs_entity_init(world, &(ecs_entity_desc_t){\
        .name = #id,\
        .symbol = #id\
    });\
    ECS_VECTOR_STACK(FLECS__T##id, ecs_entity_t, &id, 1);\
    (void)ecs_type(id)

#define ECS_TAG_EXTERN(id)\
    extern ecs_entity_t id;\
    extern ecs_type_t ecs_type(id)

#define ECS_TAG_DECLARE(id)\
    ecs_entity_t id;\
    ecs_type_t ecs_type(id)

#define ECS_TAG_DEFINE(world, id)\
    id = ecs_entity_init(world, &(ecs_entity_desc_t){\
        .name = #id,\
        .symbol = #id\
    });\
    ecs_type(id) = ecs_type_from_entity(world, id)

#define ECS_TYPE(world, id, ...) \
    ecs_entity_t id = ecs_type_init(world, &(ecs_type_desc_t){\
        .entity.name = #id,\
        .ids_expr = #__VA_ARGS__\
    });\
    ecs_type_t ecs_type(id) = ecs_type_from_entity(world, id);\
    (void)id;\
    (void)ecs_type(id)

#define ECS_TYPE_EXTERN(id)\
    extern ecs_entity_t id;\
    extern ecs_type_t ecs_type(id)

#define ECS_TYPE_DECLARE(id)\
    ecs_entity_t id;\
    ecs_type_t ecs_type(id)

#define ECS_TYPE_DEFINE(world, id, ...)\
    id = ecs_type_init(world, &(ecs_type_desc_t){\
        .entity.name = #id,\
        .ids_expr = #__VA_ARGS__\
    });\
    ecs_type(id) = ecs_type_from_entity(world, id);\

#define ECS_COLUMN(it, type, id, column)\
    ecs_id_t ecs_id(type) = ecs_column_entity(it, column);\
    ecs_type_t ecs_type(type) = ecs_column_type(it, column);\
    type *id = ecs_column(it, type, column);\
    (void)ecs_id(type);\
    (void)ecs_type(type);\
    (void)id

#define ECS_COLUMN_COMPONENT(it, id, column)\
    ecs_id_t ecs_id(id) = ecs_column_entity(it, column);\
    ecs_type_t ecs_type(id) = ecs_column_type(it, column);\
    (void)ecs_id(id);\
    (void)ecs_type(id)

#define ECS_COLUMN_ENTITY(it, id, column)\
    ecs_entity_t id = ecs_column_entity(it, column);\
    ecs_type_t ecs_type(id) = ecs_column_type(it, column);\
    (void)id;\
    (void)ecs_type(id)

#define ECS_IMPORT_COLUMN(it, module, column) \
    module *ecs_module_ptr(module) = ecs_column(it, module, column);\
    ecs_assert(ecs_module_ptr(module) != NULL, ECS_MODULE_UNDEFINED, #module);\
    ecs_assert(!ecs_is_owned(it, column), ECS_COLUMN_IS_NOT_SHARED, NULL);\
    module ecs_module(module) = *ecs_module_ptr(module);\
    module##ImportHandles(ecs_module(module))

#define ecs_new(world, type) ecs_new_w_type(world, ecs_type(type))

#define ecs_bulk_new(world, component, count)\
    ecs_bulk_new_w_type(world, ecs_type(component), count)

#define ecs_add(world, entity, component)\
    ecs_add_type(world, entity, ecs_type(component))

#define ecs_remove(world, entity, type)\
    ecs_remove_type(world, entity, ecs_type(type))

#define ecs_add_remove(world, entity, to_add, to_remove)\
    ecs_add_remove_type(world, entity, ecs_type(to_add), ecs_type(to_remove))

#define ecs_has(world, entity, type)\
    ecs_has_type(world, entity, ecs_type(type))

#define ecs_owns(world, entity, type, owned)\
    ecs_type_owns_type(world, ecs_get_type(world, entity), ecs_type(type), owned)

#define ecs_set_ptr_w_id(world, entity, size, ptr)\
    ecs_set_id(world, entity, size, ptr)

#define ecs_owns_entity(world, entity, id, owned)\
    ecs_type_owns_id(world, ecs_get_type(world, entity), id, owned)

typedef ecs_ids_t ecs_entities_t;

ECS_DEPRECATED("deprecated functionality")
FLECS_API
void ecs_dim_type(
    ecs_world_t *world,
    ecs_type_t type,
    int32_t entity_count);

ECS_DEPRECATED("use ecs_new_w_id")
FLECS_API
ecs_entity_t ecs_new_w_type(
    ecs_world_t *world,
    ecs_type_t type);

ECS_DEPRECATED("use ecs_bulk_new_w_id")
FLECS_API
const ecs_entity_t* ecs_bulk_new_w_type(
    ecs_world_t *world,
    ecs_type_t type,
    int32_t count);

ECS_DEPRECATED("use ecs_add_id")
FLECS_API
void ecs_add_type(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_type_t type);

ECS_DEPRECATED("use ecs_remove_id")
FLECS_API
void ecs_remove_type(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_type_t type);

ECS_DEPRECATED("use ecs_add_remove_id")
FLECS_API
void ecs_add_remove_type(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_type_t to_add,
    ecs_type_t to_remove);

ECS_DEPRECATED("use ecs_has_id")
FLECS_API
bool ecs_has_type(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_type_t type);

ECS_DEPRECATED("use ecs_count_filter")
FLECS_API
int32_t ecs_count_type(
    const ecs_world_t *world,
    ecs_type_t type);

ECS_DEPRECATED("use ecs_count_id")
FLECS_API
int32_t ecs_count_entity(
    const ecs_world_t *world,
    ecs_id_t entity);    

ECS_DEPRECATED("use ecs_count_filter")
FLECS_API
int32_t ecs_count_w_filter(
    const ecs_world_t *world,
    const ecs_filter_t *filter);

ECS_DEPRECATED("use ecs_set_component_actions_w_entity")
FLECS_API
void ecs_set_component_actions_w_entity(
    ecs_world_t *world,
    ecs_id_t id,
    EcsComponentLifecycle *actions);

ECS_DEPRECATED("use ecs_new_w_id")
FLECS_API
ecs_entity_t ecs_new_w_entity(
    ecs_world_t *world,
    ecs_id_t id);

ECS_DEPRECATED("use ecs_bulk_new_w_id")
FLECS_API
const ecs_entity_t* ecs_bulk_new_w_entity(
    ecs_world_t *world,
    ecs_id_t id,
    int32_t count);

ECS_DEPRECATED("use ecs_enable_component_w_id")
FLECS_API 
void ecs_enable_component_w_entity(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id,
    bool enable);

ECS_DEPRECATED("use ecs_is_component_enabled_w_id")
FLECS_API 
bool ecs_is_component_enabled_w_entity(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id);

ECS_DEPRECATED("use ecs_get_id")
FLECS_API
const void* ecs_get_w_id(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id);

ECS_DEPRECATED("use ecs_get_id")
FLECS_API
const void* ecs_get_w_entity(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id);    

ECS_DEPRECATED("use ecs_get_ref_w_id")
FLECS_API
const void* ecs_get_ref_w_entity(
    const ecs_world_t *world,
    ecs_ref_t *ref,
    ecs_entity_t entity,
    ecs_id_t id);

ECS_DEPRECATED("use ecs_get_mut_id")
FLECS_API
void* ecs_get_mut_w_entity(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id,
    bool *is_added); 

ECS_DEPRECATED("use ecs_get_mut_id")
FLECS_API
void* ecs_get_mut_w_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id,
    bool *is_added);     

ECS_DEPRECATED("use ecs_modified_id")
FLECS_API 
void ecs_modified_w_entity(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id);

ECS_DEPRECATED("use ecs_modified_id")
void ecs_modified_w_id(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id);

ECS_DEPRECATED("use ecs_set_id")
FLECS_API
ecs_entity_t ecs_set_ptr_w_entity(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id,
    size_t size,
    const void *ptr);

ECS_DEPRECATED("use ecs_has_id")
FLECS_API
bool ecs_has_entity(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id);

ECS_DEPRECATED("use ecs_id_str")
FLECS_API
size_t ecs_entity_str(
    const ecs_world_t *world,
    ecs_id_t entity,
    char *buffer,
    size_t buffer_len);

ECS_DEPRECATED("use ecs_get_object_w_id(world, entity, EcsChildOf, id)")
FLECS_API
ecs_entity_t ecs_get_parent_w_entity(
    const ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id);

#define ecs_get_parent(world, entity, component)\
    ecs_get_parent_w_entity(world, entity, ecs_typeid(component))

ECS_DEPRECATED("use ecs_get_stage_id")
FLECS_API
int32_t ecs_get_thread_index(
    const ecs_world_t *world);

ECS_DEPRECATED("use ecs_add_id")
FLECS_API
void ecs_add_entity(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_entity_t entity_add);

ECS_DEPRECATED("use ecs_remove_id")
FLECS_API
void ecs_remove_entity(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id);

ECS_DEPRECATED("use ecs_add_id / ecs_remove_id")
FLECS_API
void ecs_add_remove_entity(
    ecs_world_t *world,
    ecs_entity_t entity,
    ecs_id_t id_add,
    ecs_id_t id_remove);    

ECS_DEPRECATED("use ecs_type_from_id")
FLECS_API
ecs_type_t ecs_type_from_entity(
    ecs_world_t *world,
    ecs_entity_t entity);

ECS_DEPRECATED("use ecs_type_to_id")
FLECS_API
ecs_entity_t ecs_type_to_entity(
    const ecs_world_t *world,
    ecs_type_t type);

ECS_DEPRECATED("use ecs_type_has_id")
FLECS_API
bool ecs_type_has_entity(
    const ecs_world_t *world,
    ecs_type_t type,
    ecs_entity_t entity);

ECS_DEPRECATED("use ecs_type_owns_id")
FLECS_API
bool ecs_type_owns_entity(
    const ecs_world_t *world,
    ecs_type_t type,
    ecs_entity_t entity,
    bool owned);

ECS_DEPRECATED("use ecs_term/ecs_term_w_size")
FLECS_API
void* ecs_column_w_size(
    const ecs_iter_t *it,
    size_t size,
    int32_t column);

#define ecs_column(it, T, column)\
    ecs_column_w_size(it, sizeof(T), column)

ECS_DEPRECATED("no replacement")
FLECS_API
int32_t ecs_column_index_from_name(
    const ecs_iter_t *it,
    const char *name);

ECS_DEPRECATED("no replacement")
FLECS_API
void *ecs_element_w_size(
    const ecs_iter_t *it,
    size_t size,
    int32_t column,
    int32_t row);

#define ecs_element(it, type, column, row)\
    ((type*)ecs_element_w_size(it, sizeof(type), column, row))

ECS_DEPRECATED("use ecs_term_subject")
FLECS_API
ecs_entity_t ecs_column_source(
    const ecs_iter_t *it,
    int32_t column);

ECS_DEPRECATED("use ecs_term_id")
FLECS_API
ecs_entity_t ecs_column_entity(
    const ecs_iter_t *it,
    int32_t column);

ECS_DEPRECATED("no replacement")
FLECS_API
ecs_type_t ecs_column_type(
    const ecs_iter_t *it,
    int32_t column);

ECS_DEPRECATED("use ecs_term_size")
FLECS_API
size_t ecs_column_size(
    const ecs_iter_t *it,
    int32_t column);

ECS_DEPRECATED("use ecs_term_is_readonly")
FLECS_API
bool ecs_is_readonly(
    const ecs_iter_t *it,
    int32_t column);

ECS_DEPRECATED("use ecs_term_is_owned")
FLECS_API
bool ecs_is_owned(
    const ecs_iter_t *it,
    int32_t column);

ECS_DEPRECATED("use ecs_iter_column")
FLECS_API
void* ecs_table_column(
    const ecs_iter_t *it,
    int32_t column);

ECS_DEPRECATED("use ecs_iter_column_size")
FLECS_API
size_t ecs_table_column_size(
    const ecs_iter_t *it,
    int32_t column);

ECS_DEPRECATED("use ecs_iter_column_index")
FLECS_API
int32_t ecs_table_component_index(
    const ecs_iter_t *it,
    ecs_entity_t component);

ECS_DEPRECATED("use ecs_set_rate")
FLECS_API
ecs_entity_t ecs_set_rate_filter(
    ecs_world_t *world,
    ecs_entity_t filter,
    int32_t rate,
    ecs_entity_t source);

ECS_DEPRECATED("use ecs_query_init")
FLECS_API
ecs_query_t* ecs_query_new(
    ecs_world_t *world,
    const char *sig);

ECS_DEPRECATED("use ecs_query_init")
FLECS_API
ecs_query_t* ecs_subquery_new(
    ecs_world_t *world,
    ecs_query_t *parent,
    const char *sig);    

ECS_DEPRECATED("use ecs_query_deinit")
FLECS_API
void ecs_query_free(
    ecs_query_t *query);

ECS_DEPRECATED("use ecs_query_init")
FLECS_API
void ecs_query_order_by(
    ecs_world_t *world,
    ecs_query_t *query,
    ecs_entity_t component,
    ecs_order_by_action_t compare);

ECS_DEPRECATED("use ecs_query_init") 
FLECS_API
void ecs_query_group_by(
    ecs_world_t *world,
    ecs_query_t *query,
    ecs_entity_t component,
    ecs_group_by_action_t rank_action);

#ifdef __cplusplus
}
#endif

#endif

#endif
