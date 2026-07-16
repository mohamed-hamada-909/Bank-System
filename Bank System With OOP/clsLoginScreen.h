#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	
	static bool _Login()
	{
		bool LoginFaild = false;
		short WrongLogin = 0;

		string UserName, Password;

		do
		{
			if (LoginFaild)
			{
				cout << "\nInvalid UserName/Password!\n";

				WrongLogin++;
				cout << "You Have " << (3-WrongLogin) << " Trial(s) To Login.\n\n";

			}		

			if (WrongLogin == 3)
			{
				cout << "You Are Locked After 3 Faild Trial(s).\n";

				return false;
			}

			cout << "\n\x1b[31mEnter UserName:\x1b[0m ";
			cin >> UserName;

			cout << "\n\x1b[31mEnter Password:\x1b[0m ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     \x1b[31mLogin Screen\x1b[0m");

		return _Login();
	}
};