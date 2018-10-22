/************************************************************************************************************************

Name: Rosalba Monterrosas           
Date: 10/22/2018 

Description:
In this assignment a program that processes customer call records is implemented. The program reads the records in a datafile
into a dynamic array of call records, then processes each call record in the dynamic array, and prints the dynamic array of call records to 
the screen. The program is able to search, add, and remove records. Each customer call record contains nine fields, which are as follows: 
1) first name 2) last name 3) a ten digit cell phone number, 4) the number of relay stations used in making the call, 5) the length of the 
call in minutes, 6) the net cost of the call, 7) the tax rate, 8) the call tax, and 9) the total cost of the call. 
*************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
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

//Prototypes

void Initialize(call_record *& call_DB, int & count, int & size);
bool Is_empty(const int count); //inline implementation
bool Is_full(const int count, int size);//inline implementation
int Search(const call_record *call_DB, const int count, const string key);//returns location if item in listl; otherwise return -1
void Add(call_record * &call_DB, int & count, int & size, const string key); //adds item inorder to the list
void Remove(call_record *call_DB, int & count, const string key); //removes an item from the list
void Double_size(call_record * &call_DB, const int & count, int & size);
void Process(call_record *call_DB, const int & count);
void Print(const call_record *call_DB, const int & count); //prints all the elements in the list to the screen
void Destroy_call_DB(call_record * &call_DB); //de-allocates all memory allocate to call_DB by operator new.



/************************************************************************************************************************************/
//Name: Initialize
//Precondition: The variables (firstname, lastname, cell_num, relays, call_length) from the dynamic array call_record call_DB[] have not 
//been initialized.
//Postcondition: The variables (firstname, lastname, cell_num, relays, call_length) from the dynamic array call_record call_DB[] have 
//been initialized.
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
void Initialize(call_record * & call_DB, int & count, int & size)
{
	count = 0;
	ifstream in;
	in.open("callstats_data.txt");
	if (in.fail()) {
		cout << "Input file did not open correctly.\n";
		exit(1);
	}

	while (!in.eof()) {
		if (Is_full(count, size)) {
			Double_size(call_DB, count, size);
		}

		in >> call_DB[count].firstname;
		in >> call_DB[count].lastname;
		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length;

		count++;
	}
	Process(call_DB, count);
	in.close();
}

/***********************************************************************************************************************************/
//Name: Is_empty
//Precondition: The variable count is initilialized.
//Postcondition: True or false is returned based on the value of the variable count.
//Decription: Returns true if call_DB is empty.
/**********************************************************************************************************************************/

//ONE WAY TO MAKE A FUNCTION INLINE IS TO PUT THE KEYWORD "inline" in from of the 
//FUNCTION HEADER AS SHOWN BELOW:
inline bool Is_empty(const int count)
{
	return (count==0);
}

//ONE WAY TO MAKE A FUNCTION INLINE IS TO PUT THE KEYWORD "inline" in from of the 
//FUNCTION HEADER AS SHOWN BELOW:
/**********************************************************************************************************************************/
//Name: Is_full 
//Precondition: The variables count and size initilialized.
//Postcondition: True or false is returned based on whether the variables count and size have the same value.
//Decription: Returns true if call_DB is full.
/*********************************************************************************************************************************/
inline bool Is_full(const int count, int size)
{
	return (count == size);
}

