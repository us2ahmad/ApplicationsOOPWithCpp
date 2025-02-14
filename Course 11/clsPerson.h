#pragma once
#include <iostream>

using namespace std;

class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	string _Phone;
	string _Email;

public:

	clsPerson(string FirstName,string LastName,string Phone,string Email) 
	{
		_FirstName = FirstName;
		_LastName  = LastName;
		_Phone = Phone;
		_Email = Email;
	}


	void SetFirstName(string FirstName) 
	{
		_FirstName = FirstName;
	}
	string GetFirstName() const
	{
		return _FirstName;
	}
	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;


	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}
	string GetLastName() const
	{
		return _LastName;
	}
	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;


	void SetPhone(string Phone)
	{
		_Phone = Phone;
	}
	string GetPhone() const
	{
		return _Phone;
	}
	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;

	void SetEmail(string Email)
	{
		_Email = Email;
	}
	string GetEmail() const
	{
		return _Email;
	}
	__declspec(property(get = GetEmail, put = SetEmail)) string Email;

	string FullName() const
	{
		return _FirstName + " " + _LastName;
	}

	void Print() 
	{
		cout << "Info" << endl;
		cout << "___________________\n";
		cout << "FirstName : " << _FirstName << endl;
		cout << "LastName  : " << _LastName << endl;
		cout << "FullName  : " << FullName() << endl;
		cout << "Phone     : " << _Phone << endl;
		cout << "Email     : " << _Email<< endl;
		cout << "___________________\n";
	}
};

