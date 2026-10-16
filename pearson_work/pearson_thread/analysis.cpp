/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "analysis.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>
#include <pthread.h>
namespace Analysis {

//Separate the inner loop from previous optimization so
void calculate_row(const std::vector<Vector>& datasets,
                   std::vector<double>& result,
                   std::size_t i)
{
    const std::size_t n = datasets.size();
    // Normalize the first vector once and reuse it for every pair in this row.
    auto x = normalize(datasets[i]);
    // Count the pairs in all preceding rows to find this rows first result slot.
    // Each row writes to a separate section, so workers need no mutex.
    std::size_t index = i * (2 * n - i - 1) / 2;

    for (std::size_t j = i + 1; j < n; ++j) {
        result[index++] = pearson(x, datasets[j]);
    }
}
// Arguments passed to one worker: shared datasets and results,
// plus its ID and the total number of workers.
struct ThreadData {
    const std::vector<Vector>& datasets;
    std::vector<double>& result;
    std::size_t id;
    std::size_t thread_count;
};

void* worker(void* argument)
{
    // Recover our argument type from the void pointer required by pthreads.
    auto& data = *static_cast<ThreadData*>(argument);

    // Assign rows cyclically to spread the longer early rows across workers.
    // With 4 threads, worker 0 handles rows 0, 4, 8, ...;
    // worker 1 handles rows 1, 5, 9, ..., and so on.
    for (std::size_t i = data.id; i < data.datasets.size() - 1; i += data.thread_count) {
        calculate_row(data.datasets, data.result, i);
    }

    return nullptr;
}
std::vector<double>
correlation_coefficients(const std::vector<Vector>& datasets, std::size_t thread_count)
{
    const std::size_t n = datasets.size();

    // At least two datasets are needed to form a pair.
    if (n < 2) {
        return {};
    }

    // Allocate one slot for each unique pair before workers start.
    // Workers write by index instead of modifying the vector with push_back() (avoiding data races).
    std::vector<double> result(n * (n - 1) / 2);

    std::vector<ThreadData> arguments;
    std::vector<pthread_t> threads;

    // Reserve storage in advance. In particular, worker argument addresses
    // must remain valid while threads use them.
    arguments.reserve(thread_count);
    threads.reserve(thread_count);

    for (std::size_t id = 0; id < thread_count; ++id) {
        arguments.push_back({datasets, result, id, thread_count});
    }

    // Start each worker and keep the handles of successfully created threads.
    for (std::size_t id = 0; id < thread_count; ++id) {
        pthread_t thread;

        if (pthread_create(&thread, nullptr, worker,
                           &arguments[id]) == 0) {
            threads.push_back(thread);
        } else {
            worker(&arguments[id]);
        }
    }

    for (pthread_t thread : threads) {
        pthread_join(thread, nullptr);
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
