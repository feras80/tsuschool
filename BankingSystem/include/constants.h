#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
using namespace std;
class constants
{
	public:
		static
	const char *dataPath;
	static
	const string adminUser;
	static string test;
	char *GetPath();
	constants();
};

#endif	// CONSTANTS_H
