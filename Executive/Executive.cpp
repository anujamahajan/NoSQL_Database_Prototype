//////////////////////////////////////////////////////////////////////////
//  Executive.cpp - Registers tests and executes it                     //
//  ver 1.0                                                             //                                                             //
//  Language:      Visual C++ 11                                        // 
//  Application:   Prototype for NoSQL database CSE687 Pr1, SP18        //
//  Author:        Anuja Mahajan, Syracuse University(MSCS-Spring 2018) //
//				   apmahaja@syr.edu                                     //     
//////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package executes all the test cases

* Required Files:
* ---------------
* Test.h, TestUtilities.h, DateTime.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 04 Feb 2018
* - first release
*/
#include <iostream>
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include "../Test/Test.h"

#ifdef TEST_EXECUTIVE

int main()
{
	Utilities::Title("Testing NoSQL Database");
	TestExecutive ex;
	 //define test structures with test function and message
	TestExecutive::TestStr ts1{ testR1, "Use C++11" };
	TestExecutive::TestStr ts2{ testR2, "Use streams and new and delete" };
	TestExecutive::TestStr ts3a{ testR3a, "Create DbElement<std::string>" };
	TestExecutive::TestStr ts3b{ testR3b, "Create DbCore<std::string>" };
	TestExecutive::TestStr tsR4b{ testR4b, "Delete key-value pair" };
	TestExecutive::TestStr tsR5a{ testR5a, "Add children" };
	TestExecutive::TestStr tsR5b{ testR5b, "Delete specific child from elements" };
	TestExecutive::TestStr tsR5c{ testR5c, "Editing text metadata" };
	TestExecutive::TestStr tsR5d{ testR5d, "Replace existing element" };
	TestExecutive::TestStr tsR6a{ testR6a, "Query- Value of the speicfied key" };
	TestExecutive::TestStr tsR6b{ testR6b, "Query-Children of the speicfied key" };
	TestExecutive::TestStr tsR6c{ testR6c, "Query-keys matching regular expression" };
	TestExecutive::TestStr tsR6d{ testR6d, "Query-metadata matching regular expression" };
	TestExecutive::TestStr tsR6e{ testR6e, "Query-Keys within specified time interval" };
	TestExecutive::TestStr tsR6f{ testR6f, "Query-Keys within date specified and current time" };
	TestExecutive::TestStr tsR7a{ testR7a, "Query-Intersection of Keys (AND)" };
	TestExecutive::TestStr tsR7b{ testR7b, "Query-Union of Keys (OR)" };
	TestExecutive::TestStr tsR8a{ testR8a, "Save database to XML file" };
	TestExecutive::TestStr tsR8b{ testR8b, "Restore database from XML file" };
	//// register test structures with TestExecutive instance, ex
	ex.registerTest(ts1);
	ex.registerTest(ts2);
	ex.registerTest(ts3a);
	ex.registerTest(ts3b);
	ex.registerTest(tsR4b);
	ex.registerTest(tsR5a);
	ex.registerTest(tsR5b);
	ex.registerTest(tsR5c);
	ex.registerTest(tsR5d);
	ex.registerTest(tsR6a);
	ex.registerTest(tsR6b);
	ex.registerTest(tsR6c);
	ex.registerTest(tsR6d);
	ex.registerTest(tsR6e);
	ex.registerTest(tsR6f);
	ex.registerTest(tsR7a);
	ex.registerTest(tsR7b);
	ex.registerTest(tsR8a);
	ex.registerTest(tsR8b);
	// run tests
	bool result = ex.doTests();
	if (result == true)
		std::cout << "\n  all tests passed";
	else
		std::cout << "\n  at least one test failed";

	std::cin.get();
	return 0;
}
#endif