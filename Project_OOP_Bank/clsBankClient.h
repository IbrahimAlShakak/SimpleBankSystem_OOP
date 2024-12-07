#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include <string>    // For string operations
#include "clsPerson.h"  // Base class for person details
#include "clsString.h"  // String utility functions
#include <vector>    // For vector operations
#include <fstream>   // For file operations

using namespace std;

// Class representing a bank client, inheriting from clsPerson
class clsBankClient : public clsPerson
{
private:
    struct stTransferLogRecord;
    // Modes for client operations
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

    enMode _Mode;  // Current mode of the client
    string _AccountNumber;  // Unique account number
    string _PinCode;  // Account PIN code
    float _AccountBalance;  // Current account balance
    bool _MarkForDelete = false;  // Flag for deletion

    // Converts a line from the file to a clsBankClient object
    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        // Create a new clsBankClient object with data from the line
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    // Converts a clsBankClient object to a line for file storage
    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {
        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;
    }

    // Loads all client data from the file into a vector of clsBankClient
    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;
        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);  // Open file in read mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                vClients.push_back(Client);  // Add client to the vector
            }
            MyFile.close();
        }

        return vClients;
    }

    // Saves all client data from a vector back to the file
    static void _SaveCleintsDataToFile(vector<clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);  // Open file in overwrite mode
        string DataLine;

        if (MyFile.is_open())
        {
            for (clsBankClient C : vClients)
            {
                if (C.MarkForDelete() == false)  // Only save clients not marked for deletion
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;  // Write client data to file
                }
            }
            MyFile.close();
        }
    }

    // Updates an existing client in the file
    void _Update()
    {
        vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())  // Find the matching account
            {
                C = *this;  // Update with current object data
                break;
            }
        }

        _SaveCleintsDataToFile(_vClients);  // Save updated data back to file
    }

    // Adds a new client to the file
    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));  // Add new client as a line
    }

    // Adds a single line of data to the file
    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);  // Open file in append mode
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;  // Append client data
            MyFile.close();
        }
    }

    // Returns an empty client object
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);  // Empty values
    }
    // Structure to log transfer details
    

    // Prepares a transfer record string for logging or file storage
    string _PrepareTransferRecord(clsBankClient DestinationClient, double TransferAmount,
        string Username, string Seperator = "#//#")
    {
        string TransferRecord = "";
        TransferRecord += clsDate::GetSystemDateAndTime() + Seperator;  // Add date and time
        TransferRecord += AccountNumber() + Seperator;                 // Add source account number
        TransferRecord += DestinationClient.AccountNumber() + Seperator; // Add destination account number
        TransferRecord += to_string(TransferAmount) + Seperator;       // Add transfer amount
        TransferRecord += to_string(AccountBalance) + Seperator;       // Add source account balance
        TransferRecord += to_string(DestinationClient.AccountBalance) + Seperator; // Add destination balance
        TransferRecord += Username;                                    // Add username
        return TransferRecord;                                         // Return formatted record
    }

    // Converts a transfer log line from the file into a `stTransferLogRecord` structure
    static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTransferLogRecord TransferLogRecord;

        vector<string> vLogData = clsString::Split(Line, Seperator);   // Split the line into components
        TransferLogRecord.DateTime = vLogData[0];
        TransferLogRecord.SourceAN = vLogData[1];
        TransferLogRecord.DestinationAN = vLogData[2];
        TransferLogRecord.TransferAmount = stod(vLogData[3]);
        TransferLogRecord.SourceBalance = stof(vLogData[4]);
        TransferLogRecord.DestinationBalance = stof(vLogData[5]);
        TransferLogRecord.Username = vLogData[6];
        return TransferLogRecord;  // Return the populated log record
    }

