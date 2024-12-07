#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include <fstream>   // For file operations
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsUser.h"  // For managing user details and login records
#include "clsMainScreen.h"  // Main screen reference
#include "clsInputValidate.h"  // For input validation utilities
#include "Global.h"  // Global settings and constants

using namespace std;

// Class to manage the Login Register List Screen
class clsLoginRegisterScreen : protected clsScreen
{
private:
    // Prints a single login/register record in a formatted line
    static void _PrintLoginRegisterLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(25) << left << LoginRegisterRecord.DateTime;      // Date and time of the login
        cout << "| " << setw(20) << left << LoginRegisterRecord.Username;       // Username
        cout << "| " << setw(12) << left << LoginRegisterRecord.Password;       // Password
        cout << "| " << setw(20) << left << LoginRegisterRecord.Permissions;    // Permissions level
    }

public:
    // Displays the Login Register List Screen and handles the listing operation
    static void ShowLoginRegisterListScreen()
    {
        // Check if the user has the required permissions
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegisterList))
            return;

        // Retrieve the list of all login/register records
        vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecord =
            clsUser::GetLoginRegisterList();

        // Set the screen title and subtitle
        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);  // Draw the screen header

        // Print table header
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(12) << "Password";
        cout << "| " << left << setw(20) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        // Check if there are no login/register records in the system
        if (vLoginRegisterRecord.empty())
        {
            cout << "\t\t\t\tNo Records Available In the System!";
        }
        else
        {
            // Print each record's details in the table
            for (clsUser::stLoginRegisterRecord LoginRegisterRecord : vLoginRegisterRecord)
            {
                _PrintLoginRegisterLine(LoginRegisterRecord);
                cout << endl;
            }
        }

        // Print table footer
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
