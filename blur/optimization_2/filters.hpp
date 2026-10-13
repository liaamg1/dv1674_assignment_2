/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "matrix.hpp"

#if !defined(FILTERS_HPP)
#define FILTERS_HPP

namespace Filter
{

    namespace Gauss
    {
        // We can only set radius to 1000 
        constexpr unsigned max_radius{1000};
        // 
        constexpr float max_x{1.33};
        constexpr float pi{3.14159};

        /*
        
        */
        void get_weights(int n, double *weights_out);
    }

    Matrix blur(const Matrix & m, const int radius);

}

#endif