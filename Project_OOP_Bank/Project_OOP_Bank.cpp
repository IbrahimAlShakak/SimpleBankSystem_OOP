#include <iostream>  // For input and output functionalities
#include <iomanip>   // For controlling the format of output
#include "clsLoginScreen.h"  // Includes the LoginScreen class definition

// Main entry point of the program
int main()
{
    /*
    The main function handles the application's flow.

    To allow users to attempt to log in after logging out, the login screen
    needs to be called in an infinite loop. This ensures that the user
    can continuously attempt to log in until their trials are exhausted
    or they succeed.

    Note: 'LoginTrials' is assumed to be a global or static variable
    declared elsewhere in the code, tracking the remaining login attempts.
    */
    while (LoginTrials > 0)
    {
        clsLoginScreen::ShowLoginScreen();  // Display the login screen
    }

    return 0;  // Program successfully exits
}
