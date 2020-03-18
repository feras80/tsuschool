#include "constants.h"
#include <windows.h>
#include <iostream>
#define BUFSIZE MAX_PATH
using namespace std;
// Constants class

constants::constants()
{
	GetPath();

}

// Returns executable path
char *constants::GetPath()
{
	try
	{
		char buffer[MAX_PATH];
		string strResult;
		char *charResult;
		GetModuleFileName(NULL, buffer, MAX_PATH);
		string::size_type pos = string(buffer).find_last_of("\\/");
		strResult = string(buffer).substr(0, pos) + "\\data.xml";
		charResult = strdup(strResult.c_str());
		return charResult;
	}

	catch (exception ex)
	{
		std::cout << "Error thrown. Please contact the system administrator";
	}
}

const string adminUser = "Admin";
