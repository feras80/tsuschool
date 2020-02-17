#include "Users.h"
#include <tinyxml2.h>
#include <iostream>
#include <constants.h>
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
	string result;
	XMLDocument doc;
	const char *path = constants::dataPath;

	// Load the XML file into the Doc instance
	doc.LoadFile(path);
	//Get root Element
	XMLElement *pRootElement = doc.RootElement();

	if (NULL != pRootElement)
	{
		//Get 'users' Child
		XMLElement *pUsers = pRootElement->FirstChildElement("users");

		if (NULL != pUsers)
		{
			// Get 'user' Child
			XMLElement *pUser = pUsers->FirstChildElement("user");

			while (pUser)
			{
				// Get 'password' Child
				XMLElement *pPassword = pUser->FirstChildElement("password");

				result = pPassword->GetText();

				std::cout << std::endl;
				//Return result
				return result;

			}
		}
	}

	return result;
}

Users::~Users() {}
