//#include "clsBankClient.h"
//#include "clsUtil.h"
//#include <iomanip>
//#include <iostream>
//
//void PrintClientRecordLine(clsBankClient Client)
//{
//
//    cout << "| " << setw(15) << left << Client.AccountNumber();
//    cout << "| " << setw(20) << left << Client.FullName();
//    cout << "| " << setw(12) << left << Client.Phone;
//    cout << "| " << setw(20) << left << Client.Email;
//    cout << "| " << setw(10) << left << Client.PinCode;
//    cout << "| " << setw(12) << left << Client.AccountBalance;
//
//}
//
//void ShowClientsList()
//{
//    vector <clsBankClient> vClients = clsBankClient::GetClientsList();
//
//    cout << "\n" << clsUtil::Tabs(5) << "Client List(" << vClients.size() << ") Client(s).";
//    cout << "\n_______________________________________________________";
//    cout << "_________________________________________\n" << endl;
//
//    cout << "| " << left << setw(15) << "Accout Number";
//    cout << "| " << left << setw(20) << "Client Name";
//    cout << "| " << left << setw(12) << "Phone";
//    cout << "| " << left << setw(20) << "Email";
//    cout << "| " << left << setw(10) << "Pin Code";
//    cout << "| " << left << setw(12) << "Balance";
//    cout << "\n_______________________________________________________";
//    cout << "_________________________________________\n" << endl;
//
//    if (vClients.size() == 0)
//    {
//        cout <<  clsUtil::Tabs(4) << "No Clients Available In the System!";
//    }
//    else
//    {
//        for (clsBankClient Client : vClients)
//        {
//            PrintClientRecordLine(Client);
//            cout << endl;
//        }
//    }
//
//    cout << "\n_______________________________________________________";
//    cout << "_________________________________________\n" << endl;
//
//}
//
//int main()
//{
//    ShowClientsList();
//    system("pause > 0");
//    return 0;
//}