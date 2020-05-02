#include "simple_chrono.hpp"

simple_chrono::simple_chrono(/* args */) {}

simple_chrono::~simple_chrono() {}

void simple_chrono::start() { m_start = std::chrono::steady_clock::now(); }

void simple_chrono::stop() { m_stop = std::chrono::steady_clock::now(); }

void simple_chrono::stop(std::string message) {
	m_stop = std::chrono::steady_clock::now();
	m_duration =
		std::chrono::duration_cast<std::chrono::microseconds>(m_stop - m_start);
	std::cout << message << m_duration.count() << "µs" << std::endl;
}

int simple_chrono::getUS() { return m_duration.count(); }