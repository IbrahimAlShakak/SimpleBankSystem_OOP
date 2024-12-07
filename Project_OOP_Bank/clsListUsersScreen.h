#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsUser.h"  // For managing user details
#include <iomanip>  // For formatting output

using namespace std;

// Class to manage the List Users Screen
class clsListUsersScreen : protected clsScreen
{
private:
    // Prints a single user's record in a formatted line
    static void _PrintUserRecordLine(clsUser User)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << User.Username;       // Username
        cout << "| " << setw(20) << left << User.FullName();        // Full name
        cout << "| " << setw(12) << left << User.Phone;             // Phone number
        cout << "| " << setw(20) << left << User.Email;             // Email address
        cout << "| " << setw(10) << left << User.Password;          // Password
        cout << "| " << setw(12) << left << User.Permissions;       // Permissions level
    }

public:
    // Displays the Users List Screen and handles the listing operation
    static void ShowUsersListScreen()
    {
        // Retrieve the list of all users
        vector<clsUser> vUsers = clsUser::GetUsersList();

        // Set the screen title and subtitle
        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);  // Draw the screen header

        // Print table header
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Username";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        // Check if there are no users in the system
        if (vUsers.empty())
        {
            cout << "\t\t\t\tNo Users Available In the System!";
        }
        else
        {
            // Print each user's details in the table
            for (clsUser User : vUsers)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }
        }

        // Print table footer
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
