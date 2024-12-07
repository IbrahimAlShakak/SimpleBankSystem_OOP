#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include <fstream>   // For file operations
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsUser.h"  // For managing user details
#include "clsMainScreen.h"  // Reference to the main screen
#include "clsInputValidate.h"  // For input validation utilities
#include "Global.h"  // Global settings and constants

using namespace std;

// Class to manage the Transfer Log Screen
class clsTransferLogScreen : protected clsScreen
{
private:
    // Prints a single transfer log record in a formatted line
    static void _PrintTransferLogLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferLogRecord.DateTime;       // Date/Time of the transfer
        cout << "| " << setw(7) << left << TransferLogRecord.SourceAN;        // Source account number
        cout << "| " << setw(7) << left << TransferLogRecord.DestinationAN;   // Destination account number
        cout << "| " << setw(10) << left << TransferLogRecord.TransferAmount; // Transfer amount
        cout << "| " << setw(13) << left << TransferLogRecord.SourceBalance;  // Source account balance
        cout << "| " << setw(13) << left << TransferLogRecord.DestinationBalance;  // Destination account balance
        cout << "| " << setw(8) << left << TransferLogRecord.Username;        // User who performed the transfer
    }

public:
    // Displays the Transfer Log Screen and handles the listing of transfer logs
    static void ShowTransferLogScreen()
    {
        // Retrieve the list of transfer log records
        vector<clsBankClient::stTransferLogRecord> vTransferLogRecord =
            clsBankClient::GetTransferLogList();

        // Set the screen title and subtitle
        string Title = "\t  Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);  // Draw the screen header

        // Print the table header
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(7) << "S. Acc";          // Source account
        cout << "| " << left << setw(7) << "D. Acc";          // Destination account
        cout << "| " << left << setw(10) << "Amount";         // Transfer amount
        cout << "| " << left << setw(13) << "S. Balance";     // Source balance
        cout << "| " << left << setw(13) << "D. Balance";     // Destination balance
        cout << "| " << left << setw(8) << "User";            // User
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        // Check if there are no logs in the system
        if (vTransferLogRecord.empty())
        {
            cout << "\t\t\t\tNo Logs Available In the System!";
        }
        else
        {
            // Print each transfer log record in the table
            for (clsBankClient::stTransferLogRecord TransferLogRecord : vTransferLogRecord)
            {
                _PrintTransferLogLine(TransferLogRecord);
                cout << endl;
            }
        }

        // Print the table footer
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
