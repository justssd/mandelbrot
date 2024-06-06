#ifndef _CEXPR_MANDELBROT_
#define _CEXPR_MANDELBROT_

#include <stdexcept>
#include "ra/cexpr_basic_string.hpp"

namespace ra::fractal {

class cexpr_complex {
public:
    double real;
    double imaginary;

    constexpr cexpr_complex() : real(0.0), imaginary(0.0) {}
    constexpr cexpr_complex(double a, double b) : real(a), imaginary(b) {}

    constexpr cexpr_complex& operator+=(const cexpr_complex& other) {
        real += other.real;
        imaginary += other.imaginary;
        return *this;
    }

    constexpr cexpr_complex operator*(const cexpr_complex& other) {
        return cexpr_complex(real * other.real - imaginary * other.imaginary,
                                real * other.imaginary + imaginary * other.real);
    }
};

// A variable template for a string that represents an image depicting
// the Mandelbrot set. The image has width W and height H.
// This object must be of type cexpr_string<M> for some appropriate M.
// The string is a binary image encoded in the text-based bitmap PNM
// format.
// The values of W and H must be such that W >= 2 and H >= 2.

// can hold PNM-encoded character sequence for all std::size_t W and H.
template <std::size_t W, std::size_t H>
constexpr ra::cexpr::cexpr_string<(W + 1) * H + 45>  mandelbrot;

constexpr cexpr_complex point_to_complex(std::size_t k, std::size_t l, std::size_t W, std::size_t H) {
    assert(W > 1 && H > 1 && "W and H cannot be < 2");
    assert(k < W && l < H && "point outside domain");

    constexpr double a_0 =  -1.6;
    constexpr double a_1 =  -1.1;
    constexpr double b_0 =  0.6;
    constexpr double b_1 =  1.1;

    double real = a_0 + k * (b_0 - a_0) / (W - 1);
    double imaginary = a_1 + (H - 1 - l) * (b_1 - a_1) / (H - 1);
    return cexpr_complex(real, imaginary);
}

}

#endif // _CEXPR_MANDELBROT_
