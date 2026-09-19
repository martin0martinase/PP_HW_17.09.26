#include <iostream>
#include <thread>
#include <vector>

bool isInside(double x, double y, double r){
    return x * x + y * y <= r * r;
}

struct Data{
    double r;
    size_t tests;
    size_t seed;
    size_t result;
};

int main(){
    size_t threads_count = 67;
    std::vector<Data> threads_data(threads_count);
    return 0;
}