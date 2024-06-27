#ifndef VIEW_HPP
#define VIEW_HPP

#include "def.hpp"
#include "container.hpp"

/// An immutable, non-owning collection of data.
template <typename Type>
concept IsView = requires(Type p_span) {
    IsCollection<Type>;

    typename Type::CloneType;
    IsContainer<typename Type::ContainerType>;
    IsSameType<typename Type::ContainerType::KeyType, typename Type::KeyType>;
    IsSameType<typename Type::ContainerType::ValueType, typename Type::ValueType>;

    { p_span.clone() } -> IsSameType<typename Type::CloneType>;
};

#endif // VIEW_HPP