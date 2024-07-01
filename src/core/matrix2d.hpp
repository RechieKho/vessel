#ifndef MATRIX2D_HPP
#define MATRIX2D_HPP

#include "def.hpp"
#include "vector2d.hpp"

namespace Ragine {

template <typename Type>
concept IsMatrix2D = requires(Type p_matrix) {
  IsArithmaticAvailable<Type>;
  IsValueAvailable<Type>;
  IsVector2D<typename Type::ValueType>;
  IsSintTypeAvailable<Type>;
  IsFloatTypeAvailable<Type>;

  IsSameType<decltype(p_matrix.x), typename Type::ValueType &>;
  IsSameType<decltype(p_matrix.y), typename Type::ValueType &>;

  {
    p_matrix *declval<typename Type::ValueType>()
    } -> IsSameType<typename Type::ValueType>;

  { p_matrix.compute_determinant() } -> IsSameType<typename Type::FloatType>;
  {
    p_matrix.compute_trace()
    } -> IsSameType<typename Type::ValueType::ValueType>;
  {
    p_matrix.compute_rotated(declval<typename Type::FloatType>())
    } -> IsSameType<Type>;
};

} // namespace Ragine

#endif // MATRIX2D_HPP