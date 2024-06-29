#ifndef AUDIO_SERVER_HPP
#define AUDIO_SERVER_HPP

#include "server.hpp"

namespace Ragine {

template <typename Type>
concept IsAudioServer = requires(Type &p_server) {
  IsServer<Type>;
};

} // namespace Ragine

#endif // AUDIO_SERVER_HPP