#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <pthread.h>

struct Data{
    double r;
    size_t tests;
    size_t seed;
    size_t result;
};

bool isInside(double x, double y, double r){
    return x * x + y * y <= r * r;
}

void CutandFillVector(std::vector<Data>& thread_data, double r, size_t tests)
{
    size_t threads_count = thread_data.size();
    size_t whole = tests / threads_count;
    size_t rem = tests % threads_count;

    for (size_t i = 0; i < threads_count; ++i) {
        thread_data[i].r = r;
        thread_data[i].tests = (i < rem) ? whole + 1 : whole;
        thread_data[i].seed = i;
    }
}

void* calc(void* arg)
{
    auto data = static_cast<Data*>(arg);

    std::mt19937 gen(data->seed);
    std::uniform_real_distribution<double> dist(-data->r, data->r);

    double hits = 0;
    for (size_t i = 0; i < data->tests; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        if (isInside(x, y, data->r)) {
            ++hits;
        }
    }

    data->result = hits;
    return nullptr;
}

double area(double r, size_t threads, size_t tests){
    std::vector<Data> thread_data(threads);
    CutandFillVector(thread_data, r, tests);
    
    std::vector<pthread_t> handles(threads);
    for (size_t i = 0; i < threads; ++i){
        int err = pthread_create(&handles[i], nullptr, calc, &thread_data[i]);
        if (err){
            std::cerr << strerror(errno) << "\n";
        }
    }

    double hits_sum_count = 0;
    for (size_t i = 0; i < threads; ++i){
        int err = pthread_join(handles[i], nullptr);
        if (err){
            std::cerr << strerror(errno) << "\n";
        }
        hits_sum_count += thread_data[i].result;
    }

    double square_area = (2 * r) * (2 * r);
    return square_area * hits_sum_count / tests;
}
int main(int argc, char* argv[]){
    size_t threads_count = 67;
    double r = 1.0;
    size_t tests = 1000;

    return area(r, threads_count, tests);
}