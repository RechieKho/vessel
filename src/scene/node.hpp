#ifndef NODE_HPP
#define NODE_HPP

#include "def.hpp"
#include "text.hpp"

template <typename Type>
concept IsNode = requires(Type p_node) {
    IsKeyTypeAvailable<Type>;

    typename Type::NodeListType;
    IsList<typename Type::NodeListType>;
    IsSameType<typename Type::NodeListType::ValueType, Type>;

    { p_node.get_children() } -> IsSameType<typename Type::NodeListType>;
    { p_node.get_child(declval<SizeType>()) } -> IsSameType<Type>;
    { p_node.get_node(declval<typename Type::KeyType>()) } -> IsSameType<Type>;

    { p_node.ready() } -> IsSameType<void>;
    { p_node.process(declval<Float>()) } -> IsSameType<void>;
    { p_node.draw2D() } -> IsSameType<void>;
};

#endif // NODE_HPP