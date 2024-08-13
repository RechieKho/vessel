#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "collection.hpp"
#include "def.hpp"

namespace Vessel {

/// A mutable, owned collection of data.
template <typename Type>
concept IsContainer = IsCollection<Type> && requires {
  { declval<Type>().clone() } -> IsSameType<Type>;
  {
    declval<Type>()[declval<typename Type::KeyType>()]
  } -> IsSameType<typename Type::ValueType &>;
  {
    declval<Type>().insert(declval<typename Type::KeyType>(),
                           declval<typename Type::ValueType>())
  } -> IsSameType<void>;
  {
    declval<Type>().remove(declval<typename Type::KeyType>())
  } -> IsSameType<typename Type::ValueType>;
};

} // namespace Vessel

#endif // CONTAINER_HPP