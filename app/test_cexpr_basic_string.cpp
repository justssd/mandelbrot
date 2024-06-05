#include <catch2/catch_all.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "ra/cexpr_basic_string.hpp"

using ra::cexpr::cexpr_basic_string;
using ra::cexpr::cexpr_string;

TEMPLATE_TEST_CASE_SIG("default constructor", "",
        ((typename T, std::size_t M), T, M),
        (char, 3), (unsigned char, 0), (wchar_t, 9)) {

    constexpr cexpr_basic_string<T, M> s;
}

TEMPLATE_TEST_CASE_SIG("c-string constructor (empty c-string)", "",
        ((typename T, std::size_t M), T, M),
        (char, 0), (unsigned char, 1), (wchar_t, 0)) {

    constexpr T empty[] = {'\0'};
    constexpr cexpr_basic_string<T, M> es(empty);
}

TEMPLATE_TEST_CASE_SIG("c-string constructor", "",
        ((typename T, std::size_t M), T, M),
        (char, 3), (unsigned char, 4), (wchar_t, 9)) {

    constexpr T temp[] = {'a', 'b', 'c', '\0'};
    constexpr cexpr_basic_string<T, M> s(temp);
}

TEMPLATE_TEST_CASE_SIG("range constructor (empty range)", "",
        ((typename T, std::size_t M), T, M),
        (char, 4), (unsigned char, 0), (wchar_t, 0)) {

    constexpr T empty[] = {'\0'};
    constexpr cexpr_basic_string<T, M> es(empty, empty);

    constexpr T temp[] = {'1', '2', '3', '4', '\0'};
    constexpr cexpr_basic_string<T, M> ts(temp + 3, temp + 3);
}

TEMPLATE_TEST_CASE_SIG("range constructor", "",
        ((typename T, std::size_t M), T, M),
        (char, 4), (unsigned char, 6), (wchar_t, 10)) {

    constexpr T temp[] = {'1', '2', '3', '4', '\0'};
    constexpr cexpr_basic_string<T, M> es(temp, temp + 4);
    constexpr cexpr_basic_string<T, M> s(temp + 1, temp + 3);
}

// The below test case attempts to throws a runtime_error.
// But constexpr functions can't throw exceptions. Hence compile error.
/*
TEMPLATE_TEST_CASE_SIG("c-string constructor (insufficient capacity)", "",
        ((typename T, std::size_t M), T, M),
        (char, 0), (unsigned char, 2), (wchar_t, 2)) {

    constexpr T temp[] = {'a', 'b', 'c', '\0'};
    constexpr cexpr_basic_string<T, M> css(temp);
    constexpr cexpr_basic_string<T, M> rs(temp, temp + 3);
}
*/
