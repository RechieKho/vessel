#ifndef SERVER_HPP
#define SERVER_HPP

#include "def.hpp"

template <typename Type>
concept IsServer = requires {
    { Type::get_instance() } -> IsSameType<Type &>;
};

#endif // SERVER_HPP