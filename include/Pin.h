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
		std::string name = "";	

		/*!
		 * \brief Export the pin to a valid gpio folder.
		 * 
		 * Effectively, creates a folder with the direction, value
		 * and other informations about the pin, allowing its manipulation.
		 * In this implementation, this action cannot be called by itself,
		 * but is always invoked when a Pin object is created.
		 * */
		void doExport() const;

		/*!
		 * \brief Unexport pin, called in the destructor.
		 * */
		void unexport() const;

	public:

		/*! \brief Simplest constructor. */
		Pin();

		/*!
		 * \brief Constructor.
		 * 
		 * \param name			Pin's name.
		 * \param direction		Pin's direction.
		 * \param value			Pin's value.
		 * */
		Pin(std::string, GPIOSystem::Direction, GPIOSystem::Value);

		/*!
		 * \brief Destructor.
		 * */
		~Pin();

		/*! \brief Set name method. */
		void setName(std::string _name);

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
		GPIOSystem::Direction getDirection() const;

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
		GPIOSystem::Value getValue() const;

};

#endif
