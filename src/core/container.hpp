#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "def.hpp"
#include "collection.hpp"

/// A mutable, owned collection of data.
template <typename Type>
concept IsContainer = requires(Type p_container) {
    IsCollection<Type>;

    { p_container.clone() } -> IsSameType<Type>;
    { p_container.insert(declval<typename Type::KeyType>(), declval<typename Type::ValueType>()) } -> IsSameType<void>;
    { p_container.remove(declval<typename Type::KeyType>()) } -> IsSameType<typename Type::ValueType>;
};

#endif // CONTAINER_HPP