#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include"Global.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;


    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
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

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector <clsBankClient>  _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;

        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

    static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        string DataLine;

        if (MyFile.is_open())
        {
            for (clsBankClient& C : vClients)
            {
                if (C._MarkedForDelete == false)
                {
                    DataLine = _ConvertClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    string _PrepareTransferRecord(float Amount, clsBankClient& DestinationClient, string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += AccountNumber() + Seperator;
        LoginRecord += DestinationClient.AccountNumber() + Seperator;
        LoginRecord += to_string(Amount) + Seperator;
        LoginRecord += to_string(AccountBalance) + Seperator;
        LoginRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        LoginRecord += CurrentUser.UserName;
        return LoginRecord;
    }

    void _RegisterTransfer(float Amount, clsBankClient& DestenationClient)
    {
        string stDataLine = _PrepareTransferRecord(Amount, DestenationClient);
        fstream MyFile;

        MyFile.open("TransferRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }
    struct stTransferRegisterRecord;
    static stTransferRegisterRecord _ConvertTransferRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stTransferRegisterRecord TransferRegisterRecord;


        vector <string> TransferRegisterDataLine = clsString::Split(Line, Seperator);
        TransferRegisterRecord.DateTime = TransferRegisterDataLine[0];
        TransferRegisterRecord.SourceAccountNumber = TransferRegisterDataLine[1];
        TransferRegisterRecord.DestenationAccountNumber = TransferRegisterDataLine[2];
        TransferRegisterRecord.Amount = stof(TransferRegisterDataLine[3]);
        TransferRegisterRecord.SourceAccountBalance = TransferRegisterDataLine[4];
        TransferRegisterRecord.DestenationAccountBalance = TransferRegisterDataLine[5];
        TransferRegisterRecord.UserName = TransferRegisterDataLine[6];


        return TransferRegisterRecord;

    }

public:

    struct stTransferRegisterRecord {
        string DateTime;
        string UserName;
        string SourceAccountNumber;
        string DestenationAccountNumber;
        float Amount;
        string SourceAccountBalance;
        string DestenationAccountBalance;
    };

    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    static clsBankClient Find(string AccountNumber)
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExist = 2 };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFailedEmptyObject;
            }
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }
        case enMode::AddNewMode:
        {
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFailedAccountNumberExist;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

        }
        }
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(_vClients);

        *this = _GetEmptyClientObject();
        return 1;
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        double TotalBalances = 0;
        vector <clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : vClients)
        {
            TotalBalances += C.AccountBalance;
        }
        return TotalBalances;
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }

    bool Transfer(float Amount, clsBankClient& DestinationClient)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransfer(Amount, DestinationClient);

        return true;
    }

    static  vector <stTransferRegisterRecord> GetTransferRegisterList()
    {
        vector <stTransferRegisterRecord> vTransferRegisterRecord;

        fstream MyFile;
        MyFile.open("TransferRegister.txt", ios::in);

        if (MyFile.is_open())
        {

            string Line;

            stTransferRegisterRecord TransferRegisterRecord;

            while (getline(MyFile, Line))
            {

                TransferRegisterRecord = _ConvertTransferRegisterLineToRecord(Line);

                vTransferRegisterRecord.push_back(TransferRegisterRecord);

            }

            MyFile.close();

        }

        return vTransferRegisterRecord;

    }

};
