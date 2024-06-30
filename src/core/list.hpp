#ifndef LIST_HPP
#define LIST_HPP

#include "container.hpp"

namespace Ragine {

/// A container with element arranged in series.
template <typename Type>
concept IsList = requires(Type p_list) {
  IsContainer<Type>;
  IsComparable<Type>;
  IsComparable<typename Type::ValueType>;
  IsSameType<typename Type::KeyType, SizeType>;

  {
    p_list.slice(declval<typename Type::KeyType>(),
                 declval<typename Type::KeyType>())
    } -> IsSameType<Type>;
  { p_list << declval<typename Type::ValueType>() } -> IsSameType<void>;
  { p_list.push_back(declval<typename Type::ValueType>()) } -> IsSameType<void>;
  {
    p_list.push_front(declval<typename Type::ValueType>())
    } -> IsSameType<void>;
  {
    p_list.pop_back(declval<typename Type::KeyType>())
    } -> IsSameType<typename Type::ValueType>;
  {
    p_list.pop_front(declval<typename Type::KeyType>())
    } -> IsSameType<typename Type::ValueType>;
};

} // namespace Ragine

#endif // LIST_HPP