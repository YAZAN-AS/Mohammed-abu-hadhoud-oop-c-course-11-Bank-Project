#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsString.h"
#include"clsCurrency.h"
#include"clsInputValidate.h"

class clsFindCurrenciesScreen : protected clsScreen
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

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrensy(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

public:

    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t  Find User Screen");

        cout << "Find By: [1] Code or [2] Country ? ";
        short Answer = clsInputValidate::ReadShortNumberBetween(1, 2);

        if (Answer == 1)
        {
            cout << "\nPlease Enter CurrencyCode: ";
            string CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else
        {
            cout << "\nPlease Enter CurrencyCountry: ";
            string CurrencyCountry = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(CurrencyCountry);
            _ShowResults(Currency);
        }
    }
};