public:
    static struct stTransferLogRecord
    {
        string DateTime;             // Date and time of the transfer
        string SourceAN;             // Source account number
        string DestinationAN;        // Destination account number
        string Username;             // Username of the user performing the transfer
        float SourceBalance;         // Source account balance after the transfer
        float DestinationBalance;    // Destination account balance after the transfer
        double TransferAmount;       // Amount transferred
    };
    // Constructor to initialize a clsBankClient object
    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber,
        string PinCode, float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)  // Call base class constructor
    {
        _Mode = Mode;                    // Initialize mode
        _AccountNumber = AccountNumber;  // Initialize account number
        _PinCode = PinCode;              // Initialize PIN code
        _AccountBalance = AccountBalance; // Initialize account balance
    }

    // Check if the client object is empty
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);  // Returns true if mode is empty
    }

    // Get the account number of the client
    string AccountNumber()
    {
        return _AccountNumber;
    }

    // Set and get the PIN code of the client
    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    // Set and get the account balance of the client
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    // Check if the client is marked for deletion
    bool MarkForDelete()
    {
        return _MarkForDelete;
    }

    // Find a client by account number
    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);  // Open file in read mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);  // Convert line to client object
                if (Client.AccountNumber() == AccountNumber)  // Match account number
                {
                    MyFile.close();
                    return Client;  // Return the matched client
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();  // Return an empty client object if not found
    }

    // Find a client by account number and PIN code
    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);  // Open file in read mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);  // Convert line to client object
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)  // Match account and PIN
                {
                    MyFile.close();
                    return Client;  // Return the matched client
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();  // Return an empty client object if not found
    }
    // Enumeration for save results
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    // Saves the client object to the file
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode: // Save fails if the object is in empty mode
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode: // Updates an existing record
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }

        case enMode::AddNewMode: // Adds a new client to the file
        {
            if (clsBankClient::IsClientExist(_AccountNumber)) // Check if the account number exists
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode; // Set mode to update after adding a new client
                return enSaveResults::svSucceeded;
            }
            break;
        }
        }
    }

    // Checks if a client exists based on their account number
    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty()); // Returns true if the client is found
    }

    // Creates a new client object for adding
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    // Deletes a client by marking them for deletion and saving the updated list
    bool Delete()
    {
        vector<clsBankClient> _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber()) // Match account number
            {
                C._MarkForDelete = true; // Mark client for deletion
                break;
            }
        }
        _SaveCleintsDataToFile(_vClients); // Save updated client list
        *this = _GetEmptyClientObject(); // Reset the current object
        return true;
    }

    // Retrieves a list of all clients from the file
    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    // Calculates the total balances of all clients
    static double GetTotalBalances()
    {
        double TotalBalances = 0;
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient& Client : vClients)
        {
            TotalBalances += Client.AccountBalance; // Accumulate balances
        }
        return TotalBalances;
    }

    // Deposits an amount to the client's account and saves the changes
    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    // Withdraws an amount from the client's account if possible
    void Withdraw(double Amount)
    {
        if (IsWithdrawAmountPossible(Amount))
        {
            _AccountBalance -= Amount;
            Save();
        }
    }

    // Checks if the withdrawal amount is possible
    bool IsWithdrawAmountPossible(double Amount)
    {
        return Amount <= _AccountBalance;
    }

    // Registers a transfer in the transfer log
    void RegisterTransfer(clsBankClient DestinationClient, double TransferAmount, string Username)
    {
        string Line = _PrepareTransferRecord(DestinationClient, TransferAmount, Username);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app); // Append mode
        if (MyFile.is_open())
        {
            MyFile << Line << endl; // Write transfer record
            MyFile.close();
        }
    }

    // Retrieves the transfer log as a vector of `stTransferLogRecord`
    static vector<stTransferLogRecord> GetTransferLogList()
    {
        vector<stTransferLogRecord> vTransferLogRecord;
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in); // Read mode

        if (MyFile.is_open())
        {
            string Line;
            stTransferLogRecord TransferLogRecord;

            while (getline(MyFile, Line))
            {
                TransferLogRecord = _ConvertTransferLogLineToRecord(Line, "#//#");
                vTransferLogRecord.push_back(TransferLogRecord); // Add record to the vector
            }

            MyFile.close();
        }

        return vTransferLogRecord;
    }

};

