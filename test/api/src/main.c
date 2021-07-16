
/* A friendly warning from bake.test
 * ----------------------------------------------------------------------------
 * This file is generated. To add/remove testcases modify the 'project.json' of
 * the test project. ANY CHANGE TO THIS FILE IS LOST AFTER (RE)BUILDING!
 * ----------------------------------------------------------------------------
 */

#include <api.h>

// Testsuite 'Entity'
void Entity_init_id(void);
void Entity_init_id_name(void);
void Entity_init_id_path(void);
void Entity_init_id_add_1_comp(void);
void Entity_init_id_add_2_comp(void);
void Entity_init_id_w_scope(void);
void Entity_init_id_name_w_scope(void);
void Entity_init_id_path_w_scope(void);
void Entity_init_id_name_1_comp(void);
void Entity_init_id_name_2_comp(void);
void Entity_init_id_name_2_comp_w_scope(void);
void Entity_id_add_1_comp(void);
void Entity_id_add_2_comp(void);
void Entity_id_remove_1_comp(void);
void Entity_id_remove_2_comp(void);
void Entity_init_id_path_w_sep(void);
void Entity_find_id_name(void);
void Entity_find_w_existing_id_name(void);
void Entity_find_id_name_w_scope(void);
void Entity_find_id_path(void);
void Entity_find_id_path_w_scope(void);
void Entity_find_id_name_match(void);
void Entity_find_id_name_match_w_scope(void);
void Entity_find_id_path_match(void);
void Entity_find_id_path_match_w_scope(void);
void Entity_find_id_name_mismatch(void);
void Entity_find_id_name_mismatch_w_scope(void);
void Entity_find_id_path_mismatch(void);
void Entity_find_id_path_mismatch_w_scope(void);
void Entity_find_id_add_1_comp(void);
void Entity_find_id_add_2_comp(void);
void Entity_find_id_remove_1_comp(void);
void Entity_find_id_remove_2_comp(void);
void Entity_init_w_scope_name(void);
void Entity_init_w_core_name(void);
void Entity_init_w_with(void);
void Entity_init_w_with_w_name(void);
void Entity_init_w_with_w_scope(void);
void Entity_init_w_with_w_name_scope(void);

// Testsuite 'New'
void New_setup(void);
void New_empty(void);
void New_component(void);
void New_type(void);
void New_type_of_2(void);
void New_type_w_type(void);
void New_type_w_2_types(void);
void New_type_mixed(void);
void New_tag(void);
void New_type_w_tag(void);
void New_type_w_2_tags(void);
void New_type_w_tag_mixed(void);
void New_redefine_component(void);
void New_recycle_id_empty(void);
void New_recycle_id_w_entity(void);
void New_recycle_id_w_type(void);
void New_recycle_empty_staged_delete(void);
void New_recycle_staged_delete(void);
void New_new_id(void);
void New_new_component_id(void);
void New_new_hi_component_id(void);
void New_new_component_id_skip_used(void);
void New_new_component_id_skip_to_hi_id(void);
void New_new_w_entity_0(void);
void New_create_w_explicit_id_2_worlds(void);
void New_new_w_id_0_w_with(void);
void New_new_w_id_w_with(void);
void New_new_w_type_0_w_with(void);
void New_new_w_type_w_with(void);
void New_new_w_id_w_with_w_scope(void);
void New_new_w_type_w_with_w_scope(void);
void New_new_w_id_w_with_defer(void);
void New_new_w_id_w_with_defer_w_scope(void);
void New_new_w_type_w_with_defer(void);
void New_new_w_type_w_with_defer_w_scope(void);

// Testsuite 'New_w_Count'
void New_w_Count_empty(void);
void New_w_Count_component(void);
void New_w_Count_type(void);
void New_w_Count_type_of_2(void);
void New_w_Count_type_w_type(void);
void New_w_Count_type_w_2_types(void);
void New_w_Count_type_mixed(void);
void New_w_Count_tag(void);
void New_w_Count_type_w_tag(void);
void New_w_Count_type_w_2_tags(void);
void New_w_Count_type_w_tag_mixed(void);
void New_w_Count_new_w_data_1_comp(void);
void New_w_Count_new_w_data_2_comp(void);
void New_w_Count_new_w_data_w_tag(void);
void New_w_Count_new_w_data_w_comp_and_tag(void);
void New_w_Count_new_w_data_pair(void);
void New_w_Count_new_w_data_pair(void);
void New_w_Count_new_w_data_2_comp_1_not_set(void);
void New_w_Count_new_w_on_add_on_set_monitor(void);
void New_w_Count_new_w_data_override_set_comp(void);
void New_w_Count_new_w_data_override_set_pair(void);

// Testsuite 'Add'
void Add_zero(void);
void Add_component(void);
void Add_component_again(void);
void Add_2_components(void);
void Add_2_components_again(void);
void Add_2_components_overlap(void);
void Add_type(void);
void Add_type_of_2(void);
void Add_type_w_type(void);
void Add_type_w_2_types(void);
void Add_type_mixed(void);
void Add_type_again(void);
void Add_type_overlap(void);
void Add_type_again_component(void);
void Add_type_overlap_component(void);
void Add_component_to_nonempty(void);
void Add_component_to_nonempty_again(void);
void Add_component_to_nonempty_overlap(void);
void Add_type_to_nonempty(void);
void Add_type_to_nonempty_again(void);
void Add_type_to_nonempty_overlap(void);
void Add_tag(void);
void Add_type_w_tag(void);
void Add_type_w_2_tags(void);
void Add_type_w_tag_mixed(void);
void Add_add_remove(void);
void Add_add_remove_same(void);
void Add_add_remove_entity(void);
void Add_add_remove_entity_same(void);
void Add_add_2_remove(void);
void Add_add_entity(void);
void Add_remove_entity(void);
void Add_add_0_entity(void);
void Add_remove_0_entity(void);
void Add_add_w_xor(void);
void Add_add_same_w_xor(void);
void Add_add_after_remove_xor(void);

// Testsuite 'Switch'
void Switch_setup(void);
void Switch_get_case_empty(void);
void Switch_get_case_no_switch(void);
void Switch_get_case_unset(void);
void Switch_get_case_set(void);
void Switch_get_case_change(void);
void Switch_remove_case(void);
void Switch_remove_last(void);
void Switch_3_entities_same_case(void);
void Switch_2_entities_1_change_case(void);
void Switch_3_entities_change_case(void);
void Switch_query_switch(void);
void Switch_query_1_case_1_type(void);
void Switch_query_1_case_2_types(void);
void Switch_query_2_cases_1_type(void);
void Switch_query_2_cases_2_types(void);
void Switch_query_after_remove(void);
void Switch_add_switch_in_stage(void);
void Switch_add_case_in_stage(void);
void Switch_change_case_in_stage(void);
void Switch_change_one_case_in_stage(void);
void Switch_remove_switch_in_stage(void);
void Switch_switch_no_match_for_case(void);
void Switch_empty_entity_has_case(void);
void Switch_zero_entity_has_case(void);
void Switch_add_to_entity_w_switch(void);
void Switch_add_pair_to_entity_w_switch(void);
void Switch_sort(void);
void Switch_recycled_tags(void);
void Switch_query_recycled_tags(void);

// Testsuite 'EnabledComponents'
void EnabledComponents_is_component_enabled(void);
void EnabledComponents_is_empty_entity_disabled(void);
void EnabledComponents_is_0_entity_disabled(void);
void EnabledComponents_is_0_component_disabled(void);
void EnabledComponents_is_nonexist_component_disabled(void);
void EnabledComponents_is_enabled_component_enabled(void);
void EnabledComponents_is_disabled_component_enabled(void);
void EnabledComponents_has_enabled_component(void);
void EnabledComponents_is_enabled_after_add(void);
void EnabledComponents_is_enabled_after_remove(void);
void EnabledComponents_is_enabled_after_disable(void);
void EnabledComponents_is_disabled_after_enable(void);
void EnabledComponents_is_enabled_randomized(void);
void EnabledComponents_is_enabled_after_add_randomized(void);
void EnabledComponents_is_enabled_after_randomized_add_randomized(void);
void EnabledComponents_is_enabled_2(void);
void EnabledComponents_is_enabled_3(void);
void EnabledComponents_is_enabled_2_after_add(void);
void EnabledComponents_is_enabled_3_after_add(void);
void EnabledComponents_query_disabled(void);
void EnabledComponents_query_disabled_skip_initial(void);
void EnabledComponents_query_mod_2(void);
void EnabledComponents_query_mod_8(void);
void EnabledComponents_query_mod_64(void);
void EnabledComponents_query_mod_256(void);
void EnabledComponents_query_mod_1024(void);
void EnabledComponents_query_enable_mod_10(void);
void EnabledComponents_query_mod_2_2_bitsets(void);
void EnabledComponents_query_mod_8_2_bitsets(void);
void EnabledComponents_query_mod_64_2_bitsets(void);
void EnabledComponents_query_mod_256_2_bitsets(void);
void EnabledComponents_query_mod_1024_2_bitsets(void);
void EnabledComponents_query_randomized_2_bitsets(void);
void EnabledComponents_query_randomized_3_bitsets(void);
void EnabledComponents_query_randomized_4_bitsets(void);
void EnabledComponents_defer_enable(void);
void EnabledComponents_sort(void);

// Testsuite 'Remove'
void Remove_zero(void);
void Remove_zero_from_nonzero(void);
void Remove_1_of_1(void);
void Remove_1_of_1_again(void);
void Remove_1_of_2(void);
void Remove_2_of_2(void);
void Remove_2_of_3(void);
void Remove_2_again(void);
void Remove_2_overlap(void);
void Remove_type_of_1_of_2(void);
void Remove_type_of_2_of_2(void);
void Remove_type_of_2_of_3(void);
void Remove_1_from_empty(void);
void Remove_type_from_empty(void);
void Remove_not_added(void);

// Testsuite 'Parser'
void Parser_resolve_this(void);
void Parser_resolve_wildcard(void);
void Parser_resolve_is_a(void);
void Parser_0(void);
void Parser_component_implicit_subject(void);
void Parser_component_explicit_subject(void);
void Parser_component_explicit_subject_this(void);
void Parser_component_explicit_subject_this_by_name(void);
void Parser_component_explicit_subject_wildcard(void);
void Parser_pair_implicit_subject(void);
void Parser_pair_implicit_subject_wildcard_pred(void);
void Parser_pair_implicit_subject_wildcard_obj(void);
void Parser_pair_implicit_subject_this_pred(void);
void Parser_pair_implicit_subject_this_obj(void);
void Parser_pair_explicit_subject(void);
void Parser_pair_explicit_subject_this(void);
void Parser_pair_explicit_subject_this_by_name(void);
void Parser_pair_explicit_subject_wildcard_pred(void);
void Parser_pair_explicit_subject_wildcard_subj(void);
void Parser_pair_explicit_subject_wildcard_obj(void);
void Parser_in_component_implicit_subject(void);
void Parser_in_component_explicit_subject(void);
void Parser_in_pair_implicit_subject(void);
void Parser_in_pair_explicit_subject(void);
void Parser_inout_component_implicit_subject(void);
void Parser_inout_component_explicit_subject(void);
void Parser_inout_pair_implicit_subject(void);
void Parser_inout_pair_explicit_subject(void);
void Parser_out_component_implicit_subject(void);
void Parser_out_component_explicit_subject(void);
void Parser_out_pair_implicit_subject(void);
void Parser_out_pair_explicit_subject(void);
void Parser_component_singleton(void);
void Parser_this_singleton(void);
void Parser_component_implicit_no_subject(void);
void Parser_component_explicit_no_subject(void);
void Parser_pair_no_subject(void);
void Parser_variable_single_char(void);
void Parser_variable_multi_char(void);
void Parser_variable_multi_char_w_underscore(void);
void Parser_variable_multi_char_w_number(void);
void Parser_escaped_all_caps_single_char(void);
void Parser_escaped_all_caps_multi_char(void);
void Parser_component_not(void);
void Parser_pair_implicit_subject_not(void);
void Parser_pair_explicit_subject_not(void);
void Parser_2_component_not(void);
void Parser_2_component_not_no_space(void);
void Parser_component_optional(void);
void Parser_2_component_optional(void);
void Parser_2_component_optional_no_space(void);
void Parser_from_and(void);
void Parser_from_or(void);
void Parser_from_not(void);
void Parser_pair_implicit_subject_optional(void);
void Parser_pair_explicit_subject_optional(void);
void Parser_pred_implicit_subject_w_role(void);
void Parser_pred_explicit_subject_w_role(void);
void Parser_pred_no_subject_w_role(void);
void Parser_pair_implicit_subject_w_role(void);
void Parser_pair_explicit_subject_w_role(void);
void Parser_inout_role_pred_implicit_subject(void);
void Parser_inout_role_pred_no_subject(void);
void Parser_inout_role_pred_explicit_subject(void);
void Parser_inout_role_pair_implicit_subject(void);
void Parser_inout_role_pair_explicit_subject(void);
void Parser_2_pred_implicit_subject(void);
void Parser_2_pred_no_subject(void);
void Parser_2_pred_explicit_subject(void);
void Parser_2_pair_implicit_subject(void);
void Parser_2_pair_explicit_subject(void);
void Parser_2_pred_role(void);
void Parser_2_pair_implicit_subj_role(void);
void Parser_2_pair_explicit_subj_role(void);
void Parser_2_or_pred_implicit_subj(void);
void Parser_2_or_pred_explicit_subj(void);
void Parser_2_or_pair_implicit_subj(void);
void Parser_2_or_pair_explicit_subj(void);
void Parser_2_or_pred_inout(void);
void Parser_1_digit_pred_implicit_subj(void);
void Parser_1_digit_pred_no_subj(void);
void Parser_1_digit_pred_explicit_subj(void);
void Parser_1_digit_pair_implicit_subj(void);
void Parser_1_digit_pair_explicit_subj(void);
void Parser_pred_implicit_subject_self(void);
void Parser_pred_implicit_subject_superset(void);
void Parser_pred_implicit_subject_subset(void);
void Parser_pred_implicit_subject_superset_inclusive(void);
void Parser_pred_implicit_subject_subset_inclusive(void);
void Parser_pred_implicit_subject_superset_cascade(void);
void Parser_pred_implicit_subject_subset_cascade(void);
void Parser_pred_implicit_subject_superset_inclusive_cascade(void);
void Parser_pred_implicit_subject_subset_inclusive_cascade(void);
void Parser_pred_implicit_subject_implicit_superset_cascade(void);
void Parser_pred_implicit_subject_implicit_superset_inclusive_cascade(void);
void Parser_pred_implicit_subject_implicit_superset_cascade_w_rel(void);
void Parser_pred_implicit_subject_implicit_superset_inclusive_cascade_w_rel(void);
void Parser_pred_implicit_subject_superset_depth_1_digit(void);
void Parser_pred_implicit_subject_subset_depth_1_digit(void);
void Parser_pred_implicit_subject_superset_depth_2_digits(void);
void Parser_pred_implicit_subject_subset_depth_2_digits(void);
void Parser_pred_implicit_superset_min_max_depth(void);
void Parser_pred_implicit_superset_childof_min_max_depth(void);
void Parser_pred_implicit_subject_superset_childof(void);
void Parser_pred_implicit_subject_cascade_superset_childof(void);
void Parser_pred_implicit_subject_superset_cascade_childof(void);
void Parser_pred_implicit_subject_superset_cascade_childof_optional(void);

// Testsuite 'GlobalComponentIds'
void GlobalComponentIds_declare(void);
void GlobalComponentIds_declare_w_entity(void);
void GlobalComponentIds_declare_2_world(void);
void GlobalComponentIds_declare_tag(void);
void GlobalComponentIds_declare_tag_w_entity(void);
void GlobalComponentIds_declare_entity(void);
void GlobalComponentIds_declare_type(void);

// Testsuite 'Hierarchies'
void Hierarchies_setup(void);
void Hierarchies_empty_scope(void);
void Hierarchies_get_parent(void);
void Hierarchies_get_parent_from_nested(void);
void Hierarchies_get_parent_from_nested_2(void);
void Hierarchies_get_parent_from_root(void);
void Hierarchies_tree_iter_empty(void);
void Hierarchies_tree_iter_1_table(void);
void Hierarchies_tree_iter_2_tables(void);
void Hierarchies_tree_iter_w_filter(void);
void Hierarchies_path_depth_0(void);
void Hierarchies_path_depth_1(void);
void Hierarchies_path_depth_2(void);
void Hierarchies_rel_path_from_root(void);
void Hierarchies_rel_path_from_self(void);
void Hierarchies_rel_path_depth_1(void);
void Hierarchies_rel_path_depth_2(void);
void Hierarchies_rel_path_no_match(void);
void Hierarchies_path_for_component_0(void);
void Hierarchies_path_for_component_1(void);
void Hierarchies_path_for_component_2(void);
void Hierarchies_path_custom_sep(void);
void Hierarchies_path_custom_prefix(void);
void Hierarchies_path_prefix_rel_match(void);
void Hierarchies_path_prefix_rel_no_match(void);
void Hierarchies_fullpath_for_core(void);
void Hierarchies_path_w_number(void);
void Hierarchies_lookup_depth_0(void);
void Hierarchies_lookup_depth_1(void);
void Hierarchies_lookup_depth_2(void);
void Hierarchies_lookup_rel_0(void);
void Hierarchies_lookup_rel_1(void);
void Hierarchies_lookup_rel_2(void);
void Hierarchies_lookup_custom_sep(void);
void Hierarchies_lookup_custom_prefix(void);
void Hierarchies_lookup_custom_prefix_from_root(void);
void Hierarchies_lookup_self(void);
void Hierarchies_lookup_in_parent_from_scope(void);
void Hierarchies_lookup_in_root_from_scope(void);
void Hierarchies_lookup_number(void);
void Hierarchies_delete_children(void);
void Hierarchies_scope_set(void);
void Hierarchies_scope_set_again(void);
void Hierarchies_scope_set_w_new(void);
void Hierarchies_scope_set_w_new_staged(void);
void Hierarchies_scope_set_w_lookup(void);
void Hierarchies_scope_component(void);
void Hierarchies_scope_component_no_macro(void);
void Hierarchies_new_from_path_depth_0(void);
void Hierarchies_new_from_path_depth_1(void);
void Hierarchies_new_from_path_depth_2(void);
void Hierarchies_new_from_path_existing_depth_0(void);
void Hierarchies_new_from_path_existing_depth_1(void);
void Hierarchies_new_from_path_existing_depth_2(void);
void Hierarchies_add_path_depth_0(void);
void Hierarchies_add_path_depth_1(void);
void Hierarchies_add_path_depth_2(void);
void Hierarchies_add_path_existing_depth_0(void);
void Hierarchies_add_path_existing_depth_1(void);
void Hierarchies_add_path_existing_depth_2(void);
void Hierarchies_add_path_from_scope(void);
void Hierarchies_add_path_from_scope_new_entity(void);
void Hierarchies_new_w_child_in_root(void);
void Hierarchies_delete_child(void);
void Hierarchies_delete_2_children(void);
void Hierarchies_delete_2_children_different_type(void);
void Hierarchies_delete_tree_2_levels(void);
void Hierarchies_delete_tree_3_levels(void);
void Hierarchies_delete_tree_count_tables(void);
void Hierarchies_delete_tree_staged(void);
void Hierarchies_delete_tree_empty_table(void);
void Hierarchies_delete_tree_recreate(void);
void Hierarchies_delete_tree_w_onremove(void);
void Hierarchies_delete_tree_w_dtor(void);
void Hierarchies_get_child_count(void);
void Hierarchies_get_child_count_2_tables(void);
void Hierarchies_get_child_count_no_children(void);
void Hierarchies_scope_iter_after_delete_tree(void);
void Hierarchies_add_child_after_delete_tree(void);
void Hierarchies_add_child_to_recycled_parent(void);
void Hierarchies_get_type_after_recycled_parent_add(void);
void Hierarchies_rematch_after_add_to_recycled_parent(void);
void Hierarchies_cascade_after_recycled_parent_change(void);
void Hierarchies_long_name_depth_0(void);
void Hierarchies_long_name_depth_1(void);
void Hierarchies_long_name_depth_2(void);

// Testsuite 'Add_bulk'
void Add_bulk_add_comp_from_comp_to_empty(void);
void Add_bulk_add_comp_from_comp_to_existing(void);
void Add_bulk_add_comp_from_tag_to_empty(void);
void Add_bulk_add_comp_from_tag_to_existing(void);
void Add_bulk_add_tag_from_tag_to_empty(void);
void Add_bulk_add_tag_from_tag_to_existing(void);
void Add_bulk_add_comp_to_more_existing(void);
void Add_bulk_add_comp_to_fewer_existing(void);
void Add_bulk_on_add(void);
void Add_bulk_add_entity_comp(void);
void Add_bulk_add_entity_tag(void);
void Add_bulk_add_entity_on_add(void);
void Add_bulk_add_entity_existing(void);

// Testsuite 'Remove_bulk'
void Remove_bulk_remove_comp_from_comp_to_empty(void);
void Remove_bulk_remove_comp_from_comp_to_existing(void);
void Remove_bulk_remove_comp_from_tag_to_empty(void);
void Remove_bulk_remove_comp_from_tag_to_existing(void);
void Remove_bulk_remove_tag_from_tag_to_empty(void);
void Remove_bulk_remove_tag_from_tag_to_existing(void);
void Remove_bulk_remove_all_comp(void);
void Remove_bulk_remove_all_tag(void);
void Remove_bulk_on_remove(void);
void Remove_bulk_remove_entity_comp(void);
void Remove_bulk_remove_entity_tag(void);
void Remove_bulk_remove_entity_on_remove(void);

// Testsuite 'Add_remove_bulk'
void Add_remove_bulk_add_remove_add_only(void);
void Add_remove_bulk_add_remove_remove_only(void);
void Add_remove_bulk_add_remove_both(void);
void Add_remove_bulk_add_remove_same(void);

// Testsuite 'Has'
void Has_zero(void);
void Has_zero_from_nonzero(void);
void Has_1_of_0(void);
void Has_1_of_1(void);
void Has_1_of_2(void);
void Has_2_of_0(void);
void Has_2_of_2(void);
void Has_3_of_2(void);
void Has_2_of_1(void);
void Has_1_of_empty(void);
void Has_has_in_progress(void);
void Has_has_of_zero(void);
void Has_owns(void);
void Has_has_entity(void);
void Has_has_entity_0(void);
void Has_has_entity_0_component(void);
void Has_has_entity_owned(void);
void Has_has_entity_owned_0(void);
void Has_has_entity_owned_0_component(void);
void Has_has_wildcard(void);
void Has_has_wildcard_pair(void);

// Testsuite 'Count'
void Count_count_empty(void);
void Count_count_w_entity_0(void);
void Count_count_1_component(void);
void Count_count_2_components(void);
void Count_count_3_components(void);
void Count_count_2_types_2_comps(void);

// Testsuite 'Get_component'
void Get_component_setup(void);
void Get_component_get_empty(void);
void Get_component_get_1_from_1(void);
void Get_component_get_1_from_2(void);
void Get_component_get_2_from_2(void);
void Get_component_get_2_from_3(void);
void Get_component_get_1_from_2_in_progress_from_main_stage(void);
void Get_component_get_1_from_2_add_in_progress(void);
void Get_component_get_both_from_2_add_in_progress(void);
void Get_component_get_both_from_2_add_remove_in_progress(void);
void Get_component_get_childof_component(void);

// Testsuite 'Reference'
void Reference_setup(void);
void Reference_get_ref(void);
void Reference_get_ref_after_add(void);
void Reference_get_ref_after_remove(void);
void Reference_get_ref_after_delete(void);
void Reference_get_ref_after_realloc(void);
void Reference_get_ref_after_realloc_w_lifecycle(void);
void Reference_get_ref_staged(void);
void Reference_get_ref_after_new_in_stage(void);
void Reference_get_ref_monitored(void);
void Reference_get_nonexisting(void);

// Testsuite 'Delete'
void Delete_setup(void);
void Delete_delete_1(void);
void Delete_delete_1_again(void);
void Delete_delete_empty(void);
void Delete_delete_nonexist(void);
void Delete_delete_1st_of_3(void);
void Delete_delete_2nd_of_3(void);
void Delete_delete_2_of_3(void);
void Delete_delete_3_of_3(void);
void Delete_delete_w_on_remove(void);
void Delete_clear_1_component(void);
void Delete_clear_2_components(void);
void Delete_alive_after_delete(void);
void Delete_alive_after_clear(void);
void Delete_alive_after_staged_delete(void);
void Delete_alive_while_staged(void);
void Delete_alive_while_staged_w_delete(void);
void Delete_alive_while_staged_w_delete_recycled_id(void);
void Delete_alive_after_recycle(void);
void Delete_delete_recycled(void);
void Delete_get_alive_for_alive(void);
void Delete_get_alive_for_recycled(void);
void Delete_get_alive_for_not_alive(void);
void Delete_get_alive_w_generation_for_recycled_alive(void);
void Delete_get_alive_w_generation_for_recycled_not_alive(void);
void Delete_get_alive_for_0(void);
void Delete_get_alive_for_nonexistent(void);

// Testsuite 'OnDelete'
void OnDelete_on_delete_id_default(void);
void OnDelete_on_delete_id_remove(void);
void OnDelete_on_delete_id_delete(void);
void OnDelete_on_delete_relation_default(void);
void OnDelete_on_delete_relation_remove(void);
void OnDelete_on_delete_relation_delete(void);
void OnDelete_on_delete_object_default(void);
void OnDelete_on_delete_object_remove(void);
void OnDelete_on_delete_object_delete(void);
void OnDelete_on_delete_id_throw(void);
void OnDelete_on_delete_relation_throw(void);
void OnDelete_on_delete_object_throw(void);
void OnDelete_on_delete_id_remove_no_instances(void);
void OnDelete_on_delete_id_delete_no_instances(void);
void OnDelete_on_delete_id_throw_no_instances(void);
void OnDelete_on_delete_cyclic_id_default(void);
void OnDelete_on_delete_cyclic_id_remove(void);
void OnDelete_on_delete_cyclic_id_remove_both(void);
void OnDelete_on_delete_cyclic_id_delete(void);
void OnDelete_on_delete_cyclic_id_delete_both(void);
void OnDelete_on_delete_cyclic_relation_default(void);
void OnDelete_on_delete_cyclic_relation_remove(void);
void OnDelete_on_delete_cyclic_relation_remove_both(void);
void OnDelete_on_delete_cyclic_relation_delete(void);
void OnDelete_on_delete_cyclic_object_default(void);
void OnDelete_on_delete_cyclic_object_remove(void);
void OnDelete_on_delete_cyclic_object_delete(void);
void OnDelete_on_delete_remove_2_comps(void);
void OnDelete_on_delete_remove_2_comps_to_existing_table(void);
void OnDelete_on_delete_delete_recursive(void);
void OnDelete_on_delete_component_throw(void);
void OnDelete_on_delete_remove_2_relations(void);
void OnDelete_on_delete_remove_object_w_2_relations(void);
void OnDelete_remove_id_from_2_tables(void);
void OnDelete_remove_relation_from_2_tables(void);
void OnDelete_remove_object_from_2_tables(void);
void OnDelete_remove_id_and_relation(void);
void OnDelete_remove_id_and_relation_from_2_tables(void);
void OnDelete_stresstest_many_objects(void);
void OnDelete_stresstest_many_relations(void);
void OnDelete_stresstest_many_objects_on_delete(void);
void OnDelete_stresstest_many_relations_on_delete(void);
void OnDelete_on_delete_empty_table_w_on_remove(void);
void OnDelete_delete_table_in_on_remove_during_fini(void);
void OnDelete_delete_other_in_on_remove_during_fini(void);

// Testsuite 'Delete_w_filter'
void Delete_w_filter_delete_1(void);
void Delete_w_filter_delete_2(void);
void Delete_w_filter_delete_1_2_types(void);
void Delete_w_filter_delete_2_2_types(void);
void Delete_w_filter_delete_except_1(void);
void Delete_w_filter_delete_except_2(void);
void Delete_w_filter_delete_with_any_of_2(void);
void Delete_w_filter_delete_except_all_of_2(void);
void Delete_w_filter_include_exact(void);
void Delete_w_filter_exclude_exact(void);
void Delete_w_filter_system_activate_test(void);
void Delete_w_filter_skip_builtin_tables(void);
void Delete_w_filter_delete_w_on_remove(void);

// Testsuite 'Set'
void Set_set_empty(void);
void Set_set_nonempty(void);
void Set_set_non_empty_override(void);
void Set_set_again(void);
void Set_set_2(void);
void Set_add_set(void);
void Set_set_add(void);
void Set_set_add_other(void);
void Set_set_remove(void);
void Set_set_remove_other(void);
void Set_set_remove_twice(void);
void Set_set_and_new(void);
void Set_set_null(void);
void Set_get_mut_new(void);
void Set_get_mut_existing(void);
void Set_get_mut_tag_new(void);
void Set_get_mut_tag_existing(void);
void Set_get_mut_tag_new_w_comp(void);
void Set_get_mut_tag_existing_w_comp(void);
void Set_get_mut_tag_new_w_pair(void);
void Set_get_mut_tag_existing_w_pair(void);
void Set_modified_w_on_set(void);
void Set_modified_no_component(void);
void Set_get_mut_w_add_in_on_add(void);
void Set_get_mut_w_remove_in_on_add(void);
void Set_emplace(void);
void Set_emplace_existing(void);

// Testsuite 'Lookup'
void Lookup_setup(void);
void Lookup_lookup(void);
void Lookup_lookup_component(void);
void Lookup_lookup_not_found(void);
void Lookup_lookup_child(void);
void Lookup_lookup_w_null_name(void);
void Lookup_get_name(void);
void Lookup_get_name_no_name(void);
void Lookup_get_name_from_empty(void);
void Lookup_lookup_by_id(void);
void Lookup_lookup_symbol_by_id(void);
void Lookup_lookup_name_w_digit(void);
void Lookup_lookup_symbol_w_digit(void);
void Lookup_lookup_path_w_digit(void);
void Lookup_set_name_of_existing(void);
void Lookup_change_name_of_existing(void);
void Lookup_lookup_alias(void);
void Lookup_lookup_scoped_alias(void);
void Lookup_define_duplicate_alias(void);
void Lookup_define_alias_in_scope(void);
void Lookup_lookup_null(void);
void Lookup_lookup_symbol_null(void);
void Lookup_lookup_this(void);
void Lookup_lookup_wildcard(void);
void Lookup_lookup_path_this(void);
void Lookup_lookup_path_wildcard(void);
void Lookup_lookup_path_this_from_scope(void);
void Lookup_lookup_path_wildcard_from_scope(void);

// Testsuite 'Singleton'
void Singleton_set(void);
void Singleton_set_ptr(void);
void Singleton_system_w_singleton(void);
void Singleton_system_w_singleton_no_match(void);
void Singleton_system_w_not_singleton(void);
void Singleton_lookup_singleton(void);
void Singleton_get_singleton_id(void);
void Singleton_set_get_singleton(void);
void Singleton_get_mut_singleton(void);
void Singleton_singleton_system(void);

// Testsuite 'Clone'
void Clone_empty(void);
void Clone_empty_w_value(void);
void Clone_null(void);
void Clone_null_w_value(void);
void Clone_1_component(void);
void Clone_2_component(void);
void Clone_1_component_w_value(void);
void Clone_2_component_w_value(void);
void Clone_3_component(void);
void Clone_3_component_w_value(void);
void Clone_tag(void);
void Clone_tag_w_value(void);
void Clone_1_tag_1_component(void);
void Clone_1_tag_1_component_w_value(void);

