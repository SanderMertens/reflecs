
#include "private_api.h"

static
bool term_id_is_set(
    const ecs_term_id_t *id)
{
    return id->entity != 0 || id->name != NULL;
}

static
int resolve_identifier(
    const ecs_world_t *world,
    const char *name,
    const char *expr,
    ecs_term_id_t *identifier)
{
    if (!identifier->name) {
        return 0;
    }

    if (identifier->var == EcsVarDefault) {
        if (ecs_identifier_is_var(identifier->name)) {
            identifier->var = EcsVarIsVariable;
        }
    }

    if (identifier->var != EcsVarIsVariable) {
        if (ecs_identifier_is_0(identifier->name)) {
            identifier->entity = 0;
        } else {
            ecs_entity_t e = ecs_lookup_fullpath(world, identifier->name);
            if (!e) {
                ecs_parser_error(name, expr, 0,
                    "unresolved identifier '%s'", identifier->name);
                return -1;
            }

            /* Use OR, as entity may have already been populated with role */
            identifier->entity = e;
        }
    }

    return 0;
}

static
int term_resolve_ids(
    const ecs_world_t *world,
    const char *name,
    const char *expr,
    ecs_term_t *term)
{
    if (resolve_identifier(world, name, expr, &term->pred)) {
        return -1;
    }
    if (resolve_identifier(world, name, expr, &term->args[0])) {
        return -1;
    }
    if (resolve_identifier(world, name, expr, &term->args[1])) {
        return -1;
    }

    /* An explicitly set PAIR role indicates legacy behavior. In the legacy
     * query language a wildcard object means that the entity should have the
     * matched object by itself. This is incompatible with the new query parser.
     * For now, this behavior is mapped to a pair with a 0 object, but in the
     * future this behavior will be replaced with variables. */
    if (term->role == ECS_PAIR) {
        if (term->args[1].entity == EcsWildcard) {
            term->args[1].entity = 0;
            if (term->move) {
                ecs_os_free(term->args[1].name);
            }
            term->args[1].name = NULL;
        } else if (!term->args[1].entity) {
            term->args[1].entity = EcsWildcard;
        }
    }

    if (term->args[1].entity || term->role == ECS_PAIR) {
        term->id = ecs_pair(term->pred.entity, term->args[1].entity);
    } else {
        term->id = term->pred.entity;
    }

    return 0;
}

static
void filter_str_add_id(
    const ecs_world_t *world,
    ecs_strbuf_t *buf,
    ecs_term_id_t *id)
{
    if (id->name) {
        ecs_strbuf_appendstr(buf, id->name);
    } else if (id->entity) {
        char *path = ecs_get_fullpath(world, id->entity);
        ecs_strbuf_appendstr(buf, path);
        ecs_os_free(path);
    } else {
        ecs_strbuf_appendstr(buf, "0");
    }
}

static
void assert_matched_type_is_valid(
    ecs_cached_type_t *matched)
{
    ecs_assert(matched != NULL, ECS_INVALID_PARAMETER,  NULL);
    ecs_assert(matched->ids != NULL, ECS_INTERNAL_ERROR,  NULL);
    ecs_assert(matched->subjects != NULL, ECS_INTERNAL_ERROR,  NULL);
    ecs_assert(matched->sizes != NULL, ECS_INTERNAL_ERROR,  NULL);
    ecs_assert(matched->types != NULL, ECS_INTERNAL_ERROR,  NULL);
    ecs_assert(matched->type_map != NULL, ECS_INTERNAL_ERROR,  NULL);
}

