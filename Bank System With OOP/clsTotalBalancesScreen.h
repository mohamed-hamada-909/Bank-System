#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsBankClient.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:

	static void PrintClientRecordBalanceLine(clsBankClient Client)
	{
		cout << setw(25) << left << "" << left << "| " << "\x1b[36m" << setw(15) << Client.AccNumber << "\x1b[0m";
		cout << left << "| " << "\x1b[36m" << setw(40) << Client.FullName() << "\x1b[0m";
		cout << left << "| " << "\x1b[32m" << setw(12) << Client.AccBalance << "\x1b[0m";
	}

public:

	static void ShowTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		
		string Title = "\t  \x1b[36mBalances List Screen\x1b[0m";
		string SubTitle = "\t   \x1b[33m(" + to_string(vClients.size()) + ") Client(s).\x1b[0m";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(25) << left << "" << string(70, '_') << "\n";

		cout << setw(25) << left << "" << left << "| " << "\x1b[36m" << setw(15) << "Account Number" << "\x1b[0m";
		cout << left << "| " << "\x1b[36m" << setw(40) << "Client Name" << "\x1b[0m";
		cout << left << "| " << "\x1b[32m" << setw(12) << "Balance" << "\x1b[0m";
		cout << "\n";

		cout << setw(25) << left << "" << string(70, '_') << "\n";

		if (vClients.size() == 0)
		{
			cout << "\t\t\t\x1b[31mNo Clients Available In The System!\x1b[0m\n";
		}
		else
		{
			for (clsBankClient& C : vClients)
			{
				PrintClientRecordBalanceLine(C);
				cout << "\n";
			}
		}

		cout << setw(25) << left << "" << string(70, '_') << "\n";

		double TotalBalances = clsBankClient::GetTotalBalances();

		cout << setw(25) << left << "" << "\t\t\t\x1b[36mTotal Balances = \x1b[32m"
			<< TotalBalances << "\x1b[0m" << endl;

		cout << setw(25) << left << "" << "\t\t\x1b[33m( "
			<< clsUtil::NumberToText(TotalBalances)<< " )\x1b[0m\n";
	}
};