#ifndef SPAN_HPP
#define SPAN_HPP

#include "view.hpp"

namespace Vessel {

template <typename PType>
concept IsSpanSubTypesAvailable =
    IsViewSubTypesAvailable<PType> && IsComparable<typename PType::ValueType> &&
    IsSameType<typename PType::KeyType, SizeType>;

/// A view of contiguous memory.
template <typename PType>
concept IsSpan =
    IsSpanSubTypesAvailable<PType> && IsView<PType> && IsComparable<PType> &&
    requires {
      {
        declval<const PType>().slice(declval<typename PType::KeyType>(),
                                     declval<typename PType::KeyType>())
      } -> IsSameType<PType>;
      {
        PType(declval<typename PType::ValueType *>(),
              declval<typename PType::SizeType>())
      } -> IsSameType<PType>;
    };

} // namespace Vessel

#endif // SPAN_HPP