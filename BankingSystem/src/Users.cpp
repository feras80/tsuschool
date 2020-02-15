#include "Users.h"

#include <tinyxml2.h>

#include <iostream>

#include <constants.h>

using namespace std;
using namespace tinyxml2;
Users::Users() {
  GetPassword();

}
string Users::GetPassword() {
  string result;
  XMLDocument doc;
  const char * path = constants::dataPath;

  //doc.LoadFile( "\\bin\\Debug\\data.xml");
  doc.LoadFile(path);
  XMLElement *  pRootElement = doc.RootElement();

  if (NULL != pRootElement) {
    // set of &lt;person&gt; tags
    XMLElement * pUsers = pRootElement-> FirstChildElement("users");

    if (NULL != pUsers) {
      XMLElement * pUser = pUsers -> FirstChildElement("user");

      while (pUser) {
        XMLElement * l_pForename = pUser -> FirstChildElement("password");

        result = l_pForename -> GetText();


        std::cout << std::endl;
        return result;

      }
    }
  }

  return result;
}

Users::~Users() {

}
