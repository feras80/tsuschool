#include "Users.h"
#include <tinyxml2.h>
#include <iostream>
#include <constants.h>
#include <Helper.h>
using namespace std;
using namespace tinyxml2;
// Class Constructor
Users::Users()
{
	GetPassword();

}

// To return a password
// Returns a string
string Users::GetPassword()
{
    constants constants;
	string result;
	XMLDocument doc;
	char* pathChar[1000];
	const char *path = constants.GetPath();
Helper helper;
	// Load the XML file into the Doc instance
	doc.LoadFile(path);
	//Get root Element

	XMLElement *pRootElement =  doc.RootElement();

	if (NULL != pRootElement)
	{
		//Get 'users' Child
	XMLElement *pUsers = helper.GetFirstChildElement(pRootElement,"users");

		if (NULL != pUsers)
		{
			// Get 'user' Child
			XMLElement *pUser = helper.GetFirstChildElement(pUsers,"user");

			while (pUser)
			{
				// Get 'password' Child
             XMLElement *pPassword = helper.GetFirstChildElement(pUser,"password");

				result = helper.GetElementText(pPassword);

				std::cout << std::endl;
				//Return result
				return result;

			}
		}
	}

	return result;
}

Users::~Users() {}
