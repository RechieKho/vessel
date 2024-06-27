#ifndef VIEW_HPP
#define VIEW_HPP

#include "def.hpp"
#include "container.hpp"

namespace Ragine
{

    /// An immutable, non-owning collection of data.
    template <typename Type>
    concept IsView = requires(Type p_view) {
        IsCollection<Type>;

        typename Type::CloneType;
        IsContainer<typename Type::ContainerType>;
        IsSameType<typename Type::ContainerType::KeyType, typename Type::KeyType>;
        IsSameType<typename Type::ContainerType::ValueType, typename Type::ValueType>;

        { p_view[declval<typename Type::KeyType>()] } -> IsSameType<const typename Type::ValueType &>;
        { p_view.clone() } -> IsSameType<typename Type::CloneType>;
    };

} // namespace Ragine

#endif // VIEW_HPP