bool ecs_filter_populate_from_type(
    ecs_world_t *world,
    const ecs_filter_t *filter,
    ecs_type_t type,
    ecs_cached_type_t *matched,
    bool first)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER,  NULL);
    ecs_assert(filter != NULL, ECS_INVALID_PARAMETER,  NULL);
    ecs_assert(type != NULL, ECS_INVALID_PARAMETER,  NULL);
    assert_matched_type_is_valid(matched);

    int32_t i, count = filter->term_count;
    ecs_term_t *terms = filter->terms;

    bool is_or = false;
    bool or_result = false;

    for (i = 0; i < count; i ++) {
        ecs_term_t *term = &terms[i];
        ecs_id_t id = term->id;
        ecs_oper_kind_t op = term->oper;
        ecs_entity_t subject = term->args[0].entity;
        ecs_type_t actual_type = type;

        if (matched) {
            matched->ids[i] = 0;
            matched->subjects[i] = 0;
            matched->type_map[i] = -1;
            matched->types[i] = NULL;
        }

        if (!is_or && op == EcsOr) {
            is_or = true;
            or_result = false;
        } else if (is_or && op != EcsOr) {
            if (!or_result) {
                return false;
            }

            is_or = false;
        }

        /* If no subject is provided, this term just passes an id */
        if (!subject) {
            if (matched) {
                matched->ids[i] = id;
            }
            continue;
        }

        /* If subject is not This, find component on entity */
        if (subject != EcsThis) {
            actual_type = ecs_get_type(world, subject);
        }

        if (subject == EcsThis) {
            subject = 0;
        }

        int32_t index = ecs_type_find_id(
            world, 
            actual_type, 
            first ? 0 : matched->type_map[i], /* offset search by prev index */ 
            id, 
            term->args[0].set.relation, /* set parameters for substitution */
            term->args[0].set.min_depth,
            term->args[0].set.max_depth,
            &subject /* contains the result of substitution, if necessary */
        );

        bool result = index != -1;
        if (term->oper == EcsNot) {
            result = !result;
        }

        if (op == EcsNot) {
            result = !result;
        }

        if (is_or) {
            or_result |= result;
        } else if (!result) {
            return false;
        }

        /* Get the actual id, which may be different from the term id if it is
         * a wildcard term. */
        id = ecs_vector_get(actual_type, ecs_id_t, index)[0];

        if (matched) {
            matched->ids[i] = id;
            matched->subjects[i] = subject;
            matched->type_map[i] = index;
            matched->types[i] = ecs_type_from_id(world, id);

            const EcsComponent *comp = ecs_get_component(world, id);
            if (comp) {
                matched->sizes[i] = comp->size;
            } else {
                matched->sizes[i] = 0;
            }
        }
    }

    return !is_or || or_result;
}

void ecs_filter_populate_from_table(
    ecs_world_t *world,
    const ecs_filter_t *filter,
    ecs_table_t *table,
    ecs_cached_type_t *matched,
    void **columns)
{
    ecs_assert(world != NULL, ECS_INVALID_PARAMETER,  NULL);
    ecs_assert(filter != NULL, ECS_INVALID_PARAMETER,  NULL);
    ecs_assert(table != NULL, ECS_INVALID_PARAMETER,  NULL);    
    assert_matched_type_is_valid(matched);

    ecs_data_t *data = ecs_table_get_data(table);

    int32_t i, count = filter->term_count;
    ecs_term_t *terms = filter->terms;

    for (i = 0; i < count; i ++) {
        ecs_term_t *term = &terms[i];

        columns[i] = NULL;

        if (term->oper == EcsNot) {
            /* Nothing to set for Not terms */
            continue;
        }

        int32_t index = matched->type_map[i];

        if (index >= table->column_count) {
            /* Term is not a component */
            ecs_assert(matched->sizes[i] == 0, ECS_INTERNAL_ERROR, NULL);
            continue;
        }
        
        if (index < 0) {
            /* Term is not retrieved from table */
            continue;
        }

        ecs_column_t *column = &data->columns[index];
        ecs_assert(column->size == matched->sizes[i], ECS_INTERNAL_ERROR, NULL);
        columns[i] = ecs_vector_first_t(column->data, column->size, 
            column->alignment);
    }
}

/* -- Public API -- */

bool ecs_identifier_is_0(
    const char *id)
{
    return id[0] == '0' && !id[1];
}

bool ecs_identifier_is_var(
    const char *id)
{
    if (id[0] == '_') {
        return true;
    }

    if (isdigit(id[0])) {
        return false;
    }

    const char *ptr;
    char ch;
    for (ptr = id; (ch = *ptr); ptr ++) {
        if (!isupper(ch) && ch != '_' && !isdigit(ch)) {
            return false;
        }
    }

    return true;
}

