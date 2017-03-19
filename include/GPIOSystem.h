#ifndef _GPIOSYSTEM_
#define _GPIOSYSTEM_

#include <map>
#include <string>

/*!
 * \brief Configurations of GPIO System based on SysFS.
 *
 * Contains a map from pins to gpio folders
 * and any other configurations related to the
 * filesystem of the Beaglebone Black being used.
 *
 * \author		Vitor Greati, Vinicius Campos
 * \date		2017-03-18
 * \version		1.0
 * */
class GPIOSystem {

	public:
		
		/*!
		 * \brief Direction of the communication in the I/O port.
		 * */
		enum class Direction {
			OUT = 0,
			IN = 1
		};

		/*!
		 * \brief Values that a port can assume.
		 * */
		enum class Value {
			LOW	= 0,
			HIGH = 1
		};
		
		/*!< Maps pin numbers into gpio folder names, default based on BeagleBone SRM. */
		static std::map<std::string, std::string> pinToIO;

		/*!< Path containing pin folders, default is /sys/class/gpio/ */
		static std::string sysgpiopath;

};
#endif
