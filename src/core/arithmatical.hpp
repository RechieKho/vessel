#ifndef ARITHMATICAL_HPP
#define ARITHMATICAL_HPP

#include "def.hpp"

template <typename Type>
concept IsArithmatical = requires(Type p_object) {
    IsComparable<Type>;

    { p_object + p_object } -> IsSameType<Type>;
    { p_object - p_object } -> IsSameType<Type>;
    { p_object *p_object } -> IsSameType<Type>;
    { p_object / p_object } -> IsSameType<Type>;
};

#endif // ARITHMATICAL_HPP