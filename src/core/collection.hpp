#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "def.hpp"

namespace Vessel {

template <typename PType>
concept IsCollectionSubTypesAvailable = requires {
  requires IsValueTypeAvailable<PType>;
  requires IsSizeTypeAvailable<PType>;
};

/// A collection of data.
template <typename PType>
concept IsCollection = requires {
  requires IsCollectionSubTypesAvailable<PType>;
  requires IsCopyableFrom<PType>;
  requires IsMovableFrom<PType>;
  requires IsDefaultConstructible<PType>;
  requires IsIterable<PType>;
  requires IsConstantIterable<PType>;

  {
    declval<const PType>().get_count()
  } -> IsSameType<typename PType::SizeType>;
  {
    declval<const PType>().contain(declval<typename PType::ValueType>())
  } -> IsSameType<Bool>;
};

} // namespace Vessel

#endif // COLLECTION_HPP