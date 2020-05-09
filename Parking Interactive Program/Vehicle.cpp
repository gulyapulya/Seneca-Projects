/* Citation and Sources...
Final Project Milestone 4
Module: Vehicle
Filename: Vehicle.cpp
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
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cctype>
#include "Vehicle.h"

using namespace std;

namespace sdds
{
    Vehicle::Vehicle()
    {
        setEmpty();
    }

    Vehicle::Vehicle(const char *n_plate, const char *n_model) 
    {
        setEmpty();
        if(n_plate != nullptr && n_model != nullptr && strlen(n_plate) <= MAX_CHAR && strlen(n_model) > 2)
        {   
            char temp[MAX_CHAR + 1];
            for(int i = 0; i < (int)strlen(n_plate); i++)
                temp[i] = toupper(n_plate[i]);
            temp[(int)strlen(n_plate)] = '\0';
            strcpy(plate, temp);
            setMakeModel(n_model);
        }
    }

    Vehicle::~Vehicle()
    {
        delete[] model;
    }

    void Vehicle::setEmpty()
    {
        plate[0] = '\0';
        model = nullptr;
        spotn = 0;
    }

    bool Vehicle::isEmpty() const
    {
        return plate[0] == '\0';
    }

    const char* Vehicle::getLicensePlate() const
    {
        return plate;
    }

    const char *Vehicle::getMakeModel() const
    {
        return model;
    }

    void Vehicle::setMakeModel(const char * n_model)
    {
        delete[] model;
        model = nullptr;
        if(n_model != nullptr && strlen(n_model) > 1)
        {
            model = new char[strlen(n_model) + 1];
            strcpy(model, n_model);
        }
        else
            setEmpty();
    }

    int Vehicle::getParkingSpot() const
    {
        return spotn;
    }

    void Vehicle::setParkingSpot(const int n_spotn)
    {
        if(n_spotn < 0)
        {
            delete[] model;
            setEmpty();
        }
        else
            spotn = n_spotn;
    }

    bool operator==(const Vehicle &curr, const char *source)
    {
        char temp[MAX_CHAR + 1];
        for(int i = 0; i < (int)strlen(source); i++)
            temp[i] = toupper(source[i]);
        temp[(int)strlen(source)] = '\0';
        return strcmp(temp, curr.getLicensePlate()) == 0;
    }

    bool operator==(const Vehicle &curr, const Vehicle &source)
    {
        return strcmp(source.getLicensePlate(), curr.getLicensePlate()) == 0;
    }

    istream &Vehicle::read(istream & is)
    {
        string temp_plate, temp_model;
        if(!is)
            return is;
        if(isCsv())
        {
            is>>spotn;
            is.ignore();
            is.width(9);
            getline(is, temp_plate, ',');
            is.width(61);
            getline(is, temp_model, ',');
        }
        else
        {
            spotn = 0;
            cout<<"Enter Licence Plate Number: ";
            getline(is, temp_plate);
            while((int)temp_plate.length() > 8 || (int)temp_plate.length() < 1)
            {
                cout<<"Invalid Licence Plate, try again: ";
                getline(is, temp_plate);
            }
            cout<<"Enter Make and Model: ";
            getline(is, temp_model);
            while((int)temp_model.length() > 60 || (int)temp_model.length() < 2)
            {
                cout<<"Invalid Make and model, try again: ";
                getline(is, temp_model);
            }
        }
        for(int i = 0; i < (int)temp_plate.length(); i++)
                plate[i] = toupper(temp_plate[i]);
        plate[(int)temp_plate.length()] = '\0';

        char n_model[60 + 1];
        for(int i = 0; i < (int)temp_model.length(); i++)
                n_model[i] = temp_model[i];
        n_model[(int)temp_model.length()] = '\0';
        setMakeModel(n_model);
        return is;
    }

    std::ostream &Vehicle::write(std::ostream & os) const
    {
        if(isEmpty())
        {
            os<<"Invalid Vehicle Object"<<endl;
            return os;
        }
        if(isCsv())
            os<<spotn<<','<<plate<<','<<model<<',';
        else
        {
            os<<"Parking Spot Number: ";
            if (spotn == 0)
                os<<"N/A\n";
            else
                os<<spotn<<endl;
            os<<"Licence Plate: "<<plate<<endl;
            os<<"Make and Model: "<<model<<endl;            
        }
        return os;
    }

} // namespace sdds
