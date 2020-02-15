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

void Header() {
  system("Color A");

  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "...............................Welcome to the Banking System................................\n";
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << endl;
}

void mainMenu() {
  int ch;
  Accounts account;
  while (1) {

    char c;
    string accountNumber;
    string accountType;
    string customerName;
    string accountBalance;

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

      cout << "Enter your choice : \n\ ";

      cin >> ch;
      cout << endl;

      cout << endl;
      switch (ch) {
      case 1:
system("cls");
        do {
          system("Color B");
          Header();

                    cout << "Enter Account Number(Must be unique):";
          cin >> accountNumber;
          cout <<endl;
          cout << "Enter Account Type(Checking or Saving):";
          cin >> accountType;
  cout <<endl;
                    cout << "Enter customer name:";
          cin >> customerName;
  cout <<endl;
           cout << "Enter account balance:";
          cin >> accountBalance;
          account.InsertAccount(accountNumber,accountType,customerName, accountBalance);
            cout <<endl;
cout << "Account has been created!";
  cout <<endl;

          cout << "Back to main menu?('y' or 'n')\n";

          cin >> c;
        }
        while (c == 'n');
        break;
      case 2:
        system("cls");
        do {
          system("Color B");
          Header();
          cout << "Enter Account Number: ";
          cin >> accountNumber;
          account.GetAccount(accountNumber);
          cout << "Back to main menu?('y' or 'n')\n";

          cin >> c;
        }
        while (c == 'n');
        break;
      case 3:
        system("cls");
        Header();
        do {
          account.GetAllAccounts();
          cout << "\n";

          cout << "Back to main menu?('y' or 'n')\n";

          cin >> c;
        }
        while (c == 'n');

        break;
      case 4:

        break;
      case 5:

        break;
      case 6:
          system("cls");
        do {
          system("Color B");
          Header();
          cout << "Enter Account Number: ";
          cin >> accountNumber;
          account.GetAccountBalance(accountNumber);
          cout << "Back to main menu?('y' or 'n')\n";

          cin >> c;
        }
        while (c == 'n');
        break;
      case 7:
        exit(0);
        break;
      }
    }
    while (ch <= 7);
  }
}

int main() {

  string ch;
  Users user;

  Header();

  cout << "Enter your password:";
  cin >> ch;
  cout << endl;

  if (ch == user.GetPassword()) {
    mainMenu();

  } else {
    cout << "You are not permitted to access this system\n";

  }

}
