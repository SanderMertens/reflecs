
/* A friendly warning from bake.test
 * ----------------------------------------------------------------------------
 * This file is generated. To add/remove testcases modify the 'project.json' of
 * the test project. ANY CHANGE TO THIS FILE IS LOST AFTER (RE)BUILDING!
 * ----------------------------------------------------------------------------
 */

#include <cpp_api.h>

// Testsuite 'Entity'
void Entity_new(void);
void Entity_new_named(void);
void Entity_new_named_from_scope(void);
void Entity_new_nested_named_from_scope(void);
void Entity_new_nested_named_from_nested_scope(void);
void Entity_new_add(void);
void Entity_new_add_2(void);
void Entity_new_set(void);
void Entity_new_set_2(void);
void Entity_add(void);
void Entity_add_2(void);
void Entity_add_entity(void);
void Entity_add_childof(void);
void Entity_add_instanceof(void);
void Entity_remove(void);
void Entity_remove_2(void);
void Entity_remove_entity(void);
void Entity_remove_childof(void);
void Entity_remove_instanceof(void);
void Entity_set(void);
void Entity_set_2(void);
void Entity_emplace(void);
void Entity_emplace_2(void);
void Entity_emplace_after_add(void);
void Entity_emplace_after_add_pair(void);
void Entity_emplace_w_self_ctor(void);
void Entity_replace(void);
void Entity_get_generic(void);
void Entity_get_mut_generic(void);
void Entity_get_generic_w_id(void);
void Entity_get_mut_generic_w_id(void);
void Entity_add_role(void);
void Entity_remove_role(void);
void Entity_has_role(void);
void Entity_pair_role(void);
void Entity_equals(void);
void Entity_compare_0(void);
void Entity_compare_id_t(void);
void Entity_compare_id(void);
void Entity_compare_literal(void);
void Entity_greater_than(void);
void Entity_less_than(void);
void Entity_not_0_or_1(void);
void Entity_not_true_or_false(void);
void Entity_has_childof(void);
void Entity_has_instanceof(void);
void Entity_has_instanceof_indirect(void);
void Entity_null_string(void);
void Entity_set_name(void);
void Entity_change_name(void);
void Entity_delete(void);
void Entity_clear(void);
void Entity_foce_owned(void);
void Entity_force_owned_2(void);
void Entity_force_owned_nested(void);
void Entity_force_owned_type(void);
void Entity_force_owned_type_w_pair(void);
void Entity_tag_has_size_zero(void);
void Entity_get_null_name(void);
void Entity_get_parent(void);
void Entity_get_parent_w_tag(void);
void Entity_is_component_enabled(void);
void Entity_is_enabled_component_enabled(void);
void Entity_is_disabled_component_enabled(void);
void Entity_get_type(void);
void Entity_get_nonempty_type(void);
void Entity_set_no_copy(void);
void Entity_set_copy(void);
void Entity_set_deduced(void);
void Entity_add_owned(void);
void Entity_set_owned(void);
void Entity_implicit_name_to_char(void);
void Entity_implicit_path_to_char(void);
void Entity_implicit_type_str_to_char(void);
void Entity_entity_to_entity_view(void);
void Entity_entity_view_to_entity_world(void);
void Entity_entity_view_to_entity_stage(void);
void Entity_create_entity_view_from_stage(void);
void Entity_set_template(void);
void Entity_get_1_component_w_callback(void);
void Entity_get_2_components_w_callback(void);
void Entity_set_1_component_w_callback(void);
void Entity_set_2_components_w_callback(void);
void Entity_set_3_components_w_callback(void);
void Entity_defer_set_1_component(void);
void Entity_defer_set_2_components(void);
void Entity_defer_set_3_components(void);
void Entity_set_2_w_on_set(void);
void Entity_defer_set_2_w_on_set(void);
void Entity_set_2_after_fluent(void);
void Entity_set_2_before_fluent(void);
void Entity_set_2_after_set_1(void);
void Entity_set_2_after_set_2(void);
void Entity_with_self(void);
void Entity_with_relation_type_self(void);
void Entity_with_relation_self(void);
void Entity_with_self_w_name(void);
void Entity_with_self_nested(void);
void Entity_with_after_builder_method(void);
void Entity_with_before_builder_method(void);
void Entity_with_scope(void);
void Entity_with_scope_nested(void);
void Entity_with_scope_nested_same_name_as_parent(void);
void Entity_scope_after_builder_method(void);
void Entity_scope_before_builder_method(void);
void Entity_no_recursive_lookup(void);
void Entity_defer_new_w_name(void);
void Entity_defer_new_w_nested_name(void);
void Entity_defer_new_w_scope_name(void);
void Entity_defer_new_w_scope_nested_name(void);
void Entity_defer_new_w_deferred_scope_nested_name(void);
void Entity_defer_new_w_scope(void);
void Entity_defer_new_w_with(void);
void Entity_defer_new_w_name_scope_with(void);
void Entity_defer_w_with_implicit_component(void);
void Entity_entity_id_str(void);
void Entity_pair_id_str(void);
void Entity_role_id_str(void);
void Entity_id_str_from_entity_view(void);
void Entity_id_str_from_entity(void);
void Entity_null_entity(void);
void Entity_null_entity_w_world(void);
void Entity_null_entity_w_0(void);
void Entity_null_entity_w_world_w_0(void);
void Entity_entity_view_null_entity(void);
void Entity_entity_view_null_entity_w_world(void);
void Entity_entity_view_null_entity_w_0(void);
void Entity_entity_view_null_entity_w_world_w_0(void);
void Entity_is_wildcard(void);
void Entity_has_id_t(void);
void Entity_has_pair_id_t(void);
void Entity_has_pair_id_t_w_type(void);
void Entity_has_id(void);
void Entity_has_pair_id(void);
void Entity_has_pair_id_w_type(void);
void Entity_has_wildcard_id(void);
void Entity_has_wildcard_pair_id(void);
void Entity_owns_id_t(void);
void Entity_owns_pair_id_t(void);
void Entity_owns_pair_id_t_w_type(void);
void Entity_owns_id(void);
void Entity_owns_pair_id(void);
void Entity_owns_pair_id_w_type(void);
void Entity_owns_wildcard_id(void);
void Entity_owns_wildcard_pair(void);
void Entity_id_from_world(void);
void Entity_id_pair_from_world(void);
void Entity_id_default_from_world(void);

// Testsuite 'Pairs'
void Pairs_add_component_pair(void);
void Pairs_add_tag_pair(void);
void Pairs_add_tag_pair_to_tag(void);
void Pairs_remove_component_pair(void);
void Pairs_remove_tag_pair(void);
void Pairs_remove_tag_pair_to_tag(void);
void Pairs_set_component_pair(void);
void Pairs_set_tag_pair(void);
void Pairs_system_1_pair_instance(void);
void Pairs_system_2_pair_instances(void);
void Pairs_override_pair(void);
void Pairs_override_tag_pair(void);
void Pairs_get_mut_pair(void);
void Pairs_get_mut_pair_existing(void);
void Pairs_get_mut_pair_tag(void);
void Pairs_get_mut_pair_tag_existing(void);
void Pairs_type_w_pair(void);
void Pairs_type_w_pair_tag(void);
void Pairs_type_w_pair_tags(void);
void Pairs_type_w_tag_pair(void);
void Pairs_override_pair_w_type(void);
void Pairs_override_pair_w_type_tag(void);
void Pairs_override_tag_pair_w_type(void);
void Pairs_get_relation_from_id(void);
void Pairs_get_object_from_id(void);
void Pairs_get_recycled_relation_from_id(void);
void Pairs_get_recycled_object_from_id(void);
void Pairs_each(void);
void Pairs_each_pair(void);
void Pairs_each_pair_by_type(void);
void Pairs_each_pair_w_childof(void);
void Pairs_each_pair_w_recycled_rel(void);
void Pairs_each_pair_w_recycled_obj(void);
void Pairs_match_pair(void);
void Pairs_match_pair_obj_wildcard(void);
void Pairs_match_pair_rel_wildcard(void);
void Pairs_match_pair_both_wildcard(void);
void Pairs_has_tag_w_object(void);
void Pairs_has_object_tag(void);
void Pairs_add_pair_type(void);
void Pairs_remove_pair_type(void);
void Pairs_set_pair_type(void);
void Pairs_has_pair_type(void);
void Pairs_get_1_pair_arg(void);
void Pairs_get_2_pair_arg(void);
void Pairs_set_1_pair_arg(void);
void Pairs_set_2_pair_arg(void);
void Pairs_get_inline_pair_type(void);
void Pairs_set_inline_pair_type(void);
void Pairs_get_pair_type_object(void);
void Pairs_set_pair_type_object(void);
void Pairs_set_get_object_variants(void);

