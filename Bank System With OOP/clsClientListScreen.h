#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

using namespace std;

class clsClientListScreen :protected clsScreen
{
private:
	
	static void _PrintClientRecordLine(clsBankClient Client)
	{
		cout << setw(8) << left << "" << "| " << "\x1b[36m" << setw(15) << left << Client.GetAccNumber() << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(20) << left << Client.FullName() << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(12) << left << Client.Phone << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(20) << left << Client.Email << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(10) << left << Client.PINCode << "\x1b[0m";
		cout << "| " << "\x1b[32m" << setw(12) << left << Client.AccBalance << "\x1b[0m";
	}

public:

	static void ShowClientsList()
	{
		if (!CheckAccessRight(clsUser::enPermission::pListClient))
		{
			return;
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t  \x1b[36mClient List Screen\x1b[0m";
		string SubTitle = "\t   (\x1b[33m" + to_string(vClients.size()) + "\x1b[0m) Client(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t" << string(97, '_') << "\n\n";

		cout << setw(8) << left << "" << "| " << "\x1b[36m" << left << setw(15) << "Accout Number" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(20) << "Client Name" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(12) << "Phone" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(20) << "Email" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(10) << "PIN Code" << "\x1b[0m";
		cout << "| " << "\x1b[32m" << left << setw(12) << "Balance" << "\x1b[0m";

		cout << setw(8) << left << "" << "\n\t" << string(97, '_') << "\n\n";

		if (vClients.size() == 0)
		{
			cout << "\t\t\t\t\x1b[31mNo Clients Available in The System!\x1b[0m\n";
		}
		else
		{
			for (clsBankClient& C : vClients)
			{
				_PrintClientRecordLine(C);
				cout << "\n";
			}
		}

		cout << setw(8) << left << "" << "\n\t" << string(97, '_') << "\n\n";
	}
};