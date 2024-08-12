#ifndef VIEW_HPP
#define VIEW_HPP

#include "container.hpp"
#include "def.hpp"

namespace Ragine {

/// An immutable, non-owning collection of data.
template <typename Type>
concept IsView = 
  requires {
    typename Type::CloneType;
  } &&
  IsCollection<Type> &&
  IsContainer<typename Type::ContainerType> &&
  IsSameType<typename Type::ContainerType::KeyType, typename Type::KeyType> &&
  IsSameType<typename Type::ContainerType::ValueType, typename Type::ValueType> &&
  requires {
    { declval<Type>()[declval<typename Type::KeyType>()] } -> IsSameType<const typename Type::ValueType &>;
    { declval<Type>().clone() } -> IsSameType<typename Type::CloneType>;
  };

} // namespace Ragine

#endif // VIEW_HPP