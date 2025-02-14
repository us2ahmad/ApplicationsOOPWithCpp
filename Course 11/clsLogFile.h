#pragma once
#include <iostream>
#include <fstream>
#include "clsDate.h"
#include "clsUser.h"
#include "Global.h"

using namespace std;

class clsLogFile
{
private:

	string _DateTime;
	string _UserName;
	string _Password;
	int	   _Permissions;
	string _Mode;

	static string _ConverLogFileDataToLine(string Mode,string Delim = "#//#")
	{
		string Line;
		Line += clsDate::GetSystemDateTimeString() + Delim;
		Line += gCurrentUser.UserName + Delim;
		Line += gCurrentUser.Password + Delim;
		Line += to_string(gCurrentUser.Permissions) + Delim;
		Line += Mode;

		return Line;
	}
	
	static clsLogFile _ConvertLogFileLineToRecord(string Line, string Seperator = "#//#")
	{
		clsLogFile LogFile;

		vector <string> LogFileDataLine = clsString::Split(Line, Seperator);
		LogFile._DateTime = LogFileDataLine[0];
		LogFile._UserName = LogFileDataLine[1];
		LogFile._Password = LogFileDataLine[2];
		LogFile._Permissions = stoi(LogFileDataLine[3]);
		LogFile._Mode = LogFileDataLine[4];

		return LogFile;
	}

	static void _SaveLogFile(string Mode)
	{
		fstream MyFile;
		MyFile.open("C:\\Users\\ahmad\\Desktop\\LogFile.txt", ios::out | ios::app);
		
		if (MyFile.is_open())
		{
			MyFile << _ConverLogFileDataToLine(Mode) << endl;
		}
		MyFile.close();
	}

	static vector<clsLogFile> _GetLogFileList()
	{
		vector <clsLogFile> vLogFileRecord;

		fstream MyFile;
		MyFile.open("C:\\Users\\ahmad\\Desktop\\LogFile.txt", ios::in); //read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				vLogFileRecord.push_back(_ConvertLogFileLineToRecord(Line));
			}
		
			MyFile.close();
		}

		return vLogFileRecord;
	}

public:

	string DateTime() const
	{
		return _DateTime;
	}
	string UserName() const
	{
		return _UserName;
	}
	string Password() const
	{
		return _Password;
	}
	int Permissions() const
	{
		return _Permissions;
	}
	string Mode() const
	{
		return _Mode;
	}

	static void LogFile(string Mode)
	{
		_SaveLogFile(Mode);
	}

	static vector<clsLogFile> GetLogFileList()
	{
		return	_GetLogFileList();
	}
};

