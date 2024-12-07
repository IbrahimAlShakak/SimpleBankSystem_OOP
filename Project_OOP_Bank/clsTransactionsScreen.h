#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <iomanip>   // For formatting output
#include "clsScreen.h"  // Base class for screen functionalities
#include "clsInputValidate.h"  // For input validation utilities
#include "clsDepositScreen.h"  // For deposit transactions
#include "clsWithdrawScreen.h"  // For withdrawal transactions
#include "clsTotalBalancesScreen.h"  // For viewing total balances
#include "clsTransferScreen.h"  // For money transfers
#include "clsTransferLogScreen.h"  // For viewing transfer logs

using namespace std;

// Class to manage the Transactions Menu Screen
class clsTransactionsScreen : protected clsScreen
{
private:
    // Enum for transactions menu options
    enum enTransactionsMenueOptions {
        eDeposit = 1,        // Deposit money
        eWithdraw = 2,       // Withdraw money
        eTotalBalances = 3,  // View total balances
        eTransfer = 4,       // Transfer money
        eTransferLog = 5,    // View transfer log
        eMainMenu = 6        // Return to the main menu
    };

    // Reads and validates the user's menu option choice
    static short _ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        return clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
    }

    // Prompts the user to go back to the transactions menu
    static void _GoBackToTransactionsMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";
        system("pause>0");
        ShowTransactionsMenue();  // Show the transactions menu again
    }

    // Displays the various transaction-related screens
    static void _ShowDepositScreen() { clsDepositScreen::ShowDepositScreen(); }
    static void _ShowWithdrawScreen() { clsWithdrawScreen::ShowWithdrawScreen(); }
    static void _ShowTotalBalancesScreen() { clsTotalBalancesScreen::ShowTotalBalancesScreen(); }
    static void _ShowTransferScreen() { clsTransferScreen::ShowTransferScreen(); }
    static void _ShowTransferLogScreen() { clsTransferLogScreen::ShowTransferLogScreen(); }

    // Executes the selected transactions menu option
    static void _PerfromTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;

        case eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;

        case eTotalBalances:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;

        case eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;

        case eTransferLog:
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;

        case eMainMenu:
            // Placeholder for navigating back to the main menu
            // clsMainScreen::ShowMainMenue(); 
            break;
        }
    }

public:
    // Displays the Transactions Menu and handles user navigation
    static void ShowTransactionsMenue()
    {
        // Check if the user has the required permissions
        if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
            return;

        system("cls");  // Clear the console
        _DrawScreenHeader("\t\Transactions Screen");  // Display the screen header

        // Print the transactions menu options
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        // Execute the selected option
        _PerfromTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
    }
};
