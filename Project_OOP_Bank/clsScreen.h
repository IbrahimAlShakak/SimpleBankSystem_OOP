#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "Global.h"  // Global settings and constants
#include "clsDate.h"  // For managing date and time functionalities

using namespace std;

// Base class for managing screen functionalities
class clsScreen
{
protected:
    // Draws the screen header with title, optional subtitle, and user information
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        // Draw the top border of the screen
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;  // Display the main title

        // Display the subtitle if provided
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }

        // Draw the bottom border and additional user information
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\tUser: " << CurrentUser.Username << endl;  // Display the current username
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";  // Display the current date
    }

    // Checks if the current user has the required access rights for a specific permission
    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        // Verify the user's access rights
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            // Display an "Access Denied" message if the user lacks permission
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;  // Deny access
        }
        else
        {
            return true;  // Grant access
        }
    }
};
