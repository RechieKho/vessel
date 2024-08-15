#include <catch2/catch_test_macros.hpp>
#include <exception>

#include "impl/array_list.hpp"
#include "impl/binary_tree_map.hpp"
#include "list_test.hpp"
#include "map_test.hpp"

using namespace Vessel;

TEST_CASE("`ArrayList` implementation", "[ArrayList]") {
  try {
    ListTest::test_uint_list<ArrayList<Uint>>();
  } catch (UnimplementedException<> p_exception) {
    throw std::runtime_error(p_exception.what());
  }
}

TEST_CASE("`BinaryTreeMap` implementation", "[BinaryTreeMap]") {
  try {
    MapTest::test_uint_to_uint_map<BinaryTreeMap<Uint, Uint>>();
  } catch (UnimplementedException<> p_exception) {
    throw std::runtime_error(p_exception.what());
  }
}