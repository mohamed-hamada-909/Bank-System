#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:

	static void _PrintUser(clsUser User)
	{
		cout << "\n\x1b[36mUser Card:\x1b[0m";
		cout << "\n___________________________";
		cout << "\n\x1b[36mFirstName   : \x1b[0m" << User.FirstName;
		cout << "\n\x1b[36mLastName    : \x1b[0m" << User.LastName;
		cout << "\n\x1b[36mFull Name   : \x1b[0m" << User.FullName();
		cout << "\n\x1b[36mEmail       : \x1b[0m" << User.Email;
		cout << "\n\x1b[36mPhone       : \x1b[0m" << User.Phone;
		cout << "\n\x1b[31mUser Name   : \x1b[0m" << User.UserName;
		cout << "\n\x1b[31mPassword    : \x1b[0m" << User.Password;
		cout << "\n\x1b[32mPermissions : \x1b[0m" << User.Permission;
		cout << "\n___________________________\n";
	}

public:

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t  \x1b[36mFind User Screen\x1b[0m");

		string UserName = "";

		cout << "\n\x1b[31mEnter User Name:\x1b[0m ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\n\x1b[31mUser Is Not Found, Choose Another One:\x1b[0m ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
		{
			cout << "\n\x1b[32mUser Found :)\x1b[0m\n";
		}
		else
		{
			cout << "\n\x1b[31mUser Was Not Found :(\x1b[0m\n";
		}

		_PrintUser(User);
	}
};