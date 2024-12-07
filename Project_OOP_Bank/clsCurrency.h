#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <fstream>   // For file operations
#include <vector>    // For using vectors
#include <string>    // For string operations
#include "clsString.h"  // Utility class for string manipulations

using namespace std;

// Class representing a currency
class clsCurrency
{
private:
    // Enumeration for the operational mode of the currency object
    enum enMode { EmptyMode = 0, UpdateMode = 1 };

    enMode _Mode;           // Mode of the currency object (empty or update)
    string _Country;        // Country associated with the currency
    string _CurrencyCode;   // Currency code (e.g., USD, EUR)
    string _CurrencyName;   // Name of the currency (e.g., Dollar, Euro)
    float _Rate;            // Exchange rate of the currency (relative to 1 USD)

    // Converts a line of data into a `clsCurrency` object
    static clsCurrency _ConvertLineToCurrencyObject(string Line)
    {
        vector<string> vDataLine = clsString::Split(Line, "#//#");  // Split the line into components

        // Return a `clsCurrency` object initialized with the data
        return clsCurrency(enMode::UpdateMode, vDataLine[0], vDataLine[1], vDataLine[2], stof(vDataLine[3]));
    }

    // Converts a `clsCurrency` object to a line for file storage
    static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
    {
        string Line = "";
        Line += Currency.Country() + Seperator;        // Add country
        Line += Currency.CurrencyCode() + Seperator;   // Add currency code
        Line += Currency.CurrencyName() + Seperator;   // Add currency name
        Line += to_string(Currency.Rate());            // Add exchange rate
        return Line;
    }

    // Loads all currencies from the file into a vector
    static vector<clsCurrency> _LoadCurrencyFromFile()
    {
        vector<clsCurrency> vCurrencies;  // Vector to store currencies
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);  // Open the file in read mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))  // Read each line
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);  // Convert line to currency object
                vCurrencies.push_back(Currency);  // Add to vector
            }
            MyFile.close();  // Close the file
        }

        return vCurrencies;  // Return the list of currencies
    }

    // Returns an empty currency object
    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

    // Saves all currencies in the vector back to the file
    static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencies)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);  // Open the file in overwrite mode
        if (MyFile.is_open())
        {
            for (clsCurrency& Currency : vCurrencies)  // Write each currency as a line
            {
                string Line = _ConvertCurrencyObjectToLine(Currency);
                MyFile << Line << endl;
            }
            MyFile.close();  // Close the file
        }
    }

    // Updates the currency object in the file
    void _Update()
    {
        vector<clsCurrency> vCurrencies = _LoadCurrencyFromFile();  // Load existing currencies

        for (clsCurrency& Currency : vCurrencies)  // Find the matching currency code
        {
            if (Currency.CurrencyCode() == CurrencyCode())
            {
                Currency = *this;  // Update with current object data
                break;
            }
        }

        _SaveCurrencyDataToFile(vCurrencies);  // Save updated currencies back to the file
    }

public:
    // Constructor to initialize a `clsCurrency` object
    clsCurrency(enMode Mode, string Country, string CurrencyCode,
        string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    // Getter for country
    string Country()
    {
        return _Country;
    }

    // Getter for currency code
    string CurrencyCode()
    {
        return _CurrencyCode;
    }

    // Getter for currency name
    string CurrencyName()
    {
        return _CurrencyName;
    }

    // Getter for exchange rate
    float Rate()
    {
        return _Rate;
    }

    // Setter for exchange rate
    void SetRate(float Rate)
    {
        _Rate = Rate;
        _Update();  // Update the currency in the file after modifying the rate
    }

    // Checks if the currency object is empty
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    // Finds a currency by its currency code
    static clsCurrency FindByCurrencyCode(string CurrencyCode)
    {
        CurrencyCode = clsString::UpperAllString(CurrencyCode);  // Convert to uppercase for case-insensitive comparison

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);  // Open the file in read mode

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))  // Read each line
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);  // Convert line to a currency object
                if (CurrencyCode == Currency.CurrencyCode())  // Compare currency code
                {
                    MyFile.close();  // Close the file
                    return Currency;  // Return the matching currency object
                }
            }
            MyFile.close();  // Close the file
        }

        return _GetEmptyCurrencyObject();  // Return an empty object if not found
    }

    // Finds a currency by its associated country
    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);  // Convert to uppercase for case-insensitive comparison

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);  // Open the file in read mode

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))  // Read each line
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);  // Convert line to a currency object
                if (Country == clsString::UpperAllString(Currency.Country()))  // Compare country names
                {
                    MyFile.close();  // Close the file
                    return Currency;  // Return the matching currency object
                }
            }
            MyFile.close();  // Close the file
        }
        return _GetEmptyCurrencyObject();  // Return an empty object if not found
    }

    // Checks if a currency exists based on its currency code
    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency Currency = FindByCurrencyCode(CurrencyCode);  // Attempt to find the currency
        return (!Currency.IsEmpty());  // Return true if the currency exists
    }

    // Retrieves the list of all currencies
    static vector<clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencyFromFile();  // Load currencies from the file and return the list
    }

    // Converts a specified amount in this currency to USD
    float ConvertToUSD(float Amount)
    {
        return (float)(Amount / Rate());  // Divide the amount by the exchange rate
    }

    // Converts a specified amount in this currency to another currency
    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);  // First, convert the amount to USD

        if (Currency2.CurrencyCode() == "USD")  // If the target currency is USD, return the amount in USD
        {
            return AmountInUSD;
        }

        return (float)(AmountInUSD * Currency2.Rate());  // Multiply the USD amount by the target currency's rate
    }

};

