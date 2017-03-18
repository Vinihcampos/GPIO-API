#ifndef _PIN_
#define _PIN_

#include "GPIOSystem.h"

/*!
 * \brief Represents and allows manipulation of a pin.
 * 
 * \author		Vitor Greati, Vinicius Campos
 * \date		2017-03-18
 * \version		1.0
 * */
class Pin {

	private:

		/*!< Pin name, generally in the form P[8,9]_[0-9][0-9][0-9]. */
		std::string name;	

	public:

		/*!
		 * \brief Constructor.
		 * 
		 * \param name			Pin's name.
		 * \param direction		Pin's direction.
		 * \param value			Pin's value.
		 * */
		Pin(std::string, GPIOSystem::Direction, GPIOSystem::Value);

		/*! 
		 * \brief Get pin's name.
		 * 
		 * \return Pin's name.
		 * */
		std::string getName() const;

		/*!
		 * \brief Set pin's direction.
		 * 
		 * \param direction		Pin's direction.
		 * */
		void setDirection(GPIOSystem::Direction _direction);

		/*!
		 * \brief Get pin's direction.
		 * 
		 * \return Current pin's direction.
		 * */
		GPIOSystem::Value getDirection() const;

		/*!
		 * \brief Set pin's value.
		 * 
		 * \param value			Pin's value.
		 * */
		void setValue(GPIOSystem::Value _value);

		/*!
		 * \brief Get pin's value.
		 * 
		 * \return Current pin's value.
		 * */
		GPIOSystem::Direction getValue() const;

};

#endif
