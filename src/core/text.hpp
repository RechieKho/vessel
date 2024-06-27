#ifndef TEXT_HPP
#define TEXT_HPP

#include "list.hpp"

template <typename Type, typename CharType = Char>
concept IsText = requires {
    IsList<Type>;
    IsSameType<typename Type::ValueType, CharType>;
};

#endif // TEXT_HPP