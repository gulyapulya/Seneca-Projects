/* Citation and Sources...
Final Project Milestone 4
Module: Vehicle
Filename: Vehicle.h
Version 1.0
Author Baimukhambetova Gulnur
Revision History
-----------------------------------------------------------
Date Reason
2020/03/30 Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_VEHICLE_H__
#define SDDS_VEHICLE_H__

#include <iostream>
#include "ReadWritable.h"

namespace sdds
{
    const int MAX_CHAR = 8;
    class Vehicle : public ReadWritable
    {
        char plate[MAX_CHAR + 1];
        char *model;
        int spotn;
    protected:
        void setEmpty();
        bool isEmpty() const;
        const char *getLicensePlate() const;
        const char *getMakeModel() const;
        void setMakeModel(const char *);
    public:
        Vehicle();
        Vehicle(const char *, const char *);
        Vehicle(const Vehicle &) = delete;
        Vehicle &operator=(const Vehicle &) = delete;
        ~Vehicle();
        int getParkingSpot() const;
        void setParkingSpot(const int);
        friend bool operator==(const Vehicle &, const char *);
        friend bool operator==(const Vehicle &, const Vehicle &); 
        std::istream &read(std::istream & = std::cin);
        std::ostream &write(std::ostream & = std::cout) const;
    };
} // namespace sdds
#endif
