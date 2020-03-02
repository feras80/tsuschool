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

using namespace std;

Security::Security()
{
 string  Encrypt(string file);
  string Decrypt(string file);
}
string Security::Encrypt(string file)
{
    string str="";
return str;


}

string Decrypt(string file)
{
    constants constants;

   const char *fname = constants.GetPath();

	char    sh, choice;
	fstream fps, fpt;

	fps.open(fname);
   if(!fps)
	{
		cout<<"Error in opening source file..!!";
		cout<<"\nPress any key to exit...";

	}
	fpt.open("temp.txt");
	if(!fpt)
	{
		cout<<"Error in opening temp.txt file..!!";
		fps.close();
		cout<<"\nPress any key to exit...";

	}
	while(fpt.eof()==0)
	{
		fpt>>sh;
		sh=sh-100;
		fps<<sh;
	}
	cout<<"File "<<fname<<" decrypted successfully..!!";
	cout<<"\nPress any key to exit...";
	fps.close();
	fpt.close();
}


Security::~Security()
{
    //dtor
}
