#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsUser.h"  // For managing user details
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>  // For formatting output

using namespace std;

// Class to manage the Find User Screen
class clsFindUserScreen : protected clsScreen
{
private:
    // Prints the details of a user in a formatted "User Card"
    static void _Print(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;         // User's first name
        cout << "\nLastName    : " << User.LastName;          // User's last name
        cout << "\nFull Name   : " << User.FullName();        // Full name (concatenation of first and last name)
        cout << "\nEmail       : " << User.Email;             // Email address
        cout << "\nPhone       : " << User.Phone;             // Phone number
        cout << "\nUsername    : " << User.Username;          // Unique username
        cout << "\nPassword    : " << User.Password;          // Password
        cout << "\nPermissions : " << User.Permissions;       // Permissions level
        cout << "\n___________________\n";
    }

public:
    // Displays the Find User Screen and handles user interactions
    static void ShowFindUserScreen()
    {
        clsScreen::_DrawScreenHeader("\tFind User Screen");  // Display screen header

        // Prompt the user to enter a username
        string Username = "";
        cout << "\nPlease Enter Username: ";
        Username = clsInputValidate::ReadString();

        // Ensure the entered username exists
        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUsername is not found, choose another one: ";
            Username = clsInputValidate::ReadString();  // Retry input
        }

        // Find the user associated with the entered username
        clsUser User = clsUser::Find(Username);

        // Display the user details if found
        if (!User.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
            _Print(User);  // Print the user's details
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";  // Display error if the user is not found
        }
    }
};
