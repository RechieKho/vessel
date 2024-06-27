#ifndef SPAN_TEST_HPP
#define SPAN_TEST_HPP

#include <catch2/catch_test_macros.hpp>

#include "span.hpp"

namespace Ragine::SpanTest
{
    template <IsSpan SpanType>
        requires IsUnsignedInteger<typename SpanType::ValueType>
    auto test_uint_span() -> void
    {
        test_uint_span_count<SpanType>();
        test_uint_span_get<SpanType>();
        test_uint_span_iteration<SpanType>();
        test_uint_span_compare<SpanType>();
        test_uint_span_slice<SpanType>();
        test_uint_span_clone<SpanType>();
    }

    template <IsSpan SpanType>
        requires IsUnsignedInteger<typename SpanType::ValueType>
    auto test_uint_span_count() -> void
    {
        const Uint data[] = {1, 2, 3, 4, 5};
        const auto count = sizeof(data) / sizeof(data[0]);

        SpanType span(data, count);

        REQUIRE(span.get_count() == count);
    }

    template <IsSpan SpanType>
        requires IsUnsignedInteger<typename SpanType::ValueType>
    auto test_uint_span_get() -> void
    {
        const Uint data[] = {1, 2, 3, 4, 5};
        const auto count = sizeof(data) / sizeof(data[0]);

        SpanType span(data, count);

        REQUIRE(span[0] == 1);
        REQUIRE(span[1] == 2);
        REQUIRE(span[2] == 3);
        REQUIRE(span[3] == 4);
        REQUIRE(span[4] == 5);
        REQUIRE_THROWS(span[5]);
    }

    template <IsSpan SpanType>
        requires IsUnsignedInteger<typename SpanType::ValueType>
    auto test_uint_span_iteration() -> void
    {
        const Uint data[] = {1, 2, 3, 4, 5};
        const auto count = sizeof(data) / sizeof(data[0]);

        SpanType span(data, count);

        auto index = 0;
        for (const auto element : span)
        {
            REQUIRE(span[index] == element);
            ++index;
        }
    }

    template <IsSpan SpanType>
        requires IsUnsignedInteger<typename SpanType::ValueType>
    auto test_uint_span_compare() -> void
    {
        const Uint data_a[] = {1, 2, 3, 4, 5};
        const auto count_a = sizeof(data_a) / sizeof(data_a[0]);
        SpanType span_a(data_a, count_a);

        const Uint data_b[] = {1, 2, 3, 4, 5}; // Same.
        const auto count_b = sizeof(data_b) / sizeof(data_b[0]);
        SpanType span_b(data_b, count_b);

        const Uint data_c[] = {1, 2, 3, 4}; // Different count.
        const auto count_c = sizeof(data_c) / sizeof(data_c[0]);
        SpanType span_c(data_c, count_c);

        const Uint data_d[] = {2, 2, 3, 4, 5}; // Same count but bigger element at the front of span.
        const auto count_d = sizeof(data_d) / sizeof(data_d[0]);
        SpanType span_d(data_d, count_d);

        REQUIRE(span_a == span_b);
        REQUIRE(span_c < span_a);
        REQUIRE(span_a < span_d);
    }

    template <IsSpan SpanType>
        requires IsUnsignedInteger<typename SpanType::ValueType>
    auto test_uint_span_slice() -> void
    {
        const Uint data[] = {1, 2, 3, 4, 5};
        const auto count = sizeof(data) / sizeof(data[0]);
        SpanType span(data, count);

        const Uint expected_data[] = {2, 3, 4};
        const auto expected_count = sizeof(expected_data) / sizeof(expected_data[0]);
        SpanType expected_span(expected_data, expected_count);

        SpanType result = span.slice(1, 4);

        REQUIRE(result == expected_span);
    }

    template <IsSpan SpanType>
        requires IsUnsignedInteger<typename SpanType::ValueType>
    auto test_uint_span_clone() -> void
    {
        const Uint data[] = {1, 2, 3, 4, 5};
        const auto count = sizeof(data) / sizeof(data[0]);
        SpanType span(data, count);

        typename SpanType::CloneType cloned = span.clone();

        cloned[0] = 5; // Cloned should be writable.

        REQUIRE(cloned[0] == 5);
        REQUIRE(cloned[0] != span[0]); // Cloned shouldn't be the same memory as span.
    }

    template <IsSpan SpanType>
        requires IsUnsignedInteger<typename SpanType::ValueType>
    auto test_uint_span_clone() -> void
    {
        const Uint data[] = {1, 2, 3, 4, 5};
        const auto count = sizeof(data) / sizeof(data[0]);
        SpanType span(data, count);

        typename SpanType::CloneType cloned = span.clone();

        cloned[0] = 5; // Cloned should be writable.

        REQUIRE(cloned[0] == 5);
        REQUIRE(cloned[0] != span[0]); // Cloned shouldn't be the same memory as span.
    }

} // namespace Ragine::SpanTest

#endif // SPAN_TEST_HPP