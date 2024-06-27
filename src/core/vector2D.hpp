#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include "def.hpp"
#include "arithmatical.hpp"

template <typename Type>
concept IsVector2D = requires(Type p_vector) {
    IsArithmatical<Type>;
    IsSintTypeAvailable<Type>;
    IsFloatTypeAvailable<Type>;

    IsSameType<AsPure<decltype(p_vector.x)>, typename Type::FloatType>;
    IsSameType<AsPure<decltype(p_vector.y)>, typename Type::FloatType>;
    IsSameType<AsPure<decltype(p_vector.w)>, typename Type::FloatType>;
    IsSameType<AsPure<decltype(p_vector.h)>, typename Type::FloatType>;

    { p_vector *declval<typename Type::SintType>() } -> IsSameType<Type>;
    { p_vector *declval<typename Type::FloatType>() } -> IsSameType<Type>;
    { p_vector / declval<typename Type::SintType>() } -> IsSameType<Type>;
    { p_vector / declval<typename Type::FloatType>() } -> IsSameType<Type>;

    { p_vector.dot(p_vector) } -> IsSameType<typename Type::FloatType>;
    { p_vector.compute_length() } -> IsSameType<typename Type::FloatType>;
    { p_vector.compute_length_squared() } -> IsSameType<typename Type::FloatType>;
};

#endif // VECTOR2D_HPP