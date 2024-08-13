#ifndef TEXT_HPP
#define TEXT_HPP

#include "list.hpp"

namespace Vessel {

template <typename Type, typename CharType = Char>
concept IsText = IsList<Type> && IsSameType<typename Type::ValueType, CharType>;

} // namespace Vessel

#endif // TEXT_HPP