//==============================================
// Name:           Baimukhambeova Gulnur
// Student Number: 100577196
// Email:          gbaimukhambetova@myseneca.ca
// Section:        NZA
// Date:           11/15/2019
//==============================================
// Assignment:     2
// Milestone:      2
//==============================================

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "contacts.h"
#include "contactHelpers.h"

void getName(struct Name* name) 
{
	printf("Please enter the contact's first name: ");
	scanf("%30[^\n]", name->firstName);
	clearKeyboard();

	printf("Do you want to enter a middle initial(s)? (y or n): ");
	if (yes())
	{
		printf("Please enter the contact's middle initial(s): ");
		scanf("%6[^\n]", name->middleInitial);
		clearKeyboard();
	}

	printf("Please enter the contact's last name: ");
	scanf("%35[^\n]", name->lastName);
	clearKeyboard();
}

void getAddress(struct Address* address) 
{
	int streetNum = 0;
	printf("Please enter the contact's street number: ");
	while (streetNum <= 0) 
	{
		streetNum = getInt();
		if (streetNum <= 0)
			printf("*** INVALID STREET NUMBER *** <must be a positive number>: ");
	}
	address->streetNumber = streetNum;

	printf("Please enter the contact's street name: ");
	scanf("%40[^\n]", address->street);
	clearKeyboard();

	printf("Do you want to enter an apartment number? (y or n): ");
	if (yes())
	{
		int apartmentNum = 0;
		printf("Please enter the contact's apartment number: ");
		while (apartmentNum <= 0) 
		{
			apartmentNum = getInt();
			if (apartmentNum <= 0)
				printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");
		}
		address->apartmentNumber = apartmentNum;
	}

	printf("Please enter the contact's postal code: ");
	scanf("%7[^\n]", address->postalCode);
	clearKeyboard();

	printf("Please enter the contact's city: ");
	scanf("%40[^\n]", address->city);
	clearKeyboard();
}

void getNumbers(struct Numbers* numbers) 
{
	printf("Please enter the contact's cell phone number: ");
	scanf("%10[^\n]", numbers->cell);
	clearKeyboard();
	

	printf("Do you want to enter a home phone number? (y or n): ");
	if (yes())
	{
		printf("Please enter the contact's home phone number: ");
		scanf("%10[^\n]", numbers->home);
		clearKeyboard();
	}

	printf("Do you want to enter a business phone number? (y or n): ");
	if (yes())
	{
		printf("Please enter the contact's business phone number: ");
		scanf("%10[^\n]", numbers->business);
		clearKeyboard();
	}
}

void getContact(struct Contact* contact) 
{
	getName(&(contact->name));
	getAddress(&(contact->address));
	getNumbers(&(contact->numbers));
}