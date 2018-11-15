#include "GodInt.h"
#include <iostream>

int main() {
	std::string test1 = "1000000000000000000000000000000000000000000000000000000000000000000000000000000";
	std::string test2 = "9999999999999312312312312312312312312313123";
	GodInt gd(test1);
	std::cout << gd << '+' << '\n';
	GodInt test(test2);
	std::cout << test << '=' << '\n';
	gd += test;
	std::cout << gd << '\n';

	system("pause");

	return 0;
}