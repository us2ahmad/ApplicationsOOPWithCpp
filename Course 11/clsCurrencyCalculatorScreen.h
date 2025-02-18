#pragma once
#include <iostream> 
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsString.h"



class clsCurrencyCalculatorScreen : clsScreen
{
private:

    static clsCurrency _GetCurrency(const string& Message) 
    {
        cout << Message;
        string CurrencyCode = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }
        return clsCurrency::FindByCode(CurrencyCode);
    }

    static float _ReadAmount()
    {
        cout << "\nEnter Amount To Exchange : ";
        return clsInputValidate::ReadFloatNumber();
    }

    static  void _PrintCurrencyCard(const clsCurrency& Currency, string Title = "Currency Card:")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$) =    : " << Currency.Rate();
        cout << "\n_____________________________\n\n";

    }
    static void _PrintCalculationsResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
    {
        if (CurrencyFrom == CurrencyTo)
        {
            cout << Amount << " " << clsString::UpperAllString(CurrencyFrom.CurrencyCode()) 
               << " = " << Amount << " " << CurrencyTo.CurrencyCode();
            return;
        }
        else
        {
            _PrintCurrencyCard(CurrencyFrom, "Convert From : ");

            float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

            if(CurrencyFrom.CurrencyCode() != "USD")
            cout << Amount << " " << clsString::UpperAllString(CurrencyFrom.CurrencyCode()) << " = " << AmountInUSD << " USD ";

            if (clsString::UpperAllString(CurrencyTo.CurrencyCode()) == "USD")
                return;

            cout << "\nConverting From USD To " << clsString::UpperAllString(CurrencyTo.CurrencyCode()) << endl;
            _PrintCurrencyCard(CurrencyTo, "Convert To : ");

            float  CurrencyFromEqualCurrencyTo = CurrencyFrom.ConvertToOtherCurrency(Amount,CurrencyTo);

            cout << Amount << " " << clsString::UpperAllString(CurrencyFrom.CurrencyCode())
                << " = " << CurrencyFromEqualCurrencyTo << " " << CurrencyTo.CurrencyCode();
        }
    }
public:

	static void CurrencyCalculatorScreen() 
	{
        char Continue = 'y';

        while (toupper(Continue) == 'Y')
        {
            system("cls");

            DrowHeaderScreen("\tCurrency Calculator Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;
        }
	}
};

