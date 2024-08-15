#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "def.hpp"

namespace Vessel {

template <typename PType>
concept IsCollectionSubTypesAvailable =
    IsValueTypeAvailable<PType> && IsKeyTypeAvailable<PType> &&
    IsSizeTypeAvailable<PType>;

/// A collection of data.
template <typename PType>
concept IsCollection =
    IsCollectionSubTypesAvailable<PType> && IsIterable<PType> &&
    IsConstantIterable<PType> && requires {
      {
        declval<const PType>().get_count()
      } -> IsSameType<typename PType::SizeType>;
      {
        declval<const PType>().contain(declval<typename PType::ValueType>())
      } -> IsSameType<Bool>;
    };

} // namespace Vessel

#endif // COLLECTION_HPP