bool ecs_id_match(
    ecs_id_t id,
    ecs_id_t pattern)
{
    if (id == pattern) {
        return true;
    }

    if (ECS_HAS_ROLE(pattern, PAIR)) {
        if (!ECS_HAS_ROLE(id, PAIR)) {
            /* legacy roles that are now relations */
            if (!ECS_HAS_ROLE(id, INSTANCEOF) && !ECS_HAS_ROLE(id, CHILDOF)) {
                return false;
            }
        }

        ecs_entity_t id_rel = ECS_PAIR_RELATION(id);
        ecs_entity_t id_obj = ECS_PAIR_OBJECT(id);
        ecs_entity_t pattern_rel = ECS_PAIR_RELATION(pattern);
        ecs_entity_t pattern_obj = ECS_PAIR_OBJECT(pattern);

        if (pattern_rel == EcsWildcard) {
            if (pattern_obj == EcsWildcard || !pattern_obj || pattern_obj == id_obj) {
                return true;
            }
        } else if (!pattern_obj || pattern_obj == EcsWildcard) {
            if (pattern_rel == id_rel) {
                return true;
            }
        }
    } else {
        if ((id & ECS_ROLE_MASK) != (pattern & ECS_ROLE_MASK)) {
            return false;
        }

        if ((ECS_COMPONENT_MASK & pattern) == EcsWildcard) {
            return true;
        }
    }

    return false;
}

bool ecs_id_is_wildcard(
    ecs_id_t id)
{
    if (id == EcsWildcard) {
        return true;
    } else if (ECS_HAS_ROLE(id, PAIR)) {
        return ECS_PAIR_RELATION(id) == EcsWildcard || 
               ECS_PAIR_OBJECT(id) == EcsWildcard;
    }

    return false;
}

bool ecs_term_is_set(
    const ecs_term_t *term)
{
    return term->id != 0 || term_id_is_set(&term->pred);
}

bool ecs_term_is_trivial(
    ecs_term_t *term)
{
    if (term->args[0].entity != EcsThis) {
        return false;
    }

    if (term->args[0].set.mask != EcsDefaultSet) {
        return false;
    }

    if (term->oper != EcsAnd) {
        return false;
    }

    return true;
}

int ecs_term_finalize(
    const ecs_world_t *world,
    const char *name,
    const char *expr,
    ecs_term_t *term)
{
    if (term->id) {
        /* Allow for combining explicit object with id */
        if (term->args[1].name && !term->args[1].entity) {
            if (resolve_identifier(world, name, expr, &term->args[1])) {
                return -1;
            }
        }

        /* If other fields are set, make sure they are consistent with id */
        if (term->args[1].entity) {
            ecs_assert(term->pred.entity != 0, ECS_INVALID_PARAMETER, NULL);
            ecs_assert(term->id == 
                ecs_pair(term->pred.entity, term->args[1].entity), 
                    ECS_INVALID_PARAMETER, NULL);
        } else if (term->pred.entity) {
            /* If only predicate is set (not object) it must match the id
             * without any roles set. */
            ecs_assert(term->pred.entity == (term->id & ECS_COMPONENT_MASK), 
                ECS_INVALID_PARAMETER, NULL);
        }

        /* If id is set, check for pair and derive predicate and object */
        if (ECS_HAS_ROLE(term->id, PAIR)) {
            term->pred.entity = ECS_PAIR_RELATION(term->id);
            term->args[1].entity = ECS_PAIR_OBJECT(term->id);
        } else {
            term->pred.entity = term->id & ECS_COMPONENT_MASK;
        }

        if (!term->role) {
            term->role = term->id & ECS_ROLE_MASK;
        } else {
            /* If id already has a role set it should be equal to the provided
             * role */
            ecs_assert(!(term->id & ECS_ROLE_MASK) || 
                        (term->id & ECS_ROLE_MASK) == term->role, 
                            ECS_INVALID_PARAMETER, NULL);
        }      
    } else {
        if (term_resolve_ids(world, name, expr, term)) {
            /* One or more identifiers could not be resolved */
            return -1;
        }
    }

    /* role field should only set role bits */
    ecs_assert(term->role == (term->role & ECS_ROLE_MASK), 
        ECS_INVALID_PARAMETER, NULL);    

    term->id |= term->role;

    if (!term->args[0].entity && 
        term->args[0].set.mask != EcsNothing && 
        term->args[0].var != EcsVarIsVariable) 
    {
        term->args[0].entity = EcsThis;
    }

    if (term->args[0].set.mask & (EcsSuperSet | EcsSubSet)) {
        if (!term->args[0].set.relation) {
            term->args[0].set.relation = EcsIsA;
        }
    }

    return 0;
}

