#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>
#include <string>
#include <Employee.h>
using namespace std;

Employee::Employee()
{

GetPassword();
}

string Employee::GetPassword()
{
    return "FF";
}
