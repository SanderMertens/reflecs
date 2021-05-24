
namespace flecs {

namespace _ {
    struct pair_base { };   
} // _


// Type that represents a pair and can encapsulate a temporary value
template <typename R, typename O, typename Type = R>
struct pair : _::pair_base { 
    // Traits used to deconstruct the pair
    using type = Type;
    using relation = R;
    using object = O;

    pair(Type& v) : ref_(v) { }

    // This allows the class to be used as a temporary object
    pair(const Type& v) : ref_(const_cast<Type&>(v)) { }

    operator Type&() { 
        return ref_;
    }

    operator const Type&() const { 
        return ref_;
    }    

    Type* operator->() {
        return &ref_;
    }

    const Type* operator->() const {
        return &ref_;
    }

    Type& operator*() {
        return &ref_;
    }

    const Type& operator*() const {
        return ref_;
    }
    
private:
    Type& ref_;
};

// A pair_object is a pair where the type is determined by the object
template <typename R, typename O>
using pair_object = pair<R, O, O>;


// Utilities to test if type is a pair
template <typename T>
struct is_pair {
    static constexpr bool value = is_base_of<_::pair_base, remove_reference_t<T> >::value;
};


// Get actual type, relation or object from pair while preserving cv qualifiers.
template <typename P>
using pair_relation_t = transcribe_cv_t<remove_reference_t<P>, typename remove_reference_t<P>::relation>;

template <typename P>
using pair_object_t = transcribe_cv_t<remove_reference_t<P>, typename remove_reference_t<P>::object>;

template <typename P>
using pair_type_t = transcribe_cv_t<remove_reference_t<P>, typename remove_reference_t<P>::type>;


// Get actual type from a regular type or pair
template <typename T, typename U = int>
struct actual_type;

template <typename T>
struct actual_type<T, if_not_t< is_pair<T>::value >> {
    using type = T;
};

template <typename T>
struct actual_type<T, if_t< is_pair<T>::value >> {
    using type = pair_type_t<T>;
};

template <typename T>
using actual_type_t = typename actual_type<T>::type;


// Get type without const, *, &
template<typename T>
struct base_type {
    using type = remove_pointer_t< decay_t< actual_type_t<T> > >;
};

template <typename T>
using base_type_t = typename base_type<T>::type;


// Get type without *, & (retains const which is useful for function args)
template<typename T>
struct base_arg_type {
    using type = remove_pointer_t< remove_reference_t< actual_type_t<T> > >;
};

template <typename T>
using base_arg_type_t = typename base_arg_type<T>::type;


// Test if type is the same as its actual type
template <typename T>
struct is_actual {
    static constexpr bool value = std::is_same<T, actual_type_t<T> >::value;
};

} // flecs