ecs_term_t ecs_term_copy(
    const ecs_term_t *src)
{
    ecs_term_t dst = *src;
    dst.name = ecs_os_strdup(src->name);
    dst.pred.name = ecs_os_strdup(src->pred.name);
    dst.args[0].name = ecs_os_strdup(src->args[0].name);
    dst.args[1].name = ecs_os_strdup(src->args[1].name);

    return dst;
}

ecs_term_t ecs_term_move(
    ecs_term_t *src)
{
    if (src->move) {
        ecs_term_t dst = *src;
        src->name = NULL;
        src->pred.name = NULL;
        src->args[0].name = NULL;
        src->args[1].name = NULL;
        return dst;
    } else {
        return ecs_term_copy(src);
    }
}

void ecs_term_fini(
    ecs_term_t *term)
{
    ecs_os_free(term->pred.name);
    ecs_os_free(term->args[0].name);
    ecs_os_free(term->args[1].name);
    ecs_os_free(term->name);
}

int ecs_filter_init(
    const ecs_world_t *world,
    ecs_filter_t *filter_out,
    const ecs_filter_desc_t *desc)    
{
    int i, term_count = 0;
    ecs_term_t *terms = desc->terms_buffer;
    const char *name = desc->name;
    const char *expr = desc->expr;

    ecs_filter_t f = {
        /* Temporarily set the fields to the values provided in desc, until the
         * filter has been validated. */
        .name = (char*)name,
        .expr = (char*)expr
    };

    if (terms) {
        terms = desc->terms_buffer;
        term_count = desc->terms_buffer_count;
    } else {
        terms = (ecs_term_t*)desc->terms;
        for (i = 0; i < ECS_FILTER_DESC_TERM_ARRAY_MAX; i ++) {
            if (!ecs_term_is_set(&terms[i])) {
                break;
            }

            term_count ++;
        }
    }

    /* Temporarily set array from desc to filter, until the filter has been
     * validated. */
    f.terms = terms;
    f.term_count = term_count;

    if (expr) {
#ifdef FLECS_PARSER
        int32_t buffer_count = 0;

        /* If terms have already been set, copy buffer to allocated one */
        if (terms && term_count) {
            terms = ecs_os_memdup(terms, term_count * ECS_SIZEOF(ecs_term_t));
            buffer_count = term_count;
        } else {
            terms = NULL;
        }

        /* Parse expression into array of terms */
        const char *ptr = desc->expr;
        ecs_term_t term = {0};
        while (ptr[0] && (ptr = ecs_parse_term(world, name, expr, ptr, &term))){
            if (!ecs_term_is_set(&term)) {
                break;
            }
            
            if (term_count == buffer_count) {
                buffer_count = buffer_count ? buffer_count * 2 : 8;
                terms = ecs_os_realloc(terms, 
                    buffer_count * ECS_SIZEOF(ecs_term_t));
            }

            terms[term_count] = term;
            term_count ++;
        }

        f.terms = terms;
        f.term_count = term_count;

        if (!ptr) {
            goto error;
        }
#else
        ecs_abort(ECS_UNSUPPORTED, "parser addon is not available");
#endif
    }

    /* If default substitution is enabled, replace DefaultSet with SuperSet */
    if (desc->substitute_default) {
        for (i = 0; i < term_count; i ++) {
            if (terms[i].args[0].set.mask == EcsDefaultSet) {
                terms[i].args[0].set.mask = EcsSuperSet | EcsSelf;
                terms[i].args[0].set.relation = EcsIsA;
            }            
        }
    }

    /* Ensure all fields are consistent and properly filled out */
    if (ecs_filter_finalize(world, &f)) {
        goto error;
    }

    /* Copy term resources. */
    if (term_count) {
        if (!f.expr) {
            f.terms = ecs_os_malloc(term_count * ECS_SIZEOF(ecs_term_t));
        }

        for (i = 0; i < term_count; i ++) {
            f.terms[i] = ecs_term_move(&terms[i]);
        }        
    } else {
        f.terms = NULL;
    }

    f.name = ecs_os_strdup(desc->name);
    f.expr = ecs_os_strdup(desc->expr);

    *filter_out = f;

    return 0;
error:
    /* NULL members that point to non-owned resources */
    if (!f.expr) {
        f.terms = NULL;
    }

    f.name = NULL;
    f.expr = NULL;

    ecs_filter_fini(&f);

    return -1;
}

