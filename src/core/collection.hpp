#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "def.hpp"

namespace Ragine {

/// A collection of data.
template <typename Type>
concept IsCollection =
  IsValueTypeAvailable<Type> && 
  IsKeyTypeAvailable<Type> &&
  IsSizeTypeAvailable<Type> && 
  IsIterable<Type> &&
  requires {
    { declval<const Type>().get_count() } -> IsSameType<typename Type::SizeType>;
    { declval<const Type>().contain(declval<const typename Type::ValueType &>()) } -> IsSameType<Bool>;
  };

} // namespace Ragine

#endif // COLLECTION_HPP