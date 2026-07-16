#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
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

	static string _ReadAccNumber()
	{
		cout << "Please Enter Account Number? \n";

		string choice = clsInputValidate::ReadString();
		return choice;
	}

	static double _ReadWithdraw()
	{
		cout << "Please Enter Withdraw Amount? ";

		double Amount = clsInputValidate::ReadDbNumberBetween(1, 100000000, "PleaseEnter Positive Number");
		return Amount;
	}

public:

	static void ShowWithdrawScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Withdraw Screen");

		string AccNumber = _ReadAccNumber();

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			cout << "\nClient With Account Number [" << AccNumber << "] Not Found!\n";

			AccNumber = _ReadAccNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccNumber);
		_PrintClient(Client);

		double Amount = _ReadWithdraw();

		cout << "Are You Sure You Want To Perform This Transaction? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client.Withdraw(Amount))
			{
				cout << "\nAmount Withdraw Successfully.\n";
				cout << "\nNew Balance is: " << Client.AccBalance << endl;
			}
			else
			{
				cout << "\nCan't Withdraw, Insufficient Balance!";
				cout << "\nAmount To Withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client.AccBalance << endl;
			}
		}
		else
		{
			cout << "The Operation Was Cancelled!\n";
		}
	}
};