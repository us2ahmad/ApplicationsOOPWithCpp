//#include <iostream>
//#include "clsBankClient.h"
//#include "clsInputValidate.h"
//
//void DeleteClient()
//{
//    cout << "\nPlease Enter Account Number: ";
//    string AccountNumber  = clsInputValidate::ReadString();
//  
//    while (!clsBankClient::IsClientExist(AccountNumber))
//    {
//        cout << "\nAccount number is not found, choose another one : ";
//        AccountNumber = clsInputValidate::ReadString();
//    }
//
//    clsBankClient Client = clsBankClient::Find(AccountNumber);
//    Client.Print();
//
//    cout << "\nAre you sure you want to delete this client y/n ? ";
//
//    char Answer = 'n';
//    cin >> Answer;
//
//    if (toupper(Answer) == 'Y')
//    {
//        if (Client.Delete())
//        {
//            cout << "\nClient Deleted Successfully :-)\n";
//            Client.Print();
//        }
//        else
//        {
//            cout << "\nError Client Was not Deleted\n";
//        }
//    }
//}
//
//int main()
//{
//    DeleteClient();
//    system("pause > 0");
//    return 0;
//}