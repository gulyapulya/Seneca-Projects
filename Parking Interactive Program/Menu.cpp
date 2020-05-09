/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include "Menu.h"

using namespace std;

namespace sdds
{
    Menu::Menu()
    {
        mTitle = nullptr;
		mIndents = 0;
		mNumItems = 0;
		for (int i = 0; i < MAX_NO_OF_ITEMS; i++)
			mItems[i] = nullptr;
    }

	Menu::Menu(const char* title, int indent)
	{
		mTitle = nullptr;
		mIndents = indent;
		mNumItems = 0;
		*this = title;
		for (int i = 0; i < MAX_NO_OF_ITEMS; i++)
			mItems[i] = nullptr;
	}

	Menu::Menu(const Menu& pMenu)
	{
		mNumItems = 0;
		mIndents = pMenu.mIndents;
		for (int i = 0; i < MAX_NO_OF_ITEMS; i++)
		{
			mItems[i] = nullptr;
			if (pMenu.mItems[i] != nullptr)
				add(pMenu.mItems[i]->miName);
		}
		mTitle = nullptr;
		*this = pMenu.mTitle;
	}

	Menu::~Menu()
	{
		delete[] mTitle;
		for (int i = 0; i < MAX_NO_OF_ITEMS; i++)
			delete mItems[i];
	}

	bool Menu::isEmpty() const
	{
		return !*this;
	}

	ostream& Menu::display(ostream& os) const
	{
		if (isEmpty())
			os << "Invalid Menu!" << endl;
		else if (mNumItems == 0)
		{
			os << string(mIndents * 4, ' ');
			os << mTitle << endl;
			os << "No Items to display!" << endl;
		}
		else
		{
			os << string(mIndents * 4, ' ');
			os << mTitle << endl;
			for (int i = 0; i < mNumItems; i++)
			{
				os << string(mIndents * 4, ' ');
				os << (i + 1) << "- ";
				mItems[i]->display(os);
			}
			os << string(mIndents * 4, ' ');
			os << "> ";
		}
		return os;
	}

	void Menu::add(const char* name)
	{
		if (name == nullptr)
		{
			delete[] mTitle;
			mTitle = nullptr;
		}
		else if (mNumItems < MAX_NO_OF_ITEMS)
		{
			mItems[mNumItems] = new MenuItem(name);
			mNumItems++;
		}
	}

	int Menu::run() const
	{
		display();
		if (mNumItems == 0 || isEmpty())
			return 0;
		int inp;
		while (true)
		{
			cin >> inp;
			int check = cin.fail();
			cin.clear();
			cin.ignore(1000, '\n');
			if (check)
				cout << "Invalid Integer, try again: ";
			else if (inp > mNumItems || inp <= 0)
				cout << "Invalid selection, try again: ";
			else break;
		}
		return inp;
	}

	Menu::operator bool() const
	{
		return mTitle != nullptr;
	}

	Menu::operator int() const
	{
		return run();
	}

	Menu& Menu::operator=(const Menu& pMenu)
	{
		if (this != &pMenu)
		{
			for (int i = 0; i < mNumItems; i++)
			{
				delete mItems[i];
				mItems[i] = nullptr;
			}
			mNumItems = 0;
			mIndents = pMenu.mIndents;
			*this = pMenu.mTitle;
			for (int i = 0; i < pMenu.mNumItems; i++)
				add(pMenu.mItems[i]->miName);
		}
		return *this;
	}

	Menu& Menu::operator=(const char* title)
	{
		delete[] mTitle;
		mTitle = nullptr;
		if (title != nullptr && strlen(title) != 0)
		{
			mTitle = new char[strlen(title) + 1];
			strcpy(mTitle, title);
		}
		return *this;
	}

	Menu& Menu::operator<<(const char* name)
	{
		add(name);
		return *this;
	}

	MenuItem::MenuItem(const char* name)
	{
		if (name == nullptr)
			miName = nullptr;
		else
		{
			miName = new char[strlen(name) + 1];
			strcpy(miName, name);
		}
	}

	MenuItem::~MenuItem()
	{
		delete[] miName;
	}

	ostream& MenuItem::display(ostream& os) const
	{
		if (miName != nullptr)
			os << miName<<endl;
		return os;
	}
}
