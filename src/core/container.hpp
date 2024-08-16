#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "collection.hpp"
#include "def.hpp"

namespace Vessel {

template <typename PType>
concept IsContainerSubTypesAvailable = IsCollectionSubTypesAvailable<PType>;

/// A mutable, owned collection of data.
template <typename PType>
concept IsContainer =
    IsContainerSubTypesAvailable<PType> && IsCollection<PType> &&
    IsCopyableFrom<PType> && IsMovableFrom<PType> &&
    IsDefaultConstructible<PType> && requires {
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

#endif // CONTAINER_HPP