/************************************************************************************************************************

Name: Rosalba Monterrosas            
Due Date: 11/29/2018          

Description:
This program processes customer call records. The program reads the records in a datafile
into a dynamic array of call records which is managed by a class, then processes each call record in the dynamic array, and
prints the dynamic array of call records to the screen. The program is able to search, add, and remove records. Each customer
call record contains nine fields, which are as follows: 1) first name 2) last name 3) a ten digit cell phone number,
4) the number of relay stations used in making the call, 5) the length of the call in minutes, 6) the net cost of the call,
7) the tax rate, 8) the call tax, and 9) the total cost of the call.

The file "call_class.h" contains the class call_class declaration, the file "call_class.cpp" contains the class implementation,
and the file "call_stats8.cpp" is the driver of the program.
*************************************************************************************************************************/

#include "call_class.h"

/************************************************************************************************************************************/
//Name: default constructor
//Precondition: The variables (firstname, lastname, cell_number, relays, call_length) from the dynamic array call_record call_DB[] in 
//class call_class have not been initialized.
//Postcondition: The variables (firstname, lastname, cell_number, relays, call_length) from the dynamic array call_record call_DB[] in 
//class call_class have been initialized.
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	count = 0;
	size = 5;
	call_DB = new call_record[size];
	ifstream in;
	in.open("callstats_data.txt");
	if (in.fail()) {
		cout << "Input file did not open correctly.\n";
		exit(1);
	}

	while (!in.eof()) {
		if (is_full()) {
			double_size();
		}

		in >> call_DB[count].firstname;
		in >> call_DB[count].lastname;
		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length;

		count++;
	}
	process();
	in.close();
}

/************************************************************************************************************************************/
//Name: copy constructor
//Precondition: The object const call_class & Org has been initialized. 
//Postcondition: An independent copy of the object const call_class & Org is made to the current object. The objects involved will 
//have their own copy of dynamic memory.
//Decription: Performs a deep copy.
/************************************************************************************************************************************/
call_class::call_class(const call_class & Org)
{
	int i;

	count = Org.count;
	size = Org.size;
	delete[] call_DB;
	call_DB = new call_record[size];
	for (i = 0; i < count; i++) {
		call_DB[i] = Org.call_DB[i];
	}
}

