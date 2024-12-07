# Bank Management System

A comprehensive C++ project for managing a bank's operations, including clients, users, transactions, and currency exchanges. This project is an upgrade of the [Simple Bank System](https://github.com/IbrahimAlShakak/SimpleBankSystem.git) by Ibrahim AlShakak, adding advanced features like money transfers between client accounts and a login log record to monitor user activity.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Added Features](#added-features)
- [Technologies Used](#technologies-used)
- [File Structure](#file-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Screenshots](#screenshots)
- [Future Improvements](#future-improvements)
- [Contributing](#contributing)
- [License](#license)

## Overview
This project simulates a bank's management system with functionalities like adding, updating, deleting, and searching for clients and users. It also supports transactions such as deposits, withdrawals, and money transfers. Additionally, the project includes a currency exchange module.

## Features
- **Client Management:**
  - Add, update, delete, and search clients.
  - Display a list of all clients with their details.
- **User Management:**
  - Add, update, delete, and search users.
  - Assign and manage user permissions.
- **Transaction Management:**
  - Perform deposits, withdrawals, and transfers between accounts.
  - View transaction logs.
- **Currency Exchange:**
  - List available currencies.
  - Update currency rates.
  - Convert between currencies.
- **Authentication:**
  - Login system with username and password.
  - Limited login attempts with tracking.

## Added Features
This project builds on the foundation of the [Simple Bank System](https://github.com/IbrahimAlShakak/SimpleBankSystem.git) with the following enhancements:
1. **Transfer Feature**:
   - Enables users to transfer money between client accounts.
   - Tracks transfer history for record-keeping and transparency.
2. **Login Log Record**:
   - Monitors user login activities.
   - Stores login details (date, time, username, permissions) in a log file for auditing purposes.

## Technologies Used
- **Programming Language:** C++
- **Development Environment:** Visual Studio
- **Core Concepts:**
  - Object-Oriented Programming (OOP)
  - File Handling
  - Modular Design
  - Input Validation
  - Role-based Access Control

## File Structure
BankManagementSystem/ ├── Priject_OOP_Bank.cpp # Main entry point ├── clsAddNewClientScreen.h # Add new client functionality ├── clsAddNewUserScreen.h # Add new user functionality ├── clsBankClient.h # Bank client management ├── clsClientListScreen.h # List all clients ├── clsCurrenciesListScreen.h # List all currencies ├── clsCurrency.h # Currency management ├── clsCurrencyCalculatorScreen.h # Currency calculator ├── clsCurrencyExchangeScreen.h # Currency exchange menu ├── clsDeleteClientScreen.h # Delete client functionality ├── clsDeleteUserScreen.h # Delete user functionality ├── clsDepositScreen.h # Deposit transaction ├── clsFindClientScreen.h # Find a client ├── clsFindCurrencyScreen.h # Find a currency ├── clsFindUserScreen.h # Find a user ├── clsInputValidate.h # Input validation utilities ├── clsListUsersScreen.h # List all users ├── clsLoginRegisterScreen.h # View login register ├── clsLoginScreen.h # Login functionality ├── clsMainScreen.h # Main menu ├── clsManageUsersScreen.h # User management menu ├── clsScreen.h # Base screen functionalities ├── clsTotalBalancesScreen.h # Total balances report ├── clsTransactionsScreen.h # Transactions menu ├── clsTransferLogScreen.h # Transfer logs ├── clsTransferScreen.h # Money transfer ├── clsUpdateClientScreen.h # Update client details ├── clsUpdateCurrencyScreen.h # Update currency rates ├── clsUpdateUserScreen.h # Update user details ├── clsWithdrawScreen.h # Withdraw transaction ├── clsString.h # String utilities ├── clsDate.h # Date utilities ├── Global.h # Global variables


## Getting Started
### Prerequisites
- Visual Studio (or any other C++ IDE)
- Basic knowledge of C++

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/BankManagementSystem.git

2. Open the project in Visual Studio.
3. Build the solution to ensure all dependencies are compiled.
4. Run the project.

### Data Files

Ensure the following text files are in the same directory as the executable:

* Clients.txt: Stores client data.
* Users.txt: Stores user data.
* LoginRegister.txt: Stores login activity logs.
* TransferLog.txt: Stores transfer transaction logs.
* Currencies.txt: Stores currency data.

### Usage

1. Launch the application.
2. Log in with a valid username and password.
3. Navigate through the menu to perform various operations:
* Manage clients and users.
* Perform transactions, including money transfers.
* Monitor login activities.
* Exchange currencies.

### Screenshots

Add screenshots of your application here to showcase its features.

## Future Improvements

* Implement a graphical user interface (GUI).
* Add support for database integration instead of file handling.
* Include additional user roles and permissions.
* Enhance security with password hashing.

## Contributing

Contributions are welcome! If you have suggestions for improvements, please create a pull request or open an issue.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.

### Summary of Changes:
1. Added a reference to the original project ([Simple Bank System](https://github.com/IbrahimAlShakak/SimpleBankSystem.git)) under the **Overview** and **Added Features** sections.
2. Detailed the two new features:
   - Transfer Feature
   - Login Log Record
3. Updated the **Usage** section to include these new functionalities.

Feel free to add screenshots or a `LICENSE` file for completeness. Let me know if you need further edits!
