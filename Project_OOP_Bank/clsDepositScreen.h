#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsInputValidate.h"  // For input validation utilities
#include "clsBankClient.h"  // For managing bank client details

using namespace std;

// Class to manage the Deposit Screen
class clsDepositScreen : protected clsScreen
{
private:
    // Prints the details of a client in a formatted "Client Card"
    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;         // Client's first name
        cout << "\nLastName    : " << Client.LastName;          // Client's last name
        cout << "\nFull Name   : " << Client.FullName();        // Full name (concatenation of first and last name)
        cout << "\nEmail       : " << Client.Email;             // Email address
        cout << "\nPhone       : " << Client.Phone;             // Phone number
        cout << "\nAcc. Number : " << Client.AccountNumber();   // Account number
        cout << "\nPassword    : " << Client.PinCode;           // Account PIN code
        cout << "\nBalance     : " << Client.AccountBalance;    // Account balance
        cout << "\n___________________\n";
    }

    // Reads and validates the account number input
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();  // Reads the account number
        return AccountNumber;
    }

public:
    // Displays the Deposit Screen and handles the deposit operation
    static void ShowDepositScreen()
    {
        string Title = "\t   Deposit Screen";
        clsScreen::_DrawScreenHeader(Title);  // Display the screen header

        // Prompt the user to enter an account number
        string AccountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber))  // Validate the account number
        {
            cout << "\nAccount Number (" << AccountNumber << ") Not Found! Try Again... ";
            AccountNumber = clsInputValidate::ReadString();  // Retry input
        }

        // Find the client associated with the account number
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        // Display the client's details
        _Print(Client);

        // Prompt the user to enter the deposit amount
        double DepositAmount = 0;
        cout << "Enter Deposit Amount: ";
        DepositAmount = clsInputValidate::ReadDblNumber();  // Read and validate the deposit amount

        // Confirm the transaction
        char UserAnswer = 'n';
        cout << "\nAre you sure you want to perform this transaction? (N/Y) ";
        cin >> UserAnswer;

        // Process the deposit if the user confirms
        if (tolower(UserAnswer) == 'y')
        {
            Client.Deposit(DepositAmount);  // Perform the deposit operation
            cout << "\nAmount Deposited Successfully." << endl;
            cout << "\nNew Balance = " << Client.AccountBalance << endl;  // Display the updated balance
        }
        else
        {
            cout << "\nOperation Cancelled" << endl;  // Handle cancellation
        }
    }
};
