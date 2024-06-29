#ifndef LIST_TEST_HPP
#define LIST_TEST_HPP

#include <catch2/catch_test_macros.hpp>

#include "list.hpp"

namespace Ragine::ListTest {
template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list() -> void {
  test_uint_list_count<ListType>();
  test_uint_list_get<ListType>();
  test_uint_list_iteration<ListType>();
  test_uint_list_compare<ListType>();
  test_uint_list_slice<ListType>();
  test_uint_list_clone<ListType>();
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_count() -> void {
  auto list = ListType();
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  REQUIRE(list.get_count() == 4);
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_push_front() -> void {
  auto list_a = ListType();
  list_a.push_back(1);
  list_a.push_back(2);
  list_a.push_back(3);
  list_a.push_back(4);

  auto list_b = ListType();
  list_b.push_front(4);
  list_b.push_front(3);
  list_b.push_front(2);
  list_b.push_front(1);

  REQUIRE(list_a == list_b);
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_pop_back() -> void {
  auto list = ListType();
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  REQUIRE(list.pop_back() == 4);
  REQUIRE(list.pop_back() == 3);
  REQUIRE(list.pop_back() == 2);
  REQUIRE(list.pop_back() == 1);
  REQUIRE_THROWS(list.pop_back());
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_pop_front() -> void {
  auto list = ListType();
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  REQUIRE(list.pop_front() == 1);
  REQUIRE(list.pop_front() == 2);
  REQUIRE(list.pop_front() == 3);
  REQUIRE(list.pop_front() == 4);
  REQUIRE_THROWS(list.pop_front());
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_insert() -> void {
  auto list = ListType();

  list.insert(0, 2);
  list.insert(0, 1);
  list.insert(2, 4);
  list.insert(2, 3);

  REQUIRE(list[0] == 1);
  REQUIRE(list[1] == 2);
  REQUIRE(list[2] == 3);
  REQUIRE(list[3] == 4);
  REQUIRE_THROWS(list.insert(6, 0)); // Insert out of bound.
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_remove() -> void {
  auto list = ListType();
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  auto popped = list.remove(2);

  REQUIRE(popped == 3);
  REQUIRE(list[0] == 1);
  REQUIRE(list[1] == 2);
  REQUIRE(list[2] == 4);
  REQUIRE_THROWS(list.remove(3)); // Remove out of bound.
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_get() -> void {
  auto list = ListType();
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  REQUIRE(list[0] == 1);
  REQUIRE(list[1] == 2);
  REQUIRE(list[2] == 3);
  REQUIRE(list[3] == 4);
  REQUIRE_THROWS(list[4]);
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_iteration() -> void {
  auto list = ListType();
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  auto index = 0;
  for (const auto element : list) {
    REQUIRE(list[index] == element);
    ++index;
  }
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_compare() -> void {
  auto list_a = ListType();
  list_a.push_back(1);
  list_a.push_back(2);
  list_a.push_back(3);
  list_a.push_back(4);

  auto list_b = ListType(); // Same
  list_b.push_back(1);
  list_b.push_back(2);
  list_b.push_back(3);
  list_b.push_back(4);

  auto list_c = ListType(); // Shorter length.
  list_c.push_back(1);
  list_c.push_back(2);
  list_c.push_back(3);

  auto list_d = ListType(); // Bigger element at the front.
  list_d.push_back(2);
  list_d.push_back(2);
  list_d.push_back(3);
  list_d.push_back(4);

  REQUIRE(list_a == list_b);
  REQUIRE(list_a > list_c);
  REQUIRE(list_a < list_d);
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_slice() -> void {
  auto list = ListType();
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  auto expected = ListType();
  expected.push_back(2);
  expected.push_back(3);

  auto result = list.slice(1, 3);

  REQUIRE(list == expected);
}

template <IsList ListType>
requires IsUnsignedInteger<typename ListType::ValueType>
auto test_uint_list_clone() -> void {
  auto list = ListType();
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  auto cloned = list.clone();

  cloned[0] = 5; // Cloned should be owned, thus writable.

  REQUIRE(cloned[0] == 5);
  REQUIRE(cloned[0] !=
          list[0]); // Cloned shouldn't have the same memory as list.
}

} // namespace Ragine::ListTest

#endif // LIST_TEST_HPP