// Testsuite 'ComponentLifecycle'
void ComponentLifecycle_setup(void);
void ComponentLifecycle_ctor_on_add(void);
void ComponentLifecycle_ctor_on_new(void);
void ComponentLifecycle_dtor_on_remove(void);
void ComponentLifecycle_dtor_on_delete(void);
void ComponentLifecycle_copy_on_set(void);
void ComponentLifecycle_copy_on_override(void);
void ComponentLifecycle_copy_on_new_w_data(void);
void ComponentLifecycle_copy_on_clone(void);
void ComponentLifecycle_no_copy_on_move(void);
void ComponentLifecycle_ctor_on_bulk_add(void);
void ComponentLifecycle_dtor_on_bulk_remove(void);
void ComponentLifecycle_ctor_on_bulk_add_entity(void);
void ComponentLifecycle_dtor_on_bulk_remove_entity(void);
void ComponentLifecycle_ctor_dtor_on_bulk_add_remove(void);
void ComponentLifecycle_ctor_copy_on_snapshot(void);
void ComponentLifecycle_copy_on_snapshot(void);
void ComponentLifecycle_dtor_on_restore(void);
void ComponentLifecycle_ctor_on_tag(void);
void ComponentLifecycle_dtor_on_tag(void);
void ComponentLifecycle_copy_on_tag(void);
void ComponentLifecycle_move_on_tag(void);
void ComponentLifecycle_merge_to_different_table(void);
void ComponentLifecycle_merge_to_new_table(void);
void ComponentLifecycle_delete_in_stage(void);
void ComponentLifecycle_ctor_on_add_pair(void);
void ComponentLifecycle_ctor_on_add_pair_set_ctor_after_table(void);
void ComponentLifecycle_ctor_on_add_pair_tag(void);
void ComponentLifecycle_ctor_on_add_pair_tag_set_ctor_after_table(void);
void ComponentLifecycle_ctor_on_move_pair(void);
void ComponentLifecycle_move_on_realloc(void);
void ComponentLifecycle_move_on_dim(void);
void ComponentLifecycle_move_on_bulk_new(void);
void ComponentLifecycle_move_on_delete(void);
void ComponentLifecycle_copy_on_override_pair(void);
void ComponentLifecycle_copy_on_override_pair_tag(void);
void ComponentLifecycle_copy_on_set_pair(void);
void ComponentLifecycle_copy_on_set_pair_tag(void);
void ComponentLifecycle_prevent_lifecycle_overwrite(void);
void ComponentLifecycle_prevent_lifecycle_overwrite_null_callbacks(void);
void ComponentLifecycle_allow_lifecycle_overwrite_equal_callbacks(void);
void ComponentLifecycle_set_lifecycle_after_trigger(void);
void ComponentLifecycle_valid_entity_in_dtor_after_delete(void);
void ComponentLifecycle_ctor_w_emplace(void);
void ComponentLifecycle_dtor_on_fini(void);
void ComponentLifecycle_valid_type_in_dtor_on_fini(void);
void ComponentLifecycle_valid_other_type_of_entity_in_dtor_on_fini(void);
void ComponentLifecycle_valid_same_type_comp_of_entity_in_dtor_on_fini(void);
void ComponentLifecycle_valid_same_type_comp_of_entity_in_dtor_on_delete_parent(void);
void ComponentLifecycle_valid_entity_bulk_remove_all_components(void);
void ComponentLifecycle_delete_in_dtor_same_type_on_fini(void);
void ComponentLifecycle_delete_in_dtor_other_type_on_fini(void);
void ComponentLifecycle_delete_self_in_dtor_on_fini(void);
void ComponentLifecycle_delete_in_dtor_same_type_on_delete_parent(void);
void ComponentLifecycle_delete_in_dtor_other_type_on_delete_parent(void);
void ComponentLifecycle_delete_self_in_dtor_on_delete_parent(void);
void ComponentLifecycle_delete_in_dtor_same_type_on_delete(void);
void ComponentLifecycle_delete_in_dtor_other_type_on_delete(void);
void ComponentLifecycle_delete_self_in_dtor_on_delete(void);

// Testsuite 'Pipeline'
void Pipeline_setup(void);
void Pipeline_system_order_same_phase(void);
void Pipeline_system_order_same_phase_after_disable(void);
void Pipeline_system_order_same_phase_after_activate(void);
void Pipeline_system_order_different_phase(void);
void Pipeline_system_order_different_phase_after_disable(void);
void Pipeline_system_order_different_phase_after_activate(void);
void Pipeline_system_order_after_new_system_lower_id(void);
void Pipeline_system_order_after_new_system_inbetween_id(void);
void Pipeline_system_order_after_new_system_higher_id(void);
void Pipeline_merge_after_staged_out(void);
void Pipeline_merge_after_not_out(void);
void Pipeline_no_merge_after_main_out(void);
void Pipeline_no_merge_after_staged_in_out(void);
void Pipeline_merge_after_staged_out_before_owned(void);
void Pipeline_switch_pipeline(void);
void Pipeline_run_pipeline(void);
void Pipeline_get_pipeline_from_stage(void);
void Pipeline_3_systems_3_types(void);
void Pipeline_random_read_after_random_write_out_in(void);
void Pipeline_random_read_after_random_write_inout_in(void);
void Pipeline_random_read_after_random_write_out_inout(void);
void Pipeline_random_read_after_random_write_inout_inout(void);
void Pipeline_random_read_after_random_write_w_not_write(void);
void Pipeline_random_read_after_random_write_w_not_read(void);
void Pipeline_random_read_after_random_write_w_wildcard(void);
void Pipeline_random_in_after_random_inout_after_random_out(void);

// Testsuite 'SystemMisc'
void SystemMisc_setup(void);
void SystemMisc_invalid_not_without_id(void);
void SystemMisc_invalid_optional_without_id(void);
void SystemMisc_invalid_system_without_id(void);
void SystemMisc_invalid_container_without_id(void);
void SystemMisc_invalid_cascade_without_id(void);
void SystemMisc_invalid_entity_without_id(void);
void SystemMisc_invalid_empty_without_id(void);
void SystemMisc_invalid_singleton_without_id(void);
void SystemMisc_invalid_empty_element(void);
void SystemMisc_invalid_empty_element_w_space(void);
void SystemMisc_invalid_empty_or(void);
void SystemMisc_invalid_empty_or_w_space(void);
void SystemMisc_invalid_or_w_not(void);
void SystemMisc_invalid_not_w_or(void);
void SystemMisc_invalid_0_w_and(void);
void SystemMisc_invalid_0_w_from_system(void);
void SystemMisc_invalid_0_w_from_container(void);
void SystemMisc_invalid_0_w_from_cascade(void);
void SystemMisc_invalid_0_w_from_entity(void);
void SystemMisc_invalid_0_w_from_empty(void);
void SystemMisc_invalid_0_w_from_singleton(void);
void SystemMisc_invalid_or_w_empty(void);
void SystemMisc_invalid_component_id(void);
void SystemMisc_invalid_entity_id(void);
void SystemMisc_invalid_null_string(void);
void SystemMisc_invalid_empty_string(void);
void SystemMisc_invalid_empty_string_w_space(void);
void SystemMisc_invalid_mixed_src_modifier(void);
void SystemMisc_redefine_row_system(void);
void SystemMisc_system_w_or_prefab(void);
void SystemMisc_system_w_or_disabled(void);
void SystemMisc_system_w_or_disabled_and_prefab(void);
void SystemMisc_table_columns_access(void);
void SystemMisc_status_enable_after_new(void);
void SystemMisc_status_enable_after_disable(void);
void SystemMisc_status_disable_after_new(void);
void SystemMisc_status_disable_after_disable(void);
void SystemMisc_status_activate_after_new(void);
void SystemMisc_status_deactivate_after_delete(void);
void SystemMisc_dont_enable_after_rematch(void);
void SystemMisc_ensure_single_merge(void);
void SystemMisc_table_count(void);
void SystemMisc_match_system(void);
void SystemMisc_match_system_w_filter(void);
void SystemMisc_system_initial_state(void);
void SystemMisc_add_own_component(void);
void SystemMisc_change_system_action(void);
void SystemMisc_system_readeactivate(void);
void SystemMisc_system_readeactivate_w_2_systems(void);
void SystemMisc_add_to_system_in_progress(void);
void SystemMisc_add_to_lazy_system_in_progress(void);
void SystemMisc_redefine_null_signature(void);
void SystemMisc_redefine_0_signature(void);
void SystemMisc_one_named_column_of_two(void);
void SystemMisc_two_named_columns_of_two(void);
void SystemMisc_get_column_by_name(void);
void SystemMisc_get_column_by_name_not_found(void);
void SystemMisc_get_column_by_name_no_names(void);
void SystemMisc_redeclare_system_same_expr(void);
void SystemMisc_redeclare_system_null_expr(void);
void SystemMisc_redeclare_system_0_expr(void);
void SystemMisc_redeclare_system_different_expr(void);
void SystemMisc_redeclare_system_null_and_expr(void);
void SystemMisc_redeclare_system_expr_and_null(void);
void SystemMisc_redeclare_system_expr_and_0(void);
void SystemMisc_redeclare_system_0_and_expr(void);
void SystemMisc_redeclare_system_0_and_null(void);
void SystemMisc_redeclare_system_null_and_0(void);
void SystemMisc_redeclare_system_explicit_id(void);
void SystemMisc_redeclare_system_explicit_id_null_expr(void);
void SystemMisc_redeclare_system_explicit_id_no_name(void);
void SystemMisc_declare_different_id_same_name(void);
void SystemMisc_declare_different_id_same_name_w_scope(void);
void SystemMisc_rw_in_implicit_any(void);
void SystemMisc_rw_in_implicit_shared(void);
void SystemMisc_rw_in_implicit_from_empty(void);
void SystemMisc_rw_in_implicit_from_entity(void);
void SystemMisc_rw_out_explicit_any(void);
void SystemMisc_rw_out_explicit_shared(void);
void SystemMisc_rw_out_explicit_from_empty(void);
void SystemMisc_rw_out_explicit_from_entity(void);
void SystemMisc_activate_system_for_table_w_n_pairs(void);
void SystemMisc_get_query(void);
void SystemMisc_set_get_context(void);
void SystemMisc_set_get_binding_context(void);
void SystemMisc_deactivate_after_disable(void);
void SystemMisc_system_w_self(void);
void SystemMisc_delete_system(void);
void SystemMisc_delete_pipeline_system(void);
void SystemMisc_delete_system_w_ctx(void);

// Testsuite 'Sorting'
void Sorting_sort_by_component(void);
void Sorting_sort_by_component_2_tables(void);
void Sorting_sort_by_component_3_tables(void);
void Sorting_sort_by_entity(void);
void Sorting_sort_after_add(void);
void Sorting_sort_after_remove(void);
void Sorting_sort_after_delete(void);
void Sorting_sort_after_set(void);
void Sorting_sort_after_system(void);
void Sorting_sort_after_query(void);
void Sorting_sort_by_component_same_value_1(void);
void Sorting_sort_by_component_same_value_2(void);
void Sorting_sort_by_component_move_pivot(void);
void Sorting_sort_1000_entities(void);
void Sorting_sort_1000_entities_w_duplicates(void);
void Sorting_sort_1000_entities_again(void);
void Sorting_sort_1000_entities_2_types(void);
void Sorting_sort_1500_entities_3_types(void);
void Sorting_sort_2000_entities_4_types(void);
void Sorting_sort_2_entities_2_types(void);
void Sorting_sort_3_entities_3_types(void);
void Sorting_sort_3_entities_3_types_2(void);
void Sorting_sort_4_entities_4_types(void);
void Sorting_sort_1000_entities_2_types_again(void);
void Sorting_sort_1000_entities_add_type_after_sort(void);
void Sorting_sort_shared_component(void);
void Sorting_sort_w_tags_only(void);
void Sorting_sort_childof_marked(void);
void Sorting_sort_isa_marked(void);
void Sorting_sort_relation_marked(void);

// Testsuite 'Filter'
void Filter_filter_1_term(void);
void Filter_filter_2_terms(void);
void Filter_filter_3_terms(void);
void Filter_filter_3_terms_w_or(void);
void Filter_filter_4_terms_w_or_at_1(void);
void Filter_filter_w_pair_id(void);
void Filter_filter_w_pred_obj(void);
void Filter_term_w_id(void);
void Filter_term_w_pair_id(void);
void Filter_term_w_pred_obj(void);
void Filter_term_w_pair_finalize_twice(void);
void Filter_term_w_role(void);
void Filter_term_w_pred_role(void);

// Testsuite 'Query'
void Query_query_changed_after_new(void);
void Query_query_changed_after_delete(void);
void Query_query_changed_after_add(void);
void Query_query_changed_after_remove(void);
void Query_query_changed_after_set(void);
void Query_query_change_after_modified(void);
void Query_query_change_after_out_system(void);
void Query_query_change_after_in_system(void);
void Query_subquery_match_existing(void);
void Query_subquery_match_new(void);
void Query_subquery_inactive(void);
void Query_subquery_unmatch(void);
void Query_subquery_rematch(void);
void Query_subquery_rematch_w_parent_optional(void);
void Query_subquery_rematch_w_sub_optional(void);
void Query_query_single_pairs(void);
void Query_query_single_instanceof(void);
void Query_query_single_childof(void);
void Query_query_w_filter(void);
void Query_query_optional_owned(void);
void Query_query_optional_shared(void);
void Query_query_optional_shared_nested(void);
void Query_query_optional_any(void);
void Query_query_rematch_optional_after_add(void);
void Query_get_owned_tag(void);
void Query_get_shared_tag(void);
void Query_explicit_delete(void);
void Query_get_column_size(void);
void Query_orphaned_query(void);
void Query_nested_orphaned_query(void);
void Query_invalid_access_orphaned_query(void);
void Query_stresstest_query_free(void);
void Query_only_from_entity(void);
void Query_only_from_singleton(void);
void Query_only_not_from_entity(void);
void Query_only_not_from_singleton(void);
void Query_get_filter(void);
void Query_group_by(void);
void Query_group_by_w_ctx(void);

// Testsuite 'Pairs'
void Pairs_type_w_one_pair(void);
void Pairs_type_w_two_pairs(void);
void Pairs_add_pair(void);
void Pairs_remove_pair(void);
void Pairs_add_tag_pair_for_tag(void);
void Pairs_add_tag_pair_for_component(void);
void Pairs_query_2_pairs(void);
void Pairs_query_2_pairs_2_instances_per_type(void);
void Pairs_query_pair_or_component(void);
void Pairs_query_pair_or_pair(void);
void Pairs_query_not_pair(void);
void Pairs_override_pair(void);
void Pairs_override_tag_pair(void);
void Pairs_pair_w_component_query(void);
void Pairs_pair_wildcard_system(void);
void Pairs_pair_only_wildcard_system(void);
void Pairs_pair_wildcard_on_set(void);
void Pairs_on_add_pair(void);
void Pairs_on_add_pair_tag(void);
void Pairs_on_remove_pair(void);
void Pairs_on_remove_pair_tag(void);
void Pairs_on_remove_pair_on_delete(void);
void Pairs_on_remove_pair_tag_on_delete(void);
void Pairs_pair_from_shared(void);
void Pairs_simple_pair_syntax(void);
void Pairs_get_typeid_w_recycled_rel(void);
void Pairs_get_typeid_w_recycled_obj(void);
void Pairs_id_str_w_recycled_rel(void);
void Pairs_id_str_w_recycled_obj(void);
void Pairs_set_object_w_zero_sized_rel_comp(void);
void Pairs_dsl_pair(void);
void Pairs_dsl_pair_w_pred_wildcard(void);
void Pairs_dsl_pair_w_obj_wildcard(void);
void Pairs_dsl_pair_w_both_wildcard(void);
void Pairs_dsl_pair_w_explicit_subj_this(void);
void Pairs_dsl_pair_w_explicit_subj(void);
void Pairs_api_pair(void);
void Pairs_api_pair_w_pred_wildcard(void);
void Pairs_api_pair_w_obj_wildcard(void);
void Pairs_api_pair_w_both_wildcard(void);
void Pairs_api_pair_w_explicit_subj_this(void);
void Pairs_api_pair_w_explicit_subj(void);
void Pairs_typeid_from_tag(void);
void Pairs_typeid_from_component(void);
void Pairs_typeid_from_pair(void);
void Pairs_typeid_from_pair_w_rel_type(void);
void Pairs_typeid_from_pair_w_obj_type(void);
void Pairs_typeid_from_pair_w_rel_obj_type(void);
void Pairs_typeid_from_pair_w_rel_0_obj_type(void);
void Pairs_typeid_from_pair_w_rel_obj_0_type(void);
void Pairs_typeid_from_pair_w_rel_0_obj_0_type(void);
void Pairs_tag_pair_w_rel_comp(void);
void Pairs_tag_pair_w_obj_comp(void);
void Pairs_tag_pair_w_rel_obj_comp(void);
void Pairs_get_tag_pair_w_rel_comp(void);
void Pairs_get_tag_pair_w_obj_comp(void);
void Pairs_get_tag_pair_w_rel_obj_comp(void);
void Pairs_tag_pair_w_childof_w_comp(void);
void Pairs_tag_pair_w_isa_w_comp(void);

// Testsuite 'Trigger'
void Trigger_on_add_trigger_before_table(void);
void Trigger_on_add_trigger_after_table(void);
void Trigger_on_remove_trigger_before_table(void);
void Trigger_on_remove_trigger_after_table(void);
void Trigger_on_add_tag(void);
void Trigger_on_add_component(void);
void Trigger_on_add_wildcard(void);
void Trigger_on_add_pair(void);
void Trigger_on_add_pair_obj_wildcard(void);
void Trigger_on_add_pair_pred_wildcard(void);
void Trigger_on_add_pair_wildcard(void);
void Trigger_on_remove_tag(void);
void Trigger_on_remove_component(void);
void Trigger_on_remove_wildcard(void);
void Trigger_on_remove_pair(void);
void Trigger_on_remove_pair_obj_wildcard(void);
void Trigger_on_remove_pair_pred_wildcard(void);
void Trigger_on_remove_pair_wildcard(void);
void Trigger_on_add_remove(void);
void Trigger_on_set_component(void);
void Trigger_on_set_wildcard(void);
void Trigger_on_set_pair(void);
void Trigger_on_set_pair_w_obj_wildcard(void);
void Trigger_on_set_pair_pred_wildcard(void);
void Trigger_on_set_pair_wildcard(void);
void Trigger_on_set_component_after_modified(void);
void Trigger_un_set_component(void);
void Trigger_un_set_wildcard(void);
void Trigger_un_set_pair(void);
void Trigger_un_set_pair_w_obj_wildcard(void);
void Trigger_un_set_pair_pred_wildcard(void);
void Trigger_un_set_pair_wildcard(void);
void Trigger_add_twice(void);
void Trigger_remove_twice(void);
void Trigger_on_remove_w_clear(void);
void Trigger_on_remove_w_delete(void);
void Trigger_on_remove_w_world_fini(void);
void Trigger_on_add_w_clone(void);
void Trigger_add_in_trigger(void);
void Trigger_remove_in_trigger(void);
void Trigger_clear_in_trigger(void);
void Trigger_delete_in_trigger(void);
void Trigger_trigger_w_named_entity(void);
void Trigger_on_remove_tree(void);
void Trigger_set_get_context(void);
void Trigger_set_get_binding_context(void);
void Trigger_trigger_w_self(void);
void Trigger_delete_trigger_w_delete_ctx(void);
void Trigger_trigger_w_index(void);

// Testsuite 'Observer'
void Observer_2_terms_w_on_add(void);
void Observer_2_terms_w_on_remove(void);
void Observer_2_terms_w_on_set_value(void);
void Observer_2_terms_w_on_remove_value(void);
void Observer_2_terms_w_on_add_2nd(void);
void Observer_2_terms_w_on_remove_2nd(void);
void Observer_2_pair_terms_w_on_add(void);
void Observer_2_pair_terms_w_on_remove(void);
void Observer_2_wildcard_pair_terms_w_on_add(void);
void Observer_2_wildcard_pair_terms_w_on_add_2_matching(void);
void Observer_2_wildcard_pair_terms_w_on_add_3_matching(void);
void Observer_2_wildcard_pair_terms_w_on_remove(void);
void Observer_2_terms_1_not_w_on_add(void);
void Observer_2_terms_1_not_w_on_remove(void);
void Observer_2_terms_w_on_set(void);
void Observer_2_terms_w_un_set(void);
void Observer_3_terms_2_or_on_add(void);
void Observer_3_terms_2_or_on_remove(void);
void Observer_2_terms_w_from_entity_on_add(void);
void Observer_2_terms_on_remove_on_clear(void);
void Observer_2_terms_on_remove_on_delete(void);
void Observer_observer_w_self(void);
void Observer_add_after_delete_observer(void);
void Observer_remove_after_delete_observer(void);
void Observer_delete_observer_w_ctx(void);

// Testsuite 'TriggerOnAdd'
void TriggerOnAdd_setup(void);
void TriggerOnAdd_new_match_1_of_1(void);
void TriggerOnAdd_new_match_1_of_2(void);
void TriggerOnAdd_new_no_match_1(void);
void TriggerOnAdd_new_w_count_match_1_of_1(void);
void TriggerOnAdd_add_match_1_of_1(void);
void TriggerOnAdd_add_match_1_of_2(void);
void TriggerOnAdd_add_no_match_1(void);
void TriggerOnAdd_set_match_1_of_1(void);
void TriggerOnAdd_set_no_match_1(void);
void TriggerOnAdd_clone_match_1_of_1(void);
void TriggerOnAdd_clone_match_1_of_2(void);
void TriggerOnAdd_add_again_1(void);
void TriggerOnAdd_set_again_1(void);
void TriggerOnAdd_add_again_2(void);
void TriggerOnAdd_override_after_add_in_on_add(void);
void TriggerOnAdd_add_again_in_progress(void);
void TriggerOnAdd_add_in_progress_before_system_def(void);
void TriggerOnAdd_2_systems_w_table_creation(void);
void TriggerOnAdd_2_systems_w_table_creation_in_progress(void);
void TriggerOnAdd_sys_context(void);
void TriggerOnAdd_get_sys_context_from_param(void);
void TriggerOnAdd_remove_added_component_in_on_add_w_set(void);
void TriggerOnAdd_on_add_in_on_add(void);
void TriggerOnAdd_on_remove_in_on_add(void);
void TriggerOnAdd_on_set_in_on_add(void);
void TriggerOnAdd_on_add_in_on_update(void);
void TriggerOnAdd_emplace(void);
void TriggerOnAdd_add_after_delete_trigger(void);
void TriggerOnAdd_add_after_delete_wildcard_id_trigger(void);

// Testsuite 'TriggerOnRemove'
void TriggerOnRemove_remove_match_1_of_1(void);
void TriggerOnRemove_remove_match_1_of_2(void);
void TriggerOnRemove_remove_no_match_1(void);
void TriggerOnRemove_delete_match_1_of_1(void);
void TriggerOnRemove_delete_match_1_of_2(void);
void TriggerOnRemove_delete_no_match_1(void);
void TriggerOnRemove_remove_watched(void);
void TriggerOnRemove_delete_watched(void);
void TriggerOnRemove_valid_entity_after_delete(void);
void TriggerOnRemove_remove_after_delete_trigger(void);
void TriggerOnRemove_remove_after_delete_wildcard_id_trigger(void);

// Testsuite 'TriggerOnSet'
void TriggerOnSet_set(void);
void TriggerOnSet_set_new(void);
void TriggerOnSet_set_again(void);
void TriggerOnSet_clone(void);
void TriggerOnSet_clone_w_value(void);
void TriggerOnSet_set_and_add_system(void);
void TriggerOnSet_on_set_after_override(void);
void TriggerOnSet_on_set_after_override_w_new(void);
void TriggerOnSet_on_set_after_override_w_new_w_count(void);
void TriggerOnSet_on_set_after_override_1_of_2_overridden(void);
void TriggerOnSet_on_set_after_snapshot_restore(void);
void TriggerOnSet_emplace(void);

// Testsuite 'Monitor'
void Monitor_1_comp(void);
void Monitor_2_comps(void);
void Monitor_1_comp_1_not(void);
void Monitor_1_parent(void);
void Monitor_1_comp_1_parent(void);
void Monitor_1_comp_prefab_new(void);
void Monitor_1_comp_prefab_add(void);

// Testsuite 'SystemOnSet'
void SystemOnSet_set_1_of_1(void);
void SystemOnSet_set_1_of_2(void);
void SystemOnSet_set_1_of_3(void);
void SystemOnSet_bulk_new_1(void);
void SystemOnSet_bulk_new_2(void);
void SystemOnSet_bulk_new_2_of_1(void);
void SystemOnSet_bulk_new_3(void);
void SystemOnSet_bulk_new_3_of_2(void);
void SystemOnSet_bulk_new_1_from_base(void);
void SystemOnSet_set_1_of_2_1_from_base(void);
void SystemOnSet_set_1_of_3_1_from_base(void);
void SystemOnSet_add_base(void);
void SystemOnSet_add_base_to_1_overridden(void);
void SystemOnSet_add_base_to_2_overridden(void);
void SystemOnSet_add_base_to_1_of_2_overridden(void);
void SystemOnSet_on_set_after_remove_override(void);
void SystemOnSet_no_set_after_remove_base(void);
void SystemOnSet_un_set_after_remove(void);
void SystemOnSet_un_set_after_remove_base(void);
void SystemOnSet_add_to_current_in_on_set(void);
void SystemOnSet_remove_from_current_in_on_set(void);
void SystemOnSet_remove_set_component_in_on_set(void);
void SystemOnSet_match_table_created_w_add_in_on_set(void);
void SystemOnSet_set_optional(void);
void SystemOnSet_set_from_nothing(void);
void SystemOnSet_add_null_type_in_on_set(void);
void SystemOnSet_add_0_entity_in_on_set(void);
void SystemOnSet_on_set_prefab(void);

// Testsuite 'SystemUnSet'
void SystemUnSet_unset_1_of_1(void);
void SystemUnSet_unset_1_of_2(void);
void SystemUnSet_unset_1_of_3(void);
void SystemUnSet_unset_on_delete_1(void);
void SystemUnSet_unset_on_delete_2(void);
void SystemUnSet_unset_on_delete_3(void);
void SystemUnSet_unset_on_fini_1(void);
void SystemUnSet_unset_on_fini_2(void);
void SystemUnSet_unset_on_fini_3(void);
void SystemUnSet_overlapping_unset_systems(void);
void SystemUnSet_unset_move_to_nonempty_table(void);
void SystemUnSet_write_in_unset(void);

// Testsuite 'SystemPeriodic'
void SystemPeriodic_1_type_1_component(void);
void SystemPeriodic_1_type_3_component(void);
void SystemPeriodic_3_type_1_component(void);
void SystemPeriodic_2_type_3_component(void);
void SystemPeriodic_1_type_1_component_1_tag(void);
void SystemPeriodic_2_type_1_component_1_tag(void);
void SystemPeriodic_2_type_1_and_1_not(void);
void SystemPeriodic_2_type_2_and_1_not(void);
void SystemPeriodic_2_type_2_and_2_not(void);
void SystemPeriodic_4_type_1_and_1_or(void);
void SystemPeriodic_4_type_1_and_1_or_of_3(void);
void SystemPeriodic_1_type_1_and_1_or(void);
void SystemPeriodic_2_type_1_and_1_optional(void);
void SystemPeriodic_2_type_2_and_1_optional(void);
void SystemPeriodic_6_type_1_and_2_optional(void);
void SystemPeriodic_ensure_optional_is_unset_column(void);
void SystemPeriodic_ensure_optional_is_null_shared(void);
void SystemPeriodic_ensure_optional_is_null_field_owned(void);
void SystemPeriodic_ensure_optional_is_null_field_shared(void);
void SystemPeriodic_use_fields_2_owned(void);
void SystemPeriodic_use_fields_1_owned_1_shared(void);
void SystemPeriodic_match_2_systems_w_populated_table(void);
void SystemPeriodic_on_period(void);
void SystemPeriodic_on_period_long_delta(void);
void SystemPeriodic_disabled(void);
void SystemPeriodic_disabled_feature(void);
void SystemPeriodic_disabled_nested_feature(void);
void SystemPeriodic_two_refs(void);
void SystemPeriodic_filter_disabled(void);
void SystemPeriodic_match_disabled(void);
void SystemPeriodic_match_disabled_and_enabled(void);
void SystemPeriodic_match_prefab(void);
void SystemPeriodic_match_prefab_and_normal(void);
void SystemPeriodic_is_shared_on_column_not_set(void);
void SystemPeriodic_owned_column(void);
void SystemPeriodic_owned_not_column(void);
void SystemPeriodic_owned_or_column(void);
void SystemPeriodic_shared_column(void);
void SystemPeriodic_shared_not_column(void);
void SystemPeriodic_shared_or_column(void);
void SystemPeriodic_container_dont_match_inheritance(void);
void SystemPeriodic_cascade_dont_match_inheritance(void);
void SystemPeriodic_not_from_singleton(void);
void SystemPeriodic_not_from_entity(void);
void SystemPeriodic_sys_context(void);
void SystemPeriodic_get_sys_context_from_param(void);
void SystemPeriodic_use_field_w_0_size(void);
void SystemPeriodic_owned_only(void);
void SystemPeriodic_shared_only(void);
void SystemPeriodic_is_in_readonly(void);
void SystemPeriodic_get_period(void);
void SystemPeriodic_and_type(void);
void SystemPeriodic_or_type(void);

// Testsuite 'Timer'
void Timer_timeout(void);
void Timer_interval(void);
void Timer_shared_timeout(void);
void Timer_shared_interval(void);
void Timer_start_stop_one_shot(void);
void Timer_start_stop_interval(void);
void Timer_rate_filter(void);
void Timer_rate_filter_w_rate_filter_src(void);
void Timer_rate_filter_w_timer_src(void);
void Timer_rate_filter_with_empty_src(void);
void Timer_one_shot_timer_entity(void);
void Timer_interval_timer_entity(void);
void Timer_rate_entity(void);
void Timer_nested_rate_entity(void);
void Timer_nested_rate_entity_empty_src(void);
void Timer_naked_tick_entity(void);

// Testsuite 'SystemOnDemand'
void SystemOnDemand_enable_out_after_in(void);
void SystemOnDemand_enable_in_after_out(void);
void SystemOnDemand_enable_out_after_in_2_out_1_in(void);
void SystemOnDemand_enable_out_after_in_1_out_2_in(void);
void SystemOnDemand_enable_in_after_out_2_out_1_in(void);
void SystemOnDemand_enable_in_after_out_1_out_2_in(void);
void SystemOnDemand_disable_after_disable_in(void);
void SystemOnDemand_disable_after_disable_in_2_out_1_in(void);
void SystemOnDemand_disable_after_disable_in_1_out_2_in(void);
void SystemOnDemand_table_after_out(void);
void SystemOnDemand_table_after_out_and_in(void);
void SystemOnDemand_table_after_out_and_in_overlapping_columns(void);
void SystemOnDemand_1_out_system_2_in_systems(void);
void SystemOnDemand_1_out_system_2_in_systems_different_columns(void);
void SystemOnDemand_1_out_system_2_in_systems_overlapping_columns(void);
void SystemOnDemand_disable_after_inactive_in_system(void);
void SystemOnDemand_disable_after_2_inactive_in_systems(void);
void SystemOnDemand_disable_after_2_inactive_in_systems_different_columns(void);
void SystemOnDemand_enable_2_output_1_input_system(void);
void SystemOnDemand_enable_2_output_1_input_system_different_columns(void);
void SystemOnDemand_enable_2_output_1_input_system_overlapping_columns(void);
void SystemOnDemand_out_not_column(void);
void SystemOnDemand_trigger_on_manual(void);
void SystemOnDemand_trigger_on_manual_not_column(void);
void SystemOnDemand_on_demand_task_w_from_entity(void);
void SystemOnDemand_on_demand_task_w_not_from_entity(void);
void SystemOnDemand_enable_after_user_disable(void);

// Testsuite 'SystemCascade'
void SystemCascade_cascade_depth_1(void);
void SystemCascade_cascade_depth_2(void);
void SystemCascade_cascade_depth_2_new_syntax(void);
void SystemCascade_add_after_match(void);
void SystemCascade_adopt_after_match(void);
void SystemCascade_rematch_w_empty_table(void);
void SystemCascade_query_w_only_cascade(void);
void SystemCascade_custom_relation_cascade_depth_1(void);
void SystemCascade_custom_relation_cascade_depth_2(void);
void SystemCascade_custom_relation_add_after_match(void);
void SystemCascade_custom_relation_adopt_after_match(void);
void SystemCascade_custom_relation_rematch_w_empty_table(void);

// Testsuite 'SystemManual'
void SystemManual_setup(void);
void SystemManual_1_type_1_component(void);
void SystemManual_activate_status(void);
void SystemManual_no_automerge(void);
void SystemManual_dont_run_w_unmatching_entity_query(void);

// Testsuite 'Tasks'
void Tasks_no_components(void);
void Tasks_one_tag(void);
void Tasks_from_system(void);
void Tasks_tasks_in_phases(void);

