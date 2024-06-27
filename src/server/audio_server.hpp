#ifndef AUDIO_SERVER_HPP
#define AUDIO_SERVER_HPP

#include "server.hpp"

template <typename Type>
concept IsAudioServer = requires(Type &p_server) {
    IsServer<Type>;
};

#endif // AUDIO_SERVER_HPP