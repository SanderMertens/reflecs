#include "private_api.h"

static const char* mixin_kind_str[] = {
    [EcsMixinBase] = "base (should never be requested by application)",
    [EcsMixinWorld] = "world",
    [EcsMixinCtx] = "ctx",
    [EcsMixinBindingCtx] = "binding_ctx",
    [EcsMixinTerm] = "term",
    [EcsMixinFilter] = "filter",
    [EcsMixinObservable] = "observable",
    [EcsMixinCallback] = "callback",
    [EcsMixinMax] = "max (should never be requested by application)"
};

static
void* get_mixin(
    const ecs_object_t **object_ptr,
    ecs_mixin_kind_t kind)
{
    ecs_assert(object_ptr != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(kind < EcsMixinMax, ECS_INVALID_PARAMETER, NULL);
    
    const ecs_header_t *hdr = *object_ptr;
    ecs_assert(hdr != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(hdr->magic == ECS_OBJECT_MAGIC, ECS_INVALID_PARAMETER, NULL);

    const ecs_mixins_t *mixins = hdr->mixins;
    if (!mixins) {
        /* Object has no mixins */
        goto not_found;
    }

    ecs_size_t offset = mixins->elems[kind];
    if (offset == 0) {
        /* Object has mixins but not the requested one. Try to find the mixin
         * in the object's base */
        goto find_in_base;
    }

    if (offset == -1) {
        /* If offset is -1 the mixin is the object itself. While using offset 0
         * would have been more convenient here, the mixin tables would have to 
         * be prepopulated with -1 (or some other invalid value) which is more 
         * error prone as it requires explicit (static) initialization. */
        return (void*)object_ptr;
    }
    
    /* Object has mixin, return its address */
    return ECS_OFFSET(hdr, offset);

find_in_base:
    /* Mixin wasn't found, find base mixin which can't be the object itself */
    offset = mixins->elems[EcsMixinBase];
    ecs_assert(offset != -1, ECS_INTERNAL_ERROR, NULL);
    
    if (offset) {
        /* If the object has a base, try to find the mixin in the base */
        ecs_object_t *base = *(ecs_object_t**)ECS_OFFSET(hdr, offset);
        if (base) {
            return get_mixin(base, kind);
        }
    }
    
not_found:
    /* Mixin wasn't found for object */
    return NULL;
}

static
void* assert_mixin(
    const ecs_object_t **object_ptr,
    ecs_mixin_kind_t kind)
{
    void *ptr = get_mixin(object_ptr, kind);
    if (!ptr) {
        const ecs_header_t *header = *object_ptr;
        const ecs_mixins_t *mixins = header->mixins;
        ecs_err("%s not available for type %s", 
            mixin_kind_str[kind],
            mixins ? mixins->type_name : "unknown");
        ecs_os_abort();
    }

    return ptr;
}

void _ecs_object_init(
    ecs_object_t *object,
    int32_t type,
    ecs_size_t size,
    ecs_mixins_t *mixins)
{
    ecs_assert(object != NULL, ECS_INVALID_PARAMETER, NULL);

    ecs_header_t *hdr = object;
    memset(object, 0, size);

    hdr->magic = ECS_OBJECT_MAGIC;
    hdr->type = type;
    hdr->mixins = mixins;
}

void _ecs_object_fini(
    ecs_object_t *object,
    int32_t type)
{
    ecs_assert(object != NULL, ECS_INVALID_PARAMETER, NULL);

    ecs_header_t *hdr = object;

    /* Don't deinit object that wasn't initialized */
    ecs_assert(hdr->magic == ECS_OBJECT_MAGIC, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(hdr->type == type, ECS_INVALID_PARAMETER, NULL);
    hdr->magic = 0;
}

#define assert_object(cond, file, line)\
    _ecs_assert((cond), ECS_INVALID_PARAMETER, NULL, #cond, file, line)

void _ecs_object_assert(
    const ecs_object_t *object,
    int32_t type,
    const char *file,
    int32_t line)
{
    assert_object(object != NULL, file, line);
    
    const ecs_header_t *hdr = object;
    assert_object(hdr->magic == ECS_OBJECT_MAGIC, file, line);
    assert_object(hdr->type == type, file, line);
}

bool _ecs_object_is(
    const ecs_object_t *object,
    int32_t type)
{
    ecs_assert(object != NULL, ECS_INVALID_PARAMETER, NULL);

    const ecs_header_t *hdr = object;
    ecs_assert(hdr->magic == ECS_OBJECT_MAGIC, ECS_INVALID_PARAMETER, NULL);
    return hdr->type == type;    
}

const ecs_world_t* ecs_get_world(
    const ecs_object_t *object)
{
    ecs_world_t *world = *(ecs_world_t**)assert_mixin(&object, EcsMixinWorld);
    ecs_object_assert(world, ecs_world_t);
    return world;
}

void* ecs_get_ctx(
    const ecs_object_t *object)
{
    return *(void**)assert_mixin(&object, EcsMixinCtx);
}

void ecs_set_ctx(
    ecs_object_t *object,
    void *context)
{
    *(void**)assert_mixin(
        (const ecs_object_t**)&object, EcsMixinCtx) = context;
}

void* ecs_get_binding_ctx(
    const ecs_object_t *object)
{
    return *(void**)assert_mixin(
        (const ecs_object_t**)&object, EcsMixinBindingCtx);
}

void ecs_set_binding_ctx(
    ecs_object_t *object,
    void *context)
{
    *(void**)assert_mixin(
        (const ecs_object_t**)&object, EcsMixinBindingCtx) = context;
}

ecs_observable_t* ecs_get_observable(
    const ecs_object_t *object)
{
    return (ecs_observable_t*)assert_mixin(&object, EcsMixinObservable);
}
