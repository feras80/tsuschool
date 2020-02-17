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

//Class Constructor
Accounts::Accounts()
{
	void GetAllAccounts();
	void GetAccount(string a);
	void GetAccountBalance(string a);
	void Deposit(string a, string amount);
	void Withdraw(string a, string amount);
}

//To return all Transaction for a Selected Account.
//Parameters:
// a: The Account Number

void bindTransaction(string a)
{
	// Build Header
	cout << "\n";
	cout << "------------------------------------------------------------------\n";
	cout << "------------------------Account Transactions----------------------\n";
	cout << "------------------------------------------------------------------\n";
	cout << "\n";
	string accountChar;

	XMLDocument doc;
	const char *path = constants::dataPath;
	double totalBalance;
	char amountText[100];

	// Load the XML file into the doc instance
	doc.LoadFile(path);
	// To get current system date
	time_t t = time(0);
	struct tm *timeStruct = localtime(&t);

	//Get The root Element
	XMLElement *pRootElement = doc.RootElement();

	// Print out the table header.

	cout << '|' << setw(12) << "Type" << '|' << setw(12) << "Amount" << '|' << setw(14) << "Date" << '|' <<
		endl;
	cout << "------------------------------------------\n";

	if (NULL != pRootElement)
	{
		// Get 'Transactions' Child
		XMLElement *pTransactions = pRootElement->FirstChildElement("Transactions");

		if (NULL != pTransactions)
		{
			//Get 'transaction' Child
			XMLElement *pTransaction = pTransactions->FirstChildElement("transaction");

			while (pTransaction)
			{
				//Get 'AccountNo' Child
				XMLElement *pAccountNo = pTransaction->FirstChildElement("AccountNo");
				accountChar = pAccountNo->GetText();
				// Check for Matching Account Number
				if (accountChar == a)
				{
					// Get 'type' Child
					XMLElement *pType = pTransaction->FirstChildElement("type");

					if (NULL != pType)
					{
						// Print out Type
						cout << '|' << setw(12) << pType->GetText();

					}

					//Get 'amount' Child
					XMLElement *name = pTransaction->FirstChildElement("amount");

					if (NULL != name)
					{
						// convert string to *Char
						totalBalance += strtod(name->GetText(), NULL);
						strcpy(amountText, "$");
						strcat(amountText, name->GetText());
						// Print out Amount
						cout << '|' << setw(12) << amountText;

					}

					// Get 'date' Child
					XMLElement *balance = pTransaction->FirstChildElement("date");

					if (NULL != balance)
					{
						// Print out Balance
						cout << '|' << setw(14) << balance->GetText() << '|';

					}

					std::cout << std::endl;

				}

				//Next transaction
				pTransaction = pTransaction->NextSiblingElement("transaction");
			}

			cout << endl;
			// Print out Total Balance
			cout << "Total Account Balance as of today is: $" << totalBalance;
			cout << endl;

			// Print Footer
			cout << "\n";
			cout << "------------------------------------------------------------------\n";
			cout << "----------------------End Account Transactions--------------------\n";
			cout << "------------------------------------------------------------------\n";
			cout << "\n";
		}
	}
}

// To Insert a Deposit for a Selected Account
// Parameters:
// a: the account number
// amount: amount to be Deposited

void Accounts::Deposit(string a, string amount)
{
	char date[9];
	_strdate(date);

	XMLDocument doc;
	const char *path = constants::dataPath;
	char accountNumberChar[100];
	char typeChar[100];

	// Load the XML file into the Doc instance
	doc.LoadFile(path);

	// Get root Element
	XMLElement *pTop = doc.RootElement();
	// Get 'Transactions' Child
	XMLElement *pTransactions = pTop->FirstChildElement("Transactions");
	//Create new Element
	XMLNode *pRoot = doc.NewElement("transaction");
	//Insert new Element
	pTransactions->InsertEndChild(pRoot);
	//Create new Element
	XMLElement *pElement = doc.NewElement("AccountNo");
	//Set new Element Text
	pElement->SetText(strdup(a.c_str()));	// AccountNo
	// Insert new Element
	pRoot->InsertEndChild(pElement);
	//Create new element
	pElement = doc.NewElement("type");
	// Set new Element Text
	pElement->SetText("Deposit");	// type
	// Insert new Element
	pRoot->InsertEndChild(pElement);
	//Create new Element
	pElement = doc.NewElement("amount");
	// Set new Element Text
	pElement->SetText(strdup(amount.c_str()));	// Amount
	// Insert new element
	pRoot->InsertEndChild(pElement);

	//Create new Element
	pElement = doc.NewElement("date");
	//set new Element Text
	pElement->SetText(strdup(date));	// Date
	//Insert new Element
	pRoot->InsertEndChild(pElement);

	//Save the changes into the XML file
	doc.SaveFile(path);

}

