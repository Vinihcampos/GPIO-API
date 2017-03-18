#include "Pin.h"

Pin::Pin(std::string _name, GPIOSystem::Direction _direction, GPIOSystem::Value _value) : name{_name} {
	setValue(_value);
	setDirection(_direction);
}


std::string Pin::getName() const {
	return name;
}

void Pin::setDirection(GPIOSystem::Direction _direction) {

}

GPIOSystem::Value Pin::getDirection() const {

}


void Pin::setValue(GPIOSystem::Value _value) {

}

GPIOSystem::Direction Pin::getValue() const {

}

