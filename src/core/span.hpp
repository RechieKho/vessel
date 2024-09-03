#ifndef SPAN_HPP
#define SPAN_HPP

#include "view.hpp"

namespace Vessel {

template <typename PType>
concept IsSpanSubTypesAvailable = requires {
  requires IsViewSubTypesAvailable<PType>;
  requires IsComparable<typename PType::ValueType>;
  requires IsSameType<typename PType::KeyType, SizeType>;
};

/// A view of contiguous memory.
template <typename PType>
concept IsSpan = requires {
  requires IsSpanSubTypesAvailable<PType>;
  requires IsView<PType>;
  requires IsComparable<PType>;

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