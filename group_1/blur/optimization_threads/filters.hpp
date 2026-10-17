/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "../optimization_2/matrix.hpp"

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


/*
    Executes a horizontal or vertical blur pass using multiple threads.
    The image is divided into sections based on its width, and each
    thread processes its assigned columns independently.
 
    ThreadData stores the information required by each thread.
    pthread_create() starts the threads, while pthread_join() ensures
    that all threads finish before the function returns.
 */
    Matrix blur(const Matrix & m, const int radius, const int num_threads);

}

#endif