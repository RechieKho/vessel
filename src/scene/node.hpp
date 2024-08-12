#ifndef NODE_HPP
#define NODE_HPP

#include "controller.hpp"
#include "def.hpp"
#include "text.hpp"

namespace Ragine {

template <typename Type>
concept IsNode = 
  requires {
    typename Type::MainControllerType;
    typename Type::NodeListType;
  } &&
  IsKeyTypeAvailable<Type> &&
  IsMainController<typename Type::MainControllerType> &&
  IsList<typename Type::NodeListType> &&
  IsSameType<typename Type::NodeListType::ValueType, Type> &&
  requires {
    Type(declval<typename Type::MainControllerType>());
    { declval<Type>().get_children() } -> IsSameType<typename Type::NodeListType>;
    { declval<Type>().get_child(declval<SizeType>()) } -> IsSameType<Type>;
    { declval<Type>().get_node(declval<typename Type::KeyType>()) } -> IsSameType<Type>;
    { declval<Type>().ready() } -> IsSameType<void>;
    { declval<Type>().process(declval<Float>()) } -> IsSameType<void>;
    { declval<Type>().draw2D() } -> IsSameType<void>;
  };

} // namespace Ragine

#endif // NODE_HPP