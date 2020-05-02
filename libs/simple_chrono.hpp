#include <chrono>  // https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
#include <iostream>	 // std::cout

class simple_chrono {
   private:
	std::chrono::_V2::steady_clock::time_point m_start;
	std::chrono::_V2::steady_clock::time_point m_stop;
	std::chrono::__enable_if_is_duration<std::chrono::microseconds> m_duration;

   public:
	simple_chrono(/* args */);
	~simple_chrono();

	void start();
	void stop();
	void stop(std::string message);
	int getUS();
};
