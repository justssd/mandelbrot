#include <iostream>
#include <cassert>
#include "ra/mandelbrot.hpp"

constexpr void test_point_to_complex() {
    // auto invalid_WH_z = ra::fractal::point_to_complex(0, 0, 1, 1);
    // auto point_outside_domain_z = ra::fractal::point_to_complex(3, 4, 4, 4);
    auto z = ra::fractal::point_to_complex(10, 14, 15, 15);
    assert(std::abs(z.real - (-0.0285711428)) < 1e-6);
    assert(std::abs(z.imaginary - (-1.1)) < 1e-6);
}

int main() {
    static_assert((test_point_to_complex(), true));
// Force the image (in PNM format) to be computed at compile time.
    constexpr auto s = ra::fractal::mandelbrot<256, 256>;
    //constexpr ra::cexpr::cexpr_string<128> s("P1 8 4\n10000001\n01000010\n00100100\n00011000");

// Output the image (in PNM format).
    std::cout << s.begin() << '\n';
}

