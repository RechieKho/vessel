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
  IsIterable<Type>;

  { p_collection.get_count() } -> IsSameType<typename Type::SizeType>;
  {
    p_collection.contain(declval<typename Type::ValueType>())
    } -> IsSameType<Bool>;
};

} // namespace Ragine

#endif // COLLECTION_HPP