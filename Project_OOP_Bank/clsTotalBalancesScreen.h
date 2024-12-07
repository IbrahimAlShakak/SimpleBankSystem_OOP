#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsInputValidate.h"  // For input validation utilities
#include "clsBankClient.h"  // For managing bank client details
#include "clsUtil.h"  // For utility functions like number to text conversion

using namespace std;

// Class to manage the Total Balances Screen
class clsTotalBalancesScreen : protected clsScreen
{
private:
    // Prints a single client's record with their balance in a formatted line
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber();  // Account number
        cout << "| " << setw(40) << left << Client.FullName();        // Full name
        cout << "| " << setw(12) << left << Client.AccountBalance;    // Account balance
    }

public:
    // Displays the Total Balances Screen and handles listing and summing balances
    static void ShowTotalBalancesScreen()
    {
        // Retrieve the list of all clients
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        // Set the screen title and subtitle
        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);  // Draw the screen header

        // Print the table header
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(25) << left << "" << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        // Calculate the total balances across all clients
        double TotalBalances = clsBankClient::GetTotalBalances();

        // Check if there are no clients in the system
        if (vClients.empty())
        {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
        {
            // Print each client's details in the table
            for (clsBankClient Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }
        }

        // Print the table footer
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        // Display the total balances and its textual representation
        cout << setw(8) << left << "" << "\t\t\t\t\t     Total Balances = " << TotalBalances << endl;
        cout << setw(8) << left << "" << "\t\t\t\t  ( " << clsUtil::NumberToText(TotalBalances) << ")";
    }
};
