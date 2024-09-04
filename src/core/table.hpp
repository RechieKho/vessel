#ifndef TABLE_HPP
#define TABLE_HPP

#include "collection.hpp"
#include "def.hpp"

namespace Vessel {

template <typename PType>
concept IsTableSubTypesAvailable = requires {
  requires IsCollectionSubTypesAvailable<PType>;
  requires IsKeyTypeAvailable<PType>;
};

/// An indexed collection of data.
template <typename PType>
concept IsTable = requires {
  requires IsTableSubTypesAvailable<PType>;
  requires IsCollection<PType>;

  {
    declval<PType>()[declval<typename PType::KeyType>()]
  } -> IsSameType<typename PType::ValueType &>;
  {
    declval<const PType>()[declval<typename PType::KeyType>()]
  } -> IsSameType<const typename PType::ValueType &>;
  {
    declval<PType>().insert(declval<typename PType::KeyType>(),
                            declval<typename PType::ValueType>())
  } -> IsSameType<void>;
  {
    declval<PType>().remove(declval<typename PType::KeyType>())
  } -> IsSameType<typename PType::ValueType>;
};

} // namespace Vessel

#endif // TABLE_HPP