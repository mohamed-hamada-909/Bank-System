#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRight(clsUser::enPermission::pDeleteCLient))
		{
			return;
		}

		_DrawScreenHeader("\t  Delete Client Screen");

		string AccNumber = "";

		cout << "Please Enter Account Number: ";
		AccNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			cout << "\nAccount Number is not Found, Choose Another One: ";
			AccNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccNumber);
		_PrintClient(Client);

		cout << "\nAre You Sure You Want to Delete This Client? Y/N: ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfully :)\n";

				_PrintClient(Client);
			}
			else
			{
				cout << "\nError Client Was Not Deleted :(\n";
			}
		}
		else
		{
			cout << "The Operation Faild :(\n";
		}
	}
};