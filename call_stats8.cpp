/************************************************************************************************************************

Name: Rosalba Monterrosas             
Date: 11/29/2018           

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

//driver to test the functionality of your class.
int main()
{
	cout << "TEST1: Testing the Default Constructor, is_full and double_size\n";
	call_class MyClass;
	cout << "Finish TEST1: testing the default constructor\n\n\n\n";

	cout << "Test2: Testing add, double_size, process, and is_full() \n";
	MyClass.add();
	cout << "Finish TEST2\n\n\n\n";

	cout << "Test3: Testing operator-, serach, and is_empty\n";
	MyClass - "5617278899" - "9546321555" - "1234567890";
	cout << "Finish TEST3\n\n\n\n";

	cout << "Test4: Testing operator<<\n\n";
	cout << MyClass << endl;
	cout << "Finish TEST4\n\n\n\n";

	cout << "Test5: Testing copy constructor\n\n";
	call_class YourClass = MyClass;
	cout << YourClass << endl;
	cout << "Finish TEST5\n\n\n\n";

	cout << "The destructor will be called automatically\n";

	return 0;
}

