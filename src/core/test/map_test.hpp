#ifndef MAP_TEST_HPP
#define MAP_TEST_HPP

#include <catch2/catch_test_macros.hpp>

#include "map.hpp"

namespace Ragine::MapTest {
template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_count() -> void {
  auto map = MapType();
  map.insert(0, 0);
  map.insert(1, 1);
  map.insert(5, 5);
  map.insert(10, 10);

  REQUIRE(map.get_count() == 4);
}

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_insert() -> void {
  auto map = MapType();
  map.insert(0, 0);
  map.insert(1, 1);
  map.insert(5, 5);
  map.insert(10, 10);

  REQUIRE(map[0] == 0);
  REQUIRE(map[1] == 1);
  REQUIRE(map[5] == 5);
  REQUIRE(map[10] == 10);
}

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_remove() -> void {
  auto map = MapType();
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

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_index() -> void {
  auto map = MapType();
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

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_iteration() -> void {
  auto map = MapType();
  map.insert(0, 0);
  map.insert(1, 1);
  map.insert(5, 5);
  map.insert(10, 10);

  for (const auto [key, value] : map)
    REQUIRE(key == value);
}

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_equality() -> void {
  auto map_a = MapType();
  map_a.insert(0, 0);
  map_a.insert(1, 1);
  map_a.insert(5, 5);
  map_a.insert(10, 10);

  auto map_b = MapType(); // Same.
  map_b.insert(0, 0);
  map_b.insert(1, 1);
  map_b.insert(5, 5);
  map_b.insert(10, 10);

  auto map_c = MapType(); // Not the same.
  map_c.insert(0, 0);
  map_c.insert(1, 1);
  map_c.insert(5, 5);

  REQUIRE(map_a == map_b);
  REQUIRE(map_a != map_c);
}

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_clone() -> void {
  auto map = MapType();
  map.insert(0, 0);
  map.insert(1, 1);
  map.insert(5, 5);
  map.insert(10, 10);

  auto cloned = map.clone();

  cloned[0] = 2;

  REQUIRE(cloned[0] == 2);
  REQUIRE(cloned[0] != map[0]);
}

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_contain() -> void {
  auto map = MapType();
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

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_contain_key() -> void {
  auto map = MapType();
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

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_compute_keys() -> void {
  auto map = MapType();
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

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map_compute_values() -> void {
  auto map = MapType();
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

template <IsMap MapType>
requires IsUnsignedInteger<typename MapType::KeyType> &&
    IsUnsignedInteger<typename MapType::ValueType>
auto test_uint_to_uint_map() -> void {
  test_uint_to_uint_map_count<MapType>();
  test_uint_to_uint_map_insert<MapType>();
  test_uint_to_uint_map_remove<MapType>();
  test_uint_to_uint_map_index<MapType>();
  test_uint_to_uint_map_iteration<MapType>();
  test_uint_to_uint_map_equality<MapType>();
  test_uint_to_uint_map_clone<MapType>();
  test_uint_to_uint_map_contain<MapType>();
  test_uint_to_uint_map_contain_key<MapType>();
  test_uint_to_uint_map_compute_keys<MapType>();
  test_uint_to_uint_map_compute_values<MapType>();
}

} // namespace Ragine::MapTest

#endif // MAP_TEST_HPP