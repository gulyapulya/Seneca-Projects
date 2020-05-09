/* Citation and Sources...
Final Project Milestone 6
Module: Parking
Filename: Parking.cpp
Version 1.0
Author Baimukhambetova Gulnur
Revision History
-----------------------------------------------------------
Date Reason
2020/04/10 Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Parking.h"
#include "Car.h"
#include "Motorcycle.h"

using namespace std;

namespace sdds
{
    Parking::Parking(const char* datafile, int noOfSpots)
    {
        pNumParked = 0;
        for(int i = 0; i < maxSpots; i++)
            pSpots[i] = nullptr;
        if (datafile == nullptr || strlen(datafile) == 0 || noOfSpots < 10 || noOfSpots > maxSpots)
        {
            pData = nullptr;
            pNumSpots = 0;
        }
        else
        {
            pData = new char[strlen(datafile) + 1];
            strcpy(pData, datafile);
            pNumSpots = noOfSpots;
            
        }
        if (loadData())
        {
            pMenu = Menu("Parking Menu, select an action:");
            pMenu.add("Park Vehicle");
            pMenu.add("Return Vehicle");
            pMenu.add("List Parked Vehicles");
            pMenu.add("Close Parking (End of day)");
            pMenu.add("Exit Program");

            pVSMenu = Menu("Select type of the vehicle:", 1);
            pVSMenu.add("Car");
            pVSMenu.add("Motorcycle");
            pVSMenu.add("Cancel");
        }
        else
        {
            cout << "Error in data file" << endl;
            pData = nullptr;
        }
    }

    Parking::~Parking()
    {
        saveData();
        delete[] pData;
        for(int i = 0; i < maxSpots; i++)
            delete pSpots[i];
    }

    bool Parking::isEmpty()
    {
        return pData == nullptr;
    }

    void Parking::pStatus()
    {
        cout << "****** Seneca Valet Parking ******" << endl;
        cout << "*****  Available spots: ";
        cout << left << setw(4) << (pNumSpots - pNumParked);
        cout << " *****" << endl;
    }

    int Parking::findSpot()
    {
        for(int i = 0; i < pNumSpots; i++)
            if(pSpots[i] == nullptr)
                return i;
        return -1;
    }

    void Parking::parkVehicle()
    {
        if(pNumSpots - pNumParked < 1)
        {
            cout<<"Parking is full"<<endl;
            return;
        }
        Vehicle* vehP = nullptr;
        int option = pVSMenu.run();
        if(option == 3)
        {
            cout << "Parking cancelled" << endl;
            return;
        }
        if(option == 1)
            vehP = new Car();
        else
            vehP = new Motorcycle();
        cin >> (*vehP);
        int ticket = findSpot();
        pSpots[ticket] = vehP;
        pNumParked++;
        vehP->setParkingSpot(ticket + 1);
        cout << endl << "Parking Ticket" << endl << (*vehP) << endl;
    }

    void Parking::returnVehicle()
    {
        cout << "Return Vehicle" << endl;
        string temp_plate;
        char selPlate[MAX_CHAR + 1];
        cout << "Enter Licence Plate Number: ";
        getline(cin, temp_plate);
        while((int)temp_plate.length() > 8 || (int)temp_plate.length() < 1)
        {
            cout << "Invalid Licence Plate, try again: ";
            getline(cin, temp_plate);
        }
        for(int i = 0; i < (int)temp_plate.length(); i++)
                selPlate[i] = toupper(temp_plate[i]);
        selPlate[(int)temp_plate.length()] = '\0';
        for(int i = 0; i < pNumSpots; i++)
            if(pSpots[i] != nullptr && (*pSpots[i]) == selPlate)
            {
                cout << endl << "Returning: " << endl << *pSpots[i] << endl;
                delete pSpots[i];
                pSpots[i] = nullptr;
                pNumParked--;
                return;
            }
        cout << "License plate " << selPlate <<  " Not found" << endl;
    }

    void Parking::listParkedVehicles()
    {
        cout << "*** List of parked vehicles ***" << endl;
        for(int i = 0; i < pNumSpots; i++)
            if(pSpots[i] != nullptr )
            {
                cout << (*pSpots[i]);
                cout<< "-------------------------------" << endl;
            }
    }

    bool Parking::closeParking()
    {
        if(pNumParked == 0)
        {
            cout << "Closing Parking" << endl;
            return true;
        }
        cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
        cout << "Are you sure? (Y)es/(N)o: ";
        string s;
        getline(cin, s);
        while (s != "Y" && s != "y" && s != "N" && s != "n") 
        {
		    cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
		    getline(cin, s);
		}
        if(s == "N" || s == "n")
        {
            cout << "Aborted!" << endl;
            return false;
        }
        cout << "Closing Parking" << endl;
        for(int i = 0; i < pNumSpots; i++)
            if(pSpots[i] != nullptr )
            {
                cout << endl << "Towing request" << endl;
                cout << "*********************" << endl;
                cout << (*pSpots[i]);
                delete pSpots[i];
                pSpots[i] = nullptr;
                pNumParked--;
            }
        return true;
    }

    bool Parking::exitParkingApp()
    {
        cout << "This will terminate the program!" << endl;
        cout << "Are you sure? (Y)es/(N)o: ";
        string ans;
        getline(cin, ans);
        while (ans != "y" && ans != "n" && ans != "Y" && ans != "N")
        {
            cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
            getline(cin, ans);
        }
        if(ans == "y" || ans == "Y")
        {
            cout<<"Exiting program!"<<endl;
            return true;
        }
        else
            return false;
    }

    bool Parking::loadData()
    {
        if(isEmpty())
            return true;
        bool state = true;
        ifstream f(pData);
        if(!f.is_open())
            return true;
        while (state && pNumParked < pNumSpots) 
        {
            Vehicle* vehP = nullptr;
            char vehType = '\0';
            f >> vehType;
            if(vehType == '\0')
                break;
            if (vehType == 'C')
                vehP = new Car();
            else
                vehP = new Motorcycle();
            f.ignore(1, ',');
            vehP->setCsv(true);
            vehP->read(f);
            if(!f)
            {
                delete vehP;
                vehP = nullptr;
                state = false;
            }
            else
            {
                vehP->setCsv(false);
                pSpots[vehP->getParkingSpot() - 1] = vehP;
                pNumParked++;
            }
        }
        return state;
    }

    void Parking::saveData()
    {
        ofstream f(pData);
        if (f.is_open()) 
        {
            for(int i = 0; i < pNumSpots; i++)
            if(pSpots[i] != nullptr )
            {
                pSpots[i]->setCsv(true);
                pSpots[i]->write(f);
            }
        }  
    }

    int Parking::run()
    {
        while (!isEmpty())
        {
            pStatus();
            int choice = pMenu.run();
            if (choice == 1)
                parkVehicle();
            else if (choice == 2)
                returnVehicle();
            else if (choice == 3)
                listParkedVehicles();
            else if (choice == 4 && closeParking())
                break;
            else if (choice == 5 && exitParkingApp())
                break;
        }
        return isEmpty();
    }
} // namespace sdds