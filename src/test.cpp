#include "GodInt.h"
#include <iostream>
#include <chrono>
GodInt fibo_iter(int n);
long long fibo_iter2(int n);

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
	GodInt result = fibo_iter(100000);
	std::cout << "Time elapsed: " << t.elapsed() << " seconds \n";
	std::cout << result << '\n';
	//t.reset();
	//long long result2 = fibo_iter2(50);
	//std::cout << "Time elapsed: " << t.elapsed() << " seconds \n";
	//std::cout << result2 << '\n';

	system("pause");

	return 0;
}

GodInt fibo_iter(int n)
{
	GodInt previous = 1;
	GodInt current = 1;
	GodInt next = 1;

	for (register int i = 3; i <= n; ++i)
	{
		next = current + previous;
		previous = current;
		current = next;
		std::cout << i << '\n';
	}
	return next;
}
long long fibo_iter2(int n)
{
	long long previous = 1;
	long long current = 1;
	long long next = 1;

	for (int i = 3; i <= n; ++i)
	{
		next = current + previous;
		previous = current;
		current = next;
	}
	return next;
}