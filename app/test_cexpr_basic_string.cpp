#include <catch2/catch_all.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "ra/cexpr_basic_string.hpp"

#define ASSERT_THROW(X, Y) if (!X) throw std::logic_error(Y)

using ra::cexpr::cexpr_basic_string;
using ra::cexpr::cexpr_string;
using ra::cexpr::to_string;

TEMPLATE_TEST_CASE_SIG("default constructor", "", ((typename T, std::size_t M), T, M),
        (char, 3), (unsigned char, 0), (wchar_t, 9)) {

    constexpr cexpr_basic_string<T, M> s;

    STATIC_CHECK(s.capacity() == M);
    STATIC_CHECK(s.max_size() == M);
    STATIC_CHECK(s.size() == 0);
    STATIC_CHECK(s.begin() == s.end());
}

TEMPLATE_TEST_CASE_SIG("c-string constructor (empty c-string)", "", ((typename T, std::size_t M), T, M),
        (char, 0), (unsigned char, 1), (wchar_t, 0)) {

    constexpr T empty[] = {'\0'};

    constexpr cexpr_basic_string<T, M> es(empty);

    STATIC_CHECK(es.size() == 0);
    STATIC_CHECK(es[0] == '\0');
    STATIC_CHECK(es.begin() == es.end());
}

TEMPLATE_TEST_CASE_SIG("c-string constructor", "", ((typename T, std::size_t M), T, M),
        (char, 3), (unsigned char, 4), (wchar_t, 9)) {

    constexpr T temp[] = {'a', 'b', 'c', '\0'};

    constexpr cexpr_basic_string<T, M> s(temp);

    STATIC_CHECK(s.size() == 3);
    STATIC_CHECK(s[0] == 'a');
    STATIC_CHECK(s[1] == 'b');
    STATIC_CHECK(s[2] == 'c');
    CHECK(*(s.data() + s.size()) == '\0');
}

TEMPLATE_TEST_CASE_SIG("range constructor (empty range)", "", ((typename T, std::size_t M), T, M),
        (char, 4), (unsigned char, 0), (wchar_t, 0)) {

    constexpr T empty[] = {'\0'};
    constexpr T temp[] = {'1', '2', '3', '4', '\0'};
    
    constexpr cexpr_basic_string<T, M> es(empty, empty);
    constexpr cexpr_basic_string<T, M> s(temp + 3, temp + 3);

    STATIC_CHECK(es.size() == 0);
    STATIC_CHECK(s.size() == 0);
    STATIC_CHECK(s.max_size() == M && s.capacity() == M);
}

TEMPLATE_TEST_CASE_SIG("range constructor", "", ((typename T, std::size_t M), T, M),
        (char, 4), (unsigned char, 6), (wchar_t, 10)) {

    constexpr T temp[] = {'1', '2', '3', '4', '\0'};

    constexpr cexpr_basic_string<T, M> x(temp, temp + 4);
    constexpr cexpr_basic_string<T, M> y(temp + 1, temp + 3);

    STATIC_CHECK(x[0] == '1' && x[1] == '2' && x[2] == '3' && x[3] == '4');
    STATIC_CHECK(y[0] == '2' && y[1] == '3');
}

TEMPLATE_TEST_CASE_SIG("operator[]", "", ((typename T, std::size_t M), T, M),
        (char, 6), (unsigned char, 8), (wchar_t, 4)) {

    constexpr T temp[] = {'1', '2', '3', '4', '\0'};

    constexpr cexpr_basic_string<T, M> x(temp);
    cexpr_basic_string<T, M> y(temp);

    STATIC_CHECK(x[0] == '1');
    CHECK(y[0] == '1');
    y[0] = '0';
    CHECK(y[0] == '0');
}

template <typename T, std::size_t M>
constexpr void test_iterator() {
    
    T temp[] = {'1', '2', '3', '4', '\0'};

    cexpr_basic_string<T, M> s(temp);
    const T* i = s.begin();
    ASSERT_THROW((*i == '1'), "iterator");
    ASSERT_THROW((i + 4 == s.end()), "iterator");
}

TEMPLATE_TEST_CASE_SIG("iterator", "", ((typename T, std::size_t M), T, M),
        (unsigned char, 6), (char, 4), (wchar_t, 5)) {

    static_assert((test_iterator<T, M>(), true));
}

TEMPLATE_TEST_CASE_SIG("push_back, pop_back", "", ((typename T, std::size_t M), T, M),
        (unsigned char, 7), (char, 6), (wchar_t, 8)) {

    constexpr T temp[] = {'1', '2', '3', '4', '\0'};

    cexpr_basic_string<T, M> s(temp);

    // Will test at compile time later, if time permits.
    s.push_back(T('5'));
    CHECK(s[4] == '5');
    CHECK(s.size() == 5);
    CHECK(s[5] =='\0');
    s.pop_back();
    CHECK(s.size() == 4);
    CHECK(s[4] == '\0');
    CHECK(s[3] == '4');
}

template <typename T, std::size_t M>
constexpr void test_append() {
    constexpr T temp[] = {'1', '2', '3', '4', '\0'};
    constexpr T append[] = {'5', '6', '7', '8', '\0'};

    cexpr_basic_string<T, M> s(temp);
    s.append(append);
    ASSERT_THROW((s.size() == 8), "append");
    ASSERT_THROW((s[7] == '8' && s[8] == '\0'), "BRUH");
    s.append(s);
    ASSERT_THROW((s.size() == 16), "append");
    ASSERT_THROW((s[0] == '1' && s[15] == '8' && s[16] == '\0'), "Self Modification?");
    s.pop_back();
    ASSERT_THROW((s[15] == '\0'), "pop null terminator");
    s.clear();
    ASSERT_THROW((s[0] == '\0'), "clear");
}

TEMPLATE_TEST_CASE_SIG("append", "", ((typename T, std::size_t M), T, M),
        (unsigned char, 30), (char, 30), (wchar_t, 16)) {

    static_assert((test_append<T, M>(), true));
}

void test_to_string() {
    char temp[7]{};
    char* end = nullptr;
    to_string(1234, temp, 7, &end);
    assert(end == temp + 4);
    assert(!std::strcmp(temp, "1234"));
    to_string(0, temp, 2, nullptr);
    assert(!std::strcmp(temp, "0"));
    to_string(30, temp, 3, &end);
    assert(!std::strcmp(temp, "30"));
}

TEST_CASE("to_string") {
    test_to_string();
}

// The below test case attempts to throws a runtime_error.
/*
TEMPLATE_TEST_CASE_SIG("constructor (insufficient capacity)", "[.]", ((typename T, std::size_t M), T, M),
        (char, 0), (unsigned char, 2), (wchar_t, 2)) {

    constexpr T temp[] = {'a', 'b', 'c', '\0'};

    constexpr cexpr_basic_string<T, M> x(temp);
    constexpr cexpr_basic_string<T, M> y(temp, temp + 3);
}
*/

// The operator[] when used to access out of bounds, fails the assertion.
/*
TEMPLATE_TEST_CASE_SIG("operator[] (out of bounds access)", "[.]", ((typename T, std::size_t M), T, M),
        (char, 3), (unsigned char, 8), (wchar_t, 4)) {

    constexpr T temp[] = {'a', 'b', 'c', '\0'};

    constexpr cexpr_basic_string<T, M> x(temp);

    // OK
    STATIC_CHECK(x[3] == '\0');
    // assert(i >= 0 && i <= m_size_)
    STATIC_CHECK(x[4]);
}
*/
