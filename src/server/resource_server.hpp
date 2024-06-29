#ifndef RESOURCE_SERVER_HPP
#define RESOURCE_SERVER_HPP

#include "server.hpp"

namespace Ragine {

template <typename Type>
concept IsResourceServer = requires(Type &p_server) {
  IsServer<Type>;
};

} // namespace Ragine

#endif // RESOURCE_SERVER_HPP