#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsUser.h"  // For managing user details
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>  // For formatting output

using namespace std;

// Class to manage the Delete User Screen
class clsDeleteUserScreen : protected clsScreen
{
private:
    // Prints the details of a user in a formatted "User Card"
    static void _Print(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;         // User's first name
        cout << "\nLastName    : " << User.LastName;          // User's last name
        cout << "\nFull Name   : " << User.FullName();        // User's full name (concatenation of first and last name)
        cout << "\nEmail       : " << User.Email;             // User's email address
        cout << "\nPhone       : " << User.Phone;             // User's phone number
        cout << "\nUsername    : " << User.Username;          // User's unique username
        cout << "\nPassword    : " << User.Password;          // User's password
        cout << "\nPermissions : " << User.Permissions;       // User's permission level
        cout << "\n___________________\n";
    }

public:
    // Displays the Delete User Screen and handles user interactions
    static void ShowDeleteUserScreen()
    {
        clsScreen::_DrawScreenHeader("\tDelete User Screen");  // Display screen header

        string Username = "";

        // Prompt the user to enter a username
        cout << "\nPlease Enter Username: ";
        Username = clsInputValidate::ReadString();

        // Ensure the entered username exists
        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUsername is not found, choose another one: ";
            Username = clsInputValidate::ReadString();
        }

        // Find the user based on the username
        clsUser User = clsUser::Find(Username);

        // Display the user details
        _Print(User);

        // Confirm the deletion with the user
        char UserAnswer = 'n';
        cout << "\nAre you sure you want to delete this user? (N/Y) ";
        cin >> UserAnswer;

        // Proceed with deletion if the user confirms
        if (tolower(UserAnswer) == 'y')
        {
            if (User.Delete())  // Attempt to delete the user
            {
                cout << "User Deleted Successfully :)" << endl;
                _Print(User);  // Print user details after deletion
            }
            else
            {
                cout << "User was not deleted due to an error." << endl;
            }
        }
    }
};