// Testsuite 'Switch'
void Switch_add_case(void);
void Switch_get_case(void);
void Switch_system_w_case(void);
void Switch_system_w_switch(void);
void Switch_add_case_w_type(void);

// Testsuite 'Paths'
void Paths_name(void);
void Paths_path_depth_1(void);
void Paths_path_depth_2(void);
void Paths_entity_lookup_name(void);
void Paths_entity_lookup_depth_1(void);
void Paths_entity_lookup_depth_2(void);
void Paths_alias_component(void);
void Paths_alias_scoped_component(void);
void Paths_alias_scoped_component_w_name(void);
void Paths_alias_entity(void);
void Paths_alias_entity_by_name(void);
void Paths_alias_entity_by_scoped_name(void);

// Testsuite 'Type'
void Type_add_2(void);
void Type_add_instanceof(void);
void Type_add_childof(void);
void Type_1_component(void);
void Type_2_component(void);
void Type_1_component_signature(void);
void Type_2_component_signature(void);
void Type_type_no_name(void);
void Type_null_args(void);
void Type_has_type(void);
void Type_has_entity(void);
void Type_has_pair_type(void);
void Type_has_pair_entity(void);
void Type_get(void);
void Type_get_out_of_range(void);

// Testsuite 'System'
void System_action(void);
void System_action_const(void);
void System_action_shared(void);
void System_action_optional(void);
void System_each(void);
void System_each_const(void);
void System_each_shared(void);
void System_each_optional(void);
void System_signature(void);
void System_signature_const(void);
void System_signature_shared(void);
void System_signature_optional(void);
void System_copy_name_on_create(void);
void System_nested_system(void);
void System_empty_signature(void);
void System_action_tag(void);
void System_iter_tag(void);
void System_each_tag(void);
void System_system_from_id(void);
void System_set_interval(void);
void System_order_by_type(void);
void System_order_by_id(void);
void System_order_by_type_after_create(void);
void System_order_by_id_after_create(void);
void System_get_query(void);
void System_add_from_each(void);
void System_delete_from_each(void);
void System_add_from_each_world_handle(void);
void System_new_from_each(void);
void System_add_from_iter(void);
void System_delete_from_iter(void);
void System_add_from_iter_world_handle(void);
void System_new_from_iter(void);
void System_each_w_mut_children_it(void);
void System_readonly_children_iter(void);
void System_rate_filter(void);
void System_update_rate_filter(void);
void System_default_ctor(void);
void System_test_auto_defer_each(void);
void System_test_auto_defer_iter(void);
void System_custom_pipeline(void);
void System_system_w_self(void);

// Testsuite 'Trigger'
void Trigger_on_add(void);
void Trigger_on_remove(void);
void Trigger_on_add_tag_action(void);
void Trigger_on_add_tag_iter(void);
void Trigger_on_add_tag_each(void);
void Trigger_trigger_w_self(void);

// Testsuite 'Query'
void Query_action(void);
void Query_action_const(void);
void Query_action_shared(void);
void Query_action_optional(void);
void Query_each(void);
void Query_each_const(void);
void Query_each_shared(void);
void Query_each_optional(void);
void Query_signature(void);
void Query_signature_const(void);
void Query_signature_shared(void);
void Query_signature_optional(void);
void Query_subquery(void);
void Query_subquery_w_expr(void);
void Query_query_single_pair(void);
void Query_tag_w_each(void);
void Query_shared_tag_w_each(void);
void Query_sort_by(void);
void Query_changed(void);
void Query_orphaned(void);
void Query_default_ctor(void);
void Query_expr_w_template(void);
void Query_query_type_w_template(void);
void Query_compare_term_id(void);
void Query_test_no_defer_each(void);
void Query_test_no_defer_iter(void);
void Query_inspect_terms(void);
void Query_inspect_terms_w_each(void);
void Query_comp_to_str(void);
void Query_pair_to_str(void);
void Query_oper_not_to_str(void);
void Query_oper_optional_to_str(void);
void Query_oper_or_to_str(void);
void Query_each_pair_type(void);
void Query_iter_pair_type(void);
void Query_term_pair_type(void);
void Query_each_no_entity_1_comp(void);
void Query_each_no_entity_2_comps(void);
void Query_iter_no_comps_1_comp(void);
void Query_iter_no_comps_2_comps(void);
void Query_iter_no_comps_no_comps(void);
void Query_each_pair_object(void);
void Query_iter_pair_object(void);
void Query_iter_query_in_system(void);
void Query_iter_type(void);

// Testsuite 'QueryBuilder'
void QueryBuilder_builder_assign_same_type(void);
void QueryBuilder_builder_assign_from_empty(void);
void QueryBuilder_builder_assign_to_empty(void);
void QueryBuilder_builder_build(void);
void QueryBuilder_builder_build_to_auto(void);
void QueryBuilder_builder_build_n_statements(void);
void QueryBuilder_1_type(void);
void QueryBuilder_add_1_type(void);
void QueryBuilder_add_2_types(void);
void QueryBuilder_add_1_type_w_1_type(void);
void QueryBuilder_add_2_types_w_1_type(void);
void QueryBuilder_add_pair(void);
void QueryBuilder_add_not(void);
void QueryBuilder_add_or(void);
void QueryBuilder_add_optional(void);
void QueryBuilder_ptr_type(void);
void QueryBuilder_const_type(void);
void QueryBuilder_string_term(void);
void QueryBuilder_singleton_term(void);
void QueryBuilder_isa_superset_term(void);
void QueryBuilder_isa_self_superset_term(void);
void QueryBuilder_childof_superset_term(void);
void QueryBuilder_childof_self_superset_term(void);
void QueryBuilder_isa_superset_term_w_each(void);
void QueryBuilder_isa_self_superset_term_w_each(void);
void QueryBuilder_childof_superset_term_w_each(void);
void QueryBuilder_childof_self_superset_term_w_each(void);
void QueryBuilder_isa_superset_shortcut(void);
void QueryBuilder_isa_superset_shortcut_w_self(void);
void QueryBuilder_childof_superset_shortcut(void);
void QueryBuilder_childof_superset_shortcut_w_self(void);
void QueryBuilder_isa_supetset_max_depth_1(void);
void QueryBuilder_isa_supetset_max_depth_2(void);
void QueryBuilder_isa_supetset_min_depth_2(void);
void QueryBuilder_isa_supetset_min_depth_2_max_depth_3(void);
void QueryBuilder_role(void);
void QueryBuilder_relation(void);
void QueryBuilder_relation_w_object_wildcard(void);
void QueryBuilder_relation_w_predicate_wildcard(void);
void QueryBuilder_add_pair_w_rel_type(void);
void QueryBuilder_template_term(void);
void QueryBuilder_explicit_subject_w_id(void);
void QueryBuilder_explicit_subject_w_type(void);
void QueryBuilder_explicit_object_w_id(void);
void QueryBuilder_explicit_object_w_type(void);
void QueryBuilder_explicit_term(void);
void QueryBuilder_explicit_term_w_type(void);
void QueryBuilder_explicit_term_w_pair_type(void);
void QueryBuilder_explicit_term_w_id(void);
void QueryBuilder_explicit_term_w_pair_id(void);
void QueryBuilder_1_term_to_empty(void);
void QueryBuilder_2_subsequent_args(void);

// Testsuite 'SystemBuilder'
void SystemBuilder_builder_assign_same_type(void);
void SystemBuilder_builder_assign_from_empty(void);
void SystemBuilder_builder_build_to_auto(void);
void SystemBuilder_builder_build_n_statements(void);
void SystemBuilder_1_type(void);
void SystemBuilder_add_1_type(void);
void SystemBuilder_add_2_types(void);
void SystemBuilder_add_1_type_w_1_type(void);
void SystemBuilder_add_2_types_w_1_type(void);
void SystemBuilder_add_pair(void);
void SystemBuilder_add_not(void);
void SystemBuilder_add_or(void);
void SystemBuilder_add_optional(void);
void SystemBuilder_ptr_type(void);
void SystemBuilder_const_type(void);
void SystemBuilder_string_term(void);
void SystemBuilder_singleton_term(void);

// Testsuite 'Observer'
void Observer_2_terms_on_add(void);
void Observer_2_terms_on_remove(void);
void Observer_2_terms_on_set(void);
void Observer_2_terms_un_set(void);
void Observer_observer_w_self(void);

