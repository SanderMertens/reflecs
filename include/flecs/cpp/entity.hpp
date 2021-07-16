
namespace flecs {

template<typename T, typename Base>
class entity_builder_base {
public:
    const Base& base() const { return *static_cast<const Base*>(this); }
    flecs::world_t* base_world() const { return base().world(); }
    flecs::entity_t base_id() const { return base().id(); }
    operator const Base&() const {
        return this->base();
    }
};

}

#ifdef FLECS_DEPRECATED
#include "../addons/deprecated/entity.hpp"
#else
namespace flecs
{
template <typename Base>
class entity_builder_deprecated { };
class entity_deprecated { };
}
#endif

namespace flecs
{

/** Entity view class
 * This class provides readonly access to entities. Using this class to store 
 * entities in components ensures valid handles, as this class will always store
 * the actual world vs. a stage. The constructors of this class will never 
 * create a new entity.
 *
 * To obtain a mutable handle to the entity, use the "mut" function.
 */
class entity_view : public id {
public:
    explicit entity_view() : flecs::id() { }

    /** Wrap an existing entity id.
     *
     * @param world The world in which the entity is created.
     * @param id The entity id.
     */
    explicit entity_view(const flecs::world& world, const entity_view& id)
        : flecs::id( world.get_world(), id.id() ) { }

    /** Wrap an existing entity id.
     *
     * @param world Pointer to the world in which the entity is created.
     * @param id The entity id.
     */
    explicit entity_view(world_t *world, const entity_view& id) 
        : flecs::id( flecs::world(world).get_world(), id.id() ) { }

    /** Implicit conversion from flecs::entity_t to flecs::entity_view. */
    entity_view(entity_t id) 
        : flecs::id( nullptr, id ) { }

    /** Get entity id.
     * @return The integer entity id.
     */
    entity_t id() const {
        return m_id;
    }

    /** Check is entity is valid.
     *
     * @return True if the entity is alive, false otherwise.
     */
    bool is_valid() const {
        return m_world && ecs_is_valid(m_world, m_id);
    }
  
    explicit operator bool() const {
        return is_valid();
    }

    /** Check is entity is alive.
     *
     * @return True if the entity is alive, false otherwise.
     */
    bool is_alive() const {
        return m_world && ecs_is_alive(m_world, m_id);
    }

    /** Return the entity name.
     *
     * @return The entity name, or an empty string if the entity has no name.
     */
    flecs::string_view name() const {
        const EcsName *name = static_cast<const EcsName*>(
            ecs_get_id(m_world, m_id, static_cast<ecs_entity_t>(ecs_id(EcsName))));
        return flecs::string_view(name ? name->value : nullptr);
    }

    /** Return the entity path.
     *
     * @return The hierarchical entity path, or an empty string if the entity 
     *         has no name.
     */
    flecs::string path(const char *sep = "::", const char *init_sep = "::") const {
        char *path = ecs_get_path_w_sep(m_world, 0, m_id, 0, sep, init_sep);
        return flecs::string(path);
    }   

    bool enabled() {
        return !ecs_has_entity(m_world, m_id, flecs::Disabled);
    }

    /** Return the type.
     *
     * @return Returns the entity type.
     */
    flecs::type type() const;

    /** Return type containing the entity.
     *
     * @return A type that contains only this entity.
     */
    flecs::type to_type() const;

    /** Iterate contents (type) of an entity.
     */
    template <typename Func>
    void each(const Func& func) const;

    /** Iterate contents (type) of an entity for a specific relationship.
     */
    template <typename Func>
    void each(const flecs::entity_view& rel, const Func& func) const;

    /** Iterate contents (type) of an entity for a specific relationship.
     */
    template <typename Rel, typename Func>
    void each(const Func& func) const { 
        return each(_::cpp_type<Rel>::id(m_world), func);
    }

    /** Find all contents of an entity matching a pattern. */
    template <typename Func>
    void match(id_t pattern, const Func& func) const;

