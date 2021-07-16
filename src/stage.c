#include "private_api.h"

static
ecs_op_t* new_defer_op(ecs_stage_t *stage) {
    ecs_op_t *result = ecs_vector_add(&stage->defer_queue, ecs_op_t);
    ecs_os_memset(result, 0, ECS_SIZEOF(ecs_op_t));
    return result;
}

static 
void new_defer_component_ids(
    ecs_op_t *op, 
    const ecs_ids_t *components)
{
    ecs_assert(components != NULL, ECS_INTERNAL_ERROR, NULL);
    
    int32_t components_count = components->count;
    if (components_count == 1) {
        ecs_entity_t component = components->array[0];
        op->component = component;
        op->components = (ecs_ids_t) {
            .array = NULL,
            .count = 1
        };
    } else if (components_count) {
        ecs_size_t array_size = components_count * ECS_SIZEOF(ecs_entity_t);
        op->components.array = ecs_os_malloc(array_size);
        ecs_os_memcpy(op->components.array, components->array, array_size);
        op->components.count = components_count;
    } else {
        op->component = 0;
        op->components = (ecs_ids_t){ 0 };
    }
}

static
bool defer_add_remove(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_op_kind_t op_kind,
    ecs_entity_t entity,
    ecs_ids_t *components)
{
    if (stage->defer) {
        if (components) {
            if (!components->count) {
                return true;
            }
        }

        ecs_op_t *op = new_defer_op(stage);
        op->kind = op_kind;
        op->is._1.entity = entity;

        new_defer_component_ids(op, components);

        if (op_kind == EcsOpNew) {
            world->new_count ++;
        } else if (op_kind == EcsOpAdd) {
            world->add_count ++;
        } else if (op_kind == EcsOpRemove) {
            world->remove_count ++;
        }

        return true;
    } else {
        stage->defer ++;
    }
    
    return false;
}

static
void merge_stages(
    ecs_world_t *world,
    bool force_merge)
{
    bool is_stage = ecs_object_is(world, ecs_stage_t);
    ecs_stage_t *stage = ecs_stage_from_world(&world);

    bool measure_frame_time = world->measure_frame_time;

    ecs_time_t t_start;
    if (measure_frame_time) {
        ecs_os_get_time(&t_start);
    }

    if (is_stage) {
        /* Check for consistency if force_merge is enabled. In practice this
         * function will never get called with force_merge disabled for just
         * a single stage. */
        if (force_merge || stage->auto_merge) {
            ecs_defer_end((ecs_world_t*)stage);
        }
    } else {
        /* Merge stages. Only merge if the stage has auto_merging turned on, or 
         * if this is a forced merge (like when ecs_merge is called) */
        int32_t i, count = ecs_get_stage_count(world);
        for (i = 0; i < count; i ++) {
            ecs_stage_t *s = (ecs_stage_t*)ecs_get_stage(world, i);
            ecs_object_assert(s, ecs_stage_t);

            if (force_merge || s->auto_merge) {
                ecs_defer_end((ecs_world_t*)s);
            }
        }
    }

    ecs_eval_component_monitors(world);

    if (measure_frame_time) {
        world->stats.merge_time_total += 
            (FLECS_FLOAT)ecs_time_measure(&t_start);
    }

    world->stats.merge_count_total ++; 

    /* If stage is asynchronous, deferring is always enabled */
    if (stage->asynchronous) {
        ecs_defer_begin((ecs_world_t*)stage);
    }
}

static
void do_auto_merge(
    ecs_world_t *world)
{
    merge_stages(world, false);
}

static
void do_manual_merge(
    ecs_world_t *world)
{
    merge_stages(world, true);
}

bool ecs_defer_none(
    ecs_world_t *world,
    ecs_stage_t *stage)
{
    (void)world;
    return (++ stage->defer) == 1;
}

bool ecs_defer_modified(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t entity,
    ecs_entity_t component)
{
    (void)world;
    if (stage->defer) {
        ecs_op_t *op = new_defer_op(stage);
        op->kind = EcsOpModified;
        op->component = component;
        op->is._1.entity = entity;
        return true;
    } else {
        stage->defer ++;
    }
    
    return false;
}

bool ecs_defer_clone(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t entity,
    ecs_entity_t src,
    bool clone_value)
{   
    (void)world;
    if (stage->defer) {
        ecs_op_t *op = new_defer_op(stage);
        op->kind = EcsOpClone;
        op->component = src;
        op->is._1.entity = entity;
        op->is._1.clone_value = clone_value;
        return true;
    } else {
        stage->defer ++;
    }
    
    return false;   
}

