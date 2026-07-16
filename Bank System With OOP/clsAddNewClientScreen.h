#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PIN Code: ";
		Client.PINCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccBalance = clsInputValidate::ReadDbNumber();
	}

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n\x1b[36mClient Card:\x1b[0m";
		cout << "\n________________________________";
		cout << "\n\x1b[33mFirstName   : \x1b[0m" << Client.FirstName;
		cout << "\n\x1b[33mLastName    : \x1b[0m" << Client.LastName;
		cout << "\n\x1b[33mFull Name   : \x1b[0m" << Client.FullName();
		cout << "\n\x1b[33mEmail       : \x1b[0m" << Client.Email;
		cout << "\n\x1b[33mPhone       : \x1b[0m" << Client.Phone;
		cout << "\n\x1b[33mAcc. Number : \x1b[0m" << Client.AccNumber;
		cout << "\n\x1b[33mPassword    : \x1b[0m" << Client.PINCode;
		cout << "\n\x1b[33mBalance     : \x1b[32m" << Client.AccBalance << "\x1b[0m";
		cout << "\n________________________________\n";
	}

public:

	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRight(clsUser::enPermission::pAddNewClient))
		{
			return;
		}

		_DrawScreenHeader("\t   Add New Client Screen");

		string AccNumber = "";

		cout << "Please Enter Account Number: ";
		AccNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccNumber))
		{
			cout << "\nAccount number is Already Used, Enter another one: ";
			AccNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case  clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "\nAccount Added Successfully :-)\n";
			_PrintClient(NewClient);
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmpty:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		case clsBankClient::enSaveResults::svFaildAccNumberExist:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}
		}
	}
};