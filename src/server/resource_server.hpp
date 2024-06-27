#ifndef RESOURCE_SERVER_HPP
#define RESOURCE_SERVER_HPP

#include "server.hpp"

template <typename Type>
concept IsResourceServer = requires(Type &p_server) {
    IsServer<Type>;
};

#endif // RESOURCE_SERVER_HPP