#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsCurrency.h"  // For managing currency details
#include "clsInputValidate.h"  // For input validation utilities
#include <iomanip>  // For formatting output

using namespace std;

// Class to manage the Find Currency Screen
class clsFindCurrencyScreen : protected clsScreen
{
private:
    // Prints the details of a currency in a formatted "Currency Card"
    static void _Print(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n______________________________________";
        cout << "\nCountry  : " << Currency.Country();         // Currency's country
        cout << "\nCode     : " << Currency.CurrencyCode();    // Currency's code (e.g., USD, EUR)
        cout << "\nName     : " << Currency.CurrencyName();    // Currency's name
        cout << "\nRate(1$) : " << Currency.Rate();            // Exchange rate (relative to 1 USD)
        cout << "\n______________________________________\n";
    }

public:
    // Displays the Find Currency Screen and handles user interactions
    static void ShowFindCurrencyScreen()
    {
        clsScreen::_DrawScreenHeader("\tFind Currency Screen");  // Display the screen header

        // Prompt the user to choose a search method
        cout << "Find By : [1] Code or [2] Country ? ";
        short UserChoice = clsInputValidate::ReadShortNumber();  // Read the user's choice

        // Handle the user's choice
        switch (UserChoice)
        {
        case 1:  // Search by currency code
        {
            cout << "Enter Currency Code: ";
            string UserCurrencyCode = clsInputValidate::ReadString();  // Read the currency code

            // Check if the currency exists
            if (clsCurrency::IsCurrencyExist(UserCurrencyCode))
            {
                cout << "\nCurrency Found :-)" << endl;

                // Find and display the currency details
                clsCurrency Currency = clsCurrency::FindByCurrencyCode(UserCurrencyCode);
                _Print(Currency);
            }
            else
            {
                cout << "\nCurrency Was not Found :-(\n";  // Display an error message
            }
            break;
        }
        case 2:  // Search by country
        {
            cout << "Enter Country: ";
            string UserInputCountry = clsInputValidate::ReadString();  // Read the country name

            // Find the currency associated with the country
            clsCurrency Currency = clsCurrency::FindByCountry(UserInputCountry);

            // Check if the currency object is not empty
            if (!Currency.IsEmpty())
            {
                cout << "Currency Found :-)" << endl;

                _Print(Currency);  // Display the currency details
            }
            else
            {
                cout << "\nCurrency Was not Found :-(\n";  // Display an error message
            }
            break;
        }
        default:
            cout << "\nInvalid choice. Please try again.\n";  // Handle invalid input
            break;
        }
    }
};
