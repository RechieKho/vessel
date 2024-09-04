#ifndef SET_HPP
#define SET_HPP

#include "collection.hpp"
#include "def.hpp"

namespace Vessel {

template <typename PType>
concept IsSetSubTypesAvailable = requires {
  requires IsCollectionSubTypesAvailable<PType>;
  requires IsComparable<typename PType::ValueType>;

  typename PType::FindType;
  requires IsComparable<typename PType::ValueType, typename PType::FindType>;
};

/// A unindexed collection of data.
template <typename PType>
concept IsSet = requires {
  requires IsSetSubTypesAvailable<PType>;
  requires IsCollection<PType>;
  requires IsEqualityAvailable<PType>;

  {
    declval<PType>().find(declval<typename PType::FindType>())
  } -> IsSameType<typename PType::ValueType &>;
  {
    declval<const PType>().find(declval<typename PType::FindType>())
  } -> IsSameType<const typename PType::ValueType &>;
  {
    declval<PType>().insert(declval<typename PType::ValueType>())
  } -> IsSameType<void>;
  {
    declval<PType>().remove(declval<typename PType::FindType>())
  } -> IsSameType<void>;
};

} // namespace Vessel

#endif // SET_HPP