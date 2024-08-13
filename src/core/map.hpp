#ifndef MAP_HPP
#define MAP_HPP

#include "container.hpp"
#include "list.hpp"

namespace Vessel {

/// A container in which a key maps to a value.
template <typename Type>
concept IsMap =
    requires {
      typename Type::KeyListType;
      typename Type::ValueListType;
    } && IsList<typename Type::KeyListType> &&
    IsSameType<typename Type::KeyListType::ValueType, typename Type::KeyType> &&
    IsList<typename Type::ValueListType> &&
    IsSameType<typename Type::ValueListType::ValueType,
               typename Type::ValueType> &&
    IsContainer<Type> && IsEqualityAvailable<Type> &&
    IsComparable<typename Type::KeyType> &&
    IsEqualityAvailable<typename Type::ValueType> && requires {
      {
        declval<Type>().compute_keys()
      } -> IsSameType<typename Type::KeyListType>;
      {
        declval<Type>().compute_values()
      } -> IsSameType<typename Type::ValueListType>;
      {
        declval<Type>().contain_key(declval<typename Type::KeyType>())
      } -> IsSameType<Bool>;
    };

} // namespace Vessel

#endif // MAP_HPP