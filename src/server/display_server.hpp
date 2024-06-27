#ifndef DISPLAY_SERVER_HPP
#define DISPLAY_SERVER_HPP

#include "server.hpp"
#include "vector2D.hpp"

template <typename Type>
concept IsDisplayServer = requires(Type &p_server) {
    IsServer<Type>;

    typename Type::Vector2DType;
    IsVector2D<typename Type::Vector2DType>;

    { p_server.get_size() } -> IsSameType<typename Type::Vector2DType>;
};

#endif // DISPLAY_SERVER_HPP