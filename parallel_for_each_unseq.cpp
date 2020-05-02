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
		std::vector<float> toIterate;
		std::vector<float> out;
		float uS_sync, uS_async;

		sc.start();
		for (size_t i = 0; i < SIZE_VECTOR; i++) {
			toIterate.push_back(rand() / RAND_MAX);
		}
		sc.stop("fill the vector        : ");

		sc.start();
		std::for_each(toIterate.begin(), toIterate.end(),
					  [&](auto i) { out.push_back(i * 2); });
		sc.stop("multiply by 2 syncrone : ");
		uS_sync = sc.getUS();

		out.clear();
		sc.start();
		std::for_each(std::execution::par_unseq, toIterate.begin(),
					  toIterate.end(), [&](auto i) { out.push_back(i * 2); });
		sc.stop("multiply by 2 asyncrone: ");
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