// To Insert a Withdrawal for a Selected Account
// Parameters:
// a: the account number
// amount: amount to be Withdrawn

void Accounts::Withdraw(string a, string amount)
{
	char date[9];
	_strdate(date);

	XMLDocument doc;
	const char *path = constants::dataPath;
	char accountNumberChar[100];
	char typeChar[100];
	// Load the XML file into the Doc instance
	doc.LoadFile(path);
	// Get root Element// Check for Matching Account Number
	XMLElement *pTop = doc.RootElement();
	//Get 'Transactions' Child
	XMLElement *pTransactions = pTop->FirstChildElement("Transactions");

	//Create new Element
	XMLNode *pRoot = doc.NewElement("transaction");
	//Insert new Element
	pTransactions->InsertEndChild(pRoot);

	//Create new Element
	XMLElement *pElement = doc.NewElement("AccountNo");
	// Set new Element Text
	pElement->SetText(strdup(a.c_str()));	// AccountNo
	//Insert new Element
	pRoot->InsertEndChild(pElement);
	//Create new Element

	pElement = doc.NewElement("type");
	//Set new element Text
	pElement->SetText("Withdrawal");	// type
	//Insert new Element
	pRoot->InsertEndChild(pElement);
	//Create new Element
	pElement = doc.NewElement("amount");
	//Set new Element Text
	pElement->SetText(strdup(amount.c_str()));	// Amount
	//Insert new Element
	pRoot->InsertEndChild(pElement);
	// Create new Element
	pElement = doc.NewElement("date");
	//Set new Element Text
	pElement->SetText(strdup(date));	// Date
	//Insert new Element
	pRoot->InsertEndChild(pElement);

	//Save the changes into the XML file
	doc.SaveFile(path);

}

// Check if Current Account Exists
// Parameters:
// a: the account number
// Returns: A boolean

bool Accounts::AcountExists(string a)
{
	XMLDocument doc;
	string acountChar;
	const char *path = constants::dataPath;

	int i = 0;
	// Load the XML file into the Doc instance
	doc.LoadFile(path);

	// Get root Element
	XMLElement *pRootElement = doc.RootElement();

	if (NULL != pRootElement)
	{
		// Get 'Accounts' Child
		XMLElement *pAccounts = pRootElement->FirstChildElement("Accounts");

		if (NULL != pAccounts)
		{
			// Get 'Account' Child
			XMLElement *pAccount = pAccounts->FirstChildElement("Account");

			while (pAccount)
			{
				// Get 'AccountNo' Child
				XMLElement *pAccountNo = pAccount->FirstChildElement("AccountNo");
				// Get Child Text
				acountChar = pAccountNo->GetText();
				// Check for Matching Account Number
				if (acountChar == a)
				{
					return true;

				}

				//Next Account
				pAccount = pAccount->NextSiblingElement("Account");
			}
		}
	}

	return false;
}

// To get a Specific Account Details
// Parameters:
// a: the account number

