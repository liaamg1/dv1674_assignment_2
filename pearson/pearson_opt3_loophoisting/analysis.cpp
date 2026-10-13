/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "analysis.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>

namespace Analysis {

std::vector<double> correlation_coefficients(const std::vector<Vector>& datasets)
{
    std::vector<double> result {};

    for (auto sample1 { 0 }; sample1 < datasets.size() - 1; sample1++) {
        auto x_normalized{normalize(datasets[sample1])};
        for (auto sample2 { sample1 + 1 }; sample2 < datasets.size(); sample2++) {
            auto corr { pearson(x_normalized, datasets[sample2]) };
            result.push_back(corr);
        }
    }

    return result;
}

double pearson(const Vector& vec1,  const Vector& vec2)
{
    auto y_mean { vec2.mean() };

    auto y_mm { vec2 - y_mean };

    auto y_mag { y_mm.magnitude() };

    auto y_mm_over_y_mag { y_mm / y_mag };

    auto r { vec1.dot(y_mm_over_y_mag) };

    return std::max(std::min(r, 1.0), -1.0);
}
Vector normalize(const Vector& vec)
{
    auto mean{vec.mean()};
    auto mm{vec - mean};
    auto mag{mm.magnitude()};
    return mm / mag;
}
};
