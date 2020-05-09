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

struct Name {
    char firstName[31];
    char middleInitial[7];
    char lastName[36];
};

struct Address
{
	int streetNumber;
	char street[41];
	int apartmentNumber;
	char postalCode[8];
	char city[41];
};

struct Numbers
{
	char cell[11];
	char home[11];
	char business[11];
};

struct Contact
{
	struct Name name;
	struct Address address;
	struct Numbers numbers;
};

void getName(struct Name* name);
void getAddress(struct Address* address);
void getNumbers(struct Numbers* numbers);
void getContact(struct Contact* contact);