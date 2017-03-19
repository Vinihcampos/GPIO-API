#include <iostream>
#include "GPIOSystem.h"
#include "Pin.h"

int main(void) {

	std::cout << GPIOSystem::pinToIO["P9_14"].substr(4) << std::endl;

	Pin redled {"P9_14", GPIOSystem::Direction::IN, GPIOSystem::Value::LOW};

	return 0;
};
