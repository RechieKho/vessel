#ifndef SPAN_HPP
#define SPAN_HPP

#include "view.hpp"

namespace Vessel {

/// A view of contiguous memory.
template <typename Type>
concept IsSpan = IsView<Type> && IsComparable<Type> &&
                 IsComparable<typename Type::ValueType> &&
                 IsSameType<typename Type::KeyType, SizeType> && requires {
                   {
                     declval<Type>().slice(declval<typename Type::KeyType>(),
                                           declval<typename Type::KeyType>())
                   } -> IsSameType<Type>;
                   {
                     Type(declval<typename Type::ValueType *>(),
                          declval<typename Type::SizeType>())
                   } -> IsSameType<Type>;
                 };

} // namespace Vessel

#endif // SPAN_HPP