void Accounts::GetAccount(string a)
{
	string acountChar;
	XMLDocument doc;
	const char *path = constants::dataPath;
	char amountText[100];
	int i = 0;

	// Load the XML file into the Doc instance
	doc.LoadFile(path);
	//Get root Element
	XMLElement *pRootElement = doc.RootElement();

	// Print out the Header
	cout << "\n";
	cout << "------------------------------------------------------------------\n";
	cout << "--------------------------Accounts Detail-------------------------\n";
	cout << "------------------------------------------------------------------\n";
	cout << "\n";

	// Print out the table header.
	cout << '|' << setw(7) << "Acc No." << '|' << setw(12) << "Account Type" << '|' << setw(15) << "Customer Name" << '|' << setw(10) << "Balance" << '|' << setw(12) << "Open Date" <<
		endl << endl;

	if (NULL != pRootElement)
	{
		// Get 'Accounts' Child
		XMLElement *pAccounts = pRootElement->FirstChildElement("Accounts");

		if (NULL != pAccounts)
		{
			// Get 'Account' Child
			XMLElement *pAccount = pAccounts->FirstChildElement("Account");

			while (pAccount)
			{
				// Get 'AccountNo' Child
				XMLElement *pAccountNo = pAccount->FirstChildElement("AccountNo");

				acountChar = pAccountNo->GetText();
				// Check for Matching Account Number
				if (acountChar == a)
				{
					i++;
					// Print out AccountNo
					cout << '|' << setw(7) << pAccountNo->GetText();
					XMLElement *pType = pAccount->FirstChildElement("type");

					if (NULL != pType)
					{
						// Print out Type
						cout << '|' << setw(12) << pType->GetText();

					}

					// Get 'customer' Child
					XMLElement *name = pAccount->FirstChildElement("customer");

					if (NULL != name)
					{
						//Print out name
						cout << '|' << setw(15) << name->GetText();

					}

					// Get 'balance' Child
					XMLElement *balance = pAccount->FirstChildElement("balance");

					if (NULL != balance)
					{
						// Convert to Char
						strcpy(amountText, "$");
						strcat(amountText, balance->GetText());
						//Print out amount
						cout << '|' << setw(10) << amountText << '|';

					}

					// Get 'openDate' Child
					XMLElement *openDate = pAccount->FirstChildElement("openDate");

					if (NULL != openDate)
					{
						// print out Open Date
						cout << setw(12) << openDate->GetText() << '|';

					}

					std::cout << std::endl;
					// Call bindTransaction  method
					bindTransaction(a);
				}

				// Next Account
				pAccount = pAccount->NextSiblingElement("Account");
			}

			// Print message if account is not found
			if (i == 0)
			{
				std::cout << "\t\tNO ACCOUNT FOUND!!!\n";
				cout << endl;
			}
		}
	}
}

// To get the Account Balance for a Specific Account
// Parameters:
// a: the account number

void Accounts::GetAccountBalance(string a)
{
	string acountChar;
	XMLDocument doc;
	const char *path = constants::dataPath;
	char amountText[100];
	int i = 0;

	// Load the XML file into the Doc instance
	doc.LoadFile(path);
	// Get root Element
	XMLElement *pRootElement = doc.RootElement();

	cout << endl;
	// Print out Message
	cout << "Balance for account No." << a << " is ";

	if (NULL != pRootElement)
	{
		// Get 'Accounts' Child
		XMLElement *pAccounts = pRootElement->FirstChildElement("Accounts");

		if (NULL != pAccounts)
		{
			XMLElement *pAccount = pAccounts->FirstChildElement("Account");

			while (pAccount)
			{
				// Get 'AccountNo' child
				XMLElement *pAccountNo = pAccount->FirstChildElement("AccountNo");
				acountChar = pAccountNo->GetText();
				// Check for Matching Account Number
				if (acountChar == a)
				{
					// Get 'type' Child
					XMLElement *pType = pAccount->FirstChildElement("type");

					// Get 'customer' Child
					XMLElement *name = pAccount->FirstChildElement("customer");

					// Get 'balance' Child
					XMLElement *balance = pAccount->FirstChildElement("balance");

					if (NULL != balance)
					{
						//Convert to *char
						strcpy(amountText, "$");
						strcat(amountText, balance->GetText());
						//Print out amount
						cout << amountText << endl;

					}

					// Get 'openDate' Child
					XMLElement *openDate = pAccount->FirstChildElement("openDate");

					std::cout << std::endl;

				}

				//Next Account
				pAccount = pAccount->NextSiblingElement("Account");
			}
		}
	}
}

// To Return All Accounts
// Parameters:
// none

