#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsClientListScreen.h"  // For listing clients
#include "clsInputValidate.h"  // For input validation utilities
#include "clsAddNewClientScreen.h"  // For adding new clients
#include "clsDeleteClientScreen.h"  // For deleting clients
#include "clsUpdateClientScreen.h"  // For updating client information
#include "clsFindClientScreen.h"  // For finding clients
#include "clsTransactionsScreen.h"  // For managing transactions
#include "clsManageUsersScreen.h"  // For managing users
#include "Global.h"  // Global settings and constants
#include "clsUser.h"  // For managing user details
#include "clsLoginRegisterScreen.h"  // For showing login/register records
#include "clsCurrencyExchangeScreen.h"  // For currency exchange operations

using namespace std;

// Class to manage the Main Screen menu
class clsMainScreen : protected clsScreen
{
private:
    // Enum for main menu options
    enum enMainMenueOptions {
        eListClients = 1,  // Show client list
        eAddNewClient = 2,  // Add new client
        eDeleteClient = 3,  // Delete client
        eUpdateClient = 4,  // Update client information
        eFindClient = 5,  // Find a client
        eShowTransactionsMenue = 6,  // Show transactions menu
        eManageUsers = 7,  // Manage users
        eLoginRegisterList = 8,  // Show login register list
        eCurrencyExchange = 9,  // Currency exchange
        eExit = 10  // Logout
    };

    // Reads and validates the user's menu option choice
    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        return clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number between 1 to 10? ");
    }

    // Prompts the user to go back to the main menu
    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMenue();  // Show the main menu again
    }

    // Displays various screens based on the menu selection
    static void _ShowAllClientsScreen() { clsClientListScreen::ShowClientsListScreen(); }
    static void _ShowAddNewClientsScreen() { clsAddNewClientScreen::ShowAddNewClientScreen(); }
    static void _ShowDeleteClientScreen() { clsDeleteClientScreen::ShowDeleteClientScreen(); }
    static void _ShowUpdateClientScreen() { clsUpdateClientScreen::ShowUpdateClientScreen(); }
    static void _ShowFindClientScreen() { clsFindClientScreen::ShowFindClientScreen(); }
    static void _ShowTransactionsMenue() { clsTransactionsScreen::ShowTransactionsMenue(); }
    static void _ShowManageUsersMenue() { clsManageUsersScreen::ShowUsersMenue(); }
    static void _ShowLoginRegisterScreen() { clsLoginRegisterScreen::ShowLoginRegisterListScreen(); }
    static void _ShowCurrencyExchangeScreen() { clsCurrencyExchangeScreen::ShowCurrencyExchangeMenueScreen(); }

    // Logs out the current user
    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");  // Clear the current user
    }

    // Executes the selected main menu option
    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;

        case eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case eLoginRegisterList:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;

        case eCurrencyExchange:
            system("cls");
            _ShowCurrencyExchangeScreen();
            _GoBackToMainMenue();
            break;

        case eExit:
            system("cls");
            _Logout();
            break;
        }
    }

public:
    // Displays the Main Menu and handles user navigation
    static void ShowMainMenue()
    {
        system("cls");  // Clear the console
        _DrawScreenHeader("\t\tMain Screen");  // Display the screen header

        // Print the main menu options
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Show Login Register List.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());  // Execute the selected option
    }
};
