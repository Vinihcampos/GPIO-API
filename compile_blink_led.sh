g++ -std=c++11 -Wall src/led_blink.cpp src/GPIOSystem.cpp src/Pin.cpp -o "bin/led_blink" -O3 -I"include/"
arm-linux-gnueabihf-g++-4.9 -std=c++11 -Wall src/led_blink.cpp src/GPIOSystem.cpp src/Pin.cpp -o "bin/led_blink_arm" -O3 -I"include/"