// Testsuite 'Prefab'
void Prefab_setup(void);
void Prefab_new_w_prefab(void);
void Prefab_new_w_count_prefab(void);
void Prefab_new_w_type_w_prefab(void);
void Prefab_add_prefab(void);
void Prefab_add_type_w_prefab(void);
void Prefab_remove_prefab_after_new(void);
void Prefab_remove_prefab_after_add(void);
void Prefab_override_component(void);
void Prefab_override_remove_component(void);
void Prefab_override_2_of_3_components_1_self(void);
void Prefab_new_type_w_1_override(void);
void Prefab_new_type_w_2_overrides(void);
void Prefab_add_type_w_1_overrides(void);
void Prefab_add_type_w_2_overrides(void);
void Prefab_get_ptr_prefab(void);
void Prefab_iterate_w_prefab_field(void);
void Prefab_iterate_w_prefab_shared(void);
void Prefab_match_entity_prefab_w_system_optional(void);
void Prefab_prefab_in_system_expr(void);
void Prefab_dont_match_prefab(void);
void Prefab_new_w_count_w_override(void);
void Prefab_override_2_components_different_size(void);
void Prefab_ignore_prefab_parent_component(void);
void Prefab_match_table_created_in_progress(void);
void Prefab_prefab_w_1_child(void);
void Prefab_prefab_w_2_children(void);
void Prefab_prefab_w_grandchild(void);
void Prefab_prefab_tree_1_2_1(void);
void Prefab_prefab_w_base_w_child(void);
void Prefab_prefab_w_child_w_base(void);
void Prefab_prefab_w_child_w_base_w_children(void);
void Prefab_prefab_w_child_new_w_count(void);
void Prefab_prefab_auto_override_child_component(void);
void Prefab_ignore_on_add(void);
void Prefab_ignore_on_remove(void);
void Prefab_ignore_on_set(void);
void Prefab_on_set_on_instance(void);
void Prefab_instantiate_in_progress(void);
void Prefab_copy_from_prefab_in_progress(void);
void Prefab_copy_from_prefab_first_instance_in_progress(void);
void Prefab_ref_after_realloc(void);
void Prefab_revalidate_ref_w_mixed_table_refs(void);
void Prefab_no_overwrite_on_2nd_add(void);
void Prefab_no_overwrite_on_2nd_add_in_progress(void);
void Prefab_no_instantiate_on_2nd_add(void);
void Prefab_no_instantiate_on_2nd_add_in_progress(void);
void Prefab_nested_prefab_in_progress_w_count(void);
void Prefab_nested_prefab_in_progress_w_count_set_after_override(void);
void Prefab_get_ptr_from_prefab_from_new_table_in_progress(void);
void Prefab_match_base(void);
void Prefab_match_base_after_add_in_prev_phase(void);
void Prefab_override_watched_prefab(void);
void Prefab_rematch_twice(void);
void Prefab_add_to_empty_base_in_system(void);
void Prefab_dont_inherit_disabled(void);
void Prefab_clone_after_inherit_in_on_add(void);
void Prefab_override_from_nested(void);
void Prefab_create_multiple_nested_w_on_set(void);
void Prefab_create_multiple_nested_w_on_set_in_progress(void);
void Prefab_single_on_set_on_child_w_override(void);
void Prefab_force_owned(void);
void Prefab_force_owned_2(void);
void Prefab_force_owned_nested(void);
void Prefab_force_owned_type(void);
void Prefab_force_owned_type_w_pair(void);
void Prefab_prefab_instanceof_hierarchy(void);
void Prefab_override_tag(void);
void Prefab_empty_prefab(void);
void Prefab_instanceof_0(void);
void Prefab_instantiate_empty_child_table(void);
void Prefab_instantiate_emptied_child_table(void);
void Prefab_override_2_prefabs(void);
void Prefab_rematch_after_add_instanceof_to_parent(void);
void Prefab_child_of_instance(void);
void Prefab_rematch_after_prefab_delete(void);
void Prefab_add_tag_w_low_id_to_instance(void);
void Prefab_get_type_after_base_add(void);
void Prefab_get_type_after_recycled_base_add(void);
void Prefab_new_w_recycled_base(void);
void Prefab_add_recycled_base(void);
void Prefab_remove_recycled_base(void);
void Prefab_get_from_recycled_base(void);
void Prefab_override_from_recycled_base(void);
void Prefab_remove_override_from_recycled_base(void);
void Prefab_instantiate_tree_from_recycled_base(void);
void Prefab_rematch_after_add_to_recycled_base(void);

// Testsuite 'System_w_FromContainer'
void System_w_FromContainer_setup(void);
void System_w_FromContainer_1_column_from_container(void);
void System_w_FromContainer_2_column_1_from_container(void);
void System_w_FromContainer_3_column_2_from_container(void);
void System_w_FromContainer_3_column_2_from_different_container(void);
void System_w_FromContainer_2_column_1_from_container_w_not(void);
void System_w_FromContainer_2_column_1_from_container_w_not_prefab(void);
void System_w_FromContainer_3_column_1_from_comtainer_1_from_container_w_not(void);
void System_w_FromContainer_2_column_1_from_container_w_or(void);
void System_w_FromContainer_select_same_from_container(void);
void System_w_FromContainer_add_component_after_match(void);
void System_w_FromContainer_add_component_after_match_and_rematch(void);
void System_w_FromContainer_add_component_after_match_unmatch(void);
void System_w_FromContainer_add_component_after_match_unmatch_match(void);
void System_w_FromContainer_add_component_after_match_2_systems(void);
void System_w_FromContainer_add_component_in_progress_after_match(void);
void System_w_FromContainer_add_component_after_match_and_rematch_w_entity_type_expr(void);
void System_w_FromContainer_add_component_after_match_and_rematch_w_entity_type_expr_in_progress(void);
void System_w_FromContainer_adopt_after_match(void);
void System_w_FromContainer_new_child_after_match(void);
void System_w_FromContainer_realloc_after_match(void);

// Testsuite 'System_w_FromId'
void System_w_FromId_2_column_1_from_id(void);
void System_w_FromId_3_column_2_from_id(void);
void System_w_FromId_column_type(void);

// Testsuite 'System_w_FromSystem'
void System_w_FromSystem_2_column_1_from_system(void);
void System_w_FromSystem_3_column_2_from_system(void);
void System_w_FromSystem_auto_add_tag(void);

// Testsuite 'System_w_FromEntity'
void System_w_FromEntity_2_column_1_from_entity(void);
void System_w_FromEntity_task_from_entity(void);
void System_w_FromEntity_task_not_from_entity(void);

// Testsuite 'World'
void World_setup(void);
void World_progress_w_0(void);
void World_progress_w_t(void);
void World_get_tick(void);
void World_entity_range_offset(void);
void World_entity_range_offset_out_of_range(void);
void World_entity_range_limit_out_of_range(void);
void World_entity_range_add_existing_in_progress(void);
void World_entity_range_add_in_range_in_progress(void);
void World_entity_range_add_out_of_range_in_progress(void);
void World_entity_range_out_of_range_check_disabled(void);
void World_dim(void);
void World_dim_dim_type(void);
void World_phases(void);
void World_phases_w_merging(void);
void World_phases_match_in_create(void);
void World_measure_time(void);
void World_control_fps(void);
void World_control_fps_busy_system(void);
void World_control_fps_busy_app(void);
void World_control_fps_random_system(void);
void World_control_fps_random_app(void);
void World_measure_fps_vs_actual(void);
void World_measure_delta_time_vs_actual(void);
void World_system_time_scale(void);
void World_quit(void);
void World_get_delta_time(void);
void World_get_delta_time_auto(void);
void World_recreate_world(void);
void World_recreate_world_w_component(void);
void World_no_threading(void);
void World_no_time(void);
void World_is_entity_enabled(void);
void World_get_stats(void);

// Testsuite 'Type'
void Type_setup(void);
void Type_type_of_1_tostr(void);
void Type_type_of_2_tostr(void);
void Type_type_of_2_tostr_no_id(void);
void Type_type_redefine(void);
void Type_type_from_array(void);
void Type_type_from_array_unsorted(void);
void Type_type_has(void);
void Type_type_has_not(void);
void Type_zero_type_has_not(void);
void Type_type_has_prefab(void);
void Type_type_has_parent(void);
void Type_type_has_pair(void);
void Type_type_has_pair_exact(void);
void Type_type_has_pair_0(void);
void Type_type_has_pair_0_multiple(void);
void Type_type_has_pair_0_no_pair(void);
void Type_type_owns_pair(void);
void Type_type_owns_pair_exact(void);
void Type_type_owns_pair_0(void);
void Type_type_owns_pair_0_multiple(void);
void Type_type_owns_pair_0_no_pair(void);
void Type_type_merge(void);
void Type_type_merge_overlap(void);
void Type_type_merge_overlap_one(void);
void Type_type_merge_overlap_w_flag(void);
void Type_type_merge_overlap_w_flags_from_both(void);
void Type_type_add(void);
void Type_type_add_empty(void);
void Type_type_add_entity_again(void);
void Type_type_add_out_of_order(void);
void Type_type_add_existing(void);
void Type_type_add_empty_existing(void);
void Type_type_add_out_of_order_existing(void);
void Type_type_remove(void);
void Type_type_remove_empty(void);
void Type_type_remove_non_existing(void);
void Type_type_of_2_add(void);
void Type_type_of_3_add_entity_again(void);
void Type_invalid_entity_type_expression(void);
void Type_invalid_singleton_type_expression(void);
void Type_invalid_container_type_expression(void);
void Type_invalid_system_type_expression(void);
void Type_type_from_empty_entity(void);
void Type_get_type(void);
void Type_get_type_from_empty(void);
void Type_get_type_from_0(void);
void Type_entity_from_type(void);
void Type_entity_from_empty_type(void);
void Type_entity_from_type_w_2_elements(void);
void Type_type_from_entity(void);
void Type_type_from_empty(void);
void Type_type_from_0(void);
void Type_type_to_expr_1_comp(void);
void Type_type_to_expr_2_comp(void);
void Type_type_to_expr_instanceof(void);
void Type_type_to_expr_childof(void);
void Type_type_to_expr_pair(void);
void Type_type_to_expr_pair_w_comp(void);
void Type_type_to_expr_scope(void);
void Type_type_from_expr(void);
void Type_type_from_expr_scope(void);
void Type_type_from_expr_digit(void);
void Type_type_from_expr_instanceof(void);
void Type_type_from_expr_childof(void);
void Type_type_from_expr_pair(void);
void Type_type_from_expr_pair_w_comp(void);
void Type_entity_str(void);
void Type_entity_path_str(void);
void Type_entity_instanceof_str(void);
void Type_entity_childof_str(void);
void Type_entity_pair_str(void);
void Type_entity_switch_str(void);
void Type_entity_case_str(void);
void Type_entity_and_str(void);
void Type_entity_or_str(void);
void Type_entity_xor_str(void);
void Type_entity_not_str(void);
void Type_entity_str_small_buffer(void);
void Type_role_childof_str(void);
void Type_role_instanceof_str(void);
void Type_role_pair_str(void);
void Type_role_switch_str(void);
void Type_role_case_str(void);
void Type_role_and_str(void);
void Type_role_or_str(void);
void Type_role_xor_str(void);
void Type_role_not_str(void);
void Type_role_owned_str(void);
void Type_role_disabled_str(void);
void Type_large_type_expr(void);
void Type_large_type_expr_limit(void);

// Testsuite 'Run'
void Run_setup(void);
void Run_run(void);
void Run_run_w_param(void);
void Run_run_no_match(void);
void Run_run_w_offset(void);
void Run_run_w_offset_skip_1_archetype(void);
void Run_run_w_offset_skip_1_archetype_plus_one(void);
void Run_run_w_offset_skip_2_archetypes(void);
void Run_run_w_limit_skip_1_archetype(void);
void Run_run_w_limit_skip_1_archetype_minus_one(void);
void Run_run_w_limit_skip_2_archetypes(void);
void Run_run_w_offset_1_limit_max(void);
void Run_run_w_offset_1_limit_minus_1(void);
void Run_run_w_offset_2_type_limit_max(void);
void Run_run_w_offset_2_type_limit_minus_1(void);
void Run_run_w_limit_1_all_offsets(void);
void Run_run_w_offset_out_of_bounds(void);
void Run_run_w_limit_out_of_bounds(void);
void Run_run_w_component_filter(void);
void Run_run_w_type_filter_of_2(void);
void Run_run_w_container_filter(void);
void Run_run_comb_10_entities_1_type(void);
void Run_run_comb_10_entities_2_types(void);
void Run_run_w_interrupt(void);
void Run_run_staging(void);

// Testsuite 'MultiThread'
void MultiThread_setup(void);
void MultiThread_2_thread_1_entity(void);
void MultiThread_2_thread_2_entity(void);
void MultiThread_2_thread_5_entity(void);
void MultiThread_2_thread_10_entity(void);
void MultiThread_3_thread_1_entity(void);
void MultiThread_3_thread_2_entity(void);
void MultiThread_3_thread_5_entity(void);
void MultiThread_3_thread_10_entity(void);
void MultiThread_4_thread_1_entity(void);
void MultiThread_4_thread_2_entity(void);
void MultiThread_4_thread_5_entity(void);
void MultiThread_4_thread_10_entity(void);
void MultiThread_5_thread_1_entity(void);
void MultiThread_5_thread_2_entity(void);
void MultiThread_5_thread_5_entity(void);
void MultiThread_5_thread_10_entity(void);
void MultiThread_6_thread_1_entity(void);
void MultiThread_6_thread_2_entity(void);
void MultiThread_6_thread_5_entity(void);
void MultiThread_6_thread_10_entity(void);
void MultiThread_2_thread_test_combs_100_entity(void);
void MultiThread_3_thread_test_combs_100_entity(void);
void MultiThread_4_thread_test_combs_100_entity(void);
void MultiThread_5_thread_test_combs_100_entity(void);
void MultiThread_6_thread_test_combs_100_entity(void);
void MultiThread_2_thread_test_combs_100_entity_2_types(void);
void MultiThread_3_thread_test_combs_100_entity_2_types(void);
void MultiThread_4_thread_test_combs_100_entity_2_types(void);
void MultiThread_5_thread_test_combs_100_entity_2_types(void);
void MultiThread_6_thread_test_combs_100_entity_2_types(void);
void MultiThread_change_thread_count(void);
void MultiThread_multithread_quit(void);
void MultiThread_schedule_w_tasks(void);
void MultiThread_reactive_system(void);
void MultiThread_fini_after_set_threads(void);

// Testsuite 'DeferredActions'
void DeferredActions_defer_new(void);
void DeferredActions_defer_bulk_new(void);
void DeferredActions_defer_bulk_new_w_data(void);
void DeferredActions_defer_bulk_new_w_data_pair(void);
void DeferredActions_defer_bulk_new_two(void);
void DeferredActions_defer_bulk_new_w_data_two(void);
void DeferredActions_defer_add(void);
void DeferredActions_defer_add_two(void);
void DeferredActions_defer_remove(void);
void DeferredActions_defer_remove_two(void);
void DeferredActions_defer_set(void);
void DeferredActions_defer_delete(void);
void DeferredActions_defer_twice(void);
void DeferredActions_defer_twice_in_progress(void);
void DeferredActions_run_w_defer(void);
void DeferredActions_system_in_progress_w_defer(void);
void DeferredActions_defer_get_mut_no_modify(void);
void DeferredActions_defer_get_mut_w_modify(void);
void DeferredActions_defer_modify(void);
void DeferredActions_defer_set_pair(void);
void DeferredActions_defer_clear(void);
void DeferredActions_defer_add_after_delete(void);
void DeferredActions_defer_set_after_delete(void);
void DeferredActions_defer_get_mut_after_delete(void);
void DeferredActions_defer_get_mut_after_delete_2nd_to_last(void);
void DeferredActions_defer_add_child_to_deleted_parent(void);
void DeferredActions_recreate_deleted_entity_while_deferred(void);
void DeferredActions_discard_add(void);
void DeferredActions_discard_remove(void);
void DeferredActions_discard_add_two(void);
void DeferredActions_discard_remove_two(void);
void DeferredActions_discard_child(void);
void DeferredActions_discard_child_w_add(void);
void DeferredActions_defer_return_value(void);
void DeferredActions_defer_get_mut_pair(void);
void DeferredActions_async_stage_add(void);
void DeferredActions_async_stage_add_twice(void);
void DeferredActions_async_stage_remove(void);
void DeferredActions_async_stage_clear(void);
void DeferredActions_async_stage_delete(void);
void DeferredActions_async_stage_new(void);
void DeferredActions_async_stage_no_get(void);
void DeferredActions_async_stage_readonly(void);
void DeferredActions_async_stage_is_async(void);
void DeferredActions_register_component_while_in_progress(void);
void DeferredActions_register_component_while_staged(void);
void DeferredActions_register_component_while_deferred(void);
void DeferredActions_defer_enable(void);
void DeferredActions_defer_disable(void);

// Testsuite 'SingleThreadStaging'
void SingleThreadStaging_setup(void);
void SingleThreadStaging_new_empty(void);
void SingleThreadStaging_new_w_component(void);
void SingleThreadStaging_new_w_type_of_2(void);
void SingleThreadStaging_new_empty_w_count(void);
void SingleThreadStaging_new_component_w_count(void);
void SingleThreadStaging_new_type_w_count(void);
void SingleThreadStaging_add_to_new_empty(void);
void SingleThreadStaging_2_add_to_new_empty(void);
void SingleThreadStaging_add_remove_same_to_new_empty(void);
void SingleThreadStaging_add_remove_2_same_to_new_empty(void);
void SingleThreadStaging_add_remove_same_to_new_w_component(void);
void SingleThreadStaging_2_add_1_remove_to_new_empty(void);
void SingleThreadStaging_2_add_1_remove_same_to_new_empty(void);
void SingleThreadStaging_clone(void);
void SingleThreadStaging_clone_w_value(void);
void SingleThreadStaging_add_to_current(void);
void SingleThreadStaging_2_add_to_current(void);
void SingleThreadStaging_remove_from_current(void);
void SingleThreadStaging_remove_2_from_current(void);
void SingleThreadStaging_add_remove_same_to_current(void);
void SingleThreadStaging_add_remove_same_existing_to_current(void);
void SingleThreadStaging_remove_add_same_to_current(void);
void SingleThreadStaging_remove_add_same_existing_to_current(void);
void SingleThreadStaging_add_remove_2_same_to_current(void);
void SingleThreadStaging_add_remove_2_same_existing_to_current(void);
void SingleThreadStaging_remove_add_2_same_to_current(void);
void SingleThreadStaging_remove_add_2_same_existing_to_current(void);
void SingleThreadStaging_add_remove_different_to_current(void);
void SingleThreadStaging_add_remove_add_same_to_current(void);
void SingleThreadStaging_2_add_1_remove_to_current(void);
void SingleThreadStaging_1_add_2_remove_to_current(void);
void SingleThreadStaging_delete_current(void);
void SingleThreadStaging_delete_even(void);
void SingleThreadStaging_delete_new_empty(void);
void SingleThreadStaging_delete_new_w_component(void);
void SingleThreadStaging_set_current(void);
void SingleThreadStaging_set_new_empty(void);
void SingleThreadStaging_set_new_w_component(void);
void SingleThreadStaging_set_existing_new_w_component(void);
void SingleThreadStaging_set_new_after_add(void);
void SingleThreadStaging_remove_after_set(void);
void SingleThreadStaging_delete_after_set(void);
void SingleThreadStaging_add_to_current_in_on_add(void);
void SingleThreadStaging_remove_from_current_in_on_add(void);
void SingleThreadStaging_remove_added_component_in_on_add(void);
void SingleThreadStaging_match_table_created_in_progress(void);
void SingleThreadStaging_match_table_created_w_new_in_progress(void);
void SingleThreadStaging_match_table_created_w_new_in_on_set(void);
void SingleThreadStaging_merge_table_w_container_added_in_progress(void);
void SingleThreadStaging_merge_table_w_container_added_on_set(void);
void SingleThreadStaging_merge_table_w_container_added_on_set_reverse(void);
void SingleThreadStaging_merge_after_tasks(void);
void SingleThreadStaging_override_after_remove_in_progress(void);
void SingleThreadStaging_get_parent_in_progress(void);
void SingleThreadStaging_merge_once(void);
void SingleThreadStaging_clear_stage_after_merge(void);
void SingleThreadStaging_get_mutable(void);
void SingleThreadStaging_get_mutable_from_main(void);
void SingleThreadStaging_get_mutable_w_add(void);
void SingleThreadStaging_on_add_after_new_type_in_progress(void);
void SingleThreadStaging_new_type_from_entity(void);
void SingleThreadStaging_existing_type_from_entity(void);
void SingleThreadStaging_new_type_add(void);
void SingleThreadStaging_existing_type_add(void);
void SingleThreadStaging_lock_table(void);
void SingleThreadStaging_recursive_lock_table(void);
void SingleThreadStaging_modify_after_lock(void);

// Testsuite 'MultiThreadStaging'
void MultiThreadStaging_setup(void);
void MultiThreadStaging_2_threads_add_to_current(void);
void MultiThreadStaging_3_threads_add_to_current(void);
void MultiThreadStaging_4_threads_add_to_current(void);
void MultiThreadStaging_5_threads_add_to_current(void);
void MultiThreadStaging_6_threads_add_to_current(void);
void MultiThreadStaging_2_threads_on_add(void);
void MultiThreadStaging_new_w_count(void);
void MultiThreadStaging_custom_thread_auto_merge(void);
void MultiThreadStaging_custom_thread_manual_merge(void);
void MultiThreadStaging_custom_thread_partial_manual_merge(void);

// Testsuite 'Stresstests'
void Stresstests_setup(void);
void Stresstests_create_1m_set_two_components(void);
void Stresstests_create_delete_entity_random_components(void);
void Stresstests_set_entity_random_components(void);
void Stresstests_create_delete_entity_random_components_staged(void);
void Stresstests_set_entity_random_components_staged(void);
void Stresstests_create_delete_entity_random_components_2_threads(void);
void Stresstests_set_entity_random_components_2_threads(void);
void Stresstests_create_delete_entity_random_components_6_threads(void);
void Stresstests_set_entity_random_components_6_threads(void);
void Stresstests_create_delete_entity_random_components_12_threads(void);
void Stresstests_set_entity_random_components_12_threads(void);
void Stresstests_create_2m_entities_1_comp(void);
void Stresstests_create_2m_entities_bulk_1_comp(void);
void Stresstests_add_1k_tags(void);
void Stresstests_create_1m_set_two_components(void);

// Testsuite 'Snapshot'
void Snapshot_simple_snapshot(void);
void Snapshot_snapshot_after_new(void);
void Snapshot_snapshot_after_delete(void);
void Snapshot_snapshot_after_new_type(void);
void Snapshot_snapshot_after_add(void);
void Snapshot_snapshot_after_remove(void);
void Snapshot_snapshot_w_include_filter(void);
void Snapshot_snapshot_w_exclude_filter(void);
void Snapshot_snapshot_w_filter_after_new(void);
void Snapshot_snapshot_w_filter_after_delete(void);
void Snapshot_snapshot_free_empty(void);
void Snapshot_snapshot_free(void);
void Snapshot_snapshot_free_filtered(void);
void Snapshot_snapshot_activate_table_w_filter(void);
void Snapshot_snapshot_copy(void);
void Snapshot_snapshot_copy_filtered(void);
void Snapshot_snapshot_copy_w_filter(void);
void Snapshot_snapshot_get_ref_after_restore(void);
void Snapshot_new_after_snapshot(void);
void Snapshot_new_empty_after_snapshot(void);
void Snapshot_add_after_snapshot(void);
void Snapshot_delete_after_snapshot(void);
void Snapshot_set_after_snapshot(void);
void Snapshot_restore_recycled(void);
void Snapshot_snapshot_w_new_in_onset(void);
void Snapshot_snapshot_w_new_in_onset_in_snapshot_table(void);

// Testsuite 'ReaderWriter'
void ReaderWriter_simple(void);
void ReaderWriter_id(void);
void ReaderWriter_id_w_simple(void);
void ReaderWriter_unaligned(void);
void ReaderWriter_empty(void);
void ReaderWriter_tag(void);
void ReaderWriter_simple_w_tag(void);
void ReaderWriter_tag_w_simple(void);
void ReaderWriter_empty_parent(void);
void ReaderWriter_parent(void);
void ReaderWriter_simple_w_parent(void);
void ReaderWriter_inheritance(void);
void ReaderWriter_simple_w_inheritance(void);
void ReaderWriter_deserialize_twice(void);
void ReaderWriter_entity_conflict(void);
void ReaderWriter_snapshot_reader_simple(void);
void ReaderWriter_snapshot_reader_id(void);
void ReaderWriter_read_zero_size(void);
void ReaderWriter_write_zero_size(void);
void ReaderWriter_invalid_header(void);
void ReaderWriter_recycled_id(void);
void ReaderWriter_new_component_after_restore(void);
void ReaderWriter_delete_all_after_restore(void);

// Testsuite 'FilterIter'
void FilterIter_iter_one_table(void);
void FilterIter_iter_two_tables(void);
void FilterIter_iter_two_comps(void);
void FilterIter_iter_snapshot_one_table(void);
void FilterIter_iter_snapshot_two_tables(void);
void FilterIter_iter_snapshot_two_comps(void);
void FilterIter_iter_snapshot_filtered_table(void);
void FilterIter_iter_get_component_index(void);
void FilterIter_iter_get_component_size(void);
void FilterIter_iter_get_tag_index(void);
void FilterIter_iter_get_tag_size(void);
void FilterIter_iter_get_tag_column(void);

// Testsuite 'Modules'
void Modules_setup(void);
void Modules_simple_module(void);
void Modules_import_module_from_system(void);
void Modules_import_again(void);
void Modules_scoped_component(void);
void Modules_scoped_tag(void);
void Modules_scoped_system(void);
void Modules_scoped_entity(void);
void Modules_name_prefix_component(void);
void Modules_name_prefix_tag(void);
void Modules_name_prefix_system(void);
void Modules_name_prefix_entity(void);
void Modules_name_prefix_type(void);
void Modules_name_prefix_prefab(void);
void Modules_name_prefix_pipeline(void);
void Modules_name_prefix_trigger(void);
void Modules_name_prefix_underscore(void);
void Modules_lookup_by_symbol(void);
void Modules_import_type(void);
void Modules_nested_module(void);
void Modules_module_tag_on_namespace(void);

// Testsuite 'DirectAccess'
void DirectAccess_get_table_from_str(void);
void DirectAccess_get_table_from_type(void);
void DirectAccess_insert_record(void);
void DirectAccess_insert_record_w_entity(void);
void DirectAccess_table_count(void);
void DirectAccess_find_column(void);
void DirectAccess_get_column(void);
void DirectAccess_get_empty_column(void);
void DirectAccess_set_column(void);
void DirectAccess_delete_column(void);
void DirectAccess_delete_column_explicit(void);
void DirectAccess_delete_column_w_dtor(void);
void DirectAccess_copy_to(void);
void DirectAccess_copy_pod_to(void);
void DirectAccess_move_to(void);
void DirectAccess_copy_to_no_copy(void);
void DirectAccess_move_to_no_move(void);
void DirectAccess_find_record_not_exists(void);
void DirectAccess_get_entities_empty_table(void);
void DirectAccess_get_records_empty_table(void);
void DirectAccess_get_column_empty_table(void);
void DirectAccess_delete_column_empty_table(void);
void DirectAccess_get_record_column_empty_table(void);
void DirectAccess_has_module(void);

// Testsuite 'Internals'
void Internals_setup(void);
void Internals_deactivate_table(void);
void Internals_activate_table(void);
void Internals_activate_deactivate_table(void);
void Internals_activate_deactivate_reactive(void);
void Internals_activate_deactivate_activate_other(void);
void Internals_no_double_system_table_after_merge(void);
void Internals_recreate_deleted_table(void);
void Internals_create_65k_tables(void);

// Testsuite 'Error'
void Error_setup(void);
void Error_abort(void);
void Error_abort_w_param(void);
void Error_override_abort(void);
void Error_assert_true(void);
void Error_assert_false(void);
void Error_assert_false_w_param(void);
void Error_error_codes(void);
void Error_log_dbg(void);
void Error_log_log(void);
void Error_log_warning(void);
void Error_log_error(void);

// Testsuite 'Deprecated'
void Deprecated_trait_type_str(void);

bake_test_case Entity_testcases[] = {
    {
        "init_id",
        Entity_init_id
    },
    {
        "init_id_name",
        Entity_init_id_name
    },
    {
        "init_id_path",
        Entity_init_id_path
    },
    {
        "init_id_add_1_comp",
        Entity_init_id_add_1_comp
    },
    {
        "init_id_add_2_comp",
        Entity_init_id_add_2_comp
    },
    {
        "init_id_w_scope",
        Entity_init_id_w_scope
    },
    {
        "init_id_name_w_scope",
        Entity_init_id_name_w_scope
    },
    {
        "init_id_path_w_scope",
        Entity_init_id_path_w_scope
    },
    {
        "init_id_name_1_comp",
        Entity_init_id_name_1_comp
    },
    {
        "init_id_name_2_comp",
        Entity_init_id_name_2_comp
    },
    {
        "init_id_name_2_comp_w_scope",
        Entity_init_id_name_2_comp_w_scope
    },
    {
        "id_add_1_comp",
        Entity_id_add_1_comp
    },
    {
        "id_add_2_comp",
        Entity_id_add_2_comp
    },
    {
        "id_remove_1_comp",
        Entity_id_remove_1_comp
    },
    {
        "id_remove_2_comp",
        Entity_id_remove_2_comp
    },
    {
        "init_id_path_w_sep",
        Entity_init_id_path_w_sep
    },
    {
        "find_id_name",
        Entity_find_id_name
    },
    {
        "find_w_existing_id_name",
        Entity_find_w_existing_id_name
    },
    {
        "find_id_name_w_scope",
        Entity_find_id_name_w_scope
    },
    {
        "find_id_path",
        Entity_find_id_path
    },
    {
        "find_id_path_w_scope",
        Entity_find_id_path_w_scope
    },
    {
        "find_id_name_match",
        Entity_find_id_name_match
    },
    {
        "find_id_name_match_w_scope",
        Entity_find_id_name_match_w_scope
    },
    {
        "find_id_path_match",
        Entity_find_id_path_match
    },
    {
        "find_id_path_match_w_scope",
        Entity_find_id_path_match_w_scope
    },
    {
        "find_id_name_mismatch",
        Entity_find_id_name_mismatch
    },
    {
        "find_id_name_mismatch_w_scope",
        Entity_find_id_name_mismatch_w_scope
    },
    {
        "find_id_path_mismatch",
        Entity_find_id_path_mismatch
    },
    {
        "find_id_path_mismatch_w_scope",
        Entity_find_id_path_mismatch_w_scope
    },
    {
        "find_id_add_1_comp",
        Entity_find_id_add_1_comp
    },
    {
        "find_id_add_2_comp",
        Entity_find_id_add_2_comp
    },
    {
        "find_id_remove_1_comp",
        Entity_find_id_remove_1_comp
    },
    {
        "find_id_remove_2_comp",
        Entity_find_id_remove_2_comp
    },
    {
        "init_w_scope_name",
        Entity_init_w_scope_name
    },
    {
        "init_w_core_name",
        Entity_init_w_core_name
    },
    {
        "init_w_with",
        Entity_init_w_with
    },
    {
        "init_w_with_w_name",
        Entity_init_w_with_w_name
    },
    {
        "init_w_with_w_scope",
        Entity_init_w_with_w_scope
    },
    {
        "init_w_with_w_name_scope",
        Entity_init_w_with_w_name_scope
    }
};

bake_test_case New_testcases[] = {
    {
        "empty",
        New_empty
    },
    {
        "component",
        New_component
    },
    {
        "type",
        New_type
    },
    {
        "type_of_2",
        New_type_of_2
    },
    {
        "type_w_type",
        New_type_w_type
    },
    {
        "type_w_2_types",
        New_type_w_2_types
    },
    {
        "type_mixed",
        New_type_mixed
    },
    {
        "tag",
        New_tag
    },
    {
        "type_w_tag",
        New_type_w_tag
    },
    {
        "type_w_2_tags",
        New_type_w_2_tags
    },
    {
        "type_w_tag_mixed",
        New_type_w_tag_mixed
    },
    {
        "redefine_component",
        New_redefine_component
    },
    {
        "recycle_id_empty",
        New_recycle_id_empty
    },
    {
        "recycle_id_w_entity",
        New_recycle_id_w_entity
    },
    {
        "recycle_id_w_type",
        New_recycle_id_w_type
    },
    {
        "recycle_empty_staged_delete",
        New_recycle_empty_staged_delete
    },
    {
        "recycle_staged_delete",
        New_recycle_staged_delete
    },
    {
        "new_id",
        New_new_id
    },
    {
        "new_component_id",
        New_new_component_id
    },
    {
        "new_hi_component_id",
        New_new_hi_component_id
    },
    {
        "new_component_id_skip_used",
        New_new_component_id_skip_used
    },
    {
        "new_component_id_skip_to_hi_id",
        New_new_component_id_skip_to_hi_id
    },
    {
        "new_w_entity_0",
        New_new_w_entity_0
    },
    {
        "create_w_explicit_id_2_worlds",
        New_create_w_explicit_id_2_worlds
    },
    {
        "new_w_id_0_w_with",
        New_new_w_id_0_w_with
    },
    {
        "new_w_id_w_with",
        New_new_w_id_w_with
    },
    {
        "new_w_type_0_w_with",
        New_new_w_type_0_w_with
    },
    {
        "new_w_type_w_with",
        New_new_w_type_w_with
    },
    {
        "new_w_id_w_with_w_scope",
        New_new_w_id_w_with_w_scope
    },
    {
        "new_w_type_w_with_w_scope",
        New_new_w_type_w_with_w_scope
    },
    {
        "new_w_id_w_with_defer",
        New_new_w_id_w_with_defer
    },
    {
        "new_w_id_w_with_defer_w_scope",
        New_new_w_id_w_with_defer_w_scope
    },
    {
        "new_w_type_w_with_defer",
        New_new_w_type_w_with_defer
    },
    {
        "new_w_type_w_with_defer_w_scope",
        New_new_w_type_w_with_defer_w_scope
    }
};