bool ecs_defer_delete(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t entity)
{
    (void)world;
    if (stage->defer) {
        ecs_op_t *op = new_defer_op(stage);
        op->kind = EcsOpDelete;
        op->is._1.entity = entity;
        world->delete_count ++;
        return true;
    } else {
        stage->defer ++;
    }
    return false;
}

bool ecs_defer_clear(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t entity)
{
    (void)world;
    if (stage->defer) {
        ecs_op_t *op = new_defer_op(stage);
        op->kind = EcsOpClear;
        op->is._1.entity = entity;
        world->clear_count ++;
        return true;
    } else {
        stage->defer ++;
    }
    return false;
}

bool ecs_defer_enable(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t entity,
    ecs_entity_t component,
    bool enable)
{
    (void)world;
    if (stage->defer) {
        ecs_op_t *op = new_defer_op(stage);
        op->kind = enable ? EcsOpEnable : EcsOpDisable;
        op->is._1.entity = entity;
        op->component = component;
        return true;
    } else {
        stage->defer ++;
    }
    return false;
}

bool ecs_defer_bulk_new(
    ecs_world_t *world,
    ecs_stage_t *stage,
    int32_t count,
    const ecs_ids_t *components_ids,
    void **component_data,
    const ecs_entity_t **ids_out)
{
    if (stage->defer) {
        ecs_entity_t *ids = ecs_os_malloc(count * ECS_SIZEOF(ecs_entity_t));
        void **defer_data = NULL;

        world->bulk_new_count ++;

        /* Use ecs_new_id as this is thread safe */
        int i;
        for (i = 0; i < count; i ++) {
            ids[i] = ecs_new_id(world);
        }

        /* Create private copy for component data */
        if (component_data) {
            int c, c_count = components_ids->count;
            ecs_entity_t *components = components_ids->array;
            defer_data = ecs_os_malloc(ECS_SIZEOF(void*) * c_count);
            for (c = 0; c < c_count; c ++) {
                ecs_entity_t comp = components[c];
                const EcsComponent *cptr = ecs_get_component(world, comp);
                ecs_assert(cptr != NULL, ECS_INVALID_PARAMETER, NULL);

                ecs_size_t size = cptr->size;
                void *data = ecs_os_malloc(size * count);
                defer_data[c] = data;

                const ecs_type_info_t *cinfo = NULL;
                ecs_entity_t real_id = ecs_get_typeid(world, comp);
                if (real_id) {
                    cinfo = ecs_get_c_info(world, real_id);
                }
                ecs_xtor_t ctor;
                if (cinfo && (ctor = cinfo->lifecycle.ctor)) {
                    void *ctx = cinfo->lifecycle.ctx;
                    ctor(world, comp, ids, data, ecs_to_size_t(size), count, ctx);
                    ecs_move_t move;
                    if ((move = cinfo->lifecycle.move)) {
                        move(world, comp, ids, ids, data, component_data[c], 
                            ecs_to_size_t(size), count, ctx);
                    } else {
                        ecs_os_memcpy(data, component_data[c], size * count);
                    }
                } else {
                    ecs_os_memcpy(data, component_data[c], size * count);
                }
            }
        }

        /* Store data in op */
        ecs_op_t *op = new_defer_op(stage);
        op->kind = EcsOpBulkNew;
        op->is._n.entities = ids;
        op->is._n.bulk_data = defer_data;
        op->is._n.count = count;
        new_defer_component_ids(op, components_ids);
        *ids_out = ids;

        return true;
    } else {
        stage->defer ++;
    }

    return false;
}

bool ecs_defer_new(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t entity,
    ecs_ids_t *components)
{   
    return defer_add_remove(world, stage, EcsOpNew, entity, components);
}

bool ecs_defer_add(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t entity,
    ecs_ids_t *components)
{   
    return defer_add_remove(world, stage, EcsOpAdd, entity, components);
}

bool ecs_defer_remove(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t entity,
    ecs_ids_t *components)
{
    return defer_add_remove(world, stage, EcsOpRemove, entity, components);
}

