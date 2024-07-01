#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include "def.hpp"

namespace Ragine {

template <typename Type>
concept IsVector2D = requires(Type p_vector) {
  IsArithmaticAvailable<Type>;
  IsValueTypeAvailable<Type>;
  IsNumeric<typename Type::ValueType>;
  IsSintTypeAvailable<Type>;
  IsFloatTypeAvailable<Type>;

  IsSameType<decltype(p_vector.x), typename Type::ValueType &>;
  IsSameType<decltype(p_vector.y), typename Type::ValueType &>;
  IsSameType<decltype(p_vector.w), typename Type::ValueType &>;
  IsSameType<decltype(p_vector.h), typename Type::ValueType &>;

  { p_vector *declval<typename Type::SintType>() } -> IsSameType<Type>;
  { p_vector *declval<typename Type::FloatType>() } -> IsSameType<Type>;
  { p_vector / declval<typename Type::SintType>() } -> IsSameType<Type>;
  { p_vector / declval<typename Type::FloatType>() } -> IsSameType<Type>;

  { p_vector.compute_dot(p_vector) } -> IsSameType<typename Type::FloatType>;
  { p_vector.compute_length() } -> IsSameType<typename Type::FloatType>;
  { p_vector.compute_length_squared() } -> IsSameType<typename Type::FloatType>;
  { p_vector.compute_normalized() } -> IsSameType<Type>;
  {
    p_vector.compute_rotated(declval<typename Type::FloatType>())
    } -> IsSameType<Type>;
  { p_vector.compute_reflected(p_vector) } -> IsSameType<Type>;
  {
    Type::lerp(p_vector, p_vector, declval<typename Type::FloatType>())
    } -> IsSameType<Type>;
  { Type::clamp(p_vector, p_vector, p_vector) } -> IsSameType<Type>;
  {
    Type::clamp_length(p_vector, declval<typename Type::ValueType>(),
                       declval<typename Type::ValueType>())
    } -> IsSameType<Type>;
};

} // namespace Ragine

#endif // VECTOR2D_HPP