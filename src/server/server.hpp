#ifndef SERVER_HPP
#define SERVER_HPP

#include "def.hpp"

namespace Ragine
{

    template <typename Type>
    concept IsServer = requires {
        { Type::get_instance() } -> IsSameType<Type &>;
    };

} // namespace Ragine

#endif // SERVER_HPP