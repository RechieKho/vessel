#ifndef VIEW_HPP
#define VIEW_HPP

#include "container.hpp"
#include "def.hpp"

namespace Vessel {

template <typename PType>
concept IsViewSubTypesAvailable =
    requires {
      typename PType::CloneType;
      typename PType::ContainerType;
    } && IsContainerSubTypesAvailable<PType> &&
    IsContainer<typename PType::ContainerType> &&
    IsSameType<typename PType::ContainerType::KeyType,
               typename PType::KeyType> &&
    IsSameType<typename PType::ContainerType::ValueType,
               typename PType::ValueType>;

/// An immutable, non-owning collection of data.
template <typename PType>
concept IsView =
    IsViewSubTypesAvailable<PType> && IsCollection<PType> && requires {
      {
        declval<const PType>()[declval<typename PType::KeyType>()]
      } -> IsSameType<const typename PType::ValueType &>;
      {
        declval<const PType>().clone()
      } -> IsSameType<typename PType::CloneType>;
    };

} // namespace Vessel

#endif // VIEW_HPP