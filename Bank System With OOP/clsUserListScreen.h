#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsUserListScreen : protected clsScreen
{
private:

	static void _PrintUser(clsUser User)
	{
		cout << setw(8) << left << "" << "| " << "\x1b[31m" << setw(15) << left << User.UserName << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(25) << left << User.FullName() << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(12) << left << User.Phone << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(20) << left << User.Email << "\x1b[0m";
		cout << "| " << "\x1b[31m" << setw(10) << left << User.Password << "\x1b[0m";
		cout << "| " << "\x1b[32m" << setw(12) << left << User.Permission << "\x1b[0m";
	}

public:

	static void ShowUsersList()
	{
		vector <clsUser> vUsers = clsUser::GetUsersList();

		string Title = "\t  \x1b[36mUsers List Screen\x1b[0m";
		string SubTitle = "\t    \x1b[33m(" + to_string(vUsers.size()) + ") User(s).\x1b[0m";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t" << string(105, '_') << "\n\n";

		cout << setw(8) << left << "" << "| " << "\x1b[31m" << left << setw(15) << "UserName" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(25) << "Full Name" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(12) << "Phone" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(20) << "Email" << "\x1b[0m";
		cout << "| " << "\x1b[31m" << left << setw(10) << "Password" << "\x1b[0m";
		cout << "| " << "\x1b[32m" << left << setw(12) << "Permission" << "\x1b[0m";

		cout << setw(8) << left << "" << "\n\t" << string(105, '_') << "\n\n";

		if (vUsers.size() == 0)
		{
			cout << "\t\t\t\t\x1b[31mNo Users Available In The System!\x1b[0m\n";
		}
		else
		{
			for (clsUser& U : vUsers)
			{
				_PrintUser(U);
				cout << "\n";
			}
		}
		cout << setw(8) << left << "" << "\n\t" << string(105, '_') << "\n";
	}
};