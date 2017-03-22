#include <csignal>
#include "Pin.h"
#include <unistd.h>
#include "check_cpu.cpp"

// Initialize pins
Pin green_led 		{"P9_16", GPIOSystem::Direction::OUT, GPIOSystem::Value::LOW};
Pin yellow_led 		{"P9_14", GPIOSystem::Direction::OUT, GPIOSystem::Value::LOW};
Pin red_led 		{"P9_12", GPIOSystem::Direction::OUT, GPIOSystem::Value::LOW};
Pin kill_button 	{"P9_27", GPIOSystem::Direction::IN, GPIOSystem::Value::LOW};

void interruptHandler(int signal) {
	green_led.setValue(GPIOSystem::Value::LOW);
	yellow_led.setValue(GPIOSystem::Value::LOW);
	red_led.setValue(GPIOSystem::Value::LOW);
}

int main(int argn, char * args[]) {

	// Configure to turn all leds off when interrupted by terminal
	signal(SIGINT, interruptHandler);

	// Main loop
	unsigned int interval_update = atoi(args[1]) * 1000; 	/*!< Update at each 'interval_update' ms */
	while (true) {

		std::pair<int,int> totaltime;
		double usage_percentage = check_cpu_usage(interval_update/1000, totaltime);

		std::cout << usage_percentage << std::endl;

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
				if (kill_button.getValue() == GPIOSystem::Value::HIGH) {
					std::string kill_command = "kill -9 " + check_process_usage(interval_update/1000);
					int s = system(kill_command.c_str());
					usage_percentage = check_cpu_usage(interval_update/1000, totaltime); 
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
				usleep(10000); 
				green_led.setValue(GPIOSystem::Value::LOW);
				yellow_led.setValue(GPIOSystem::Value::LOW);
				red_led.setValue(GPIOSystem::Value::LOW);
				usage_percentage = check_cpu_usage(100, totaltime);
			}
		}

		usleep(interval_update);			
	}

	return 0;
}
