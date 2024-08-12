#ifndef TEXT_HPP
#define TEXT_HPP

#include "list.hpp"

namespace Ragine {

template <typename Type, typename CharType = Char>
concept IsText = 
    IsList<Type> && 
    IsSameType<typename Type::ValueType, CharType>;

} // namespace Ragine

#endif // TEXT_HPP