#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_translate_exception.hpp>

#include "impl/array_list.hpp"
#include "list.hpp"

using namespace Vessel;

CATCH_TRANSLATE_EXCEPTION(const Exception<> &p_exception) {
  return p_exception.what();
}

TEMPLATE_PRODUCT_TEST_CASE("List types test cases.", "[list]", (ArrayList),
                           (Uint)) {
  static_assert(IsList<TestType>);

  SECTION("Test count.") {
    auto list = TestType();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    REQUIRE(list.get_count() == 4);
  }

  SECTION("Test `push_front`.") {
    auto list = TestType();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    auto list_b = TestType();
    list_b.push_front(4);
    list_b.push_front(3);
    list_b.push_front(2);
    list_b.push_front(1);

    REQUIRE(list == list_b);
  }

  SECTION("Test `pop_back`.") {
    auto list = TestType();
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

  SECTION("Test `pop_front`.") {
    auto list = TestType();
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

  SECTION("Test `insert`.") {
    auto list = TestType();

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

  SECTION("Test `remove`.") {
    auto list = TestType();
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

  SECTION("Test indexing.") {
    auto list = TestType();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    REQUIRE_NOTHROW(list[0] = 5);

    REQUIRE(list[0] == 5);
    REQUIRE(list[1] == 2);
    REQUIRE(list[2] == 3);
    REQUIRE(list[3] == 4);
    REQUIRE_THROWS(list[4]);
  }

  SECTION("Test iteration.") {
    auto list = TestType();
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

  SECTION("Test comparison.") {
    auto list_a = TestType();
    list_a.push_back(1);
    list_a.push_back(2);
    list_a.push_back(3);
    list_a.push_back(4);

    auto list_b = TestType(); // Same
    list_b.push_back(1);
    list_b.push_back(2);
    list_b.push_back(3);
    list_b.push_back(4);

    auto list_c = TestType(); // Shorter length.
    list_c.push_back(1);
    list_c.push_back(2);
    list_c.push_back(3);

    auto list_d = TestType(); // Bigger element at the front.
    list_d.push_back(2);
    list_d.push_back(2);
    list_d.push_back(3);
    list_d.push_back(4);

    REQUIRE(list_a == list_b);
    REQUIRE(list_c < list_a);
    REQUIRE(list_a < list_d);
  }

  SECTION("Test slicing.") {
    auto list = TestType();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    auto expected = TestType();
    expected.push_back(2);
    expected.push_back(3);

    auto result = list.slice(1, 3);

    REQUIRE(result == expected);
  }

  SECTION("Test copying.") {
    auto list = TestType();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    auto copied = list;
    REQUIRE(copied.get_count() == list.get_count());
    REQUIRE(copied == list); // Copied should be the same as the original.

    copied[0] = 5; // Copied should be owned, thus writable.

    REQUIRE(copied[0] == 5);
    REQUIRE(copied[0] !=
            list[0]); // Copied shouldn't have the same memory as list.
  }

  SECTION("Test moving.") {
    auto list = TestType();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    auto moved = move(list);

    moved[0] = 5; // Moved should be owned, thus writable.

    REQUIRE(list == TestType()); // Original should be empty.
    REQUIRE(moved[0] == 5);
    REQUIRE(moved[1] == 2);
    REQUIRE(moved[2] == 3);
    REQUIRE(moved[3] == 4);
    REQUIRE_THROWS(moved[4]);
  }

  SECTION("Test `contain`.") {
    auto list = TestType();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    REQUIRE(list.contain(1));
    REQUIRE(list.contain(2));
    REQUIRE(list.contain(3));
    REQUIRE(list.contain(4));
    REQUIRE_FALSE(list.contain(5));
  }
}
