#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
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

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t  \x1b[36mDelete User Screen\x1b[0m");

		string UserName = "";

		cout << "\n\x1b[31mEnter UserName:\x1b[0m ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\n\x1b[31mUser Not Found, Choose Another One:\x1b[0m ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);

		cout << "\n\x1b[33mDo You Want To Delete This User? Y/N?\x1b[0m ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (User1.Delete())
			{
				cout << "\n\x1b[32mUser Deleted Successfully :)\x1b[0m\n";
				_PrintUser(User1);
			}
			else
			{
				cout << "\n\x1b[31mError: User Was Not Deleted :(\x1b[0m\n";
			}
		}
		else
		{
			cout << "\n\x1b[33mThe Operation Was Cancelled.\x1b[0m\n";
		}
	}
};