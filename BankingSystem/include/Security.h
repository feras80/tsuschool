#ifndef SECURITY_H
#define SECURITY_H
#include <iostream>
using namespace std;

class Security
{
	public:
		Security();
	string Encrypt(string str);
	string Decrypt(string str);
	virtual~Security();

	protected:

		private:
};

#endif	// SECURITY_H
