#include "GodInt.h"
#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>
#include <string>
void EulerProblem8();
void EulerProblem13();

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
	system("pause");
	return 0;
}

void EulerProblem13() {
	std::ifstream file("C:/Dev/C++/GodInt/GodInt/src/1.txt");
	std::vector<GodInt> numbers;
	GodInt result(0);
	std::string line;
	numbers.reserve(100);

	if (file.is_open()) {
		while (std::getline(file, line)) {
			numbers.emplace_back(line);
		}

		for (auto & i : numbers) {
			result += i;
		}
		std::cout << result;
		file.close();
	}
}
void EulerProblem8() {
	GodInt big_number("7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450");

	GodInt temp(0);
	GodInt result(0);
	unsigned long long int comparison = 1;
	unsigned long long int greatest_comparison = 1;

	Timer t;

	for (register int i = 0; i < big_number.size(); ++i) {
		comparison = 1;
		temp.clear();
		for (register int j = i; j < i + 13; j++) {
			temp.addLSV(big_number.getDigit(j));
			comparison *= big_number.getDigit(j);
		}
		if (comparison > greatest_comparison) {
			greatest_comparison = comparison;
			result = temp;
		}
	}
	double time = t.elapsed();

	std::cout << "The set of 13 consecutive numbers whose product is greates is " << result << " with a product of " << greatest_comparison << "\nIt was found in " << time << " ms\n";
}