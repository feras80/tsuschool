#include "Accounts.h"
#include <iostream>
#include <string>
#include <tinyxml2.h>
#include <constants.h>
#include <iomanip>
#include <cstddef>
#include <ctime>
#include <Helper.h>
#include <Enums.h>
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
	void CreditDecision(double income, int creditScore, int creditHistory);
}

Helper helper;
constants constants;
// Position enumerator

enum Position
{
	AfterChild, EndChild, FirstChild
};

//To return all Transaction for a Selected Account.
//Parameters:
// a: The Account Number

void bindTransaction(string a)
{
	try
	{
		// Build Header
		cout << "\n";
		cout << "------------------------------------------------------------------\n";
		cout << "------------------------Account Transactions----------------------\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\n";
		string accountChar;

		XMLDocument doc;
		const char *path = constants.GetPath();
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
			XMLElement *pTransactions = helper.GetFirstChildElement(pRootElement, "Transactions");

			if (NULL != pTransactions)
			{
				//Get 'transaction' Child
				XMLElement *pTransaction = helper.GetFirstChildElement(pTransactions, "transaction");

				while (pTransaction)
				{
					//Get 'AccountNo' Child
					XMLElement *pAccountNo = helper.GetFirstChildElement(pTransaction, "AccountNo");
					accountChar = helper.GetElementText(pAccountNo);
					// Check for Matching Account Number
					if (accountChar == a)
					{
						// Get 'type' Child
						XMLElement *pType = helper.GetFirstChildElement(pTransaction, "type");

						if (NULL != pType)
						{
							// Print out Type
							cout << '|' << setw(12) << helper.GetElementText(pType);

						}

						//Get 'amount' Child
						XMLElement *name = helper.GetFirstChildElement(pTransaction, "amount");

						if (NULL != name)
						{
							// convert string to *Char
							totalBalance += strtod(helper.GetElementText(name), NULL);
							strcpy(amountText, "$");
							strcat(amountText, helper.GetElementText(name));
							// Print out Amount
							cout << '|' << setw(12) << amountText;

						}

						// Get 'date' Child
						XMLElement *date = helper.GetFirstChildElement(pTransaction, "date");

						if (NULL != date)
						{
							// Print out Balance
							cout << '|' << setw(14) << helper.GetElementText(date) << '|';

						}

						std::cout << std::endl;

					}

					//Next transaction
					pTransaction = helper.GetNextSiblingElement(pTransaction, "transaction");
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

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
	}
}

// To Insert a Deposit for a Selected Account
// Parameters:
// a: the account number
// amount: amount to be Deposited

void Accounts::Deposit(string a, string amount, bool isTransfer)
{
	try
	{
		char date[9];
		_strdate(date);
		XMLDocument doc;
		const char *path = constants.GetPath();
		char accountNumberChar[100];
		char typeChar[100];

		// Load the XML file into the Doc instance
		doc.LoadFile(path);

		// Get root Element
		XMLElement *pTop = doc.RootElement();
		// Get 'Transactions' Child
		XMLElement *pTransactions = helper.GetFirstChildElement(pTop, "Transactions");

		//Create new Element
		XMLNode *pRoot = doc.NewElement("transaction");
		//Insert new Element
		pTransactions->InsertEndChild(pRoot);

		//Create new Element
		XMLElement *pElement = doc.NewElement("AccountNo");
		//Set new Element Text
		helper.SetElementText(pElement, strdup(a.c_str()));	// AccountNo
		// Insert new Element
		helper.InsertChild(pRoot, pElement, "EndChild");

		//Create new element
		pElement = doc.NewElement("type");
		// Set new Element Text
		helper.SetElementText(pElement, isTransfer == true? "Transfer-in": "Deposit");	// type  n1 > n2) ? n1 : n2;
		// Insert new Element
		pRoot->InsertEndChild(pElement);

		//Create new Element
		pElement = doc.NewElement("amount");
		// Set new Element Text
		helper.SetElementText(pElement, strdup(amount.c_str()));	// Amount
		// Insert new element
		pRoot->InsertEndChild(pElement);

		//Create new Element
		pElement = doc.NewElement("date");
		//set new Element Text
		helper.SetElementText(pElement, strdup(date));	// Amount
		//Insert new Element
		pRoot->InsertEndChild(pElement);

		//Save the changes into the XML file
		doc.SaveFile(path);
	}

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
	}
}

// To Insert a Withdrawal for a Selected Account
// Parameters:
// a: the account number
// amount: amount to be Withdrawn

void Accounts::Withdraw(string a, string amount, bool isTransfer)
{
	try
	{
		char date[9];
		_strdate(date);
		XMLDocument doc;
		const char *path = constants.GetPath();
		char accountNumberChar[100];
		char typeChar[100];
		// Load the XML file into the Doc instance
		doc.LoadFile(path);
		// Get root Element// Check for Matching Account Number
		XMLElement *pTop = doc.RootElement();
		//Get 'Transactions' Child
		XMLElement *pTransactions = helper.GetFirstChildElement(pTop, "Transactions");	// pTop->FirstChildElement("Transactions");

		//Create new Element
		XMLNode *pRoot = doc.NewElement("transaction");
		//Insert new Element
		pTransactions->InsertEndChild(pRoot);

		//Create new Element
		XMLElement *pElement = doc.NewElement("AccountNo");
		// Set new Element Text
		helper.SetElementText(pElement, strdup(a.c_str()));	// AccountNo
		//Insert new Element
		pRoot->InsertEndChild(pElement);

		//Create new Element
		pElement = doc.NewElement("type");
		//Set new element Text
		helper.SetElementText(pElement,isTransfer == true? "Transfer-out": "Withdrawal");   // type
		//Insert new Element
		pRoot->InsertEndChild(pElement);

		//Create new Element
		pElement = doc.NewElement("amount");
		//Set new Element Text
		helper.SetElementText(pElement, strdup(amount.c_str()));	// Amount
		//Insert new Element
		pRoot->InsertEndChild(pElement);

		// Create new Element
		pElement = doc.NewElement("date");
		//Set new Element Text
		helper.SetElementText(pElement, strdup(date));	// Date
		//Insert new Element
		pRoot->InsertEndChild(pElement);

		//Save the changes into the XML file
		doc.SaveFile(path);
	}

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
	}
}

