#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsCurrency.h"  // For managing currency details
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>   // For formatting output

using namespace std;

// Class to manage the Update Currency Screen
class clsUpdateCurrencyScreen : protected clsScreen
{
private:
    // Prints the details of a currency in a formatted "Currency Card"
    static void _Print(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n______________________________________";
        cout << "\nCountry  : " << Currency.Country();        // Country name
        cout << "\nCode     : " << Currency.CurrencyCode();   // Currency code
        cout << "\nName     : " << Currency.CurrencyName();   // Currency name
        cout << "\nRate(1$) : " << Currency.Rate();           // Exchange rate for 1 USD
        cout << "\n______________________________________\n";
    }

public:
    // Displays the Update Currency Screen and handles the update process
    static void ShowUpdateCurrencyScreen()
    {
        clsScreen::_DrawScreenHeader("\t Update Currency Screen");  // Draw the screen header

        // Prompt the user to enter a country name
        cout << "Enter Country: ";
        string UserInputCountry = clsInputValidate::ReadString();

        // Retrieve the currency object for the entered country
        clsCurrency Currency = clsCurrency::FindByCountry(UserInputCountry);

        // Print the current details of the selected currency
        _Print(Currency);

        // Confirm if the user wants to update the currency rate
        char UserChoice = 'n';
        cout << "Are you sure you want to update this country rate? (Y/N): ";
        cin >> UserChoice;

        if (tolower(UserChoice) == 'y')  // Proceed if the user confirms
        {
            float NewRate = 0;

            // Prompt the user to enter the new exchange rate
            cout << "Enter New Rate: ";
            cin >> NewRate;

            // Update the currency's exchange rate
            Currency.SetRate(NewRate);

            // Notify the user of the successful update and display the updated details
            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _Print(Currency);
        }
        else
        {
            cout << "\nUpdate Operation Canceled.\n";
        }
    }
};
