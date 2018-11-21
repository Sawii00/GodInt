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
	/*Timer t;
	GodInt *result = new GodInt();
	*result = fibo_iter(500000);

	std::cout << "Time elapsed: " << t.elapsed() << " seconds \n";
	std::cout << *result << '\n';*/
	GodInt test1(123);
	GodInt test2 = test1.multiplyBySingleDigit(82);
	std::cout << test2 << std::endl;

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