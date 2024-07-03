#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "def.hpp"

namespace Ragine {

template <typename Type>
concept IsWindowController = requires(Type p_controller) {
  { p_controller.set_fullscreen(declval<Bool>()) } -> IsSameType<void>;
};

template <typename Type>
concept IsMainController = requires(Type p_controller) {
  IsWindowController<decltype(p_controller.window)>;
};

} // namespace Ragine

#endif // CONTROLLER_HPP