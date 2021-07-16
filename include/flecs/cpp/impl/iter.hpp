
namespace flecs
{

inline flecs::entity iter::system() const {
    return flecs::entity(m_iter->world, m_iter->system);
}

 inline flecs::entity iter::self() const {
    return flecs::entity(m_iter->world, m_iter->self);
}

inline flecs::world iter::world() const {
    return flecs::world(m_iter->world);
}

inline flecs::entity iter::entity(size_t row) const {
    ecs_assert(row < static_cast<size_t>(m_iter->count), ECS_COLUMN_INDEX_OUT_OF_RANGE, NULL);
    if (!this->world().is_readonly()) {
        return flecs::entity(m_iter->entities[row])
            .mut(this->world());
    } else {
        return flecs::entity(this->world().c_ptr(), m_iter->entities[row]);
    }
}

/* Obtain column source (0 if self) */
template <typename Base>
inline flecs::entity iter_deprecated<Base>::column_source(int32_t col) const {
    return flecs::entity(iter()->world, ecs_term_subject(iter(), col));
}

/* Obtain component/tag entity of column */
template <typename Base>
inline flecs::entity iter_deprecated<Base>::column_entity(int32_t col) const {
    return flecs::entity(iter()->world, ecs_term_id(iter(), col));
}

/* Obtain type of column */
template <typename Base>
inline type iter_deprecated<Base>::column_type(int32_t col) const {
    return flecs::type(iter()->world, ecs_column_type(iter(), col));
}

/* Obtain type of table being iterated over */
template <typename Base>
inline type iter_deprecated<Base>::table_type() const {
    return flecs::type(iter()->world, ecs_iter_type(iter()));
}

template <typename T>
inline column<T>::column(iter &iter, int32_t index) {
    *this = iter.term<T>(index);
}

inline flecs::entity iter::term_source(int32_t index) const {
    return flecs::entity(m_iter->world, ecs_term_subject(m_iter, index));
}

inline flecs::entity iter::term_id(int32_t index) const {
    return flecs::entity(m_iter->world, ecs_term_id(m_iter, index));
}

/* Obtain type of iter */
inline flecs::type iter::type() const {
    return flecs::type(m_iter->world, ecs_iter_type(m_iter));
}

} // namespace flecs