// Check if Current Account Exists
// Parameters:
// a: the account number
// Returns: A boolean

bool Accounts::AcountExists(string a)
{
	try
	{
		XMLDocument doc;
		string acountChar;
		const char *path = constants.GetPath();

		int i = 0;
		// Load the XML file into the Doc instance
		doc.LoadFile(path);

		// Get root Element
		XMLElement *pRootElement = doc.RootElement();

		if (NULL != pRootElement)
		{
			// Get 'Accounts' Child
			XMLElement *pAccounts = helper.GetFirstChildElement(pRootElement, "Accounts");

			if (NULL != pAccounts)
			{
				// Get 'Account' Child
				XMLElement *pAccount = helper.GetFirstChildElement(pAccounts, "Account");

				while (pAccount)
				{
					// Get 'AccountNo' Child
					XMLElement *pAccountNo = helper.GetFirstChildElement(pAccount, "AccountNo");
					// Get Child Text
					acountChar = helper.GetElementText(pAccountNo);
					// Check for Matching Account Number
					if (acountChar == a)
					{
						return true;

					}

					//Next Account
					pAccount = helper.GetNextSiblingElement(pAccount, "Account");
				}
			}
		}

		return false;
	}

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
	}
}

// To get a Specific Account Details
// Parameters:
// a: the account number

