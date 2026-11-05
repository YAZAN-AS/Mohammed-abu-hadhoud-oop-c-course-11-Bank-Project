#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsUser.h"
#include"clsBankClient.h"


class clsTransferLogScreen :protected clsScreen
{

private:

    static void PrintTransferRegisterRecordLine(clsBankClient::stTransferRegisterRecord TransferRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferRegisterRecord.DateTime;
        cout << "| " << setw(10) << left << TransferRegisterRecord.SourceAccountNumber;
        cout << "| " << setw(10) << left << TransferRegisterRecord.DestenationAccountNumber;
        cout << "| " << setw(10) << left << TransferRegisterRecord.Amount;
        cout << "| " << setw(12) << left << TransferRegisterRecord.SourceAccountBalance;
        cout << "| " << setw(12) << left << TransferRegisterRecord.DestenationAccountBalance;
        cout << "| " << setw(10) << left << TransferRegisterRecord.UserName;
    }

public:

    static void ShowTransferRegisterScreen()
    {

        vector <clsBankClient::stTransferRegisterRecord> vTransferRegisterRecord = clsBankClient::GetTransferRegisterList();

        string Title = "\t  Transfer Log List Screen";
        string SubTitle = "\t\t(" + to_string(vTransferRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t__________________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acct";
        cout << "| " << left << setw(10) << "d.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(12) << "s.Balance";
        cout << "| " << left << setw(12) << "d.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t__________________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferRegisterRecord Record : vTransferRegisterRecord)
            {

                PrintTransferRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t__________________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};