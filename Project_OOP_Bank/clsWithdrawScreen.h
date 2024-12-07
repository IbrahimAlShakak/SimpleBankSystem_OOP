#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsInputValidate.h"  // For input validation utilities
#include "clsBankClient.h"  // For managing bank client details

using namespace std;

// Class to manage the Withdraw Screen
class clsWithdrawScreen : protected clsScreen
{
private:
    // Prints the details of a bank client in a formatted "Client Card"
    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;        // Client's first name
        cout << "\nLastName    : " << Client.LastName;         // Client's last name
        cout << "\nFull Name   : " << Client.FullName();       // Full name (concatenation of first and last name)
        cout << "\nEmail       : " << Client.Email;            // Email address
        cout << "\nPhone       : " << Client.Phone;            // Phone number
        cout << "\nAcc. Number : " << Client.AccountNumber();  // Account number
        cout << "\nPassword    : " << Client.PinCode;          // Account PIN code
        cout << "\nBalance     : " << Client.AccountBalance;   // Account balance
        cout << "\n___________________\n";
    }

    // Reads an account number from the user
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

public:
    // Displays the Withdraw Screen and handles the withdrawal process
    static void ShowWithdrawScreen()
    {
        // Set the screen title
        string Title = "\t   Withdraw Screen";
        clsScreen::_DrawScreenHeader(Title);  // Draw the screen header

        // Prompt the user to enter a valid account number
        string AccountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number (" << AccountNumber << ") Not Found! Try Again... ";
            AccountNumber = clsInputValidate::ReadString();
        }

        // Retrieve the client object for the entered account number
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _Print(Client);  // Print the client's current details

        // Prompt the user to enter a withdrawal amount
        double WithdrawAmount = 0;
        cout << "Enter Withdraw Amount: ";
        WithdrawAmount = clsInputValidate::ReadDblNumber();

        // Confirm the withdrawal operation
        char UserAnswer = 'n';
        cout << "\nAre you sure you want to perform this transaction? (N/Y): ";
        cin >> UserAnswer;

        if (tolower(UserAnswer) == 'y')  // Proceed if the user confirms
        {
            // Check if the withdrawal amount is possible
            if (Client.IsWithdrawAmountPossible(WithdrawAmount))
            {
                Client.Withdraw(WithdrawAmount);  // Deduct the amount from the account
                cout << "\nAmount Withdrawn Successfully." << endl;
                cout << "\nNew Balance = " << Client.AccountBalance << endl;
            }
            else
            {
                // Insufficient balance, cancel the operation
                cout << "\nOperation Cancelled, Not Sufficient Account Balance." << endl;
                cout << "\nAmount to Withdraw = " << WithdrawAmount << endl;
                cout << "\nYour Balance = " << Client.AccountBalance << endl;
            }
        }
        else
        {
            // User cancels the operation
            cout << "\nOperation Cancelled" << endl;
        }
    }
};
