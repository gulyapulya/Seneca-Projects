/* Citation and Sources...
Final Project Milestone 6
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
#ifndef SDDS_PARKING_H__
#define SDDS_PARKING_H__

#include "Menu.h"
#include "Vehicle.h"

namespace sdds
{
    const int maxSpots = 100;
	class Parking
    {
        char* pData;
        Menu pMenu;
        Menu pVSMenu;
        int pNumSpots;
        Vehicle* pSpots[maxSpots];
        int pNumParked;
        Parking(const Parking&) = delete;
        Parking& operator=(const Parking&) = delete;
        bool isEmpty();
        void pStatus();
        void parkVehicle();
        void returnVehicle();
        void listParkedVehicles();
        bool closeParking();
        bool exitParkingApp();
        bool loadData();
        void saveData();
        int findSpot();
    public:
        Parking(const char*, int);
        ~Parking();
		int run();
    };

}
#endif
