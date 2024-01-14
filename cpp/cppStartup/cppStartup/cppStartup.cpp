// cppStartup.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "testSuiteForComplex.h"
#include "MyString.h"

int  main()
{   
    char a[]{ 'a','b', '\0' };
    cout << MyString(a) << endl;

}

