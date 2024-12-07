#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>
#include "Global.h"
#include "clsBankClient.h"
#include "clsUser.h"

using namespace std;

class clsUser : public clsPerson
{
private:
    // Enumeration to define the mode of the user object (Empty, Update, AddNew)
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

    enMode _Mode;            // Mode of the user object
    string _Username;        // User's unique username
    string _Password;        // User's encrypted password
    int _Permissions;        // Permissions assigned to the user
    bool _MarkForDelete = false;  // Flag to mark a user for deletion

    // Structure to store login register record details
    struct stLoginRegisterRecord;

    // Converts a line from the data file to a `clsUser` object
    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData = clsString::Split(Line, Seperator);

        // Create a user object with data from the file
        return clsUser(
            enMode::UpdateMode,           // Mode is set to Update
            vUserData[0],                 // First name
            vUserData[1],                 // Last name
            vUserData[2],                 // Email
            vUserData[3],                 // Phone
            vUserData[4],                 // Username
            DecryptText(vUserData[5]),    // Decrypted password
            stoi(vUserData[6])            // Permissions
        );
    }

    // Converts a `clsUser` object to a line for the data file
    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string stUserRecord = "";
        stUserRecord += User.FirstName + Seperator;
        stUserRecord += User.LastName + Seperator;
        stUserRecord += User.Email + Seperator;
        stUserRecord += User.Phone + Seperator;
        stUserRecord += User.Username + Seperator;
        stUserRecord += EncryptText(User.Password) + Seperator;
        stUserRecord += to_string(User.Permissions);
        return stUserRecord;
    }

    // Returns an empty `clsUser` object
    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    // Loads user data from the file into a vector
    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> vUsers;
        fstream MyFile("Users.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                vUsers.push_back(User);
            }

            MyFile.close();
        }

        return vUsers;
    }

    // Saves user data from a vector to the file
    static void _SaveUsersDataToFile(vector<clsUser> vUsers)
    {
        fstream MyFile("Users.txt", ios::out);  // Overwrite mode
        if (MyFile.is_open())
        {
            for (clsUser U : vUsers)
            {
                if (!U.MarkForDelete())  // Skip users marked for deletion
                {
                    string DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    // Updates an existing user record in the file
    void _Update()
    {
        vector<clsUser> _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.GetUsername() == GetUsername())  // Match by username
            {
                U = *this;  // Update with current object data
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);  // Save updated data to the file
    }

    // Adds a new user record to the file
    void _AddNew()
    {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));  // Append the new user
    }

    // Appends a new data line to the file
    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile("Users.txt", ios::out | ios::app);  // Append mode
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    // Prepares a login record for logging purposes
    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LogLineRecord = "";
        LogLineRecord += clsDate::GetSystemDateAndTime() + Seperator;  // Date and time of login
        LogLineRecord += Username + Seperator;                        // Username
        LogLineRecord += EncryptText(Password) + Seperator;           // Encrypted password
        LogLineRecord += to_string(Permissions);                      // Permissions
        return LogLineRecord;
    }

    // Converts a login register line from the file to a record object
    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;
        vector<string> vLoginData = clsString::Split(Line, Seperator);

        LoginRegisterRecord.DateTime = vLoginData[0];
        LoginRegisterRecord.Username = vLoginData[1];
        LoginRegisterRecord.Password = DecryptText(vLoginData[2]);
        LoginRegisterRecord.Permissions = stoi(vLoginData[3]);

        return LoginRegisterRecord;
    }

    
