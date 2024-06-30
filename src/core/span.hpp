#ifndef SPAN_HPP
#define SPAN_HPP

#include "view.hpp"

namespace Ragine {

/// A view of contiguous memory.
template <typename Type>
concept IsSpan = requires(Type p_span) {
  IsView<Type>;
  IsComparable<Type>;
  IsComparable<typename Type::ValueType>;
  IsSameType<typename Type::KeyType, SizeType>;

  {
    p_span.slice(declval<typename Type::KeyType>(),
                 declval<typename Type::KeyType>())
    } -> IsSameType<Type>;
  {
    Type(declval<typename Type::ValueType *>(),
         declval<typename Type::SizeType>())
    } -> IsSameType<Type>;
};

} // namespace Ragine

#endif // SPAN_HPP