#ifndef HELPER_H
#define HELPER_H
#include <tinyxml2.h>
#include <iostream>
using namespace std;
using namespace tinyxml2;

class Helper
{
	public:

    XMLElement* GetFirstChildElement(XMLElement *parentElement, string elementName);
	XMLElement* GetRootElement(XMLDocument doc);
	XMLElement* GetNextSiblingElement(XMLElement *parentElement, string elementName);
	char *GetElementText(XMLElement *element);
	void InsertChild(XMLNode *parentElement, XMLElement *child, string position);
	void SetElementText(XMLElement *element, string text);
	Helper();
	virtual~Helper();

	protected:

		private:
};

#endif	// HELPER_H
