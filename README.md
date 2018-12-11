# call-stats
This program, developed in C++, processes customer call records. The program reads the records in the datafile "callstats_data.txt" into a dynamic array of call records which is managed by a class, then processes each call record in the dynamic array, and prints the dynamic array of call records to the screen. 

The main program contains different test cases that are able to search, add, and remove records from the dynamic array of call records. 

Each customer call record contains nine fields, which are as follows:
1)  first name 
2) last name 
3) a ten digit cell phone number 
4) the number of relay stations used in making the call
5) the length of the call in minutes
6) the net cost of the call
7) the tax rate
8) the call tax
9) the total cost of the call

The file "call_class.h" contains the class call_class declaration, the file "call_class.cpp" contains the class implementation,
and the file "call_stats8.cpp" contains the driver of the program.