bake_test_case New_w_Count_testcases[] = {
    {
        "empty",
        New_w_Count_empty
    },
    {
        "component",
        New_w_Count_component
    },
    {
        "type",
        New_w_Count_type
    },
    {
        "type_of_2",
        New_w_Count_type_of_2
    },
    {
        "type_w_type",
        New_w_Count_type_w_type
    },
    {
        "type_w_2_types",
        New_w_Count_type_w_2_types
    },
    {
        "type_mixed",
        New_w_Count_type_mixed
    },
    {
        "tag",
        New_w_Count_tag
    },
    {
        "type_w_tag",
        New_w_Count_type_w_tag
    },
    {
        "type_w_2_tags",
        New_w_Count_type_w_2_tags
    },
    {
        "type_w_tag_mixed",
        New_w_Count_type_w_tag_mixed
    },
    {
        "new_w_data_1_comp",
        New_w_Count_new_w_data_1_comp
    },
    {
        "new_w_data_2_comp",
        New_w_Count_new_w_data_2_comp
    },
    {
        "new_w_data_w_tag",
        New_w_Count_new_w_data_w_tag
    },
    {
        "new_w_data_w_comp_and_tag",
        New_w_Count_new_w_data_w_comp_and_tag
    },
    {
        "new_w_data_pair",
        New_w_Count_new_w_data_pair
    },
    {
        "new_w_data_pair",
        New_w_Count_new_w_data_pair
    },
    {
        "new_w_data_2_comp_1_not_set",
        New_w_Count_new_w_data_2_comp_1_not_set
    },
    {
        "new_w_on_add_on_set_monitor",
        New_w_Count_new_w_on_add_on_set_monitor
    },
    {
        "new_w_data_override_set_comp",
        New_w_Count_new_w_data_override_set_comp
    },
    {
        "new_w_data_override_set_pair",
        New_w_Count_new_w_data_override_set_pair
    }
};

bake_test_case Add_testcases[] = {
    {
        "zero",
        Add_zero
    },
    {
        "component",
        Add_component
    },
    {
        "component_again",
        Add_component_again
    },
    {
        "2_components",
        Add_2_components
    },
    {
        "2_components_again",
        Add_2_components_again
    },
    {
        "2_components_overlap",
        Add_2_components_overlap
    },
    {
        "type",
        Add_type
    },
    {
        "type_of_2",
        Add_type_of_2
    },
    {
        "type_w_type",
        Add_type_w_type
    },
    {
        "type_w_2_types",
        Add_type_w_2_types
    },
    {
        "type_mixed",
        Add_type_mixed
    },
    {
        "type_again",
        Add_type_again
    },
    {
        "type_overlap",
        Add_type_overlap
    },
    {
        "type_again_component",
        Add_type_again_component
    },
    {
        "type_overlap_component",
        Add_type_overlap_component
    },
    {
        "component_to_nonempty",
        Add_component_to_nonempty
    },
    {
        "component_to_nonempty_again",
        Add_component_to_nonempty_again
    },
    {
        "component_to_nonempty_overlap",
        Add_component_to_nonempty_overlap
    },
    {
        "type_to_nonempty",
        Add_type_to_nonempty
    },
    {
        "type_to_nonempty_again",
        Add_type_to_nonempty_again
    },
    {
        "type_to_nonempty_overlap",
        Add_type_to_nonempty_overlap
    },
    {
        "tag",
        Add_tag
    },
    {
        "type_w_tag",
        Add_type_w_tag
    },
    {
        "type_w_2_tags",
        Add_type_w_2_tags
    },
    {
        "type_w_tag_mixed",
        Add_type_w_tag_mixed
    },
    {
        "add_remove",
        Add_add_remove
    },
    {
        "add_remove_same",
        Add_add_remove_same
    },
    {
        "add_remove_entity",
        Add_add_remove_entity
    },
    {
        "add_remove_entity_same",
        Add_add_remove_entity_same
    },
    {
        "add_2_remove",
        Add_add_2_remove
    },
    {
        "add_entity",
        Add_add_entity
    },
    {
        "remove_entity",
        Add_remove_entity
    },
    {
        "add_0_entity",
        Add_add_0_entity
    },
    {
        "remove_0_entity",
        Add_remove_0_entity
    },
    {
        "add_w_xor",
        Add_add_w_xor
    },
    {
        "add_same_w_xor",
        Add_add_same_w_xor
    },
    {
        "add_after_remove_xor",
        Add_add_after_remove_xor
    }
};

bake_test_case Switch_testcases[] = {
    {
        "get_case_empty",
        Switch_get_case_empty
    },
    {
        "get_case_no_switch",
        Switch_get_case_no_switch
    },
    {
        "get_case_unset",
        Switch_get_case_unset
    },
    {
        "get_case_set",
        Switch_get_case_set
    },
    {
        "get_case_change",
        Switch_get_case_change
    },
    {
        "remove_case",
        Switch_remove_case
    },
    {
        "remove_last",
        Switch_remove_last
    },
    {
        "3_entities_same_case",
        Switch_3_entities_same_case
    },
    {
        "2_entities_1_change_case",
        Switch_2_entities_1_change_case
    },
    {
        "3_entities_change_case",
        Switch_3_entities_change_case
    },
    {
        "query_switch",
        Switch_query_switch
    },
    {
        "query_1_case_1_type",
        Switch_query_1_case_1_type
    },
    {
        "query_1_case_2_types",
        Switch_query_1_case_2_types
    },
    {
        "query_2_cases_1_type",
        Switch_query_2_cases_1_type
    },
    {
        "query_2_cases_2_types",
        Switch_query_2_cases_2_types
    },
    {
        "query_after_remove",
        Switch_query_after_remove
    },
    {
        "add_switch_in_stage",
        Switch_add_switch_in_stage
    },
    {
        "add_case_in_stage",
        Switch_add_case_in_stage
    },
    {
        "change_case_in_stage",
        Switch_change_case_in_stage
    },
    {
        "change_one_case_in_stage",
        Switch_change_one_case_in_stage
    },
    {
        "remove_switch_in_stage",
        Switch_remove_switch_in_stage
    },
    {
        "switch_no_match_for_case",
        Switch_switch_no_match_for_case
    },
    {
        "empty_entity_has_case",
        Switch_empty_entity_has_case
    },
    {
        "zero_entity_has_case",
        Switch_zero_entity_has_case
    },
    {
        "add_to_entity_w_switch",
        Switch_add_to_entity_w_switch
    },
    {
        "add_pair_to_entity_w_switch",
        Switch_add_pair_to_entity_w_switch
    },
    {
        "sort",
        Switch_sort
    },
    {
        "recycled_tags",
        Switch_recycled_tags
    },
    {
        "query_recycled_tags",
        Switch_query_recycled_tags
    }
};

bake_test_case EnabledComponents_testcases[] = {
    {
        "is_component_enabled",
        EnabledComponents_is_component_enabled
    },
    {
        "is_empty_entity_disabled",
        EnabledComponents_is_empty_entity_disabled
    },
    {
        "is_0_entity_disabled",
        EnabledComponents_is_0_entity_disabled
    },
    {
        "is_0_component_disabled",
        EnabledComponents_is_0_component_disabled
    },
    {
        "is_nonexist_component_disabled",
        EnabledComponents_is_nonexist_component_disabled
    },
    {
        "is_enabled_component_enabled",
        EnabledComponents_is_enabled_component_enabled
    },
    {
        "is_disabled_component_enabled",
        EnabledComponents_is_disabled_component_enabled
    },
    {
        "has_enabled_component",
        EnabledComponents_has_enabled_component
    },
    {
        "is_enabled_after_add",
        EnabledComponents_is_enabled_after_add
    },
    {
        "is_enabled_after_remove",
        EnabledComponents_is_enabled_after_remove
    },
    {
        "is_enabled_after_disable",
        EnabledComponents_is_enabled_after_disable
    },
    {
        "is_disabled_after_enable",
        EnabledComponents_is_disabled_after_enable
    },
    {
        "is_enabled_randomized",
        EnabledComponents_is_enabled_randomized
    },
    {
        "is_enabled_after_add_randomized",
        EnabledComponents_is_enabled_after_add_randomized
    },
    {
        "is_enabled_after_randomized_add_randomized",
        EnabledComponents_is_enabled_after_randomized_add_randomized
    },
    {
        "is_enabled_2",
        EnabledComponents_is_enabled_2
    },
    {
        "is_enabled_3",
        EnabledComponents_is_enabled_3
    },
    {
        "is_enabled_2_after_add",
        EnabledComponents_is_enabled_2_after_add
    },
    {
        "is_enabled_3_after_add",
        EnabledComponents_is_enabled_3_after_add
    },
    {
        "query_disabled",
        EnabledComponents_query_disabled
    },
    {
        "query_disabled_skip_initial",
        EnabledComponents_query_disabled_skip_initial
    },
    {
        "query_mod_2",
        EnabledComponents_query_mod_2
    },
    {
        "query_mod_8",
        EnabledComponents_query_mod_8
    },
    {
        "query_mod_64",
        EnabledComponents_query_mod_64
    },
    {
        "query_mod_256",
        EnabledComponents_query_mod_256
    },
    {
        "query_mod_1024",
        EnabledComponents_query_mod_1024
    },
    {
        "query_enable_mod_10",
        EnabledComponents_query_enable_mod_10
    },
    {
        "query_mod_2_2_bitsets",
        EnabledComponents_query_mod_2_2_bitsets
    },
    {
        "query_mod_8_2_bitsets",
        EnabledComponents_query_mod_8_2_bitsets
    },
    {
        "query_mod_64_2_bitsets",
        EnabledComponents_query_mod_64_2_bitsets
    },
    {
        "query_mod_256_2_bitsets",
        EnabledComponents_query_mod_256_2_bitsets
    },
    {
        "query_mod_1024_2_bitsets",
        EnabledComponents_query_mod_1024_2_bitsets
    },
    {
        "query_randomized_2_bitsets",
        EnabledComponents_query_randomized_2_bitsets
    },
    {
        "query_randomized_3_bitsets",
        EnabledComponents_query_randomized_3_bitsets
    },
    {
        "query_randomized_4_bitsets",
        EnabledComponents_query_randomized_4_bitsets
    },
    {
        "defer_enable",
        EnabledComponents_defer_enable
    },
    {
        "sort",
        EnabledComponents_sort
    }
};

bake_test_case Remove_testcases[] = {
    {
        "zero",
        Remove_zero
    },
    {
        "zero_from_nonzero",
        Remove_zero_from_nonzero
    },
    {
        "1_of_1",
        Remove_1_of_1
    },
    {
        "1_of_1_again",
        Remove_1_of_1_again
    },
    {
        "1_of_2",
        Remove_1_of_2
    },
    {
        "2_of_2",
        Remove_2_of_2
    },
    {
        "2_of_3",
        Remove_2_of_3
    },
    {
        "2_again",
        Remove_2_again
    },
    {
        "2_overlap",
        Remove_2_overlap
    },
    {
        "type_of_1_of_2",
        Remove_type_of_1_of_2
    },
    {
        "type_of_2_of_2",
        Remove_type_of_2_of_2
    },
    {
        "type_of_2_of_3",
        Remove_type_of_2_of_3
    },
    {
        "1_from_empty",
        Remove_1_from_empty
    },
    {
        "type_from_empty",
        Remove_type_from_empty
    },
    {
        "not_added",
        Remove_not_added
    }
};

bake_test_case Parser_testcases[] = {
    {
        "resolve_this",
        Parser_resolve_this
    },
    {
        "resolve_wildcard",
        Parser_resolve_wildcard
    },
    {
        "resolve_is_a",
        Parser_resolve_is_a
    },
    {
        "0",
        Parser_0
    },
    {
        "component_implicit_subject",
        Parser_component_implicit_subject
    },
    {
        "component_explicit_subject",
        Parser_component_explicit_subject
    },
    {
        "component_explicit_subject_this",
        Parser_component_explicit_subject_this
    },
    {
        "component_explicit_subject_this_by_name",
        Parser_component_explicit_subject_this_by_name
    },
    {
        "component_explicit_subject_wildcard",
        Parser_component_explicit_subject_wildcard
    },
    {
        "pair_implicit_subject",
        Parser_pair_implicit_subject
    },
    {
        "pair_implicit_subject_wildcard_pred",
        Parser_pair_implicit_subject_wildcard_pred
    },
    {
        "pair_implicit_subject_wildcard_obj",
        Parser_pair_implicit_subject_wildcard_obj
    },
    {
        "pair_implicit_subject_this_pred",
        Parser_pair_implicit_subject_this_pred
    },
    {
        "pair_implicit_subject_this_obj",
        Parser_pair_implicit_subject_this_obj
    },
    {
        "pair_explicit_subject",
        Parser_pair_explicit_subject
    },
    {
        "pair_explicit_subject_this",
        Parser_pair_explicit_subject_this
    },
    {
        "pair_explicit_subject_this_by_name",
        Parser_pair_explicit_subject_this_by_name
    },
    {
        "pair_explicit_subject_wildcard_pred",
        Parser_pair_explicit_subject_wildcard_pred
    },
    {
        "pair_explicit_subject_wildcard_subj",
        Parser_pair_explicit_subject_wildcard_subj
    },
    {
        "pair_explicit_subject_wildcard_obj",
        Parser_pair_explicit_subject_wildcard_obj
    },
    {
        "in_component_implicit_subject",
        Parser_in_component_implicit_subject
    },
    {
        "in_component_explicit_subject",
        Parser_in_component_explicit_subject
    },
    {
        "in_pair_implicit_subject",
        Parser_in_pair_implicit_subject
    },
    {
        "in_pair_explicit_subject",
        Parser_in_pair_explicit_subject
    },
    {
        "inout_component_implicit_subject",
        Parser_inout_component_implicit_subject
    },
    {
        "inout_component_explicit_subject",
        Parser_inout_component_explicit_subject
    },
    {
        "inout_pair_implicit_subject",
        Parser_inout_pair_implicit_subject
    },
    {
        "inout_pair_explicit_subject",
        Parser_inout_pair_explicit_subject
    },
    {
        "out_component_implicit_subject",
        Parser_out_component_implicit_subject
    },
    {
        "out_component_explicit_subject",
        Parser_out_component_explicit_subject
    },
    {
        "out_pair_implicit_subject",
        Parser_out_pair_implicit_subject
    },
    {
        "out_pair_explicit_subject",
        Parser_out_pair_explicit_subject
    },
    {
        "component_singleton",
        Parser_component_singleton
    },
    {
        "this_singleton",
        Parser_this_singleton
    },
    {
        "component_implicit_no_subject",
        Parser_component_implicit_no_subject
    },
    {
        "component_explicit_no_subject",
        Parser_component_explicit_no_subject
    },
    {
        "pair_no_subject",
        Parser_pair_no_subject
    },
    {
        "variable_single_char",
        Parser_variable_single_char
    },
    {
        "variable_multi_char",
        Parser_variable_multi_char
    },
    {
        "variable_multi_char_w_underscore",
        Parser_variable_multi_char_w_underscore
    },
    {
        "variable_multi_char_w_number",
        Parser_variable_multi_char_w_number
    },
    {
        "escaped_all_caps_single_char",
        Parser_escaped_all_caps_single_char
    },
    {
        "escaped_all_caps_multi_char",
        Parser_escaped_all_caps_multi_char
    },
    {
        "component_not",
        Parser_component_not
    },
    {
        "pair_implicit_subject_not",
        Parser_pair_implicit_subject_not
    },
    {
        "pair_explicit_subject_not",
        Parser_pair_explicit_subject_not
    },
    {
        "2_component_not",
        Parser_2_component_not
    },
    {
        "2_component_not_no_space",
        Parser_2_component_not_no_space
    },
    {
        "component_optional",
        Parser_component_optional
    },
    {
        "2_component_optional",
        Parser_2_component_optional
    },
    {
        "2_component_optional_no_space",
        Parser_2_component_optional_no_space
    },
    {
        "from_and",
        Parser_from_and
    },
    {
        "from_or",
        Parser_from_or
    },
    {
        "from_not",
        Parser_from_not
    },
    {
        "pair_implicit_subject_optional",
        Parser_pair_implicit_subject_optional
    },
    {
        "pair_explicit_subject_optional",
        Parser_pair_explicit_subject_optional
    },
    {
        "pred_implicit_subject_w_role",
        Parser_pred_implicit_subject_w_role
    },
    {
        "pred_explicit_subject_w_role",
        Parser_pred_explicit_subject_w_role
    },
    {
        "pred_no_subject_w_role",
        Parser_pred_no_subject_w_role
    },
    {
        "pair_implicit_subject_w_role",
        Parser_pair_implicit_subject_w_role
    },
    {
        "pair_explicit_subject_w_role",
        Parser_pair_explicit_subject_w_role
    },
    {
        "inout_role_pred_implicit_subject",
        Parser_inout_role_pred_implicit_subject
    },
    {
        "inout_role_pred_no_subject",
        Parser_inout_role_pred_no_subject
    },
    {
        "inout_role_pred_explicit_subject",
        Parser_inout_role_pred_explicit_subject
    },
    {
        "inout_role_pair_implicit_subject",
        Parser_inout_role_pair_implicit_subject
    },
    {
        "inout_role_pair_explicit_subject",
        Parser_inout_role_pair_explicit_subject
    },
    {
        "2_pred_implicit_subject",
        Parser_2_pred_implicit_subject
    },
    {
        "2_pred_no_subject",
        Parser_2_pred_no_subject
    },
    {
        "2_pred_explicit_subject",
        Parser_2_pred_explicit_subject
    },
    {
        "2_pair_implicit_subject",
        Parser_2_pair_implicit_subject
    },
    {
        "2_pair_explicit_subject",
        Parser_2_pair_explicit_subject
    },
    {
        "2_pred_role",
        Parser_2_pred_role
    },
    {
        "2_pair_implicit_subj_role",
        Parser_2_pair_implicit_subj_role
    },
    {
        "2_pair_explicit_subj_role",
        Parser_2_pair_explicit_subj_role
    },
    {
        "2_or_pred_implicit_subj",
        Parser_2_or_pred_implicit_subj
    },
    {
        "2_or_pred_explicit_subj",
        Parser_2_or_pred_explicit_subj
    },
    {
        "2_or_pair_implicit_subj",
        Parser_2_or_pair_implicit_subj
    },
    {
        "2_or_pair_explicit_subj",
        Parser_2_or_pair_explicit_subj
    },
    {
        "2_or_pred_inout",
        Parser_2_or_pred_inout
    },
    {
        "1_digit_pred_implicit_subj",
        Parser_1_digit_pred_implicit_subj
    },
    {
        "1_digit_pred_no_subj",
        Parser_1_digit_pred_no_subj
    },
    {
        "1_digit_pred_explicit_subj",
        Parser_1_digit_pred_explicit_subj
    },
    {
        "1_digit_pair_implicit_subj",
        Parser_1_digit_pair_implicit_subj
    },
    {
        "1_digit_pair_explicit_subj",
        Parser_1_digit_pair_explicit_subj
    },
    {
        "pred_implicit_subject_self",
        Parser_pred_implicit_subject_self
    },
    {
        "pred_implicit_subject_superset",
        Parser_pred_implicit_subject_superset
    },
    {
        "pred_implicit_subject_subset",
        Parser_pred_implicit_subject_subset
    },
    {
        "pred_implicit_subject_superset_inclusive",
        Parser_pred_implicit_subject_superset_inclusive
    },
    {
        "pred_implicit_subject_subset_inclusive",
        Parser_pred_implicit_subject_subset_inclusive
    },
    {
        "pred_implicit_subject_superset_cascade",
        Parser_pred_implicit_subject_superset_cascade
    },
    {
        "pred_implicit_subject_subset_cascade",
        Parser_pred_implicit_subject_subset_cascade
    },
    {
        "pred_implicit_subject_superset_inclusive_cascade",
        Parser_pred_implicit_subject_superset_inclusive_cascade
    },
    {
        "pred_implicit_subject_subset_inclusive_cascade",
        Parser_pred_implicit_subject_subset_inclusive_cascade
    },
    {
        "pred_implicit_subject_implicit_superset_cascade",
        Parser_pred_implicit_subject_implicit_superset_cascade
    },
    {
        "pred_implicit_subject_implicit_superset_inclusive_cascade",
        Parser_pred_implicit_subject_implicit_superset_inclusive_cascade
    },
    {
        "pred_implicit_subject_implicit_superset_cascade_w_rel",
        Parser_pred_implicit_subject_implicit_superset_cascade_w_rel
    },
    {
        "pred_implicit_subject_implicit_superset_inclusive_cascade_w_rel",
        Parser_pred_implicit_subject_implicit_superset_inclusive_cascade_w_rel
    },
    {
        "pred_implicit_subject_superset_depth_1_digit",
        Parser_pred_implicit_subject_superset_depth_1_digit
    },
    {
        "pred_implicit_subject_subset_depth_1_digit",
        Parser_pred_implicit_subject_subset_depth_1_digit
    },
    {
        "pred_implicit_subject_superset_depth_2_digits",
        Parser_pred_implicit_subject_superset_depth_2_digits
    },
    {
        "pred_implicit_subject_subset_depth_2_digits",
        Parser_pred_implicit_subject_subset_depth_2_digits
    },
    {
        "pred_implicit_superset_min_max_depth",
        Parser_pred_implicit_superset_min_max_depth
    },
    {
        "pred_implicit_superset_childof_min_max_depth",
        Parser_pred_implicit_superset_childof_min_max_depth
    },
    {
        "pred_implicit_subject_superset_childof",
        Parser_pred_implicit_subject_superset_childof
    },
    {
        "pred_implicit_subject_cascade_superset_childof",
        Parser_pred_implicit_subject_cascade_superset_childof
    },
    {
        "pred_implicit_subject_superset_cascade_childof",
        Parser_pred_implicit_subject_superset_cascade_childof
    },
    {
        "pred_implicit_subject_superset_cascade_childof_optional",
        Parser_pred_implicit_subject_superset_cascade_childof_optional
    }
};

bake_test_case GlobalComponentIds_testcases[] = {
    {
        "declare",
        GlobalComponentIds_declare
    },
    {
        "declare_w_entity",
        GlobalComponentIds_declare_w_entity
    },
    {
        "declare_2_world",
        GlobalComponentIds_declare_2_world
    },
    {
        "declare_tag",
        GlobalComponentIds_declare_tag
    },
    {
        "declare_tag_w_entity",
        GlobalComponentIds_declare_tag_w_entity
    },
    {
        "declare_entity",
        GlobalComponentIds_declare_entity
    },
    {
        "declare_type",
        GlobalComponentIds_declare_type
    }
};

bake_test_case Hierarchies_testcases[] = {
    {
        "empty_scope",
        Hierarchies_empty_scope
    },
    {
        "get_parent",
        Hierarchies_get_parent
    },
    {
        "get_parent_from_nested",
        Hierarchies_get_parent_from_nested
    },
    {
        "get_parent_from_nested_2",
        Hierarchies_get_parent_from_nested_2
    },
    {
        "get_parent_from_root",
        Hierarchies_get_parent_from_root
    },
    {
        "tree_iter_empty",
        Hierarchies_tree_iter_empty
    },
    {
        "tree_iter_1_table",
        Hierarchies_tree_iter_1_table
    },
    {
        "tree_iter_2_tables",
        Hierarchies_tree_iter_2_tables
    },
    {
        "tree_iter_w_filter",
        Hierarchies_tree_iter_w_filter
    },
    {
        "path_depth_0",
        Hierarchies_path_depth_0
    },
    {
        "path_depth_1",
        Hierarchies_path_depth_1
    },
    {
        "path_depth_2",
        Hierarchies_path_depth_2
    },
    {
        "rel_path_from_root",
        Hierarchies_rel_path_from_root
    },
    {
        "rel_path_from_self",
        Hierarchies_rel_path_from_self
    },
    {
        "rel_path_depth_1",
        Hierarchies_rel_path_depth_1
    },
    {
        "rel_path_depth_2",
        Hierarchies_rel_path_depth_2
    },
    {
        "rel_path_no_match",
        Hierarchies_rel_path_no_match
    },
    {
        "path_for_component_0",
        Hierarchies_path_for_component_0
    },
    {
        "path_for_component_1",
        Hierarchies_path_for_component_1
    },
    {
        "path_for_component_2",
        Hierarchies_path_for_component_2
    },
    {
        "path_custom_sep",
        Hierarchies_path_custom_sep
    },
    {
        "path_custom_prefix",
        Hierarchies_path_custom_prefix
    },
    {
        "path_prefix_rel_match",
        Hierarchies_path_prefix_rel_match
    },
    {
        "path_prefix_rel_no_match",
        Hierarchies_path_prefix_rel_no_match
    },
    {
        "fullpath_for_core",
        Hierarchies_fullpath_for_core
    },
    {
        "path_w_number",
        Hierarchies_path_w_number
    },
    {
        "lookup_depth_0",
        Hierarchies_lookup_depth_0
    },
    {
        "lookup_depth_1",
        Hierarchies_lookup_depth_1
    },
    {
        "lookup_depth_2",
        Hierarchies_lookup_depth_2
    },
    {
        "lookup_rel_0",
        Hierarchies_lookup_rel_0
    },
    {
        "lookup_rel_1",
        Hierarchies_lookup_rel_1
    },
    {
        "lookup_rel_2",
        Hierarchies_lookup_rel_2
    },
    {
        "lookup_custom_sep",
        Hierarchies_lookup_custom_sep
    },
    {
        "lookup_custom_prefix",
        Hierarchies_lookup_custom_prefix
    },
    {
        "lookup_custom_prefix_from_root",
        Hierarchies_lookup_custom_prefix_from_root
    },
    {
        "lookup_self",
        Hierarchies_lookup_self
    },
    {
        "lookup_in_parent_from_scope",
        Hierarchies_lookup_in_parent_from_scope
    },
    {
        "lookup_in_root_from_scope",
        Hierarchies_lookup_in_root_from_scope
    },
    {
        "lookup_number",
        Hierarchies_lookup_number
    },
    {
        "delete_children",
        Hierarchies_delete_children
    },
    {
        "scope_set",
        Hierarchies_scope_set
    },
    {
        "scope_set_again",
        Hierarchies_scope_set_again
    },
    {
        "scope_set_w_new",
        Hierarchies_scope_set_w_new
    },
    {
        "scope_set_w_new_staged",
        Hierarchies_scope_set_w_new_staged
    },
    {
        "scope_set_w_lookup",
        Hierarchies_scope_set_w_lookup
    },
    {
        "scope_component",
        Hierarchies_scope_component
    },
    {
        "scope_component_no_macro",
        Hierarchies_scope_component_no_macro
    },
    {
        "new_from_path_depth_0",
        Hierarchies_new_from_path_depth_0
    },
    {
        "new_from_path_depth_1",
        Hierarchies_new_from_path_depth_1
    },
    {
        "new_from_path_depth_2",
        Hierarchies_new_from_path_depth_2
    },
    {
        "new_from_path_existing_depth_0",
        Hierarchies_new_from_path_existing_depth_0
    },
    {
        "new_from_path_existing_depth_1",
        Hierarchies_new_from_path_existing_depth_1
    },
    {
        "new_from_path_existing_depth_2",
        Hierarchies_new_from_path_existing_depth_2
    },
    {
        "add_path_depth_0",
        Hierarchies_add_path_depth_0
    },
    {
        "add_path_depth_1",
        Hierarchies_add_path_depth_1
    },
    {
        "add_path_depth_2",
        Hierarchies_add_path_depth_2
    },
    {
        "add_path_existing_depth_0",
        Hierarchies_add_path_existing_depth_0
    },
    {
        "add_path_existing_depth_1",
        Hierarchies_add_path_existing_depth_1
    },
    {
        "add_path_existing_depth_2",
        Hierarchies_add_path_existing_depth_2
    },
    {
        "add_path_from_scope",
        Hierarchies_add_path_from_scope
    },
    {
        "add_path_from_scope_new_entity",
        Hierarchies_add_path_from_scope_new_entity
    },
    {
        "new_w_child_in_root",
        Hierarchies_new_w_child_in_root
    },
    {
        "delete_child",
        Hierarchies_delete_child
    },
    {
        "delete_2_children",
        Hierarchies_delete_2_children
    },
    {
        "delete_2_children_different_type",
        Hierarchies_delete_2_children_different_type
    },
    {
        "delete_tree_2_levels",
        Hierarchies_delete_tree_2_levels
    },
    {
        "delete_tree_3_levels",
        Hierarchies_delete_tree_3_levels
    },
    {
        "delete_tree_count_tables",
        Hierarchies_delete_tree_count_tables
    },
    {
        "delete_tree_staged",
        Hierarchies_delete_tree_staged
    },
    {
        "delete_tree_empty_table",
        Hierarchies_delete_tree_empty_table
    },
    {
        "delete_tree_recreate",
        Hierarchies_delete_tree_recreate
    },
    {
        "delete_tree_w_onremove",
        Hierarchies_delete_tree_w_onremove
    },
    {
        "delete_tree_w_dtor",
        Hierarchies_delete_tree_w_dtor
    },
    {
        "get_child_count",
        Hierarchies_get_child_count
    },
    {
        "get_child_count_2_tables",
        Hierarchies_get_child_count_2_tables
    },
    {
        "get_child_count_no_children",
        Hierarchies_get_child_count_no_children
    },
    {
        "scope_iter_after_delete_tree",
        Hierarchies_scope_iter_after_delete_tree
    },
    {
        "add_child_after_delete_tree",
        Hierarchies_add_child_after_delete_tree
    },
    {
        "add_child_to_recycled_parent",
        Hierarchies_add_child_to_recycled_parent
    },
    {
        "get_type_after_recycled_parent_add",
        Hierarchies_get_type_after_recycled_parent_add
    },
    {
        "rematch_after_add_to_recycled_parent",
        Hierarchies_rematch_after_add_to_recycled_parent
    },
    {
        "cascade_after_recycled_parent_change",
        Hierarchies_cascade_after_recycled_parent_change
    },
    {
        "long_name_depth_0",
        Hierarchies_long_name_depth_0
    },
    {
        "long_name_depth_1",
        Hierarchies_long_name_depth_1
    },
    {
        "long_name_depth_2",
        Hierarchies_long_name_depth_2
    }
};

bake_test_case Add_bulk_testcases[] = {
    {
        "add_comp_from_comp_to_empty",
        Add_bulk_add_comp_from_comp_to_empty
    },
    {
        "add_comp_from_comp_to_existing",
        Add_bulk_add_comp_from_comp_to_existing
    },
    {
        "add_comp_from_tag_to_empty",
        Add_bulk_add_comp_from_tag_to_empty
    },
    {
        "add_comp_from_tag_to_existing",
        Add_bulk_add_comp_from_tag_to_existing
    },
    {
        "add_tag_from_tag_to_empty",
        Add_bulk_add_tag_from_tag_to_empty
    },
    {
        "add_tag_from_tag_to_existing",
        Add_bulk_add_tag_from_tag_to_existing
    },
    {
        "add_comp_to_more_existing",
        Add_bulk_add_comp_to_more_existing
    },
    {
        "add_comp_to_fewer_existing",
        Add_bulk_add_comp_to_fewer_existing
    },
    {
        "on_add",
        Add_bulk_on_add
    },
    {
        "add_entity_comp",
        Add_bulk_add_entity_comp
    },
    {
        "add_entity_tag",
        Add_bulk_add_entity_tag
    },
    {
        "add_entity_on_add",
        Add_bulk_add_entity_on_add
    },
    {
        "add_entity_existing",
        Add_bulk_add_entity_existing
    }
};

bake_test_case Remove_bulk_testcases[] = {
    {
        "remove_comp_from_comp_to_empty",
        Remove_bulk_remove_comp_from_comp_to_empty
    },
    {
        "remove_comp_from_comp_to_existing",
        Remove_bulk_remove_comp_from_comp_to_existing
    },
    {
        "remove_comp_from_tag_to_empty",
        Remove_bulk_remove_comp_from_tag_to_empty
    },
    {
        "remove_comp_from_tag_to_existing",
        Remove_bulk_remove_comp_from_tag_to_existing
    },
    {
        "remove_tag_from_tag_to_empty",
        Remove_bulk_remove_tag_from_tag_to_empty
    },
    {
        "remove_tag_from_tag_to_existing",
        Remove_bulk_remove_tag_from_tag_to_existing
    },
    {
        "remove_all_comp",
        Remove_bulk_remove_all_comp
    },
    {
        "remove_all_tag",
        Remove_bulk_remove_all_tag
    },
    {
        "on_remove",
        Remove_bulk_on_remove
    },
    {
        "remove_entity_comp",
        Remove_bulk_remove_entity_comp
    },
    {
        "remove_entity_tag",
        Remove_bulk_remove_entity_tag
    },
    {
        "remove_entity_on_remove",
        Remove_bulk_remove_entity_on_remove
    }
};

bake_test_case Add_remove_bulk_testcases[] = {
    {
        "add_remove_add_only",
        Add_remove_bulk_add_remove_add_only
    },
    {
        "add_remove_remove_only",
        Add_remove_bulk_add_remove_remove_only
    },
    {
        "add_remove_both",
        Add_remove_bulk_add_remove_both
    },
    {
        "add_remove_same",
        Add_remove_bulk_add_remove_same
    }
};

