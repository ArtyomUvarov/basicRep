#include "random_value.h"

int random() {
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int random_value = std::rand() % 100;
	//std::cout << random_value << std::endl;
	return random_value;
}
