#pragma once

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <iostream>
#include <type_traits>
#include <memory>
#include <cstdint>

namespace flecs {

/* -- Forward declarations and types -- */

using world_t = ecs_world_t;
using entity_t = ecs_entity_t;
using type_t = ecs_type_t;

class entity;
class type;

template <typename T>
class component_base;

/* -- Types -- */

enum system_kind {
    OnLoad = EcsOnLoad,
    PostLoad = EcsPostLoad,
    PreUpdate = EcsPreUpdate,
    OnUpdate = EcsOnUpdate,
    OnValidate = EcsOnValidate,
    PostUpdate = EcsPostUpdate,
    PreStore = EcsPreStore,
    OnStore = EcsOnStore,
    Manual = EcsManual,
    OnAdd = EcsOnAdd,
    OnRemove = EcsOnRemove,
    OnSet = EcsOnSet
};

/** Utility to protect against out of bound reads on component arrays */
template <typename T>
class column final {
public:
    column(T* array, size_t count)
        : m_array(array)
        , m_count(count) {}

    T& operator[](size_t index) {
        ecs_assert(index < m_count, ECS_COLUMN_INDEX_OUT_OF_RANGE, NULL);
        return m_array[index];
    }

private:
    T* m_array;
    size_t m_count;
};

/** Provides an integer range to iterate over */
template <typename T>
class range_iterator
{
public:
    range_iterator(T value)
        : m_value(value){}

    bool operator!=(range_iterator const& other) const
    {
        return m_value != other.m_value;
    }

    T const& operator*() const
    {
        return m_value;
    }

    range_iterator& operator++()
    {
        ++m_value;
        return *this;
    }

private:
    T m_value;
};

/** Wrapper around ecs_rows_t */
class rows final {
    using row_iterator = range_iterator<int>;
public:    
    rows(const ecs_rows_t *rows) : m_rows(rows) { 
        m_begin = 0;
        m_end = rows->count;
    }

    row_iterator begin() const {
        return row_iterator(m_begin);
    }

    row_iterator end() const {
        return row_iterator(m_end);
    }

    /* Number of entities to iterate over */
    uint32_t count() const {
        return m_rows->count;
    }

    /* Is column shared */
    bool is_shared(uint32_t column) const {
        return ecs_is_shared(m_rows, column);
    }

    /* Is column readonly */
    bool is_readonly(uint32_t column) const {
        return ecs_is_readonly(m_rows, column);
    }

    /* Obtain column source (0 if self) */
    entity column_source(uint32_t column) const;

    /* Obtain component/tag entity of column */
    entity column_entity(uint32_t column) const;

    /* Obtain type of column */
    flecs::type column_type(uint32_t column) const;

    /* Obtain type of table being iterated over */
    flecs::type table_type() const;

    /* Obtain untyped pointer to table column */
    void* table_column(uint32_t table_column) {
        return ecs_table_column(m_rows, table_column);
    }   

    /* Obtain column with a const type */
    template <typename T,
        typename std::enable_if<std::is_const<T>::value, void>::type* = nullptr>
    flecs::column<T> column(unsigned int column) const {
        return get_column<T>(column);
    }

    /* Obtain column with non-const type. Ensure that column is not readonly */
    template <typename T,
        typename std::enable_if<std::is_const<T>::value == false, void>::type* = nullptr>
    flecs::column<T> column(uint32_t column) const {
        ecs_assert(!ecs_is_readonly(m_rows, column), ECS_COLUMN_ACCESS_VIOLATION, NULL);
        return get_column<T>(column);
    }

    /* Get owned */
    template <typename T>
    flecs::column<T> owned(uint32_t column) const {
        ecs_assert(!ecs_is_shared(m_rows, column), ECS_COLUMN_IS_SHARED, NULL);
        return this->column<T>(column);
    }

    /* Get shared */
    template <typename T>
    const T& shared(uint32_t column) const {
        ecs_assert(ecs_column_entity(m_rows, column) == component_base<T>::s_entity, ECS_COLUMN_TYPE_MISMATCH, NULL);
        ecs_assert(ecs_is_shared(m_rows, column), ECS_COLUMN_IS_NOT_SHARED, NULL);
        return *static_cast<T*>(_ecs_column(m_rows, sizeof(T), column));
    }

