#include "Accounts.h"
#include <iostream>
#include <string>
#include <tinyxml2.h>
#include <constants.h>
#include <iomanip>
#include <cstddef>
#include <ctime>

using namespace std;
using namespace tinyxml2;

Accounts::Accounts() {

  void GetAllAccounts();
  void GetAccount(string a);
  void GetAccountBalance(string a);
  void Deposit(string a , string amount);
  void Withdraw (string a , string amount);
}

void bindTransaction(string a) {

  cout << "\n";
  cout << "------------------------------------------------------------------\n";
  cout << "------------------------Account Transactions----------------------\n";
  cout << "------------------------------------------------------------------\n";
  cout << "\n";
  string accountChar;
  XMLDocument doc;
  const char * path = constants::dataPath;
  double totalBalance;
  char amountText[100];
  doc.LoadFile(path);
  time_t t = time(0);
  struct tm * timeStruct = localtime(&t);
  XMLElement * pRootElement = doc.RootElement();

  cout << '|' << setw(12) << "Type" << '|' << setw(12) << "Amount" << '|' << setw(14) << "Date" << '|' <<
      endl;
    cout << "------------------------------------------\n";

  if (NULL != pRootElement) {

    XMLElement *  pTransactions = pRootElement-> FirstChildElement("Transactions");

    if (NULL !=  pTransactions) {
      XMLElement *  pTransaction =  pTransactions -> FirstChildElement("transaction");

      while (pTransaction) {
        XMLElement * pAccountNo = pTransaction -> FirstChildElement("AccountNo");
        accountChar = pAccountNo -> GetText();

        if (accountChar == a) {

          XMLElement * pType = pTransaction -> FirstChildElement("type");

          if (NULL != pType) {
            cout << '|' << setw(12) << pType -> GetText();

          }

          XMLElement * name = pTransaction-> FirstChildElement("amount");

          if (NULL != name) {

                totalBalance+= strtod(name-> GetText(),NULL);
          strcpy(amountText,"$");
          strcat(amountText,name->GetText());

            cout << '|' << setw(12)   <<amountText;

          }

          XMLElement * balance = pTransaction -> FirstChildElement("date");

          if (NULL != balance) {
            cout << '|' << setw(14) << balance -> GetText() << '|';

          }
          std::cout << std::endl;

        }

        pTransaction = pTransaction -> NextSiblingElement("transaction");
      }
      cout <<endl;
      cout <<"Total Account Balance as of today is: $" << totalBalance;
      cout<< endl;

        cout << "\n";
  cout << "------------------------------------------------------------------\n";
  cout << "----------------------End Account Transactions--------------------\n";
  cout << "------------------------------------------------------------------\n";
  cout << "\n";
    }
  }

}

void Accounts::Deposit (string a , string amount)
{

    char date[9];
	_strdate(date);

XMLDocument doc;
  const char * path = constants::dataPath;
char accountNumberChar[100];
char typeChar[100];
  doc.LoadFile(path);

XMLElement * pTop = doc.RootElement();
XMLElement *pTransactions = pTop->FirstChildElement("Transactions");
   XMLNode * pRoot = doc.NewElement("transaction");
pTransactions->InsertEndChild(pRoot);
  //  doc.InsertFirstChild(pRoot);
    XMLElement * pElement = doc.NewElement("AccountNo");

    pElement->SetText(strdup(a.c_str())); // AccountNo

    pRoot->InsertEndChild(pElement);


    pElement = doc.NewElement("type");
    pElement->SetText("Deposit"); // type
    pRoot->InsertEndChild(pElement);

    pElement = doc.NewElement("amount");
    pElement->SetText(strdup(amount.c_str())); // Amount
    pRoot->InsertEndChild(pElement);


    pElement = doc.NewElement("date");
    pElement->SetText(strdup(date)); // Date
    pRoot->InsertEndChild(pElement);

    doc.SaveFile(path);

}

