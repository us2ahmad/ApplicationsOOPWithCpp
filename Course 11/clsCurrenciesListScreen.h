#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrenciesListScreen : clsScreen
{
private:
    static void PrintCurrencyRecordLine(const clsCurrency& Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(40) << left << Currency.CurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate();
        cout << "| " << setw(10) << left << Currency.LastUpdateRate().DateToString();
    }

public:

    static void ShowCurrenciesListScreen()
    {
        vector <clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();
        string Title = "\t  Currencies List Screen";
        string SubTitle = "\t    (" + to_string(vCurrencys.size()) + ") Currency.";

        DrowHeaderScreen(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________________ \n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(40) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << "| " << left << setw(10) << "Last Update";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________________\n" << endl;

        if (vCurrencys.size() == 0)
        {
            cout << "\t\t\t\tNo Currencies Available In the System!";
        }
        else
        { 
            for (const clsCurrency& Currency : vCurrencys)
            {
                PrintCurrencyRecordLine(Currency);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________________\n" << endl;
    }

};
