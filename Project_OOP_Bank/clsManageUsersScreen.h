#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsInputValidate.h"  // For input validation utilities
#include "clsListUsersScreen.h"  // For listing users
#include "clsAddNewUserScreen.h"  // For adding new users
#include "clsDeleteUserScreen.h"  // For deleting users
#include "clsUpdateUserScreen.h"  // For updating user information
#include "clsFindUserScreen.h"  // For finding users

using namespace std;

// Class to manage the Users Menu
class clsManageUsersScreen : protected clsScreen
{
private:
    // Enum for users menu options
    enum enUsersMenueOptions {
        eListUsers = 1,      // List all users
        eAddNewUser = 2,     // Add a new user
        eDeleteUser = 3,     // Delete a user
        eUpdateUser = 4,     // Update user information
        eFindUser = 5,       // Find a specific user
        eMainMenu = 6        // Return to the main menu
    };

    // Reads and validates the user's menu option choice
    static short _ReadUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        return clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
    }

    // Prompts the user to go back to the users menu
    static void _GoBackToUsersMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Users Menue...\n";
        system("pause>0");
        ShowUsersMenue();  // Show the users menu again
    }

    // Displays various user management screens
    static void _ShowListUsersScreen() { clsListUsersScreen::ShowUsersListScreen(); }
    static void _ShowAddNewUserScreen() { clsAddNewUserScreen::ShowAddNewUserScreen(); }
    static void _ShowDeleteUserScreen() { clsDeleteUserScreen::ShowDeleteUserScreen(); }
    static void _ShowUpdateUserScreen() { clsUpdateUserScreen::ShowUpdateUserScreen(); }
    static void _ShowFindUserScreen() { clsFindUserScreen::ShowFindUserScreen(); }

    // Executes the selected users menu option
    static void _PerfromUserssMenueOption(enUsersMenueOptions UserssMenueOption)
    {
        switch (UserssMenueOption)
        {
        case eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToUsersMenue();
            break;

        case eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToUsersMenue();
            break;

        case eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToUsersMenue();
            break;

        case eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToUsersMenue();
            break;

        case eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToUsersMenue();
            break;

        case eMainMenu:
            // Placeholder for navigating back to the main menu
            // clsMainScreen::ShowMainMenue(); 
            break;
        }
    }

public:
    // Displays the Users Menu and handles user navigation
    static void ShowUsersMenue()
    {
        // Check if the user has the required permissions
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
            return;

        system("cls");  // Clear the console
        _DrawScreenHeader("\t\Manage Users Screen");  // Display the screen header

        // Print the users menu options
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromUserssMenueOption((enUsersMenueOptions)_ReadUsersMenueOption());  // Execute the selected option
    }
};
