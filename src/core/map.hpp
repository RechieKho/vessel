#ifndef MAP_HPP
#define MAP_HPP

#include "container.hpp"
#include "list.hpp"

namespace Vessel {

template <typename PType>
concept IsMapSubTypesAvailable = requires {
  typename PType::KeyListType;
  typename PType::ValueListType;

  requires IsContainerSubTypesAvailable<PType>;
  requires IsComparable<typename PType::KeyType>;
  requires IsEqualityAvailable<typename PType::ValueType>;
  requires IsList<typename PType::KeyListType>;
  requires IsSameType<typename PType::KeyListType::ValueType,
                      typename PType::KeyType>;
  requires IsList<typename PType::ValueListType>;
  requires IsSameType<typename PType::ValueListType::ValueType,
                      typename PType::ValueType>;
};

/// A container in which a key maps to a value.
template <typename PType>
concept IsMap = requires {
  requires IsMapSubTypesAvailable<PType>;
  requires IsContainer<PType>;
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