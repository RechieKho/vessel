#include <catch2/catch_test_macros.hpp>
#include <exception>

#include "holder_test.hpp"
#include "impl/array_list.hpp"
#include "impl/binary_tree_map.hpp"
#include "impl/reference_holder.hpp"
#include "impl/unique_holder.hpp"
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

TEST_CASE("`UniqueHolder` implementation", "[UniqueHolder]") {
  try {
    HolderTest::test_uint_holder<UniqueHolder<Uint>>();
  } catch (UnimplementedException<> p_exception) {
    throw std::runtime_error(p_exception.what());
  }
}

TEST_CASE("`ReferenceHolder` implementation", "[ReferenceHolder]") {
  try {
    HolderTest::test_uint_holder<ReferenceHolder<Uint>>();
  } catch (UnimplementedException<> p_exception) {
    throw std::runtime_error(p_exception.what());
  }
}