// Testsuite 'ComponentLifecycle'
void ComponentLifecycle_ctor_on_add(void);
void ComponentLifecycle_dtor_on_remove(void);
void ComponentLifecycle_move_on_add(void);
void ComponentLifecycle_move_on_remove(void);
void ComponentLifecycle_copy_on_set(void);
void ComponentLifecycle_copy_on_override(void);
void ComponentLifecycle_non_pod_add(void);
void ComponentLifecycle_non_pod_remove(void);
void ComponentLifecycle_non_pod_set(void);
void ComponentLifecycle_non_pod_override(void);
void ComponentLifecycle_get_mut_new(void);
void ComponentLifecycle_get_mut_existing(void);
void ComponentLifecycle_pod_component(void);
void ComponentLifecycle_relocatable_component(void);
void ComponentLifecycle_implicit_component(void);
void ComponentLifecycle_implicit_after_query(void);
void ComponentLifecycle_deleted_copy(void);
void ComponentLifecycle_no_default_ctor(void);
void ComponentLifecycle_default_init(void);
void ComponentLifecycle_no_default_ctor_add(void);
void ComponentLifecycle_no_default_ctor_add_relation(void);
void ComponentLifecycle_no_default_ctor_add_object(void);
void ComponentLifecycle_no_default_ctor_set(void);
void ComponentLifecycle_no_copy_ctor(void);
void ComponentLifecycle_no_move_ctor(void);
void ComponentLifecycle_no_copy_assign(void);
void ComponentLifecycle_no_move_assign(void);
void ComponentLifecycle_no_copy(void);
void ComponentLifecycle_no_move(void);
void ComponentLifecycle_no_dtor(void);
void ComponentLifecycle_flecs_ctor(void);
void ComponentLifecycle_flecs_ctor_w_default_ctor(void);
void ComponentLifecycle_default_ctor_w_value_ctor(void);
void ComponentLifecycle_flecs_ctor_w_value_ctor(void);
void ComponentLifecycle_no_default_ctor_move_ctor_on_set(void);
void ComponentLifecycle_emplace_w_ctor(void);
void ComponentLifecycle_emplace_no_default_ctor(void);
void ComponentLifecycle_emplace_existing(void);
void ComponentLifecycle_emplace_singleton(void);

// Testsuite 'Refs'
void Refs_get_ref(void);
void Refs_ref_after_add(void);
void Refs_ref_after_remove(void);
void Refs_ref_after_set(void);
void Refs_ref_before_set(void);

// Testsuite 'Module'
void Module_import(void);
void Module_lookup_from_scope(void);
void Module_nested_module(void);
void Module_nested_type_module(void);
void Module_module_type_w_explicit_name(void);
void Module_component_redefinition_outside_module(void);
void Module_module_tag_on_namespace(void);
void Module_dtor_on_fini(void);

// Testsuite 'ImplicitComponents'
void ImplicitComponents_add(void);
void ImplicitComponents_remove(void);
void ImplicitComponents_has(void);
void ImplicitComponents_set(void);
void ImplicitComponents_get(void);
void ImplicitComponents_add_pair(void);
void ImplicitComponents_remove_pair(void);
void ImplicitComponents_module(void);
void ImplicitComponents_system(void);
void ImplicitComponents_system_optional(void);
void ImplicitComponents_system_const(void);
void ImplicitComponents_query(void);
void ImplicitComponents_implicit_name(void);
void ImplicitComponents_reinit(void);
void ImplicitComponents_reinit_scoped(void);
void ImplicitComponents_reinit_w_lifecycle(void);
void ImplicitComponents_first_use_in_system(void);
void ImplicitComponents_first_use_tag_in_system(void);
void ImplicitComponents_use_const(void);
void ImplicitComponents_use_const_w_stage(void);
void ImplicitComponents_use_const_w_threads(void);
void ImplicitComponents_implicit_base(void);
void ImplicitComponents_implicit_const(void);
void ImplicitComponents_implicit_ref(void);
void ImplicitComponents_implicit_ptr(void);
void ImplicitComponents_implicit_const_ref(void);

// Testsuite 'Snapshot'
void Snapshot_simple_snapshot(void);
void Snapshot_snapshot_iter(void);
void Snapshot_snapshot_iter_w_filter(void);

// Testsuite 'WorldFactory'
void WorldFactory_entity(void);
void WorldFactory_entity_w_name(void);
void WorldFactory_entity_w_id(void);
void WorldFactory_prefab(void);
void WorldFactory_prefab_w_name(void);
void WorldFactory_type(void);
void WorldFactory_type_w_name(void);
void WorldFactory_system(void);
void WorldFactory_system_w_name(void);
void WorldFactory_system_w_expr(void);
void WorldFactory_query(void);
void WorldFactory_query_w_expr(void);
void WorldFactory_snapshot(void);
void WorldFactory_module(void);
void WorldFactory_module_w_name(void);

// Testsuite 'World'
void World_builtin_components(void);
void World_multi_world_empty(void);
void World_multi_world_component(void);
void World_multi_world_component_namespace(void);
void World_multi_world_module(void);
void World_type_id(void);
void World_different_comp_same_name(void);
void World_reregister_after_reset(void);
void World_reregister_after_reset_w_namespace(void);
void World_reregister_namespace(void);
void World_implicit_reregister_after_reset(void);
void World_reregister_after_reset_different_name(void);
void World_reimport(void);
void World_reimport_module_after_reset(void);
void World_reimport_module_new_world(void);
void World_reimport_namespaced_module(void);
void World_c_interop_module(void);
void World_c_interop_after_reset(void);
void World_implicit_register_w_new_world(void);
void World_count(void);
void World_staged_count(void);
void World_async_stage_add(void);
void World_with_tag(void);
void World_with_tag_type(void);
void World_with_relation(void);
void World_with_relation_type(void);
void World_with_relation_object_type(void);
void World_with_tag_nested(void);
void World_with_scope(void);
void World_with_scope_nested(void);
void World_recursive_lookup(void);
void World_type_w_tag_name(void);
void World_entity_w_tag_name(void);
void World_template_component_name(void);
void World_template_component_w_namespace_name(void);
void World_template_component_w_same_namespace_name(void);
void World_template_component_w_namespace_name_and_namespaced_arg(void);
void World_template_component_w_same_namespace_name_and_namespaced_arg(void);

// Testsuite 'Singleton'
void Singleton_set_get_singleton(void);
void Singleton_get_mut_singleton(void);
void Singleton_emplace_singleton(void);
void Singleton_modified_singleton(void);
void Singleton_patch_singleton(void);
void Singleton_add_singleton(void);
void Singleton_remove_singleton(void);
void Singleton_has_singleton(void);
void Singleton_singleton_system(void);
void Singleton_get_singleton(void);
void Singleton_type_id_from_world(void);

// Testsuite 'Misc'
void Misc_setup(void);
void Misc_string_compare_w_char_ptr(void);
void Misc_string_compare_w_char_ptr_length_diff(void);
void Misc_string_compare_w_string(void);
void Misc_string_view_compare_w_char_ptr(void);
void Misc_string_view_compare_w_string(void);
void Misc_string_compare_nullptr(void);
void Misc_nullptr_string_compare(void);
void Misc_nullptr_string_compare_nullptr(void);

