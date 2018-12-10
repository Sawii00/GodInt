#include "GodInt.h"
#include <iostream>
#include <chrono>
GodInt fibo_iter(int n);

class Timer {
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;
public:
	Timer() :m_beg(clock_t::now()) {}

	void reset() {
		m_beg = clock_t::now();
	}
	double elapsed() const {
		return std::chrono::duration_cast<second_t> (clock_t::now() - m_beg).count();
	}
};

int main() {
	Timer t;
	GodInt test2 = GodInt::factorial(100000);
	double time = t.elapsed();
	std::cout << test2.size() << '\n';
	std::cout << "Time elapsed: " << time << " seconds \n";

	system("pause");

	return 0;
}