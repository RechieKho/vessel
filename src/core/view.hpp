#ifndef VIEW_HPP
#define VIEW_HPP

#include "container.hpp"
#include "def.hpp"

namespace Vessel {

template <typename PType>
concept IsViewSubTypesAvailable =
    requires { typename PType::ContainerType; } &&
    IsCollectionSubTypesAvailable<PType> &&
    IsContainer<typename PType::ContainerType> &&
    IsSameType<typename PType::ContainerType::KeyType,
               typename PType::KeyType> &&
    IsSameType<typename PType::ContainerType::ValueType,
               typename PType::ValueType>;

/// An immutable, non-owning collection of data.
template <typename PType>
concept IsView =
    IsViewSubTypesAvailable<PType> && IsCollection<PType> &&
    IsCopyableFrom<typename PType::ContainerType, PType> && requires {
      {
        declval<const PType>()[declval<typename PType::KeyType>()]
      } -> IsSameType<const typename PType::ValueType &>;
    };

} // namespace Vessel

#endif // VIEW_HPP