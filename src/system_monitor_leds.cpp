#include <csignal>
#include <unistd.h>
#include <cstdio>
#include "Pin.h"
#include "check_cpu.cpp"

Pin green_led; 	
Pin yellow_led; 	
Pin red_led;	
Pin kill_button; 

void interruptHandler(int sig) {
	green_led.setValue(GPIOSystem::Value::LOW);
	yellow_led.setValue(GPIOSystem::Value::LOW);
	red_led.setValue(GPIOSystem::Value::LOW);
	exit(0);
}

int main(int argn, char * args[]) {

	// Configure to turn all leds off when interrupted by terminal
	signal(SIGINT, interruptHandler);

	// Initialize pins
	green_led.setName("P9_16"); 
	green_led.setDirection(GPIOSystem::Direction::OUT); 
	green_led.setValue(GPIOSystem::Value::LOW);

	yellow_led.setName("P9_14");
	yellow_led.setDirection(GPIOSystem::Direction::OUT); 
	yellow_led.setValue(GPIOSystem::Value::LOW);

	red_led.setName("P9_12"); 
	red_led.setDirection(GPIOSystem::Direction::OUT); 
	red_led.setValue(GPIOSystem::Value::LOW);

	kill_button.setName("P9_27");
	kill_button.setDirection(GPIOSystem::Direction::IN); 
	kill_button.setValue(GPIOSystem::Value::LOW);

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
