#include <catch2/catch_all.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "ra/cexpr_basic_string.hpp"

using ra::cexpr::cexpr_basic_string;
using ra::cexpr::cexpr_string;

TEMPLATE_TEST_CASE_SIG("default constructor", "",
        ((typename T, std::size_t M), T, M),
        (char, 3), (unsigned char, 0), (wchar_t, 9)) {

    constexpr cexpr_basic_string<T, M> s;
    STATIC_CHECK(s.capacity() == M);
    STATIC_CHECK(s.max_size() == M);
    STATIC_CHECK(s.size() == 0);
    STATIC_CHECK(s.begin() == s.end());
}

TEMPLATE_TEST_CASE_SIG("c-string constructor (empty c-string)", "",
        ((typename T, std::size_t M), T, M),
        (char, 0), (unsigned char, 1), (wchar_t, 0)) {

    constexpr T empty[] = {'\0'};
    constexpr cexpr_basic_string<T, M> es(empty);
    STATIC_CHECK(es.size() == 0);
    STATIC_CHECK(es[0] == '\0');
    STATIC_CHECK(es.begin() == es.end());
}

TEMPLATE_TEST_CASE_SIG("c-string constructor", "",
        ((typename T, std::size_t M), T, M),
        (char, 3), (unsigned char, 4), (wchar_t, 9)) {

    constexpr T temp[] = {'a', 'b', 'c', '\0'};
    constexpr cexpr_basic_string<T, M> s(temp);

    STATIC_CHECK(s.size() == 3);
    STATIC_CHECK(s[0] == 'a');
    STATIC_CHECK(s[1] == 'b');
    STATIC_CHECK(s[2] == 'c');
    CHECK(*(s.data() + s.size()) == '\0');
}

TEMPLATE_TEST_CASE_SIG("range constructor (empty range)", "",
        ((typename T, std::size_t M), T, M),
        (char, 4), (unsigned char, 0), (wchar_t, 0)) {

    constexpr T empty[] = {'\0'};
    constexpr cexpr_basic_string<T, M> es(empty, empty);

    constexpr T temp[] = {'1', '2', '3', '4', '\0'};
    constexpr cexpr_basic_string<T, M> s(temp + 3, temp + 3);
    STATIC_CHECK(es.size() == 0);
    STATIC_CHECK(s.size() == 0);
    STATIC_CHECK(s.max_size() == M && s.capacity() == M);
}

TEMPLATE_TEST_CASE_SIG("range constructor", "",
        ((typename T, std::size_t M), T, M),
        (char, 4), (unsigned char, 6), (wchar_t, 10)) {

    constexpr T temp[] = {'1', '2', '3', '4', '\0'};
    constexpr cexpr_basic_string<T, M> x(temp, temp + 4);
    constexpr cexpr_basic_string<T, M> y(temp + 1, temp + 3);

    STATIC_CHECK(x[0] == '1' && x[1] == '2' && x[2] == '3' && x[3] == '4');
    STATIC_CHECK(y[0] == '2' && y[1] == '3');
}

TEMPLATE_TEST_CASE_SIG("operator[]", "",
        ((typename T, std::size_t M), T, M),
        (char, 6), (unsigned char, 8), (wchar_t, 4)) {

    T temp[] = {'1', '2', '3', '4', '\0'};
    cexpr_basic_string<T, M> s(temp);
    CHECK(s[0] == '1');
    s[0] = '0';
    CHECK(s[0] == '0');
}

TEMPLATE_TEST_CASE_SIG("iterator", "",
        ((typename T, std::size_t M), T, M),
        (unsigned char, 6), (char, 4), (wchar_t, 5)) {

    T temp[] = {'1', '2', '3', '4', '\0'};
    cexpr_basic_string<T, M> s(temp);
    auto i = s.begin();
    CHECK(*i++ == '1');
    CHECK(*i++ == '2');
    CHECK(*i++ == '3');
    CHECK(*i++ == '4');
    CHECK(i == s.end());
}
// The below test case attempts to throws a runtime_error.
/*
TEMPLATE_TEST_CASE_SIG("constructor (insufficient capacity)", "[.]",
        ((typename T, std::size_t M), T, M),
        (char, 0), (unsigned char, 2), (wchar_t, 2)) {

    constexpr T temp[] = {'a', 'b', 'c', '\0'};
    constexpr cexpr_basic_string<T, M> x(temp);
    constexpr cexpr_basic_string<T, M> y(temp, temp + 3);
}
*/

// The operator[] when used to access out of bounds, fails the assertion.
/*
TEMPLATE_TEST_CASE_SIG("operator[] (out of bounds access)", "[.]",
        ((typename T, std::size_t M), T, M),
        (char, 3), (unsigned char, 8), (wchar_t, 4)) {

    constexpr T temp[] = {'a', 'b', 'c', '\0'};
    constexpr cexpr_basic_string<T, M> x(temp);
    // OK
    STATIC_CHECK(x[3] == '\0');
    // assert(i >= 0 && i <= m_size_)
    STATIC_CHECK(x[4]);
}
*/
