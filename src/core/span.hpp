#ifndef SPAN_HPP
#define SPAN_HPP

#include "view.hpp"

namespace Ragine {

/// A view of contiguous memory.
template <typename Type>
concept IsSpan = requires {
  IsView<Type>;

  {
    Type(declval<typename Type::ValueType *>(),
         declval<typename Type::SizeType>())
    } -> IsSameType<Type>;
};

} // namespace Ragine

#endif // SPAN_HPP