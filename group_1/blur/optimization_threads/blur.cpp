/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "../optimization_2/matrix.hpp"
#include "../optimization_2/ppm.hpp"
#include "filters.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char const* argv[])
{
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " [radius] [infile] [outfile] [num_threads]" << std::endl;
        std::exit(1);
    }

     auto num_threads { static_cast<int>(std::stoul(argv[4])) };

    if (num_threads < 1 || num_threads > 32)
        throw std::invalid_argument("Thread count must be between 1 and 32");

    PPM::Reader reader {};
    PPM::Writer writer {};

    auto m { reader(argv[2]) };
    auto radius { static_cast<unsigned>(std::stoul(argv[1])) };
   

    auto blurred { Filter::blur(m, radius, num_threads) };
    writer(blurred, argv[3]);

    return 0;
}