bake_test_case Has_testcases[] = {
    {
        "zero",
        Has_zero
    },
    {
        "zero_from_nonzero",
        Has_zero_from_nonzero
    },
    {
        "1_of_0",
        Has_1_of_0
    },
    {
        "1_of_1",
        Has_1_of_1
    },
    {
        "1_of_2",
        Has_1_of_2
    },
    {
        "2_of_0",
        Has_2_of_0
    },
    {
        "2_of_2",
        Has_2_of_2
    },
    {
        "3_of_2",
        Has_3_of_2
    },
    {
        "2_of_1",
        Has_2_of_1
    },
    {
        "1_of_empty",
        Has_1_of_empty
    },
    {
        "has_in_progress",
        Has_has_in_progress
    },
    {
        "has_of_zero",
        Has_has_of_zero
    },
    {
        "owns",
        Has_owns
    },
    {
        "has_entity",
        Has_has_entity
    },
    {
        "has_entity_0",
        Has_has_entity_0
    },
    {
        "has_entity_0_component",
        Has_has_entity_0_component
    },
    {
        "has_entity_owned",
        Has_has_entity_owned
    },
    {
        "has_entity_owned_0",
        Has_has_entity_owned_0
    },
    {
        "has_entity_owned_0_component",
        Has_has_entity_owned_0_component
    },
    {
        "has_wildcard",
        Has_has_wildcard
    },
    {
        "has_wildcard_pair",
        Has_has_wildcard_pair
    }
};

bake_test_case Count_testcases[] = {
    {
        "count_empty",
        Count_count_empty
    },
    {
        "count_w_entity_0",
        Count_count_w_entity_0
    },
    {
        "count_1_component",
        Count_count_1_component
    },
    {
        "count_2_components",
        Count_count_2_components
    },
    {
        "count_3_components",
        Count_count_3_components
    },
    {
        "count_2_types_2_comps",
        Count_count_2_types_2_comps
    }
};

bake_test_case Get_component_testcases[] = {
    {
        "get_empty",
        Get_component_get_empty
    },
    {
        "get_1_from_1",
        Get_component_get_1_from_1
    },
    {
        "get_1_from_2",
        Get_component_get_1_from_2
    },
    {
        "get_2_from_2",
        Get_component_get_2_from_2
    },
    {
        "get_2_from_3",
        Get_component_get_2_from_3
    },
    {
        "get_1_from_2_in_progress_from_main_stage",
        Get_component_get_1_from_2_in_progress_from_main_stage
    },
    {
        "get_1_from_2_add_in_progress",
        Get_component_get_1_from_2_add_in_progress
    },
    {
        "get_both_from_2_add_in_progress",
        Get_component_get_both_from_2_add_in_progress
    },
    {
        "get_both_from_2_add_remove_in_progress",
        Get_component_get_both_from_2_add_remove_in_progress
    },
    {
        "get_childof_component",
        Get_component_get_childof_component
    }
};

bake_test_case Reference_testcases[] = {
    {
        "get_ref",
        Reference_get_ref
    },
    {
        "get_ref_after_add",
        Reference_get_ref_after_add
    },
    {
        "get_ref_after_remove",
        Reference_get_ref_after_remove
    },
    {
        "get_ref_after_delete",
        Reference_get_ref_after_delete
    },
    {
        "get_ref_after_realloc",
        Reference_get_ref_after_realloc
    },
    {
        "get_ref_after_realloc_w_lifecycle",
        Reference_get_ref_after_realloc_w_lifecycle
    },
    {
        "get_ref_staged",
        Reference_get_ref_staged
    },
    {
        "get_ref_after_new_in_stage",
        Reference_get_ref_after_new_in_stage
    },
    {
        "get_ref_monitored",
        Reference_get_ref_monitored
    },
    {
        "get_nonexisting",
        Reference_get_nonexisting
    }
};

bake_test_case Delete_testcases[] = {
    {
        "delete_1",
        Delete_delete_1
    },
    {
        "delete_1_again",
        Delete_delete_1_again
    },
    {
        "delete_empty",
        Delete_delete_empty
    },
    {
        "delete_nonexist",
        Delete_delete_nonexist
    },
    {
        "delete_1st_of_3",
        Delete_delete_1st_of_3
    },
    {
        "delete_2nd_of_3",
        Delete_delete_2nd_of_3
    },
    {
        "delete_2_of_3",
        Delete_delete_2_of_3
    },
    {
        "delete_3_of_3",
        Delete_delete_3_of_3
    },
    {
        "delete_w_on_remove",
        Delete_delete_w_on_remove
    },
    {
        "clear_1_component",
        Delete_clear_1_component
    },
    {
        "clear_2_components",
        Delete_clear_2_components
    },
    {
        "alive_after_delete",
        Delete_alive_after_delete
    },
    {
        "alive_after_clear",
        Delete_alive_after_clear
    },
    {
        "alive_after_staged_delete",
        Delete_alive_after_staged_delete
    },
    {
        "alive_while_staged",
        Delete_alive_while_staged
    },
    {
        "alive_while_staged_w_delete",
        Delete_alive_while_staged_w_delete
    },
    {
        "alive_while_staged_w_delete_recycled_id",
        Delete_alive_while_staged_w_delete_recycled_id
    },
    {
        "alive_after_recycle",
        Delete_alive_after_recycle
    },
    {
        "delete_recycled",
        Delete_delete_recycled
    },
    {
        "get_alive_for_alive",
        Delete_get_alive_for_alive
    },
    {
        "get_alive_for_recycled",
        Delete_get_alive_for_recycled
    },
    {
        "get_alive_for_not_alive",
        Delete_get_alive_for_not_alive
    },
    {
        "get_alive_w_generation_for_recycled_alive",
        Delete_get_alive_w_generation_for_recycled_alive
    },
    {
        "get_alive_w_generation_for_recycled_not_alive",
        Delete_get_alive_w_generation_for_recycled_not_alive
    },
    {
        "get_alive_for_0",
        Delete_get_alive_for_0
    },
    {
        "get_alive_for_nonexistent",
        Delete_get_alive_for_nonexistent
    }
};

bake_test_case OnDelete_testcases[] = {
    {
        "on_delete_id_default",
        OnDelete_on_delete_id_default
    },
    {
        "on_delete_id_remove",
        OnDelete_on_delete_id_remove
    },
    {
        "on_delete_id_delete",
        OnDelete_on_delete_id_delete
    },
    {
        "on_delete_relation_default",
        OnDelete_on_delete_relation_default
    },
    {
        "on_delete_relation_remove",
        OnDelete_on_delete_relation_remove
    },
    {
        "on_delete_relation_delete",
        OnDelete_on_delete_relation_delete
    },
    {
        "on_delete_object_default",
        OnDelete_on_delete_object_default
    },
    {
        "on_delete_object_remove",
        OnDelete_on_delete_object_remove
    },
    {
        "on_delete_object_delete",
        OnDelete_on_delete_object_delete
    },
    {
        "on_delete_id_throw",
        OnDelete_on_delete_id_throw
    },
    {
        "on_delete_relation_throw",
        OnDelete_on_delete_relation_throw
    },
    {
        "on_delete_object_throw",
        OnDelete_on_delete_object_throw
    },
    {
        "on_delete_id_remove_no_instances",
        OnDelete_on_delete_id_remove_no_instances
    },
    {
        "on_delete_id_delete_no_instances",
        OnDelete_on_delete_id_delete_no_instances
    },
    {
        "on_delete_id_throw_no_instances",
        OnDelete_on_delete_id_throw_no_instances
    },
    {
        "on_delete_cyclic_id_default",
        OnDelete_on_delete_cyclic_id_default
    },
    {
        "on_delete_cyclic_id_remove",
        OnDelete_on_delete_cyclic_id_remove
    },
    {
        "on_delete_cyclic_id_remove_both",
        OnDelete_on_delete_cyclic_id_remove_both
    },
    {
        "on_delete_cyclic_id_delete",
        OnDelete_on_delete_cyclic_id_delete
    },
    {
        "on_delete_cyclic_id_delete_both",
        OnDelete_on_delete_cyclic_id_delete_both
    },
    {
        "on_delete_cyclic_relation_default",
        OnDelete_on_delete_cyclic_relation_default
    },
    {
        "on_delete_cyclic_relation_remove",
        OnDelete_on_delete_cyclic_relation_remove
    },
    {
        "on_delete_cyclic_relation_remove_both",
        OnDelete_on_delete_cyclic_relation_remove_both
    },
    {
        "on_delete_cyclic_relation_delete",
        OnDelete_on_delete_cyclic_relation_delete
    },
    {
        "on_delete_cyclic_object_default",
        OnDelete_on_delete_cyclic_object_default
    },
    {
        "on_delete_cyclic_object_remove",
        OnDelete_on_delete_cyclic_object_remove
    },
    {
        "on_delete_cyclic_object_delete",
        OnDelete_on_delete_cyclic_object_delete
    },
    {
        "on_delete_remove_2_comps",
        OnDelete_on_delete_remove_2_comps
    },
    {
        "on_delete_remove_2_comps_to_existing_table",
        OnDelete_on_delete_remove_2_comps_to_existing_table
    },
    {
        "on_delete_delete_recursive",
        OnDelete_on_delete_delete_recursive
    },
    {
        "on_delete_component_throw",
        OnDelete_on_delete_component_throw
    },
    {
        "on_delete_remove_2_relations",
        OnDelete_on_delete_remove_2_relations
    },
    {
        "on_delete_remove_object_w_2_relations",
        OnDelete_on_delete_remove_object_w_2_relations
    },
    {
        "remove_id_from_2_tables",
        OnDelete_remove_id_from_2_tables
    },
    {
        "remove_relation_from_2_tables",
        OnDelete_remove_relation_from_2_tables
    },
    {
        "remove_object_from_2_tables",
        OnDelete_remove_object_from_2_tables
    },
    {
        "remove_id_and_relation",
        OnDelete_remove_id_and_relation
    },
    {
        "remove_id_and_relation_from_2_tables",
        OnDelete_remove_id_and_relation_from_2_tables
    },
    {
        "stresstest_many_objects",
        OnDelete_stresstest_many_objects
    },
    {
        "stresstest_many_relations",
        OnDelete_stresstest_many_relations
    },
    {
        "stresstest_many_objects_on_delete",
        OnDelete_stresstest_many_objects_on_delete
    },
    {
        "stresstest_many_relations_on_delete",
        OnDelete_stresstest_many_relations_on_delete
    },
    {
        "on_delete_empty_table_w_on_remove",
        OnDelete_on_delete_empty_table_w_on_remove
    },
    {
        "delete_table_in_on_remove_during_fini",
        OnDelete_delete_table_in_on_remove_during_fini
    },
    {
        "delete_other_in_on_remove_during_fini",
        OnDelete_delete_other_in_on_remove_during_fini
    }
};

bake_test_case Delete_w_filter_testcases[] = {
    {
        "delete_1",
        Delete_w_filter_delete_1
    },
    {
        "delete_2",
        Delete_w_filter_delete_2
    },
    {
        "delete_1_2_types",
        Delete_w_filter_delete_1_2_types
    },
    {
        "delete_2_2_types",
        Delete_w_filter_delete_2_2_types
    },
    {
        "delete_except_1",
        Delete_w_filter_delete_except_1
    },
    {
        "delete_except_2",
        Delete_w_filter_delete_except_2
    },
    {
        "delete_with_any_of_2",
        Delete_w_filter_delete_with_any_of_2
    },
    {
        "delete_except_all_of_2",
        Delete_w_filter_delete_except_all_of_2
    },
    {
        "include_exact",
        Delete_w_filter_include_exact
    },
    {
        "exclude_exact",
        Delete_w_filter_exclude_exact
    },
    {
        "system_activate_test",
        Delete_w_filter_system_activate_test
    },
    {
        "skip_builtin_tables",
        Delete_w_filter_skip_builtin_tables
    },
    {
        "delete_w_on_remove",
        Delete_w_filter_delete_w_on_remove
    }
};

bake_test_case Set_testcases[] = {
    {
        "set_empty",
        Set_set_empty
    },
    {
        "set_nonempty",
        Set_set_nonempty
    },
    {
        "set_non_empty_override",
        Set_set_non_empty_override
    },
    {
        "set_again",
        Set_set_again
    },
    {
        "set_2",
        Set_set_2
    },
    {
        "add_set",
        Set_add_set
    },
    {
        "set_add",
        Set_set_add
    },
    {
        "set_add_other",
        Set_set_add_other
    },
    {
        "set_remove",
        Set_set_remove
    },
    {
        "set_remove_other",
        Set_set_remove_other
    },
    {
        "set_remove_twice",
        Set_set_remove_twice
    },
    {
        "set_and_new",
        Set_set_and_new
    },
    {
        "set_null",
        Set_set_null
    },
    {
        "get_mut_new",
        Set_get_mut_new
    },
    {
        "get_mut_existing",
        Set_get_mut_existing
    },
    {
        "get_mut_tag_new",
        Set_get_mut_tag_new
    },
    {
        "get_mut_tag_existing",
        Set_get_mut_tag_existing
    },
    {
        "get_mut_tag_new_w_comp",
        Set_get_mut_tag_new_w_comp
    },
    {
        "get_mut_tag_existing_w_comp",
        Set_get_mut_tag_existing_w_comp
    },
    {
        "get_mut_tag_new_w_pair",
        Set_get_mut_tag_new_w_pair
    },
    {
        "get_mut_tag_existing_w_pair",
        Set_get_mut_tag_existing_w_pair
    },
    {
        "modified_w_on_set",
        Set_modified_w_on_set
    },
    {
        "modified_no_component",
        Set_modified_no_component
    },
    {
        "get_mut_w_add_in_on_add",
        Set_get_mut_w_add_in_on_add
    },
    {
        "get_mut_w_remove_in_on_add",
        Set_get_mut_w_remove_in_on_add
    },
    {
        "emplace",
        Set_emplace
    },
    {
        "emplace_existing",
        Set_emplace_existing
    }
};

bake_test_case Lookup_testcases[] = {
    {
        "lookup",
        Lookup_lookup
    },
    {
        "lookup_component",
        Lookup_lookup_component
    },
    {
        "lookup_not_found",
        Lookup_lookup_not_found
    },
    {
        "lookup_child",
        Lookup_lookup_child
    },
    {
        "lookup_w_null_name",
        Lookup_lookup_w_null_name
    },
    {
        "get_name",
        Lookup_get_name
    },
    {
        "get_name_no_name",
        Lookup_get_name_no_name
    },
    {
        "get_name_from_empty",
        Lookup_get_name_from_empty
    },
    {
        "lookup_by_id",
        Lookup_lookup_by_id
    },
    {
        "lookup_symbol_by_id",
        Lookup_lookup_symbol_by_id
    },
    {
        "lookup_name_w_digit",
        Lookup_lookup_name_w_digit
    },
    {
        "lookup_symbol_w_digit",
        Lookup_lookup_symbol_w_digit
    },
    {
        "lookup_path_w_digit",
        Lookup_lookup_path_w_digit
    },
    {
        "set_name_of_existing",
        Lookup_set_name_of_existing
    },
    {
        "change_name_of_existing",
        Lookup_change_name_of_existing
    },
    {
        "lookup_alias",
        Lookup_lookup_alias
    },
    {
        "lookup_scoped_alias",
        Lookup_lookup_scoped_alias
    },
    {
        "define_duplicate_alias",
        Lookup_define_duplicate_alias
    },
    {
        "define_alias_in_scope",
        Lookup_define_alias_in_scope
    },
    {
        "lookup_null",
        Lookup_lookup_null
    },
    {
        "lookup_symbol_null",
        Lookup_lookup_symbol_null
    },
    {
        "lookup_this",
        Lookup_lookup_this
    },
    {
        "lookup_wildcard",
        Lookup_lookup_wildcard
    },
    {
        "lookup_path_this",
        Lookup_lookup_path_this
    },
    {
        "lookup_path_wildcard",
        Lookup_lookup_path_wildcard
    },
    {
        "lookup_path_this_from_scope",
        Lookup_lookup_path_this_from_scope
    },
    {
        "lookup_path_wildcard_from_scope",
        Lookup_lookup_path_wildcard_from_scope
    }
};

bake_test_case Singleton_testcases[] = {
    {
        "set",
        Singleton_set
    },
    {
        "set_ptr",
        Singleton_set_ptr
    },
    {
        "system_w_singleton",
        Singleton_system_w_singleton
    },
    {
        "system_w_singleton_no_match",
        Singleton_system_w_singleton_no_match
    },
    {
        "system_w_not_singleton",
        Singleton_system_w_not_singleton
    },
    {
        "lookup_singleton",
        Singleton_lookup_singleton
    },
    {
        "get_singleton_id",
        Singleton_get_singleton_id
    },
    {
        "set_get_singleton",
        Singleton_set_get_singleton
    },
    {
        "get_mut_singleton",
        Singleton_get_mut_singleton
    },
    {
        "singleton_system",
        Singleton_singleton_system
    }
};

bake_test_case Clone_testcases[] = {
    {
        "empty",
        Clone_empty
    },
    {
        "empty_w_value",
        Clone_empty_w_value
    },
    {
        "null",
        Clone_null
    },
    {
        "null_w_value",
        Clone_null_w_value
    },
    {
        "1_component",
        Clone_1_component
    },
    {
        "2_component",
        Clone_2_component
    },
    {
        "1_component_w_value",
        Clone_1_component_w_value
    },
    {
        "2_component_w_value",
        Clone_2_component_w_value
    },
    {
        "3_component",
        Clone_3_component
    },
    {
        "3_component_w_value",
        Clone_3_component_w_value
    },
    {
        "tag",
        Clone_tag
    },
    {
        "tag_w_value",
        Clone_tag_w_value
    },
    {
        "1_tag_1_component",
        Clone_1_tag_1_component
    },
    {
        "1_tag_1_component_w_value",
        Clone_1_tag_1_component_w_value
    }
};

bake_test_case ComponentLifecycle_testcases[] = {
    {
        "ctor_on_add",
        ComponentLifecycle_ctor_on_add
    },
    {
        "ctor_on_new",
        ComponentLifecycle_ctor_on_new
    },
    {
        "dtor_on_remove",
        ComponentLifecycle_dtor_on_remove
    },
    {
        "dtor_on_delete",
        ComponentLifecycle_dtor_on_delete
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
        "copy_on_new_w_data",
        ComponentLifecycle_copy_on_new_w_data
    },
    {
        "copy_on_clone",
        ComponentLifecycle_copy_on_clone
    },
    {
        "no_copy_on_move",
        ComponentLifecycle_no_copy_on_move
    },
    {
        "ctor_on_bulk_add",
        ComponentLifecycle_ctor_on_bulk_add
    },
    {
        "dtor_on_bulk_remove",
        ComponentLifecycle_dtor_on_bulk_remove
    },
    {
        "ctor_on_bulk_add_entity",
        ComponentLifecycle_ctor_on_bulk_add_entity
    },
    {
        "dtor_on_bulk_remove_entity",
        ComponentLifecycle_dtor_on_bulk_remove_entity
    },
    {
        "ctor_dtor_on_bulk_add_remove",
        ComponentLifecycle_ctor_dtor_on_bulk_add_remove
    },
    {
        "ctor_copy_on_snapshot",
        ComponentLifecycle_ctor_copy_on_snapshot
    },
    {
        "copy_on_snapshot",
        ComponentLifecycle_copy_on_snapshot
    },
    {
        "dtor_on_restore",
        ComponentLifecycle_dtor_on_restore
    },
    {
        "ctor_on_tag",
        ComponentLifecycle_ctor_on_tag
    },
    {
        "dtor_on_tag",
        ComponentLifecycle_dtor_on_tag
    },
    {
        "copy_on_tag",
        ComponentLifecycle_copy_on_tag
    },
    {
        "move_on_tag",
        ComponentLifecycle_move_on_tag
    },
    {
        "merge_to_different_table",
        ComponentLifecycle_merge_to_different_table
    },
    {
        "merge_to_new_table",
        ComponentLifecycle_merge_to_new_table
    },
    {
        "delete_in_stage",
        ComponentLifecycle_delete_in_stage
    },
    {
        "ctor_on_add_pair",
        ComponentLifecycle_ctor_on_add_pair
    },
    {
        "ctor_on_add_pair_set_ctor_after_table",
        ComponentLifecycle_ctor_on_add_pair_set_ctor_after_table
    },
    {
        "ctor_on_add_pair_tag",
        ComponentLifecycle_ctor_on_add_pair_tag
    },
    {
        "ctor_on_add_pair_tag_set_ctor_after_table",
        ComponentLifecycle_ctor_on_add_pair_tag_set_ctor_after_table
    },
    {
        "ctor_on_move_pair",
        ComponentLifecycle_ctor_on_move_pair
    },
    {
        "move_on_realloc",
        ComponentLifecycle_move_on_realloc
    },
    {
        "move_on_dim",
        ComponentLifecycle_move_on_dim
    },
    {
        "move_on_bulk_new",
        ComponentLifecycle_move_on_bulk_new
    },
    {
        "move_on_delete",
        ComponentLifecycle_move_on_delete
    },
    {
        "copy_on_override_pair",
        ComponentLifecycle_copy_on_override_pair
    },
    {
        "copy_on_override_pair_tag",
        ComponentLifecycle_copy_on_override_pair_tag
    },
    {
        "copy_on_set_pair",
        ComponentLifecycle_copy_on_set_pair
    },
    {
        "copy_on_set_pair_tag",
        ComponentLifecycle_copy_on_set_pair_tag
    },
    {
        "prevent_lifecycle_overwrite",
        ComponentLifecycle_prevent_lifecycle_overwrite
    },
    {
        "prevent_lifecycle_overwrite_null_callbacks",
        ComponentLifecycle_prevent_lifecycle_overwrite_null_callbacks
    },
    {
        "allow_lifecycle_overwrite_equal_callbacks",
        ComponentLifecycle_allow_lifecycle_overwrite_equal_callbacks
    },
    {
        "set_lifecycle_after_trigger",
        ComponentLifecycle_set_lifecycle_after_trigger
    },
    {
        "valid_entity_in_dtor_after_delete",
        ComponentLifecycle_valid_entity_in_dtor_after_delete
    },
    {
        "ctor_w_emplace",
        ComponentLifecycle_ctor_w_emplace
    },
    {
        "dtor_on_fini",
        ComponentLifecycle_dtor_on_fini
    },
    {
        "valid_type_in_dtor_on_fini",
        ComponentLifecycle_valid_type_in_dtor_on_fini
    },
    {
        "valid_other_type_of_entity_in_dtor_on_fini",
        ComponentLifecycle_valid_other_type_of_entity_in_dtor_on_fini
    },
    {
        "valid_same_type_comp_of_entity_in_dtor_on_fini",
        ComponentLifecycle_valid_same_type_comp_of_entity_in_dtor_on_fini
    },
    {
        "valid_same_type_comp_of_entity_in_dtor_on_delete_parent",
        ComponentLifecycle_valid_same_type_comp_of_entity_in_dtor_on_delete_parent
    },
    {
        "valid_entity_bulk_remove_all_components",
        ComponentLifecycle_valid_entity_bulk_remove_all_components
    },
    {
        "delete_in_dtor_same_type_on_fini",
        ComponentLifecycle_delete_in_dtor_same_type_on_fini
    },
    {
        "delete_in_dtor_other_type_on_fini",
        ComponentLifecycle_delete_in_dtor_other_type_on_fini
    },
    {
        "delete_self_in_dtor_on_fini",
        ComponentLifecycle_delete_self_in_dtor_on_fini
    },
    {
        "delete_in_dtor_same_type_on_delete_parent",
        ComponentLifecycle_delete_in_dtor_same_type_on_delete_parent
    },
    {
        "delete_in_dtor_other_type_on_delete_parent",
        ComponentLifecycle_delete_in_dtor_other_type_on_delete_parent
    },
    {
        "delete_self_in_dtor_on_delete_parent",
        ComponentLifecycle_delete_self_in_dtor_on_delete_parent
    },
    {
        "delete_in_dtor_same_type_on_delete",
        ComponentLifecycle_delete_in_dtor_same_type_on_delete
    },
    {
        "delete_in_dtor_other_type_on_delete",
        ComponentLifecycle_delete_in_dtor_other_type_on_delete
    },
    {
        "delete_self_in_dtor_on_delete",
        ComponentLifecycle_delete_self_in_dtor_on_delete
    }
};

bake_test_case Pipeline_testcases[] = {
    {
        "system_order_same_phase",
        Pipeline_system_order_same_phase
    },
    {
        "system_order_same_phase_after_disable",
        Pipeline_system_order_same_phase_after_disable
    },
    {
        "system_order_same_phase_after_activate",
        Pipeline_system_order_same_phase_after_activate
    },
    {
        "system_order_different_phase",
        Pipeline_system_order_different_phase
    },
    {
        "system_order_different_phase_after_disable",
        Pipeline_system_order_different_phase_after_disable
    },
    {
        "system_order_different_phase_after_activate",
        Pipeline_system_order_different_phase_after_activate
    },
    {
        "system_order_after_new_system_lower_id",
        Pipeline_system_order_after_new_system_lower_id
    },
    {
        "system_order_after_new_system_inbetween_id",
        Pipeline_system_order_after_new_system_inbetween_id
    },
    {
        "system_order_after_new_system_higher_id",
        Pipeline_system_order_after_new_system_higher_id
    },
    {
        "merge_after_staged_out",
        Pipeline_merge_after_staged_out
    },
    {
        "merge_after_not_out",
        Pipeline_merge_after_not_out
    },
    {
        "no_merge_after_main_out",
        Pipeline_no_merge_after_main_out
    },
    {
        "no_merge_after_staged_in_out",
        Pipeline_no_merge_after_staged_in_out
    },
    {
        "merge_after_staged_out_before_owned",
        Pipeline_merge_after_staged_out_before_owned
    },
    {
        "switch_pipeline",
        Pipeline_switch_pipeline
    },
    {
        "run_pipeline",
        Pipeline_run_pipeline
    },
    {
        "get_pipeline_from_stage",
        Pipeline_get_pipeline_from_stage
    },
    {
        "3_systems_3_types",
        Pipeline_3_systems_3_types
    },
    {
        "random_read_after_random_write_out_in",
        Pipeline_random_read_after_random_write_out_in
    },
    {
        "random_read_after_random_write_inout_in",
        Pipeline_random_read_after_random_write_inout_in
    },
    {
        "random_read_after_random_write_out_inout",
        Pipeline_random_read_after_random_write_out_inout
    },
    {
        "random_read_after_random_write_inout_inout",
        Pipeline_random_read_after_random_write_inout_inout
    },
    {
        "random_read_after_random_write_w_not_write",
        Pipeline_random_read_after_random_write_w_not_write
    },
    {
        "random_read_after_random_write_w_not_read",
        Pipeline_random_read_after_random_write_w_not_read
    },
    {
        "random_read_after_random_write_w_wildcard",
        Pipeline_random_read_after_random_write_w_wildcard
    },
    {
        "random_in_after_random_inout_after_random_out",
        Pipeline_random_in_after_random_inout_after_random_out
    }
};

bake_test_case SystemMisc_testcases[] = {
    {
        "invalid_not_without_id",
        SystemMisc_invalid_not_without_id
    },
    {
        "invalid_optional_without_id",
        SystemMisc_invalid_optional_without_id
    },
    {
        "invalid_system_without_id",
        SystemMisc_invalid_system_without_id
    },
    {
        "invalid_container_without_id",
        SystemMisc_invalid_container_without_id
    },
    {
        "invalid_cascade_without_id",
        SystemMisc_invalid_cascade_without_id
    },
    {
        "invalid_entity_without_id",
        SystemMisc_invalid_entity_without_id
    },
    {
        "invalid_empty_without_id",
        SystemMisc_invalid_empty_without_id
    },
    {
        "invalid_singleton_without_id",
        SystemMisc_invalid_singleton_without_id
    },
    {
        "invalid_empty_element",
        SystemMisc_invalid_empty_element
    },
    {
        "invalid_empty_element_w_space",
        SystemMisc_invalid_empty_element_w_space
    },
    {
        "invalid_empty_or",
        SystemMisc_invalid_empty_or
    },
    {
        "invalid_empty_or_w_space",
        SystemMisc_invalid_empty_or_w_space
    },
    {
        "invalid_or_w_not",
        SystemMisc_invalid_or_w_not
    },
    {
        "invalid_not_w_or",
        SystemMisc_invalid_not_w_or
    },
    {
        "invalid_0_w_and",
        SystemMisc_invalid_0_w_and
    },
    {
        "invalid_0_w_from_system",
        SystemMisc_invalid_0_w_from_system
    },
    {
        "invalid_0_w_from_container",
        SystemMisc_invalid_0_w_from_container
    },
    {
        "invalid_0_w_from_cascade",
        SystemMisc_invalid_0_w_from_cascade
    },
    {
        "invalid_0_w_from_entity",
        SystemMisc_invalid_0_w_from_entity
    },
    {
        "invalid_0_w_from_empty",
        SystemMisc_invalid_0_w_from_empty
    },
    {
        "invalid_0_w_from_singleton",
        SystemMisc_invalid_0_w_from_singleton
    },
    {
        "invalid_or_w_empty",
        SystemMisc_invalid_or_w_empty
    },
    {
        "invalid_component_id",
        SystemMisc_invalid_component_id
    },
    {
        "invalid_entity_id",
        SystemMisc_invalid_entity_id
    },
    {
        "invalid_null_string",
        SystemMisc_invalid_null_string
    },
    {
        "invalid_empty_string",
        SystemMisc_invalid_empty_string
    },
    {
        "invalid_empty_string_w_space",
        SystemMisc_invalid_empty_string_w_space
    },
    {
        "invalid_mixed_src_modifier",
        SystemMisc_invalid_mixed_src_modifier
    },
    {
        "redefine_row_system",
        SystemMisc_redefine_row_system
    },
    {
        "system_w_or_prefab",
        SystemMisc_system_w_or_prefab
    },
    {
        "system_w_or_disabled",
        SystemMisc_system_w_or_disabled
    },
    {
        "system_w_or_disabled_and_prefab",
        SystemMisc_system_w_or_disabled_and_prefab
    },
    {
        "table_columns_access",
        SystemMisc_table_columns_access
    },
    {
        "status_enable_after_new",
        SystemMisc_status_enable_after_new
    },
    {
        "status_enable_after_disable",
        SystemMisc_status_enable_after_disable
    },
    {
        "status_disable_after_new",
        SystemMisc_status_disable_after_new
    },
    {
        "status_disable_after_disable",
        SystemMisc_status_disable_after_disable
    },
    {
        "status_activate_after_new",
        SystemMisc_status_activate_after_new
    },
    {
        "status_deactivate_after_delete",
        SystemMisc_status_deactivate_after_delete
    },
    {
        "dont_enable_after_rematch",
        SystemMisc_dont_enable_after_rematch
    },
    {
        "ensure_single_merge",
        SystemMisc_ensure_single_merge
    },
    {
        "table_count",
        SystemMisc_table_count
    },
    {
        "match_system",
        SystemMisc_match_system
    },
    {
        "match_system_w_filter",
        SystemMisc_match_system_w_filter
    },
    {
        "system_initial_state",
        SystemMisc_system_initial_state
    },
    {
        "add_own_component",
        SystemMisc_add_own_component
    },
    {
        "change_system_action",
        SystemMisc_change_system_action
    },
    {
        "system_readeactivate",
        SystemMisc_system_readeactivate
    },
    {
        "system_readeactivate_w_2_systems",
        SystemMisc_system_readeactivate_w_2_systems
    },
    {
        "add_to_system_in_progress",
        SystemMisc_add_to_system_in_progress
    },
    {
        "add_to_lazy_system_in_progress",
        SystemMisc_add_to_lazy_system_in_progress
    },
    {
        "redefine_null_signature",
        SystemMisc_redefine_null_signature
    },
    {
        "redefine_0_signature",
        SystemMisc_redefine_0_signature
    },
    {
        "one_named_column_of_two",
        SystemMisc_one_named_column_of_two
    },
    {
        "two_named_columns_of_two",
        SystemMisc_two_named_columns_of_two
    },
    {
        "get_column_by_name",
        SystemMisc_get_column_by_name
    },
    {
        "get_column_by_name_not_found",
        SystemMisc_get_column_by_name_not_found
    },
    {
        "get_column_by_name_no_names",
        SystemMisc_get_column_by_name_no_names
    },
    {
        "redeclare_system_same_expr",
        SystemMisc_redeclare_system_same_expr
    },
    {
        "redeclare_system_null_expr",
        SystemMisc_redeclare_system_null_expr
    },
    {
        "redeclare_system_0_expr",
        SystemMisc_redeclare_system_0_expr
    },
    {
        "redeclare_system_different_expr",
        SystemMisc_redeclare_system_different_expr
    },
    {
        "redeclare_system_null_and_expr",
        SystemMisc_redeclare_system_null_and_expr
    },
    {
        "redeclare_system_expr_and_null",
        SystemMisc_redeclare_system_expr_and_null
    },
    {
        "redeclare_system_expr_and_0",
        SystemMisc_redeclare_system_expr_and_0
    },
    {
        "redeclare_system_0_and_expr",
        SystemMisc_redeclare_system_0_and_expr
    },
    {
        "redeclare_system_0_and_null",
        SystemMisc_redeclare_system_0_and_null
    },
    {
        "redeclare_system_null_and_0",
        SystemMisc_redeclare_system_null_and_0
    },
    {
        "redeclare_system_explicit_id",
        SystemMisc_redeclare_system_explicit_id
    },
    {
        "redeclare_system_explicit_id_null_expr",
        SystemMisc_redeclare_system_explicit_id_null_expr
    },
    {
        "redeclare_system_explicit_id_no_name",
        SystemMisc_redeclare_system_explicit_id_no_name
    },
    {
        "declare_different_id_same_name",
        SystemMisc_declare_different_id_same_name
    },
    {
        "declare_different_id_same_name_w_scope",
        SystemMisc_declare_different_id_same_name_w_scope
    },
    {
        "rw_in_implicit_any",
        SystemMisc_rw_in_implicit_any
    },
    {
        "rw_in_implicit_shared",
        SystemMisc_rw_in_implicit_shared
    },
    {
        "rw_in_implicit_from_empty",
        SystemMisc_rw_in_implicit_from_empty
    },
    {
        "rw_in_implicit_from_entity",
        SystemMisc_rw_in_implicit_from_entity
    },
    {
        "rw_out_explicit_any",
        SystemMisc_rw_out_explicit_any
    },
    {
        "rw_out_explicit_shared",
        SystemMisc_rw_out_explicit_shared
    },
    {
        "rw_out_explicit_from_empty",
        SystemMisc_rw_out_explicit_from_empty
    },
    {
        "rw_out_explicit_from_entity",
        SystemMisc_rw_out_explicit_from_entity
    },
    {
        "activate_system_for_table_w_n_pairs",
        SystemMisc_activate_system_for_table_w_n_pairs
    },
    {
        "get_query",
        SystemMisc_get_query
    },
    {
        "set_get_context",
        SystemMisc_set_get_context
    },
    {
        "set_get_binding_context",
        SystemMisc_set_get_binding_context
    },
    {
        "deactivate_after_disable",
        SystemMisc_deactivate_after_disable
    },
    {
        "system_w_self",
        SystemMisc_system_w_self
    },
    {
        "delete_system",
        SystemMisc_delete_system
    },
    {
        "delete_pipeline_system",
        SystemMisc_delete_pipeline_system
    },
    {
        "delete_system_w_ctx",
        SystemMisc_delete_system_w_ctx
    }
};

