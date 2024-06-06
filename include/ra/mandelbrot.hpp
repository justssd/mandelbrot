#ifndef _CEXPR_MANDELBROT_
#define _CEXPR_MANDELBROT_

#include <iostream>
#include <stdexcept>
#include "ra/cexpr_basic_string.hpp"

namespace ra::fractal {

using ra::cexpr::cexpr_string;
using ra::cexpr::to_string;

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

    constexpr cexpr_complex& operator*=(const cexpr_complex& other) {
        // To prevent self modification.
        double a = real;
        double b = imaginary;
        double c = other.real;
        double d = other.imaginary;
        real = a * c - b * d;
        imaginary = a * d + b * c;
        return *this;
    }

    constexpr cexpr_complex operator*(const cexpr_complex& other) const {
        return cexpr_complex(real * other.real - imaginary * other.imaginary,
                                real * other.imaginary + imaginary * other.real);
    }
    
    constexpr double get_magnitude_squared() const {
        return real * real + imaginary * imaginary;
    }
};

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

constexpr bool in_mandelbrot(const cexpr_complex& z) {
    unsigned short iteration_limit = 16;
    unsigned short magnitude_limit = 2;
    cexpr_complex curr(z.real, z.imaginary);
    for (unsigned short i = 0; i < iteration_limit; ++i) {
        if (curr.get_magnitude_squared() > (magnitude_limit * magnitude_limit)) {
            return false;
        }
        curr *= curr;
        curr += z;
    }
    return true;
}

constexpr cexpr_string<45> header(std::size_t W, std::size_t H)
{   
    cexpr_string<40> header;
    char dimension[20]{};
    header.append("P1 ");
    to_string(W, dimension, 20, nullptr);
    header.append(dimension);
    header.append(" ");
    to_string(H, dimension, 20, nullptr);
    header.append(dimension);
    header.append("\n");
    return header.begin();
}

template <std::size_t W, std::size_t H>
constexpr cexpr_string<(W + 1) * H + 45> populate()
{
    cexpr_string<(W + 1) * H + 45> s;
    s.append(header(W, H));

    for (std::size_t l = 0; l < H; ++l) {
        for (std::size_t k = 0; k < W; ++k) {
            cexpr_complex z = point_to_complex(k, l, W, H);
            s.push_back(in_mandelbrot(z) ? '1' : '0');
        }
        s.push_back('\n');
    }
    return s;
}

// A variable template for a string that represents an image depicting
// the Mandelbrot set. The image has width W and height H.
// This object must be of type cexpr_string<M> for some appropriate M.
// The string is a binary image encoded in the text-based bitmap PNM
// format.
// The values of W and H must be such that W >= 2 and H >= 2.

// can hold PNM-encoded character sequence for all std::size_t W and H.
template <std::size_t W, std::size_t H>
constexpr auto mandelbrot = cexpr_string<(W + 1) * H + 45>{populate<W, H>()};

} // namespace ra::fractal

#endif // _CEXPR_MANDELBROT_
