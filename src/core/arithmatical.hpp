#ifndef ARITHMATICAL_HPP
#define ARITHMATICAL_HPP

#include "def.hpp"

namespace Ragine
{

    template <typename Type>
    concept IsArithmatical = requires(Type p_object) {
        IsComparable<Type>;

        { p_object + p_object } -> IsSameType<Type>;
        { p_object - p_object } -> IsSameType<Type>;
        { p_object *p_object } -> IsSameType<Type>;
        { p_object / p_object } -> IsSameType<Type>;
    };

} // namespace Ragine

#endif // ARITHMATICAL_HPP