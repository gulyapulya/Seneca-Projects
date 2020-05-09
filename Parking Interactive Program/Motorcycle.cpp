/* Citation and Sources...
Final Project Milestone 5
Module: Motorcycle
Filename: Motorcycle.cpp
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
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cctype>
#include "Motorcycle.h"

using namespace std;

namespace sdds 
{
	Motorcycle::Motorcycle()
	{
		sideCar = false;
	}

	Motorcycle::Motorcycle(const char *n_plate, const char *n_model) : Vehicle(n_plate, n_model)
	{ 
        sideCar = false;
	}

	Motorcycle::~Motorcycle()
	{
	}

	istream& Motorcycle::read(istream& is) 
	{
		string s;
		if (isCsv()) 
        {
			Vehicle::read(is);
			is>>sideCar;
			is.ignore(1000, '\n');
		}
		else
        {
			cout << "\nMotorcycle information entry\n";
			Vehicle::read(is);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			getline(is, s);
            while (s != "Y" && s != "y" && s != "N" && s != "n") 
            {
			    cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			    getline(is, s);
			}
            sideCar = (s == "Y" || s == "y");
		}
		return is;
	}
	ostream& Motorcycle::write(ostream& os) const 
	{
        if (isEmpty())
        {
			os << "Invalid Motorcycle Object\n";
			return os;
		}
		if (isCsv())
			os << "M,";
		else
			os << "Vehicle type: Motorcycle\n";
		Vehicle::write(os);
		if (isCsv())
			os << sideCar << endl;
		else if(sideCar)
			os << "With Sidecar" << endl;
		return os;
	} 

} //namespace sdds