    /* Get single field of a const type */
    template <typename T,
        typename std::enable_if<std::is_const<T>::value, void>::type* = nullptr>    
    T& field(uint32_t column, uint32_t row) const {
        return get_field<T>(column, row);
    }

    /* Get single field of a non-const type. Ensure that column is not readonly */
    template <typename T,
        typename std::enable_if<std::is_const<T>::value == false, void>::type* = nullptr>
    T& field(uint32_t column, uint32_t row) const {
        ecs_assert(!ecs_is_readonly(m_rows, column), ECS_COLUMN_ACCESS_VIOLATION, NULL);
        return get_field<T>(column, row);
    }

private:
    /* Get column, check if correct type is used */
    template <typename T>
    flecs::column<T> get_column(uint32_t column_id) const {
        ecs_assert(ecs_column_entity(m_rows, column_id) == component_base<T>::s_entity, ECS_COLUMN_TYPE_MISMATCH, NULL);
        uint32_t count;

        /* If a shared column is retrieved with 'column', there will only be a
         * single value. Ensure that the application does not accidentally read
         * out of bounds. */
        if (ecs_is_shared(m_rows, column_id)) {
            count = 1;
        } else {
            /* If column is owned, there will be as many values as there are
             * entities. */
            count = m_rows->count;
        }

        return flecs::column<T>(static_cast<T*>(_ecs_column(m_rows, sizeof(T), column_id)), count);
    }   

    /* Get single field, check if correct type is used */
    template <typename T>
    T& get_field(uint32_t column, uint32_t row) const {
        ecs_assert(ecs_column_entity(m_rows, column) == component_base<T>::s_entity, ECS_COLUMN_TYPE_MISMATCH, NULL);
        return *static_cast<T*>(_ecs_field(m_rows, sizeof(T), column, row));
    }       

    const ecs_rows_t *m_rows;
    uint32_t m_begin;
    uint32_t m_end;
};

/** Wrapper around world_t */
class world final {
public:
    world() 
        : m_world( ecs_init() )
        , m_owner( true ) { }

    world(int argc, char *argv[])
        : m_world( ecs_init_w_args(argc, argv) )
        , m_owner( true ) { }

    world(world_t *world) 
        : m_world( world )
        , m_owner( false ) { }

    world(const world& obj) {
        m_world = obj.m_world;
        m_owner = false;
    }

    world(world&& obj) {
        m_world = obj.m_world;
        m_owner = true;
        obj.m_owner = false;
    }

    world& operator=(const world& obj) {
        m_world = obj.m_world;
        m_owner = false;
        return *this;
    }

    world& operator=(world&& obj) {
        m_world = obj.m_world;
        m_owner = true;
        obj.m_owner = false;
        return *this;
    }
    
    ~world() { 
        if (m_owner) {
            ecs_fini(m_world); 
        }
    }

    world_t* c() const {
        return m_world;
    }

    bool progress(float delta_time = 0.0) const {
        return ecs_progress(m_world, delta_time);
    }

    void set_threads(std::uint32_t threads) const {
        ecs_set_threads(m_world, threads);
    }

    std::uint32_t get_threads() const {
        return ecs_get_threads(m_world);
    }

    std::uint32_t get_thread_index() const {
        return ecs_get_thread_index(m_world);
    }

    void set_target_fps(std::uint32_t target_fps) const {
        ecs_set_target_fps(m_world, target_fps);
    }

    std::uint32_t get_target_fps() const {
        return ecs_get_target_fps(m_world);
    }

    void set_context(void* ctx) const {
        ecs_set_context(m_world, ctx);
    }

    void* get_context() const {
        return ecs_get_context(m_world);
    }

    std::uint32_t get_tick() const {
        return ecs_get_tick(m_world);
    }

    void dim(std::int32_t entity_count) const {
        ecs_dim(m_world, entity_count);
    }

    void dim_type(flecs::type_t type, std::int32_t entity_count) const {
        _ecs_dim_type(m_world, type, entity_count);
    }

    void set_entity_range(entity_t min, entity_t max) const {
        ecs_set_entity_range(m_world, min, max);
    }

    void enable_range_check(bool enabled) const {
        ecs_enable_range_check(m_world, enabled);
    }

    void enable(const entity& system, bool enabled = true) const;

