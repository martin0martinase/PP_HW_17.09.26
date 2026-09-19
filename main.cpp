#include <iostream>
#include <thread>

bool isDotInsideCircle(double x, double y, double r){
    return x * x + y * y <= r * r;
}

struct Data{
    double r;
    size_t tests;
    size_t result;
};// я хз как иначе это сделать но вот это в потоковую ф.

int main(){
    return 0;
}