bool ecs_defer_set(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_op_kind_t op_kind,
    ecs_entity_t entity,
    ecs_entity_t component,
    ecs_size_t size,
    const void *value,
    void **value_out,
    bool *is_added)
{
    if (stage->defer) {
        world->set_count ++;
        if (!size) {
            const EcsComponent *cptr = ecs_get_component(world, component);
            ecs_assert(cptr != NULL, ECS_INVALID_PARAMETER, NULL);
            size = cptr->size;
        }

        ecs_op_t *op = new_defer_op(stage);
        op->kind = op_kind;
        op->component = component;
        op->is._1.entity = entity;
        op->is._1.size = size;
        op->is._1.value = ecs_os_malloc(size);

        if (!value) {
            value = ecs_get_id(world, entity, component);
            if (is_added) {
                *is_added = value == NULL;
            }
        }

        const ecs_type_info_t *c_info = NULL;
        ecs_entity_t real_id = ecs_get_typeid(world, component);
        if (real_id) {
            c_info = ecs_get_c_info(world, real_id);
        }

        if (value) {
            ecs_copy_ctor_t copy;
            if (c_info && (copy = c_info->lifecycle.copy_ctor)) {
                copy(world, component, &c_info->lifecycle, &entity, &entity, 
                    op->is._1.value, value, ecs_to_size_t(size), 1, 
                        c_info->lifecycle.ctx);
            } else {
                ecs_os_memcpy(op->is._1.value, value, size);
            }
        } else {
            ecs_xtor_t ctor;
            if (c_info && (ctor = c_info->lifecycle.ctor)) {
                ctor(world, component, &entity, op->is._1.value, 
                    ecs_to_size_t(size), 1, c_info->lifecycle.ctx);
            }
        }

        if (value_out) {
            *value_out = op->is._1.value;
        }

        return true;
    } else {
        stage->defer ++;
    }

    return false;
}

void ecs_stage_merge_post_frame(
    ecs_world_t *world,
    ecs_stage_t *stage)
{
    /* Execute post frame actions */
    ecs_vector_each(stage->post_frame_actions, ecs_action_elem_t, action, {
        action->action(world, action->ctx);
    });

    ecs_vector_free(stage->post_frame_actions);
    stage->post_frame_actions = NULL;
}

void ecs_stage_init(
    ecs_world_t *world,
    ecs_stage_t *stage)
{
    ecs_object_assert(world, ecs_world_t);
    ecs_object_init(stage, ecs_stage_t);

    stage->world = world;
    stage->thread_ctx = world;
    stage->auto_merge = true;
}

void ecs_stage_deinit(
    ecs_world_t *world,
    ecs_stage_t *stage)
{
    ecs_object_assert(world, ecs_world_t);
    ecs_object_assert(stage, ecs_stage_t);
    (void)world;

    /* Make sure stage has no unmerged data */
    ecs_assert(ecs_vector_count(stage->defer_queue) == 0, 
        ECS_INVALID_PARAMETER, NULL);

    ecs_vector_free(stage->defer_queue);

    ecs_object_fini(stage, ecs_stage_t);
}

void ecs_set_stages(
    ecs_world_t *world,
    int32_t stage_count)
{
    ecs_object_assert(world, ecs_world_t);

    ecs_stage_t *stages;
    int32_t i, count = ecs_vector_count(world->worker_stages);

    if (count && count != stage_count) {
        stages = ecs_vector_first(world->worker_stages, ecs_stage_t);

        for (i = 0; i < count; i ++) {
            /* If stage contains a thread handle, ecs_set_threads was used to
             * create the stages. ecs_set_threads and ecs_set_stages should not
             * be mixed. */
            ecs_object_assert(&stages[i], ecs_stage_t);
            ecs_assert(stages[i].thread == 0, ECS_INVALID_OPERATION, NULL);
            ecs_stage_deinit(world, &stages[i]);
        }

        ecs_vector_free(world->worker_stages);
    }
    
    if (stage_count) {
        world->worker_stages = ecs_vector_new(ecs_stage_t, stage_count);

        for (i = 0; i < stage_count; i ++) {
            ecs_stage_t *stage = ecs_vector_add(
                &world->worker_stages, ecs_stage_t);
            ecs_stage_init(world, stage);
            stage->id = 1 + i; /* 0 is reserved for main/temp stage */

            /* Set thread_ctx to stage, as this stage might be used in a
             * multithreaded context */
            stage->thread_ctx = (ecs_world_t*)stage;
        }
    } else {
        /* Set to NULL to prevent double frees */
        world->worker_stages = NULL;
    }

    /* Regardless of whether the stage was just initialized or not, when the
     * ecs_set_stages function is called, all stages inherit the auto_merge
     * property from the world */
    for (i = 0; i < stage_count; i ++) {
        ecs_stage_t *stage = (ecs_stage_t*)ecs_get_stage(world, i);
        stage->auto_merge = world->stage.auto_merge;
    }
}

int32_t ecs_get_stage_count(
    const ecs_world_t *world)
{
    world = ecs_get_world(world);
    return ecs_vector_count(world->worker_stages);
}

int32_t ecs_get_stage_id(
    const ecs_world_t *world)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);

    if (ecs_object_is(world, ecs_stage_t)) {
        ecs_stage_t *stage = (ecs_stage_t*)world;

        /* Index 0 is reserved for main stage */
        return stage->id - 1;
    } else if (ecs_object_is(world, ecs_world_t)) {
        return 0;
    } else {
        ecs_abort(ECS_INTERNAL_ERROR, NULL);
    }
}

