#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>
#include <tinyxml2.h>
#include <Users.h>
#include <Accounts.h>
#include <constants.h>
#include <security.h>
using namespace std;
using namespace tinyxml2;

#define BUFSIZE MAX_PATH
#include <fstream>
	// to Generate the Header for the application

struct Applicant
{
	string applicantName;
	string hasAJob;
	int income;
	int creditScore;
	int creditHistory;
};

Security security;
Users user;
Accounts account;
Applicant applicant;
void Header(int option)
{
	// Option 0 for main Header
	// Option 2 for credit card application

	system("Color A");

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "...............................Welcome to the Banking System................................\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << endl;
	switch (option)
	{
		case 1:
			cout << "......................................Create Account........................................\n";
			cout << endl;
			break;
		case 2:
			cout << ".....................................Account Details........................................\n";
			cout << endl;
			break;
		case 3:
			cout << ".......................................Accounts List.........................................\n";
			cout << endl;
			break;
		case 4:
			cout << "........................................Deposit.............................................\n";
			cout << endl;
			break;
		case 5:
			cout << "........................................Withdraw.............................................\n";
			cout << endl;
			break;
		case 6:
			cout << ".....................................Account Balance.........................................\n";
			cout << endl;
			break;
		case 7:
			cout << "..................................Credit Card Application...................................\n";
			cout << endl;
			break;
        case 8:
			cout << ".......................................Money Transfer.......................................\n";
			cout << endl;
			break;
	}
}

// Main Menu

void mainMenu()
{
	try
	{
		int ch;
		// Init Accounts instance

		while (1)
		{
			// Variables
			char c;
			string accountNumber;
			string fromAccount;
			string toAccount;
			string accountType;
			string customerName;
			string accountBalance;

			bool accountExists;
			// Print out main menu choices
			do {
				system("cls");
				Header(0);
				cout << " 1. Create Account\n\ ";
				cout << "2. View Account\n\ ";
				cout << "3. Account List\n\ ";
				cout << "4. Deposit\n\ ";
				cout << "5. Withdraw\n\ ";
				cout << "6. Account Balance\n\ ";
				cout << "7. Credit Card Application \n\ ";
				cout << "8. Money Transfer \n\ ";
				cout << "9. Exit \n\ ";
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
							Header(1);
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
							Header(2);
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
						Header(3);
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
							Header(4);
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
								account.Deposit(accountNumber, accountBalance,false);
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
							Header(5);
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
								account.Withdraw(accountNumber, accountBalance, false);
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
							Header(6);
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
						system("cls");
						do {
							//Change color
							system("Color B");
							//Display Header
							Header(2);
							// Prompt the user to enter the Applicant Name
							cout << "Enter the applicant name:";
							cin >> applicant.applicantName;
							cout << endl;
							// Is the applicant employed?
							cout << "Is " + applicant.applicantName + " Employed?('y' or 'n')" << endl;
							cin >> applicant.hasAJob;
							cout << endl;
							// applicant does not have a job. Exit
							if (applicant.hasAJob == "n")
							{
								cout << "Applicant has been declined";

							}

							// applicant has a job. Continue
							else
							{
								// Get the applicant income
								cout << "Select the income of the applicant " + applicant.applicantName + ":" << endl;

								cout << "1. Less than $10K" << endl;
								cout << "2. Between $10K and $30K" << endl;
								cout << "3. Between $30K and $60K" << endl;
								cout << "4. Between $60K and $90" << endl;
								cout << "5. Above $90K" << endl << endl;
								cin >> applicant.income;
								cout << endl;
								// Get the credit score of the applicant
								cout << "Select the credit Score for the applicant:" << endl;
								cout << "1. Between 300 and 579 (Very Poor)" << endl;
								cout << "2. Between 580 and 669 fair)" << endl;
								cout << "3. Between 670 and 739 (Good)" << endl;
								cout << "4. Between 740 and 799 (Very Good)" << endl;
								cout << "5. 800 and above(Exceptional)" << endl << endl;
								cin >> applicant.creditScore;
								cout << endl;
								// Get the applicant credit score
								cout << "Enter the credit history for the applicant:" << endl;
								cout << "1. Less than a year" << endl;
								cout << "2. Between 1 and 3 years" << endl;
								cout << "3. Between 4 and 6 years" << endl;
								cout << "4. Between 7 and 10 years" << endl;
								cout << "5. More than 10 years" << endl << endl;
								cin >> applicant.creditHistory;
								cout << endl;
								account.CreditDecision(applicant.income, applicant.creditScore, applicant.creditHistory);
							}

							//Call GetAccountBalance function

							cout << "Back to main menu?('y' or 'n')\n";

							cin >> c;
						}

						while (c == 'n');
						break;
						case 8:
						system("cls");
						do {
							//Change color
							system("Color B");
							//Display Header
							Header(8);
							// Prompt the user to enter the Account to Transfer Money From
							cout << "Enter the Account# that you want to transfer money from:" << endl;
							cin >> fromAccount;
							cout << endl;

                            cout << "Enter the Account# that you want to transfer money to:" << endl;
							cin >> toAccount;
							cout << endl;
							cout << "Enter the balance to be transfered:" << endl;
							cin >> accountBalance;
							cout << endl;


							if (account.AcountExists(fromAccount) == false ||account.AcountExists(toAccount) == false)
							{
								cout << "Either one or both Accounts Do not exist.";
								cout << endl << endl;

							}
							else
                            {
                             // Withdraw from account, deposit into another
                              account.Deposit(toAccount, accountBalance,true);
                              account.Withdraw(fromAccount, accountBalance,true);
                              cout << "Balance has been transfered.";
                              cout << endl;
                            }


								cout << "Back to main menu?('y' or 'n')\n";

							cin >> c;
						}
                         while (c == 'n');
						break;
					case 9:
						//Exit the application
						exit(0);
						break;
				}
			}

			while (ch <= 7);
		}
	}

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
	}
}

// Program Main
int main()
{
	try
	{
		string ch;
		string decryptedPassword;
		// Init Users Instance

		//Display the Header
		Header(0);
		// Prompt the user to enter a password
		cout << "Enter your password:";
		cin >> ch;
		cout << endl;

		decryptedPassword = security.Decrypt(user.GetPassword());
		if (ch == decryptedPassword)
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

	catch (exception ex)
	{
		cout << "Error thrown. Please contact the system administrator";
	}
}
