#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
{
private:

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

	static void ShowFindClientScreen()
	{
		if (!CheckAccessRight(clsUser::enPermission::pFindClient))
		{
			return;
		}

		_DrawScreenHeader("\t Find Client Screen");

		string AccNumber = "";

		cout << "Please Enter Account Number: ";
		AccNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			cout << "Account Number is Not Found, Enter Avalid Number: ";
			AccNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccNumber);

		if (!Client.IsEmpty())
		{
			cout << "\nClient Found :)\n";
		}
		else
		{
			cout << "\nClient Was Not Found :(\n";
		}
		_PrintClient(Client);
	}
};