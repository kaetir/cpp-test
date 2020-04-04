// sort algorithm example
#include <algorithm> // std::sort
#include <chrono> // https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
#include <execution> // std::execution::par
#include <iostream> // std::cout
#include <random> // random number generation
#include <vector> // std::vector

#define SIZE_VECTOR 100000000

std::chrono::_V2::steady_clock::time_point start;
std::chrono::_V2::steady_clock::time_point stop;
std::chrono::__enable_if_is_duration<std::chrono::microseconds> duration;

#define START_CHRONO() start = std::chrono::steady_clock::now();

#define STOP_CHRONO(mes)                                                            \
    stop = std::chrono::steady_clock::now();                                        \
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); \
    std::cout << mes << duration.count() << "µs" << std::endl;

int main()
{
    srand(time(0));
    std::vector<float> toSort;
    std::vector<float> toSort2(SIZE_VECTOR);

    START_CHRONO();
    for (size_t i = 0; i < SIZE_VECTOR; i++) {
        toSort.push_back(rand() / RAND_MAX);
    }
    STOP_CHRONO("fill the vector : ")

    START_CHRONO();
    std::copy(toSort.begin(), toSort.end(), toSort2.begin());
    STOP_CHRONO("copy done : ")

    START_CHRONO();
    std::sort(toSort.begin(), toSort.end());
    STOP_CHRONO("Sort syncrone : ");

    START_CHRONO();
    std::sort(std::execution::par, toSort2.begin(), toSort2.end());
    STOP_CHRONO("Sort asyncrone : ");

    return 0;
}