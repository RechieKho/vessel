#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_translate_exception.hpp>

#include "impl/binary_tree_map.hpp"
#include "map.hpp"

using namespace Vessel;

CATCH_TRANSLATE_EXCEPTION(const Exception<> &p_exception) {
  return p_exception.what();
}

TEMPLATE_PRODUCT_TEST_CASE("Map types test cases.", "[map]", (BinaryTreeMap),
                           ((Uint, Uint))) {
  static_assert(IsMap<TestType>);

  SECTION("Test count.") {
    auto map = TestType();
    map.insert(0, 0);
    map.insert(1, 1);
    map.insert(5, 5);
    map.insert(10, 10);

    REQUIRE(map.get_count() == 4);
  }

  SECTION("Test `insert`.") {
    auto map = TestType();
    map.insert(0, 0);
    map.insert(1, 1);
    map.insert(5, 5);
    map.insert(10, 10);

    REQUIRE(map[0] == 0);
    REQUIRE(map[1] == 1);
    REQUIRE(map[5] == 5);
    REQUIRE(map[10] == 10);
  }

  SECTION("Test `remove`.") {
    auto map = TestType();
    map.insert(0, 0);
    map.insert(1, 1);
    map.insert(5, 5);
    map.insert(10, 10);

    auto popped = map.remove(0);

    REQUIRE(popped == 0);
    REQUIRE(map[1] == 1);
    REQUIRE(map[5] == 5);
    REQUIRE(map[10] == 10);
    REQUIRE_THROWS(map.remove(0)); // Remove non-existing item.
  }

  SECTION("Test indexing.") {
    auto map = TestType();
    map.insert(0, 0);
    map.insert(1, 1);
    map.insert(5, 5);
    map.insert(10, 10);

    REQUIRE_NOTHROW(map[0] = 2);

    REQUIRE(map[0] == 2);
    REQUIRE(map[1] == 1);
    REQUIRE(map[5] == 5);
    REQUIRE(map[10] == 10);
    REQUIRE_THROWS(map[11]);
  }

  SECTION("Test iteration.") {
    auto map = TestType();
    map.insert(0, 0);
    map.insert(1, 1);
    map.insert(5, 5);
    map.insert(10, 10);

    for (const auto [key, value] : map)
      REQUIRE(key == value);
  }

  SECTION("Test equality.") {
    auto map_a = TestType();
    map_a.insert(0, 0);
    map_a.insert(1, 1);
    map_a.insert(5, 5);
    map_a.insert(10, 10);

    auto map_b = TestType(); // Same.
    map_b.insert(0, 0);
    map_b.insert(1, 1);
    map_b.insert(5, 5);
    map_b.insert(10, 10);

    auto map_c = TestType(); // Not the same.
    map_c.insert(0, 0);
    map_c.insert(1, 1);
    map_c.insert(5, 5);

    REQUIRE(map_a == map_b);
    REQUIRE(map_a != map_c);
  }

  SECTION("Test copying.") {
    auto map = TestType();
    map.insert(0, 0);
    map.insert(1, 1);
    map.insert(5, 5);
    map.insert(10, 10);

    auto copied = TestType(map);
    REQUIRE(copied == map);

    copied[0] = 2;

    REQUIRE(copied[0] == 2);
    REQUIRE(copied[0] != map[0]);
  }

  SECTION("Test moving.") {
    auto map = TestType();
    map.insert(0, 0);
    map.insert(1, 1);
    map.insert(5, 5);
    map.insert(10, 10);

    auto moved = move(TestType(map));

    REQUIRE(map == TestType());
    REQUIRE(map[0] == 2);
    REQUIRE(map[1] == 1);
    REQUIRE(map[5] == 5);
    REQUIRE(map[10] == 10);
    REQUIRE_THROWS(map[11]);
  }

  SECTION("Test `contain`.") {
    auto map = TestType();
    map.insert(1, 0);
    map.insert(2, 1);
    map.insert(6, 5);
    map.insert(11, 10);

    REQUIRE(map.contain(0));
    REQUIRE(map.contain(1));
    REQUIRE(map.contain(5));
    REQUIRE(map.contain(10));
    REQUIRE_FALSE(map.contain(11));
  }

  SECTION("Test `contain_key`.") {
    auto map = TestType();
    map.insert(0, 1);
    map.insert(1, 2);
    map.insert(5, 6);
    map.insert(10, 11);

    REQUIRE(map.contain_key(0));
    REQUIRE(map.contain_key(1));
    REQUIRE(map.contain_key(5));
    REQUIRE(map.contain_key(10));
    REQUIRE_FALSE(map.contain_key(11));
  }

  SECTION("Test `compute_keys`.") {

    auto map = TestType();
    map.insert(0, 1);
    map.insert(1, 2);
    map.insert(5, 6);
    map.insert(10, 11);

    auto keys = map.compute_keys();

    REQUIRE(map.get_count() == keys.get_count());
    REQUIRE(keys.contain(0));
    REQUIRE(keys.contain(1));
    REQUIRE(keys.contain(5));
    REQUIRE(keys.contain(10));
    REQUIRE_FALSE(keys.contain(11));
  }

  SECTION("Test `compute_values`.") {
    auto map = TestType();
    map.insert(0, 1);
    map.insert(1, 2);
    map.insert(5, 6);
    map.insert(10, 11);

    auto values = map.compute_values();

    REQUIRE(map.get_count() == values.get_count());
    REQUIRE(values.contain(1));
    REQUIRE(values.contain(2));
    REQUIRE(values.contain(6));
    REQUIRE(values.contain(11));
    REQUIRE_FALSE(values.contain(12));
  }
}