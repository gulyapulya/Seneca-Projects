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
#include "contactHelpers.h"

void clearKeyboard(void)
{
    while (getchar() != '\n')   ; // empty execution code block on purpose
}

void pause(void) 
{
	printf("(Press Enter to Continue)");
	clearKeyboard(); 
}

int getInt(void)
{
	char NL = 'x';
	int Value;
	while (NL != '\n') 
	{
		scanf("%d%c", &Value, &NL);
		if (NL != '\n')
		{
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		}
	}
	return Value;
}

int getIntInRange(int min, int max)
{
	int Value = max + 1;
	while (max < Value || Value < min)
	{
		Value = getInt();
		if (max < Value || Value < min)
			printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
	} 
	return Value;
}

int yes(void)
{
	char NL = 'x', Value;
	while (NL != '\n')
	{
		scanf("%c%c", &Value, &NL);
		if (NL != '\n')
		{
			clearKeyboard();
			printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		}
		else if (Value != 'y' && Value != 'Y' && Value != 'n' && Value != 'N')
		{
			NL = 'x';
			clearKeyboard();
			printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		}
	}
	if (Value == 'y' || Value == 'Y')
		return 1;
	else
		return 0;
}

int menu(void)
{
	int Value;
	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n");
	printf("\n");
	printf("Select an option:> ");
	Value = getIntInRange(0, 6);
	printf("\n");
	return Value;
}

void contactManagerSystem(void)
{
	int Value = 1;
	while (1 <= Value && Value <= 6)
	{
		Value = menu();
		if (1 <= Value && Value <= 6)
		{
			printf("<<< Feature %d is unavailable >>>\n\n", Value);
			pause();
			printf("\n");
		}
		else
		{
			printf("Exit the program? (Y)es/(N)o: ");
			if (!yes())
				Value = 1;
			printf("\n");
		}
	}
	printf("Contact Management System: terminated\n");
}