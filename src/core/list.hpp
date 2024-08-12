#ifndef LIST_HPP
#define LIST_HPP

#include "container.hpp"

namespace Ragine {

/// A container with element arranged in series.
template <typename Type>
concept IsList = 
  IsContainer<Type> && 
  IsComparable<Type> &&
  IsComparable<typename Type::ValueType> &&
  IsSameType<typename Type::KeyType, typename Type::SizeType> &&
  requires {
    { declval<const Type>().slice(declval<typename Type::KeyType>(), declval<typename Type::KeyType>()) } -> IsSameType<Type>;
    { declval<Type>() << declval<typename Type::ValueType>() } -> IsSameType<Type &>;
    { declval<Type>().push_back(declval<typename Type::ValueType>()) } -> IsSameType<void>;
    { declval<Type>().push_front(declval<typename Type::ValueType>()) } -> IsSameType<void>;
    { declval<Type>().pop_back() } -> IsSameType<typename Type::ValueType>;
    { declval<Type>().pop_front() } -> IsSameType<typename Type::ValueType>;
  };

} // namespace Ragine

#endif // LIST_HPP