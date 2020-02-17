#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>
#include <Employee.h>
#include <tinyxml2.h>
#include <Users.h>
#include <Accounts.h>
using namespace std;
using namespace tinyxml2;

// to Generate the Header for the application
void Header()
{
	system("Color A");

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "...............................Welcome to the Banking System................................\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << endl;
}

// Main Menu

void mainMenu()
{
	int ch;
	// Init Accounts instance
	Accounts account;
	while (1)
	{
		// Variables
		char c;
		string accountNumber;
		string accountType;
		string customerName;
		string accountBalance;
		bool accountExists;
		// Print out main menu choices
		do {
			system("cls");
			Header();
			cout << " 1. Create Account\n\ ";
			cout << "2. View Account\n\ ";
			cout << "3. Account List\n\ ";
			cout << "4. Deposit\n\ ";
			cout << "5. Withdraw\n\ ";
			cout << "6. Account Balance\n\ ";
			cout << "7. Exit \n\ ";
			cout << endl;
			// Prompt the user the enter a choice
			cout << "Enter your choice : \n\ ";

			cin >> ch;
			cout << endl;

			cout << endl;
			switch (ch)
			{
				case 1:
					// Clear screen
					system("cls");
					do {
						//Change color
						system("Color B");
						// Display Header
						Header();
						// Prompt the user to enter new account information
						cout << "Enter Account Number(Must be unique):";
						cin >> accountNumber;
						cout << endl;
						cout << "Enter Account Type(Checking or Saving):";
						cin >> accountType;
						cout << endl;
						cout << "Enter customer name:";
						cin >> customerName;
						cout << endl;
						cout << "Enter account balance:";
						cin >> accountBalance;

						// Call InsertAccount Function
						account.InsertAccount(accountNumber, accountType, customerName, accountBalance);
						cout << endl;
						cout << "Account has been created!";
						cout << endl;

						cout << "Back to main menu?('y' or 'n')\n";

						cin >> c;
					}

					while (c == 'n');
					break;
				case 2:
					//Clear screen
					system("cls");
					do {
						//Change color
						system("Color B");
						//Display Header
						Header();
						//Prompt the user to enter account number
						cout << "Enter Account Number: ";
						cin >> accountNumber;
						//Call GetAccount Function
						account.GetAccount(accountNumber);
						cout << "Back to main menu?('y' or 'n')\n";

						cin >> c;
					}

					while (c == 'n');
					break;
				case 3:
					//Clear screen
					system("cls");
					//Display header
					Header();
					do {
						//Call GetAllAccounts Function
						account.GetAllAccounts();
						cout << "\n";

						cout << "Back to main menu?('y' or 'n')\n";

						cin >> c;
					}

					while (c == 'n');

					break;
				case 4:

					do {
						//Clear screen
						system("cls");
						//Change color
						system("Color B");
						//Display Header
						Header();
						//Prompt the user to enter deposit information
						cout << "Enter Account Number: ";
						cin >> accountNumber;
						cout << "Enter Deposit Amount: ";
						cin >> accountBalance;
						//Check if account exists
						accountExists = account.AcountExists(accountNumber);

						if (accountExists == false)
						{
							cout << "Account Does not exist.";
							cout << endl;
						}
						else
						{
							// Call Deposit function
							account.Deposit(accountNumber, accountBalance);
							cout << "Amount has been deposited.";
						}

						cout << endl << endl;
						cout << "Back to main menu?('y' or 'n')\n";

						cin >> c;
					}

					while (c == 'n');
					break;
				case 5:
					do {
						//Clear screen
						system("cls");
						//Change color
						system("Color B");
						//Display Header
						Header();
						// Prompt the user to enter withdrawal information
						cout << "Enter Account Number: ";
						cin >> accountNumber;
						cout << "Enter Amount to Withdraw (Must be negative amount): ";
						cin >> accountBalance;
						// Check if account exists
						accountExists = account.AcountExists(accountNumber);

						if (accountExists == false)
						{
							cout << "Account Does not exist.";
							cout << endl;
						}
						else
						{
							// Call Withdraw Function
							account.Withdraw(accountNumber, accountBalance);
							cout << "Amount has been withdrawn.";
						}

						cout << endl << endl;
						cout << "Back to main menu?('y' or 'n')\n";

						cin >> c;
					}

					while (c == 'n');
					break;
				case 6:
					//Clear screen
					system("cls");
					do {
						//Change color
						system("Color B");
						//Display Header
						Header();
						// Prompt the user to enter an account number
						cout << "Enter Account Number: ";
						cin >> accountNumber;
						//Call GetAccountBalance function
						account.GetAccountBalance(accountNumber);
						cout << "Back to main menu?('y' or 'n')\n";

						cin >> c;
					}

					while (c == 'n');
					break;
				case 7:
					//Exit the application
					exit(0);
					break;
			}
		}

		while (ch <= 7);
	}
}

// Program Main
int main()
{
	string ch;
	// Init Users Instance
	Users user;
	//Display the Header
	Header();
	// Prompt the user to enter a password
	cout << "Enter your password:";
	cin >> ch;
	cout << endl;

	if (ch == user.GetPassword())
	{
		//Valid password
		mainMenu();

	}
	else
	{
		//Invalid password
		cout << "You are not permitted to access this system\n";

	}
}