int ecs_filter_finalize(
    const ecs_world_t *world,
    ecs_filter_t *f)
{
    int32_t i, term_count = f->term_count, actual_count = 0;
    ecs_term_t *terms = f->terms;
    bool is_or = false, prev_or = false;

    f->match_this = false;
    f->match_only_this = true;

    for (i = 0; i < term_count; i ++) {
        ecs_term_t *term = &terms[i];

        if (ecs_term_finalize(world, f->name, f->expr, term)) {
            return -1;
        }

        is_or = term->oper == EcsOr;
        actual_count += !(is_or && prev_or);
        term->index = actual_count - 1;
        prev_or = is_or;

        if (term->args[0].entity == EcsThis) {
            f->match_this = true;
            if (term->args[0].set.mask != EcsSelf) {
                f->match_only_this = false;
            }
        } else {
            f->match_only_this = false;
        }        
    }

    f->term_count_actual = actual_count;

    return 0;
}

char* ecs_filter_str(
    const ecs_world_t *world,
    const ecs_filter_t *filter)
{
    ecs_strbuf_t buf = ECS_STRBUF_INIT;

    ecs_term_t *terms = filter->terms;
    int32_t i, count = filter->term_count;
    int32_t or_count = 0;

    for (i = 0; i < count; i ++) {
        ecs_term_t *term = &terms[i];

        if (i) {
            if (terms[i - 1].oper == EcsOr && term->oper == EcsOr) {
                ecs_strbuf_appendstr(&buf, " || ");
            } else {
                ecs_strbuf_appendstr(&buf, ", ");
            }
        }

        if (or_count < 1) {
            if (term->inout == EcsIn) {
                ecs_strbuf_appendstr(&buf, "[in] ");
            } else if (term->inout == EcsInOut) {
                ecs_strbuf_appendstr(&buf, "[inout] ");
            } else if (term->inout == EcsOut) {
                ecs_strbuf_appendstr(&buf, "[out] ");
            }
        }

        if (term->role && term->role != ECS_PAIR) {
            ecs_strbuf_appendstr(&buf, ecs_role_str(term->role));
            ecs_strbuf_appendstr(&buf, " ");
        }

        if (term->oper == EcsOr) {
            or_count ++;
        } else {
            or_count = 0;
        }

        if (term->oper == EcsNot) {
            ecs_strbuf_appendstr(&buf, "!");
        } else if (term->oper == EcsOptional) {
            ecs_strbuf_appendstr(&buf, "?");
        }

        if (term->args[0].entity == EcsThis && term_id_is_set(&term->args[1])) {
            ecs_strbuf_appendstr(&buf, "(");
        }

        if (!term_id_is_set(&term->args[1]) && 
            (term->pred.entity != term->args[0].entity)) 
        {
            filter_str_add_id(world, &buf, &term->pred);

            if (!term_id_is_set(&term->args[0])) {
                ecs_strbuf_appendstr(&buf, "()");
            } else if (term->args[0].entity != EcsThis) {
                ecs_strbuf_appendstr(&buf, "(");
                filter_str_add_id(world, &buf, &term->args[0]);
            }

            if (term_id_is_set(&term->args[1])) {
                ecs_strbuf_appendstr(&buf, ", ");
                filter_str_add_id(world, &buf, &term->args[1]);
                ecs_strbuf_appendstr(&buf, ")");
            } else if (term->args[0].entity != EcsThis) {
                ecs_strbuf_appendstr(&buf, ")");
            }
        } else if (!term_id_is_set(&term->args[1])) {
            ecs_strbuf_appendstr(&buf, "$");
            filter_str_add_id(world, &buf, &term->pred);
        } else if (term_id_is_set(&term->args[1])) {
            filter_str_add_id(world, &buf, &term->pred);
            ecs_strbuf_appendstr(&buf, ", ");
            filter_str_add_id(world, &buf, &term->args[1]);
            ecs_strbuf_appendstr(&buf, ")");
        }
    }

    return ecs_strbuf_get(&buf);
}

