#include "Pin.h"
#include <unistd.h>

int main(int argn, char * args[]) {

	// Initialize pins
	Pin green_led 		{"P9_12", GPIOSystem::Direction::OUT, GPIOSystem::Value::LOW};
	Pin yellow_led 		{"P9_14", GPIOSystem::Direction::OUT, GPIOSystem::Value::LOW};
	Pin red_led 		{"P9_16", GPIOSystem::Direction::OUT, GPIOSystem::Value::LOW};
	Pin kill_button 	{"P9_27", GPIOSystem::Direction::IN, GPIOSystem::Value::LOW};

	// Main loop
	unsigned int interval_update = atoi(args[1]) * 1000; 	/*!< Update at each 'interval_update' ms */
	while (true) {
		double usage_percentage; // TODO: update CPU percentage

		if (usage_percentage <= 25) {
			// Green LED
			green_led.setValue(GPIOSystem::Value::HIGH);
			yellow_led.setValue(GPIOSystem::Value::LOW);
			red_led.setValue(GPIOSystem::Value::LOW);
		} else if (usage_percentage <= 50) {
			// Yellow LED
			green_led.setValue(GPIOSystem::Value::LOW);
			yellow_led.setValue(GPIOSystem::Value::HIGH);
			red_led.setValue(GPIOSystem::Value::LOW);
		} else if (usage_percentage <= 75) {
			// Red LED
			green_led.setValue(GPIOSystem::Value::LOW);
			yellow_led.setValue(GPIOSystem::Value::LOW);
			red_led.setValue(GPIOSystem::Value::HIGH);
		} else {
			while (usage_percentage >= 75) {
				// Kill the most expensive by button pressing
				if (button.getValue() == GPIOSystem::Value::HIGH) {
					pid_t expensive_process; // TODO: Return the PID of most expensive
					system("kill -9 " + pid_t);
					usage_percentage = 74; // TODO: Get percentage
					if (usage_percentage < 75) {
						green_led.setValue(GPIOSystem::Value::LOW);
						yellow_led.setValue(GPIOSystem::Value::LOW);
						red_led.setValue(GPIOSystem::Value::LOW);
						break;
					}
				}
				// Make all blink
				green_led.setValue(GPIOSystem::Value::HIGH);
				yellow_led.setValue(GPIOSystem::Value::HIGH);
				red_led.setValue(GPIOSystem::Value::HIGH);
				usleep(interval_update/4); 
				green_led.setValue(GPIOSystem::Value::LOW);
				yellow_led.setValue(GPIOSystem::Value::LOW);
				red_led.setValue(GPIOSystem::Value::LOW);
				usage_percentage = 75;// TODO: update usage_percentage
			}
		}

		usleep(interval_update);			
	}

	return 0;
}
