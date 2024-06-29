#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "def.hpp"

namespace Ragine {

/// A collection of data.
template <typename Type>
concept IsCollection = requires(Type p_collection) {
  IsValueTypeAvailable<Type>;
  IsKeyTypeAvailable<Type>;
  IsSizeTypeAvailable<Type>;
  IsComparable<Type>;
  IsIterable<Type>;

  IsComparable<typename Type::ValueType>;
  IsComparable<typename Type::KeyType>;

  { p_collection.get_count() } -> IsSameType<typename Type::SizeType>;
  {
    p_collection.slice(declval<typename Type::KeyType>(),
                       declval<typename Type::KeyType>())
    } -> IsSameType<Type>;
};

} // namespace Ragine

#endif // COLLECTION_HPP