ecs_world_t* ecs_get_stage(
    const ecs_world_t *world,
    int32_t stage_id)
{
    ecs_object_assert(world, ecs_world_t);

    ecs_assert(ecs_vector_count(world->worker_stages) > stage_id, 
        ECS_INVALID_PARAMETER, NULL);

    return (ecs_world_t*)ecs_vector_get(
        world->worker_stages, ecs_stage_t, stage_id);
}

bool ecs_staging_begin(
    ecs_world_t *world)
{
    ecs_object_assert(world, ecs_world_t);

    int32_t i, count = ecs_get_stage_count(world);
    for (i = 0; i < count; i ++) {
        ecs_defer_begin(ecs_get_stage(world, i));
    }

    bool is_readonly = world->is_readonly;

    /* From this point on, the world is "locked" for mutations, and it is only 
     * allowed to enqueue commands from stages */
    world->is_readonly = true;

    return is_readonly;
}

void ecs_staging_end(
    ecs_world_t *world)
{
    ecs_object_assert(world, ecs_world_t);
    ecs_assert(world->is_readonly == true, ECS_INVALID_OPERATION, NULL);

    /* After this it is safe again to mutate the world directly */
    world->is_readonly = false;

    do_auto_merge(world);
}

void ecs_merge(
    ecs_world_t *world)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_assert(ecs_object_is(world, ecs_world_t) || 
               ecs_object_is(world, ecs_stage_t), ECS_INVALID_PARAMETER, NULL);
    do_manual_merge(world);
}

void ecs_set_automerge(
    ecs_world_t *world,
    bool auto_merge)
{
    /* If a world is provided, set auto_merge globally for the world. This
     * doesn't actually do anything (the main stage never merges) but it serves
     * as the default for when stages are created. */
    if (ecs_object_is(world, ecs_world_t)) {
        world->stage.auto_merge = auto_merge;

        /* Propagate change to all stages */
        int i, stage_count = ecs_get_stage_count(world);
        for (i = 0; i < stage_count; i ++) {
            ecs_stage_t *stage = (ecs_stage_t*)ecs_get_stage(world, i);
            stage->auto_merge = auto_merge;
        }

    /* If a stage is provided, override the auto_merge value for the individual
     * stage. This allows an application to control per-stage which stage should
     * be automatically merged and which one shouldn't */
    } else {
        /* Magic needs to be either a world or a stage */
        ecs_assert(ecs_object_is(world, ecs_stage_t), 
            ECS_INVALID_FROM_WORKER, NULL);

        ecs_stage_t *stage = (ecs_stage_t*)world;
        stage->auto_merge = auto_merge;
    }
}

bool ecs_stage_is_readonly(
    const ecs_world_t *stage)
{
    const ecs_world_t *world = ecs_get_world(stage);

    if (ecs_object_is(stage, ecs_stage_t)) {
        if (((ecs_stage_t*)stage)->asynchronous) {
            return false;
        }
    }

    if (world->is_readonly) {
        if (ecs_object_is(stage, ecs_stage_t)) {
            return true;
        }
    } else {
        if (ecs_object_is(stage, ecs_stage_t)) {
            return true;
        }
    }

    return false;
}

ecs_world_t* ecs_async_stage_new(
    ecs_world_t *world)
{
    ecs_stage_t *stage = ecs_os_malloc(sizeof(ecs_stage_t));
    ecs_stage_init(world, stage);

    stage->id = -1;
    stage->auto_merge = false;
    stage->asynchronous = true;

    ecs_defer_begin((ecs_world_t*)stage);

    return (ecs_world_t*)stage;
}

void ecs_async_stage_free(
    ecs_world_t *world)
{
    ecs_object_assert(world, ecs_stage_t);
    ecs_stage_t *stage = (ecs_stage_t*)world;
    ecs_assert(stage->asynchronous == true, ECS_INVALID_PARAMETER, NULL);
    ecs_stage_deinit(stage->world, stage);
    ecs_os_free(stage);
}

bool ecs_stage_is_async(
    ecs_world_t *stage)
{
    if (!stage) {
        return false;
    }
    
    if (!ecs_object_is(stage, ecs_stage_t)) {
        return false;
    }

    return ((ecs_stage_t*)stage)->asynchronous;
}

bool ecs_is_deferred(
    const ecs_world_t *world)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER, NULL);
    const ecs_stage_t *stage = ecs_stage_from_readonly_world(world);
    return stage->defer != 0;
}
