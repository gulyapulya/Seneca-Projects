#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <mysql.h> 

using namespace std;

struct Employee
{
	int employeeNumber;
	char lastName[50];
	char firstName[50];
	char email[100];
	char phone[50];
	char extension[10];
	char reportsTo[100];
	char jobTitle[50];
	char city[50];
};

void displayAllEmployees(MYSQL* conn)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	ostringstream allEmps;
	allEmps << "select employees.employeeNumber, concat(employees.firstName, ' ', employees.lastName) as employee_name, employees.email, offices.phone, employees.extension, concat(man.lastName, ' ', man.firstName) as reportsTo from employees employees inner join employees man on employees.reportsTo = man.employeeNumber left join offices on employees.officeCode = offices.officeCode;";
	int exequery = mysql_query(conn, allEmps.str().c_str());
	if (!exequery)
	{
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		if (row == nullptr)
			cout << "There is no employee information to show." << endl;
		else
		{
			cout << endl;
			cout << "E" << '\t' << setw(25) << left << "Employee name" << setw(36) << left << "Email" << setw(20) << left << "Phone" << setw(10) << left << "Ext" << "Manager" << endl << endl;
			for (int i = 0; i < 106; i++)
				cout << "-";
			cout << endl;
			while (row = mysql_fetch_row(res))
			{
				cout << endl << row[0] << '\t';
				cout << setw(25) << left << row[1];
				cout << left << setw(36) << row[2];
				cout << setw(20) << left << row[3];
				cout << setw(10) << left << row[4];
				cout << row[5];
				cout << endl;
			}
		}
	}
	else
		cout << "Error message: " << mysql_error(conn) << ": " << mysql_errno(conn) << endl;
}

int findEmployee(MYSQL* conn, int employeeNumber, struct Employee* emp) 
{
	MYSQL_ROW row;
	MYSQL_RES* res;

	char tempReport[100] = "";
	int final = 0;

	string query = "select distinct e1.employeeNumber, e1.lastName, e1.firstName, e1.email, phone, e1.extension, concat(e2.firstName,' ', e2.lastname) as reportsTo, e1.jobTitle, city from employees as e1 inner join offices as o on e1.officeCode = o.officeCode left join employees as e2 on e1.reportsTo = e2.employeeNumber where e1.employeeNumber =";
	query.append(to_string(employeeNumber));
	query.append(";");
	const char* q = query.c_str();

	if (!mysql_query(conn, q))
	{
		res = mysql_store_result(conn);
		if (res == nullptr)
			final = 0;
		while (row = mysql_fetch_row(res))
		{
			emp->employeeNumber = stoi(row[0]);
			strcpy(emp->lastName, row[1]);
			strcpy(emp->firstName, row[2]);
			strcpy(emp->email, row[3]);
			strcpy(emp->phone, row[4]);
			strcpy(emp->extension, row[5]);

			if (row[6] == nullptr)
			{
				tempReport[0] = '\0';
			}
			else
			{
				strcpy(tempReport, row[6]);
			}
			strcpy(emp->reportsTo, tempReport);
			strcpy(emp->jobTitle, row[7]);
			strcpy(emp->city, row[8]);
			final = 1;
		}
	}
	else
	{
		cout << "Error message: " << mysql_error(conn) << ":" << mysql_errno(conn) << endl;
	}

	return final;
}

void deleteEmployee(MYSQL* conn, int employeeNumber)
{
	struct Employee emp;
	if (findEmployee(conn, employeeNumber, &emp) == 1)
	{
		ostringstream deleteEmp;
		deleteEmp << "delete from employees where employeeNumber =" << employeeNumber;
		int exequery = mysql_query(conn, deleteEmp.str().c_str());
		if (!exequery)
			cout << "Everythin worked correctly. The employee " << employeeNumber << " was successfully deleted" << endl;
		else
			cout << "Error message: " << mysql_error(conn) << ": " << mysql_errno(conn) << endl;
	}
	else
		cout << endl << "An employee with the same employee number does not exist." << endl;
}

void updateEmployee(MYSQL* conn, int employeeNumber)
{
	struct Employee emp;
	if (findEmployee(conn, employeeNumber, &emp) == 1)
	{
		string extension;
		ostringstream updateEmp;
		cout << "Please put the new extension" << employeeNumber << ": ";
		cin >> extension;
		updateEmp << "update employees set extension =\"" << extension << "\" where employeeNumber =" << employeeNumber;
		int exequery = mysql_query(conn, updateEmp.str().c_str());
		if (!exequery)
			cout << endl << "Everythin worked correctly. The info of employee " << employeeNumber << " was updated" << endl;
		else
			cout << "Error message: " << mysql_error(conn) << ": " << mysql_errno(conn) << endl;
	}
	else
		cout << "An employee with the same employee number does not exist." << endl;
}

