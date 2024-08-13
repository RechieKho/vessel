#include <catch2/catch_test_macros.hpp>
#include <exception>

#include "impl/array_list.hpp"
#include "list_test.hpp"

using namespace Vessel;

TEST_CASE("`ArrayList` implementation", "[ArrayList]") {
  try {
    ListTest::test_uint_list<ArrayList<Uint>>();
  } catch (UnimplementedException<> p_exception) {
    throw std::runtime_error(p_exception.what());
  }
}