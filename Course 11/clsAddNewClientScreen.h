#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsAddNewClientScreen : clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& Client) 
	{
		cout << "Enter First Name : ";
		Client.FirstName = clsInputValidate::ReadString();
	
		cout << "\nEnter Last Name : ";
		Client.LastName = clsInputValidate::ReadString();
	
		cout << "\nEnter Email  : ";
		Client.Email = clsInputValidate::ReadString();
	
		cout << "\nEnter Phone  : ";
		Client.Phone = clsInputValidate::ReadString();
	
		cout << "\nEnter PinCode  : ";
		Client.PinCode = clsInputValidate::ReadString();
	
		cout << "\nEnter Balance : ";
		Client.AccountBalance = clsInputValidate::ReadDblNumber();
	}
	 
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

public:

	static void ShowAddNewClientScreen()
	{
		DrowHeaderScreen("\t  Add New Client Screen");
		cout << "\nPlease Enter Account Number: ";

		string AccountNumber = clsInputValidate::ReadString();
		
		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Already Used, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult = NewClient.Save();

		switch (SaveResult)
		{
			case  clsBankClient::enSaveResults::svSucceeded:
			{
				cout << "\nAccount Addeded Successfully :-)\n";
				_PrintClient(NewClient);
				break;
			}
			case clsBankClient::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty";
				break;
			}
			case clsBankClient::enSaveResults::svFaildAccountNumberExists:
			{
				cout << "\nError account was not saved because account number is used!\n";
				break;

			}
		}
	
	}

};


