#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for UI screens
#include "clsUser.h"  // Represents the User and related operations
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>  // For formatting output

using namespace std;

// Class for managing the "Add New User" screen in the application
class clsAddNewUserScreen : protected clsScreen
{
private:
    // Prints the details of the user
    static void _Print(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();  // Assumes FullName() concatenates first and last name
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUsername    : " << User.Username;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;  // Numeric representation of permissions
        cout << "\n___________________\n";
    }

    // Reads user permissions and calculates the appropriate permission value
    static int _ReadPermissions()
    {
        char UserInput = ' ';
        short Permissions = 0;

        // Prompt for full access
        cout << "\nDo you want to give full access? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            return clsUser::enPermissions::eAll;  // Full permissions

        // Ask for specific permissions
        cout << "\nDo you want to:";

        // Each permission option is prompted and, if confirmed, added to the total permissions
        cout << "\nShow Client List? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pListClients;

        cout << "\nAdd New Client? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pAddNewClient;

        cout << "\nDelete Client? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pDeleteClient;

        cout << "\nUpdate Client Info? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pUpdateClient;

        cout << "\nFind Client? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pFindClinet;

        cout << "\nTransactions? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pTransactions;

        cout << "\nManage Users? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pManageUsers;

        cout << "\nShow Login Register? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pLoginRegisterList;

        cout << "\nCurrency Exchange? y/n?";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pCurrencyExchange;

        return Permissions;  // Returns the combined permissions
    }

    // Reads user information from input
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permissions: ";
        User.Permissions = _ReadPermissions();  // Calls helper function to read permissions
    }

public:
    // Displays the "Add New User" screen and handles user addition
    static void ShowAddNewUserScreen()
    {
        string Title = "\t  Add New User Screen";
        clsScreen::_DrawScreenHeader(Title);  // Draws the screen header

        // Prompt user for a username
        string Username = clsInputValidate::ReadString("Please Enter Username: ");

        // Ensure the username is unique
        while (clsUser::IsUserExist(Username))
        {
            cout << "\nUsername Is Already Used, Choose another one: ";
            Username = clsInputValidate::ReadString();
        }

        // Create a new user object with the unique username
        clsUser NewUser = clsUser::GetAddNewUserObject(Username);

        // Read the new user's details
        _ReadUserInfo(NewUser);

        // Save the new user information
        clsUser::enSaveResults SaveResult;
        SaveResult = NewUser.Save();

        // Handle save results and display appropriate messages
        switch (SaveResult)
        {
        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Added Successfully :-)\n";
            _Print(NewUser);  // Print the user's details
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError: User was not saved because it's empty.";
            break;
        }
        case clsUser::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError: User was not saved because the username is already in use!\n";
            break;
        }
        }
    }
};
