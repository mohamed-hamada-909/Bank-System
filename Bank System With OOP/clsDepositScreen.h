#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

	static double _ReadAmount()
	{
		cout << "Please Enter Deposit Amount? ";

		double Amount = clsInputValidate::ReadDbNumberBetween(1, 100000000, "Please Enter Positive Number");
		return Amount;
	}

public:

	static void ShowDepositScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Deposit Screen");

		string AccNumber = _ReadAccNumber();

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			cout << "\nClient With Number [" << AccNumber << "] Is Not Found!\n";

			AccNumber = _ReadAccNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccNumber);
		_PrintClient(Client);

		double Amount = _ReadAmount();
		cout << "Are You Sure You Want To Perform This Transaction? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			Client.Deposit(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance is: " << Client.AccBalance << endl;
		}
		else
		{
			cout << "\nOperation Was Cancelled!\n";
		}
	}
};