bake_test_case Entity_testcases[] = {
    {
        "new",
        Entity_new
    },
    {
        "new_named",
        Entity_new_named
    },
    {
        "new_named_from_scope",
        Entity_new_named_from_scope
    },
    {
        "new_nested_named_from_scope",
        Entity_new_nested_named_from_scope
    },
    {
        "new_nested_named_from_nested_scope",
        Entity_new_nested_named_from_nested_scope
    },
    {
        "new_add",
        Entity_new_add
    },
    {
        "new_add_2",
        Entity_new_add_2
    },
    {
        "new_set",
        Entity_new_set
    },
    {
        "new_set_2",
        Entity_new_set_2
    },
    {
        "add",
        Entity_add
    },
    {
        "add_2",
        Entity_add_2
    },
    {
        "add_entity",
        Entity_add_entity
    },
    {
        "add_childof",
        Entity_add_childof
    },
    {
        "add_instanceof",
        Entity_add_instanceof
    },
    {
        "remove",
        Entity_remove
    },
    {
        "remove_2",
        Entity_remove_2
    },
    {
        "remove_entity",
        Entity_remove_entity
    },
    {
        "remove_childof",
        Entity_remove_childof
    },
    {
        "remove_instanceof",
        Entity_remove_instanceof
    },
    {
        "set",
        Entity_set
    },
    {
        "set_2",
        Entity_set_2
    },
    {
        "emplace",
        Entity_emplace
    },
    {
        "emplace_2",
        Entity_emplace_2
    },
    {
        "emplace_after_add",
        Entity_emplace_after_add
    },
    {
        "emplace_after_add_pair",
        Entity_emplace_after_add_pair
    },
    {
        "emplace_w_self_ctor",
        Entity_emplace_w_self_ctor
    },
    {
        "replace",
        Entity_replace
    },
    {
        "get_generic",
        Entity_get_generic
    },
    {
        "get_mut_generic",
        Entity_get_mut_generic
    },
    {
        "get_generic_w_id",
        Entity_get_generic_w_id
    },
    {
        "get_mut_generic_w_id",
        Entity_get_mut_generic_w_id
    },
    {
        "add_role",
        Entity_add_role
    },
    {
        "remove_role",
        Entity_remove_role
    },
    {
        "has_role",
        Entity_has_role
    },
    {
        "pair_role",
        Entity_pair_role
    },
    {
        "equals",
        Entity_equals
    },
    {
        "compare_0",
        Entity_compare_0
    },
    {
        "compare_id_t",
        Entity_compare_id_t
    },
    {
        "compare_id",
        Entity_compare_id
    },
    {
        "compare_literal",
        Entity_compare_literal
    },
    {
        "greater_than",
        Entity_greater_than
    },
    {
        "less_than",
        Entity_less_than
    },
    {
        "not_0_or_1",
        Entity_not_0_or_1
    },
    {
        "not_true_or_false",
        Entity_not_true_or_false
    },
    {
        "has_childof",
        Entity_has_childof
    },
    {
        "has_instanceof",
        Entity_has_instanceof
    },
    {
        "has_instanceof_indirect",
        Entity_has_instanceof_indirect
    },
    {
        "null_string",
        Entity_null_string
    },
    {
        "set_name",
        Entity_set_name
    },
    {
        "change_name",
        Entity_change_name
    },
    {
        "delete",
        Entity_delete
    },
    {
        "clear",
        Entity_clear
    },
    {
        "foce_owned",
        Entity_foce_owned
    },
    {
        "force_owned_2",
        Entity_force_owned_2
    },
    {
        "force_owned_nested",
        Entity_force_owned_nested
    },
    {
        "force_owned_type",
        Entity_force_owned_type
    },
    {
        "force_owned_type_w_pair",
        Entity_force_owned_type_w_pair
    },
    {
        "tag_has_size_zero",
        Entity_tag_has_size_zero
    },
    {
        "get_null_name",
        Entity_get_null_name
    },
    {
        "get_parent",
        Entity_get_parent
    },
    {
        "get_parent_w_tag",
        Entity_get_parent_w_tag
    },
    {
        "is_component_enabled",
        Entity_is_component_enabled
    },
    {
        "is_enabled_component_enabled",
        Entity_is_enabled_component_enabled
    },
    {
        "is_disabled_component_enabled",
        Entity_is_disabled_component_enabled
    },
    {
        "get_type",
        Entity_get_type
    },
    {
        "get_nonempty_type",
        Entity_get_nonempty_type
    },
    {
        "set_no_copy",
        Entity_set_no_copy
    },
    {
        "set_copy",
        Entity_set_copy
    },
    {
        "set_deduced",
        Entity_set_deduced
    },
    {
        "add_owned",
        Entity_add_owned
    },
    {
        "set_owned",
        Entity_set_owned
    },
    {
        "implicit_name_to_char",
        Entity_implicit_name_to_char
    },
    {
        "implicit_path_to_char",
        Entity_implicit_path_to_char
    },
    {
        "implicit_type_str_to_char",
        Entity_implicit_type_str_to_char
    },
    {
        "entity_to_entity_view",
        Entity_entity_to_entity_view
    },
    {
        "entity_view_to_entity_world",
        Entity_entity_view_to_entity_world
    },
    {
        "entity_view_to_entity_stage",
        Entity_entity_view_to_entity_stage
    },
    {
        "create_entity_view_from_stage",
        Entity_create_entity_view_from_stage
    },
    {
        "set_template",
        Entity_set_template
    },
    {
        "get_1_component_w_callback",
        Entity_get_1_component_w_callback
    },
    {
        "get_2_components_w_callback",
        Entity_get_2_components_w_callback
    },
    {
        "set_1_component_w_callback",
        Entity_set_1_component_w_callback
    },
    {
        "set_2_components_w_callback",
        Entity_set_2_components_w_callback
    },
    {
        "set_3_components_w_callback",
        Entity_set_3_components_w_callback
    },
    {
        "defer_set_1_component",
        Entity_defer_set_1_component
    },
    {
        "defer_set_2_components",
        Entity_defer_set_2_components
    },
    {
        "defer_set_3_components",
        Entity_defer_set_3_components
    },
    {
        "set_2_w_on_set",
        Entity_set_2_w_on_set
    },
    {
        "defer_set_2_w_on_set",
        Entity_defer_set_2_w_on_set
    },
    {
        "set_2_after_fluent",
        Entity_set_2_after_fluent
    },
    {
        "set_2_before_fluent",
        Entity_set_2_before_fluent
    },
    {
        "set_2_after_set_1",
        Entity_set_2_after_set_1
    },
    {
        "set_2_after_set_2",
        Entity_set_2_after_set_2
    },
    {
        "with_self",
        Entity_with_self
    },
    {
        "with_relation_type_self",
        Entity_with_relation_type_self
    },
    {
        "with_relation_self",
        Entity_with_relation_self
    },
    {
        "with_self_w_name",
        Entity_with_self_w_name
    },
    {
        "with_self_nested",
        Entity_with_self_nested
    },
    {
        "with_after_builder_method",
        Entity_with_after_builder_method
    },
    {
        "with_before_builder_method",
        Entity_with_before_builder_method
    },
    {
        "with_scope",
        Entity_with_scope
    },
    {
        "with_scope_nested",
        Entity_with_scope_nested
    },
    {
        "with_scope_nested_same_name_as_parent",
        Entity_with_scope_nested_same_name_as_parent
    },
    {
        "scope_after_builder_method",
        Entity_scope_after_builder_method
    },
    {
        "scope_before_builder_method",
        Entity_scope_before_builder_method
    },
    {
        "no_recursive_lookup",
        Entity_no_recursive_lookup
    },
    {
        "defer_new_w_name",
        Entity_defer_new_w_name
    },
    {
        "defer_new_w_nested_name",
        Entity_defer_new_w_nested_name
    },
    {
        "defer_new_w_scope_name",
        Entity_defer_new_w_scope_name
    },
    {
        "defer_new_w_scope_nested_name",
        Entity_defer_new_w_scope_nested_name
    },
    {
        "defer_new_w_deferred_scope_nested_name",
        Entity_defer_new_w_deferred_scope_nested_name
    },
    {
        "defer_new_w_scope",
        Entity_defer_new_w_scope
    },
    {
        "defer_new_w_with",
        Entity_defer_new_w_with
    },
    {
        "defer_new_w_name_scope_with",
        Entity_defer_new_w_name_scope_with
    },
    {
        "defer_w_with_implicit_component",
        Entity_defer_w_with_implicit_component
    },
    {
        "entity_id_str",
        Entity_entity_id_str
    },
    {
        "pair_id_str",
        Entity_pair_id_str
    },
    {
        "role_id_str",
        Entity_role_id_str
    },
    {
        "id_str_from_entity_view",
        Entity_id_str_from_entity_view
    },
    {
        "id_str_from_entity",
        Entity_id_str_from_entity
    },
    {
        "null_entity",
        Entity_null_entity
    },
    {
        "null_entity_w_world",
        Entity_null_entity_w_world
    },
    {
        "null_entity_w_0",
        Entity_null_entity_w_0
    },
    {
        "null_entity_w_world_w_0",
        Entity_null_entity_w_world_w_0
    },
    {
        "entity_view_null_entity",
        Entity_entity_view_null_entity
    },
    {
        "entity_view_null_entity_w_world",
        Entity_entity_view_null_entity_w_world
    },
    {
        "entity_view_null_entity_w_0",
        Entity_entity_view_null_entity_w_0
    },
    {
        "entity_view_null_entity_w_world_w_0",
        Entity_entity_view_null_entity_w_world_w_0
    },
    {
        "is_wildcard",
        Entity_is_wildcard
    },
    {
        "has_id_t",
        Entity_has_id_t
    },
    {
        "has_pair_id_t",
        Entity_has_pair_id_t
    },
    {
        "has_pair_id_t_w_type",
        Entity_has_pair_id_t_w_type
    },
    {
        "has_id",
        Entity_has_id
    },
    {
        "has_pair_id",
        Entity_has_pair_id
    },
    {
        "has_pair_id_w_type",
        Entity_has_pair_id_w_type
    },
    {
        "has_wildcard_id",
        Entity_has_wildcard_id
    },
    {
        "has_wildcard_pair_id",
        Entity_has_wildcard_pair_id
    },
    {
        "owns_id_t",
        Entity_owns_id_t
    },
    {
        "owns_pair_id_t",
        Entity_owns_pair_id_t
    },
    {
        "owns_pair_id_t_w_type",
        Entity_owns_pair_id_t_w_type
    },
    {
        "owns_id",
        Entity_owns_id
    },
    {
        "owns_pair_id",
        Entity_owns_pair_id
    },
    {
        "owns_pair_id_w_type",
        Entity_owns_pair_id_w_type
    },
    {
        "owns_wildcard_id",
        Entity_owns_wildcard_id
    },
    {
        "owns_wildcard_pair",
        Entity_owns_wildcard_pair
    },
    {
        "id_from_world",
        Entity_id_from_world
    },
    {
        "id_pair_from_world",
        Entity_id_pair_from_world
    },
    {
        "id_default_from_world",
        Entity_id_default_from_world
    }
};

