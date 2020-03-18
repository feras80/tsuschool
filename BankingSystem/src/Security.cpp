#include "Security.h"
#include <constants.h>
#include <iostream>
#include <fstream>
#include "Accounts.h"
#include <iostream>
#include <string>
#include <tinyxml2.h>
#include <constants.h>
#include <iomanip>
#include <cstddef>
#include <ctime>
#include <sstream>
using namespace std;

Security::Security()
{
	string Encrypt(string str);
	string Decrypt(string str);
}

string Security::Encrypt(string str)
{
	string result;
	for (string::size_type i = 0; i < str.size(); i++)
	{
		result += int(str[i]);

	}

	return result;
}
// To decrypt a string
string Security::Decrypt(string str)
{
	string result = "";
	string tempHold = "";
	int tempHoldInt;
	// loop through the string
	for (string::size_type i = 0; i < str.size(); i++)
	{
		ostringstream oss;
		oss << str[i];
		tempHold += oss.str();
		// If the size of the temp hold is 3, convert it to its ascii representation
		if (tempHold.size() == 3)
		{
			char c;

			int number;
			std::istringstream(tempHold) >> tempHoldInt;

			c = char(tempHoldInt);
			result += char(tempHoldInt);
			tempHold = "";
		}
	}

	return result;

}

Security::~Security()
{
	//dtor
}