void Accounts::GetAccount(string a)
{
	try
	{
		string acountChar;
		XMLDocument doc;
		const char *path = constants.GetPath();
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
			XMLElement *pAccounts = helper.GetFirstChildElement(pRootElement, "Accounts");

			if (NULL != pAccounts)
			{
				// Get 'Account' Child
				XMLElement *pAccount = helper.GetFirstChildElement(pAccounts, "Account");

				while (pAccount)
				{
					// Get 'AccountNo' Child
					XMLElement *pAccountNo = helper.GetFirstChildElement(pAccount, "AccountNo");

					acountChar = helper.GetElementText(pAccountNo);

					// Check for Matching Account Number
					if (acountChar == a)
					{
						i++;
						// Print out AccountNo
						cout << '|' << setw(7) << helper.GetElementText(pAccountNo);
						XMLElement *pType = pAccount->FirstChildElement("type");

						if (NULL != pType)
						{
							// Print out Type
							cout << '|' << setw(12) << helper.GetElementText(pType);

						}

						// Get 'customer' Child
						XMLElement *name = helper.GetFirstChildElement(pAccount, "customer");

						if (NULL != name)
						{
							//Print out name
							cout << '|' << setw(15) << helper.GetElementText(name);

						}

						// Get 'balance' Child
						XMLElement *balance = helper.GetFirstChildElement(pAccount, "balance");

						if (NULL != balance)
						{
							// Convert to Char
							strcpy(amountText, "$");

							strcat(amountText, helper.GetElementText(balance));
							//Print out amount
							cout << '|' << setw(10) << amountText << '|';

						}

						// Get 'openDate' Child
						XMLElement *openDate = helper.GetFirstChildElement(pAccount, "openDate");

						if (NULL != openDate)
						{
							// print out Open Date
							cout << setw(12) << helper.GetElementText(openDate) << '|';

						}

						std::cout << std::endl;
						// Call bindTransaction  method
						bindTransaction(a);
					}

					// Next Account
					pAccount = helper.GetNextSiblingElement(pAccount, "Account");
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

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
	}
}

// To get the Account Balance for a Specific Account
// Parameters:
// a: the account number

void Accounts::GetAccountBalance(string a)
{
	try
	{
		string acountChar;
		XMLDocument doc;
		const char *path = constants.GetPath();
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
			XMLElement *pAccounts = helper.GetFirstChildElement(pRootElement, "Accounts");

			if (NULL != pAccounts)
			{
				XMLElement *pAccount = helper.GetFirstChildElement(pAccounts, "Account");

				while (pAccount)
				{
					// Get 'AccountNo' child
					XMLElement *pAccountNo = helper.GetFirstChildElement(pAccount, "AccountNo");
					acountChar = helper.GetElementText(pAccountNo);
					// Check for Matching Account Number
					if (acountChar == a)
					{
						// Get 'type' Child
						XMLElement *pType = helper.GetFirstChildElement(pAccount, "type");

						// Get 'customer' Child
						XMLElement *name = helper.GetFirstChildElement(pAccount, "customer");

						// Get 'balance' Child
						XMLElement *balance = helper.GetFirstChildElement(pAccount, "balance");

						if (NULL != balance)
						{
							//Convert to *char
							strcpy(amountText, "$");
							strcat(amountText, helper.GetElementText(balance));
							//Print out amount
							cout << amountText << endl;

						}

						// Get 'openDate' Child
						XMLElement *openDate = helper.GetFirstChildElement(pAccount, "openDate");

						std::cout << std::endl;

					}

					//Next Account
					pAccount = helper.GetNextSiblingElement(pAccount, "Account");
				}
			}
		}
	}

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
	}
}

// To Return All Accounts
// Parameters:
// none

