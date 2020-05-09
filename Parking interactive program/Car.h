/* Citation and Sources...
Final Project Milestone 5
Module: Car
Filename: Car.h
Version 1.0
Author Baimukhambetova Gulnur
Revision History
-----------------------------------------------------------
Date Reason
2020/04/02 Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_CAR_H__
#define SDDS_CAR_H__

#include <iostream>
#include "Vehicle.h"

namespace sdds
{
	class Car : public Vehicle 
    {
		bool carWash;
	public:
		Car();
		Car(const char *, const char*);
        ~Car();
        Car(const Car &) = delete;
        Car &operator=(const Car &) = delete;
		std::istream& read(std::istream& = std::cin) override;
		std::ostream& write(std::ostream& = std::cout) const override; 
	};
}
#endif
