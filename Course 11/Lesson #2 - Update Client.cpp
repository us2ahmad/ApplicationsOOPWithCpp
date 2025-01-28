//#include <iostream>
//#include "clsBankClient.h"
//#include "clsInputValidate.h"
//
//void ReadClientInfo(clsBankClient& Client) 
//{
//	cout << "Enter First Name : ";
//	Client.FirstName = clsInputValidate::ReadString();
//
//	cout << "\nEnter Last Name : ";
//	Client.LastName = clsInputValidate::ReadString();
//
//	cout << "\nEnter Email  : ";
//	Client.Email = clsInputValidate::ReadString();
//
//	cout << "\nEnter Phone  : ";
//	Client.Phone = clsInputValidate::ReadString();
//
//	cout << "\nEnter PinCode  : ";
//	Client.PinCode = clsInputValidate::ReadString();
//
//	cout << "\nEnter Balance : ";
//	Client.AccountBalance = clsInputValidate::ReadDblNumber();
//}
//
//void UpdateClient() 
//{
//	cout << "\nPlease Enter client Account Number: ";
//	string AccountNumber = clsInputValidate::ReadString();	 
//
//	while (!clsBankClient::IsClientExist(AccountNumber))
//	{
//		cout << "Account Number Is Not Found , Choose another one : ";
//		AccountNumber = clsInputValidate::ReadString();
//	}
//
//	clsBankClient Client = clsBankClient::Find(AccountNumber);
//	Client.Print();
//
//	cout << "\n\nUpdate Client Info:";
//	cout << "\n____________________\n";
//
//	ReadClientInfo(Client);
//
//	clsBankClient::enSaveResults SaveResult = Client.Save();
//	
//	switch (SaveResult)
//	{
//		case clsBankClient::svFaildEmptyObject:
//		{
//			cout << "\nError account was not saved because it's Empty";
//			break;
//		}	
//
//		case clsBankClient::svSucceeded:
//		{
//			cout << "\nAccount Updated Successfully :-)\n";
//			Client.Print();
//			break;
//		}
//	}
//
//}
//
//int main() 
//{
//	UpdateClient();
//	system("pause > 0");
//
//	return 0;
//}