    bool is_enabled(const entity& system) const;

    void set_period(const entity& system, float period) const;

    void set_system_context(const entity& system, void *ctx) const;
    
    void* get_system_context(const entity& system) const;

    entity run(const entity& system, float delta_time = 0, void *param = nullptr) const;

    entity run(const entity& system, float delta_time, std::uint32_t offset, std::uint32_t limit, flecs::type_t filter, void *param) const;

    entity lookup(const char *name) const;

    entity lookup_child(const entity& parent, const char *name) const;

private:
    world_t *m_world;
    bool m_owner;
};

/** Fluent interface for entity class */
template <typename base>
class entity_fluent {
    using base_type = const base;
public:

    /* -- adopt -- */

    base_type& add(entity_t entity) const {
        static_cast<base_type*>(this)->invoke(
        [entity](world_t *world, entity_t id) {
            ecs_add_entity(world, id, entity);
        });
        return *static_cast<base_type*>(this);         
    }

    template <typename T>
    base_type& add() const {
        return add(component_base<T>::s_entity);
    }

    base_type& add(const entity& entity) const;

    base_type& add(flecs::type_t type) const {
        static_cast<base_type*>(this)->invoke(
        [type](world_t *world, entity_t id) {
            _ecs_add(world, id, type);
        });
        return *static_cast<base_type*>(this); 
    }

    base_type& add(flecs::type type) const;

    /* -- remove -- */

    base_type& remove(entity_t entity) const {
        static_cast<base_type*>(this)->invoke(
        [entity](world_t *world, entity_t id) {
            ecs_remove_entity(world, id, entity);
        });
        return *static_cast<base_type*>(this);         
    }    

    template <typename T>
    base_type& remove() {
        return remove(component_base<T>::s_entity);
    }

    base_type& remove(const entity& entity) const;

    base_type& remove(flecs::type_t type) const {
        static_cast<base_type*>(this)->invoke(
        [type](world_t *world, entity_t id) {
            _ecs_remove(world, id, type);
        });
        return *static_cast<base_type*>(this);         
    }

    /* -- adopt -- */

    base_type& adopt(entity_t parent) const {
        static_cast<base_type*>(this)->invoke(
        [parent](world_t *world, entity_t id) {
            ecs_adopt(world, id, parent);
        });
        return *static_cast<base_type*>(this);  
    }

    base_type& adopt(const entity& parent) const;

    /* -- orphan -- */

    base_type& orphan(entity_t parent) const {
        static_cast<base_type*>(this)->invoke(
        [parent](world_t *world, entity_t id) {
            ecs_orphan(world, id, parent);
        });
        return *static_cast<base_type*>(this);  
    }

    base_type& orphan(const entity& parent) const;

    /* -- inherit -- */

    base_type& inherit(entity_t base_entity) const {
        static_cast<base_type*>(this)->invoke(
        [base_entity](world_t *world, entity_t id) {
            ecs_inherit(world, id, base_entity);
        });
        return *static_cast<base_type*>(this);  
    }

    base_type& inherit(const entity& base_entity) const;  

    /* -- disinherit -- */

    base_type& disinherit(entity_t base_entity) const {
        static_cast<base_type*>(this)->invoke(
        [base_entity](world_t *world, entity_t id) {
            ecs_disinherit(world, id, base_entity);
        });
        return *static_cast<base_type*>(this);
    }

    base_type& disinherit(const entity& base_entity) const;

    /* -- set -- */

    template <typename T>
    const base_type& set(const T&& value) const {
        static_cast<base_type*>(this)->invoke(
        [value](world_t *world, entity_t id) {
            _ecs_set_ptr(world, id, component_base<T>::s_entity, sizeof(T), &value);
        });
        return *static_cast<base_type*>(this);
    }    
};

/** Entity class */
class entity : public entity_fluent<entity> {
public:
    entity(const world& world) 
        : m_world( world.c() )
        , m_id( _ecs_new(m_world, 0) ) { }

    entity(const world& world, entity_t id) 
        : m_world( world.c() )
        , m_id(id) { }

    entity(const world& world, const char *name) 
        : m_world( world.c() )
        , m_id( ecs_new_entity(m_world, name, 0) ) { }

    entity_t id() const {
        return m_id;
    }