    /** Get component value.
     * 
     * @tparam T The component to get.
     * @return Pointer to the component value, nullptr if the entity does not
     *         have the component.
     */
    template <typename T, if_t< is_actual<T>::value > = 0>
    const T* get() const {
        auto comp_id = _::cpp_type<T>::id(m_world);
        ecs_assert(_::cpp_type<T>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        return static_cast<const T*>(ecs_get_id(m_world, m_id, comp_id));
    }

    /** Get component value.
     * Overload for when T is not the same as the actual type, which happens
     * when using pair types.
     * 
     * @tparam T The component to get.
     * @return Pointer to the component value, nullptr if the entity does not
     *         have the component.
     */
    template <typename T, typename A = actual_type_t<T>, 
        if_not_t< is_actual<T>::value > = 0>
    const A* get() const {
        auto comp_id = _::cpp_type<T>::id(m_world);
        ecs_assert(_::cpp_type<A>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        return static_cast<const A*>(ecs_get_id(m_world, m_id, comp_id));
    }

    /** Get a pair.
     * This operation gets the value for a pair from the entity.
     *
     * @tparam R the relation type.
     * @tparam O the object type.
     */
    template <typename R, typename O, typename P = pair<R, O>, 
        typename A = actual_type_t<P>, if_not_t< flecs::is_pair<R>::value > = 0>
    const A* get() const {
        return this->get<P>();
    }

    /** Get a pair.
     * This operation gets the value for a pair from the entity. 
     *
     * @tparam R the relation type.
     * @param object the object.
     */
    template<typename R>
    const R* get(const flecs::entity_view& object) const {
        auto comp_id = _::cpp_type<R>::id(m_world);
        ecs_assert(_::cpp_type<R>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        return static_cast<const R*>(
            ecs_get_id(m_world, m_id, ecs_pair(comp_id, object.id())));
    }

    /** Get component value (untyped).
     * 
     * @param component The component to get.
     * @return Pointer to the component value, nullptr if the entity does not
     *         have the component.
     */
    const void* get(const flecs::entity_view& component) const {
        return ecs_get_id(m_world, m_id, component.id());
    }

    /** Get a pair (untyped).
     * This operation gets the value for a pair from the entity. If neither the
     * relation nor the object part of the pair are components, the operation 
     * will fail.
     *
     * @param relation the relation.
     * @param object the object.
     */
    const void* get(const flecs::entity_view& relation, const flecs::entity_view& object) const {
        return ecs_get_id(m_world, m_id, ecs_pair(relation.id(), object.id()));
    }

    /** Get 1..N components.
     * This operation accepts a callback with as arguments the components to
     * retrieve. The callback will only be invoked when the entity has all
     * the components.
     *
     * This operation is faster than individually calling get for each component
     * as it only obtains entity metadata once.
     *
     * @param func The callback to invoke.
     * @return True if the entity has all components, false if not.
     */
    template <typename Func, if_t< is_callable<Func>::value > = 0>
    bool get(const Func& func) const;

    /** Get the object part from a pair.
     * This operation gets the value for a pair from the entity. The relation
     * part of the pair should not be a component.
     *
     * @tparam O the object type.
     * @param relation the relation.
     */
    template<typename O>
    const O* get_object(const flecs::entity_view& relation) const {
        auto comp_id = _::cpp_type<O>::id(m_world);
        ecs_assert(_::cpp_type<O>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        return static_cast<const O*>(
            ecs_get_id(m_world, m_id, ecs_pair(relation.id(), comp_id)));
    }

    /** Get the object part from a pair.
     * This operation gets the value for a pair from the entity. The relation
     * part of the pair should not be a component.
     *
     * @tparam R the relation type.
     * @tparam O the object type.
     */
    template<typename R, typename O>
    const O* get_object() const {
        return get<pair_object<R, O>>();
    }    

    /** Get parent from an entity.
     * This operation retrieves the parent entity that has the specified 
     * component. If no parent with the specified component is found, an entity
     * with id 0 is returned. If multiple parents have the specified component,
     * the operation returns the first encountered one.
     *
     * @tparam T The component for which to find the parent.
     * @return The parent entity.
     */
    template <typename T>
    flecs::entity_view get_parent() {
        return flecs::entity_view(m_world, 
            ecs_get_parent_w_entity(m_world, m_id, 
                _::cpp_type<T>::id(m_world)));
    }

    flecs::entity_view get_parent(flecs::entity_view e) {
        return flecs::entity_view(m_world, 
            ecs_get_parent_w_entity(m_world, m_id, e.id()));
    }    

    /** Lookup an entity by name.
     * Lookup an entity in the scope of this entity. The provided path may
     * contain double colons as scope separators, for example: "Foo::Bar".
     *
     * @param path The name of the entity to lookup.
     * @return The found entity, or entity::null if no entity matched.
     */
    flecs::entity_view lookup(const char *path) const {
        auto id = ecs_lookup_path_w_sep(m_world, m_id, path, "::", "::", false);
        return flecs::entity_view(m_world, id);
    }

    /** Check if entity has the provided type.
     *
     * @param entity The type pointer to check.
     * @return True if the entity has the provided type, false otherwise.
     */
    bool has(type_t type) const {
        return ecs_has_type(m_world, m_id, type);
    }

    /** Check if entity has the provided entity.
     *
     * @param entity The entity to check.
     * @return True if the entity has the provided entity, false otherwise.
     */
    bool has(flecs::id_t e) const {
        return ecs_has_id(m_world, m_id, e);
    }     

    /** Check if entity has the provided component.
     *
     * @tparam T The component to check.
     * @return True if the entity has the provided component, false otherwise.
     */
    template <typename T>
    bool has() const {
        return ecs_has_id(m_world, m_id, _::cpp_type<T>::id(m_world));
    }

    /** Check if entity has the provided pair.
     *
     * @tparam Relation The relation type.
     * @param Object The object type.
     * @return True if the entity has the provided component, false otherwise.
     */
    template <typename Relation, typename Object>
    bool has() const {
        return this->has<Relation>(_::cpp_type<Object>::id(m_world));
    }

    /** Check if entity has the provided pair.
     *
     * @tparam Relation The relation type.
     * @param object The object.
     * @return True if the entity has the provided component, false otherwise.
     */
    template <typename Relation>
    bool has(flecs::id_t object) const {
        auto comp_id = _::cpp_type<Relation>::id(m_world);
        return ecs_has_id(m_world, m_id, ecs_pair(comp_id, object));
    }

    /** Check if entity has the provided pair.
     *
     * @param relation The relation.
     * @param object The object.
     * @return True if the entity has the provided component, false otherwise.
     */
    bool has(flecs::id_t relation, flecs::id_t object) const {
        return ecs_has_id(m_world, m_id, ecs_pair(relation, object));
    }

    /** Check if entity has the provided pair.
     *
     * @tparam Object The object type.
     * @param relation The relation.
     * @return True if the entity has the provided component, false otherwise.
     */
    template <typename Object>
    bool has_object(flecs::id_t relation) const {
        auto comp_id = _::cpp_type<Object>::id(m_world);
        return ecs_has_id(m_world, m_id, ecs_pair(relation, comp_id));
    }

    /** Check if entity owns the provided type.
     * An type is owned if it is not shared from a base entity.
     *
     * @param type The type to check.
     * @return True if the entity owns the provided type, false otherwise.
     */
    bool owns(type_t type) const {
        return ecs_type_owns_type(
            m_world, ecs_get_type(m_world, m_id), type, true);
    }

    /** Check if entity owns the provided entity.
     * An entity is owned if it is not shared from a base entity.
     *
     * @param entity The entity to check.
     * @return True if the entity owns the provided entity, false otherwise.
     */
    bool owns(flecs::id_t e) const {
        return ecs_owns_entity(m_world, m_id, e, true);
    }

    /** Check if entity owns the provided pair.
     *
     * @tparam Relation The relation type.
     * @param object The object.
     * @return True if the entity owns the provided component, false otherwise.
     */
    template <typename Relation>
    bool owns(flecs::id_t object) const {
        auto comp_id = _::cpp_type<Relation>::id(m_world);
        return owns(ecs_pair(comp_id, object));
    }

    /** Check if entity owns the provided pair.
     *
     * @param relation The relation.
     * @param object The object.
     * @return True if the entity owns the provided component, false otherwise.
     */
    bool owns(flecs::id_t relation, flecs::id_t object) const {
        return owns(ecs_pair(relation, object));
    }

    /** Check if entity owns the provided component.
     * An component is owned if it is not shared from a base entity.
     *
     * @tparam T The component to check.
     * @return True if the entity owns the provided component, false otherwise.
     */
    template <typename T>
    bool owns() const {
        return owns(_::cpp_type<T>::id(m_world));
    }

    /** Check if entity has the provided switch.
     *
     * @param sw The switch to check.
     * @return True if the entity has the provided switch, false otherwise.
     */
    bool has_switch(const flecs::type& sw) const;

    /** Check if entity has the provided case.
     *
     * @param sw_case The case to check.
     * @return True if the entity has the provided case, false otherwise.
     */
    bool has_case(flecs::id_t sw_case) const {
        return ecs_has_entity(m_world, m_id, flecs::Case | sw_case);
    }

    template<typename T>
    bool has_case() const {
        return this->has_case(_::cpp_type<T>::id(m_world));
    }

    /** Get case for switch.
     *
     * @param sw The switch for which to obtain the case.
     * @return True if the entity has the provided case, false otherwise.
     */
    flecs::entity_view get_case(const flecs::type& sw) const;

    /** Get case for switch.
     *
     * @param sw The switch for which to obtain the case.
     * @return True if the entity has the provided case, false otherwise.
     */
    flecs::entity_view get_case(flecs::id_t sw) const {
        return flecs::entity_view(m_world, ecs_get_case(m_world, m_id, sw));
    }

    /** Test if component is enabled.
     *
     * @tparam T The component to test.
     * @return True if the component is enabled, false if it has been disabled.
     */
    template<typename T>
    bool is_enabled() {
        return ecs_is_component_enabled_w_entity(
            m_world, m_id, _::cpp_type<T>::id(m_world));
    }

    /** Test if component is enabled.
     *
     * @param entity The component to test.
     * @return True if the component is enabled, false if it has been disabled.
     */
    bool is_enabled(const flecs::entity_view& e) {
        return ecs_is_component_enabled_w_entity(
            m_world, m_id, e.id());
    }

    /** Get current delta time.
     * Convenience function so system implementations can get delta_time, even
     * if they are using the .each() function.
     *
     * @return Current delta_time.
     */
    FLECS_FLOAT delta_time() const {
        const ecs_world_info_t *stats = ecs_get_world_info(m_world);
        return stats->delta_time;
    }

    /** Return iterator to entity children.
     * Enables depth-first iteration over entity children.
     *
     * @return Iterator to child entities.
     */
    child_iterator children() const;

    /** Return mutable entity handle for current stage 
     * When an entity handle created from the world is used while the world is
     * in staged mode, it will only allow for readonly operations since 
     * structural changes are not allowed on the world while in staged mode.
     * 
     * To do mutations on the entity, this operation provides a handle to the
     * entity that uses the stage instead of the actual world.
     *
     * Note that staged entity handles should never be stored persistently, in
     * components or elsewhere. An entity handle should always point to the
     * main world.
     *
     * Also note that this operation is not necessary when doing mutations on an
     * entity outside of a system. It is allowed to do entity operations 
     * directly on the world, as long as the world is not in staged mode.
     *
     * @param stage The current stage.
     * @return An entity handle that allows for mutations in the current stage.
     */
    flecs::entity mut(const flecs::world& stage) const;

    /** Same as mut(world), but for iterator.
     * This operation allows for the construction of a mutable entity handle
     * from an iterator.
     *
     * @param stage An created for the current stage.
     * @return An entity handle that allows for mutations in the current stage.
     */
    flecs::entity mut(const flecs::iter& it) const;

    /** Same as mut(world), but for entity.
     * This operation allows for the construction of a mutable entity handle
     * from another entity. This is useful in each() functions, which only 
     * provide a handle to the entity being iterated over.
     *
     * @param stage An created for the current stage.
     * @return An entity handle that allows for mutations in the current stage.
     */
    flecs::entity mut(const flecs::entity_view& e) const;

private:
    flecs::entity set_stage(world_t *stage);
};

/** Fluent API for chaining entity operations
 * This class contains entity operations that can be chained. For example, by
 * using this class, an entity can be created like this:
 *
 * flecs::entity e = flecs::entity(world)
 *   .add<Position>()
 *   .add<Velocity>();
 */
struct entity_builder_tag { }; // Tag to prevent ambiguous base

template <typename Base>
class entity_builder : public entity_builder_base<entity_builder_tag, Base> {
public:
    /** Add a component to an entity.
     * To ensure the component is initialized, it should have a constructor.
     * 
     * @tparam T the component type to add.
     */
    template <typename T>
    const Base& add() const {
        flecs_static_assert(is_flecs_constructible<T>::value,
            "add<T>() cannot construct type: add T() or "
                "T(flecs::world&, flecs::entity)");
        ecs_add_id(this->base_world(), this->base_id(), _::cpp_type<T>::id(this->base_world()));
        return *this;
    }

    /** Add an entity to an entity.
     * Add an entity to the entity. This is typically used for tagging.
     *
     * @param entity The entity to add.
     */
    const Base& add(entity_t entity) const {
        ecs_add_id(this->base_world(), this->base_id(), entity);
        return *this;
    }

    /** Add a type to an entity.
     * A type is a vector of component ids. This operation adds all components
     * in a single operation, and is a more efficient version of doing 
     * individual add operations.
     * 
     * @param type The type to add.
     */
    const Base& add(const type& type) const;

    /** Add a pair.
     * This operation adds a pair to the entity.
     *
     * @param relation The relation id.
     * @param object The object id.
     */
    const Base& add(entity_t relation, entity_t object) const {
        ecs_add_pair(this->base_world(), this->base_id(), relation, object);
        return *this;
    }

    /** Add a pair.
     * This operation adds a pair to the entity.
     *
     * @tparam R the relation type.
     * @tparam O the object type.
     */
    template<typename R, typename O>
    const Base& add() const {
        return this->add<R>(_::cpp_type<O>::id(this->base_world()));
    }

    /** Add a pair.
     * This operation adds a pair to the entity.
     *
     * @tparam R the relation type.
     * @param object the object type.
     */
    template<typename R>
    const Base& add(entity_t object) const {
        flecs_static_assert(is_flecs_constructible<R>::value,
            "add<T>(entity_t) cannot construct type: add T() or "
                "T(flecs::world&, flecs::entity)");        
        return this->add(_::cpp_type<R>::id(this->base_world()), object);
    }

    /** Shortcut for add(IsA. obj).
     *
     * @param object the object id.
     */
    const Base& is_a(entity_t object) const {
        return this->add(flecs::IsA, object);
    }

    /** Shortcut for add(ChildOf. obj).
     *
     * @param object the object id.
     */
    const Base& child_of(entity_t object) const {
        return this->add(flecs::ChildOf, object);
    }

    /** Add a pair with object type.
     * This operation adds a pair to the entity. The relation part of the pair
     * should not be a component.
     *
     * @param relation the relation type.
     * @tparam O the object type.
     */
    template<typename O>
    const Base& add_object(entity_t relation) const {
        flecs_static_assert(is_flecs_constructible<O>::value,
            "add_object<T>(entity_t) cannot construct type: add T() or "
                "T(flecs::world&, flecs::entity)");        
        return this->add(relation,  _::cpp_type<O>::id(this->base_world()));
    }

    /** Remove a component from an entity.
     *
     * @tparam T the type of the component to remove.
     */
    template <typename T>
    const Base& remove() const {
        ecs_remove_id(this->base_world(), this->base_id(), _::cpp_type<T>::id(this->base_world()));
        return *this;
    }

    /** Remove an entity from an entity.
     *
     * @param entity The entity to remove.
     */
    const Base& remove(entity_t entity) const {
        ecs_remove_id(this->base_world(), this->base_id(), entity);
        return *this;
    }

    /** Remove a type from an entity.
     * A type is a vector of component ids. This operation adds all components
     * in a single operation, and is a more efficient version of doing 
     * individual add operations.
     *
     * @param type the type to remove.
     */
    const Base& remove(const type& type) const;

    /** Remove a pair.
     * This operation removes a pair from the entity.
     *
     * @param relation The relation id.
     * @param object The object id.
     */
    const Base& remove(entity_t relation, entity_t object) const {
        ecs_remove_pair(this->base_world(), this->base_id(), relation, object);
        return *this;
    }

    /** Removes a pair.
     * This operation removes a pair from the entity.
     *
     * @tparam Relation the relation type.
     * @tparam Object the object type.
     */
    template<typename Relation, typename Object>
    const Base& remove() const {
        return this->remove<Relation>(_::cpp_type<Object>::id(this->base_world()));
    }

    /** Remove a pair.
     * This operation adds a pair to the entity.
     *
     * @tparam Relation the relation type.
     * @param object the object type.
     */
    template<typename Relation>
    const Base& remove(entity_t object) const {
        return this->remove(_::cpp_type<Relation>::id(this->base_world()), object);
    }  

    /** Removes a pair with object type.
     * This operation removes a pair from the entity.
     *
     * @param relation the relation type.
     * @tparam Object the object type.
     */
    template<typename Object>
    const Base& remove_object(entity_t relation) const {
        return this->remove(relation, _::cpp_type<Object>::id(this->base_world()));
    }    

    /** Add owned flag for component (forces ownership when instantiating)
     *
     * @param entity The entity for which to add the OWNED flag
     */    
    const Base& add_owned(entity_t entity) const {
        ecs_add_id(this->base_world(), this->base_id(), ECS_OWNED | entity);
        return *this;  
    }

    /** Add owned flag for component (forces ownership when instantiating)
     *
     * @tparam T The component for which to add the OWNED flag
     */    
    template <typename T>
    const Base& add_owned() const {
        ecs_add_id(this->base_world(), this->base_id(), ECS_OWNED | _::cpp_type<T>::id(this->base_world()));
        return *this;  
    }

    ECS_DEPRECATED("use add_owned(flecs::entity e)")
    const Base& add_owned(const type& type) const;

    /** Set value, add owned flag.
     *
     * @tparam T The component to set and for which to add the OWNED flag
     */    
    template <typename T>
    const Base& set_owned(T&& val) const {
        this->add_owned<T>();
        this->set<T>(std::forward<T>(val));
        return *this;  
    }    

    /** Add a switch to an entity by id.
     * The switch entity must be a type, that is it must have the EcsType
     * component. Entities created with flecs::type are valid here.
     *
     * @param sw The switch entity id to add.
     */    
    const Base& add_switch(entity_t sw) const {
        ecs_add_id(this->base_world(), this->base_id(), ECS_SWITCH | sw);
        return *this;  
    }

    /** Add a switch to an entity.
     * Any instance of flecs::type can be used as a switch.
     *
     * @param sw The switch to add.
     */     
    const Base& add_switch(const type& sw) const;

    /** Remove a switch from an entity by id.
     *
     * @param sw The switch entity id to remove.
     */    
    const Base& remove_switch(entity_t sw) const {
        ecs_remove_id(this->base_world(), this->base_id(), ECS_SWITCH | sw);
        return *this;  
    }
    
    /** Remove a switch from an entity.
     * Any instance of flecs::type can be used as a switch.
     *
     * @param sw The switch to remove.
     */      
    const Base& remove_switch(const type& sw) const;

    /** Add a switch to an entity by id.
     * The case must belong to a switch that is already added to the entity.
     *
     * @param sw_case The case entity id to add.
     */    
    const Base& add_case(entity_t sw_case) const {
        ecs_add_id(this->base_world(), this->base_id(), ECS_CASE | sw_case);
        return *this;
    }

    /** Add a switch to an entity by id.
     * The case must belong to a switch that is already added to the entity.
     *
     * @tparam T The case to add.
     */   
    template<typename T>
    const Base& add_case() const {
        return this->add_case(_::cpp_type<T>::id());
    }

    /** Remove a case from an entity by id.
     * The case must belong to a switch that is already added to the entity.
     *
     * @param sw_case The case entity id to remove.
     */    
    const Base& remove_case(entity_t sw_case) const {
        ecs_remove_id(this->base_world(), this->base_id(), ECS_CASE | sw_case);
        return *this;  
    }

    /** Remove a switch from an entity by id.
     * The case must belong to a switch that is already added to the entity.
     *
     * @tparam T The case to remove.
     */   
    template<typename T>
    const Base& remove_case() const {
        return this->remove_case(_::cpp_type<T>::id());
    }

    /** Enable an entity.
     * Enabled entities are matched with systems and can be searched with
     * queries.
     */
    const Base& enable() const {
        ecs_enable(this->base_world(), this->base_id(), true);
        return *this;
    }

    /** Disable an entity.
     * Disabled entities are not matched with systems and cannot be searched 
     * with queries, unless explicitly specified in the query expression.
     */
    const Base& disable() const {
        ecs_enable(this->base_world(), this->base_id(), false);
        return *this;
    }

    /** Enable a component.
     * This sets the enabled bit for this component. If this is the first time
     * the component is enabled or disabled, the bitset is added.
     *
     * @tparam T The component to enable.
     */   
    template<typename T>
    const Base& enable() const {
        ecs_enable_component_w_entity(this->base_world(), this->base_id(), _::cpp_type<T>::id(), true);
        return *this;
    }  

    /** Disable a component.
     * This sets the enabled bit for this component. If this is the first time
     * the component is enabled or disabled, the bitset is added.
     *
     * @tparam T The component to enable.
     */   
    template<typename T>
    const Base& disable() const {
        ecs_enable_component_w_entity(this->base_world(), this->base_id(), _::cpp_type<T>::id(), false);
        return *this;
    }  

    /** Enable a component.
     * See enable<T>.
     *
     * @param component The component to enable.
     */   
    const Base& enable(entity_t component) const {
        ecs_enable_component_w_entity(this->base_world(), this->base_id(), component, true);
        return *this;       
    }

    /** Disable a component.
     * See disable<T>.
     *
     * @param component The component to disable.
     */   
    const Base& disable(entity_t component) const {
        ecs_enable_component_w_entity(this->base_world(), this->base_id(), component, false);
        return *this;       
    }

    template<typename T, if_t< 
        !is_callable<T>::value && is_actual<T>::value> = 0 >
    const Base& set(T&& value) const {
        flecs::set<T>(this->base_world(), this->base_id(), std::forward<T&&>(value));
        return *this;
    }

    template<typename T, if_t< 
        !is_callable<T>::value && is_actual<T>::value > = 0>
    const Base& set(const T& value) const {
        flecs::set<T>(this->base_world(), this->base_id(), value);
        return *this;
    }

    template<typename T, typename A = actual_type_t<T>, if_not_t< 
        is_callable<T>::value || is_actual<T>::value > = 0>
    const Base& set(A&& value) const {
        flecs::set<T>(this->base_world(), this->base_id(), std::forward<A&&>(value));
        return *this;
    }

    template<typename T, typename A = actual_type_t<T>, if_not_t<
        is_callable<T>::value || is_actual<T>::value > = 0>
    const Base& set(const A& value) const {
        flecs::set<T>(this->base_world(), this->base_id(), value);
        return *this;
    }

    /** Set a pair for an entity.
     * This operation sets the pair value, and uses the relation as type. If the
     * entity did not yet have the pair, it will be added.
     *
     * @tparam R The relation part of the pair.
     * @tparam O The object part of the pair.
     * @param value The value to set.
     */
    template <typename R, typename O, typename P = pair<R, O>, 
        typename A = actual_type_t<P>, if_not_t< is_pair<R>::value> = 0>
    const Base& set(const A& value) const {
        flecs::set<P>(this->base_world(), this->base_id(), value);
        return *this;
    }

    /** Set a pair for an entity.
     * This operation sets the pair value, and uses the relation as type. If the
     * entity did not yet have the pair, it will be added.
     *
     * @tparam R The relation part of the pair.
     * @param object The object part of the pair.
     * @param value The value to set.
     */
    template <typename R>
    const Base& set(entity_t object, const R& value) const {
        auto relation = _::cpp_type<R>::id(this->base_world());
        flecs::set(this->base_world(), this->base_id(), value, 
            ecs_pair(relation, object));
        return *this;
    }

    /** Set a pair for an entity.
     * This operation sets the pair value, and uses the relation as type. If the
     * entity did not yet have the pair, it will be added.
     *
     * @tparam Object The object part of the pair.
     * @param relation The relation part of the pair.
     * @param value The value to set.
     */
    template <typename O>
    const Base& set_object(entity_t relation, const O& value) const {
        auto object = _::cpp_type<O>::id(this->base_world());
        flecs::set(this->base_world(), this->base_id(), value, 
            ecs_pair(relation, object));
        return *this;
    }

    template <typename R, typename O>
    const Base& set_object(const O& value) const {
        flecs::set<pair_object<R, O>>(this->base_world(), this->base_id(), value);
        return *this;
    }    

    /** Set 1..N components.
     * This operation accepts a callback with as arguments the components to
     * set. If the entity does not have all of the provided components, they
     * will be added.
     *
     * This operation is faster than individually calling get for each component
     * as it only obtains entity metadata once. When this operation is called
     * while deferred, its performance is equivalent to that of calling get_mut
     * for each component separately.
     *
     * The operation will invoke modified for each component after the callback
     * has been invoked.
     *
     * @param func The callback to invoke.
     */
    template <typename Func, if_t< is_callable<Func>::value > = 0>
    const Base& set(const Func& func) const;

    /** Emplace component.
     * Emplace constructs a component in the storage, which prevents calling the
     * destructor on the object passed into the function.
     *
     * Emplace attempts the following signatures to construct the component:
     *  T{Args...}
     *  T{flecs::entity, Args...}
     *
     * If the second signature matches, emplace will pass in the current entity 
     * as argument to the constructor, which is useful if the component needs
     * to be aware of the entity to which it has been added.
     *
     * Emplace may only be called for components that have not yet been added
     * to the entity.
     *
     * @tparam T the component to emplace
     * @param args The arguments to pass to the constructor of T
     */
    template <typename T, typename ... Args>
    const Base& emplace(Args&&... args) const {
        flecs::emplace<T>(this->base_world(), this->base_id(), 
            std::forward<Args>(args)...);
        return *this;
    }

    /** Entities created in function will have the current entity.
     *
     * @param func The function to call.
     */
    template <typename Func>
    const Base& with(const Func& func) const {
        ecs_id_t prev = ecs_set_with(this->base_world(), this->base_id());
        func();
        ecs_set_with(this->base_world(), prev);
        return *this;
    }

    /** Entities created in function will have (Relation, this) 
     * This operation is thread safe.
     *
     * @tparam Relation The relation to use.
     * @param func The function to call.
     */
    template <typename Relation, typename Func>
    const Base& with(const Func& func) const {
        with(_::cpp_type<Relation>::id(this->base_world()), func);
        return *this;
    }  

    /** Entities created in function will have (relation, this) 
     *
     * @param relation The relation to use.
     * @param func The function to call.
     */
    template <typename Func>
    const Base& with(id_t relation, const Func& func) const {
        ecs_id_t prev = ecs_set_with(this->base_world(), 
            ecs_pair(relation, this->base_id()));
        func();
        ecs_set_with(this->base_world(), prev);
        return *this;
    }

    /** The function will be ran with the scope set to the current entity. */
    template <typename Func>
    const Base& scope(const Func& func) const {
        ecs_entity_t prev = ecs_set_scope(this->base_world(), this->base_id());
        func();
        ecs_set_scope(this->base_world(), prev);
        return *this;
    }    
};

////////////////////////////////////////////////////////////////////////////////
//// Quick and safe access to a component pointer
////////////////////////////////////////////////////////////////////////////////

template <typename T>
class ref {
public:
    ref()
        : m_world( nullptr )
        , m_entity( 0 )
        , m_ref() { }

    ref(world_t *world, entity_t entity) 
        : m_world( world )
        , m_entity( entity )
        , m_ref() 
    {
        auto comp_id = _::cpp_type<T>::id(world);

        ecs_assert(_::cpp_type<T>::size() != 0, 
                ECS_INVALID_PARAMETER, NULL);

        ecs_get_ref_w_entity(
            m_world, &m_ref, m_entity, comp_id);
    }

    const T* operator->() {
        const T* result = static_cast<const T*>(ecs_get_ref_w_entity(
            m_world, &m_ref, m_entity, _::cpp_type<T>::id(m_world)));

        ecs_assert(result != NULL, ECS_INVALID_PARAMETER, NULL);

        return result;
    }

    const T* get() {
        if (m_entity) {
            ecs_get_ref_w_entity(
                m_world, &m_ref, m_entity, _::cpp_type<T>::id(m_world));    
        }

        return static_cast<T*>(m_ref.ptr);
    }

    flecs::entity entity() const;

private:
    world_t *m_world;
    entity_t m_entity;
    flecs::ref_t m_ref;
};

/** Entity class
 * This class provides access to entities. */
class entity : 
    public entity_view,
    public entity_builder<entity>, 
    public entity_deprecated<entity>, 
    public entity_builder_deprecated<entity>
{
public:
    /** Default constructor.
     */
    explicit entity()
        : flecs::entity_view() { }

    /** Create entity.
     *
     * @param world The world in which to create the entity.
     */
    explicit entity(world_t *world) 
        : flecs::entity_view() 
    {
        m_world = world;
        m_id = ecs_new_w_type(world, 0);
    }

    /** Create a named entity.
     * Named entities can be looked up with the lookup functions. Entity names
     * may be scoped, where each element in the name is separated by "::".
     * For example: "Foo::Bar". If parts of the hierarchy in the scoped name do
     * not yet exist, they will be automatically created.
     *
     * @param world The world in which to create the entity.
     * @param name The entity name.
     * @param is_component If true, the entity will be created from the pool of component ids (default = false).
     */
    explicit entity(world_t *world, const char *name) 
        : flecs::entity_view()
    { 
        m_world = world;

        ecs_entity_desc_t desc = {};
        desc.name = name;
        desc.sep = "::";
        m_id = ecs_entity_init(world, &desc);
    }

    /** Wrap an existing entity id.
     *
     * @param world The world in which the entity is created.
     * @param id The entity id.
     */
    explicit entity(world_t *world, entity_t id)
        : flecs::entity_view()
    {
        m_world = world;
        m_id = id;
    }

    /** Conversion from flecs::entity_t to flecs::entity. */
    explicit entity(entity_t id) 
        : flecs::entity_view( nullptr, id ) { }

    /** Get entity id.
     * @return The integer entity id.
     */
    entity_t id() const {
        return m_id;
    }

    /** Get mutable component value.
     * This operation returns a mutable pointer to the component. If the entity
     * did not yet have the component, it will be added. If a base entity had
     * the component, it will be overridden, and the value of the base component
     * will be copied to the entity before this function returns.
     *
     * @tparam T The component to get.
     * @param is_added If provided, this parameter will be set to true if the component was added.
     * @return Pointer to the component value.
     */
    template <typename T>
    T* get_mut(bool *is_added = nullptr) const {
        auto comp_id = _::cpp_type<T>::id(m_world);
        ecs_assert(_::cpp_type<T>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        return static_cast<T*>(
            ecs_get_mut_w_entity(m_world, m_id, comp_id, is_added));
    }

    /** Get mutable component value (untyped).
     * This operation returns a mutable pointer to the component. If the entity
     * did not yet have the component, it will be added. If a base entity had
     * the component, it will be overridden, and the value of the base component
     * will be copied to the entity before this function returns.
     *
     * @param component The component to get.
     * @param is_added If provided, this parameter will be set to true if the component was added.
     * @return Pointer to the component value.
     */
    void* get_mut(entity_t component, bool *is_added = nullptr) const {
        return ecs_get_mut_w_entity(m_world, m_id, component, is_added);
    }

    /** Get mutable pointer for a pair.
     * This operation gets the value for a pair from the entity.
     *
     * @tparam Relation the relation type.
     * @tparam Object the object type.
     */
    template <typename Relation, typename Object>
    Relation* get_mut(bool *is_added = nullptr) const {
        return this->get_mut<Relation>(
            _::cpp_type<Object>::id(m_world), is_added);
    }

    /** Get mutable pointer for a pair.
     * This operation gets the value for a pair from the entity.
     *
     * @tparam Relation the relation type.
     * @param object the object.
     */
    template <typename Relation>
    Relation* get_mut(entity_t object, bool *is_added = nullptr) const {
        auto comp_id = _::cpp_type<Relation>::id(m_world);
        ecs_assert(_::cpp_type<Relation>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        return static_cast<Relation*>(
            ecs_get_mut_w_entity(m_world, m_id, 
                ecs_pair(comp_id, object), is_added));
    }

    /** Get mutable pointer for a pair (untyped).
     * This operation gets the value for a pair from the entity. If neither the
     * relation or object are a component, the operation will fail.
     *
     * @param relation the relation.
     * @param object the object.
     */
    void* get_mut(entity_t relation, entity_t object, bool *is_added = nullptr) const {
        return ecs_get_mut_w_entity(m_world, m_id, 
                ecs_pair(relation, object), is_added);
    }

    /** Get mutable pointer for the object from a pair.
     * This operation gets the value for a pair from the entity.
     *
     * @tparam Object the object type.
     * @param relation the relation.
     */
    template <typename Object>
    Object* get_mut_object(entity_t relation, bool *is_added = nullptr) const {
        auto comp_id = _::cpp_type<Object>::id(m_world);
        ecs_assert(_::cpp_type<Object>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        return static_cast<Object*>(
            ecs_get_mut_w_entity(m_world, m_id, 
                ecs_pair(relation, comp_id), is_added));
    }           

    /** Signal that component was modified.
     *
     * @tparam T component that was modified.
     */
    template <typename T>
    void modified() const {
        auto comp_id = _::cpp_type<T>::id(m_world);
        ecs_assert(_::cpp_type<T>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        this->modified(comp_id);
    } 

    /** Signal that the relation part of a pair was modified.
     *
     * @tparam Relation the relation type.
     * @tparam Object the object type.
     */
    template <typename Relation, typename Object>
    void modified() const {
        this->modified<Relation>(_::cpp_type<Object>::id(m_world));
    }

    /** Signal that the relation part of a pair was modified.
     *
     * @tparam Relation the relation type.
     * @param object the object.
     */
    template <typename Relation>
    void modified(entity_t object) const {
        auto comp_id = _::cpp_type<Relation>::id(m_world);
        ecs_assert(_::cpp_type<Relation>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        this->modified(comp_id, object);
    }

    /** Signal that a pair has modified (untyped).
     * If neither the relation or object part of the pair are a component, the
     * operation will fail.
     *
     * @param relation the relation.
     * @param object the object.
     */
    void modified(entity_t relation, entity_t object) const {
        this->modified(ecs_pair(relation, object));
    }

    /** Signal that component was modified.
     *
     * @param component component that was modified.
     */
    void modified(entity_t component) const {
        ecs_modified_w_entity(m_world, m_id, component);
    }

    /** Get reference to component.
     * A reference allows for quick and safe access to a component value, and is
     * a faster alternative to repeatedly calling 'get' for the same component.
     *
     * @tparam T component for which to get a reference.
     * @return The reference.
     */
    template <typename T>
    ref<T> get_ref() const {
        // Ensure component is registered
        _::cpp_type<T>::id(m_world);
        ecs_assert(_::cpp_type<T>::size() != 0, ECS_INVALID_PARAMETER, NULL);
        return ref<T>(m_world, m_id);
    }

    /** Clear an entity.
     * This operation removes all components from an entity without recycling
     * the entity id.
     */
    void clear() const {
        ecs_clear(m_world, m_id);
    }

    /** Delete an entity.
     * Entities have to be deleted explicitly, and are not deleted when the
     * flecs::entity object goes out of scope.
     */
    void destruct() const {
        ecs_delete(m_world, m_id);
    }

    /** Used by builder class. Do not invoke (deprecated). */
    template <typename Func>
    void invoke(Func&& action) const {
        action(m_world, m_id);
    }

    /** Entity id 0.
     * This function is useful when the API must provide an entity object that
     * belongs to a world, but the entity id is 0.
     *
     * @param world The world.
     */
    static
    flecs::entity null(const flecs::world& world) {
        return flecs::entity(world.get_world().c_ptr(), 
            static_cast<entity_t>(0));
    }

    static
    flecs::entity null() {
        return flecs::entity(static_cast<entity_t>(0));
    }     
};

/** Prefab class */
class prefab final : public entity {
public:
    explicit prefab(world_t *world, const char *name = nullptr) 
        : entity(world, name)
    {
        this->add(flecs::Prefab);
    }
};

} // namespace flecs
