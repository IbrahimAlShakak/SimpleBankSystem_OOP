#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsBankClient.h"  // For managing bank client details
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>   // For formatting output

using namespace std;

// Class to manage the Update Client Screen
class clsUpdateClientScreen : protected clsScreen
{
private:
    // Reads updated client information from the user
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

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
        cout << "\nPIN         : " << Client.PinCode;          // Account PIN code
        cout << "\nBalance     : " << Client.AccountBalance;   // Account balance
        cout << "\n___________________\n";
    }

public:
    // Displays the Update Client Screen and handles the update process
    static void ShowUpdateClientScreen()
    {
        // Check if the user has the required permissions
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient))
            return;

        clsScreen::_DrawScreenHeader("\tUpdate Client Screen");  // Draw the screen header

        string AccountNumber = "";

        // Prompt the user to enter a valid account number
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        // Retrieve the client object for the entered account number
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _Print(Client1);  // Print the current client details

        // Prompt the user to update client information
        cout << "\n\nUpdate Client Info:";
        cout << "\n____________________\n";
        _ReadClientInfo(Client1);  // Read updated information

        // Save the updated client details and handle the save result
        clsBankClient::enSaveResults SaveResult;
        SaveResult = Client1.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            _Print(Client1);  // Print the updated client details
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError: Account was not saved because it's empty.";
            break;
        }
        }
    }
};
