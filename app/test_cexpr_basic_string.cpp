#include <catch2/catch_all.hpp>
#include "ra/cexpr_basic_string.hpp"

using ra::cexpr::cexpr_basic_string;
using ra::cexpr::cexpr_string;

TEST_CASE("default constructor", "[cexpr_basic_string][constructor]") {
    constexpr cexpr_string<10> s;
    constexpr cexpr_basic_string<unsigned char, 0> ucs;
    constexpr cexpr_basic_string<wchar_t, 100> wcs;
}

TEST_CASE("constructor with null-terminated character array", "[cexpr_basic_string][constructor]") {
    constexpr cexpr_string<8> s("12345678");
    constexpr unsigned char temp[] = "123456";
    // throws std::runtime_error
    // constexpr cexpr_basic_string<unsigned char, 5> ucs(temp);
    constexpr cexpr_basic_string<wchar_t, 0> wcs(L"");
}

TEST_CASE("constructor with iterator range [first, last)", "[cexpr_basic_string][constructor]") {
    constexpr char c[] = "123456789"; 
    constexpr unsigned char uc[] = "";
    constexpr wchar_t wc[] = L"123";
    
    constexpr cexpr_string<0> cs1(c, c);
    // throws std::runtime_error
    // constexpr cexpr_string<0> cs2(c, c + 1);
    
    constexpr cexpr_basic_string<unsigned char, 0> ucs(uc, uc);

    constexpr cexpr_basic_string<wchar_t, 3> wcs1(wc + 1, wc + 2);
    constexpr cexpr_basic_string<wchar_t, 3> wcs2(wc, wc + 3);
}
