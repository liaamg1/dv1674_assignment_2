/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "analysis.hpp"
#include "dataset.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char const* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
                  << " [dataset] [outfile] [threads]\n";
        return 1;
    }

    const int thread_count = std::atoi(argv[3]);

    if (thread_count < 1) {
        std::cerr << "Thread count must be positive\n";
        return 1;
    }

    auto datasets = Dataset::read(argv[1]);
    auto corrs =
        Analysis::correlation_coefficients(datasets, thread_count);

    Dataset::write(corrs, argv[2]);
    return 0;
}
