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
		 * \brief Intern class for initializing static members.
		 * */
		class _init {
			public:
				_init() {
					pinToIO = {
						{"P9_11", "gpio30"},
						{"P9_12", "gpio60"},
						{"P9_13", "gpio31"},
						{"P9_14", "gpio50"},
						{"P9_15", "gpio48"},
						{"P9_16", "gpio51"},
						{"P9_17", "gpio5"},
						{"P9_18", "gpio4"},
						{"P9_21", "gpio3"},
						{"P9_22", "gpio2"},
						{"P9_23", "gpio49"},
						{"P9_25", "gpio117"},
						{"P9_26", "gpio14"},
						{"P9_27", "gpio115"},
						{"P9_28", "gpio113"},
						{"P9_29", "gpio111"},
						{"P9_30", "gpio112"},
						{"P9_31", "gpio110"},
						{"P9_41", "gpio20"},
						{"P9_42", "gpio7"},
						{"P8_03", "gpio38"},
						{"P8_04", "gpio39"},
						{"P8_05", "gpio34"},
						{"P8_06", "gpio35"},
						{"P8_07", "gpio66"},
						{"P8_08", "gpio67"},
						{"P8_09", "gpio69"},
						{"P8_10", "gpio68"},
						{"P8_11", "gpio45"},
						{"P8_12", "gpio44"},
						{"P8_13", "gpio23"},
						{"P8_14", "gpio26"},
						{"P8_15", "gpio47"},
						{"P8_16", "gpio46"},
						{"P8_17", "gpio27"},
						{"P8_18", "gpio65"},
						{"P8_19", "gpio22"},
						{"P8_20", "gpio63"},
						{"P8_21", "gpio62"},
						{"P8_22", "gpio37"},
						{"P8_23", "gpio36"},
						{"P8_24", "gpio33"},
						{"P8_25", "gpio32"},
						{"P8_26", "gpio61"},
						{"P8_27", "gpio86"},
						{"P8_28", "gpio88"},
						{"P8_29", "gpio87"},
						{"P8_30", "gpio89"},
						{"P8_31", "gpio10"},
						{"P8_32", "gpio11"},
						{"P8_33", "gpio9"},
						{"P8_34", "gpio81"},
						{"P8_35", "gpio8"},
						{"P8_36", "gpio80"},
						{"P8_37", "gpio78"},
						{"P8_38", "gpio79"},
						{"P8_39", "gpio76"},
						{"P8_40", "gpio77"},
						{"P8_41", "gpio74"},
						{"P8_42", "gpio75"},
						{"P8_43", "gpio72"},
						{"P8_44", "gpio73"},
						{"P8_45", "gpio70"},
						{"P8_46", "gpio71"}
					};

					sysgpiopath = "/sys/class/gpio/";
			};
		};

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

	private:
		/*!< Create _init object to initialize static attributes. */
		static _init init;

};
#endif
