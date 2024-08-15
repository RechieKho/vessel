#ifndef MAP_HPP
#define MAP_HPP

#include "container.hpp"
#include "list.hpp"

namespace Vessel {

template <typename PType>
concept IsMapSubTypesAvailable =
    requires {
      typename PType::KeyListType;
      typename PType::ValueListType;
    } && IsContainerSubTypesAvailable<PType> &&
    IsComparable<typename PType::KeyType> &&
    IsEqualityAvailable<typename PType::ValueType> &&
    IsList<typename PType::KeyListType> &&
    IsSameType<typename PType::KeyListType::ValueType,
               typename PType::KeyType> &&
    IsList<typename PType::ValueListType> &&
    IsSameType<typename PType::ValueListType::ValueType,
               typename PType::ValueType>;

/// A container in which a key maps to a value.
template <typename PType>
concept IsMap = IsMapSubTypesAvailable<PType> && IsContainer<PType> &&
                IsEqualityAvailable<PType> && requires {
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