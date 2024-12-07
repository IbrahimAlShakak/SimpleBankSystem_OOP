#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsUser.h"  // For managing user details
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>   // For formatting output

using namespace std;

// Class to manage the Update User Screen
class clsUpdateUserScreen : protected clsScreen
{
private:
    // Prints the details of a user in a formatted "User Card"
    static void _Print(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;       // User's first name
        cout << "\nLastName    : " << User.LastName;        // User's last name
        cout << "\nFull Name   : " << User.FullName();      // Full name (concatenation of first and last name)
        cout << "\nEmail       : " << User.Email;           // Email address
        cout << "\nPhone       : " << User.Phone;           // Phone number
        cout << "\nUsername    : " << User.Username;        // Username
        cout << "\nPassword    : " << User.Password;        // Password
        cout << "\nPermissions : " << User.Permissions;     // Permissions assigned to the user
        cout << "\n___________________\n";
    }

    // Reads permissions input from the user
    static int _ReadPermissions()
    {
        char UserInput = ' ';
        short Permissions = 0;

        // Check if the user wants full access
        cout << "\nDo you want to give full access? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            return clsUser::enPermissions::eAll;  // Assign all permissions

        // Otherwise, prompt for individual permissions
        cout << "\nDo you want to:";
        cout << "\nShow User List? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pListClients;

        cout << "\nAdd New User? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pAddNewClient;

        cout << "\nDelete User? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pDeleteClient;

        cout << "\nUpdate User Info? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pUpdateClient;

        cout << "\nFind Client? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pFindClinet;

        cout << "\nTransactions? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pTransactions;

        cout << "\nManage Users? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pManageUsers;

        cout << "\nShow Login Register? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pLoginRegisterList;

        cout << "\nCurrency Exchange? y/n? ";
        cin >> UserInput;
        if (tolower(UserInput) == 'y')
            Permissions += clsUser::enPermissions::pCurrencyExchange;

        return Permissions;  // Return the accumulated permissions
    }

    // Reads updated user information from the user
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
        User.Permissions = _ReadPermissions();
    }

public:
    // Displays the Update User Screen and handles the update process
    static void ShowUpdateUserScreen()
    {
        clsScreen::_DrawScreenHeader("\tUpdate User Screen");  // Draw the screen header

        string Username = "";

        // Prompt the user to enter a valid username
        cout << "\nPlease Enter Username: ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUsername is not found, choose another one: ";
            Username = clsInputValidate::ReadString();
        }

        // Retrieve the user object for the entered username
        clsUser User = clsUser::Find(Username);
        _Print(User);  // Print the current user details

        // Prompt the user to update user information
        cout << "\n\nUpdate User Info:";
        cout << "\n____________________\n";
        _ReadUserInfo(User);  // Read updated information

        // Save the updated user details and handle the save result
        clsUser::enSaveResults SaveResult;
        SaveResult = User.Save();

        switch (SaveResult)
        {
        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Updated Successfully :-)\n";
            _Print(User);  // Print the updated user details
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError: User was not saved because it's empty.";
            break;
        }
        }
    }
};
