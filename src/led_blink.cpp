#include "Pin.h"
#include <unistd.h>

int main(void) {

	Pin redled {"P9_16", GPIOSystem::Direction::OUT, GPIOSystem::Value::LOW};
	Pin button {"P9_27", GPIOSystem::Direction::IN, GPIOSystem::Value::LOW};

	while (true) {
		if (button.getValue() == GPIOSystem::Value::HIGH)
			redled.setValue(GPIOSystem::Value::HIGH);
		else
			redled.setValue(GPIOSystem::Value::LOW);
	}

	return 0;
}
