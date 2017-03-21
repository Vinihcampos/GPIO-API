g++ -std=c++11 -Wall src/system_monitor_leds.cpp src/GPIOSystem.cpp src/Pin.cpp -o "bin/system_monitor_leds" -O3 -I"include/" -lboost_system -lboost_filesystem 
#arm-linux-gnueabihf-g++-4.9 -std=c++11 -Wall src/system_monitor_leds.cpp src/GPIOSystem.cpp src/Pin.cpp -o "bin/system_monitor_leds" -O3 -I"include/" 
