#include <iostream>
#include "ra/mandelbrot.hpp"

int main() {
// Force the image (in PNM format) to be computed at compile time.
    constexpr auto s = ra::fractal::mandelbrot<256, 256>;
    //constexpr ra::cexpr::cexpr_string<128> s("P1 8 4\n10000001\n01000010\n00100100\n00011000");

// Output the image (in PNM format).
    std::cout << s.begin() << '\n';
}

