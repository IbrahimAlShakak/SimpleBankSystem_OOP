#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsCurrency.h"  // For managing currency details
#include "clsInputValidate.h"  // For validating user input

using namespace std;

// Class to manage the Currency Calculator Screen
class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
    // Reads the amount to be exchanged from the user
    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = clsInputValidate::ReadFloatNumber();  // Validates and reads a float value
        return Amount;
    }

    // Prompts the user to input a currency code and retrieves the corresponding currency object
    static clsCurrency _GetCurrency(string Message)
    {
        string CurrencyCode;
        cout << Message << endl;

        CurrencyCode = clsInputValidate::ReadString();  // Reads the input as a string

        // Keep prompting until a valid currency code is entered
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        // Find and return the corresponding currency object
        clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
        return Currency;
    }

    // Prints the details of a currency in a formatted "Currency Card"
    static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {
        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country();         // Print country
        cout << "\nCode          : " << Currency.CurrencyCode();   // Print currency code
        cout << "\nName          : " << Currency.CurrencyName();   // Print currency name
        cout << "\nRate(1$) =    : " << Currency.Rate();           // Print exchange rate
        cout << "\n_____________________________\n\n";
    }

    // Prints the results of the currency conversion calculations
    static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {
        _PrintCurrencyCard(Currency1, "Convert From:");  // Print details of the source currency

        float AmountInUSD = Currency1.ConvertToUSD(Amount);  // Convert the amount to USD

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " USD\n";  // Display the USD equivalent

        // If the target currency is USD, stop further calculations
        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");  // Print details of the target currency

        float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);  // Convert USD to target currency

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();  // Display the converted amount
    }

public:
    // Displays the Currency Calculator Screen and handles user interactions
    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        // Loop to allow multiple conversions
        while (tolower(Continue) == 'y')
        {
            system("cls");  // Clear the console

            _DrawScreenHeader("\tCurrency Calculator Screen");  // Display screen header

            // Get the source and target currencies
            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");

            // Read the amount to convert
            float Amount = _ReadAmount();

            // Print the calculation results
            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            // Ask if the user wants to perform another calculation
            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;
        }
    }
};