void ecs_filter_fini(
    ecs_filter_t *filter) 
{
    if (filter->terms) {
        int i, count = filter->term_count;
        for (i = 0; i < count; i ++) {
            ecs_term_fini(&filter->terms[i]);
        }

        ecs_os_free(filter->terms);
    }

    ecs_os_free(filter->name);
    ecs_os_free(filter->expr);
}

bool ecs_filter_match_type(
    const ecs_world_t *world,
    const ecs_filter_t *filter,
    ecs_type_t type)
{
    return ecs_filter_populate_from_type(
        (ecs_world_t*)world, filter, type, NULL, true);
}

bool ecs_filter_match_entity(
    const ecs_world_t *world,
    const ecs_filter_t *filter,
    ecs_entity_t e)
{
    if (e) {
        return ecs_filter_match_type(world, filter, ecs_get_type(world, e));
    } else {
        return ecs_filter_match_type(world, filter, NULL);
    }
}

ecs_iter_t ecs_filter_iter(
    ecs_world_t *world,
    const ecs_filter_t *filter)
{
    int32_t i, term_count = filter->term_count;
    ecs_term_t *terms = filter->terms;
    int32_t min_count = -1;
    ecs_map_t *table_index = NULL;
    ecs_map_t *substitution_index = NULL;

    ecs_iter_t it = { 
        .world = world
    };
    ecs_filter_iter_t *iter = &it.private.iter.filter;
    iter->filter = filter;

    /* Find smallest set of tables to start iterating from */
    if (filter->match_this) {
        for (i = 0; i < term_count; i ++) {
            ecs_term_t *term = &terms[i];

            if (!ecs_term_is_trivial(term)) {
                continue;
            }

            ecs_id_t id = term->id;
            ecs_id_record_t *idr = ecs_get_id_record(world, id);
            if (idr) {
                int32_t count = ecs_map_count(idr->table_index);
                if (min_count == -1 || count < min_count) {
                    min_count = count;
                    table_index = idr->table_index;

                    if (term->args[0].set.mask & EcsSuperSet) {
                        idr = ecs_get_id_record(world, 
                            ecs_pair(term->args[0].set.relation, EcsWildcard));
                        substitution_index = idr->table_index;
                    }
                }
            } else {
                /* If one of the terms has no tables, the iterator won't return
                 * any data */
                iter->kind = EcsFilterIterNoData;
                return it;
            }
        }

        if (table_index || substitution_index) {
            iter->kind = EcsFilterIterEvalIndex;
            iter->table_index = table_index;
            iter->substitution_index = substitution_index;

            if (table_index) {
                iter->table_index_iter = ecs_map_iter(table_index);
            } else {
                iter->table_index_iter = ecs_map_iter(substitution_index);
            }
        } else {
            iter->kind = EcsFilterIterEvalAll;
            iter->tables = world->store.tables;
        }
    } else {
        iter->kind = EcsFilterIterEvalNone;
    }

    int32_t term_count_actual = filter->term_count_actual;
    if (term_count_actual <= ECS_ITER_TERM_STORAGE_SIZE) {
        ecs_iter_init_from_storage(&it);
        if (filter->match_only_this) {
            it.subjects = NULL;
        }
    } else {
        it.ids = ecs_os_malloc(term_count_actual * ECS_SIZEOF(ecs_id_t));
        it.sizes = ecs_os_malloc(term_count_actual * ECS_SIZEOF(size_t));
        it.types = ecs_os_malloc(term_count_actual * ECS_SIZEOF(ecs_type_t));
        it.type_map = ecs_os_malloc(term_count_actual * ECS_SIZEOF(int32_t*));
        it.columns = ecs_os_malloc(term_count_actual * ECS_SIZEOF(void*));
        
        if (!filter->match_only_this) {
            it.subjects = ecs_os_malloc(
                term_count_actual * ECS_SIZEOF(ecs_entity_t));
        }
    }
    
    return it;
}

