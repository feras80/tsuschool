#include "Util.h"


class Util
{
public:

static    StringTochar(string s);
}
    //
static StringTochar(string s)
{

    return "feras";
}
    std::string str = "std::string to char*";

	char* c = const_cast<char*>(str.c_str());
	std::cout << c;

	return 0;

}


