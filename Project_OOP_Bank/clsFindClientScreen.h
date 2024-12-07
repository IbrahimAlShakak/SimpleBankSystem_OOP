#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsBankClient.h"  // For managing bank client details
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>  // For formatting output

using namespace std;

// Class to manage the Find Client Screen
class clsFindClientScreen : protected clsScreen
{
private:
    // Prints the details of a client in a formatted "Client Card"
    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n______________________________________";
        cout << "\nFirstName   : " << Client.FirstName;         // Client's first name
        cout << "\nLastName    : " << Client.LastName;          // Client's last name
        cout << "\nFull Name   : " << Client.FullName();        // Full name (concatenation of first and last name)
        cout << "\nEmail       : " << Client.Email;             // Email address
        cout << "\nPhone       : " << Client.Phone;             // Phone number
        cout << "\nAcc. Number : " << Client.AccountNumber();   // Account number
        cout << "\nPassword    : " << Client.PinCode;           // Account PIN code
        cout << "\nBalance     : " << Client.AccountBalance;    // Account balance
        cout << "\n______________________________________\n";
    }

public:
    // Displays the Find Client Screen and handles user interactions
    static void ShowFindClientScreen()
    {
        // Check if the user has the required permissions
        if (!CheckAccessRights(clsUser::enPermissions::pFindClinet))
            return;

        clsScreen::_DrawScreenHeader("\tFind Client Screen");  // Display screen header

        // Prompt the user to enter an account number
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        // Ensure the entered account number exists
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        // Find the client based on the account number
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        // Display the client details if found
        if (!Client.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
            _Print(Client);  // Print the client's details
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";  // Display error if the client is not found
        }
    }
};
