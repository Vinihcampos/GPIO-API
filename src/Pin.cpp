#include "Pin.h"
#include <iostream>
#include <fstream>

Pin::Pin() {}

Pin::Pin(std::string _name, GPIOSystem::Direction _direction, GPIOSystem::Value _value) : name{_name} {
	// Check if this pin is defined
	if (GPIOSystem::pinToIO.find(_name) == GPIOSystem::pinToIO.end())
		throw std::invalid_argument("PIN name not registered!");
	// Creates the folder
	doExport();
	// Set initial direction
	setDirection(_direction);
	// Set initial value
	setValue(_value);
}

Pin::~Pin() {
	setValue(GPIOSystem::Value::HIGH);
	unexport();
}

void Pin::doExport() const {
	std::string path = GPIOSystem::sysgpiopath + "/export";
	std::ofstream ofs {path};
	if (ofs.is_open()) {
		ofs << GPIOSystem::pinToIO[name].substr(4);	
	} else throw std::logic_error("Unable to export pin.");
}

void Pin::unexport() const {
	std::string path = GPIOSystem::sysgpiopath + "/unexport";
	std::ofstream ofs {path};
	if (ofs.is_open()) {
		ofs << GPIOSystem::pinToIO[name].substr(4);	
	} else throw std::logic_error("Unable to unexport pin.");
}

std::string Pin::getName() const {
	return name;
}

void Pin::setName(std::string _name) {
	// Check if this pin is defined
	if (GPIOSystem::pinToIO.find(_name) == GPIOSystem::pinToIO.end())
		throw std::invalid_argument("PIN name not registered!");
	// Set attribute
	this->name = _name;
	// Creates the folder
	doExport();
}

void Pin::setDirection(GPIOSystem::Direction _direction) {
	std::string path = GPIOSystem::sysgpiopath + GPIOSystem::pinToIO[name] + "/direction";
	std::ofstream ofs {path};
	if (ofs.is_open()) {
		switch (_direction) {
			case GPIOSystem::Direction::IN:
				ofs << "in";
				break;
			case GPIOSystem::Direction::OUT:
				ofs << "out";
				break;
			default:
				throw std::logic_error("Invalid direction.");
		}	
	} else throw std::logic_error("Error at setting this direction.");
}

GPIOSystem::Direction Pin::getDirection() const {
	std::string path = GPIOSystem::sysgpiopath + GPIOSystem::pinToIO[name] + "/direction";
	std::ifstream ifs {path};
	std::string str_direction;
	GPIOSystem::Direction direction; 
	if (ifs.is_open()) {
		ifs >> str_direction;
		if (str_direction == "in")
				direction = GPIOSystem::Direction::IN;
		else if (str_direction == "out")
				direction = GPIOSystem::Direction::OUT;
		else
				throw std::logic_error("Invalid direction.");
		return direction;
	} else throw std::logic_error("Error at reading this direction.");
}


void Pin::setValue(GPIOSystem::Value _value) {
	std::string path = GPIOSystem::sysgpiopath + GPIOSystem::pinToIO[name] + "/value";
	std::ofstream ofs {path};
	if (ofs.is_open()) {
		switch (_value) {
			case GPIOSystem::Value::HIGH:
				ofs << "1";
				break;
			case GPIOSystem::Value::LOW:
				ofs << "0";
				break;
			default:
				throw std::logic_error("Invalid value.");
		}	
	} else throw std::logic_error("Error at setting this value.");
}

GPIOSystem::Value Pin::getValue() const {
	std::string path = GPIOSystem::sysgpiopath + GPIOSystem::pinToIO[name] + "/value";
	std::ifstream ifs {path};
	std::string str_value;
	GPIOSystem::Value value; 
	if (ifs.is_open()) {
		ifs >> str_value;
		if (str_value == "1")
				value = GPIOSystem::Value::HIGH;
		else if (str_value == "0")
				value = GPIOSystem::Value::LOW;
		else
				throw std::logic_error("Invalid value.");
		return value;
	} else throw std::logic_error("Error at reading this value.");
}

