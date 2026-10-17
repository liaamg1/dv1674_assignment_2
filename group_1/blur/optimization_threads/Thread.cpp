#include "Thread.hpp"

void* blur_thread::ThreadData::blurWorker() {
    for (int x = this->start_x; x < this->end_x; x++) {
        for (int y = 0; y < this->m->get_y_size(); y++)
        {
            auto r{this->weights[0] * this->m->r(x, y)};
            auto g{this->weights[0] * this->m->g(x, y)};
            auto b{this->weights[0] * this->m->b(x, y)};
            auto n{this->weights[0]};

            for (int wi = 1; wi <= radius; wi++)
            {
                auto wc{weights[wi]};

                int position = this->is_horizontal ? x : y;
                int limit = this->is_horizontal ? this->m->get_x_size() : this->m->get_y_size();

                for (int offset : {-wi, wi})
                {
                    int neighbor = position + offset;

                    if (neighbor >= 0 && neighbor < limit)
                    {
                        int nx = this->is_horizontal ? neighbor : x;
                        int ny = this->is_horizontal ? y : neighbor;

                        r += wc * this->m->r(nx, ny);
                        g += wc * this->m->g(nx, ny);
                        b += wc * this->m->b(nx, ny);
                        n += wc;
                    }
                }
            }
            this->dst->r(x, y) = r / n;
            this->dst->g(x, y) = g / n;
            this->dst->b(x, y) = b / n;
        }
    }
    return nullptr;
}
