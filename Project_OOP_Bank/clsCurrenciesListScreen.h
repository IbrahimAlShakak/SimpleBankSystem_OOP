#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsCurrency.h"  // For managing currency details
#include <iomanip>  // For formatting output

using namespace std;

// Class to manage the Currencies List Screen
class clsCurrenciesListScreen : protected clsScreen
{
private:
    // Prints a single currency record in a formatted line
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();  // Country name
        cout << "| " << setw(8) << left << Currency.CurrencyCode();  // Currency code
        cout << "| " << setw(45) << left << Currency.CurrencyName();  // Currency name
        cout << "| " << setw(10) << left << Currency.Rate();  // Exchange rate (rate per 1 USD)
    }

public:
    // Displays the Currencies List Screen
    static void ShowCurrenciesListScreen()
    {
        // Retrieve the list of all currencies
        vector<clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();

        // Set screen title and subtitle
        string Title = "\t  Currencies List Screen";
        string SubTitle = "\t    (" + to_string(vCurrencys.size()) + ") Currency.";

        _DrawScreenHeader(Title, SubTitle);  // Draw the screen header

        // Print table header
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        // Check if there are no currencies in the system
        if (vCurrencys.empty())
        {
            cout << "\t\t\t\tNo Currencies Available In the System!";
        }
        else
        {
            // Print each currency's details in the table
            for (clsCurrency Currency : vCurrencys)
            {
                PrintCurrencyRecordLine(Currency);
                cout << endl;
            }
        }

        // Print table footer
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;
    }
};
