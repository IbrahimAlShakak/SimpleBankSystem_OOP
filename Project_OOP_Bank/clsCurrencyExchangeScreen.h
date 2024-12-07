#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsInputValidate.h"  // For validating user input
#include "clsCurrenciesListScreen.h"  // For listing currencies
#include "clsFindCurrencyScreen.h"  // For finding a specific currency
#include "clsUpdateCurrencyScreen.h"  // For updating currency rates
#include "clsCurrencyCalculatorScreen.h"  // For currency conversion calculations

using namespace std;

// Class to manage the Currency Exchange Menu Screen
class clsCurrencyExchangeScreen : protected clsScreen
{
private:
    // Enum for menu options in the currency exchange screen
    enum enCurrencyExchangeMenueOptions {
        eListCurrencies = 1,  // Option to list currencies
        eFindCurrency = 2,    // Option to find a currency
        eUpdateRate = 3,      // Option to update a currency's exchange rate
        eCurrencyCalculator = 4,  // Option to use the currency calculator
        eMainMenu = 5         // Option to return to the main menu
    };

    // Reads the user's menu option choice
    static short _ReadCurrencyExchangeMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    // Prompts the user to go back to the currency exchange menu
    static void _GoBackToCurrencyExchangeMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Exchange Menue...\n";
        system("pause>0");  // Wait for user input
        ShowCurrencyExchangeMenueScreen();  // Show the menu again
    }

    // Displays the list currencies screen
    static void _ShowListCurrenciesScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    // Displays the find currency screen
    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    // Displays the update currency rate screen
    static void _ShowUpdateRateScreen()
    {
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }

    // Displays the currency calculator screen
    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    // Executes the selected menu option
    static void _PerfromCurrencyExchangeMenueOption(enCurrencyExchangeMenueOptions CurrencyExchangeMenueOption)
    {
        switch (CurrencyExchangeMenueOption)
        {
        case enCurrencyExchangeMenueOptions::eListCurrencies:
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOptions::eUpdateRate:
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOptions::eMainMenu:
            // Placeholder for returning to the main menu (avoiding circular reference)
            // clsMainScreen::ShowMainMenue();  // Uncomment if `clsMainScreen` is implemented
            break;
        }
    }

public:
    // Displays the Currency Exchange Menu Screen
    static void ShowCurrencyExchangeMenueScreen()
    {
        // Check if the user has the required permissions
        if (!CheckAccessRights(clsUser::enPermissions::pCurrencyExchange))
            return;

        system("cls");  // Clear the console
        _DrawScreenHeader("\t\t Currency Exchange Main Screen");  // Display screen header

        // Display menu options
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\Currency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        // Perform the selected menu option
        _PerfromCurrencyExchangeMenueOption((enCurrencyExchangeMenueOptions)_ReadCurrencyExchangeMenueOption());
    }
};
