#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsUser : public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
   
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
                   vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += User.Password + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;
    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {
        vector <clsUser> vUsers;
        
        fstream MyFile;
        MyFile.open("C:\\Users\\ahmad\\Desktop\\UserData.txt", ios::in); //read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vUsers.push_back(_ConvertLinetoUserObject(Line));
            }

            MyFile.close();
        }

        return vUsers;
    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("C:\\Users\\ahmad\\Desktop\\UserData.txt", ios::out); //overwrite

        if (MyFile.is_open())
        {
            for (const clsUser& User : vUsers)
            {
                if (User.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    MyFile << _ConverUserObjectToLine(User) << endl;
                }
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsUser> vUsers = _LoadUsersDataFromFile();
        
        for (clsUser& User : vUsers)
        {
            if (User.UserName == UserName)
            {
                User = *this;
                break;
            }
        }
        _SaveUsersDataToFile(vUsers);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("C:\\Users\\ahmad\\Desktop\\UserData.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:

    enum enPermissions
    {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
    };

    clsUser(enMode Mode, string FirstName, string LastName, string Phone, string Email , string UserName, string Password,int Permissions)
     : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty() const
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted() const
    {
        return _MarkedForDelete;
    }

    string GetUserName() const
    {
        return _UserName;
    }
    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword() const
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int GetPermissions() const
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("C:\\Users\\ahmad\\Desktop\\UserData.txt", ios::in); //read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("C:\\Users\\ahmad\\Desktop\\UserData.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

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
                //This will add new record to file or database
                if (clsUser::IsUserExist(_UserName))
                {
                    return enSaveResults::svFaildUserExists;
                }
                else
                {
                    _AddNew();
                    //We need to set the mode to update after add new
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }

            }
        }
    }

    static bool IsUserExist(string UserName)
    {
        return (!clsUser::Find(UserName).IsEmpty());
    }

    bool Delete()
    {
        vector <clsUser> vUsers = _LoadUsersDataFromFile();
        bool Deleted = false;

        for (clsUser& User : vUsers)
        {
            if (User.UserName == UserName)
            {
                User._MarkedForDelete = true;
                Deleted = true;
                break;
            }
        }
        
        _SaveUsersDataToFile(vUsers);

        *this = _GetEmptyUserObject();

        return Deleted;
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

};