void Accounts::Withdraw (string a , string amount)
{

    char date[9];
	_strdate(date);

XMLDocument doc;
  const char * path = constants::dataPath;
char accountNumberChar[100];
char typeChar[100];
  doc.LoadFile(path);

XMLElement * pTop = doc.RootElement();
XMLElement *pTransactions = pTop->FirstChildElement("Transactions");
   XMLNode * pRoot = doc.NewElement("transaction");
pTransactions->InsertEndChild(pRoot);
  //  doc.InsertFirstChild(pRoot);
    XMLElement * pElement = doc.NewElement("AccountNo");

    pElement->SetText(strdup(a.c_str())); // AccountNo

    pRoot->InsertEndChild(pElement);


    pElement = doc.NewElement("type");
    pElement->SetText("Withdrawal"); // type
    pRoot->InsertEndChild(pElement);

    pElement = doc.NewElement("amount");
    pElement->SetText(strdup(amount.c_str())); // Amount
    pRoot->InsertEndChild(pElement);


    pElement = doc.NewElement("date");
    pElement->SetText(strdup(date)); // Date
    pRoot->InsertEndChild(pElement);

    doc.SaveFile(path);

}

bool Accounts::AcountExists(string a)
{
     XMLDocument doc;
       string acountChar;
  const char * path = constants::dataPath;

  int i = 0;
  doc.LoadFile(path);

  XMLElement * pRootElement = doc.RootElement();


  if (NULL != pRootElement) {

    XMLElement * pAccounts = pRootElement -> FirstChildElement("Accounts");

    if (NULL != pAccounts) {
      XMLElement * pAccount = pAccounts -> FirstChildElement("Account");

      while (pAccount) {
        XMLElement * pAccountNo = pAccount -> FirstChildElement("AccountNo");
        acountChar = pAccountNo -> GetText();

        if (acountChar == a) {
          return true;


          }
                pAccount = pAccount -> NextSiblingElement("Account");
      }
  }
    }


    return false;
}

void Accounts::GetAccount(string a) {
  string acountChar;
  XMLDocument doc;
  const char * path = constants::dataPath;
  char amountText[100];
  int i = 0;
  doc.LoadFile(path);

  XMLElement * pRootElement = doc.RootElement();
  cout << "\n";
  cout << "------------------------------------------------------------------\n";
  cout << "--------------------------Accounts Detail-------------------------\n";
  cout << "------------------------------------------------------------------\n";
  cout << "\n";
  cout << '|' << setw(7) << "Acc No." << '|' << setw(12) << "Account Type" << '|' << setw(15) << "Customer Name" << '|' << setw(10) << "Balance" << '|' << setw(12) << "Open Date" <<
    endl << endl;

  if (NULL != pRootElement) {

    XMLElement * pAccounts = pRootElement -> FirstChildElement("Accounts");

    if (NULL != pAccounts) {
      XMLElement * pAccount = pAccounts -> FirstChildElement("Account");

      while (pAccount) {
        XMLElement * pAccountNo = pAccount -> FirstChildElement("AccountNo");
        acountChar = pAccountNo -> GetText();

        if (acountChar == a) {
          i++;
          cout << '|' << setw(7) << pAccountNo -> GetText();
          XMLElement * pType = pAccount -> FirstChildElement("type");

          if (NULL != pType) {
            cout << '|' << setw(12) << pType -> GetText();

          }

          XMLElement * name = pAccount -> FirstChildElement("customer");

          if (NULL != name) {
            cout << '|' << setw(15) << name -> GetText();

          }

          XMLElement * balance = pAccount -> FirstChildElement("balance");

          if (NULL != balance) {
                strcpy(amountText,"$");
             strcat(amountText,balance->GetText());
            cout << '|' << setw(10) << amountText << '|';

          }

          XMLElement * openDate = pAccount -> FirstChildElement("openDate");

          if (NULL != openDate) {
            cout << setw(12) << openDate -> GetText() << '|';

          }

          std::cout << std::endl;

          bindTransaction(a);
        }

        pAccount = pAccount -> NextSiblingElement("Account");
      }
      if (i == 0) {
        std::cout << "\t\tNO ACCOUNT FOUND!!!\n";
        cout << endl;
      }
    }
  }

}

void Accounts::GetAccountBalance( string a)
{

 string acountChar;
  XMLDocument doc;
  const char * path = constants::dataPath;
  char amountText[100];
  int i = 0;
  doc.LoadFile(path);

  XMLElement * pRootElement = doc.RootElement();

  cout << endl;
  cout<<"Balance for account No." <<a<< " is ";

  if (NULL != pRootElement) {

    XMLElement * pAccounts = pRootElement -> FirstChildElement("Accounts");

    if (NULL != pAccounts) {
      XMLElement * pAccount = pAccounts -> FirstChildElement("Account");

      while (pAccount) {
        XMLElement * l_pForename = pAccount -> FirstChildElement("AccountNo");
        acountChar = l_pForename -> GetText();

        if (acountChar == a) {

          XMLElement * l_pSurname = pAccount -> FirstChildElement("type");

          XMLElement * name = pAccount -> FirstChildElement("customer");

          XMLElement * balance = pAccount -> FirstChildElement("balance");

          if (NULL != balance) {
                strcpy(amountText,"$");
             strcat(amountText,balance->GetText());
            cout  << amountText << endl;

          }

          XMLElement * openDate = pAccount -> FirstChildElement("openDate");

          std::cout << std::endl;

        }

        pAccount = pAccount -> NextSiblingElement("Account");
      }

    }
  }
}

