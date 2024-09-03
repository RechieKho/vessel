#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_translate_exception.hpp>

#include "holder.hpp"
#include "impl/reference_holder.hpp"
#include "impl/unique_holder.hpp"

using namespace Vessel;

CATCH_TRANSLATE_EXCEPTION(const Exception<> &p_exception) {
  return p_exception.what();
}

TEMPLATE_PRODUCT_TEST_CASE("Holder types test cases.", "[map]",
                           (ReferenceHolder, UniqueHolder), (Uint)) {
  static_assert(IsHolder<TestType>);

  SECTION("Test dereferencing.") {
    auto number_pointer = new Uint;
    *number_pointer = 5;
    auto holder = TestType(number_pointer);
    REQUIRE(*holder == 5);
  }
}