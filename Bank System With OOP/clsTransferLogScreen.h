#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLogRecord(clsBankClient::stTransferLog Record)
	{
		cout << setw(8) << left << "" << "| " << "\x1b[36m" << setw(22) << left << Record.DataTime << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(12) << left << Record.sAccount << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(12) << left << Record.dAccount << "\x1b[0m";
		cout << "| " << "\x1b[32m" << setw(10) << left << Record.Amount << "\x1b[0m";
		cout << "| " << "\x1b[32m" << setw(12) << left << Record.sBalance << "\x1b[0m";
		cout << "| " << "\x1b[32m" << setw(12) << left << Record.dBalance << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(12) << left << Record.Username << "\x1b[0m";
	}

public:

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLog> vTransferLog = clsBankClient::GetTransferLogList();

		string Title = "\t Transfer Log List Screen";
		string SubTitle = "\t    (" + to_string(vTransferLog.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t" << string(100, '_') << "\n\n";

		cout << setw(8) << left << "" << "| " << "\x1b[36m" << left << setw(22) << "Date / Time" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(12) << "s.AccNumber" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(12) << "d.AccNumber" << "\x1b[0m";
		cout << "| " << "\x1b[32m" << left << setw(10) << "Amount" << "\x1b[0m";
		cout << "| " << "\x1b[32m" << left << setw(12) << "s.Balance" << "\x1b[0m";
		cout << "| " << "\x1b[32m" << left << setw(12) << "d.Balance" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(12) << "User" << "\x1b[0m";

		cout << setw(8) << left << "" << "\n\t" << string(100, '_') << "\n\n";

		if (vTransferLog.size() == 0)
		{
			cout << "\t\t\t\t\x1b[31mNo Registers Available In The System!\x1b[0m\n";
		}
		else
		{
			for (clsBankClient::stTransferLog Record : vTransferLog)
			{
				_PrintTransferLogRecord(Record);
				cout << "\n";
			}
		}
		cout << setw(8) << left << "" << "\n\t" << string(100, '_') << "\n";
	}
};