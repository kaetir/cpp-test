// sort algorithm example
#include <algorithm>  // std::sort
#include <execution>  // std::execution::par
#include <iostream>	  // std::cout
#include <random>	  // random number generation
#include <vector>	  // std::vector

#include "libs/simple_chrono.hpp"

#define SIZE_VECTOR 100000000

int main() {
	srand(time(0));
	simple_chrono sc = simple_chrono();
	std::vector<float> toSort;
	std::vector<float> toSort2(SIZE_VECTOR);

	sc.start();
	for (size_t i = 0; i < SIZE_VECTOR; i++) {
		toSort.push_back(rand() / RAND_MAX);
	}
	sc.stop("fill the vector : ");

	sc.start();
	std::copy(toSort.begin(), toSort.end(), toSort2.begin());
	sc.stop("copy done in : ");

	sc.start();
	std::sort(toSort.begin(), toSort.end());
	sc.stop("Sort syncrone : ");

	sc.start();
	std::sort(std::execution::par, toSort2.begin(), toSort2.end());
	sc.stop("Sort asyncrone : ");

	return 0;
}