bake_test_case Sorting_testcases[] = {
    {
        "sort_by_component",
        Sorting_sort_by_component
    },
    {
        "sort_by_component_2_tables",
        Sorting_sort_by_component_2_tables
    },
    {
        "sort_by_component_3_tables",
        Sorting_sort_by_component_3_tables
    },
    {
        "sort_by_entity",
        Sorting_sort_by_entity
    },
    {
        "sort_after_add",
        Sorting_sort_after_add
    },
    {
        "sort_after_remove",
        Sorting_sort_after_remove
    },
    {
        "sort_after_delete",
        Sorting_sort_after_delete
    },
    {
        "sort_after_set",
        Sorting_sort_after_set
    },
    {
        "sort_after_system",
        Sorting_sort_after_system
    },
    {
        "sort_after_query",
        Sorting_sort_after_query
    },
    {
        "sort_by_component_same_value_1",
        Sorting_sort_by_component_same_value_1
    },
    {
        "sort_by_component_same_value_2",
        Sorting_sort_by_component_same_value_2
    },
    {
        "sort_by_component_move_pivot",
        Sorting_sort_by_component_move_pivot
    },
    {
        "sort_1000_entities",
        Sorting_sort_1000_entities
    },
    {
        "sort_1000_entities_w_duplicates",
        Sorting_sort_1000_entities_w_duplicates
    },
    {
        "sort_1000_entities_again",
        Sorting_sort_1000_entities_again
    },
    {
        "sort_1000_entities_2_types",
        Sorting_sort_1000_entities_2_types
    },
    {
        "sort_1500_entities_3_types",
        Sorting_sort_1500_entities_3_types
    },
    {
        "sort_2000_entities_4_types",
        Sorting_sort_2000_entities_4_types
    },
    {
        "sort_2_entities_2_types",
        Sorting_sort_2_entities_2_types
    },
    {
        "sort_3_entities_3_types",
        Sorting_sort_3_entities_3_types
    },
    {
        "sort_3_entities_3_types_2",
        Sorting_sort_3_entities_3_types_2
    },
    {
        "sort_4_entities_4_types",
        Sorting_sort_4_entities_4_types
    },
    {
        "sort_1000_entities_2_types_again",
        Sorting_sort_1000_entities_2_types_again
    },
    {
        "sort_1000_entities_add_type_after_sort",
        Sorting_sort_1000_entities_add_type_after_sort
    },
    {
        "sort_shared_component",
        Sorting_sort_shared_component
    },
    {
        "sort_w_tags_only",
        Sorting_sort_w_tags_only
    },
    {
        "sort_childof_marked",
        Sorting_sort_childof_marked
    },
    {
        "sort_isa_marked",
        Sorting_sort_isa_marked
    },
    {
        "sort_relation_marked",
        Sorting_sort_relation_marked
    }
};

bake_test_case Filter_testcases[] = {
    {
        "filter_1_term",
        Filter_filter_1_term
    },
    {
        "filter_2_terms",
        Filter_filter_2_terms
    },
    {
        "filter_3_terms",
        Filter_filter_3_terms
    },
    {
        "filter_3_terms_w_or",
        Filter_filter_3_terms_w_or
    },
    {
        "filter_4_terms_w_or_at_1",
        Filter_filter_4_terms_w_or_at_1
    },
    {
        "filter_w_pair_id",
        Filter_filter_w_pair_id
    },
    {
        "filter_w_pred_obj",
        Filter_filter_w_pred_obj
    },
    {
        "term_w_id",
        Filter_term_w_id
    },
    {
        "term_w_pair_id",
        Filter_term_w_pair_id
    },
    {
        "term_w_pred_obj",
        Filter_term_w_pred_obj
    },
    {
        "term_w_pair_finalize_twice",
        Filter_term_w_pair_finalize_twice
    },
    {
        "term_w_role",
        Filter_term_w_role
    },
    {
        "term_w_pred_role",
        Filter_term_w_pred_role
    }
};

bake_test_case Query_testcases[] = {
    {
        "query_changed_after_new",
        Query_query_changed_after_new
    },
    {
        "query_changed_after_delete",
        Query_query_changed_after_delete
    },
    {
        "query_changed_after_add",
        Query_query_changed_after_add
    },
    {
        "query_changed_after_remove",
        Query_query_changed_after_remove
    },
    {
        "query_changed_after_set",
        Query_query_changed_after_set
    },
    {
        "query_change_after_modified",
        Query_query_change_after_modified
    },
    {
        "query_change_after_out_system",
        Query_query_change_after_out_system
    },
    {
        "query_change_after_in_system",
        Query_query_change_after_in_system
    },
    {
        "subquery_match_existing",
        Query_subquery_match_existing
    },
    {
        "subquery_match_new",
        Query_subquery_match_new
    },
    {
        "subquery_inactive",
        Query_subquery_inactive
    },
    {
        "subquery_unmatch",
        Query_subquery_unmatch
    },
    {
        "subquery_rematch",
        Query_subquery_rematch
    },
    {
        "subquery_rematch_w_parent_optional",
        Query_subquery_rematch_w_parent_optional
    },
    {
        "subquery_rematch_w_sub_optional",
        Query_subquery_rematch_w_sub_optional
    },
    {
        "query_single_pairs",
        Query_query_single_pairs
    },
    {
        "query_single_instanceof",
        Query_query_single_instanceof
    },
    {
        "query_single_childof",
        Query_query_single_childof
    },
    {
        "query_w_filter",
        Query_query_w_filter
    },
    {
        "query_optional_owned",
        Query_query_optional_owned
    },
    {
        "query_optional_shared",
        Query_query_optional_shared
    },
    {
        "query_optional_shared_nested",
        Query_query_optional_shared_nested
    },
    {
        "query_optional_any",
        Query_query_optional_any
    },
    {
        "query_rematch_optional_after_add",
        Query_query_rematch_optional_after_add
    },
    {
        "get_owned_tag",
        Query_get_owned_tag
    },
    {
        "get_shared_tag",
        Query_get_shared_tag
    },
    {
        "explicit_delete",
        Query_explicit_delete
    },
    {
        "get_column_size",
        Query_get_column_size
    },
    {
        "orphaned_query",
        Query_orphaned_query
    },
    {
        "nested_orphaned_query",
        Query_nested_orphaned_query
    },
    {
        "invalid_access_orphaned_query",
        Query_invalid_access_orphaned_query
    },
    {
        "stresstest_query_free",
        Query_stresstest_query_free
    },
    {
        "only_from_entity",
        Query_only_from_entity
    },
    {
        "only_from_singleton",
        Query_only_from_singleton
    },
    {
        "only_not_from_entity",
        Query_only_not_from_entity
    },
    {
        "only_not_from_singleton",
        Query_only_not_from_singleton
    },
    {
        "get_filter",
        Query_get_filter
    },
    {
        "group_by",
        Query_group_by
    },
    {
        "group_by_w_ctx",
        Query_group_by_w_ctx
    }
};

bake_test_case Pairs_testcases[] = {
    {
        "type_w_one_pair",
        Pairs_type_w_one_pair
    },
    {
        "type_w_two_pairs",
        Pairs_type_w_two_pairs
    },
    {
        "add_pair",
        Pairs_add_pair
    },
    {
        "remove_pair",
        Pairs_remove_pair
    },
    {
        "add_tag_pair_for_tag",
        Pairs_add_tag_pair_for_tag
    },
    {
        "add_tag_pair_for_component",
        Pairs_add_tag_pair_for_component
    },
    {
        "query_2_pairs",
        Pairs_query_2_pairs
    },
    {
        "query_2_pairs_2_instances_per_type",
        Pairs_query_2_pairs_2_instances_per_type
    },
    {
        "query_pair_or_component",
        Pairs_query_pair_or_component
    },
    {
        "query_pair_or_pair",
        Pairs_query_pair_or_pair
    },
    {
        "query_not_pair",
        Pairs_query_not_pair
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
        "pair_w_component_query",
        Pairs_pair_w_component_query
    },
    {
        "pair_wildcard_system",
        Pairs_pair_wildcard_system
    },
    {
        "pair_only_wildcard_system",
        Pairs_pair_only_wildcard_system
    },
    {
        "pair_wildcard_on_set",
        Pairs_pair_wildcard_on_set
    },
    {
        "on_add_pair",
        Pairs_on_add_pair
    },
    {
        "on_add_pair_tag",
        Pairs_on_add_pair_tag
    },
    {
        "on_remove_pair",
        Pairs_on_remove_pair
    },
    {
        "on_remove_pair_tag",
        Pairs_on_remove_pair_tag
    },
    {
        "on_remove_pair_on_delete",
        Pairs_on_remove_pair_on_delete
    },
    {
        "on_remove_pair_tag_on_delete",
        Pairs_on_remove_pair_tag_on_delete
    },
    {
        "pair_from_shared",
        Pairs_pair_from_shared
    },
    {
        "simple_pair_syntax",
        Pairs_simple_pair_syntax
    },
    {
        "get_typeid_w_recycled_rel",
        Pairs_get_typeid_w_recycled_rel
    },
    {
        "get_typeid_w_recycled_obj",
        Pairs_get_typeid_w_recycled_obj
    },
    {
        "id_str_w_recycled_rel",
        Pairs_id_str_w_recycled_rel
    },
    {
        "id_str_w_recycled_obj",
        Pairs_id_str_w_recycled_obj
    },
    {
        "set_object_w_zero_sized_rel_comp",
        Pairs_set_object_w_zero_sized_rel_comp
    },
    {
        "dsl_pair",
        Pairs_dsl_pair
    },
    {
        "dsl_pair_w_pred_wildcard",
        Pairs_dsl_pair_w_pred_wildcard
    },
    {
        "dsl_pair_w_obj_wildcard",
        Pairs_dsl_pair_w_obj_wildcard
    },
    {
        "dsl_pair_w_both_wildcard",
        Pairs_dsl_pair_w_both_wildcard
    },
    {
        "dsl_pair_w_explicit_subj_this",
        Pairs_dsl_pair_w_explicit_subj_this
    },
    {
        "dsl_pair_w_explicit_subj",
        Pairs_dsl_pair_w_explicit_subj
    },
    {
        "api_pair",
        Pairs_api_pair
    },
    {
        "api_pair_w_pred_wildcard",
        Pairs_api_pair_w_pred_wildcard
    },
    {
        "api_pair_w_obj_wildcard",
        Pairs_api_pair_w_obj_wildcard
    },
    {
        "api_pair_w_both_wildcard",
        Pairs_api_pair_w_both_wildcard
    },
    {
        "api_pair_w_explicit_subj_this",
        Pairs_api_pair_w_explicit_subj_this
    },
    {
        "api_pair_w_explicit_subj",
        Pairs_api_pair_w_explicit_subj
    },
    {
        "typeid_from_tag",
        Pairs_typeid_from_tag
    },
    {
        "typeid_from_component",
        Pairs_typeid_from_component
    },
    {
        "typeid_from_pair",
        Pairs_typeid_from_pair
    },
    {
        "typeid_from_pair_w_rel_type",
        Pairs_typeid_from_pair_w_rel_type
    },
    {
        "typeid_from_pair_w_obj_type",
        Pairs_typeid_from_pair_w_obj_type
    },
    {
        "typeid_from_pair_w_rel_obj_type",
        Pairs_typeid_from_pair_w_rel_obj_type
    },
    {
        "typeid_from_pair_w_rel_0_obj_type",
        Pairs_typeid_from_pair_w_rel_0_obj_type
    },
    {
        "typeid_from_pair_w_rel_obj_0_type",
        Pairs_typeid_from_pair_w_rel_obj_0_type
    },
    {
        "typeid_from_pair_w_rel_0_obj_0_type",
        Pairs_typeid_from_pair_w_rel_0_obj_0_type
    },
    {
        "tag_pair_w_rel_comp",
        Pairs_tag_pair_w_rel_comp
    },
    {
        "tag_pair_w_obj_comp",
        Pairs_tag_pair_w_obj_comp
    },
    {
        "tag_pair_w_rel_obj_comp",
        Pairs_tag_pair_w_rel_obj_comp
    },
    {
        "get_tag_pair_w_rel_comp",
        Pairs_get_tag_pair_w_rel_comp
    },
    {
        "get_tag_pair_w_obj_comp",
        Pairs_get_tag_pair_w_obj_comp
    },
    {
        "get_tag_pair_w_rel_obj_comp",
        Pairs_get_tag_pair_w_rel_obj_comp
    },
    {
        "tag_pair_w_childof_w_comp",
        Pairs_tag_pair_w_childof_w_comp
    },
    {
        "tag_pair_w_isa_w_comp",
        Pairs_tag_pair_w_isa_w_comp
    }
};

bake_test_case Trigger_testcases[] = {
    {
        "on_add_trigger_before_table",
        Trigger_on_add_trigger_before_table
    },
    {
        "on_add_trigger_after_table",
        Trigger_on_add_trigger_after_table
    },
    {
        "on_remove_trigger_before_table",
        Trigger_on_remove_trigger_before_table
    },
    {
        "on_remove_trigger_after_table",
        Trigger_on_remove_trigger_after_table
    },
    {
        "on_add_tag",
        Trigger_on_add_tag
    },
    {
        "on_add_component",
        Trigger_on_add_component
    },
    {
        "on_add_wildcard",
        Trigger_on_add_wildcard
    },
    {
        "on_add_pair",
        Trigger_on_add_pair
    },
    {
        "on_add_pair_obj_wildcard",
        Trigger_on_add_pair_obj_wildcard
    },
    {
        "on_add_pair_pred_wildcard",
        Trigger_on_add_pair_pred_wildcard
    },
    {
        "on_add_pair_wildcard",
        Trigger_on_add_pair_wildcard
    },
    {
        "on_remove_tag",
        Trigger_on_remove_tag
    },
    {
        "on_remove_component",
        Trigger_on_remove_component
    },
    {
        "on_remove_wildcard",
        Trigger_on_remove_wildcard
    },
    {
        "on_remove_pair",
        Trigger_on_remove_pair
    },
    {
        "on_remove_pair_obj_wildcard",
        Trigger_on_remove_pair_obj_wildcard
    },
    {
        "on_remove_pair_pred_wildcard",
        Trigger_on_remove_pair_pred_wildcard
    },
    {
        "on_remove_pair_wildcard",
        Trigger_on_remove_pair_wildcard
    },
    {
        "on_add_remove",
        Trigger_on_add_remove
    },
    {
        "on_set_component",
        Trigger_on_set_component
    },
    {
        "on_set_wildcard",
        Trigger_on_set_wildcard
    },
    {
        "on_set_pair",
        Trigger_on_set_pair
    },
    {
        "on_set_pair_w_obj_wildcard",
        Trigger_on_set_pair_w_obj_wildcard
    },
    {
        "on_set_pair_pred_wildcard",
        Trigger_on_set_pair_pred_wildcard
    },
    {
        "on_set_pair_wildcard",
        Trigger_on_set_pair_wildcard
    },
    {
        "on_set_component_after_modified",
        Trigger_on_set_component_after_modified
    },
    {
        "un_set_component",
        Trigger_un_set_component
    },
    {
        "un_set_wildcard",
        Trigger_un_set_wildcard
    },
    {
        "un_set_pair",
        Trigger_un_set_pair
    },
    {
        "un_set_pair_w_obj_wildcard",
        Trigger_un_set_pair_w_obj_wildcard
    },
    {
        "un_set_pair_pred_wildcard",
        Trigger_un_set_pair_pred_wildcard
    },
    {
        "un_set_pair_wildcard",
        Trigger_un_set_pair_wildcard
    },
    {
        "add_twice",
        Trigger_add_twice
    },
    {
        "remove_twice",
        Trigger_remove_twice
    },
    {
        "on_remove_w_clear",
        Trigger_on_remove_w_clear
    },
    {
        "on_remove_w_delete",
        Trigger_on_remove_w_delete
    },
    {
        "on_remove_w_world_fini",
        Trigger_on_remove_w_world_fini
    },
    {
        "on_add_w_clone",
        Trigger_on_add_w_clone
    },
    {
        "add_in_trigger",
        Trigger_add_in_trigger
    },
    {
        "remove_in_trigger",
        Trigger_remove_in_trigger
    },
    {
        "clear_in_trigger",
        Trigger_clear_in_trigger
    },
    {
        "delete_in_trigger",
        Trigger_delete_in_trigger
    },
    {
        "trigger_w_named_entity",
        Trigger_trigger_w_named_entity
    },
    {
        "on_remove_tree",
        Trigger_on_remove_tree
    },
    {
        "set_get_context",
        Trigger_set_get_context
    },
    {
        "set_get_binding_context",
        Trigger_set_get_binding_context
    },
    {
        "trigger_w_self",
        Trigger_trigger_w_self
    },
    {
        "delete_trigger_w_delete_ctx",
        Trigger_delete_trigger_w_delete_ctx
    },
    {
        "trigger_w_index",
        Trigger_trigger_w_index
    }
};

bake_test_case Observer_testcases[] = {
    {
        "2_terms_w_on_add",
        Observer_2_terms_w_on_add
    },
    {
        "2_terms_w_on_remove",
        Observer_2_terms_w_on_remove
    },
    {
        "2_terms_w_on_set_value",
        Observer_2_terms_w_on_set_value
    },
    {
        "2_terms_w_on_remove_value",
        Observer_2_terms_w_on_remove_value
    },
    {
        "2_terms_w_on_add_2nd",
        Observer_2_terms_w_on_add_2nd
    },
    {
        "2_terms_w_on_remove_2nd",
        Observer_2_terms_w_on_remove_2nd
    },
    {
        "2_pair_terms_w_on_add",
        Observer_2_pair_terms_w_on_add
    },
    {
        "2_pair_terms_w_on_remove",
        Observer_2_pair_terms_w_on_remove
    },
    {
        "2_wildcard_pair_terms_w_on_add",
        Observer_2_wildcard_pair_terms_w_on_add
    },
    {
        "2_wildcard_pair_terms_w_on_add_2_matching",
        Observer_2_wildcard_pair_terms_w_on_add_2_matching
    },
    {
        "2_wildcard_pair_terms_w_on_add_3_matching",
        Observer_2_wildcard_pair_terms_w_on_add_3_matching
    },
    {
        "2_wildcard_pair_terms_w_on_remove",
        Observer_2_wildcard_pair_terms_w_on_remove
    },
    {
        "2_terms_1_not_w_on_add",
        Observer_2_terms_1_not_w_on_add
    },
    {
        "2_terms_1_not_w_on_remove",
        Observer_2_terms_1_not_w_on_remove
    },
    {
        "2_terms_w_on_set",
        Observer_2_terms_w_on_set
    },
    {
        "2_terms_w_un_set",
        Observer_2_terms_w_un_set
    },
    {
        "3_terms_2_or_on_add",
        Observer_3_terms_2_or_on_add
    },
    {
        "3_terms_2_or_on_remove",
        Observer_3_terms_2_or_on_remove
    },
    {
        "2_terms_w_from_entity_on_add",
        Observer_2_terms_w_from_entity_on_add
    },
    {
        "2_terms_on_remove_on_clear",
        Observer_2_terms_on_remove_on_clear
    },
    {
        "2_terms_on_remove_on_delete",
        Observer_2_terms_on_remove_on_delete
    },
    {
        "observer_w_self",
        Observer_observer_w_self
    },
    {
        "add_after_delete_observer",
        Observer_add_after_delete_observer
    },
    {
        "remove_after_delete_observer",
        Observer_remove_after_delete_observer
    },
    {
        "delete_observer_w_ctx",
        Observer_delete_observer_w_ctx
    }
};

bake_test_case TriggerOnAdd_testcases[] = {
    {
        "new_match_1_of_1",
        TriggerOnAdd_new_match_1_of_1
    },
    {
        "new_match_1_of_2",
        TriggerOnAdd_new_match_1_of_2
    },
    {
        "new_no_match_1",
        TriggerOnAdd_new_no_match_1
    },
    {
        "new_w_count_match_1_of_1",
        TriggerOnAdd_new_w_count_match_1_of_1
    },
    {
        "add_match_1_of_1",
        TriggerOnAdd_add_match_1_of_1
    },
    {
        "add_match_1_of_2",
        TriggerOnAdd_add_match_1_of_2
    },
    {
        "add_no_match_1",
        TriggerOnAdd_add_no_match_1
    },
    {
        "set_match_1_of_1",
        TriggerOnAdd_set_match_1_of_1
    },
    {
        "set_no_match_1",
        TriggerOnAdd_set_no_match_1
    },
    {
        "clone_match_1_of_1",
        TriggerOnAdd_clone_match_1_of_1
    },
    {
        "clone_match_1_of_2",
        TriggerOnAdd_clone_match_1_of_2
    },
    {
        "add_again_1",
        TriggerOnAdd_add_again_1
    },
    {
        "set_again_1",
        TriggerOnAdd_set_again_1
    },
    {
        "add_again_2",
        TriggerOnAdd_add_again_2
    },
    {
        "override_after_add_in_on_add",
        TriggerOnAdd_override_after_add_in_on_add
    },
    {
        "add_again_in_progress",
        TriggerOnAdd_add_again_in_progress
    },
    {
        "add_in_progress_before_system_def",
        TriggerOnAdd_add_in_progress_before_system_def
    },
    {
        "2_systems_w_table_creation",
        TriggerOnAdd_2_systems_w_table_creation
    },
    {
        "2_systems_w_table_creation_in_progress",
        TriggerOnAdd_2_systems_w_table_creation_in_progress
    },
    {
        "sys_context",
        TriggerOnAdd_sys_context
    },
    {
        "get_sys_context_from_param",
        TriggerOnAdd_get_sys_context_from_param
    },
    {
        "remove_added_component_in_on_add_w_set",
        TriggerOnAdd_remove_added_component_in_on_add_w_set
    },
    {
        "on_add_in_on_add",
        TriggerOnAdd_on_add_in_on_add
    },
    {
        "on_remove_in_on_add",
        TriggerOnAdd_on_remove_in_on_add
    },
    {
        "on_set_in_on_add",
        TriggerOnAdd_on_set_in_on_add
    },
    {
        "on_add_in_on_update",
        TriggerOnAdd_on_add_in_on_update
    },
    {
        "emplace",
        TriggerOnAdd_emplace
    },
    {
        "add_after_delete_trigger",
        TriggerOnAdd_add_after_delete_trigger
    },
    {
        "add_after_delete_wildcard_id_trigger",
        TriggerOnAdd_add_after_delete_wildcard_id_trigger
    }
};

bake_test_case TriggerOnRemove_testcases[] = {
    {
        "remove_match_1_of_1",
        TriggerOnRemove_remove_match_1_of_1
    },
    {
        "remove_match_1_of_2",
        TriggerOnRemove_remove_match_1_of_2
    },
    {
        "remove_no_match_1",
        TriggerOnRemove_remove_no_match_1
    },
    {
        "delete_match_1_of_1",
        TriggerOnRemove_delete_match_1_of_1
    },
    {
        "delete_match_1_of_2",
        TriggerOnRemove_delete_match_1_of_2
    },
    {
        "delete_no_match_1",
        TriggerOnRemove_delete_no_match_1
    },
    {
        "remove_watched",
        TriggerOnRemove_remove_watched
    },
    {
        "delete_watched",
        TriggerOnRemove_delete_watched
    },
    {
        "valid_entity_after_delete",
        TriggerOnRemove_valid_entity_after_delete
    },
    {
        "remove_after_delete_trigger",
        TriggerOnRemove_remove_after_delete_trigger
    },
    {
        "remove_after_delete_wildcard_id_trigger",
        TriggerOnRemove_remove_after_delete_wildcard_id_trigger
    }
};

bake_test_case TriggerOnSet_testcases[] = {
    {
        "set",
        TriggerOnSet_set
    },
    {
        "set_new",
        TriggerOnSet_set_new
    },
    {
        "set_again",
        TriggerOnSet_set_again
    },
    {
        "clone",
        TriggerOnSet_clone
    },
    {
        "clone_w_value",
        TriggerOnSet_clone_w_value
    },
    {
        "set_and_add_system",
        TriggerOnSet_set_and_add_system
    },
    {
        "on_set_after_override",
        TriggerOnSet_on_set_after_override
    },
    {
        "on_set_after_override_w_new",
        TriggerOnSet_on_set_after_override_w_new
    },
    {
        "on_set_after_override_w_new_w_count",
        TriggerOnSet_on_set_after_override_w_new_w_count
    },
    {
        "on_set_after_override_1_of_2_overridden",
        TriggerOnSet_on_set_after_override_1_of_2_overridden
    },
    {
        "on_set_after_snapshot_restore",
        TriggerOnSet_on_set_after_snapshot_restore
    },
    {
        "emplace",
        TriggerOnSet_emplace
    }
};

bake_test_case Monitor_testcases[] = {
    {
        "1_comp",
        Monitor_1_comp
    },
    {
        "2_comps",
        Monitor_2_comps
    },
    {
        "1_comp_1_not",
        Monitor_1_comp_1_not
    },
    {
        "1_parent",
        Monitor_1_parent
    },
    {
        "1_comp_1_parent",
        Monitor_1_comp_1_parent
    },
    {
        "1_comp_prefab_new",
        Monitor_1_comp_prefab_new
    },
    {
        "1_comp_prefab_add",
        Monitor_1_comp_prefab_add
    }
};

bake_test_case SystemOnSet_testcases[] = {
    {
        "set_1_of_1",
        SystemOnSet_set_1_of_1
    },
    {
        "set_1_of_2",
        SystemOnSet_set_1_of_2
    },
    {
        "set_1_of_3",
        SystemOnSet_set_1_of_3
    },
    {
        "bulk_new_1",
        SystemOnSet_bulk_new_1
    },
    {
        "bulk_new_2",
        SystemOnSet_bulk_new_2
    },
    {
        "bulk_new_2_of_1",
        SystemOnSet_bulk_new_2_of_1
    },
    {
        "bulk_new_3",
        SystemOnSet_bulk_new_3
    },
    {
        "bulk_new_3_of_2",
        SystemOnSet_bulk_new_3_of_2
    },
    {
        "bulk_new_1_from_base",
        SystemOnSet_bulk_new_1_from_base
    },
    {
        "set_1_of_2_1_from_base",
        SystemOnSet_set_1_of_2_1_from_base
    },
    {
        "set_1_of_3_1_from_base",
        SystemOnSet_set_1_of_3_1_from_base
    },
    {
        "add_base",
        SystemOnSet_add_base
    },
    {
        "add_base_to_1_overridden",
        SystemOnSet_add_base_to_1_overridden
    },
    {
        "add_base_to_2_overridden",
        SystemOnSet_add_base_to_2_overridden
    },
    {
        "add_base_to_1_of_2_overridden",
        SystemOnSet_add_base_to_1_of_2_overridden
    },
    {
        "on_set_after_remove_override",
        SystemOnSet_on_set_after_remove_override
    },
    {
        "no_set_after_remove_base",
        SystemOnSet_no_set_after_remove_base
    },
    {
        "un_set_after_remove",
        SystemOnSet_un_set_after_remove
    },
    {
        "un_set_after_remove_base",
        SystemOnSet_un_set_after_remove_base
    },
    {
        "add_to_current_in_on_set",
        SystemOnSet_add_to_current_in_on_set
    },
    {
        "remove_from_current_in_on_set",
        SystemOnSet_remove_from_current_in_on_set
    },
    {
        "remove_set_component_in_on_set",
        SystemOnSet_remove_set_component_in_on_set
    },
    {
        "match_table_created_w_add_in_on_set",
        SystemOnSet_match_table_created_w_add_in_on_set
    },
    {
        "set_optional",
        SystemOnSet_set_optional
    },
    {
        "set_from_nothing",
        SystemOnSet_set_from_nothing
    },
    {
        "add_null_type_in_on_set",
        SystemOnSet_add_null_type_in_on_set
    },
    {
        "add_0_entity_in_on_set",
        SystemOnSet_add_0_entity_in_on_set
    },
    {
        "on_set_prefab",
        SystemOnSet_on_set_prefab
    }
};

bake_test_case SystemUnSet_testcases[] = {
    {
        "unset_1_of_1",
        SystemUnSet_unset_1_of_1
    },
    {
        "unset_1_of_2",
        SystemUnSet_unset_1_of_2
    },
    {
        "unset_1_of_3",
        SystemUnSet_unset_1_of_3
    },
    {
        "unset_on_delete_1",
        SystemUnSet_unset_on_delete_1
    },
    {
        "unset_on_delete_2",
        SystemUnSet_unset_on_delete_2
    },
    {
        "unset_on_delete_3",
        SystemUnSet_unset_on_delete_3
    },
    {
        "unset_on_fini_1",
        SystemUnSet_unset_on_fini_1
    },
    {
        "unset_on_fini_2",
        SystemUnSet_unset_on_fini_2
    },
    {
        "unset_on_fini_3",
        SystemUnSet_unset_on_fini_3
    },
    {
        "overlapping_unset_systems",
        SystemUnSet_overlapping_unset_systems
    },
    {
        "unset_move_to_nonempty_table",
        SystemUnSet_unset_move_to_nonempty_table
    },
    {
        "write_in_unset",
        SystemUnSet_write_in_unset
    }
};

bake_test_case SystemPeriodic_testcases[] = {
    {
        "1_type_1_component",
        SystemPeriodic_1_type_1_component
    },
    {
        "1_type_3_component",
        SystemPeriodic_1_type_3_component
    },
    {
        "3_type_1_component",
        SystemPeriodic_3_type_1_component
    },
    {
        "2_type_3_component",
        SystemPeriodic_2_type_3_component
    },
    {
        "1_type_1_component_1_tag",
        SystemPeriodic_1_type_1_component_1_tag
    },
    {
        "2_type_1_component_1_tag",
        SystemPeriodic_2_type_1_component_1_tag
    },
    {
        "2_type_1_and_1_not",
        SystemPeriodic_2_type_1_and_1_not
    },
    {
        "2_type_2_and_1_not",
        SystemPeriodic_2_type_2_and_1_not
    },
    {
        "2_type_2_and_2_not",
        SystemPeriodic_2_type_2_and_2_not
    },
    {
        "4_type_1_and_1_or",
        SystemPeriodic_4_type_1_and_1_or
    },
    {
        "4_type_1_and_1_or_of_3",
        SystemPeriodic_4_type_1_and_1_or_of_3
    },
    {
        "1_type_1_and_1_or",
        SystemPeriodic_1_type_1_and_1_or
    },
    {
        "2_type_1_and_1_optional",
        SystemPeriodic_2_type_1_and_1_optional
    },
    {
        "2_type_2_and_1_optional",
        SystemPeriodic_2_type_2_and_1_optional
    },
    {
        "6_type_1_and_2_optional",
        SystemPeriodic_6_type_1_and_2_optional
    },
    {
        "ensure_optional_is_unset_column",
        SystemPeriodic_ensure_optional_is_unset_column
    },
    {
        "ensure_optional_is_null_shared",
        SystemPeriodic_ensure_optional_is_null_shared
    },
    {
        "ensure_optional_is_null_field_owned",
        SystemPeriodic_ensure_optional_is_null_field_owned
    },
    {
        "ensure_optional_is_null_field_shared",
        SystemPeriodic_ensure_optional_is_null_field_shared
    },
    {
        "use_fields_2_owned",
        SystemPeriodic_use_fields_2_owned
    },
    {
        "use_fields_1_owned_1_shared",
        SystemPeriodic_use_fields_1_owned_1_shared
    },
    {
        "match_2_systems_w_populated_table",
        SystemPeriodic_match_2_systems_w_populated_table
    },
    {
        "on_period",
        SystemPeriodic_on_period
    },
    {
        "on_period_long_delta",
        SystemPeriodic_on_period_long_delta
    },
    {
        "disabled",
        SystemPeriodic_disabled
    },
    {
        "disabled_feature",
        SystemPeriodic_disabled_feature
    },
    {
        "disabled_nested_feature",
        SystemPeriodic_disabled_nested_feature
    },
    {
        "two_refs",
        SystemPeriodic_two_refs
    },
    {
        "filter_disabled",
        SystemPeriodic_filter_disabled
    },
    {
        "match_disabled",
        SystemPeriodic_match_disabled
    },
    {
        "match_disabled_and_enabled",
        SystemPeriodic_match_disabled_and_enabled
    },
    {
        "match_prefab",
        SystemPeriodic_match_prefab
    },
    {
        "match_prefab_and_normal",
        SystemPeriodic_match_prefab_and_normal
    },
    {
        "is_shared_on_column_not_set",
        SystemPeriodic_is_shared_on_column_not_set
    },
    {
        "owned_column",
        SystemPeriodic_owned_column
    },
    {
        "owned_not_column",
        SystemPeriodic_owned_not_column
    },
    {
        "owned_or_column",
        SystemPeriodic_owned_or_column
    },
    {
        "shared_column",
        SystemPeriodic_shared_column
    },
    {
        "shared_not_column",
        SystemPeriodic_shared_not_column
    },
    {
        "shared_or_column",
        SystemPeriodic_shared_or_column
    },
    {
        "container_dont_match_inheritance",
        SystemPeriodic_container_dont_match_inheritance
    },
    {
        "cascade_dont_match_inheritance",
        SystemPeriodic_cascade_dont_match_inheritance
    },
    {
        "not_from_singleton",
        SystemPeriodic_not_from_singleton
    },
    {
        "not_from_entity",
        SystemPeriodic_not_from_entity
    },
    {
        "sys_context",
        SystemPeriodic_sys_context
    },
    {
        "get_sys_context_from_param",
        SystemPeriodic_get_sys_context_from_param
    },
    {
        "use_field_w_0_size",
        SystemPeriodic_use_field_w_0_size
    },
    {
        "owned_only",
        SystemPeriodic_owned_only
    },
    {
        "shared_only",
        SystemPeriodic_shared_only
    },
    {
        "is_in_readonly",
        SystemPeriodic_is_in_readonly
    },
    {
        "get_period",
        SystemPeriodic_get_period
    },
    {
        "and_type",
        SystemPeriodic_and_type
    },
    {
        "or_type",
        SystemPeriodic_or_type
    }
};