bake_test_case Pairs_testcases[] = {
    {
        "add_component_pair",
        Pairs_add_component_pair
    },
    {
        "add_tag_pair",
        Pairs_add_tag_pair
    },
    {
        "add_tag_pair_to_tag",
        Pairs_add_tag_pair_to_tag
    },
    {
        "remove_component_pair",
        Pairs_remove_component_pair
    },
    {
        "remove_tag_pair",
        Pairs_remove_tag_pair
    },
    {
        "remove_tag_pair_to_tag",
        Pairs_remove_tag_pair_to_tag
    },
    {
        "set_component_pair",
        Pairs_set_component_pair
    },
    {
        "set_tag_pair",
        Pairs_set_tag_pair
    },
    {
        "system_1_pair_instance",
        Pairs_system_1_pair_instance
    },
    {
        "system_2_pair_instances",
        Pairs_system_2_pair_instances
    },
    {
        "override_pair",
        Pairs_override_pair
    },
    {
        "override_tag_pair",
        Pairs_override_tag_pair
    },
    {
        "get_mut_pair",
        Pairs_get_mut_pair
    },
    {
        "get_mut_pair_existing",
        Pairs_get_mut_pair_existing
    },
    {
        "get_mut_pair_tag",
        Pairs_get_mut_pair_tag
    },
    {
        "get_mut_pair_tag_existing",
        Pairs_get_mut_pair_tag_existing
    },
    {
        "type_w_pair",
        Pairs_type_w_pair
    },
    {
        "type_w_pair_tag",
        Pairs_type_w_pair_tag
    },
    {
        "type_w_pair_tags",
        Pairs_type_w_pair_tags
    },
    {
        "type_w_tag_pair",
        Pairs_type_w_tag_pair
    },
    {
        "override_pair_w_type",
        Pairs_override_pair_w_type
    },
    {
        "override_pair_w_type_tag",
        Pairs_override_pair_w_type_tag
    },
    {
        "override_tag_pair_w_type",
        Pairs_override_tag_pair_w_type
    },
    {
        "get_relation_from_id",
        Pairs_get_relation_from_id
    },
    {
        "get_object_from_id",
        Pairs_get_object_from_id
    },
    {
        "get_recycled_relation_from_id",
        Pairs_get_recycled_relation_from_id
    },
    {
        "get_recycled_object_from_id",
        Pairs_get_recycled_object_from_id
    },
    {
        "each",
        Pairs_each
    },
    {
        "each_pair",
        Pairs_each_pair
    },
    {
        "each_pair_by_type",
        Pairs_each_pair_by_type
    },
    {
        "each_pair_w_childof",
        Pairs_each_pair_w_childof
    },
    {
        "each_pair_w_recycled_rel",
        Pairs_each_pair_w_recycled_rel
    },
    {
        "each_pair_w_recycled_obj",
        Pairs_each_pair_w_recycled_obj
    },
    {
        "match_pair",
        Pairs_match_pair
    },
    {
        "match_pair_obj_wildcard",
        Pairs_match_pair_obj_wildcard
    },
    {
        "match_pair_rel_wildcard",
        Pairs_match_pair_rel_wildcard
    },
    {
        "match_pair_both_wildcard",
        Pairs_match_pair_both_wildcard
    },
    {
        "has_tag_w_object",
        Pairs_has_tag_w_object
    },
    {
        "has_object_tag",
        Pairs_has_object_tag
    },
    {
        "add_pair_type",
        Pairs_add_pair_type
    },
    {
        "remove_pair_type",
        Pairs_remove_pair_type
    },
    {
        "set_pair_type",
        Pairs_set_pair_type
    },
    {
        "has_pair_type",
        Pairs_has_pair_type
    },
    {
        "get_1_pair_arg",
        Pairs_get_1_pair_arg
    },
    {
        "get_2_pair_arg",
        Pairs_get_2_pair_arg
    },
    {
        "set_1_pair_arg",
        Pairs_set_1_pair_arg
    },
    {
        "set_2_pair_arg",
        Pairs_set_2_pair_arg
    },
    {
        "get_inline_pair_type",
        Pairs_get_inline_pair_type
    },
    {
        "set_inline_pair_type",
        Pairs_set_inline_pair_type
    },
    {
        "get_pair_type_object",
        Pairs_get_pair_type_object
    },
    {
        "set_pair_type_object",
        Pairs_set_pair_type_object
    },
    {
        "set_get_object_variants",
        Pairs_set_get_object_variants
    }
};

bake_test_case Switch_testcases[] = {
    {
        "add_case",
        Switch_add_case
    },
    {
        "get_case",
        Switch_get_case
    },
    {
        "system_w_case",
        Switch_system_w_case
    },
    {
        "system_w_switch",
        Switch_system_w_switch
    },
    {
        "add_case_w_type",
        Switch_add_case_w_type
    }
};

bake_test_case Paths_testcases[] = {
    {
        "name",
        Paths_name
    },
    {
        "path_depth_1",
        Paths_path_depth_1
    },
    {
        "path_depth_2",
        Paths_path_depth_2
    },
    {
        "entity_lookup_name",
        Paths_entity_lookup_name
    },
    {
        "entity_lookup_depth_1",
        Paths_entity_lookup_depth_1
    },
    {
        "entity_lookup_depth_2",
        Paths_entity_lookup_depth_2
    },
    {
        "alias_component",
        Paths_alias_component
    },
    {
        "alias_scoped_component",
        Paths_alias_scoped_component
    },
    {
        "alias_scoped_component_w_name",
        Paths_alias_scoped_component_w_name
    },
    {
        "alias_entity",
        Paths_alias_entity
    },
    {
        "alias_entity_by_name",
        Paths_alias_entity_by_name
    },
    {
        "alias_entity_by_scoped_name",
        Paths_alias_entity_by_scoped_name
    }
};

bake_test_case Type_testcases[] = {
    {
        "add_2",
        Type_add_2
    },
    {
        "add_instanceof",
        Type_add_instanceof
    },
    {
        "add_childof",
        Type_add_childof
    },
    {
        "1_component",
        Type_1_component
    },
    {
        "2_component",
        Type_2_component
    },
    {
        "1_component_signature",
        Type_1_component_signature
    },
    {
        "2_component_signature",
        Type_2_component_signature
    },
    {
        "type_no_name",
        Type_type_no_name
    },
    {
        "null_args",
        Type_null_args
    },
    {
        "has_type",
        Type_has_type
    },
    {
        "has_entity",
        Type_has_entity
    },
    {
        "has_pair_type",
        Type_has_pair_type
    },
    {
        "has_pair_entity",
        Type_has_pair_entity
    },
    {
        "get",
        Type_get
    },
    {
        "get_out_of_range",
        Type_get_out_of_range
    }
};

bake_test_case System_testcases[] = {
    {
        "action",
        System_action
    },
    {
        "action_const",
        System_action_const
    },
    {
        "action_shared",
        System_action_shared
    },
    {
        "action_optional",
        System_action_optional
    },
    {
        "each",
        System_each
    },
    {
        "each_const",
        System_each_const
    },
    {
        "each_shared",
        System_each_shared
    },
    {
        "each_optional",
        System_each_optional
    },
    {
        "signature",
        System_signature
    },
    {
        "signature_const",
        System_signature_const
    },
    {
        "signature_shared",
        System_signature_shared
    },
    {
        "signature_optional",
        System_signature_optional
    },
    {
        "copy_name_on_create",
        System_copy_name_on_create
    },
    {
        "nested_system",
        System_nested_system
    },
    {
        "empty_signature",
        System_empty_signature
    },
    {
        "action_tag",
        System_action_tag
    },
    {
        "iter_tag",
        System_iter_tag
    },
    {
        "each_tag",
        System_each_tag
    },
    {
        "system_from_id",
        System_system_from_id
    },
    {
        "set_interval",
        System_set_interval
    },
    {
        "order_by_type",
        System_order_by_type
    },
    {
        "order_by_id",
        System_order_by_id
    },
    {
        "order_by_type_after_create",
        System_order_by_type_after_create
    },
    {
        "order_by_id_after_create",
        System_order_by_id_after_create
    },
    {
        "get_query",
        System_get_query
    },
    {
        "add_from_each",
        System_add_from_each
    },
    {
        "delete_from_each",
        System_delete_from_each
    },
    {
        "add_from_each_world_handle",
        System_add_from_each_world_handle
    },
    {
        "new_from_each",
        System_new_from_each
    },
    {
        "add_from_iter",
        System_add_from_iter
    },
    {
        "delete_from_iter",
        System_delete_from_iter
    },
    {
        "add_from_iter_world_handle",
        System_add_from_iter_world_handle
    },
    {
        "new_from_iter",
        System_new_from_iter
    },
    {
        "each_w_mut_children_it",
        System_each_w_mut_children_it
    },
    {
        "readonly_children_iter",
        System_readonly_children_iter
    },
    {
        "rate_filter",
        System_rate_filter
    },
    {
        "update_rate_filter",
        System_update_rate_filter
    },
    {
        "default_ctor",
        System_default_ctor
    },
    {
        "test_auto_defer_each",
        System_test_auto_defer_each
    },
    {
        "test_auto_defer_iter",
        System_test_auto_defer_iter
    },
    {
        "custom_pipeline",
        System_custom_pipeline
    },
    {
        "system_w_self",
        System_system_w_self
    }
};