void insertEmployee(MYSQL* conn, struct Employee emp)
{
	if (findEmployee(conn, emp.employeeNumber, &emp) == 1)
		cout << "An employee with the same employee number exists." << endl;
	else
	{
		ostringstream insert_employee;
		int officeCode = 1;
		string reportsTo = "1002";
		cout << "Please put the last name: ";
		cin >> emp.lastName;
		cout << "Please put the first name: ";
		cin >> emp.firstName;
		cout << "Please put the extension: ";
		cin >> emp.extension;
		cout << "Please put the email: ";
		cin >> emp.email;
		cout << "Please put the job tilte: ";
		cin >> emp.jobTitle;
		cout << "Please put the city: ";
		cin >> emp.city;
		if (strcmp(emp.city, "San Francisco") == 0 or strcmp(emp.city, "SAN FRANCISCO") == 0 or strcmp(emp.city, "SanFrancisco") == 0 or strcmp(emp.city, "san francisco") == 0)
			officeCode = 1;
		else if (strcmp(emp.city, "Paris") == 0 or strcmp(emp.city, "PARIS") == 0 or strcmp(emp.city, "paris") == 0)
			officeCode = 4;
		else if (strcmp(emp.city, "Boston") == 0 or strcmp(emp.city, "BOSTON") == 0 or strcmp(emp.city, "boston") == 0)
			officeCode = 2;
		else if (strcmp(emp.city, "Sydney") == 0 or strcmp(emp.city, "SYDNEY") == 0 or strcmp(emp.city, "sydney") == 0)
			officeCode = 6;
		else if (strcmp(emp.city, "Tokyo") == 0 or strcmp(emp.city, "TOKYO") == 0 or strcmp(emp.city, "tokyo") == 0)
			officeCode = 5;
		else if (strcmp(emp.city, "LONDON") == 0 or strcmp(emp.city, "London") == 0 or strcmp(emp.city, "london") == 0)
			officeCode = 7;
		else if (strcmp(emp.city, "NYC") == 0 or strcmp(emp.city, "New York") == 0 or strcmp(emp.city, "NewYork") == 0 or strcmp(emp.city, "new york") == 0)
			officeCode = 3;
		else
			officeCode = 1;
		insert_employee << "insert into employees values(" << emp.employeeNumber << ", \"" << emp.lastName << "\", \"" << emp.firstName << "\", \"" << emp.extension << "\", \"" << emp.email << "\", \"" << officeCode << "\"," << reportsTo << ", \"" << emp.jobTitle << "\");";
		int exequery = mysql_query(conn, insert_employee.str().c_str());
		if (!exequery)
			cout << endl << "Everythin worked correctly. Employee is added." << endl;
		else
			cout << "Error message: " << mysql_error(conn) << ": " << mysql_errno(conn) << endl;
	}
}



void displayEmployee(MYSQL* conn, struct Employee emp)
{
	int eNumber;
	cout << endl << "Please put the emp number: ";
	cin >> eNumber;
	int result = findEmployee(conn, eNumber, &emp);
	if (result == 0)
		cout << endl << "Employee number" << eNumber << " is not valid" << endl;
	else
	{
		cout << "employeeNumber = " << emp.employeeNumber << endl <<
			"lastName = " << emp.lastName << endl << "firstName = " << emp.firstName << endl << "email = " << emp.email << endl <<
			"phone = " << emp.phone << endl << "extension = " << emp.extension << endl << "reportsTo = " << emp.reportsTo << endl <<
			"jobTitle = " << emp.jobTitle << endl << "city = " << emp.city << endl;
	}
}

int menu()
{
	int selected;
	cout << endl << "********************* HR Menu *********************\n";
	cout << "1) Find Employee\n";
	cout << "2) Employees Report\n";
	cout << "3) Add Employee\n";
	cout << "4) Update Employee\n";
	cout << "5) Remove Employee\n";
	cout << "0) Exit\n";
	cout << "Select option: ";
	cin >> selected;
	while (selected > 5 or selected < 0)
	{
		cout << endl << "Option is wrong. Please try again: ";
		cin >> selected;
	}
	return selected;
}


int main(void)
{
	Employee emp_obj{};
	MYSQL* conn;
	int option;
	int emp_number;
	bool exit = false;
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "*username*", "*password*", "db_gbaimukhambetova", 3306, nullptr, 0);
	if (conn)
	{
		while (exit == false)
		{
			option = menu();
			if (option == 1)
				displayEmployee(conn, emp_obj);
			else if (option == 2)
				displayAllEmployees(conn);
			else if (option == 3)
			{
				cout << endl << "Please put the employee number: ";
				cin >> emp_obj.employeeNumber;
				insertEmployee(conn, emp_obj);
			}
			else if (option == 4)
			{
				cout << endl << "Please put the employee number: ";
				cin >> emp_number;
				updateEmployee(conn, emp_number);
			}
			else if (option == 5)
			{
				cout << endl << "Please put the employee number: ";
				cin >> emp_number;
				deleteEmployee(conn, emp_number);
			}
			else
				exit = true;
		}
		cout << "Program is closed!" << endl;
	}
	else
		cout << "Connection did not work" << mysql_error(conn) << endl;
	mysql_close(conn);
}