void Accounts::GetAllAccounts()
{
	string result;
	XMLDocument doc;
	const char *path = constants::dataPath;
	char amountText[100];

	// Load the XML file into the Doc instance
	doc.LoadFile(path);
	// Get root Element
	XMLElement *pRootElement = doc.RootElement();

	// Print out the Header
	cout << "\n";
	cout << "------------------------------------------------------------------\n";
	cout << "---------------------------Accounts List--------------------------\n";
	cout << "------------------------------------------------------------------\n";
	cout << "\n";
	// Print out the Table Header
	cout << '|' << setw(7) << "Acc No." << '|' << setw(12) << "Account Type" << '|' << setw(15) << "Customer Name" << '|' << setw(10) << "Balance" << '|' << setw(12) << "Open Date" <<
		endl << endl;

	if (NULL != pRootElement)
	{
		//Get 'Accounts' Child
		XMLElement *pAccounts = pRootElement->FirstChildElement("Accounts");

		if (NULL != pAccounts)
		{
			//Get 'Account' Child
			XMLElement *pAccount = pAccounts->FirstChildElement("Account");

			while (pAccount)
			{
				// Get 'AccountNo' Child
				XMLElement *pAccountNo = pAccount->FirstChildElement("AccountNo");

				if (NULL != pAccountNo)
				{
					//Print out AccountNo
					cout << '|' << setw(7) << pAccountNo->GetText();

				}

				//Get 'type' Child
				XMLElement *pType = pAccount->FirstChildElement("type");

				if (NULL != pType)
				{
					// Print out 'Tyoe'
					cout << '|' << setw(12) << pType->GetText();
				}

				// Get 'customer' Child
				XMLElement *name = pAccount->FirstChildElement("customer");

				if (NULL != name)
				{
					//Print out name
					cout << '|' << setw(15) << name->GetText();

				}

				// Get 'balance' Child
				XMLElement *balance = pAccount->FirstChildElement("balance");

				if (NULL != balance)
				{
					// Convert to *char
					strcpy(amountText, "$");	// copy string one into the result.
					strcat(amountText, balance->GetText());	// append string two to the result.
					//Print out amount
					cout << '|' << setw(10) << amountText << '|';

				}

				// Get 'openDate' Child
				XMLElement *openDate = pAccount->FirstChildElement("openDate");

				if (NULL != openDate)
				{
					//Print out openDate
					cout << setw(12) << openDate->GetText() << '|';

				}

				cout << endl;
				cout << "------------------------------------------------------------";
				std::cout << std::endl;
				// Next Account
				pAccount = pAccount->NextSiblingElement("Account");
			}

			//Print out Footer
			cout << "\n";
			cout << "------------------------------------------------------------------\n";
			cout << "-----------------------End of Accounts List-----------------------\n";
			cout << "------------------------------------------------------------------\n";
			cout << "\n";
		}
	}
}

// To Insert a New Account
// Parameters:
// accountNumber(string) : the account number
// accountType(string)   : the account type
// customerName(string)  : customer name
// accountBalance(string): account balance

void Accounts::InsertAccount(string accountNumber, string accountType, string customerName, string accountBalance)
{
	XMLDocument doc;
	const char *path = constants::dataPath;
	char accountNumberChar[100];
	char typeChar[100];

	// Load the XML file into the Doc instance
	doc.LoadFile(path);
	//Get root Element
	XMLElement *pTop = doc.RootElement();

	// Get 'Accounts' Child
	XMLElement *pAccounts = pTop->FirstChildElement("Accounts");
	//Create new Element
	XMLNode *pRoot = doc.NewElement("Account");
	//Insert new Element
	pAccounts->InsertEndChild(pRoot);
	//Create new Element
	XMLElement *pElement = doc.NewElement("AccountNo");
	// Set new Element Text
	pElement->SetText(strdup(accountNumber.c_str()));	// AccountNo
	// Insert new Element
	pRoot->InsertEndChild(pElement);
	//Create new Element
	pElement = doc.NewElement("type");
	// Set new Element Text
	pElement->SetText(strdup(accountType.c_str()));	// type
	// Insert new Element
	pRoot->InsertEndChild(pElement);
	//Create new Element
	pElement = doc.NewElement("customer");
	// Set new element Text
	pElement->SetText(strdup(customerName.c_str()));	// customer
	// Insert new Element
	pRoot->InsertEndChild(pElement);
	//Create new Element
	pElement = doc.NewElement("balance");
	// Set new Element Text
	pElement->SetText(strdup(accountBalance.c_str()));	// balance
	// Insert new Element
	pRoot->InsertEndChild(pElement);
	//Create new Element
	pElement = doc.NewElement("openDate");
	// Set new Element Text
	pElement->SetText("01/01/2020");	// openDate
	//Insert new Element
	pRoot->InsertEndChild(pElement);

	//Save the changes into the XML file
	doc.SaveFile(path);

}

Accounts::~Accounts() {}
