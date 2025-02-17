#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsDate.h"

class clsCurrency
{
private:
	enum enMode { EmptyMode = 1, UpdateMode = 2 };

	enMode _Mode;
	string _Country;
	string _CurrencyName;
	string _CurrencyCode;
	float _Rate;
	clsDate _LastUpdateRate;


	static string _ConverCurrencyObjectToLine(const clsCurrency& Currency , const string& Seperator = "#//#")
	{
		string CurrencyLine;

		CurrencyLine += Currency._Country + Seperator;
		CurrencyLine += Currency._CurrencyCode + Seperator;
		CurrencyLine += Currency._CurrencyName + Seperator;
		CurrencyLine += to_string(Currency._Rate)+ Seperator;
		CurrencyLine += clsDate::DateToString(Currency._LastUpdateRate);

		return CurrencyLine;
	}

	static clsCurrency _ConvertCurrencyLineToObject(string CurrencyLine, const string& Seperator = "#//#")
	{
		vector<string> vCurrencyData = clsString::Split(CurrencyLine, Seperator);

		return  clsCurrency(enMode::UpdateMode , vCurrencyData[0], vCurrencyData[1], 
							vCurrencyData[2],stod(vCurrencyData[3]), vCurrencyData[4]);
	}

	static vector<clsCurrency> _LoadCurrencysDataFromFile() 
	{
		vector<clsCurrency> vCurrencys;

		fstream MyFile;
		MyFile.open("C:\\Users\\ahmad\\Desktop\\Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile,Line))
			{
				vCurrencys.push_back(_ConvertCurrencyLineToObject(Line));
			}

			MyFile.close();
		}
		return vCurrencys;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencys)
	{
		fstream MyFile;
		MyFile.open("C:\\Users\\ahmad\\Desktop\\Currencies.txt", ios::out);

		if (MyFile.is_open()) 
		{
			for (const clsCurrency& Currency : vCurrencys) 
			{
				MyFile << _ConverCurrencyObjectToLine(Currency) << endl;
			}
		
			MyFile.close();
		}
	}

	void _Update() 
	{
		vector<clsCurrency> vCurrencys = _LoadCurrencysDataFromFile();
		for (clsCurrency& Currency : vCurrencys) 
		{
			if (Currency.CurrencyCode() == _CurrencyCode) 
			{
				Currency = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencys);
	}

	static clsCurrency _GetEmptyCurrencyObject() 
	{
		return clsCurrency(enMode::EmptyMode,"","","",0,clsDate());
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode , string CurrencyName, float Rate, clsDate LastUpdateRate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyName = CurrencyName;
		_CurrencyCode = CurrencyCode;
		_Rate = Rate;
		_LastUpdateRate = LastUpdateRate;
	}

	bool IsEmpty() const
	{
		return _Mode == enMode::EmptyMode;
	}

	enMode Mode() const
	{
		return _Mode;
	}
	
	string Country() const
	{
		return _Country;
	}

	string CurrencyName() const
	{
		return _CurrencyName;
	}

	string CurrencyCode() const
	{
		return _CurrencyCode;
	}

	void UpdateRate(float Rate)
	{
		_Rate = Rate;
		_LastUpdateRate = clsDate();
		_Update();
	}

	float Rate() const
	{
		return _Rate;
	}

	clsDate LastUpdateRate() const
	{
		return _LastUpdateRate;
	}

	static clsCurrency FindByCountry(string Country)
	{
		vector<clsCurrency> vCurrencys = _LoadCurrencysDataFromFile();

		if (!vCurrencys.empty()) 
		{
			Country = clsString::UpperAllString(Country);
		
			for (const clsCurrency& Currency : vCurrencys)
			{
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					return Currency;
				}
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string Code) 
	{
		vector<clsCurrency> vCurrencys = _LoadCurrencysDataFromFile();
		
		if (!vCurrencys.empty())
		{
			Code = clsString::UpperAllString(Code);

			for (const clsCurrency& Currency : vCurrencys)
			{
				if (clsString::UpperAllString(Currency.CurrencyCode()) == Code)
				{
					return Currency;
				}
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		return (!clsCurrency::FindByCode(CurrencyCode).IsEmpty());
	}

	static vector<clsCurrency> GetCurrencysList()
	{
		return _LoadCurrencysDataFromFile();
	}
};