bake_test_case Timer_testcases[] = {
    {
        "timeout",
        Timer_timeout
    },
    {
        "interval",
        Timer_interval
    },
    {
        "shared_timeout",
        Timer_shared_timeout
    },
    {
        "shared_interval",
        Timer_shared_interval
    },
    {
        "start_stop_one_shot",
        Timer_start_stop_one_shot
    },
    {
        "start_stop_interval",
        Timer_start_stop_interval
    },
    {
        "rate_filter",
        Timer_rate_filter
    },
    {
        "rate_filter_w_rate_filter_src",
        Timer_rate_filter_w_rate_filter_src
    },
    {
        "rate_filter_w_timer_src",
        Timer_rate_filter_w_timer_src
    },
    {
        "rate_filter_with_empty_src",
        Timer_rate_filter_with_empty_src
    },
    {
        "one_shot_timer_entity",
        Timer_one_shot_timer_entity
    },
    {
        "interval_timer_entity",
        Timer_interval_timer_entity
    },
    {
        "rate_entity",
        Timer_rate_entity
    },
    {
        "nested_rate_entity",
        Timer_nested_rate_entity
    },
    {
        "nested_rate_entity_empty_src",
        Timer_nested_rate_entity_empty_src
    },
    {
        "naked_tick_entity",
        Timer_naked_tick_entity
    }
};

bake_test_case SystemOnDemand_testcases[] = {
    {
        "enable_out_after_in",
        SystemOnDemand_enable_out_after_in
    },
    {
        "enable_in_after_out",
        SystemOnDemand_enable_in_after_out
    },
    {
        "enable_out_after_in_2_out_1_in",
        SystemOnDemand_enable_out_after_in_2_out_1_in
    },
    {
        "enable_out_after_in_1_out_2_in",
        SystemOnDemand_enable_out_after_in_1_out_2_in
    },
    {
        "enable_in_after_out_2_out_1_in",
        SystemOnDemand_enable_in_after_out_2_out_1_in
    },
    {
        "enable_in_after_out_1_out_2_in",
        SystemOnDemand_enable_in_after_out_1_out_2_in
    },
    {
        "disable_after_disable_in",
        SystemOnDemand_disable_after_disable_in
    },
    {
        "disable_after_disable_in_2_out_1_in",
        SystemOnDemand_disable_after_disable_in_2_out_1_in
    },
    {
        "disable_after_disable_in_1_out_2_in",
        SystemOnDemand_disable_after_disable_in_1_out_2_in
    },
    {
        "table_after_out",
        SystemOnDemand_table_after_out
    },
    {
        "table_after_out_and_in",
        SystemOnDemand_table_after_out_and_in
    },
    {
        "table_after_out_and_in_overlapping_columns",
        SystemOnDemand_table_after_out_and_in_overlapping_columns
    },
    {
        "1_out_system_2_in_systems",
        SystemOnDemand_1_out_system_2_in_systems
    },
    {
        "1_out_system_2_in_systems_different_columns",
        SystemOnDemand_1_out_system_2_in_systems_different_columns
    },
    {
        "1_out_system_2_in_systems_overlapping_columns",
        SystemOnDemand_1_out_system_2_in_systems_overlapping_columns
    },
    {
        "disable_after_inactive_in_system",
        SystemOnDemand_disable_after_inactive_in_system
    },
    {
        "disable_after_2_inactive_in_systems",
        SystemOnDemand_disable_after_2_inactive_in_systems
    },
    {
        "disable_after_2_inactive_in_systems_different_columns",
        SystemOnDemand_disable_after_2_inactive_in_systems_different_columns
    },
    {
        "enable_2_output_1_input_system",
        SystemOnDemand_enable_2_output_1_input_system
    },
    {
        "enable_2_output_1_input_system_different_columns",
        SystemOnDemand_enable_2_output_1_input_system_different_columns
    },
    {
        "enable_2_output_1_input_system_overlapping_columns",
        SystemOnDemand_enable_2_output_1_input_system_overlapping_columns
    },
    {
        "out_not_column",
        SystemOnDemand_out_not_column
    },
    {
        "trigger_on_manual",
        SystemOnDemand_trigger_on_manual
    },
    {
        "trigger_on_manual_not_column",
        SystemOnDemand_trigger_on_manual_not_column
    },
    {
        "on_demand_task_w_from_entity",
        SystemOnDemand_on_demand_task_w_from_entity
    },
    {
        "on_demand_task_w_not_from_entity",
        SystemOnDemand_on_demand_task_w_not_from_entity
    },
    {
        "enable_after_user_disable",
        SystemOnDemand_enable_after_user_disable
    }
};

bake_test_case SystemCascade_testcases[] = {
    {
        "cascade_depth_1",
        SystemCascade_cascade_depth_1
    },
    {
        "cascade_depth_2",
        SystemCascade_cascade_depth_2
    },
    {
        "cascade_depth_2_new_syntax",
        SystemCascade_cascade_depth_2_new_syntax
    },
    {
        "add_after_match",
        SystemCascade_add_after_match
    },
    {
        "adopt_after_match",
        SystemCascade_adopt_after_match
    },
    {
        "rematch_w_empty_table",
        SystemCascade_rematch_w_empty_table
    },
    {
        "query_w_only_cascade",
        SystemCascade_query_w_only_cascade
    },
    {
        "custom_relation_cascade_depth_1",
        SystemCascade_custom_relation_cascade_depth_1
    },
    {
        "custom_relation_cascade_depth_2",
        SystemCascade_custom_relation_cascade_depth_2
    },
    {
        "custom_relation_add_after_match",
        SystemCascade_custom_relation_add_after_match
    },
    {
        "custom_relation_adopt_after_match",
        SystemCascade_custom_relation_adopt_after_match
    },
    {
        "custom_relation_rematch_w_empty_table",
        SystemCascade_custom_relation_rematch_w_empty_table
    }
};

bake_test_case SystemManual_testcases[] = {
    {
        "1_type_1_component",
        SystemManual_1_type_1_component
    },
    {
        "activate_status",
        SystemManual_activate_status
    },
    {
        "no_automerge",
        SystemManual_no_automerge
    },
    {
        "dont_run_w_unmatching_entity_query",
        SystemManual_dont_run_w_unmatching_entity_query
    }
};

bake_test_case Tasks_testcases[] = {
    {
        "no_components",
        Tasks_no_components
    },
    {
        "one_tag",
        Tasks_one_tag
    },
    {
        "from_system",
        Tasks_from_system
    },
    {
        "tasks_in_phases",
        Tasks_tasks_in_phases
    }
};

bake_test_case Prefab_testcases[] = {
    {
        "new_w_prefab",
        Prefab_new_w_prefab
    },
    {
        "new_w_count_prefab",
        Prefab_new_w_count_prefab
    },
    {
        "new_w_type_w_prefab",
        Prefab_new_w_type_w_prefab
    },
    {
        "add_prefab",
        Prefab_add_prefab
    },
    {
        "add_type_w_prefab",
        Prefab_add_type_w_prefab
    },
    {
        "remove_prefab_after_new",
        Prefab_remove_prefab_after_new
    },
    {
        "remove_prefab_after_add",
        Prefab_remove_prefab_after_add
    },
    {
        "override_component",
        Prefab_override_component
    },
    {
        "override_remove_component",
        Prefab_override_remove_component
    },
    {
        "override_2_of_3_components_1_self",
        Prefab_override_2_of_3_components_1_self
    },
    {
        "new_type_w_1_override",
        Prefab_new_type_w_1_override
    },
    {
        "new_type_w_2_overrides",
        Prefab_new_type_w_2_overrides
    },
    {
        "add_type_w_1_overrides",
        Prefab_add_type_w_1_overrides
    },
    {
        "add_type_w_2_overrides",
        Prefab_add_type_w_2_overrides
    },
    {
        "get_ptr_prefab",
        Prefab_get_ptr_prefab
    },
    {
        "iterate_w_prefab_field",
        Prefab_iterate_w_prefab_field
    },
    {
        "iterate_w_prefab_shared",
        Prefab_iterate_w_prefab_shared
    },
    {
        "match_entity_prefab_w_system_optional",
        Prefab_match_entity_prefab_w_system_optional
    },
    {
        "prefab_in_system_expr",
        Prefab_prefab_in_system_expr
    },
    {
        "dont_match_prefab",
        Prefab_dont_match_prefab
    },
    {
        "new_w_count_w_override",
        Prefab_new_w_count_w_override
    },
    {
        "override_2_components_different_size",
        Prefab_override_2_components_different_size
    },
    {
        "ignore_prefab_parent_component",
        Prefab_ignore_prefab_parent_component
    },
    {
        "match_table_created_in_progress",
        Prefab_match_table_created_in_progress
    },
    {
        "prefab_w_1_child",
        Prefab_prefab_w_1_child
    },
    {
        "prefab_w_2_children",
        Prefab_prefab_w_2_children
    },
    {
        "prefab_w_grandchild",
        Prefab_prefab_w_grandchild
    },
    {
        "prefab_tree_1_2_1",
        Prefab_prefab_tree_1_2_1
    },
    {
        "prefab_w_base_w_child",
        Prefab_prefab_w_base_w_child
    },
    {
        "prefab_w_child_w_base",
        Prefab_prefab_w_child_w_base
    },
    {
        "prefab_w_child_w_base_w_children",
        Prefab_prefab_w_child_w_base_w_children
    },
    {
        "prefab_w_child_new_w_count",
        Prefab_prefab_w_child_new_w_count
    },
    {
        "prefab_auto_override_child_component",
        Prefab_prefab_auto_override_child_component
    },
    {
        "ignore_on_add",
        Prefab_ignore_on_add
    },
    {
        "ignore_on_remove",
        Prefab_ignore_on_remove
    },
    {
        "ignore_on_set",
        Prefab_ignore_on_set
    },
    {
        "on_set_on_instance",
        Prefab_on_set_on_instance
    },
    {
        "instantiate_in_progress",
        Prefab_instantiate_in_progress
    },
    {
        "copy_from_prefab_in_progress",
        Prefab_copy_from_prefab_in_progress
    },
    {
        "copy_from_prefab_first_instance_in_progress",
        Prefab_copy_from_prefab_first_instance_in_progress
    },
    {
        "ref_after_realloc",
        Prefab_ref_after_realloc
    },
    {
        "revalidate_ref_w_mixed_table_refs",
        Prefab_revalidate_ref_w_mixed_table_refs
    },
    {
        "no_overwrite_on_2nd_add",
        Prefab_no_overwrite_on_2nd_add
    },
    {
        "no_overwrite_on_2nd_add_in_progress",
        Prefab_no_overwrite_on_2nd_add_in_progress
    },
    {
        "no_instantiate_on_2nd_add",
        Prefab_no_instantiate_on_2nd_add
    },
    {
        "no_instantiate_on_2nd_add_in_progress",
        Prefab_no_instantiate_on_2nd_add_in_progress
    },
    {
        "nested_prefab_in_progress_w_count",
        Prefab_nested_prefab_in_progress_w_count
    },
    {
        "nested_prefab_in_progress_w_count_set_after_override",
        Prefab_nested_prefab_in_progress_w_count_set_after_override
    },
    {
        "get_ptr_from_prefab_from_new_table_in_progress",
        Prefab_get_ptr_from_prefab_from_new_table_in_progress
    },
    {
        "match_base",
        Prefab_match_base
    },
    {
        "match_base_after_add_in_prev_phase",
        Prefab_match_base_after_add_in_prev_phase
    },
    {
        "override_watched_prefab",
        Prefab_override_watched_prefab
    },
    {
        "rematch_twice",
        Prefab_rematch_twice
    },
    {
        "add_to_empty_base_in_system",
        Prefab_add_to_empty_base_in_system
    },
    {
        "dont_inherit_disabled",
        Prefab_dont_inherit_disabled
    },
    {
        "clone_after_inherit_in_on_add",
        Prefab_clone_after_inherit_in_on_add
    },
    {
        "override_from_nested",
        Prefab_override_from_nested
    },
    {
        "create_multiple_nested_w_on_set",
        Prefab_create_multiple_nested_w_on_set
    },
    {
        "create_multiple_nested_w_on_set_in_progress",
        Prefab_create_multiple_nested_w_on_set_in_progress
    },
    {
        "single_on_set_on_child_w_override",
        Prefab_single_on_set_on_child_w_override
    },
    {
        "force_owned",
        Prefab_force_owned
    },
    {
        "force_owned_2",
        Prefab_force_owned_2
    },
    {
        "force_owned_nested",
        Prefab_force_owned_nested
    },
    {
        "force_owned_type",
        Prefab_force_owned_type
    },
    {
        "force_owned_type_w_pair",
        Prefab_force_owned_type_w_pair
    },
    {
        "prefab_instanceof_hierarchy",
        Prefab_prefab_instanceof_hierarchy
    },
    {
        "override_tag",
        Prefab_override_tag
    },
    {
        "empty_prefab",
        Prefab_empty_prefab
    },
    {
        "instanceof_0",
        Prefab_instanceof_0
    },
    {
        "instantiate_empty_child_table",
        Prefab_instantiate_empty_child_table
    },
    {
        "instantiate_emptied_child_table",
        Prefab_instantiate_emptied_child_table
    },
    {
        "override_2_prefabs",
        Prefab_override_2_prefabs
    },
    {
        "rematch_after_add_instanceof_to_parent",
        Prefab_rematch_after_add_instanceof_to_parent
    },
    {
        "child_of_instance",
        Prefab_child_of_instance
    },
    {
        "rematch_after_prefab_delete",
        Prefab_rematch_after_prefab_delete
    },
    {
        "add_tag_w_low_id_to_instance",
        Prefab_add_tag_w_low_id_to_instance
    },
    {
        "get_type_after_base_add",
        Prefab_get_type_after_base_add
    },
    {
        "get_type_after_recycled_base_add",
        Prefab_get_type_after_recycled_base_add
    },
    {
        "new_w_recycled_base",
        Prefab_new_w_recycled_base
    },
    {
        "add_recycled_base",
        Prefab_add_recycled_base
    },
    {
        "remove_recycled_base",
        Prefab_remove_recycled_base
    },
    {
        "get_from_recycled_base",
        Prefab_get_from_recycled_base
    },
    {
        "override_from_recycled_base",
        Prefab_override_from_recycled_base
    },
    {
        "remove_override_from_recycled_base",
        Prefab_remove_override_from_recycled_base
    },
    {
        "instantiate_tree_from_recycled_base",
        Prefab_instantiate_tree_from_recycled_base
    },
    {
        "rematch_after_add_to_recycled_base",
        Prefab_rematch_after_add_to_recycled_base
    }
};

bake_test_case System_w_FromContainer_testcases[] = {
    {
        "1_column_from_container",
        System_w_FromContainer_1_column_from_container
    },
    {
        "2_column_1_from_container",
        System_w_FromContainer_2_column_1_from_container
    },
    {
        "3_column_2_from_container",
        System_w_FromContainer_3_column_2_from_container
    },
    {
        "3_column_2_from_different_container",
        System_w_FromContainer_3_column_2_from_different_container
    },
    {
        "2_column_1_from_container_w_not",
        System_w_FromContainer_2_column_1_from_container_w_not
    },
    {
        "2_column_1_from_container_w_not_prefab",
        System_w_FromContainer_2_column_1_from_container_w_not_prefab
    },
    {
        "3_column_1_from_comtainer_1_from_container_w_not",
        System_w_FromContainer_3_column_1_from_comtainer_1_from_container_w_not
    },
    {
        "2_column_1_from_container_w_or",
        System_w_FromContainer_2_column_1_from_container_w_or
    },
    {
        "select_same_from_container",
        System_w_FromContainer_select_same_from_container
    },
    {
        "add_component_after_match",
        System_w_FromContainer_add_component_after_match
    },
    {
        "add_component_after_match_and_rematch",
        System_w_FromContainer_add_component_after_match_and_rematch
    },
    {
        "add_component_after_match_unmatch",
        System_w_FromContainer_add_component_after_match_unmatch
    },
    {
        "add_component_after_match_unmatch_match",
        System_w_FromContainer_add_component_after_match_unmatch_match
    },
    {
        "add_component_after_match_2_systems",
        System_w_FromContainer_add_component_after_match_2_systems
    },
    {
        "add_component_in_progress_after_match",
        System_w_FromContainer_add_component_in_progress_after_match
    },
    {
        "add_component_after_match_and_rematch_w_entity_type_expr",
        System_w_FromContainer_add_component_after_match_and_rematch_w_entity_type_expr
    },
    {
        "add_component_after_match_and_rematch_w_entity_type_expr_in_progress",
        System_w_FromContainer_add_component_after_match_and_rematch_w_entity_type_expr_in_progress
    },
    {
        "adopt_after_match",
        System_w_FromContainer_adopt_after_match
    },
    {
        "new_child_after_match",
        System_w_FromContainer_new_child_after_match
    },
    {
        "realloc_after_match",
        System_w_FromContainer_realloc_after_match
    }
};

bake_test_case System_w_FromId_testcases[] = {
    {
        "2_column_1_from_id",
        System_w_FromId_2_column_1_from_id
    },
    {
        "3_column_2_from_id",
        System_w_FromId_3_column_2_from_id
    },
    {
        "column_type",
        System_w_FromId_column_type
    }
};

bake_test_case System_w_FromSystem_testcases[] = {
    {
        "2_column_1_from_system",
        System_w_FromSystem_2_column_1_from_system
    },
    {
        "3_column_2_from_system",
        System_w_FromSystem_3_column_2_from_system
    },
    {
        "auto_add_tag",
        System_w_FromSystem_auto_add_tag
    }
};

bake_test_case System_w_FromEntity_testcases[] = {
    {
        "2_column_1_from_entity",
        System_w_FromEntity_2_column_1_from_entity
    },
    {
        "task_from_entity",
        System_w_FromEntity_task_from_entity
    },
    {
        "task_not_from_entity",
        System_w_FromEntity_task_not_from_entity
    }
};

bake_test_case World_testcases[] = {
    {
        "progress_w_0",
        World_progress_w_0
    },
    {
        "progress_w_t",
        World_progress_w_t
    },
    {
        "get_tick",
        World_get_tick
    },
    {
        "entity_range_offset",
        World_entity_range_offset
    },
    {
        "entity_range_offset_out_of_range",
        World_entity_range_offset_out_of_range
    },
    {
        "entity_range_limit_out_of_range",
        World_entity_range_limit_out_of_range
    },
    {
        "entity_range_add_existing_in_progress",
        World_entity_range_add_existing_in_progress
    },
    {
        "entity_range_add_in_range_in_progress",
        World_entity_range_add_in_range_in_progress
    },
    {
        "entity_range_add_out_of_range_in_progress",
        World_entity_range_add_out_of_range_in_progress
    },
    {
        "entity_range_out_of_range_check_disabled",
        World_entity_range_out_of_range_check_disabled
    },
    {
        "dim",
        World_dim
    },
    {
        "dim_dim_type",
        World_dim_dim_type
    },
    {
        "phases",
        World_phases
    },
    {
        "phases_w_merging",
        World_phases_w_merging
    },
    {
        "phases_match_in_create",
        World_phases_match_in_create
    },
    {
        "measure_time",
        World_measure_time
    },
    {
        "control_fps",
        World_control_fps
    },
    {
        "control_fps_busy_system",
        World_control_fps_busy_system
    },
    {
        "control_fps_busy_app",
        World_control_fps_busy_app
    },
    {
        "control_fps_random_system",
        World_control_fps_random_system
    },
    {
        "control_fps_random_app",
        World_control_fps_random_app
    },
    {
        "measure_fps_vs_actual",
        World_measure_fps_vs_actual
    },
    {
        "measure_delta_time_vs_actual",
        World_measure_delta_time_vs_actual
    },
    {
        "system_time_scale",
        World_system_time_scale
    },
    {
        "quit",
        World_quit
    },
    {
        "get_delta_time",
        World_get_delta_time
    },
    {
        "get_delta_time_auto",
        World_get_delta_time_auto
    },
    {
        "recreate_world",
        World_recreate_world
    },
    {
        "recreate_world_w_component",
        World_recreate_world_w_component
    },
    {
        "no_threading",
        World_no_threading
    },
    {
        "no_time",
        World_no_time
    },
    {
        "is_entity_enabled",
        World_is_entity_enabled
    },
    {
        "get_stats",
        World_get_stats
    }
};

bake_test_case Type_testcases[] = {
    {
        "type_of_1_tostr",
        Type_type_of_1_tostr
    },
    {
        "type_of_2_tostr",
        Type_type_of_2_tostr
    },
    {
        "type_of_2_tostr_no_id",
        Type_type_of_2_tostr_no_id
    },
    {
        "type_redefine",
        Type_type_redefine
    },
    {
        "type_from_array",
        Type_type_from_array
    },
    {
        "type_from_array_unsorted",
        Type_type_from_array_unsorted
    },
    {
        "type_has",
        Type_type_has
    },
    {
        "type_has_not",
        Type_type_has_not
    },
    {
        "zero_type_has_not",
        Type_zero_type_has_not
    },
    {
        "type_has_prefab",
        Type_type_has_prefab
    },
    {
        "type_has_parent",
        Type_type_has_parent
    },
    {
        "type_has_pair",
        Type_type_has_pair
    },
    {
        "type_has_pair_exact",
        Type_type_has_pair_exact
    },
    {
        "type_has_pair_0",
        Type_type_has_pair_0
    },
    {
        "type_has_pair_0_multiple",
        Type_type_has_pair_0_multiple
    },
    {
        "type_has_pair_0_no_pair",
        Type_type_has_pair_0_no_pair
    },
    {
        "type_owns_pair",
        Type_type_owns_pair
    },
    {
        "type_owns_pair_exact",
        Type_type_owns_pair_exact
    },
    {
        "type_owns_pair_0",
        Type_type_owns_pair_0
    },
    {
        "type_owns_pair_0_multiple",
        Type_type_owns_pair_0_multiple
    },
    {
        "type_owns_pair_0_no_pair",
        Type_type_owns_pair_0_no_pair
    },
    {
        "type_merge",
        Type_type_merge
    },
    {
        "type_merge_overlap",
        Type_type_merge_overlap
    },
    {
        "type_merge_overlap_one",
        Type_type_merge_overlap_one
    },
    {
        "type_merge_overlap_w_flag",
        Type_type_merge_overlap_w_flag
    },
    {
        "type_merge_overlap_w_flags_from_both",
        Type_type_merge_overlap_w_flags_from_both
    },
    {
        "type_add",
        Type_type_add
    },
    {
        "type_add_empty",
        Type_type_add_empty
    },
    {
        "type_add_entity_again",
        Type_type_add_entity_again
    },
    {
        "type_add_out_of_order",
        Type_type_add_out_of_order
    },
    {
        "type_add_existing",
        Type_type_add_existing
    },
    {
        "type_add_empty_existing",
        Type_type_add_empty_existing
    },
    {
        "type_add_out_of_order_existing",
        Type_type_add_out_of_order_existing
    },
    {
        "type_remove",
        Type_type_remove
    },
    {
        "type_remove_empty",
        Type_type_remove_empty
    },
    {
        "type_remove_non_existing",
        Type_type_remove_non_existing
    },
    {
        "type_of_2_add",
        Type_type_of_2_add
    },
    {
        "type_of_3_add_entity_again",
        Type_type_of_3_add_entity_again
    },
    {
        "invalid_entity_type_expression",
        Type_invalid_entity_type_expression
    },
    {
        "invalid_singleton_type_expression",
        Type_invalid_singleton_type_expression
    },
    {
        "invalid_container_type_expression",
        Type_invalid_container_type_expression
    },
    {
        "invalid_system_type_expression",
        Type_invalid_system_type_expression
    },
    {
        "type_from_empty_entity",
        Type_type_from_empty_entity
    },
    {
        "get_type",
        Type_get_type
    },
    {
        "get_type_from_empty",
        Type_get_type_from_empty
    },
    {
        "get_type_from_0",
        Type_get_type_from_0
    },
    {
        "entity_from_type",
        Type_entity_from_type
    },
    {
        "entity_from_empty_type",
        Type_entity_from_empty_type
    },
    {
        "entity_from_type_w_2_elements",
        Type_entity_from_type_w_2_elements
    },
    {
        "type_from_entity",
        Type_type_from_entity
    },
    {
        "type_from_empty",
        Type_type_from_empty
    },
    {
        "type_from_0",
        Type_type_from_0
    },
    {
        "type_to_expr_1_comp",
        Type_type_to_expr_1_comp
    },
    {
        "type_to_expr_2_comp",
        Type_type_to_expr_2_comp
    },
    {
        "type_to_expr_instanceof",
        Type_type_to_expr_instanceof
    },
    {
        "type_to_expr_childof",
        Type_type_to_expr_childof
    },
    {
        "type_to_expr_pair",
        Type_type_to_expr_pair
    },
    {
        "type_to_expr_pair_w_comp",
        Type_type_to_expr_pair_w_comp
    },
    {
        "type_to_expr_scope",
        Type_type_to_expr_scope
    },
    {
        "type_from_expr",
        Type_type_from_expr
    },
    {
        "type_from_expr_scope",
        Type_type_from_expr_scope
    },
    {
        "type_from_expr_digit",
        Type_type_from_expr_digit
    },
    {
        "type_from_expr_instanceof",
        Type_type_from_expr_instanceof
    },
    {
        "type_from_expr_childof",
        Type_type_from_expr_childof
    },
    {
        "type_from_expr_pair",
        Type_type_from_expr_pair
    },
    {
        "type_from_expr_pair_w_comp",
        Type_type_from_expr_pair_w_comp
    },
    {
        "entity_str",
        Type_entity_str
    },
    {
        "entity_path_str",
        Type_entity_path_str
    },
    {
        "entity_instanceof_str",
        Type_entity_instanceof_str
    },
    {
        "entity_childof_str",
        Type_entity_childof_str
    },
    {
        "entity_pair_str",
        Type_entity_pair_str
    },
    {
        "entity_switch_str",
        Type_entity_switch_str
    },
    {
        "entity_case_str",
        Type_entity_case_str
    },
    {
        "entity_and_str",
        Type_entity_and_str
    },
    {
        "entity_or_str",
        Type_entity_or_str
    },
    {
        "entity_xor_str",
        Type_entity_xor_str
    },
    {
        "entity_not_str",
        Type_entity_not_str
    },
    {
        "entity_str_small_buffer",
        Type_entity_str_small_buffer
    },
    {
        "role_childof_str",
        Type_role_childof_str
    },
    {
        "role_instanceof_str",
        Type_role_instanceof_str
    },
    {
        "role_pair_str",
        Type_role_pair_str
    },
    {
        "role_switch_str",
        Type_role_switch_str
    },
    {
        "role_case_str",
        Type_role_case_str
    },
    {
        "role_and_str",
        Type_role_and_str
    },
    {
        "role_or_str",
        Type_role_or_str
    },
    {
        "role_xor_str",
        Type_role_xor_str
    },
    {
        "role_not_str",
        Type_role_not_str
    },
    {
        "role_owned_str",
        Type_role_owned_str
    },
    {
        "role_disabled_str",
        Type_role_disabled_str
    },
    {
        "large_type_expr",
        Type_large_type_expr
    },
    {
        "large_type_expr_limit",
        Type_large_type_expr_limit
    }
};

bake_test_case Run_testcases[] = {
    {
        "run",
        Run_run
    },
    {
        "run_w_param",
        Run_run_w_param
    },
    {
        "run_no_match",
        Run_run_no_match
    },
    {
        "run_w_offset",
        Run_run_w_offset
    },
    {
        "run_w_offset_skip_1_archetype",
        Run_run_w_offset_skip_1_archetype
    },
    {
        "run_w_offset_skip_1_archetype_plus_one",
        Run_run_w_offset_skip_1_archetype_plus_one
    },
    {
        "run_w_offset_skip_2_archetypes",
        Run_run_w_offset_skip_2_archetypes
    },
    {
        "run_w_limit_skip_1_archetype",
        Run_run_w_limit_skip_1_archetype
    },
    {
        "run_w_limit_skip_1_archetype_minus_one",
        Run_run_w_limit_skip_1_archetype_minus_one
    },
    {
        "run_w_limit_skip_2_archetypes",
        Run_run_w_limit_skip_2_archetypes
    },
    {
        "run_w_offset_1_limit_max",
        Run_run_w_offset_1_limit_max
    },
    {
        "run_w_offset_1_limit_minus_1",
        Run_run_w_offset_1_limit_minus_1
    },
    {
        "run_w_offset_2_type_limit_max",
        Run_run_w_offset_2_type_limit_max
    },
    {
        "run_w_offset_2_type_limit_minus_1",
        Run_run_w_offset_2_type_limit_minus_1
    },
    {
        "run_w_limit_1_all_offsets",
        Run_run_w_limit_1_all_offsets
    },
    {
        "run_w_offset_out_of_bounds",
        Run_run_w_offset_out_of_bounds
    },
    {
        "run_w_limit_out_of_bounds",
        Run_run_w_limit_out_of_bounds
    },
    {
        "run_w_component_filter",
        Run_run_w_component_filter
    },
    {
        "run_w_type_filter_of_2",
        Run_run_w_type_filter_of_2
    },
    {
        "run_w_container_filter",
        Run_run_w_container_filter
    },
    {
        "run_comb_10_entities_1_type",
        Run_run_comb_10_entities_1_type
    },
    {
        "run_comb_10_entities_2_types",
        Run_run_comb_10_entities_2_types
    },
    {
        "run_w_interrupt",
        Run_run_w_interrupt
    },
    {
        "run_staging",
        Run_run_staging
    }
};

