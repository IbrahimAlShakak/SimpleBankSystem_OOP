#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsBankClient.h"  // For managing bank clients
#include <iomanip>  // For formatting output
#include "Global.h"  // Global settings and constants
#include "clsUser.h"  // For user permissions and details

using namespace std;

// Class to manage the Client List Screen
class clsClientListScreen : protected clsScreen
{
private:
    // Prints a single client's record in a formatted line
    static void _PrintClientRecordLine(clsBankClient Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();  // Account number
        cout << "| " << setw(20) << left << Client.FullName();  // Full name
        cout << "| " << setw(12) << left << Client.Phone;  // Phone number
        cout << "| " << setw(20) << left << Client.Email;  // Email
        cout << "| " << setw(10) << left << Client.PinCode;  // PIN code
        cout << "| " << setw(12) << left << Client.AccountBalance;  // Account balance
    }

public:
    // Displays the client list screen
    static void ShowClientsListScreen()
    {
        // Check if the user has the required permissions
        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
            return; // Exit if the user lacks access rights

        // Retrieve the list of all clients
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        // Set screen title and subtitle
        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);  // Draw the screen header

        // Print table header
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

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
                _PrintClientRecordLine(Client);
                cout << endl;
            }
        }

        // Print table footer
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
