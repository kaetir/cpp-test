// sort algorithm example
#include <algorithm>  // std::sort
#include <execution>  // std::execution::par
#include <iomanip>	  // std::setw
#include <iostream>	  // std::cout
#include <random>	  // random number generation
#include <vector>	  // std::vector

#include "libs/simple_chrono.hpp"

#define SIZE_VECTOR 100000000

int main() {
	srand(time(0));
	std::vector<float> improvement;

	for (size_t i = 0; i < 20; i++) {
		std::cout << "------------------------------" << std::endl;
		simple_chrono sc = simple_chrono();
		std::vector<float> toIterate(SIZE_VECTOR);
		std::vector<float> toIterate2(SIZE_VECTOR);
		float uS_sync, uS_async;
		float toFill = rand() % 1000;

		sc.start();
		std::fill(toIterate.begin(), toIterate.end(), toFill);
		sc.stop("fill the vector        : ");
		uS_sync = sc.getUS();

		sc.start();
		std::fill(std::execution::par, toIterate2.begin(), toIterate2.end(),
				  toFill);
		sc.stop("fill the vector async  : ");
		uS_async = sc.getUS();

		std::cout << "___________________________" << std::endl;
		std::cout << "sync              : " << std::fixed << std::setw(11)
				  << std::setprecision(0) << uS_sync << " µs" << std::endl;
		std::cout << "async             : " << std::fixed << std::setw(11)
				  << std::setprecision(0) << uS_async << " µs" << std::endl;
		std::cout << "ratio (s/as)      : " << std::setw(11)
				  << std::setprecision(4) << (float)uS_sync / uS_async
				  << std::endl;
		std::cout << "improvement (s/as): " << std::setw(11)
				  << std::setprecision(4)
				  << (float)(uS_sync - uS_async) / uS_async * 100. << " %"
				  << std::endl;
		improvement.push_back((float)(uS_sync - uS_async) / uS_async * 100.);
	}
	std::cout << "==============================" << std::endl;

	int count = 0;
	for (auto &&i : improvement)
		std::cout << ++count << " : " << std::setw(11) << std::setprecision(4)
				  << i << " %" << std::endl;

	std::cout << "==============================" << std::endl;
	std::cout << "total :" << std::setw(11) << std::setprecision(4)
			  << std::accumulate(improvement.begin(), improvement.end(), 0.0) /
					 improvement.size()
			  << std::endl;

	return 0;
}