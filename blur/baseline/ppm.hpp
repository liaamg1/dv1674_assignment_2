/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "matrix.hpp"
#include <exception>
#include <iostream>
#include <sstream>

#if !defined(PPM_READER_HPP)
#define PPM_READER_HPP

namespace PPM {

void error(std::string op, std::string what);

/*
    max_dimension is the maximum width or height of an image
    max_pixels is the maximum number of pixels in an image
    magic_number "P6" means the image is stored in a raw binary format for full-color RGB graphics
*/
constexpr unsigned max_dimension { 3000 };
constexpr unsigned max_pixels { max_dimension * max_dimension };
constexpr char const* magic_number { "P6" };

class Reader {
private:
    std::stringstream stream;
    /*
        @return: the magic number of the PPM file (should always be "P6")
    */
    std::string get_magic_number();
    /*
        skips all the lines that start with a '#' character and reads the next line to get the dimensions of the image
        @return: a pair of unsigned integers representing the width and height of the image ex: 1980 x 1080

    */
    std::pair<unsigned, unsigned> get_dimensions();

    /* 
        @param x_size: the width of the image
        @param y_size: the height of the image
        @return: a tuple of three pointers to unsigned char arrays representing the R, G, and B channels of the image
    */
    std::tuple<unsigned char*, unsigned char*, unsigned char*> get_data(unsigned x_size, unsigned y_size);
    /*
        @return: the maximum color value of the image (should always be 255)
    */
    unsigned get_color_max();

    /*
        @param filename: the name of the file to read
        @if the file cannot be opened, the stream will be set the flag to failbit
        @return: void. Writes the contents of the file to the stream member variable (stringstream)
    */
    void fill(std::string filename);

public:
    Matrix operator()(std::string filename);
};

class Writer {
public:
    void operator()(Matrix m, std::string filename);
};

}

#endif