bake_test_case Trigger_testcases[] = {
    {
        "on_add",
        Trigger_on_add
    },
    {
        "on_remove",
        Trigger_on_remove
    },
    {
        "on_add_tag_action",
        Trigger_on_add_tag_action
    },
    {
        "on_add_tag_iter",
        Trigger_on_add_tag_iter
    },
    {
        "on_add_tag_each",
        Trigger_on_add_tag_each
    },
    {
        "trigger_w_self",
        Trigger_trigger_w_self
    }
};

bake_test_case Query_testcases[] = {
    {
        "action",
        Query_action
    },
    {
        "action_const",
        Query_action_const
    },
    {
        "action_shared",
        Query_action_shared
    },
    {
        "action_optional",
        Query_action_optional
    },
    {
        "each",
        Query_each
    },
    {
        "each_const",
        Query_each_const
    },
    {
        "each_shared",
        Query_each_shared
    },
    {
        "each_optional",
        Query_each_optional
    },
    {
        "signature",
        Query_signature
    },
    {
        "signature_const",
        Query_signature_const
    },
    {
        "signature_shared",
        Query_signature_shared
    },
    {
        "signature_optional",
        Query_signature_optional
    },
    {
        "subquery",
        Query_subquery
    },
    {
        "subquery_w_expr",
        Query_subquery_w_expr
    },
    {
        "query_single_pair",
        Query_query_single_pair
    },
    {
        "tag_w_each",
        Query_tag_w_each
    },
    {
        "shared_tag_w_each",
        Query_shared_tag_w_each
    },
    {
        "sort_by",
        Query_sort_by
    },
    {
        "changed",
        Query_changed
    },
    {
        "orphaned",
        Query_orphaned
    },
    {
        "default_ctor",
        Query_default_ctor
    },
    {
        "expr_w_template",
        Query_expr_w_template
    },
    {
        "query_type_w_template",
        Query_query_type_w_template
    },
    {
        "compare_term_id",
        Query_compare_term_id
    },
    {
        "test_no_defer_each",
        Query_test_no_defer_each
    },
    {
        "test_no_defer_iter",
        Query_test_no_defer_iter
    },
    {
        "inspect_terms",
        Query_inspect_terms
    },
    {
        "inspect_terms_w_each",
        Query_inspect_terms_w_each
    },
    {
        "comp_to_str",
        Query_comp_to_str
    },
    {
        "pair_to_str",
        Query_pair_to_str
    },
    {
        "oper_not_to_str",
        Query_oper_not_to_str
    },
    {
        "oper_optional_to_str",
        Query_oper_optional_to_str
    },
    {
        "oper_or_to_str",
        Query_oper_or_to_str
    },
    {
        "each_pair_type",
        Query_each_pair_type
    },
    {
        "iter_pair_type",
        Query_iter_pair_type
    },
    {
        "term_pair_type",
        Query_term_pair_type
    },
    {
        "each_no_entity_1_comp",
        Query_each_no_entity_1_comp
    },
    {
        "each_no_entity_2_comps",
        Query_each_no_entity_2_comps
    },
    {
        "iter_no_comps_1_comp",
        Query_iter_no_comps_1_comp
    },
    {
        "iter_no_comps_2_comps",
        Query_iter_no_comps_2_comps
    },
    {
        "iter_no_comps_no_comps",
        Query_iter_no_comps_no_comps
    },
    {
        "each_pair_object",
        Query_each_pair_object
    },
    {
        "iter_pair_object",
        Query_iter_pair_object
    },
    {
        "iter_query_in_system",
        Query_iter_query_in_system
    },
    {
        "iter_type",
        Query_iter_type
    }
};

bake_test_case QueryBuilder_testcases[] = {
    {
        "builder_assign_same_type",
        QueryBuilder_builder_assign_same_type
    },
    {
        "builder_assign_from_empty",
        QueryBuilder_builder_assign_from_empty
    },
    {
        "builder_assign_to_empty",
        QueryBuilder_builder_assign_to_empty
    },
    {
        "builder_build",
        QueryBuilder_builder_build
    },
    {
        "builder_build_to_auto",
        QueryBuilder_builder_build_to_auto
    },
    {
        "builder_build_n_statements",
        QueryBuilder_builder_build_n_statements
    },
    {
        "1_type",
        QueryBuilder_1_type
    },
    {
        "add_1_type",
        QueryBuilder_add_1_type
    },
    {
        "add_2_types",
        QueryBuilder_add_2_types
    },
    {
        "add_1_type_w_1_type",
        QueryBuilder_add_1_type_w_1_type
    },
    {
        "add_2_types_w_1_type",
        QueryBuilder_add_2_types_w_1_type
    },
    {
        "add_pair",
        QueryBuilder_add_pair
    },
    {
        "add_not",
        QueryBuilder_add_not
    },
    {
        "add_or",
        QueryBuilder_add_or
    },
    {
        "add_optional",
        QueryBuilder_add_optional
    },
    {
        "ptr_type",
        QueryBuilder_ptr_type
    },
    {
        "const_type",
        QueryBuilder_const_type
    },
    {
        "string_term",
        QueryBuilder_string_term
    },
    {
        "singleton_term",
        QueryBuilder_singleton_term
    },
    {
        "isa_superset_term",
        QueryBuilder_isa_superset_term
    },
    {
        "isa_self_superset_term",
        QueryBuilder_isa_self_superset_term
    },
    {
        "childof_superset_term",
        QueryBuilder_childof_superset_term
    },
    {
        "childof_self_superset_term",
        QueryBuilder_childof_self_superset_term
    },
    {
        "isa_superset_term_w_each",
        QueryBuilder_isa_superset_term_w_each
    },
    {
        "isa_self_superset_term_w_each",
        QueryBuilder_isa_self_superset_term_w_each
    },
    {
        "childof_superset_term_w_each",
        QueryBuilder_childof_superset_term_w_each
    },
    {
        "childof_self_superset_term_w_each",
        QueryBuilder_childof_self_superset_term_w_each
    },
    {
        "isa_superset_shortcut",
        QueryBuilder_isa_superset_shortcut
    },
    {
        "isa_superset_shortcut_w_self",
        QueryBuilder_isa_superset_shortcut_w_self
    },
    {
        "childof_superset_shortcut",
        QueryBuilder_childof_superset_shortcut
    },
    {
        "childof_superset_shortcut_w_self",
        QueryBuilder_childof_superset_shortcut_w_self
    },
    {
        "isa_supetset_max_depth_1",
        QueryBuilder_isa_supetset_max_depth_1
    },
    {
        "isa_supetset_max_depth_2",
        QueryBuilder_isa_supetset_max_depth_2
    },
    {
        "isa_supetset_min_depth_2",
        QueryBuilder_isa_supetset_min_depth_2
    },
    {
        "isa_supetset_min_depth_2_max_depth_3",
        QueryBuilder_isa_supetset_min_depth_2_max_depth_3
    },
    {
        "role",
        QueryBuilder_role
    },
    {
        "relation",
        QueryBuilder_relation
    },
    {
        "relation_w_object_wildcard",
        QueryBuilder_relation_w_object_wildcard
    },
    {
        "relation_w_predicate_wildcard",
        QueryBuilder_relation_w_predicate_wildcard
    },
    {
        "add_pair_w_rel_type",
        QueryBuilder_add_pair_w_rel_type
    },
    {
        "template_term",
        QueryBuilder_template_term
    },
    {
        "explicit_subject_w_id",
        QueryBuilder_explicit_subject_w_id
    },
    {
        "explicit_subject_w_type",
        QueryBuilder_explicit_subject_w_type
    },
    {
        "explicit_object_w_id",
        QueryBuilder_explicit_object_w_id
    },
    {
        "explicit_object_w_type",
        QueryBuilder_explicit_object_w_type
    },
    {
        "explicit_term",
        QueryBuilder_explicit_term
    },
    {
        "explicit_term_w_type",
        QueryBuilder_explicit_term_w_type
    },
    {
        "explicit_term_w_pair_type",
        QueryBuilder_explicit_term_w_pair_type
    },
    {
        "explicit_term_w_id",
        QueryBuilder_explicit_term_w_id
    },
    {
        "explicit_term_w_pair_id",
        QueryBuilder_explicit_term_w_pair_id
    },
    {
        "1_term_to_empty",
        QueryBuilder_1_term_to_empty
    },
    {
        "2_subsequent_args",
        QueryBuilder_2_subsequent_args
    }
};

