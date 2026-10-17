/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "filters.hpp"
#include "../optimization_2/matrix.hpp"
#include "../optimization_2/ppm.hpp"
#include <cmath>
#include "Thread.hpp"

#include <pthread.h>
#include <vector>
#include <stdexcept>
#include <algorithm>


namespace Filter
{

    namespace Gauss
    {
        void get_weights(int n, double *weights_out)
        {
            for (auto i{0}; i <= n; i++)
            {
                double x{static_cast<double>(i) * max_x / n};
                weights_out[i] = exp(-x * x * pi);
            }
        }
    }

    Matrix blur(const Matrix& m, const int radius, const int num_threads)
{

    Matrix scratch{m.get_x_size(), m.get_y_size()};
    auto dst{m};

    double w[Gauss::max_radius]{};
    Gauss::get_weights(radius, w);

    int width = m.get_x_size();
    int count = std::min(num_threads, width);

    auto runPass = [&](const Matrix& source, Matrix& target, bool horizontal)
    {
        std::vector<pthread_t> threads(count);
        std::vector<blur_thread::ThreadData> data;
        data.reserve(count);

        for (int i = 0; i < count; i++)
        {
            int start_x = i * width / count;
            int end_x = (i + 1) * width / count;

            data.emplace_back(
                &source,
                &target,
                w,
                radius,
                start_x,
                end_x,
                horizontal
            );
        }

        int created = 0;

        for (int i = 0; i < count; i++)
        {
            int result = pthread_create(
                &threads[i],
                nullptr,
                blur_thread::ThreadData::startThread,
                &data[i]
            );

            if (result != 0)
            {
                for (int j = 0; j < created; j++)
                    pthread_join(threads[j], nullptr);

                throw std::runtime_error("Failed to create thread");
            }

            created++;
        }

        for (int i = 0; i < count; i++)
        {
            pthread_join(threads[i], nullptr);
        }
    };

    // Horizontal pass
    runPass(m, scratch, true);

    // Vertical pass
    runPass(scratch, dst, false);

    return dst;
}
}
