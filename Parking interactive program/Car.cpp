/* Citation and Sources...
Final Project Milestone 5
Module: Car
Filename: Car.cpp
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
#include "Car.h"

using namespace std;

namespace sdds 
{

	Car::Car()
	{
		carWash = false;
	}

	Car::Car(const char *n_plate, const char *n_model) : Vehicle(n_plate, n_model)
    {
        carWash = false;
    }

	Car::~Car()
	{
	}

	istream& Car::read(istream& is) 
	{
		string s;
		if (isCsv()) {
			Vehicle::read(is);
			is>>carWash;
			is.ignore(1000, '\n');
		} 
        else 
        {
		    cout << "\nCar information entry\n";
			Vehicle::read(is);
		    cout << "Carwash while parked? (Y)es/(N)o: ";
			getline(is, s);
            while (s != "Y" && s != "y" && s != "N" && s != "n") 
            {
			    cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			    getline(is, s);
			}
            carWash = (s == "Y" || s == "y");
		}
		return is;
	}

	ostream& Car::write(ostream& os) const 
	{
		if (isEmpty())
        {
			os << "Invalid Car Object\n";
			return os;
		}
		if (isCsv())
			os << "C,";
		else
			os << "Vehicle type: Car\n" ;
		Vehicle::write(os);
		if (isCsv())
			os << carWash << endl;
		else
		    os << (carWash ? "With Carwash\n" : "Without Carwash\n");
		return os;
	} 
} //namespace sdds
