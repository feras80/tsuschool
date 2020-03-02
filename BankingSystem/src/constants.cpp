#include "constants.h"
#include <windows.h>
#define BUFSIZE MAX_PATH
// Constants class

constants::constants()
{

GetPath();

}

// Returns executable path
char* constants::GetPath()
{
    char buffer[MAX_PATH];
    string strResult;
    char* charResult;
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    strResult =  string( buffer ).substr( 0, pos) +"\\data.xml";
    charResult=  strdup(strResult.c_str());
    return charResult;

}

 const string adminUser= "Admin";
