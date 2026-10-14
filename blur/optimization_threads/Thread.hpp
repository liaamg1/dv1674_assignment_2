#pragma once

#include "../optimization_2/matrix.hpp"


namespace blur_thread {

    /*
        source - The source matrix to be blurred.
        target - The target matrix where the blurred result will be stored.
        weights - The weights used for the Gaussian blur.
        radius - The blur radius
        start_x - The first column
        end_x - The ending x-coordinate for the thread's work.
        is_horizontal - A flag indicating if the blur is horizontal.


    */
    struct ThreadData
    {
        private:
            const Matrix * m;
            Matrix * dst;
            const double * weights;
            const int radius;

            int start_x;
            int end_x;
            bool is_horizontal;
        
        public:
            ThreadData(const Matrix * m, Matrix * dst, const double * weights, const int radius, int start_x, int end_x, bool is_horizontal)
                : m(m), dst(dst), weights(weights), radius(radius), start_x(start_x), end_x(end_x), is_horizontal(is_horizontal) {}

            void * blurWorker();
            static void* startThread(void* arg)
            {
                    ThreadData* data = static_cast<ThreadData*>(arg);
                    return data->blurWorker();
            }
                
    };
}