    std::string name() const {
        EcsId *name = (EcsId*)_ecs_get_ptr(m_world, m_id, TEcsId);
        if (name) {
            return std::string(*name);
        } else {
            return std::string(nullptr);
        }
    }

    flecs::type type() const;

    template<typename T>
    T get() const {
        return _ecs_get(m_world, m_id, component_base<T>::s_type);
    }

    template<typename T>
    T* get_ptr() const {
        return _ecs_get(m_world, m_id, component_base<T>::s_type);
    }

    template <typename Func>
    void invoke(Func action) const {
        action(m_world, m_id);
    } 

    void destruct() const {
        ecs_delete(m_world, m_id);
    }

    /* -- has -- */

    bool has(entity_t id) const {
        return ecs_has_entity(m_world, m_id, id);
    }

    bool has(flecs::type_t type) const {
        return _ecs_has(m_world, m_id, type);
    }

    bool has(const entity& entity) const {
        return has(entity.id());
    }

    template <typename T>
    bool has() const {
        return has(component_base<T>::s_entity);
    }

protected:
    world_t *m_world;
    entity_t m_id; 
};

/** Entity range class */
class entity_range final : entity_fluent<entity_range> {
    using entity_iterator = range_iterator<entity_t>;
public:
    entity_range(const world& world, std::int32_t count) 
        : m_world(world.c())
        , m_id_start( _ecs_new_w_count(m_world, nullptr, count))
        , m_count(count) { }

    template <typename Func>
    void invoke(Func action) {
        for (auto id : *this) {
            action(m_world, id);
        }
    }
    
    entity_iterator begin() {
        return entity_iterator(m_id_start);
    }

    entity_iterator end() {
        return entity_iterator(m_id_start + m_count);
    }

private:
    world_t *m_world;
    entity_t m_id_start;
    std::int32_t m_count;
};

/** Type */

class type final : entity {
public:
    type(const world& world, const char *name, const char *expr = nullptr)
        : entity(world, ecs_new_type(world.c(), name, expr))
    { 
        sync_from_flecs();
    }

    type(const world& world, type_t type)
        : entity(world)
        , m_type( type )
        , m_normalized( type ) { }

    type& add(const type& type) {
        m_type = ecs_type_add(m_world, m_type, type.id());
        m_normalized = ecs_type_merge(m_world, m_normalized, type.c(), nullptr);
        sync_from_me();
        return *this;
    }

    type& add(const entity& entity) {
        m_type = ecs_type_add(m_world, m_type, entity.id());
        m_normalized = ecs_type_add(m_world, m_normalized, entity.id());
        sync_from_me();
        return *this;
    }

    template<typename T>
    type& add() {
        m_type = ecs_type_add(m_world, m_type, component_base<T>::s_entity);
        m_normalized = ecs_type_add(m_world, m_normalized, component_base<T>::s_entity);
        sync_from_me();
        return *this;
    }    

    type& add_instanceof(const entity& entity) {
        m_type = ecs_type_add(m_world, m_type, entity.id() | ECS_INSTANCEOF);
        m_normalized = ecs_type_add(m_world, m_normalized, entity.id() | ECS_INSTANCEOF);
        sync_from_me();
        return *this;
    }

    type& add_childof(const entity& entity) {
        m_type = ecs_type_add(m_world, m_type, entity.id() | ECS_CHILDOF);
        m_normalized = ecs_type_add(m_world, m_normalized, entity.id() | ECS_CHILDOF);
        sync_from_me();
        return *this;
    }

    std::string str() const {
        char *str = ecs_type_to_expr(m_world, m_type);
        std::string result(str);
        free(str);
        return result;
    }

    type_t c() const {
        return m_type;
    }

    type_t c_normalized() const {
        return m_normalized;
    }

private:
    void sync_from_me() {
        EcsTypeComponent *tc = ecs_get_ptr(m_world, m_id, EcsTypeComponent);
        if (tc) {
            tc->type = m_type;
            tc->resolved = m_normalized;
        }
    }

    void sync_from_flecs() {
        EcsTypeComponent *tc = ecs_get_ptr(m_world, m_id, EcsTypeComponent);
        if (tc) {
            m_type = tc->type;
            m_normalized = tc->resolved;
        }
    }

