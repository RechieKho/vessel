#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "def.hpp"

namespace Ragine {

template <typename Type>
concept IsWindowController = 
  requires {
    { declval<Type>().set_fullscreen(declval<Bool>()) } -> IsSameType<void>;
  };

template <typename Type>
concept IsMainController = 
  IsWindowController<decltype(declval<Type>().window)>;

} // namespace Ragine

#endif // CONTROLLER_HPP