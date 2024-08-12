#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include "def.hpp"

namespace Ragine {

template <typename Type>
concept IsVector2D = 
  IsArithmaticAvailable<Type> &&
  IsValueTypeAvailable<Type> && 
  IsNumeric<typename Type::ValueType> &&
  IsSintTypeAvailable<Type> && 
  IsFloatTypeAvailable<Type> &&
  IsSameType<decltype(declval<Type>().x), typename Type::ValueType &> &&
  IsSameType<decltype(declval<Type>().y), typename Type::ValueType &> &&
  IsSameType<decltype(declval<Type>().w), typename Type::ValueType &> &&
  IsSameType<decltype(declval<Type>().h), typename Type::ValueType &> &&
  requires {
    { declval<Type>() * declval<typename Type::SintType>() } -> IsSameType<Type>;
    { declval<Type>() * declval<typename Type::FloatType>() } -> IsSameType<Type>;
    { declval<Type>() / declval<typename Type::SintType>() } -> IsSameType<Type>;
    { declval<Type>() / declval<typename Type::FloatType>() } -> IsSameType<Type>;
    { declval<Type>().compute_dot(declval<Type>()) } -> IsSameType<typename Type::FloatType>;
    { declval<Type>().compute_length() } -> IsSameType<typename Type::FloatType>;
    { declval<Type>().compute_length_squared() } -> IsSameType<typename Type::FloatType>;
    { declval<Type>().compute_normalized() } -> IsSameType<Type>;
    { declval<Type>().compute_rotated(declval<typename Type::FloatType>()) } -> IsSameType<Type>;
    { declval<Type>().compute_reflected(declval<Type>()) } -> IsSameType<Type>;
    { Type::lerp(declval<Type>(), declval<Type>(), declval<typename Type::FloatType>()) } -> IsSameType<Type>;
    { Type::clamp(declval<Type>(), declval<Type>(), declval<Type>()) } -> IsSameType<Type>;
    { Type::clamp_length(declval<Type>(), declval<typename Type::ValueType>(), declval<typename Type::ValueType>()) } -> IsSameType<Type>;
  };

} // namespace Ragine

#endif // VECTOR2D_HPP