/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: The variable count in class call_class is initilialized.
//Postcondition: True or false is returned based on the value of the variable count in class call_class.
//Decription: Returns true if call_DB is empty.
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return (count == 0);
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: The variables count and size in class call_class are initilialized.
//Postcondition: True or false is returned based on whether the variables count and size in class call_class have the same value.
//Decription: Returns true if call_DB is full.
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	return (count == size);
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: The dynamic array call_record *call_DB in class call_class has been initialized. The variable count 
//in class call_class and the variable key have been initialized.
//Postcondition: Returns the location in the dynamic array call_record *call_DB in class call_class where the variable key 
//(value of cell_number) is located. 
//Decription: Locates key in call_DB if it is there; otherwise -1 is returned.
/*********************************************************************************************************************************/
int call_class::search(const string key)
{
	int i;
	for (i = 0; i < count; i++) {
		if (call_DB[i].cell_number == key)
			return i;
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: The dynamic array call_record *call_DB in class call_class has been initialized. The variables (count, size) 
//in class call_class have been initialized.
//Postcondition: A record has been added to the dynamic array call_record *call_DB in class call_class. The count is incremented by 1.
//Decription: Adds a call_record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB. The user 
//is prompted to enter the firstname, lastname, cell number, relays and call length. 
/********************************************************************************************************************************/
void call_class::add()
{
	if (is_full()) {
		double_size();
	}

	cout << "Please enter first name, last name, cell  number, number of relays, and call length in minutes, separated by a whitespace.\n";
	cin >> call_DB[count].firstname >> call_DB[count].lastname >> call_DB[count].cell_number >> call_DB[count].relays >> call_DB[count].call_length;
	count++;
	process();
}

/********************************************************************************************************************************/
//Name: operator -
//Precondition: The dynamic array call_record *call_DB in class call_class has been initialized. The variable count in 
//class call_class and the variable key have been initialized.
//Postcondition: A record has been removed from the dynamic array call_record *call_DB in class call_class. The count is decremented by 1.
//Decription: overload operator “-“ as a member function of call_class with chaining. Remove key from call_DB if it is there.
/*******************************************************************************************************************************/
call_class & call_class::operator -(const string key)
{
	int i;
	int location;

	if (is_empty()) {
		cout << "There are zero records. You cannot remove any records.\n";
		exit(1);
	}

	do {
		location = search(key);

		if (location != -1) {
			for (i = location; i < count - 1; i++) {
				call_DB[i] = call_DB[i + 1];
			}
			count--;
		}
	} while (location != -1);
	return *this;
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: The dynamic array call_record *call_DB in class call_class has been initialized. The variables (count, size)
//in class call_class have been initialized.
//Postcondition: The size of the dynamic array call_record *call_DB in class call_class has been doubled.
//Decription: Doubles the size (capacity) of call_DB.
/******************************************************************************************************************************/
void call_class::double_size()
{
	int i;
	size *= 2;
	call_record *temp = new call_record[size];

	for (i = 0; i < count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: The variables (double & net_cost, double & call_tax, double & total_cost, double & tax_rate) from 
//the dynamic array call_record call_DB[] in class call_class have not been initialized.
//Postcondition: The variables (double & net_cost, double & call_tax, double & total_cost, double & tax_rate) from 
//the dynamic array call_record call_DB[] in class call_class have been initialized.
//Decription: Calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	int i;

	for (i = 0; i < count; i++) {
		call_DB[i].net_cost = (call_DB[i].relays / 50.0 * 0.40 * call_DB[i].call_length);

		if ((call_DB[i].relays >= 0) && (call_DB[i].relays <= 5))
			call_DB[i].tax_rate = 0.01;
		else if ((call_DB[i].relays >= 6) && (call_DB[i].relays <= 11))
			call_DB[i].tax_rate = 0.03;
		else if ((call_DB[i].relays >= 12) && (call_DB[i].relays <= 20))
			call_DB[i].tax_rate = 0.05;
		else if ((call_DB[i].relays >= 21) && (call_DB[i].relays <= 50))
			call_DB[i].tax_rate = 0.08;
		else
			call_DB[i].tax_rate = 0.12;

		call_DB[i].call_tax = call_DB[i].net_cost * call_DB[i].tax_rate;

		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
	}
}


/****************************************************************************************************************************/
//Name: operator <<
//Precondition: The variables (firstname, lastname, cell_num, relays, call_length, net_cost, call_tax, total_cost, tax_rate) from 
//the dynamic array call_record call_DB[] in class call_class have been initialized.
//Postcondition: The variables (firstname, lastname, cell_num, relays, call_length, net_cost, call_tax, total_cost, tax_rate) from 
//the dynamic array call_record call_DB[] in class call_class have been printed to the screen.
//Decription:Overloading operator << as a friend function. Prints every field of every call_record in call_DB formatted to the screen.
/***************************************************************************************************************************/
ostream & operator <<(ostream & out, const call_class & Org)
{
	int i;
	string name;

	out.setf(ios::showpoint);
	out.precision(2);
	out.setf(ios::fixed);

	for (i = 0; i < Org.count; i++) {
		name = Org.call_DB[i].firstname + " " + Org.call_DB[i].lastname;

		out.width(19);
		out << std::left << name;
		out << Org.call_DB[i].cell_number << "\t";
		out << Org.call_DB[i].relays << "\t";
		out << Org.call_DB[i].call_length << "\t";
		out << Org.call_DB[i].net_cost << "\t";
		out << Org.call_DB[i].tax_rate << "\t";
		out << Org.call_DB[i].call_tax << "\t";
		out << Org.call_DB[i].total_cost << endl;
	}
	return out;
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition: The dynamic array call_record *call_DB in class call_class has been initialized.
//Postcondition: The memory allocated to call_DB in class call_class has been de-allocated.
//Decription: De-allocates all memory allocated to call_DB in class call_class. This should be the last function to be called
//before the program is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	delete[] call_DB;
	call_DB = nullptr;
	//	cout << "Message inside destructor.\n";
}
