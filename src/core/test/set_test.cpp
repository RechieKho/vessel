#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_translate_exception.hpp>

#include "impl/binary_tree_set.hpp"
#include "set.hpp"

using namespace Vessel;

CATCH_TRANSLATE_EXCEPTION(const Exception<> &p_exception) {
  return p_exception.what();
}

TEMPLATE_PRODUCT_TEST_CASE("Set types test cases.", "[set]", (BinaryTreeSet),
                           (Uint)) {
  static_assert(IsSet<TestType>);

  FAIL("Unimplemented Test.");
}