bake_test_case MultiThread_testcases[] = {
    {
        "2_thread_1_entity",
        MultiThread_2_thread_1_entity
    },
    {
        "2_thread_2_entity",
        MultiThread_2_thread_2_entity
    },
    {
        "2_thread_5_entity",
        MultiThread_2_thread_5_entity
    },
    {
        "2_thread_10_entity",
        MultiThread_2_thread_10_entity
    },
    {
        "3_thread_1_entity",
        MultiThread_3_thread_1_entity
    },
    {
        "3_thread_2_entity",
        MultiThread_3_thread_2_entity
    },
    {
        "3_thread_5_entity",
        MultiThread_3_thread_5_entity
    },
    {
        "3_thread_10_entity",
        MultiThread_3_thread_10_entity
    },
    {
        "4_thread_1_entity",
        MultiThread_4_thread_1_entity
    },
    {
        "4_thread_2_entity",
        MultiThread_4_thread_2_entity
    },
    {
        "4_thread_5_entity",
        MultiThread_4_thread_5_entity
    },
    {
        "4_thread_10_entity",
        MultiThread_4_thread_10_entity
    },
    {
        "5_thread_1_entity",
        MultiThread_5_thread_1_entity
    },
    {
        "5_thread_2_entity",
        MultiThread_5_thread_2_entity
    },
    {
        "5_thread_5_entity",
        MultiThread_5_thread_5_entity
    },
    {
        "5_thread_10_entity",
        MultiThread_5_thread_10_entity
    },
    {
        "6_thread_1_entity",
        MultiThread_6_thread_1_entity
    },
    {
        "6_thread_2_entity",
        MultiThread_6_thread_2_entity
    },
    {
        "6_thread_5_entity",
        MultiThread_6_thread_5_entity
    },
    {
        "6_thread_10_entity",
        MultiThread_6_thread_10_entity
    },
    {
        "2_thread_test_combs_100_entity",
        MultiThread_2_thread_test_combs_100_entity
    },
    {
        "3_thread_test_combs_100_entity",
        MultiThread_3_thread_test_combs_100_entity
    },
    {
        "4_thread_test_combs_100_entity",
        MultiThread_4_thread_test_combs_100_entity
    },
    {
        "5_thread_test_combs_100_entity",
        MultiThread_5_thread_test_combs_100_entity
    },
    {
        "6_thread_test_combs_100_entity",
        MultiThread_6_thread_test_combs_100_entity
    },
    {
        "2_thread_test_combs_100_entity_2_types",
        MultiThread_2_thread_test_combs_100_entity_2_types
    },
    {
        "3_thread_test_combs_100_entity_2_types",
        MultiThread_3_thread_test_combs_100_entity_2_types
    },
    {
        "4_thread_test_combs_100_entity_2_types",
        MultiThread_4_thread_test_combs_100_entity_2_types
    },
    {
        "5_thread_test_combs_100_entity_2_types",
        MultiThread_5_thread_test_combs_100_entity_2_types
    },
    {
        "6_thread_test_combs_100_entity_2_types",
        MultiThread_6_thread_test_combs_100_entity_2_types
    },
    {
        "change_thread_count",
        MultiThread_change_thread_count
    },
    {
        "multithread_quit",
        MultiThread_multithread_quit
    },
    {
        "schedule_w_tasks",
        MultiThread_schedule_w_tasks
    },
    {
        "reactive_system",
        MultiThread_reactive_system
    },
    {
        "fini_after_set_threads",
        MultiThread_fini_after_set_threads
    }
};

bake_test_case DeferredActions_testcases[] = {
    {
        "defer_new",
        DeferredActions_defer_new
    },
    {
        "defer_bulk_new",
        DeferredActions_defer_bulk_new
    },
    {
        "defer_bulk_new_w_data",
        DeferredActions_defer_bulk_new_w_data
    },
    {
        "defer_bulk_new_w_data_pair",
        DeferredActions_defer_bulk_new_w_data_pair
    },
    {
        "defer_bulk_new_two",
        DeferredActions_defer_bulk_new_two
    },
    {
        "defer_bulk_new_w_data_two",
        DeferredActions_defer_bulk_new_w_data_two
    },
    {
        "defer_add",
        DeferredActions_defer_add
    },
    {
        "defer_add_two",
        DeferredActions_defer_add_two
    },
    {
        "defer_remove",
        DeferredActions_defer_remove
    },
    {
        "defer_remove_two",
        DeferredActions_defer_remove_two
    },
    {
        "defer_set",
        DeferredActions_defer_set
    },
    {
        "defer_delete",
        DeferredActions_defer_delete
    },
    {
        "defer_twice",
        DeferredActions_defer_twice
    },
    {
        "defer_twice_in_progress",
        DeferredActions_defer_twice_in_progress
    },
    {
        "run_w_defer",
        DeferredActions_run_w_defer
    },
    {
        "system_in_progress_w_defer",
        DeferredActions_system_in_progress_w_defer
    },
    {
        "defer_get_mut_no_modify",
        DeferredActions_defer_get_mut_no_modify
    },
    {
        "defer_get_mut_w_modify",
        DeferredActions_defer_get_mut_w_modify
    },
    {
        "defer_modify",
        DeferredActions_defer_modify
    },
    {
        "defer_set_pair",
        DeferredActions_defer_set_pair
    },
    {
        "defer_clear",
        DeferredActions_defer_clear
    },
    {
        "defer_add_after_delete",
        DeferredActions_defer_add_after_delete
    },
    {
        "defer_set_after_delete",
        DeferredActions_defer_set_after_delete
    },
    {
        "defer_get_mut_after_delete",
        DeferredActions_defer_get_mut_after_delete
    },
    {
        "defer_get_mut_after_delete_2nd_to_last",
        DeferredActions_defer_get_mut_after_delete_2nd_to_last
    },
    {
        "defer_add_child_to_deleted_parent",
        DeferredActions_defer_add_child_to_deleted_parent
    },
    {
        "recreate_deleted_entity_while_deferred",
        DeferredActions_recreate_deleted_entity_while_deferred
    },
    {
        "discard_add",
        DeferredActions_discard_add
    },
    {
        "discard_remove",
        DeferredActions_discard_remove
    },
    {
        "discard_add_two",
        DeferredActions_discard_add_two
    },
    {
        "discard_remove_two",
        DeferredActions_discard_remove_two
    },
    {
        "discard_child",
        DeferredActions_discard_child
    },
    {
        "discard_child_w_add",
        DeferredActions_discard_child_w_add
    },
    {
        "defer_return_value",
        DeferredActions_defer_return_value
    },
    {
        "defer_get_mut_pair",
        DeferredActions_defer_get_mut_pair
    },
    {
        "async_stage_add",
        DeferredActions_async_stage_add
    },
    {
        "async_stage_add_twice",
        DeferredActions_async_stage_add_twice
    },
    {
        "async_stage_remove",
        DeferredActions_async_stage_remove
    },
    {
        "async_stage_clear",
        DeferredActions_async_stage_clear
    },
    {
        "async_stage_delete",
        DeferredActions_async_stage_delete
    },
    {
        "async_stage_new",
        DeferredActions_async_stage_new
    },
    {
        "async_stage_no_get",
        DeferredActions_async_stage_no_get
    },
    {
        "async_stage_readonly",
        DeferredActions_async_stage_readonly
    },
    {
        "async_stage_is_async",
        DeferredActions_async_stage_is_async
    },
    {
        "register_component_while_in_progress",
        DeferredActions_register_component_while_in_progress
    },
    {
        "register_component_while_staged",
        DeferredActions_register_component_while_staged
    },
    {
        "register_component_while_deferred",
        DeferredActions_register_component_while_deferred
    },
    {
        "defer_enable",
        DeferredActions_defer_enable
    },
    {
        "defer_disable",
        DeferredActions_defer_disable
    }
};

bake_test_case SingleThreadStaging_testcases[] = {
    {
        "new_empty",
        SingleThreadStaging_new_empty
    },
    {
        "new_w_component",
        SingleThreadStaging_new_w_component
    },
    {
        "new_w_type_of_2",
        SingleThreadStaging_new_w_type_of_2
    },
    {
        "new_empty_w_count",
        SingleThreadStaging_new_empty_w_count
    },
    {
        "new_component_w_count",
        SingleThreadStaging_new_component_w_count
    },
    {
        "new_type_w_count",
        SingleThreadStaging_new_type_w_count
    },
    {
        "add_to_new_empty",
        SingleThreadStaging_add_to_new_empty
    },
    {
        "2_add_to_new_empty",
        SingleThreadStaging_2_add_to_new_empty
    },
    {
        "add_remove_same_to_new_empty",
        SingleThreadStaging_add_remove_same_to_new_empty
    },
    {
        "add_remove_2_same_to_new_empty",
        SingleThreadStaging_add_remove_2_same_to_new_empty
    },
    {
        "add_remove_same_to_new_w_component",
        SingleThreadStaging_add_remove_same_to_new_w_component
    },
    {
        "2_add_1_remove_to_new_empty",
        SingleThreadStaging_2_add_1_remove_to_new_empty
    },
    {
        "2_add_1_remove_same_to_new_empty",
        SingleThreadStaging_2_add_1_remove_same_to_new_empty
    },
    {
        "clone",
        SingleThreadStaging_clone
    },
    {
        "clone_w_value",
        SingleThreadStaging_clone_w_value
    },
    {
        "add_to_current",
        SingleThreadStaging_add_to_current
    },
    {
        "2_add_to_current",
        SingleThreadStaging_2_add_to_current
    },
    {
        "remove_from_current",
        SingleThreadStaging_remove_from_current
    },
    {
        "remove_2_from_current",
        SingleThreadStaging_remove_2_from_current
    },
    {
        "add_remove_same_to_current",
        SingleThreadStaging_add_remove_same_to_current
    },
    {
        "add_remove_same_existing_to_current",
        SingleThreadStaging_add_remove_same_existing_to_current
    },
    {
        "remove_add_same_to_current",
        SingleThreadStaging_remove_add_same_to_current
    },
    {
        "remove_add_same_existing_to_current",
        SingleThreadStaging_remove_add_same_existing_to_current
    },
    {
        "add_remove_2_same_to_current",
        SingleThreadStaging_add_remove_2_same_to_current
    },
    {
        "add_remove_2_same_existing_to_current",
        SingleThreadStaging_add_remove_2_same_existing_to_current
    },
    {
        "remove_add_2_same_to_current",
        SingleThreadStaging_remove_add_2_same_to_current
    },
    {
        "remove_add_2_same_existing_to_current",
        SingleThreadStaging_remove_add_2_same_existing_to_current
    },
    {
        "add_remove_different_to_current",
        SingleThreadStaging_add_remove_different_to_current
    },
    {
        "add_remove_add_same_to_current",
        SingleThreadStaging_add_remove_add_same_to_current
    },
    {
        "2_add_1_remove_to_current",
        SingleThreadStaging_2_add_1_remove_to_current
    },
    {
        "1_add_2_remove_to_current",
        SingleThreadStaging_1_add_2_remove_to_current
    },
    {
        "delete_current",
        SingleThreadStaging_delete_current
    },
    {
        "delete_even",
        SingleThreadStaging_delete_even
    },
    {
        "delete_new_empty",
        SingleThreadStaging_delete_new_empty
    },
    {
        "delete_new_w_component",
        SingleThreadStaging_delete_new_w_component
    },
    {
        "set_current",
        SingleThreadStaging_set_current
    },
    {
        "set_new_empty",
        SingleThreadStaging_set_new_empty
    },
    {
        "set_new_w_component",
        SingleThreadStaging_set_new_w_component
    },
    {
        "set_existing_new_w_component",
        SingleThreadStaging_set_existing_new_w_component
    },
    {
        "set_new_after_add",
        SingleThreadStaging_set_new_after_add
    },
    {
        "remove_after_set",
        SingleThreadStaging_remove_after_set
    },
    {
        "delete_after_set",
        SingleThreadStaging_delete_after_set
    },
    {
        "add_to_current_in_on_add",
        SingleThreadStaging_add_to_current_in_on_add
    },
    {
        "remove_from_current_in_on_add",
        SingleThreadStaging_remove_from_current_in_on_add
    },
    {
        "remove_added_component_in_on_add",
        SingleThreadStaging_remove_added_component_in_on_add
    },
    {
        "match_table_created_in_progress",
        SingleThreadStaging_match_table_created_in_progress
    },
    {
        "match_table_created_w_new_in_progress",
        SingleThreadStaging_match_table_created_w_new_in_progress
    },
    {
        "match_table_created_w_new_in_on_set",
        SingleThreadStaging_match_table_created_w_new_in_on_set
    },
    {
        "merge_table_w_container_added_in_progress",
        SingleThreadStaging_merge_table_w_container_added_in_progress
    },
    {
        "merge_table_w_container_added_on_set",
        SingleThreadStaging_merge_table_w_container_added_on_set
    },
    {
        "merge_table_w_container_added_on_set_reverse",
        SingleThreadStaging_merge_table_w_container_added_on_set_reverse
    },
    {
        "merge_after_tasks",
        SingleThreadStaging_merge_after_tasks
    },
    {
        "override_after_remove_in_progress",
        SingleThreadStaging_override_after_remove_in_progress
    },
    {
        "get_parent_in_progress",
        SingleThreadStaging_get_parent_in_progress
    },
    {
        "merge_once",
        SingleThreadStaging_merge_once
    },
    {
        "clear_stage_after_merge",
        SingleThreadStaging_clear_stage_after_merge
    },
    {
        "get_mutable",
        SingleThreadStaging_get_mutable
    },
    {
        "get_mutable_from_main",
        SingleThreadStaging_get_mutable_from_main
    },
    {
        "get_mutable_w_add",
        SingleThreadStaging_get_mutable_w_add
    },
    {
        "on_add_after_new_type_in_progress",
        SingleThreadStaging_on_add_after_new_type_in_progress
    },
    {
        "new_type_from_entity",
        SingleThreadStaging_new_type_from_entity
    },
    {
        "existing_type_from_entity",
        SingleThreadStaging_existing_type_from_entity
    },
    {
        "new_type_add",
        SingleThreadStaging_new_type_add
    },
    {
        "existing_type_add",
        SingleThreadStaging_existing_type_add
    },
    {
        "lock_table",
        SingleThreadStaging_lock_table
    },
    {
        "recursive_lock_table",
        SingleThreadStaging_recursive_lock_table
    },
    {
        "modify_after_lock",
        SingleThreadStaging_modify_after_lock
    }
};

bake_test_case MultiThreadStaging_testcases[] = {
    {
        "2_threads_add_to_current",
        MultiThreadStaging_2_threads_add_to_current
    },
    {
        "3_threads_add_to_current",
        MultiThreadStaging_3_threads_add_to_current
    },
    {
        "4_threads_add_to_current",
        MultiThreadStaging_4_threads_add_to_current
    },
    {
        "5_threads_add_to_current",
        MultiThreadStaging_5_threads_add_to_current
    },
    {
        "6_threads_add_to_current",
        MultiThreadStaging_6_threads_add_to_current
    },
    {
        "2_threads_on_add",
        MultiThreadStaging_2_threads_on_add
    },
    {
        "new_w_count",
        MultiThreadStaging_new_w_count
    },
    {
        "custom_thread_auto_merge",
        MultiThreadStaging_custom_thread_auto_merge
    },
    {
        "custom_thread_manual_merge",
        MultiThreadStaging_custom_thread_manual_merge
    },
    {
        "custom_thread_partial_manual_merge",
        MultiThreadStaging_custom_thread_partial_manual_merge
    }
};

bake_test_case Stresstests_testcases[] = {
    {
        "create_1m_set_two_components",
        Stresstests_create_1m_set_two_components
    },
    {
        "create_delete_entity_random_components",
        Stresstests_create_delete_entity_random_components
    },
    {
        "set_entity_random_components",
        Stresstests_set_entity_random_components
    },
    {
        "create_delete_entity_random_components_staged",
        Stresstests_create_delete_entity_random_components_staged
    },
    {
        "set_entity_random_components_staged",
        Stresstests_set_entity_random_components_staged
    },
    {
        "create_delete_entity_random_components_2_threads",
        Stresstests_create_delete_entity_random_components_2_threads
    },
    {
        "set_entity_random_components_2_threads",
        Stresstests_set_entity_random_components_2_threads
    },
    {
        "create_delete_entity_random_components_6_threads",
        Stresstests_create_delete_entity_random_components_6_threads
    },
    {
        "set_entity_random_components_6_threads",
        Stresstests_set_entity_random_components_6_threads
    },
    {
        "create_delete_entity_random_components_12_threads",
        Stresstests_create_delete_entity_random_components_12_threads
    },
    {
        "set_entity_random_components_12_threads",
        Stresstests_set_entity_random_components_12_threads
    },
    {
        "create_2m_entities_1_comp",
        Stresstests_create_2m_entities_1_comp
    },
    {
        "create_2m_entities_bulk_1_comp",
        Stresstests_create_2m_entities_bulk_1_comp
    },
    {
        "add_1k_tags",
        Stresstests_add_1k_tags
    },
    {
        "create_1m_set_two_components",
        Stresstests_create_1m_set_two_components
    }
};

bake_test_case Snapshot_testcases[] = {
    {
        "simple_snapshot",
        Snapshot_simple_snapshot
    },
    {
        "snapshot_after_new",
        Snapshot_snapshot_after_new
    },
    {
        "snapshot_after_delete",
        Snapshot_snapshot_after_delete
    },
    {
        "snapshot_after_new_type",
        Snapshot_snapshot_after_new_type
    },
    {
        "snapshot_after_add",
        Snapshot_snapshot_after_add
    },
    {
        "snapshot_after_remove",
        Snapshot_snapshot_after_remove
    },
    {
        "snapshot_w_include_filter",
        Snapshot_snapshot_w_include_filter
    },
    {
        "snapshot_w_exclude_filter",
        Snapshot_snapshot_w_exclude_filter
    },
    {
        "snapshot_w_filter_after_new",
        Snapshot_snapshot_w_filter_after_new
    },
    {
        "snapshot_w_filter_after_delete",
        Snapshot_snapshot_w_filter_after_delete
    },
    {
        "snapshot_free_empty",
        Snapshot_snapshot_free_empty
    },
    {
        "snapshot_free",
        Snapshot_snapshot_free
    },
    {
        "snapshot_free_filtered",
        Snapshot_snapshot_free_filtered
    },
    {
        "snapshot_activate_table_w_filter",
        Snapshot_snapshot_activate_table_w_filter
    },
    {
        "snapshot_copy",
        Snapshot_snapshot_copy
    },
    {
        "snapshot_copy_filtered",
        Snapshot_snapshot_copy_filtered
    },
    {
        "snapshot_copy_w_filter",
        Snapshot_snapshot_copy_w_filter
    },
    {
        "snapshot_get_ref_after_restore",
        Snapshot_snapshot_get_ref_after_restore
    },
    {
        "new_after_snapshot",
        Snapshot_new_after_snapshot
    },
    {
        "new_empty_after_snapshot",
        Snapshot_new_empty_after_snapshot
    },
    {
        "add_after_snapshot",
        Snapshot_add_after_snapshot
    },
    {
        "delete_after_snapshot",
        Snapshot_delete_after_snapshot
    },
    {
        "set_after_snapshot",
        Snapshot_set_after_snapshot
    },
    {
        "restore_recycled",
        Snapshot_restore_recycled
    },
    {
        "snapshot_w_new_in_onset",
        Snapshot_snapshot_w_new_in_onset
    },
    {
        "snapshot_w_new_in_onset_in_snapshot_table",
        Snapshot_snapshot_w_new_in_onset_in_snapshot_table
    }
};

bake_test_case ReaderWriter_testcases[] = {
    {
        "simple",
        ReaderWriter_simple
    },
    {
        "id",
        ReaderWriter_id
    },
    {
        "id_w_simple",
        ReaderWriter_id_w_simple
    },
    {
        "unaligned",
        ReaderWriter_unaligned
    },
    {
        "empty",
        ReaderWriter_empty
    },
    {
        "tag",
        ReaderWriter_tag
    },
    {
        "simple_w_tag",
        ReaderWriter_simple_w_tag
    },
    {
        "tag_w_simple",
        ReaderWriter_tag_w_simple
    },
    {
        "empty_parent",
        ReaderWriter_empty_parent
    },
    {
        "parent",
        ReaderWriter_parent
    },
    {
        "simple_w_parent",
        ReaderWriter_simple_w_parent
    },
    {
        "inheritance",
        ReaderWriter_inheritance
    },
    {
        "simple_w_inheritance",
        ReaderWriter_simple_w_inheritance
    },
    {
        "deserialize_twice",
        ReaderWriter_deserialize_twice
    },
    {
        "entity_conflict",
        ReaderWriter_entity_conflict
    },
    {
        "snapshot_reader_simple",
        ReaderWriter_snapshot_reader_simple
    },
    {
        "snapshot_reader_id",
        ReaderWriter_snapshot_reader_id
    },
    {
        "read_zero_size",
        ReaderWriter_read_zero_size
    },
    {
        "write_zero_size",
        ReaderWriter_write_zero_size
    },
    {
        "invalid_header",
        ReaderWriter_invalid_header
    },
    {
        "recycled_id",
        ReaderWriter_recycled_id
    },
    {
        "new_component_after_restore",
        ReaderWriter_new_component_after_restore
    },
    {
        "delete_all_after_restore",
        ReaderWriter_delete_all_after_restore
    }
};

bake_test_case FilterIter_testcases[] = {
    {
        "iter_one_table",
        FilterIter_iter_one_table
    },
    {
        "iter_two_tables",
        FilterIter_iter_two_tables
    },
    {
        "iter_two_comps",
        FilterIter_iter_two_comps
    },
    {
        "iter_snapshot_one_table",
        FilterIter_iter_snapshot_one_table
    },
    {
        "iter_snapshot_two_tables",
        FilterIter_iter_snapshot_two_tables
    },
    {
        "iter_snapshot_two_comps",
        FilterIter_iter_snapshot_two_comps
    },
    {
        "iter_snapshot_filtered_table",
        FilterIter_iter_snapshot_filtered_table
    },
    {
        "iter_get_component_index",
        FilterIter_iter_get_component_index
    },
    {
        "iter_get_component_size",
        FilterIter_iter_get_component_size
    },
    {
        "iter_get_tag_index",
        FilterIter_iter_get_tag_index
    },
    {
        "iter_get_tag_size",
        FilterIter_iter_get_tag_size
    },
    {
        "iter_get_tag_column",
        FilterIter_iter_get_tag_column
    }
};

bake_test_case Modules_testcases[] = {
    {
        "simple_module",
        Modules_simple_module
    },
    {
        "import_module_from_system",
        Modules_import_module_from_system
    },
    {
        "import_again",
        Modules_import_again
    },
    {
        "scoped_component",
        Modules_scoped_component
    },
    {
        "scoped_tag",
        Modules_scoped_tag
    },
    {
        "scoped_system",
        Modules_scoped_system
    },
    {
        "scoped_entity",
        Modules_scoped_entity
    },
    {
        "name_prefix_component",
        Modules_name_prefix_component
    },
    {
        "name_prefix_tag",
        Modules_name_prefix_tag
    },
    {
        "name_prefix_system",
        Modules_name_prefix_system
    },
    {
        "name_prefix_entity",
        Modules_name_prefix_entity
    },
    {
        "name_prefix_type",
        Modules_name_prefix_type
    },
    {
        "name_prefix_prefab",
        Modules_name_prefix_prefab
    },
    {
        "name_prefix_pipeline",
        Modules_name_prefix_pipeline
    },
    {
        "name_prefix_trigger",
        Modules_name_prefix_trigger
    },
    {
        "name_prefix_underscore",
        Modules_name_prefix_underscore
    },
    {
        "lookup_by_symbol",
        Modules_lookup_by_symbol
    },
    {
        "import_type",
        Modules_import_type
    },
    {
        "nested_module",
        Modules_nested_module
    },
    {
        "module_tag_on_namespace",
        Modules_module_tag_on_namespace
    }
};

bake_test_case DirectAccess_testcases[] = {
    {
        "get_table_from_str",
        DirectAccess_get_table_from_str
    },
    {
        "get_table_from_type",
        DirectAccess_get_table_from_type
    },
    {
        "insert_record",
        DirectAccess_insert_record
    },
    {
        "insert_record_w_entity",
        DirectAccess_insert_record_w_entity
    },
    {
        "table_count",
        DirectAccess_table_count
    },
    {
        "find_column",
        DirectAccess_find_column
    },
    {
        "get_column",
        DirectAccess_get_column
    },
    {
        "get_empty_column",
        DirectAccess_get_empty_column
    },
    {
        "set_column",
        DirectAccess_set_column
    },
    {
        "delete_column",
        DirectAccess_delete_column
    },
    {
        "delete_column_explicit",
        DirectAccess_delete_column_explicit
    },
    {
        "delete_column_w_dtor",
        DirectAccess_delete_column_w_dtor
    },
    {
        "copy_to",
        DirectAccess_copy_to
    },
    {
        "copy_pod_to",
        DirectAccess_copy_pod_to
    },
    {
        "move_to",
        DirectAccess_move_to
    },
    {
        "copy_to_no_copy",
        DirectAccess_copy_to_no_copy
    },
    {
        "move_to_no_move",
        DirectAccess_move_to_no_move
    },
    {
        "find_record_not_exists",
        DirectAccess_find_record_not_exists
    },
    {
        "get_entities_empty_table",
        DirectAccess_get_entities_empty_table
    },
    {
        "get_records_empty_table",
        DirectAccess_get_records_empty_table
    },
    {
        "get_column_empty_table",
        DirectAccess_get_column_empty_table
    },
    {
        "delete_column_empty_table",
        DirectAccess_delete_column_empty_table
    },
    {
        "get_record_column_empty_table",
        DirectAccess_get_record_column_empty_table
    },
    {
        "has_module",
        DirectAccess_has_module
    }
};

bake_test_case Internals_testcases[] = {
    {
        "deactivate_table",
        Internals_deactivate_table
    },
    {
        "activate_table",
        Internals_activate_table
    },
    {
        "activate_deactivate_table",
        Internals_activate_deactivate_table
    },
    {
        "activate_deactivate_reactive",
        Internals_activate_deactivate_reactive
    },
    {
        "activate_deactivate_activate_other",
        Internals_activate_deactivate_activate_other
    },
    {
        "no_double_system_table_after_merge",
        Internals_no_double_system_table_after_merge
    },
    {
        "recreate_deleted_table",
        Internals_recreate_deleted_table
    },
    {
        "create_65k_tables",
        Internals_create_65k_tables
    }
};

bake_test_case Error_testcases[] = {
    {
        "abort",
        Error_abort
    },
    {
        "abort_w_param",
        Error_abort_w_param
    },
    {
        "override_abort",
        Error_override_abort
    },
    {
        "assert_true",
        Error_assert_true
    },
    {
        "assert_false",
        Error_assert_false
    },
    {
        "assert_false_w_param",
        Error_assert_false_w_param
    },
    {
        "error_codes",
        Error_error_codes
    },
    {
        "log_dbg",
        Error_log_dbg
    },
    {
        "log_log",
        Error_log_log
    },
    {
        "log_warning",
        Error_log_warning
    },
    {
        "log_error",
        Error_log_error
    }
};

bake_test_case Deprecated_testcases[] = {
    {
        "trait_type_str",
        Deprecated_trait_type_str
    }
};

static bake_test_suite suites[] = {
    {
        "Entity",
        NULL,
        NULL,
        39,
        Entity_testcases
    },
    {
        "New",
        New_setup,
        NULL,
        34,
        New_testcases
    },
    {
        "New_w_Count",
        NULL,
        NULL,
        21,
        New_w_Count_testcases
    },
    {
        "Add",
        NULL,
        NULL,
        37,
        Add_testcases
    },
    {
        "Switch",
        Switch_setup,
        NULL,
        29,
        Switch_testcases
    },
    {
        "EnabledComponents",
        NULL,
        NULL,
        37,
        EnabledComponents_testcases
    },
    {
        "Remove",
        NULL,
        NULL,
        15,
        Remove_testcases
    },
    {
        "Parser",
        NULL,
        NULL,
        107,
        Parser_testcases
    },
    {
        "GlobalComponentIds",
        NULL,
        NULL,
        7,
        GlobalComponentIds_testcases
    },
    {
        "Hierarchies",
        Hierarchies_setup,
        NULL,
        85,
        Hierarchies_testcases
    },
    {
        "Add_bulk",
        NULL,
        NULL,
        13,
        Add_bulk_testcases
    },
    {
        "Remove_bulk",
        NULL,
        NULL,
        12,
        Remove_bulk_testcases
    },
    {
        "Add_remove_bulk",
        NULL,
        NULL,
        4,
        Add_remove_bulk_testcases
    },
    {
        "Has",
        NULL,
        NULL,
        21,
        Has_testcases
    },
    {
        "Count",
        NULL,
        NULL,
        6,
        Count_testcases
    },
    {
        "Get_component",
        Get_component_setup,
        NULL,
        10,
        Get_component_testcases
    },
    {
        "Reference",
        Reference_setup,
        NULL,
        10,
        Reference_testcases
    },
    {
        "Delete",
        Delete_setup,
        NULL,
        26,
        Delete_testcases
    },
    {
        "OnDelete",
        NULL,
        NULL,
        45,
        OnDelete_testcases
    },
    {
        "Delete_w_filter",
        NULL,
        NULL,
        13,
        Delete_w_filter_testcases
    },
    {
        "Set",
        NULL,
        NULL,
        27,
        Set_testcases
    },
    {
        "Lookup",
        Lookup_setup,
        NULL,
        27,
        Lookup_testcases
    },
    {
        "Singleton",
        NULL,
        NULL,
        10,
        Singleton_testcases
    },
    {
        "Clone",
        NULL,
        NULL,
        14,
        Clone_testcases
    },
    {
        "ComponentLifecycle",
        ComponentLifecycle_setup,
        NULL,
        58,
        ComponentLifecycle_testcases
    },
    {
        "Pipeline",
        Pipeline_setup,
        NULL,
        26,
        Pipeline_testcases
    },
    {
        "SystemMisc",
        SystemMisc_setup,
        NULL,
        90,
        SystemMisc_testcases
    },
    {
        "Sorting",
        NULL,
        NULL,
        30,
        Sorting_testcases
    },
    {
        "Filter",
        NULL,
        NULL,
        13,
        Filter_testcases
    },
    {
        "Query",
        NULL,
        NULL,
        39,
        Query_testcases
    },
    {
        "Pairs",
        NULL,
        NULL,
        59,
        Pairs_testcases
    },
    {
        "Trigger",
        NULL,
        NULL,
        49,
        Trigger_testcases
    },
    {
        "Observer",
        NULL,
        NULL,
        25,
        Observer_testcases
    },
    {
        "TriggerOnAdd",
        TriggerOnAdd_setup,
        NULL,
        29,
        TriggerOnAdd_testcases
    },
    {
        "TriggerOnRemove",
        NULL,
        NULL,
        11,
        TriggerOnRemove_testcases
    },
    {
        "TriggerOnSet",
        NULL,
        NULL,
        12,
        TriggerOnSet_testcases
    },
    {
        "Monitor",
        NULL,
        NULL,
        7,
        Monitor_testcases
    },
    {
        "SystemOnSet",
        NULL,
        NULL,
        28,
        SystemOnSet_testcases
    },
    {
        "SystemUnSet",
        NULL,
        NULL,
        12,
        SystemUnSet_testcases
    },
    {
        "SystemPeriodic",
        NULL,
        NULL,
        53,
        SystemPeriodic_testcases
    },
    {
        "Timer",
        NULL,
        NULL,
        16,
        Timer_testcases
    },
    {
        "SystemOnDemand",
        NULL,
        NULL,
        27,
        SystemOnDemand_testcases
    },
    {
        "SystemCascade",
        NULL,
        NULL,
        12,
        SystemCascade_testcases
    },
    {
        "SystemManual",
        SystemManual_setup,
        NULL,
        4,
        SystemManual_testcases
    },
    {
        "Tasks",
        NULL,
        NULL,
        4,
        Tasks_testcases
    },
    {
        "Prefab",
        Prefab_setup,
        NULL,
        86,
        Prefab_testcases
    },
    {
        "System_w_FromContainer",
        System_w_FromContainer_setup,
        NULL,
        20,
        System_w_FromContainer_testcases
    },
    {
        "System_w_FromId",
        NULL,
        NULL,
        3,
        System_w_FromId_testcases
    },
    {
        "System_w_FromSystem",
        NULL,
        NULL,
        3,
        System_w_FromSystem_testcases
    },
    {
        "System_w_FromEntity",
        NULL,
        NULL,
        3,
        System_w_FromEntity_testcases
    },
    {
        "World",
        World_setup,
        NULL,
        33,
        World_testcases
    },
    {
        "Type",
        Type_setup,
        NULL,
        91,
        Type_testcases
    },
    {
        "Run",
        Run_setup,
        NULL,
        24,
        Run_testcases
    },
    {
        "MultiThread",
        MultiThread_setup,
        NULL,
        35,
        MultiThread_testcases
    },
    {
        "DeferredActions",
        NULL,
        NULL,
        49,
        DeferredActions_testcases
    },
    {
        "SingleThreadStaging",
        SingleThreadStaging_setup,
        NULL,
        67,
        SingleThreadStaging_testcases
    },
    {
        "MultiThreadStaging",
        MultiThreadStaging_setup,
        NULL,
        10,
        MultiThreadStaging_testcases
    },
    {
        "Stresstests",
        Stresstests_setup,
        NULL,
        15,
        Stresstests_testcases
    },
    {
        "Snapshot",
        NULL,
        NULL,
        26,
        Snapshot_testcases
    },
    {
        "ReaderWriter",
        NULL,
        NULL,
        23,
        ReaderWriter_testcases
    },
    {
        "FilterIter",
        NULL,
        NULL,
        12,
        FilterIter_testcases
    },
    {
        "Modules",
        Modules_setup,
        NULL,
        20,
        Modules_testcases
    },
    {
        "DirectAccess",
        NULL,
        NULL,
        24,
        DirectAccess_testcases
    },
    {
        "Internals",
        Internals_setup,
        NULL,
        8,
        Internals_testcases
    },
    {
        "Error",
        Error_setup,
        NULL,
        11,
        Error_testcases
    },
    {
        "Deprecated",
        NULL,
        NULL,
        1,
        Deprecated_testcases
    }
};

int main(int argc, char *argv[]) {
    ut_init(argv[0]);
    return bake_test_run("api", argc, argv, suites, 66);
}