bool ecs_filter_next(
    ecs_iter_t *it)
{
    /* There are three ways the filter can be iterated:
     * 1. The filter matches tables but there is no term that represents the
     *    superset of the filter. This can happen if a filter only contains Or
     *    or Optional terms.
     * 2. The filter matches tables and there is a term that represents the
     *    superset of all tables in the filter. The superset can be used as
     *    starting point for the iteration.
     * 3. The filter doesn't match tables and only matches components from
     *    entities stored in the filter.
     *
     * This requires three different iteration strategies:
     * 1. The iterator needs to match all tables in the world
     * 2. The iterator needs to match all tables in the found superset
     * 3. The iterator only needs to return once
     *
     * If option 2, the term may require superset substitution. In that case the
     * iterator may need to evaluate the component table as well as the table
     * for the relation used by the substitution. When evaluating the 
     * substitution tables, any tables that own the searched for component 
     * should be ignored.
     */
    ecs_filter_iter_t *iter = &it->private.iter.filter;
    ecs_filter_iter_kind_t kind = iter->kind;

    if (kind == EcsFilterIterNoData) {
        return false;
    }

    const ecs_filter_t *filter = iter->filter;
    ecs_world_t *world = it->world;

    ecs_cached_type_t cached_type = {
        .ids = it->ids,
        .subjects = it->subjects,
        .sizes = (ecs_size_t*)it->sizes,
        .types = it->types,
        .type_map = it->type_map
    };

    /* 3. The iterator doesn't match any tables but does yield data */
    if (kind == EcsFilterIterEvalNone) {
        if (iter->count == 1) {
            goto done;
        }

        if (ecs_filter_populate_from_type(
            world, filter, NULL, &cached_type, true)) 
        {
            it->table = NULL;
            goto yield;
        } else {
            goto done;
        }
    }

    do {
        ecs_table_t *table = NULL;
        ecs_type_t type = NULL;
        
        /* 1. The iterator needs to evaluate all tables */
        if (kind == EcsFilterIterEvalAll) {
            ecs_assert(iter->tables_iter > 0, ECS_INTERNAL_ERROR, NULL);
            table = ecs_sparse_get(
                iter->tables, ecs_table_t, (uint64_t)iter->tables_iter);
            iter->tables_iter ++;
        } else

        /* 2. The iterator needs to evaluate all tables in a table index */
        if (kind == EcsFilterIterEvalIndex) {
            ecs_table_record_t *tr = ecs_map_next(
                &iter->table_index_iter, ecs_table_record_t, NULL);
            if (!tr) {
                if (iter->table_index) {
                    iter->table_index = NULL;
                    if (iter->substitution_index) {
                        iter->table_index_iter = 
                            ecs_map_iter(iter->substitution_index);
                        tr = ecs_map_next(
                            &iter->table_index_iter, ecs_table_record_t, NULL);
                    }
                }
            }
            table = tr ? tr->table : NULL;
        }

        /* No more tables found, done iterating */
        if (!table) {
            goto done;
        }

        /* Skip empty tables */
        if (!ecs_table_count(table)) {
            continue;
        }
        
        type = table->type;

        /* Check if table matches fitler & populate iterator data */
        if (!ecs_filter_populate_from_type(
            world, filter, type, &cached_type, true))
        {
            continue;
        }

        /* Populate table columns */
        ecs_filter_populate_from_table(
            world, filter, table, &cached_type, it->columns);

        it->type = type;
        break;

    } while (true);

yield:
    iter->count ++;
    return true;

done:
    if (it->term_count_actual > ECS_ITER_TERM_STORAGE_SIZE) {
        ecs_os_free(it->ids);
        ecs_os_free(it->subjects);
        ecs_os_free(it->sizes);
        ecs_os_free(it->types);
        ecs_os_free(it->type_map);
        ecs_os_free(it->columns);
    }
    return false;
}
