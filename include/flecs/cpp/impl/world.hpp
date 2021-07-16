
namespace flecs 
{

// emplace for T(flecs::entity, Args...)
template <typename T, typename ... Args, if_t<
    std::is_constructible<actual_type_t<T>, flecs::entity, Args...>::value >>
inline void emplace(world_t *world, id_t entity, Args&&... args) {
    flecs::entity self(world, entity);
    emplace<T>(world, entity, self, std::forward<Args>(args)...);
}

/** Get id from a type. */
template <typename T>
inline flecs::id world::id() const {
    return flecs::id(m_world, _::cpp_type<T>::id(m_world));
}

template <typename ... Args>
inline flecs::id world::id(Args&&... args) const {
    return flecs::id(m_world, std::forward<Args>(args)...);
}

template <typename R, typename O>
inline flecs::id world::pair() const {
    return flecs::id(
        m_world, 
        ecs_pair(
            _::cpp_type<R>::id(m_world), 
            _::cpp_type<O>::id(m_world)));
}

template <typename R>
inline flecs::id world::pair(entity_t o) const {
    return flecs::id(
        m_world,
        ecs_pair(
            _::cpp_type<R>::id(m_world), 
            o));
}

inline flecs::id world::pair(entity_t r, entity_t o) const {
    return flecs::id(
        m_world,
        ecs_pair(r, o));
}    

inline void world::delete_entities(flecs::filter filter) const {
    ecs_bulk_delete(m_world, filter.c_ptr());
}

template <typename T>
inline void world::add(flecs::filter filter) const {
    ecs_bulk_add_remove_type(
        m_world, _::cpp_type<T>::type(m_world), nullptr, filter.c_ptr());
}

inline void world::add(flecs::type t) const {
    ecs_bulk_add_remove_type(m_world, t.c_ptr(), nullptr, nullptr);
}

inline void world::add(flecs::type t, flecs::filter filter) const {
    ecs_bulk_add_remove_type(m_world, t.c_ptr(), nullptr, filter.c_ptr());
}

inline void world::add(class flecs::entity e) const {
    ecs_bulk_add_remove_type(m_world, e.to_type().c_ptr(), nullptr, nullptr);
}

inline void world::add(class flecs::entity e, flecs::filter filter) const {
    ecs_bulk_add_remove_type(m_world, e.to_type().c_ptr(), nullptr, filter.c_ptr());
}

template <typename T>
inline void world::remove(flecs::filter filter) const {
    ecs_bulk_add_remove_type(
        m_world, nullptr, _::cpp_type<T>::type(m_world), filter.c_ptr());
}

inline void world::remove(flecs::type t) const {
    ecs_bulk_add_remove_type(m_world, nullptr, t.c_ptr(), nullptr);
}

inline void world::remove(flecs::type t, flecs::filter filter) const {
    ecs_bulk_add_remove_type(m_world, nullptr, t.c_ptr(), filter.c_ptr());
}

inline void world::remove(class entity e) const {
    ecs_bulk_add_remove_type(m_world, nullptr, e.to_type().c_ptr(), nullptr);
}

inline void world::remove(class entity e, flecs::filter filter) const {
    ecs_bulk_add_remove_type(m_world, nullptr, e.to_type().c_ptr(), filter.c_ptr());
}

inline flecs::world_filter world::filter(const flecs::filter& filter) const {
    return flecs::world_filter(*this, filter);
}

inline filter_iterator world::begin() const {
    return filter_iterator(*this, flecs::filter(*this), ecs_filter_next);
}

inline filter_iterator world::end() const {
    return filter_iterator(ecs_filter_next);
}

inline int world::count(flecs::filter filter) const {
    return ecs_count_w_filter(m_world, filter.c_ptr());
}

/** All entities created in function are created in scope. All operations
    * called in function (such as lookup) are relative to scope.
    */
template <typename Func>
void scope(id_t parent, const Func& func);

inline void world::init_builtin_components() {
    pod_component<Component>("flecs::core::Component");
    pod_component<Type>("flecs::core::Type");
    pod_component<Name>("flecs::core::Name");
    pod_component<Trigger>("flecs::core::Trigger");
    pod_component<Observer>("flecs::core::Observer");
    pod_component<Query>("flecs::core::Query");

    pod_component<TickSource>("flecs::system::TickSource");
    pod_component<RateFilter>("flecs::timer::RateFilter");
    pod_component<Timer>("flecs::timer::Timer");
}

template <typename T>
inline flecs::entity world::use(const char *alias) {
    entity_t e = _::cpp_type<T>::id(m_world);
    const char *name = alias;
    if (!name) {
        // If no name is defined, use the entity name without the scope
        name = ecs_get_name(m_world, e);
    }
    ecs_use(m_world, e, name);
    return flecs::entity(m_world, e);
}

inline flecs::entity world::use(const char *name, const char *alias) {
    entity_t e = ecs_lookup_path_w_sep(m_world, 0, name, "::", "::", true);
    ecs_assert(e != 0, ECS_INVALID_PARAMETER, NULL);

    ecs_use(m_world, e, alias);
    return flecs::entity(m_world, e);
}

inline void world::use(flecs::entity e, const char *alias) {
    entity_t eid = e.id();
    const char *name = alias;
    if (!name) {
        // If no name is defined, use the entity name without the scope
        ecs_get_name(m_world, eid);
    }
    ecs_use(m_world, eid, alias);
}

inline flecs::entity world::set_scope(const flecs::entity& s) const {
    return flecs::entity(ecs_set_scope(m_world, s.id()));
}

inline flecs::entity world::get_scope() const {
    return flecs::entity(ecs_get_scope(m_world));
}

inline entity world::lookup(const char *name) const {
    auto e = ecs_lookup_path_w_sep(m_world, 0, name, "::", "::", true);
    return flecs::entity(*this, e);
}

template <typename T>
T* world::get_mut() const {
    flecs::entity e(m_world, _::cpp_type<T>::id(m_world));
    return e.get_mut<T>();
}

template <typename T>
void world::modified() const {
    flecs::entity e(m_world, _::cpp_type<T>::id(m_world));
    return e.modified<T>();
}

template <typename T, typename Func>
void world::patch(const Func& func) const {
    flecs::entity e(m_world, _::cpp_type<T>::id(m_world));
    e.patch<T>(func);
} 

template <typename T>
const T* world::get() const {
    flecs::entity e(m_world, _::cpp_type<T>::id(m_world));
    return e.get<T>();
}

template <typename T>
bool world::has() const {
    flecs::entity e(m_world, _::cpp_type<T>::id(m_world));
    return e.has<T>();
}

template <typename T>
void world::add() const {
    flecs::entity e(m_world, _::cpp_type<T>::id(m_world));
    e.add<T>();
}

template <typename T>
void world::remove() const {
    flecs::entity e(m_world, _::cpp_type<T>::id(m_world));
    e.remove<T>();
}

inline void world::set_pipeline(const flecs::pipeline& pip) const {
    ecs_set_pipeline(m_world, pip.id());
}

template <typename T>
inline flecs::entity world::singleton() {
    return flecs::entity(m_world, _::cpp_type<T>::id(m_world));
}

template <typename... Args>
inline flecs::entity world::entity(Args &&... args) const {
    return flecs::entity(*this, std::forward<Args>(args)...);
}

template <typename... Args>
inline flecs::entity world::prefab(Args &&... args) const {
    return flecs::prefab(*this, std::forward<Args>(args)...);
}

template <typename... Args>
inline flecs::type world::type(Args &&... args) const {
    return flecs::type(*this, std::forward<Args>(args)...);
}

template <typename... Args>
inline flecs::pipeline world::pipeline(Args &&... args) const {
    return flecs::pipeline(*this, std::forward<Args>(args)...);
}

inline flecs::system<> world::system(flecs::entity e) const {
    return flecs::system<>(m_world, e);
}

template <typename... Comps, typename... Args>
inline flecs::system_builder<Comps...> world::system(Args &&... args) const {
    return flecs::system_builder<Comps...>(*this, std::forward<Args>(args)...);
}

template <typename... Comps, typename... Args>
inline flecs::observer_builder<Comps...> world::observer(Args &&... args) const {
    return flecs::observer_builder<Comps...>(*this, std::forward<Args>(args)...);
}

template <typename... Comps, typename... Args>
inline flecs::query<Comps...> world::query(Args &&... args) const {
    return flecs::query<Comps...>(*this, std::forward<Args>(args)...);
}

template <typename... Comps, typename... Args>
inline flecs::query_builder<Comps...> world::query_builder(Args &&... args) const {
    return flecs::query_builder<Comps...>(*this, std::forward<Args>(args)...);
}

template <typename... Args>
inline flecs::term world::term(Args &&... args) const {
    return flecs::term(*this, std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline flecs::term world::term(Args &&... args) const {
    return flecs::term(*this, std::forward<Args>(args)...).id<T>();
}

template <typename R, typename O, typename... Args>
inline flecs::term world::term(Args &&... args) const {
    return flecs::term(*this, std::forward<Args>(args)...).id<R, O>();
}

template <typename Module, typename... Args>
inline flecs::entity world::module(Args &&... args) const {
    return flecs::module<Module>(*this, std::forward<Args>(args)...);
}

template <typename Module>
inline flecs::entity world::import() {
    return flecs::import<Module>(*this);
}

template <typename T, typename... Args>
inline flecs::entity world::component(Args &&... args) const {
    return flecs::component<T>(*this, std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline flecs::entity world::pod_component(Args &&... args) const {
    return flecs::pod_component<T>(*this, std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline flecs::entity world::relocatable_component(Args &&... args) const {
    return flecs::relocatable_component<T>(*this, std::forward<Args>(args)...);
}

template <typename... Args>
inline flecs::snapshot world::snapshot(Args &&... args) const {
    return flecs::snapshot(*this, std::forward<Args>(args)...);
}

} // namespace flecs