/**********************************************************************************************************************************/
//Name: Search
//Precondition: The dynamic array call_record *call_DB has been initialized. The variables (count and key) have been initialized.
//Postcondition: Returns the location in the dynamic array call_record *call_DB where the variable key (value of cell_number) is located. 
//If the key cannot be found in the array, -1 is returned.
//Decription: Locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int Search(const call_record *call_DB, const int count, const string key)
{
	int i;
	for (i = 0; i < count; i++) {
		if (call_DB[i].cell_number == key)
			return i;
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: Add
//Precondition: The dynamic array call_record *call_DB has been initialized. The variables (count, size, and key) have been initialized.
//Postcondition: A record has been added to the dynamic array call_record *call_DB. The count is incremented by 1. 
//Decription: Add key to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void Add(call_record * &call_DB, int & count, int & size, const string key)
{
	if (Is_full(count, size)) {
		Double_size(call_DB, count, size);
	}

	call_DB[count].cell_number = key;
	
	cout << "Please enter first name, last name, number of relays, and call length in minutes, separated by a whitespace.\n";
	cin >> call_DB[count].firstname >> call_DB[count].lastname >> call_DB[count].relays >> call_DB[count].call_length;
	count++;
	Process(call_DB, count);
}

/********************************************************************************************************************************/
//Name: Remove
//Precondition: The dynamic array call_record *call_DB has been initialized. The variables (count and key) have been initialized.
//Postcondition: A record has been removed from the dynamic array call_record *call_DB. The count is decremented by 1.
//Decription: Remove key from call_DB if it is there.
/*******************************************************************************************************************************/
void Remove(call_record *call_DB, int & count, const string key)
{
	int i;
	int location;

	if (Is_empty(count)) {
		cout << "There are zero records. You cannot remove any records.\n";
		exit(1);
	}

	do {
		location = Search(call_DB, count, key);

		if (location != -1) {
			for (i = location; i < count - 1; i++) {
				call_DB[i] = call_DB[i + 1];
			}
			count--;
		}
	} while (location != -1);
}

/******************************************************************************************************************************/
//Name: Double_Size
//Precondition: The dynamic array call_record *call_DB has been initialized. The variables (count, size, and key) have been initialized.
//Postcondition: The size of the dynamic array call_record *call_DB has been doubled.
//Decription: Doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void Double_size(call_record * &call_DB, const int & count, int & size)
{
	int i;
	size *= 2;
	call_record *temp = new call_record[size];
	for (i = 0; i < count; i++) {
		temp[i] = call_DB[i];
	}
	delete [] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: Process
//Precondition: The variables (double & net_cost, double & call_tax, double & total_cost, double & tax_rate) from 
//the dynamic array call_record call_DB[] have not been initialized.
//Postcondition: The variables (double & net_cost, double & call_tax, double & total_cost, double & tax_rate) from 
//the dynamic array call_record call_DB[] have been initialized.
//Decription: Calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void Process(call_record *call_DB, const int & count)
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
//Name: Print
//Precondition: The variables (firstname, lastname, cell_num, relays, call_length, net_cost, call_tax, total_cost, tax_rate) from 
//the dynamic array call_record call_DB[] have been initialized.
//Postcondition: The variables (firstname, lastname, cell_num, relays, call_length, net_cost, call_tax, total_cost, tax_rate) from 
//the dynamic array call_record call_DB[] have been printed to the screen.
//Decription: Prints every field of every call_record in call_DB formatted to the screen.
/***************************************************************************************************************************/
void Print(const call_record *call_DB, const int & count)
{
	int i;
	string name;
	
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);

	for (i = 0; i < count; i++) {
		name = call_DB[i].firstname + " " + call_DB[i].lastname;
		
		cout.width(19);
		cout << std::left << name;
		cout << call_DB[i].cell_number << "\t";
		cout << call_DB[i].relays << "\t";
		cout << call_DB[i].call_length << "\t";
		cout << call_DB[i].net_cost << "\t";
		cout << call_DB[i].tax_rate << "\t";
		cout << call_DB[i].call_tax << "\t";
		cout << call_DB[i].total_cost << endl;
	}
}

/****************************************************************************************************************************/
//Name: Destroy_call_DB
//Precondition: The dynamic array call_record *call_DB has been initialized.
//Postcondition: The memory allocated to call_DB has been de-allocated.
//Decription: De-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//is exited.
/***************************************************************************************************************************/
void Destroy_call_DB(call_record * &call_DB)
{
	delete [] call_DB;
	call_DB = nullptr;
}

//Driver to test the program

int main()
{
	int size = 5; //total amount of memory (cells) allocated for the dynamic array of call records
	int count = 0;
	call_record *call_DB = new call_record[size];

	//put code here to test your funcitons
	//*************TEST#1---TESTING Is_empty********/
	cout << "TEST1:  ***********************************************\n\n";
	cout << "Testing Is_empty on an empty call_DB\n\n";
	if (Is_empty(count))
		cout << "call_DB is empty -- Test#1 passed\n\n\n";
	else
		cout << "Test 0 failed -- testing for empty call_DB\n";
	cout << "\n\nFinish Testing Is_empty on an empty call_DB\n\n";
	cout << "***********************************************\n\n";
	//*************END TEST#1---TESTING IS_EMPTY********/

	//*************TEST#2---TESTING INITIALIZE, IS_FULL, DOUBLE_SIZE, PROCESS AND PRINT********/
	cout << "TEST2:  ***********************************************\n\n";
	cout << "Testing Is_full inside Initialize.  The datafile has 19 records, which are \n"
		<< "read into call_DB.  Initially, call_DB's size is 5. call_DB size will be doubled \n"
		<< "twice inside Initialize. on an empty call_DB.  Once, Initialize is finish executing\n"
		<< "call_DB is printed.  If 19 records are printed and processed TEST#2 was passed. While testing \n"
		<< "Initialize, process and print are also tested...\n\n";
	Initialize(call_DB, count, size);
	Print(call_DB, count);
	cout << "\n\nFinish Testing Initialize, Is_full, Double_size, Process, and Print  \n\n";
	cout << "*********************************************************\n\n";
	//*************END TEST#2---TESTING INITIALIZE, IS_FULL, DOUBLE_SIZE, PROCESS AND PRINT********/

	//*************TEST#3---TESTING ADD, IS_FULL, PROCESS, and PRINT********/
	cout << "TEST3:  ***********************************************\n\n";
	cout << "Testing Is_full inside Add.  The call_DB has 19 records.  We will add 2 records.  call_DB should \n"
		<< "become full and Double_size should be called.  The new size should 40 call_records - increase from 20 \n"
		<< "count should be 21 \n"
		<< "    \n"
		<< " ...\n\n";
	string key = "9544567891";
	//prompt user for first and last names, relays, and minutes inside Add.  cell_number is stored in key 
	//call_DB[...].cell_number = key
	Add(call_DB, count, size, key);

	key = "5618886767";
	//prompt user for first and last names, relays, and minutes inside Add.  cell_number is stored in key 
	//call_DB[...].cell_number = key
	Add(call_DB, count, size, key);
	Print(call_DB, count);
	cout << "\n\nFinish Testing Add, Is_full, Double_size, Process, and Print  \n\n";
	cout << "*********************************************************\n\n";
	//*************TEST#3---TESTING ADD, IS_FULL, DOUBLE_SIZE, PROCESS AND PRINT************/

	//*************TEST#4---TESTING SEARCH, IS_EMPTY, REMOVE and PRINT********/
	cout << "TEST4:  ***********************************************\n\n";
	cout << "Testing Search, and Print inside Remove.  Must check to see if call_DB empty before attempting to\n"
		<< "to remove. The call_DB has 21 records.  We will remove 3 records from call_DB \n"
		<< "in the following order: call_DB[0] cell number is 9546321555, \n"
		<< "call_DB[count-1] cell number is 5617278899 and call_DB[10] cell number is 9546321555   \n";
	key = "9546321555";
	Remove(call_DB, count, key);
	key = "5617278899";
	Remove(call_DB, count, key);
	key = "9546321555";
	Remove(call_DB, count, key);
	Print(call_DB, count);
	cout << "\n\nFinish Testing Remove and Print  \n\n";
	cout << "*********************************************************\n\n";
	//*************TEST#4---TESTING TESTING SEARCH, IS_EMPTY, REMOVE and PRINT********/

	//*************TEST#5---Destroy_call_DB********/
	cout << "TEST5:  ***********************************************\n\n";
	cout << "Testing Destroy_call_DB\n\n";
	cout << "//De-allocates all memory allocated to call_DB by operator new, and sets call_DB to null.\n\n";
	Destroy_call_DB(call_DB);
	if (call_DB == 0)
	{
		cout << "Test5 was passed\n";
	}
	else
	{
		cout << "Test5 failed\n";
	}
	cout << "\n\nFinish Testing Destroy_call_DB\n\n";
	cout << "***********************************************\n\n";
	//*************END TEST#5---TESTING Destroy_call_DB********/

	Destroy_call_DB(call_DB);
	return 0;
}


