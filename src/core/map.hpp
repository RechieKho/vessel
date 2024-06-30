#ifndef MAP_HPP
#define MAP_HPP

#include "container.hpp"
#include "list.hpp"

namespace Ragine {

/// A container in which a key maps to a value.
template <typename Type>
concept IsMap = requires(Type p_map) {
  IsContainer<Type>;
  IsEqualityAvailable<Type>;
  IsComparable<typename Type::KeyType>;
  IsEqualityAvailable<typename Type::ValueType>;

  typename Type::KeyListType;
  IsList<typename Type::KeyListType>;
  IsSameType<typename Type::KeyListType::ValueType, typename Type::KeyType>;

  typename Type::ValueListType;
  IsList<typename Type::ValueListType>;
  IsSameType<typename Type::ValueListType::ValueType, typename Type::ValueType>;

  { p_map.compute_keys() } -> IsSameType<typename Type::KeyListType>;
  { p_map.compute_values() } -> IsSameType<typename Type::ValueListType>;
  { p_map.contain_key(declval<typename Type::KeyType>()) } -> IsSameType<Bool>;
};

} // namespace Ragine

#endif // MAP_HPP