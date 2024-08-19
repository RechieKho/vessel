#ifndef HOLDER_TEST_HPP
#define HOLDER_TEST_HPP

#include <catch2/catch_test_macros.hpp>

#include "def.hpp"
#include "holder.hpp"

namespace Vessel::HolderTest {

template <IsHolder HolderType>
  requires IsUnsignedInteger<typename HolderType::ValueType>
auto test_uint_holder_deref() -> void {
  auto number_pointer = new Uint;
  *number_pointer = 5;
  auto holder = HolderType(number_pointer);
  REQUIRE(*holder == 5);
}

template <IsHolder HolderType>
  requires IsUnsignedInteger<typename HolderType::ValueType>
auto test_uint_holder() -> void {
  test_uint_holder_deref<HolderType>();
}

} // namespace Vessel::HolderTest

#endif // HOLDER_TEST_HPP