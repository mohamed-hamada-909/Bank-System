#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card: \n";
		cout << "----------------------------";
		cout << "\nFull Name : " << Client.FullName();
		cout << "\nAcc.Number: " << Client.AccNumber;
		cout << "\nBalance   : " << Client.AccBalance;
		cout << "\n----------------------------\n";
	}

	static string _ReadSourseClientAccNumber()
	{
		cout << "\nPlease Enter Account Number To Transfer From: ";
		string AccNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			cout << "\nClient Not Found, Enter Invalid Acc Number!\n";

			AccNumber = clsInputValidate::ReadString();
		}
		return AccNumber;
	}

	static string _ReadDestinationClientAccNumber()
	{
		cout << "\nPlease Enter Account Number To Transfer To: ";
		string AccNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			cout << "\nClient Not Found, Enter Invalid Acc Number!\n";

			AccNumber = clsInputValidate::ReadString();
		}
		return AccNumber;
	}

	static float _ReadAmount(clsBankClient SourseClient)
	{
		cout << "\nEnter Transfer Amount: ";
		float Amount = clsInputValidate::ReadDbNumberBetween(0, SourseClient.AccBalance, "Invalid Number, Enter Again: ");;

		while (Amount > SourseClient.AccBalance)
		{
			cout << "\nAmount Exceeds The Available Balance, Enter Again: ";

			Amount = clsInputValidate::ReadDbNumber();
		}

		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t  Transfer Screen");

		clsBankClient SourseClient = clsBankClient::Find(_ReadSourseClientAccNumber());
		_PrintClientCard(SourseClient);
		
		clsBankClient DestinationClient = clsBankClient::Find(_ReadDestinationClientAccNumber());
		_PrintClientCard(DestinationClient);
		
		float Amount = _ReadAmount(SourseClient);

		cout << "\nAre You Sure You Want To Perform This Operation? Y/N? ";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (SourseClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
			{
				cout << "\tTransfer Done Successfully\n";
			}
			else
			{
				cout << "\nTransfer Faild :(\n";
			}
		}
		else
		{
			cout << "\nThe Operation Was Cancelled!...\n";
		}

		_PrintClientCard(SourseClient);
		_PrintClientCard(DestinationClient);
	}
};