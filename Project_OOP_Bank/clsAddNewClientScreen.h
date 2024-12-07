#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for UI screens
#include "clsBankClient.h"  // Represents the Bank Client and related operations
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>  // For formatting output

using namespace std;

// Class for managing the "Add New Client" screen in the application
class clsAddNewClientScreen : protected clsScreen
{
private:
    // Reads client information from user input
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();  // Input validation ensures a valid string is read

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();  // Ensures a valid float number is entered
    }

    // Prints the details of the client
    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();  // Assumes FullName() concatenates first and last name
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();  // Generates or retrieves the account number
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

public:
    // Displays the "Add New Client" screen and handles client addition
    static void ShowAddNewClientScreen()
    {
        // Ensures the user has sufficient permissions to add a new client
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
            return;

        string Title = "\t  Add New Client Screen";
        clsScreen::_DrawScreenHeader(Title);  // Draws the header for the screen

        // Prompt user for an account number
        string AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");

        // Ensure the account number is unique
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        // Create a new client object with the unique account number
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        // Read the new client's details
        _ReadClientInfo(NewClient);

        // Save the new client information
        clsBankClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();

        // Handle save results and display appropriate messages
        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Added Successfully :-)\n";
            _Print(NewClient);  // Print the client's details
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError: Account was not saved because it's empty.";
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError: Account was not saved because the account number is already in use!\n";
            break;
        }
        }
    }
};