    type_t m_type;
    type_t m_normalized;
};

/* -- entity implementation -- */

flecs::type entity::type() const {
    return flecs::type(world(m_world), ecs_get_type(m_world, m_id));
}

/* -- entity_fluent implementation -- */

template <typename base>
typename entity_fluent<base>::base_type& entity_fluent<base>::add(const entity& entity) const {
    return add(entity.id());
}

template <typename base>
typename entity_fluent<base>::base_type& entity_fluent<base>::remove(const entity& entity) const {
    return remove(entity.id());
}

template <typename base>
typename entity_fluent<base>::base_type& entity_fluent<base>::adopt(const entity& entity) const {
    return adopt(entity.id());
}

template <typename base>
typename entity_fluent<base>::base_type& entity_fluent<base>::orphan(const entity& entity) const {
    return orphan(entity.id());
}

template <typename base>
typename entity_fluent<base>::base_type& entity_fluent<base>::inherit(const entity& entity) const {
    return inherit(entity.id());
}

template <typename base>
typename entity_fluent<base>::base_type& entity_fluent<base>::disinherit(const entity& entity) const {
    return disinherit(entity.id());
}

/* -- world implementation -- */

void world::enable(const entity& system, bool enabled) const {
    ecs_enable(m_world, system.id(), enabled);
}

bool world::is_enabled(const entity& system) const {
    return ecs_is_enabled(m_world, system.id());
}

void world::set_period(const entity& system, float period) const {
    ecs_set_period(m_world, system.id(), period);
}

void world::set_system_context(const entity& system, void *ctx) const {
    ecs_set_system_context(m_world, system.id(), ctx);
}

void* world::get_system_context(const entity& system) const {
    return ecs_get_system_context(m_world, system.id());
}

entity world::run(const entity& system, float delta_time, void *param) const {
    return entity(
        *this,
        ecs_run(m_world, system.id(), delta_time, param)
    );
}

entity world::run(const entity& system, float delta_time, std::uint32_t offset, std::uint32_t limit, flecs::type_t filter, void *param) const {
    return entity(
        *this,
        _ecs_run_w_filter(
            m_world, system.id(), delta_time, offset, limit, filter, param
        )
    );
}

entity world::lookup(const char *name) const {
    auto id = ecs_lookup(m_world, name);
    return entity(*this, id);
}

entity world::lookup_child(const entity& parent, const char *name) const {
    auto parent_id = parent.id();
    auto id = ecs_lookup_child(m_world, parent_id, name);
    return entity(*this, id);
}

/* -- rows implementation -- */

/* Obtain column source (0 if self) */
entity rows::column_source(uint32_t column) const {
    return entity(m_rows->world, ecs_column_source(m_rows, column));
}

/* Obtain component/tag entity of column */
entity rows::column_entity(uint32_t column) const {
    return entity(m_rows->world, ecs_column_entity(m_rows, column));
}

/* Obtain type of column */
flecs::type rows::column_type(uint32_t column) const {
    return flecs::type(m_rows->world, ecs_column_type(m_rows, column));
}

/* Obtain type of table being iterated over */
flecs::type rows::table_type() const {
    return flecs::type(m_rows->world, ecs_table_type(m_rows));
}

/** Register component, provide global access to component handles / metadata */
template <typename T>
class component_base final {
public:
    static void init(const world& world, const char *name) {
        s_entity = ecs_new_component(world.c(), name, sizeof(T));
        s_type = ecs_type_from_entity(world.c(), s_entity);
        s_name = name;
    }

    static void init_existing(entity_t entity, flecs::type_t type, const char *name) {
        s_entity = entity;
        s_type = type;
        s_name = name;
    }

    static entity_t s_entity;
    static flecs::type_t s_type;
    static const char *s_name;
};

template <typename T> entity_t component_base<T>::s_entity( 0 );
template <typename T> flecs::type_t component_base<T>::s_type( nullptr );
template <typename T> const char* component_base<T>::s_name( nullptr );

template <typename T>
class component final {
public:
    component(world world, const char *name) { 
        component_base<T>::init(world, name);

        /* Register as well for both const and reference versions of type */
        component_base<const T>::init_existing(
            component_base<T>::s_entity, 
            component_base<T>::s_type, 
            component_base<T>::s_name);

        component_base<T&>::init_existing(
            component_base<T>::s_entity, 
            component_base<T>::s_type, 
            component_base<T>::s_name);         
    }
};

/** Class that wraps around compile-time type safe system callbacks */
template <typename Func, typename ... Components>
class system_ctx {
    using columns = std::array<void*, sizeof...(Components)>;

public:
    system_ctx(Func func) : m_func(func) { }

