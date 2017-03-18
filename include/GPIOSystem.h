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
		/*!< Maps pin numbers into gpio folder names, default based on BeagleBone SRM. */
		static std::map<std::string, std::string> pinToIO;

};
#endif
