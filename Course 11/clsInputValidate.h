#pragma once
#include <iostream> 
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsInputValidate
{
public:

	static bool IsNumberBetween( short Number,short From, short To)
	{
		if (From > To)
			clsUtil::Swap(From, To);

		return (From <= Number && To >= Number);
	}

	static bool IsNumberBetween(int Number,int From, int To)
	{
		if (From > To)
			clsUtil::Swap(From, To);

		return (From <= Number && To >= Number);
	}

	static bool IsNumberBetween(float Number,float From, float To)
	{
		if (From > To)
			clsUtil::Swap(From, To);

		return (From <= Number && To >= Number);
	}

	static bool IsNumberBetween( double Number,double From, double To)
	{
		if (From > To)
			clsUtil::Swap(From, To);

		return (From <= Number && To >= Number);
	}

	static bool IsDateBetween(clsDate Date, clsDate FromDate, clsDate ToDate)
	{
		if (!clsDate::IsValidDate(Date) || !clsDate::IsValidDate(FromDate) || !clsDate::IsValidDate(ToDate))
		{
			cout << "Invalid Date" << endl;
			return false;
		}

		if (clsDate::IsDate1AfterDate2(FromDate, ToDate))
			clsDate::SwapDates(FromDate, ToDate);

		return (clsDate::IsDate1AfterDate2(Date, FromDate) || clsDate::IsDate1EqualDate2(Date, FromDate)) &&
			(clsDate::IsDate1BeforeDate2(Date, ToDate) || clsDate::IsDate1EqualDate2(Date, ToDate));
	}

	static int ReadIntNumber(const string& ErrorMessage = "Invalid Number, Enter again\n")
	{
		int number;

		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> number;
		}

		return number;
	}

	static double ReadDblNumber(const string& ErrorMessage = "Invalid Number, Enter again\n")
	{
		double number;

		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> number;
		}

		return number;
	}

	static short ReadShortNumber(const string& ErrorMessage = "Invalid Number, Enter again\n")
	{
		short number;

		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> number;
		}

		return number;
	}

	static float ReadFloatNumber(const string& ErrorMessage = "Invalid Number, Enter again\n")
	{
		float number;

		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> number;
		}

		return number;
	}

	static short ReadShortNumberBetween(short From, short To, const string& ErrorMessage = "Number is not within range, Enter again:\n")
	{
		short number = ReadShortNumber(ErrorMessage);
		while (!IsNumberBetween(number,From, To))
		{
			cout << ErrorMessage;
			number = ReadShortNumber();
		}
		return number;
	}

	static int ReadIntNumberBetween(int From,int To, const string& ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int number = ReadIntNumber(ErrorMessage);
		while (!IsNumberBetween(number,From, To))
		{
			cout << ErrorMessage ;
			number = ReadIntNumber();
		}
		return number;
	}

	static float ReadFloatNumberBetween(float From, float To, const string& ErrorMessage = "Number is not within range, Enter again:\n")
	{
		float number = ReadFloatNumber(ErrorMessage);
		while (!IsNumberBetween(number,From, To))
		{
			cout << ErrorMessage;
			number = ReadFloatNumber();
		}
		return number;
	}

	static double ReadDblNumberBetween(double From, double To, const string& ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double number = ReadDblNumber(ErrorMessage);
		while (!IsNumberBetween(number,From, To))
		{
			cout << ErrorMessage;
			number = ReadDblNumber();
		}
		return number;
	}

	static bool IsValideDate(clsDate Date) 
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadString() 
	{
		string Text = "";

		getline(cin >> ws, Text);
		return Text;
	}
};

