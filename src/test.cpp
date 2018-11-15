#include "GodInt.h"
#include <iostream>

int main() {
	GodInt gd1(100);
	//test: -100 + (-50)
	GodInt gd3 = 10 + gd1;
	std::cout << gd3;

	system("pause");

	return 0;
}