public:
    enum enPermissions
    {
        eAll = -1, pListClients = 1, pAddNewClient = 2,pDeleteClient = 4, 
        pUpdateClient = 8, pFindClinet = 16, pTransactions = 32, pManageUsers = 64,
        pLoginRegisterList = 128, pCurrencyExchange = 256
    };
    
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string Username, string Password, int Permissions)
        : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _Username = Username;
        _Password = Password;
        _Permissions = Permissions;
    }

    // Structure to store login register details
    struct stLoginRegisterRecord
    {
        string DateTime;   // Date and time of login
        string Username;   // Username of the user
        string Password;   // Password used for login
        int Permissions;   // Permissions assigned to the user
    };

    // Getter and setter for Username
    string GetUsername() { return _Username; }
    void SetUsername(string Username) { _Username = Username; }
    __declspec(property(get = GetUsername, put = SetUsername)) string Username;

    // Getter and setter for Password
    void SetPassword(string Password) { _Password = Password; }
    string GetPassword() { return _Password; }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    // Getter and setter for Permissions
    void SetPermissions(int Permissions) { _Permissions = Permissions; }
    int GetPermissions() { return _Permissions; }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    // Checks if a user is marked for deletion
    bool MarkForDelete() { return _MarkForDelete; }

    // Checks if the user has a specific permission
    bool HasPermission(enPermissions Permission)
    {
        return (_Permissions == enPermissions::eAll || (_Permissions & Permission) != 0);
    }

    // Finds a user by username
    static clsUser Find(string Username)
    {
        fstream MyFile("Users.txt", ios::in); // Read mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.Username == Username)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    // Finds a user by username and password
    static clsUser Find(string Username, string Password)
    {
        fstream MyFile("Users.txt", ios::in); // Read mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.Username == Username && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    // Checks if the user object is empty
    bool IsEmpty() { return (_Mode == enMode::EmptyMode); }

    // Checks if a user exists by username
    static bool IsUserExist(string Username)
    {
        clsUser User = clsUser::Find(Username);
        return (!User.IsEmpty());
    }

    // Save results enumeration
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    // Saves the user object (either updates or adds a new record)
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return IsEmpty() ? enSaveResults::svFaildEmptyObject : enSaveResults::svSucceeded;
        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSucceeded;
        case enMode::AddNewMode:
            if (clsUser::IsUserExist(_Username))
                return enSaveResults::svFaildAccountNumberExists;
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode; // Change mode to update after adding new
                return enSaveResults::svSucceeded;
            }
        }
        return enSaveResults::svFaildEmptyObject; // Default case
    }

    // Deletes the user
    bool Delete()
    {
        vector<clsUser> _vUsers = _LoadUsersDataFromFile();
        for (clsUser& U : _vUsers)
        {
            if (U.Username == GetUsername())
            {
                U._MarkForDelete = true;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyUserObject();
        return true;
    }

    // Creates a new user object for adding
    static clsUser GetAddNewUserObject(string Username)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
    }

    // Retrieves the list of all users
    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    // Checks if the user has the required access permission
    bool CheckAccessPermission(clsUser::enPermissions Permissions)
    {
        if (this->Permissions == clsUser::enPermissions::eAll)
            return true;
        return ((this->Permissions & Permissions) == Permissions);
    }

    // Registers the user's login details to a log file
    void RegisterLogin()
    {
        string Line = _PrepareLogInRecord();
        fstream MyFile("LoginRegister.txt", ios::out | ios::app); // Append mode
        if (MyFile.is_open())
        {
            MyFile << Line << endl;
            MyFile.close();
        }
    }

    // Retrieves the login register list from the log file
    static vector<stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector<stLoginRegisterRecord> vLoginRegisterRecord;
        fstream MyFile("LoginRegister.txt", ios::in); // Read mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                stLoginRegisterRecord LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line, "#//#");
                vLoginRegisterRecord.push_back(LoginRegisterRecord);
            }
            MyFile.close();
        }

        return vLoginRegisterRecord;
    }

    // Encrypts text using a simple Caesar cipher
    static string EncryptText(string Text, int Key = 9)
    {
        string EncryptedText = "";
        for (int i = 0; i < Text.size(); i++)
        {
            EncryptedText += char((int)Text[i] + Key);
        }
        return EncryptedText;
    }

    // Decrypts text using a simple Caesar cipher
    static string DecryptText(string Text, int Key = 9)
    {
        string DecryptedText = "";
        for (int i = 0; i < Text.size(); i++)
        {
            DecryptedText += char((int)Text[i] - Key);
        }
        return DecryptedText;
    }

};




