/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.h
Version 1.0
Author Baimukhambetova Gulnur
Revision History
-----------------------------------------------------------
Date Reason
2020/03/11 Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__

#include <iostream>

namespace sdds
{
	const int MAX_NO_OF_ITEMS = 10;

	class Menu;

	class MenuItem
	{
		char* miName;
		MenuItem(const char*);
		~MenuItem();
		std::ostream& display(std::ostream & = std::cout) const;
		MenuItem(const MenuItem&) = delete;
		MenuItem& operator=(const MenuItem&) = delete;
		friend class Menu;
	};

	class Menu
	{
		char* mTitle;
		MenuItem* mItems[MAX_NO_OF_ITEMS];
		int mNumItems;
		int mIndents;
	public:
        Menu();
		Menu(const char*, int = 0);
		Menu(const Menu&);
		~Menu();
		bool isEmpty() const;
		int run() const;
		void add(const char*);
		operator bool() const;
		operator int() const;
		std::ostream& display(std::ostream & = std::cout) const;
		Menu& operator=(const Menu&);
		Menu& operator=(const char*);
		Menu& operator<<(const char*);
	};

}
#endif
