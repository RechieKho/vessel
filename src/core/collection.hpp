#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "def.hpp"

/// A collection of data.
template <typename Type>
concept IsCollection = requires(Type p_collection) {
    IsValueTypeAvailable<Type>;
    IsKeyTypeAvailable<Type>;
    IsSizeTypeAvailable<Type>;
    IsComparable<Type>;
    IsIterable<Type>;

    { p_collection.get_count() } -> IsSameType<typename Type::SizeType>;
    { p_collection[declval<typename Type::KeyType>()] } -> IsSameType<typename Type::ValueType>;
    { p_collection.slice(declval<typename Type::KeyType>(), declval<typename Type::KeyType>()) } -> IsSameType<Type>;
};

#endif // COLLECTION_HPP