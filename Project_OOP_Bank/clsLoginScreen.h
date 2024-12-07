#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include <fstream>   // For file operations
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsUser.h"  // For managing user details
#include "clsMainScreen.h"  // Main screen reference
#include "clsInputValidate.h"  // For input validation utilities
#include "Global.h"  // Global settings and constants

using namespace std;

// Class to manage the Login Screen
class clsLoginScreen : protected clsScreen
{
private:
    // Handles the login process
    static void _Login()
    {
        bool LoginFailed = false;  // Tracks whether the login attempt has failed
        do
        {
            if (LoginFailed)
            {
                LoginTrials--;  // Decrement the number of allowed login trials
                cout << "\nInvalid Username/Password, Try Again!\n";
                cout << "You have " << LoginTrials << " Trials to login\n" << endl;

                if (LoginTrials < 1)  // Exit if no trials remain
                    return;
            }

            // Prompt the user for username and password
            string Username = clsInputValidate::ReadString("Enter Username: ");
            string Password = clsInputValidate::ReadString("Enter Password: ");

            // Attempt to find the user with the provided credentials
            CurrentUser = clsUser::Find(Username, Password);

            // Set the login status based on whether the user was found
            LoginFailed = CurrentUser.IsEmpty();

        } while (LoginFailed);  // Repeat if login fails

        LoginTrials = 3;  // Reset login trials upon successful login
        CurrentUser.RegisterLogin();  // Register the successful login
        clsMainScreen::ShowMainMenue();  // Display the main menu
    }

public:
    // Displays the Login Screen and initiates the login process
    static void ShowLoginScreen()
    {
        system("cls");  // Clear the console
        string Title = "\t  Login Screen";
        clsScreen::_DrawScreenHeader(Title);  // Display the screen header
        _Login();  // Start the login process
    }
};
