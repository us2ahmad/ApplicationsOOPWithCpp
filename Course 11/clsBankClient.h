#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"


using namespace std;

class clsBankClient : public clsPerson 
{
private:
	enum enMode{EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2 };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line,string Delim = "#//#")
	{
		vector<string> vClientData = clsString::Split(Line, Delim);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], 
						vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Delim = "#//#")
	{
		string Line;
		Line += Client.FirstName + Delim;
		Line += Client.LastName  + Delim;
		Line += Client.Email	 + Delim;
		Line += Client.Phone	 + Delim;
		Line += Client.AccountNumber() + Delim;
		Line += Client.PinCode	 + Delim;
		Line += to_string(Client.AccountBalance);

		return Line;
	}
	
	static clsBankClient _GetEmptyClientObject() 
	{
		return clsBankClient(enMode::EmptyMode, "", "", "","", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("C:\\Users\\ahmad\\Desktop\\ClientData.txt", ios::in);

		if (MyFile.is_open()) 
		{
			string Line;
			while (getline(MyFile,Line))
			{
				vClients.push_back(_ConvertLineToClientObject(Line));
			}
		}
		MyFile.close();
		
		return vClients;
	}
	
	static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;

		MyFile.open("C:\\Users\\ahmad\\Desktop\\ClientData.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsBankClient Client : vClients)
			{
				if (!Client.MarkedForDelete()) 
				{
					MyFile << _ConverClientObjectToLine(Client)<<endl;
				}
			}
		}

		MyFile.close();

	}

	void _AddClientLineToFile(string ClientLine) 
	{
		fstream MyFile;

		MyFile.open("C:\\Users\\ahmad\\Desktop\\ClientData.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << ClientLine << endl;
		}

		MyFile.close();
	}

	void _Update() 
	{
		vector<clsBankClient>  vClients = _LoadClientsDataFromFile();

		for (clsBankClient& Client : vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client = *this;
				break;
			}
		} 

		_SaveClientsDataToFile(vClients);
	}
	
	void _AddNew() 
	{
		_AddClientLineToFile(_ConverClientObjectToLine(*this));
	}

public:
	enum enSaveResults{ svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists = 2};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double AccountBalance)
		:clsPerson(FirstName, LastName, Phone,  Email)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
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

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	double GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;
	
	/*
	No UI Related code iside object.
	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";
	}
	*/

	bool IsEmpty() 
	{
		return _Mode == enMode::EmptyMode;
	}

	static clsBankClient Find(string AccountNumber) 
	{
		fstream MyFile;
		MyFile.open("C:\\Users\\ahmad\\Desktop\\ClientData.txt", ios::in);
		string Line;
		
		if(MyFile.is_open())
		{
			while (getline(MyFile,Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber,string PinCode)
	{
		fstream MyFile;
		MyFile.open("C:\\Users\\ahmad\\Desktop\\ClientData.txt", ios::in);
		string Line;
		
		if (MyFile.is_open())
		{

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		return !(Find(AccountNumber).IsEmpty());
	}
	
	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return  clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	enSaveResults Save() 
	{

		switch (_Mode)
		{
			case enMode::EmptyMode:
			{
				return enSaveResults::svFaildEmptyObject;
			}
			case enMode::UpdateMode:
			{
				_Update();
				return enSaveResults::svSucceeded;
			}
			case enMode::AddNewMode:
			{
				if (IsClientExist(AccountNumber())) 
				{
					return enSaveResults::svFaildAccountNumberExists;
				}
				else
				{
					_AddNew();
					_Mode = enMode::EmptyMode;
					return enSaveResults::svSucceeded;
				}
			}
			default:
				break;
		}
	}

	bool Delete() 
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		bool Deleted = false;

		for  (clsBankClient& Client : vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client._MarkedForDelete = true;
				Deleted = true;
			}
		}

		_SaveClientsDataToFile(vClients);
		
		*this = _GetEmptyClientObject();

		return Deleted;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = GetClientsList();
		
		double TotalBalance = 0.0;

		for (clsBankClient Client : vClients) 
		{
			TotalBalance += Client.AccountBalance;
		}

		return TotalBalance;
	}
};

