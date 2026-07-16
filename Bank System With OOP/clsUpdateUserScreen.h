#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
private:

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\n\x1b[36mEnter First Name:\x1b[0m ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\n\x1b[36mEnter Last Name:\x1b[0m ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\n\x1b[36mEnter Email:\x1b[0m ";
		User.Email = clsInputValidate::ReadString();

		cout << "\n\x1b[36mEnter Phone:\x1b[0m ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\n\x1b[31mEnter Password:\x1b[0m ";
		User.Password = clsInputValidate::ReadString();

		cout << "\n\x1b[32mEnter Permission:\x1b[0m ";
		User.Permission = _ReadPermissionToSet();
	}

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

	static int _ReadPermissionToSet()
	{
		int Permission = 0;
		char Answer = 'n';

		cout << "\n\x1b[33mDo You Want To Give Full Access? Y/N?\x1b[0m ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			return -1;
		}

		cout << "\n\x1b[32mDo You Want To Give Access To:\x1b[0m\n";

		cout << "\n\x1b[33mShow Client List? Y/N\x1b[0m ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permission += clsUser::enPermission::pListClient;

		cout << "\n\x1b[33mAdd New Client? Y/N?\x1b[0m ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permission += clsUser::enPermission::pAddNewClient;

		cout << "\n\x1b[33mDelete Client? Y/N?\x1b[0m ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permission += clsUser::enPermission::pDeleteCLient;

		cout << "\n\x1b[33mUpdate Client? Y/N?\x1b[0m ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permission += clsUser::enPermission::pUpdateClient;

		cout << "\n\x1b[33mFind Client? Y/N?\x1b[0m ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permission += clsUser::enPermission::pFindClient;

		cout << "\n\x1b[33mTransaction? Y/N?\x1b[0m ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permission += clsUser::enPermission::pTransaction;

		cout << "\n\x1b[33mManage Users? Y/N?\x1b[0m ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permission += clsUser::enPermission::pManageUsers;

		cout << "\n\x1b[33mShow Login Register? Y/N?\x1b[0m ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permission += clsUser::enPermission::pLoginRegister;

		cout << "\n\x1b[33mShow Currency ExChange? Y/N?\x1b[0m ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permission += clsUser::enPermission::pCurrencyExchange;

		return Permission;
	}

public:
	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\t  \x1b[36mUpdate User Screen\x1b[0m");

		string UserName = "";

		cout << "\n\x1b[31mEnter User Name:\x1b[0m ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\n\x1b[31mUser Not Found, Choose Another:\x1b[0m ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		cout << "\x1b[33mAre You Sure You Want To Update This User? Y/N?\x1b[0m ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			cout << "\n\x1b[36mUpdate Info:\x1b[0m\n";
			cout << "\n___________________________";

			_ReadUserInfo(User);

			clsUser::enSaveResults SaveResult;
			SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::svSucceeded:
			{
				cout << "\n\x1b[32mUser Updated Successfully :)\x1b[0m\n";
				_PrintUser(User);
				break;
			}
			case clsUser::svFaildEmptyObject:
			{
				cout << "\n\x1b[31mError: User Was Not Updated Because It's Empty :(\x1b[0m\n";
				break;
			}
			}
		}
		else
		{
			cout << "\n\x1b[33mOperation Was Cancelled.\x1b[0m\n";
		}
	}
};