#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include "def.hpp"
#include "arithmatical.hpp"

template <typename Type>
concept IsVector2D = requires(Type p_vector) {
    IsArithmatical<Type>;

    { p_vector.x } -> IsSameType<Float &>;
    { p_vector.y } -> IsSameType<Float &>;
    { p_vector.w } -> IsSameType<Float &>;
    { p_vector.h } -> IsSameType<Float &>;

    { p_vector *declval<Sint>() } -> IsSameType<Type>;
    { p_vector *declval<Float>() } -> IsSameType<Type>;
    { p_vector / declval<Sint>() } -> IsSameType<Type>;
    { p_vector / declval<Float>() } -> IsSameType<Type>;

    { p_vector.dot(p_vector) } -> IsSameType<Float>;
    { p_vector.compute_length() } -> IsSameType<Float>;
    { p_vector.compute_length_squared() } -> IsSameType<Float>;
};

#endif // VECTOR2D_HPP