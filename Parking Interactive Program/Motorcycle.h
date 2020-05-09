/* Citation and Sources...
Final Project Milestone 5
Module: Motorcycle
Filename: Motorcycle.h
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
#ifndef SDDS_MOTORCYCLE_H__
#define SDDS_MOTORCYCLE_H__

#include <iostream>
#include "Vehicle.h"

namespace sdds 
{
	class Motorcycle : public Vehicle 
    {
		bool sideCar;
	public:
		Motorcycle();
		Motorcycle(const char *, const char*);
		~Motorcycle();
        Motorcycle(const Motorcycle &) = delete;
        Motorcycle &operator=(const Motorcycle &) = delete;
		std::istream& read(std::istream& = std::cin) override;
		std::ostream& write(std::ostream& = std::cout) const override;
	};
}
#endif
