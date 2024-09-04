#ifndef MAP_HPP
#define MAP_HPP

#include "list.hpp"
#include "table.hpp"

namespace Vessel {

template <typename PType>
concept IsMapSubTypesAvailable = requires {
  requires IsTableSubTypesAvailable<PType>;
  requires IsComparable<typename PType::KeyType>;
  requires IsEqualityAvailable<typename PType::ValueType>;

  typename PType::KeyListType;
  requires IsList<typename PType::KeyListType>;
  requires IsSameType<typename PType::KeyListType::ValueType,
                      typename PType::KeyType>;

  typename PType::ValueListType;
  requires IsList<typename PType::ValueListType>;
  requires IsSameType<typename PType::ValueListType::ValueType,
                      typename PType::ValueType>;
};

/// A table in which a key maps to a value.
template <typename PType>
concept IsMap = requires {
  requires IsMapSubTypesAvailable<PType>;
  requires IsTable<PType>;
  requires IsEqualityAvailable<PType>;

  {
    declval<const PType>().compute_keys()
  } -> IsSameType<typename PType::KeyListType>;
  {
    declval<const PType>().compute_values()
  } -> IsSameType<typename PType::ValueListType>;
  {
    declval<const PType>().contain_key(
        declval<const typename PType::KeyType &>())
  } -> IsSameType<Bool>;
};

} // namespace Vessel

#endif // MAP_HPP