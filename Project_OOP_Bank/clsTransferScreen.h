#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsInputValidate.h"  // For input validation utilities
#include "clsBankClient.h"  // For managing bank client details
#include "clsUser.h"  // For managing user details
#include "Global.h"  // Global settings and constants

using namespace std;

// Class to manage the Transfer Screen
class clsTransferScreen : protected clsScreen
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

    // Reads an account number from the user with a custom message
    static string _ReadAccountNumber(string Text = "Please Enter client Account Number: ")
    {
        string AccountNumber = "";
        cout << "\n" << Text;
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

public:
    // Displays the Transfer Screen and handles the transfer process
    static void ShowTransferScreen()
    {
        // Set the screen title
        string Title = "\t   Transfer Screen";
        clsScreen::_DrawScreenHeader(Title);  // Draw the screen header

        // Read and validate the source account number
        string FromAccountNumber;
        while (true)
        {
            FromAccountNumber = _ReadAccountNumber("Enter Account Number you want to transfer FROM: ");
            if (clsBankClient::IsClientExist(FromAccountNumber))
                break;
            cout << "Account Number not found. Please try again.\n";
        }
        clsBankClient SourceClient = clsBankClient::Find(FromAccountNumber);
        _Print(SourceClient);  // Print details of the source client

        // Read and validate the destination account number
        string ToAccountNumber;
        do {
            ToAccountNumber = _ReadAccountNumber("Enter Account Number you want to transfer TO: ");
            if (!clsBankClient::IsClientExist(ToAccountNumber))
                cout << "Account Number not found. Please try again.\n";
        } while (!clsBankClient::IsClientExist(ToAccountNumber));

        clsBankClient DestinationClient = clsBankClient::Find(ToAccountNumber);
        _Print(DestinationClient);  // Print details of the destination client

        // Read and validate the transfer amount
        double TransferAmount = 0;
        do
        {
            if (!SourceClient.IsWithdrawAmountPossible(TransferAmount))
                cout << "Amount exceeds the available balance. ";
            cout << "Enter Transfer Amount: ";
            TransferAmount = clsInputValidate::ReadDblNumber();
        } while (!SourceClient.IsWithdrawAmountPossible(TransferAmount));

        // Confirm the transfer operation
        cout << "Are you sure you want to perform this operation? (Y/N): ";
        char UserInput = 'n';
        cin >> UserInput;

        if (tolower(UserInput) == 'y')  // Proceed if the user confirms
        {
            SourceClient.Withdraw(TransferAmount);  // Deduct the amount from the source account
            DestinationClient.Deposit(TransferAmount);  // Add the amount to the destination account
            cout << "\nTransfer Done Successfully.\n";
            _Print(SourceClient);  // Print updated source client details
            _Print(DestinationClient);  // Print updated destination client details
            SourceClient.RegisterTransfer(DestinationClient, TransferAmount, CurrentUser.Username);  // Log the transfer
        }
        else
        {
            cout << "\nTransfer Operation Canceled.\n";
        }
    }
};
