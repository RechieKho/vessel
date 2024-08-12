#ifndef MATRIX2D_HPP
#define MATRIX2D_HPP

#include "def.hpp"
#include "vector2d.hpp"

namespace Ragine {

template <typename Type>
concept IsMatrix2D = 
  IsArithmaticAvailable<Type> && 
  IsValueAvailable<Type> &&
  IsVector2D<typename Type::ValueType> && 
  IsSintTypeAvailable<Type> &&
  IsFloatTypeAvailable<Type> &&
  IsSameType<decltype(declval<Type>().x), typename Type::ValueType &> &&
  IsSameType<decltype(declval<Type>().y), typename Type::ValueType &> &&
  requires(Type p_matrix) {
    { declval<Type>()*declval<typename Type::ValueType>() } -> IsSameType<typename Type::ValueType>;
    { declval<Type>().compute_determinant() } -> IsSameType<typename Type::FloatType>;
    { declval<Type>().compute_trace() } -> IsSameType<typename Type::ValueType::ValueType>;
    { declval<Type>().compute_rotated(declval<typename Type::FloatType>()) } -> IsSameType<Type>;
  };

} // namespace Ragine

#endif // MATRIX2D_HPP