void Accounts::GetAllAccounts()
{
	try
	{
		string result;
		XMLDocument doc;
		const char *path = constants.GetPath();
		char amountText[100];

		// Load the XML file into the Doc instance
		doc.LoadFile(path);
		// Get root Element
		XMLElement *pRootElement = doc.RootElement();

		// Print out the Table Header
		cout << '|' << setw(7) << "Acc No." << '|' << setw(12) << "Account Type" << '|' << setw(15) << "Customer Name" << '|' << setw(10) << "Balance" << '|' << setw(12) << "Open Date" <<
			endl << endl;

		if (NULL != pRootElement)
		{
			//Get 'Accounts' Child
			XMLElement *pAccounts = helper.GetFirstChildElement(pRootElement, "Accounts");

			if (NULL != pAccounts)
			{
				//Get 'Account' Child
				XMLElement *pAccount = helper.GetFirstChildElement(pAccounts, "Account");

				while (pAccount)
				{
					// Get 'AccountNo' Child
					XMLElement *pAccountNo = helper.GetFirstChildElement(pAccount, "AccountNo");

					if (NULL != pAccountNo)
					{
						//Print out AccountNo
						cout << '|' << setw(7) << helper.GetElementText(pAccountNo);

					}

					//Get 'type' Child
					XMLElement *pType = helper.GetFirstChildElement(pAccount, "type");

					if (NULL != pType)
					{
						// Print out 'Tyoe'
						cout << '|' << setw(12) << helper.GetElementText(pType);
					}

					// Get 'customer' Child
					XMLElement *name = helper.GetFirstChildElement(pAccount, "customer");

					if (NULL != name)
					{
						//Print out name
						cout << '|' << setw(15) << helper.GetElementText(name);

					}

					// Get 'balance' Child
					XMLElement *balance = helper.GetFirstChildElement(pAccount, "balance");

					if (NULL != balance)
					{
						// Convert to *char
						strcpy(amountText, "$");
						strcat(amountText, helper.GetElementText(balance));
						//Print out amount
						cout << '|' << setw(10) << amountText << '|';

					}

					// Get 'openDate' Child
					XMLElement *openDate = helper.GetFirstChildElement(pAccount, "openDate");
					if (NULL != openDate)
					{
						//Print out openDate
						cout << setw(12) << helper.GetElementText(openDate) << '|';

					}

					cout << endl;
					cout << "------------------------------------------------------------";
					std::cout << std::endl;
					// Next Account
					pAccount = helper.GetNextSiblingElement(pAccount, "Account");
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

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
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
	try
	{
		XMLDocument doc;
		const char *path = constants.GetPath();
		char accountNumberChar[100];
		char typeChar[100];

		// Load the XML file into the Doc instance
		doc.LoadFile(path);
		//Get root Element
		XMLElement *pTop = doc.RootElement();

		// Get 'Accounts' Child
		XMLElement *pAccounts = helper.GetFirstChildElement(pTop, "Accounts");

		//Create new Element
		XMLNode *pRoot = doc.NewElement("Account");
		//Insert new Element
		pAccounts->InsertEndChild(pRoot);

		//Create new Element
		XMLElement *pElement = doc.NewElement("AccountNo");
		// Set new Element Text
		helper.SetElementText(pElement, strdup(accountNumber.c_str()));	// AccountNo
		// Insert new Element
		pRoot->InsertEndChild(pElement);

		//Create new Element
		pElement = doc.NewElement("type");
		// Set new Element Text
		helper.SetElementText(pElement, strdup(accountType.c_str()));	// type
		// Insert new Element
		pRoot->InsertEndChild(pElement);

		//Create new Element
		pElement = doc.NewElement("customer");
		// Set new element Text
		helper.SetElementText(pElement, strdup(customerName.c_str()));	// customer
		// Insert new Element
		pRoot->InsertEndChild(pElement);

		//Create new Element
		pElement = doc.NewElement("balance");
		// Set new Element Text
		helper.SetElementText(pElement, strdup(accountBalance.c_str()));	// balance
		// Insert new Element
		pRoot->InsertEndChild(pElement);

		//Create new Element
		pElement = doc.NewElement("openDate");
		// Set new Element Text
		helper.SetElementText(pElement, "03/01/2020");	// openDate
		//Insert new Element
		pRoot->InsertEndChild(pElement);

		//Save the changes into the XML file
		doc.SaveFile(path);
	}

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
	}
}

// To check credit card application decision
// Parameters:
// income (int) : the income of the applicant
// creditScore (int)   : the credit score of the applicant
// creditHistory(int)  : the credit history of the applicant

void Accounts::CreditDecision(int income, int creditScore, int creditHistory)

{
	int points = 0;
	double CreditLine = 0.00;

	switch (income)
	{
		case 1:
			cout << "Applicant has been declined";
			cout << endl;
			return;
		case 2:
			points += 2;
			break;
		case 3:
			points += 3;
			break;
		case 4:
			points += 4;
			break;
		case 5:
			points += 5;
			break;
	}

	switch (creditScore)
	{
		case 1:
			cout << "Applicant has been declined";
			cout << endl;
			return;
			break;
		case 2:
			points += 2;
			break;
		case 3:
			points += 3;
			break;
		case 4:
			points += 4;
			break;
		case 5:
			points += 5;
			break;
	}

	switch (creditHistory)
	{
		case 1:
			points += 1;
			break;
		case 2:
			points += 2;
			break;
		case 3:
			points += 3;
			break;
		case 4:
			points += 4;
			break;
		case 5:
			points += 5;
			break;
	}

	// The formula is based on credit line between $2000 and $10000
	CreditLine = (points *10000) / 15;
	cout << "The application for a credit card has been approved! The credit line for this application is $" << CreditLine;

	cout << endl;

}

Accounts::~Accounts() {}
