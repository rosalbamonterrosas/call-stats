/************************************************************************************************************************

Name: Rosalba Monterrosas             Z#: 23361820
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 11/29/2018           Due Time: 11:59pm
Total Points: 100
Assignment #11: call_stats8.cpp

Description:
In this assignment a program that processes customer call records is implemented. The program reads the records in a datafile
into a dynamic array of call records which is managed by a class, then processes each call record in the dynamic array, and
prints the dynamic array of call records to the screen. The program is able to search, add, and remove records. Each customer
call record contains nine fields, which are as follows: 1) first name 2) last name 3) a ten digit cell phone number,
4) the number of relay stations used in making the call, 5) the length of the call in minutes, 6) the net cost of the call,
7) the tax rate, 8) the call tax, and 9) the total cost of the call.

The file "call_class.h" contains the class call_class declaration, the file "call_class.cpp" contains the class implementation,
and the file "call_stats8.cpp" is the driver of the program.
*************************************************************************************************************************/

#ifndef CALL_CLASS_H
#define CALL_CLASS_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class call_record
{
public:
	string firstname;
	string lastname;
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};

class call_class
{
public:
	call_class();
	call_class(const call_class & Org);
	~call_class(); //de-allocates all memory allocate to call_DB by operator new.
	bool is_empty(); //inline implementation
	bool is_full();//inline implementation
	int search(const string key);//returns location if item in listl; otherwise return -1
	void add(); //adds a call record to call_DB
	call_class & operator -(const string key); //removes an item from the list
	void double_size();
	void process();
	friend ostream & operator <<(ostream & out, const call_class & Org); //prints all the elements in the list to the screen
private:
	int count;
	int size;
	call_record *call_DB;
};

#endif CALL_CLASS_H