bake_test_case SystemBuilder_testcases[] = {
    {
        "builder_assign_same_type",
        SystemBuilder_builder_assign_same_type
    },
    {
        "builder_assign_from_empty",
        SystemBuilder_builder_assign_from_empty
    },
    {
        "builder_build_to_auto",
        SystemBuilder_builder_build_to_auto
    },
    {
        "builder_build_n_statements",
        SystemBuilder_builder_build_n_statements
    },
    {
        "1_type",
        SystemBuilder_1_type
    },
    {
        "add_1_type",
        SystemBuilder_add_1_type
    },
    {
        "add_2_types",
        SystemBuilder_add_2_types
    },
    {
        "add_1_type_w_1_type",
        SystemBuilder_add_1_type_w_1_type
    },
    {
        "add_2_types_w_1_type",
        SystemBuilder_add_2_types_w_1_type
    },
    {
        "add_pair",
        SystemBuilder_add_pair
    },
    {
        "add_not",
        SystemBuilder_add_not
    },
    {
        "add_or",
        SystemBuilder_add_or
    },
    {
        "add_optional",
        SystemBuilder_add_optional
    },
    {
        "ptr_type",
        SystemBuilder_ptr_type
    },
    {
        "const_type",
        SystemBuilder_const_type
    },
    {
        "string_term",
        SystemBuilder_string_term
    },
    {
        "singleton_term",
        SystemBuilder_singleton_term
    }
};

bake_test_case Observer_testcases[] = {
    {
        "2_terms_on_add",
        Observer_2_terms_on_add
    },
    {
        "2_terms_on_remove",
        Observer_2_terms_on_remove
    },
    {
        "2_terms_on_set",
        Observer_2_terms_on_set
    },
    {
        "2_terms_un_set",
        Observer_2_terms_un_set
    },
    {
        "observer_w_self",
        Observer_observer_w_self
    }
};

bake_test_case ComponentLifecycle_testcases[] = {
    {
        "ctor_on_add",
        ComponentLifecycle_ctor_on_add
    },
    {
        "dtor_on_remove",
        ComponentLifecycle_dtor_on_remove
    },
    {
        "move_on_add",
        ComponentLifecycle_move_on_add
    },
    {
        "move_on_remove",
        ComponentLifecycle_move_on_remove
    },
    {
        "copy_on_set",
        ComponentLifecycle_copy_on_set
    },
    {
        "copy_on_override",
        ComponentLifecycle_copy_on_override
    },
    {
        "non_pod_add",
        ComponentLifecycle_non_pod_add
    },
    {
        "non_pod_remove",
        ComponentLifecycle_non_pod_remove
    },
    {
        "non_pod_set",
        ComponentLifecycle_non_pod_set
    },
    {
        "non_pod_override",
        ComponentLifecycle_non_pod_override
    },
    {
        "get_mut_new",
        ComponentLifecycle_get_mut_new
    },
    {
        "get_mut_existing",
        ComponentLifecycle_get_mut_existing
    },
    {
        "pod_component",
        ComponentLifecycle_pod_component
    },
    {
        "relocatable_component",
        ComponentLifecycle_relocatable_component
    },
    {
        "implicit_component",
        ComponentLifecycle_implicit_component
    },
    {
        "implicit_after_query",
        ComponentLifecycle_implicit_after_query
    },
    {
        "deleted_copy",
        ComponentLifecycle_deleted_copy
    },
    {
        "no_default_ctor",
        ComponentLifecycle_no_default_ctor
    },
    {
        "default_init",
        ComponentLifecycle_default_init
    },
    {
        "no_default_ctor_add",
        ComponentLifecycle_no_default_ctor_add
    },
    {
        "no_default_ctor_add_relation",
        ComponentLifecycle_no_default_ctor_add_relation
    },
    {
        "no_default_ctor_add_object",
        ComponentLifecycle_no_default_ctor_add_object
    },
    {
        "no_default_ctor_set",
        ComponentLifecycle_no_default_ctor_set
    },
    {
        "no_copy_ctor",
        ComponentLifecycle_no_copy_ctor
    },
    {
        "no_move_ctor",
        ComponentLifecycle_no_move_ctor
    },
    {
        "no_copy_assign",
        ComponentLifecycle_no_copy_assign
    },
    {
        "no_move_assign",
        ComponentLifecycle_no_move_assign
    },
    {
        "no_copy",
        ComponentLifecycle_no_copy
    },
    {
        "no_move",
        ComponentLifecycle_no_move
    },
    {
        "no_dtor",
        ComponentLifecycle_no_dtor
    },
    {
        "flecs_ctor",
        ComponentLifecycle_flecs_ctor
    },
    {
        "flecs_ctor_w_default_ctor",
        ComponentLifecycle_flecs_ctor_w_default_ctor
    },
    {
        "default_ctor_w_value_ctor",
        ComponentLifecycle_default_ctor_w_value_ctor
    },
    {
        "flecs_ctor_w_value_ctor",
        ComponentLifecycle_flecs_ctor_w_value_ctor
    },
    {
        "no_default_ctor_move_ctor_on_set",
        ComponentLifecycle_no_default_ctor_move_ctor_on_set
    },
    {
        "emplace_w_ctor",
        ComponentLifecycle_emplace_w_ctor
    },
    {
        "emplace_no_default_ctor",
        ComponentLifecycle_emplace_no_default_ctor
    },
    {
        "emplace_existing",
        ComponentLifecycle_emplace_existing
    },
    {
        "emplace_singleton",
        ComponentLifecycle_emplace_singleton
    }
};

bake_test_case Refs_testcases[] = {
    {
        "get_ref",
        Refs_get_ref
    },
    {
        "ref_after_add",
        Refs_ref_after_add
    },
    {
        "ref_after_remove",
        Refs_ref_after_remove
    },
    {
        "ref_after_set",
        Refs_ref_after_set
    },
    {
        "ref_before_set",
        Refs_ref_before_set
    }
};

bake_test_case Module_testcases[] = {
    {
        "import",
        Module_import
    },
    {
        "lookup_from_scope",
        Module_lookup_from_scope
    },
    {
        "nested_module",
        Module_nested_module
    },
    {
        "nested_type_module",
        Module_nested_type_module
    },
    {
        "module_type_w_explicit_name",
        Module_module_type_w_explicit_name
    },
    {
        "component_redefinition_outside_module",
        Module_component_redefinition_outside_module
    },
    {
        "module_tag_on_namespace",
        Module_module_tag_on_namespace
    },
    {
        "dtor_on_fini",
        Module_dtor_on_fini
    }
};

bake_test_case ImplicitComponents_testcases[] = {
    {
        "add",
        ImplicitComponents_add
    },
    {
        "remove",
        ImplicitComponents_remove
    },
    {
        "has",
        ImplicitComponents_has
    },
    {
        "set",
        ImplicitComponents_set
    },
    {
        "get",
        ImplicitComponents_get
    },
    {
        "add_pair",
        ImplicitComponents_add_pair
    },
    {
        "remove_pair",
        ImplicitComponents_remove_pair
    },
    {
        "module",
        ImplicitComponents_module
    },
    {
        "system",
        ImplicitComponents_system
    },
    {
        "system_optional",
        ImplicitComponents_system_optional
    },
    {
        "system_const",
        ImplicitComponents_system_const
    },
    {
        "query",
        ImplicitComponents_query
    },
    {
        "implicit_name",
        ImplicitComponents_implicit_name
    },
    {
        "reinit",
        ImplicitComponents_reinit
    },
    {
        "reinit_scoped",
        ImplicitComponents_reinit_scoped
    },
    {
        "reinit_w_lifecycle",
        ImplicitComponents_reinit_w_lifecycle
    },
    {
        "first_use_in_system",
        ImplicitComponents_first_use_in_system
    },
    {
        "first_use_tag_in_system",
        ImplicitComponents_first_use_tag_in_system
    },
    {
        "use_const",
        ImplicitComponents_use_const
    },
    {
        "use_const_w_stage",
        ImplicitComponents_use_const_w_stage
    },
    {
        "use_const_w_threads",
        ImplicitComponents_use_const_w_threads
    },
    {
        "implicit_base",
        ImplicitComponents_implicit_base
    },
    {
        "implicit_const",
        ImplicitComponents_implicit_const
    },
    {
        "implicit_ref",
        ImplicitComponents_implicit_ref
    },
    {
        "implicit_ptr",
        ImplicitComponents_implicit_ptr
    },
    {
        "implicit_const_ref",
        ImplicitComponents_implicit_const_ref
    }
};

