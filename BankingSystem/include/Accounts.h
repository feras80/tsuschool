#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <string>
using namespace std;

class Accounts
{
public:
Accounts();
virtual ~Accounts();
void GetAllAccounts();
void GetAccount(string a);
void GetAccountBalance(string a);
void InsertAccount(string accountNumber, string accountType, string customerName, string accountBalance);
bool AcountExists(string a);
void Deposit (string a , string amount);
void Withdraw (string a , string amount);
    protected:

    private:
};

#endif // ACCOUNTS_H
