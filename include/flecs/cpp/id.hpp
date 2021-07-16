
namespace flecs {

/** Class that stores a flecs id.
 * A flecs id is an identifier that can store an entity id, an relation-object 
 * pair, or role annotated id (such as SWITCH | Movement).
 */
class id : public world_base<id> {
public:
    explicit id(flecs::id_t value = 0) 
        : m_world(nullptr)
        , m_id(value) { }

    explicit id(flecs::world_t *world, flecs::id_t value = 0)
        : m_world(world)
        , m_id(value) { }

    explicit id(flecs::world_t *world, flecs::id_t relation, flecs::id_t object)
        : m_world(world)
        , m_id(ecs_pair(relation, object)) { }

    explicit id(flecs::id_t relation, flecs::id_t object)
        : m_world(nullptr)
        , m_id(ecs_pair(relation, object)) { }

    explicit id(const flecs::id& relation, const flecs::id& object)
        : m_world(relation.world())
        , m_id(ecs_pair(relation.m_id, object.m_id)) { }

    /** Test if id is pair (has relation, object) */
    bool is_pair() const {
        return (m_id & ECS_ROLE_MASK) == flecs::Pair;
    }

    /* Test if id is a wildcard */
    bool is_wildcard() const {
        return ecs_id_is_wildcard(m_id);
    }

    /* Test if id has the Switch role */
    bool is_switch() const {
        return (m_id & ECS_ROLE_MASK) == flecs::Switch;
    }

    /* Test if id has the Case role */
    bool is_case() const {
        return (m_id & ECS_ROLE_MASK) == flecs::Case;
    }

    /* Return id with role added */
    flecs::entity add_role(flecs::id_t role) const;

    /* Return id with role removed */
    flecs::entity remove_role(flecs::id_t role) const;

    /* Return id without role */
    flecs::entity remove_role() const;

    /* Return id without role */
    flecs::entity remove_generation() const;    

    /* Test if id has specified role */
    bool has_role(flecs::id_t role) const {
        return ((m_id & ECS_ROLE_MASK) == role);
    }

    /* Test if id has any role */
    bool has_role() const {
        return (m_id & ECS_ROLE_MASK) != 0;
    }

    flecs::entity role() const;

    /* Test if id has specified relation */
    bool has_relation(flecs::id_t relation) const {
        if (!is_pair()) {
            return false;
        }
        return ECS_PAIR_RELATION(m_id) == relation;
    }

    /** Get relation from pair.
     * If the id is not a pair, this operation will fail. When the id has a
     * world, the operation will ensure that the returned id has the correct
     * generation count.
     */
    flecs::entity relation() const;

    /** Get object from pair.
     * If the id is not a pair, this operation will fail. When the id has a
     * world, the operation will ensure that the returned id has the correct
     * generation count.
     */
    flecs::entity object() const;

    /* Convert id to string */
    flecs::string str() const {
        size_t size = ecs_id_str(m_world, m_id, NULL, 0);
        char *result = static_cast<char*>(ecs_os_malloc(
            static_cast<ecs_size_t>(size) + 1));
        ecs_id_str(m_world, m_id, result, size + 1);
        return flecs::string(result);
    }

    /** Convert role of id to string. */
    flecs::string role_str() const {
        return flecs::string_view( ecs_role_str(m_id & ECS_ROLE_MASK));
    }

    ECS_DEPRECATED("use object()")
    flecs::entity lo() const;

    ECS_DEPRECATED("use relation()")
    flecs::entity hi() const;

    ECS_DEPRECATED("use flecs::id(relation, object)")
    static 
    flecs::entity comb(entity_view lo, entity_view hi);

    flecs::id_t raw_id() const {
        return m_id;
    }

    operator flecs::id_t() const {
        return m_id;
    }

    /* World is optional, but guarantees that entity identifiers extracted from
     * the id are valid */
    flecs::world_t *m_world;
    flecs::id_t m_id;
};

}