bake_test_case Snapshot_testcases[] = {
    {
        "simple_snapshot",
        Snapshot_simple_snapshot
    },
    {
        "snapshot_iter",
        Snapshot_snapshot_iter
    },
    {
        "snapshot_iter_w_filter",
        Snapshot_snapshot_iter_w_filter
    }
};

bake_test_case WorldFactory_testcases[] = {
    {
        "entity",
        WorldFactory_entity
    },
    {
        "entity_w_name",
        WorldFactory_entity_w_name
    },
    {
        "entity_w_id",
        WorldFactory_entity_w_id
    },
    {
        "prefab",
        WorldFactory_prefab
    },
    {
        "prefab_w_name",
        WorldFactory_prefab_w_name
    },
    {
        "type",
        WorldFactory_type
    },
    {
        "type_w_name",
        WorldFactory_type_w_name
    },
    {
        "system",
        WorldFactory_system
    },
    {
        "system_w_name",
        WorldFactory_system_w_name
    },
    {
        "system_w_expr",
        WorldFactory_system_w_expr
    },
    {
        "query",
        WorldFactory_query
    },
    {
        "query_w_expr",
        WorldFactory_query_w_expr
    },
    {
        "snapshot",
        WorldFactory_snapshot
    },
    {
        "module",
        WorldFactory_module
    },
    {
        "module_w_name",
        WorldFactory_module_w_name
    }
};

bake_test_case World_testcases[] = {
    {
        "builtin_components",
        World_builtin_components
    },
    {
        "multi_world_empty",
        World_multi_world_empty
    },
    {
        "multi_world_component",
        World_multi_world_component
    },
    {
        "multi_world_component_namespace",
        World_multi_world_component_namespace
    },
    {
        "multi_world_module",
        World_multi_world_module
    },
    {
        "type_id",
        World_type_id
    },
    {
        "different_comp_same_name",
        World_different_comp_same_name
    },
    {
        "reregister_after_reset",
        World_reregister_after_reset
    },
    {
        "reregister_after_reset_w_namespace",
        World_reregister_after_reset_w_namespace
    },
    {
        "reregister_namespace",
        World_reregister_namespace
    },
    {
        "implicit_reregister_after_reset",
        World_implicit_reregister_after_reset
    },
    {
        "reregister_after_reset_different_name",
        World_reregister_after_reset_different_name
    },
    {
        "reimport",
        World_reimport
    },
    {
        "reimport_module_after_reset",
        World_reimport_module_after_reset
    },
    {
        "reimport_module_new_world",
        World_reimport_module_new_world
    },
    {
        "reimport_namespaced_module",
        World_reimport_namespaced_module
    },
    {
        "c_interop_module",
        World_c_interop_module
    },
    {
        "c_interop_after_reset",
        World_c_interop_after_reset
    },
    {
        "implicit_register_w_new_world",
        World_implicit_register_w_new_world
    },
    {
        "count",
        World_count
    },
    {
        "staged_count",
        World_staged_count
    },
    {
        "async_stage_add",
        World_async_stage_add
    },
    {
        "with_tag",
        World_with_tag
    },
    {
        "with_tag_type",
        World_with_tag_type
    },
    {
        "with_relation",
        World_with_relation
    },
    {
        "with_relation_type",
        World_with_relation_type
    },
    {
        "with_relation_object_type",
        World_with_relation_object_type
    },
    {
        "with_tag_nested",
        World_with_tag_nested
    },
    {
        "with_scope",
        World_with_scope
    },
    {
        "with_scope_nested",
        World_with_scope_nested
    },
    {
        "recursive_lookup",
        World_recursive_lookup
    },
    {
        "type_w_tag_name",
        World_type_w_tag_name
    },
    {
        "entity_w_tag_name",
        World_entity_w_tag_name
    },
    {
        "template_component_name",
        World_template_component_name
    },
    {
        "template_component_w_namespace_name",
        World_template_component_w_namespace_name
    },
    {
        "template_component_w_same_namespace_name",
        World_template_component_w_same_namespace_name
    },
    {
        "template_component_w_namespace_name_and_namespaced_arg",
        World_template_component_w_namespace_name_and_namespaced_arg
    },
    {
        "template_component_w_same_namespace_name_and_namespaced_arg",
        World_template_component_w_same_namespace_name_and_namespaced_arg
    }
};

bake_test_case Singleton_testcases[] = {
    {
        "set_get_singleton",
        Singleton_set_get_singleton
    },
    {
        "get_mut_singleton",
        Singleton_get_mut_singleton
    },
    {
        "emplace_singleton",
        Singleton_emplace_singleton
    },
    {
        "modified_singleton",
        Singleton_modified_singleton
    },
    {
        "patch_singleton",
        Singleton_patch_singleton
    },
    {
        "add_singleton",
        Singleton_add_singleton
    },
    {
        "remove_singleton",
        Singleton_remove_singleton
    },
    {
        "has_singleton",
        Singleton_has_singleton
    },
    {
        "singleton_system",
        Singleton_singleton_system
    },
    {
        "get_singleton",
        Singleton_get_singleton
    },
    {
        "type_id_from_world",
        Singleton_type_id_from_world
    }
};

bake_test_case Misc_testcases[] = {
    {
        "string_compare_w_char_ptr",
        Misc_string_compare_w_char_ptr
    },
    {
        "string_compare_w_char_ptr_length_diff",
        Misc_string_compare_w_char_ptr_length_diff
    },
    {
        "string_compare_w_string",
        Misc_string_compare_w_string
    },
    {
        "string_view_compare_w_char_ptr",
        Misc_string_view_compare_w_char_ptr
    },
    {
        "string_view_compare_w_string",
        Misc_string_view_compare_w_string
    },
    {
        "string_compare_nullptr",
        Misc_string_compare_nullptr
    },
    {
        "nullptr_string_compare",
        Misc_nullptr_string_compare
    },
    {
        "nullptr_string_compare_nullptr",
        Misc_nullptr_string_compare_nullptr
    }
};

static bake_test_suite suites[] = {
    {
        "Entity",
        NULL,
        NULL,
        148,
        Entity_testcases
    },
    {
        "Pairs",
        NULL,
        NULL,
        52,
        Pairs_testcases
    },
    {
        "Switch",
        NULL,
        NULL,
        5,
        Switch_testcases
    },
    {
        "Paths",
        NULL,
        NULL,
        12,
        Paths_testcases
    },
    {
        "Type",
        NULL,
        NULL,
        15,
        Type_testcases
    },
    {
        "System",
        NULL,
        NULL,
        42,
        System_testcases
    },
    {
        "Trigger",
        NULL,
        NULL,
        6,
        Trigger_testcases
    },
    {
        "Query",
        NULL,
        NULL,
        45,
        Query_testcases
    },
    {
        "QueryBuilder",
        NULL,
        NULL,
        52,
        QueryBuilder_testcases
    },
    {
        "SystemBuilder",
        NULL,
        NULL,
        17,
        SystemBuilder_testcases
    },
    {
        "Observer",
        NULL,
        NULL,
        5,
        Observer_testcases
    },
    {
        "ComponentLifecycle",
        NULL,
        NULL,
        39,
        ComponentLifecycle_testcases
    },
    {
        "Refs",
        NULL,
        NULL,
        5,
        Refs_testcases
    },
    {
        "Module",
        NULL,
        NULL,
        8,
        Module_testcases
    },
    {
        "ImplicitComponents",
        NULL,
        NULL,
        26,
        ImplicitComponents_testcases
    },
    {
        "Snapshot",
        NULL,
        NULL,
        3,
        Snapshot_testcases
    },
    {
        "WorldFactory",
        NULL,
        NULL,
        15,
        WorldFactory_testcases
    },
    {
        "World",
        NULL,
        NULL,
        38,
        World_testcases
    },
    {
        "Singleton",
        NULL,
        NULL,
        11,
        Singleton_testcases
    },
    {
        "Misc",
        Misc_setup,
        NULL,
        8,
        Misc_testcases
    }
};

int main(int argc, char *argv[]) {
    ut_init(argv[0]);
    return bake_test_run("cpp_api", argc, argv, suites, 20);
}
