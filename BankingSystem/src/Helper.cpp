#include "Helper.h"
#include <tinyxml2.h>
#include <iostream>
using namespace std;
using namespace tinyxml2;
Helper::Helper()
{
	XMLElement* GetRootElement(XMLDocument d);
	XMLElement* GetFirstChildElement(XMLElement e, string elementName);
	char *GetElementText(XMLElement *element);
	void *InsertChild(XMLElement *parentElement, XMLElement *child, string position);
	void SetElementText(XMLElement *element, string text);

}

XMLElement *Helper::GetFirstChildElement(XMLElement *parentElement, string elementName)
{
	return parentElement->FirstChildElement(strdup(elementName.c_str()));
}

XMLElement *Helper::GetNextSiblingElement(XMLElement *parentElement, string elementName)
{
	return parentElement->NextSiblingElement(strdup(elementName.c_str()));
}

void Helper::InsertChild(XMLNode *parentElement, XMLElement *child, string position)
{
	if (position == "AfterChild")
	{
		parentElement->InsertAfterChild(child, child);
	}
	else if (position == "EndChild")
	{
		parentElement->InsertEndChild(child);
	}
	else if (position == "FirstChild")
	{
		parentElement->InsertFirstChild(child);
	}
}

char *Helper::GetElementText(XMLElement *element)
{
	return strdup(element->GetText());
}

void Helper::SetElementText(XMLElement *element, string text)
{
	element->SetText(strdup(text.c_str()));
}

Helper::~Helper() {}
