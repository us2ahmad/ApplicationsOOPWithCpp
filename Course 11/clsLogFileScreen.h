#pragma once
#include "clsScreen.h"
#include "clsString.h"
#include "clsLogFile.h"

class clsLogFileScreen : clsScreen
{
private:

    static void _PrintLogFileRecordLine(clsLogFile LogFile)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LogFile.DateTime();
        cout << "| " << setw(20) << left << LogFile.UserName();
        cout << "| " << setw(20) << left << LogFile.Password();
        cout << "| " << setw(12) << left << LogFile.Permissions();
        cout << "| " << setw(10) << left << LogFile.Mode();
    }

public:

	static void ShowLogFileScreen() 
	{
        if (!CheckAccessRights(clsUser::enPermissions::pLogFile))
        {
            return; // this will exit the function and it will not continue
        }

        vector <clsLogFile> vLogFileRecord = clsLogFile::GetLogFileList();

        string Title = "\tLogFile List Screen";
        string SubTitle = "\t\t(" + to_string(vLogFileRecord.size()) + ") Record(s).";

        DrowHeaderScreen(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "__________________________________________________ \n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "| " << left << setw(10) << "Status";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "__________________________________________________ \n" << endl;

        if (vLogFileRecord.size() == 0)
        {
            cout << "\t\t\t\tNo Logins Available In the System!";
        }
        else
        { 
            for (const clsLogFile& Record : vLogFileRecord)
            {
                _PrintLogFileRecordLine(Record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "__________________________________________________ \n" << endl;
    }
};

