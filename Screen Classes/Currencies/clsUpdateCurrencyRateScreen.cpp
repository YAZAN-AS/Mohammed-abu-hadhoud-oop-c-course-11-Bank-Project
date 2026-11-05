#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsUpdateCurrencyRateScreen :protected clsScreen
{
    static void _PrintCurrensy(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n___________________";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n___________________\n";

    }

public:

    static void ShowUpdateCurrencyRateScreen()
    {

        _DrawScreenHeader("\tUpdate Currency Screen");

        string CurrencyCode = "";

        cout << "\nPlease Enter User CurrencyCode: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency Code is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        _PrintCurrensy(Currency);

        cout << "\nAre you sure you want to update this Currency y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            float NewRate = clsInputValidate::ReadFloatNumber();
            Currency.UpdateRate(NewRate);

            cout << "\nCurrncy Rate Updated Successfully :-)\n";
            _PrintCurrensy(Currency);
        }
    }
};

