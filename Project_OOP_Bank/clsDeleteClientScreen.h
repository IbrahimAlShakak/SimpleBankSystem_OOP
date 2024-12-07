#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsBankClient.h"  // For managing bank client details
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>  // For formatting output

using namespace std;

// Class to manage the Delete Client Screen
class clsDeleteClientScreen : protected clsScreen
{
private:
    // Prints the details of a client in a formatted "Client Card"
    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();  // Full name (concatenation of first and last name)
        cout << "\nEmail       : " << Client.Email;  // Email address
        cout << "\nPhone       : " << Client.Phone;  // Phone number
        cout << "\nAcc. Number : " << Client.AccountNumber();  // Account number
        cout << "\nPin         : " << Client.PinCode;  // Account PIN code
        cout << "\nBalance     : " << Client.AccountBalance;  // Account balance
        cout << "\n___________________\n";
    }

public:
    // Displays the Delete Client Screen and handles user interactions
    static void ShowDeleteClientScreen()
    {
        // Check if the user has the required permissions
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
            return;

        clsScreen::_DrawScreenHeader("\tDelete Client Screen");  // Display screen header

        string AccountNumber = "";

        // Prompt user to enter the account number
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

        // Display the client details
        _Print(Client);

        // Confirm the deletion with the user
        char UserAnswer = 'n';
        cout << "\nAre you sure you want to delete this client account? (N/Y) ";
        cin >> UserAnswer;

        // Proceed with deletion if the user confirms
        if (tolower(UserAnswer) == 'y')
        {
            if (Client.Delete())  // Attempt to delete the client
            {
                cout << "Client Account Deleted Successfully :)" << endl;
                _Print(Client);  // Print client details after deletion
            }
            else
            {
                cout << "Client Account was not deleted due to an error." << endl;
            }
        }
    }
};