    /* Dummy function when last component has been added */
    static void populate_columns(ecs_rows_t *rows, int index, columns& columns) { }

    /* Populate columns array recursively */
    template <typename T, typename... Targs>
    static void populate_columns(ecs_rows_t *rows, int index, columns& columns, T comp, Targs... comps) {
        columns[index] = _ecs_column(rows, sizeof(*comp), index + 1);
        populate_columns(rows, index + 1, columns, comps ...);
    }

    /* Invoke system */
    template <typename... Targs,
        typename std::enable_if<sizeof...(Targs) == sizeof...(Components), void>::type* = nullptr>
    static void call_system(ecs_rows_t *rows, int index, columns& columns, Targs... comps) {
        system_ctx *self = (system_ctx*)
            ecs_get_system_context(rows->world, rows->system);

        Func func = self->m_func;

        flecs::rows rows_wrapper(rows);
        
        func(rows_wrapper, (flecs::column<typename std::remove_reference<Components>::type>(
            (typename std::remove_reference<Components>::type*)comps, rows->count))...);
    }

    /** Add components one by one to parameter pack */
    template <typename... Targs,
        typename std::enable_if<sizeof...(Targs) != sizeof...(Components), void>::type* = nullptr>
    static void call_system(ecs_rows_t *rows, int index, columns& columns, Targs... comps) {
        call_system(rows, index + 1, columns, comps..., columns[index]);
    }

    /** Callback provided to flecs */
    static void run(ecs_rows_t *rows) {
        columns columns;
        populate_columns(rows, 0, columns, (typename std::remove_reference<Components>::type*)nullptr...);
        call_system(rows, 0, columns);
    }   

private:
    Func m_func;
};

/** Helper class that constructs a new system */
template<typename ... Components>
class system {
public:
    system(world world, const char *name = nullptr)
        : m_world(world.c())
        , m_kind(static_cast<EcsSystemKind>(OnUpdate))
        , m_name(name) { }

    system& signature(const char *signature) {
        m_signature = signature;
        return *this;
    }

    system& kind(system_kind kind) {
        m_kind = static_cast<EcsSystemKind>(kind);
        return *this;
    }

    /* Action is mandatory and always the last thing that is added in the fluent
     * method chain. Create system signature from both template parameters and
     * anything provided by the signature method. */
    template <typename Func>
    void action(Func func) {
        auto ctx = new system_ctx<Func, Components...>(func);

        std::stringstream str;
        std::array<const char*, sizeof...(Components)> ids = {
            component_base<Components>::s_name...
        };

        std::array<const char*, sizeof...(Components)> inout_modifiers = {
            inout_modifier<Components>()...
        };    

        int i = 0;
        for (auto id : ids) {
            if (i) {
                str << ",";
            }
            str << inout_modifiers[i];
            str << id;
            i ++;
        }

        if (m_signature) {
            if (i) {
                str << ",";
            }

            str << m_signature;
        }

        std::string signature = str.str();

        entity_t system = ecs_new_system(
            m_world, 
            m_name, 
            m_kind, 
            signature.c_str(), 
            system_ctx<Func, Components...>::run);

        ecs_set_system_context(m_world, system, ctx);
    }

    ~system() = default;
private:

    /** Utilities to convert type trait to flecs signature syntax */
    template <typename T,
        typename std::enable_if< std::is_const<T>::value == true, void>::type* = nullptr>
    constexpr const char *inout_modifier() const {
        return "[in] ";
    }

    template <typename T,
        typename std::enable_if< std::is_reference<T>::value == true, void>::type* = nullptr>
    constexpr const char *inout_modifier() const {
        return "[out] ";
    }

    template <typename T,
        typename std::enable_if<std::is_const<T>::value == false && std::is_reference<T>::value == false, void>::type* = nullptr>
    constexpr const char *inout_modifier() const {
        return "";
    }

    world_t *m_world;
    EcsSystemKind m_kind;
    const char *m_name;
    const char *m_signature = nullptr;
};

}