#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLoginRegisterRecord(clsUser::stLoginRegister User)
	{
		cout << setw(8) << left << "" << "| " << "\x1b[36m" << setw(30) << left << User.DateTime << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(20) << left << User.Username << "\x1b[0m";
		cout << "| " << "\x1b[31m" << setw(10) << left << User.Password << "\x1b[0m";
		cout << "| " << "\x1b[32m" << setw(12) << left << User.Permission << "\x1b[0m";
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRight(clsUser::enPermission::pLoginRegister))
		{
			return;
		}

		vector <clsUser::stLoginRegister> vLoginRegister = clsUser::GetLoginRegisterList();
		
		string Title = "\t Login Register List Screen";
		string SubTitle = "\t    (" + to_string(vLoginRegister.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t" << string(80, '_') << "\n\n";

		cout << setw(8) << left << "" << "| " << "\x1b[36m" << left << setw(30) << "Date / Time" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(20) << "Username" << "\x1b[0m";
		cout << "| " << "\x1b[31m" << left << setw(10) << "Password" << "\x1b[0m";
		cout << "| " << "\x1b[32m" << left << setw(12) << "Permission" << "\x1b[0m";

		cout << setw(8) << left << "" << "\n\t" << string(80, '_') << "\n\n";

		if (vLoginRegister.size() == 0)
		{
			cout << "\t\t\t\t\x1b[31mNo Registers Available In The System!\x1b[0m\n";
		}
		else
		{
			for (clsUser::stLoginRegister Register : vLoginRegister)
			{
				_PrintLoginRegisterRecord(Register);
				cout << "\n";
			}
		}
		cout << setw(8) << left << "" << "\n\t" << string(80, '_') << "\n";
	}
};