void Accounts::GetAllAccounts() {
  string result;
  XMLDocument doc;
  const char * path = constants::dataPath;
char amountText[100];
  doc.LoadFile(path);

  XMLElement * pRootElement = doc.RootElement();
  cout << "\n";
  cout << "------------------------------------------------------------------\n";
  cout << "---------------------------Accounts List--------------------------\n";
  cout << "------------------------------------------------------------------\n";
  cout << "\n";

  cout << '|' << setw(7) << "Acc No." << '|' << setw(12) << "Account Type" << '|' << setw(15) << "Customer Name" << '|' << setw(10) << "Balance" << '|' << setw(12) << "Open Date" <<
    endl << endl;

  if (NULL != pRootElement) {
    XMLElement * pAccounts = pRootElement -> FirstChildElement("Accounts");

    if (NULL != pAccounts) {
      XMLElement * pAccount = pAccounts -> FirstChildElement("Account");

      while (pAccount) {
        XMLElement * pAccountNo = pAccount -> FirstChildElement("AccountNo");

        if (NULL != pAccountNo) {
          cout << '|' << setw(7) << pAccountNo -> GetText();

        }

        XMLElement * pType = pAccount -> FirstChildElement("type");

        if (NULL != pType) {
          cout << '|' << setw(12) << pType -> GetText();
        }

        XMLElement * name = pAccount -> FirstChildElement("customer");

        if (NULL != name) {
          cout << '|' << setw(15) << name -> GetText();

        }

        XMLElement * balance = pAccount -> FirstChildElement("balance");

        if (NULL != balance) {
                  strcpy(amountText,"$"); // copy string one into the result.
             strcat(amountText,balance->GetText()); // append string two to the result.
          cout << '|' << setw(10) << amountText << '|';

        }

        XMLElement * openDate = pAccount -> FirstChildElement("openDate");

        if (NULL != openDate) {
          cout << setw(12) << openDate -> GetText() << '|';

        }

        cout << endl;
        cout << "------------------------------------------------------------";
        std::cout << std::endl;

        pAccount = pAccount -> NextSiblingElement("Account");
      }
        cout << "\n";
  cout << "------------------------------------------------------------------\n";
  cout << "-----------------------End of Accounts List-----------------------\n";
  cout << "------------------------------------------------------------------\n";
  cout << "\n";
    }
  }
}

void Accounts::InsertAccount(string accountNumber, string accountType, string customerName, string accountBalance)
{


 XMLDocument doc;
  const char * path = constants::dataPath;
char accountNumberChar[100];
char typeChar[100];
  doc.LoadFile(path);

XMLElement * pTop = doc.RootElement();
XMLElement *pAccounts = pTop->FirstChildElement("Accounts");
   XMLNode * pRoot = doc.NewElement("Account");
pAccounts->InsertEndChild(pRoot);
  //  doc.InsertFirstChild(pRoot);
    XMLElement * pElement = doc.NewElement("AccountNo");

    pElement->SetText(strdup(accountNumber.c_str())); // AccountNo

    pRoot->InsertEndChild(pElement);

    pElement = doc.NewElement("type");

    pElement->SetText(strdup(accountType.c_str())); // type

    pRoot->InsertEndChild(pElement);

    pElement = doc.NewElement("customer");
    pElement->SetText(strdup(customerName.c_str())); // customer
        pRoot->InsertEndChild(pElement);


    pElement = doc.NewElement("balance");
    pElement->SetText(strdup(accountBalance.c_str())); // balance
    pRoot->InsertEndChild(pElement);


    pElement = doc.NewElement("openDate");
    pElement->SetText("01/01/2020"); // openDate
    pRoot->InsertEndChild(pElement);


   doc.SaveFile(path);


 }


Accounts::~Accounts() {

}
