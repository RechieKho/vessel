#ifndef VIEW_HPP
#define VIEW_HPP

#include "container.hpp"
#include "def.hpp"

namespace Vessel {

template <typename PType>
concept IsViewSubTypesAvailable = requires {
  typename PType::ContainerType;

  requires IsCollectionSubTypesAvailable<PType>;
  requires IsContainer<typename PType::ContainerType>;
  requires IsSameType<typename PType::ContainerType::KeyType,
                      typename PType::KeyType>;
  requires IsSameType<typename PType::ContainerType::ValueType,
                      typename PType::ValueType>;
};

/// An immutable, non-owning collection of data.
template <typename PType>
concept IsView = requires {
  requires IsViewSubTypesAvailable<PType>;
  requires IsCollection<PType>;
  requires IsCopyableFrom<typename PType::ContainerType, PType>;

  {
    declval<const PType>()[declval<typename PType::KeyType>()]
  } -> IsSameType<const typename PType::ValueType &>;
};

} // namespace Vessel

#endif // VIEW_HPP