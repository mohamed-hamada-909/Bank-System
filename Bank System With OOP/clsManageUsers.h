#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUserListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsers : protected clsScreen
{
private:

	enum enManageUsers
	{
		eListUser = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, FindUser = 5, eMainMenue = 6
	};

	static short _ReadManageUserOption()
	{
		cout << setw(39) << left << "" << "Choose What Do You Want To Do [1] To [6] ? ";

		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number Between [1] To [6]?");
		return Choice;
	}

	static void _GoBackMangaeUserMenue()
	{
		cout << setw(39) << left << "" << "\n\tPress any key to go back to Manage User Menue...\n";

		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowListUserScreen()
	{
		clsUserListScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}
	
	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersScreen(enManageUsers Option)
	{
		system("cls");

		switch (Option)
		{
		case clsManageUsers::eListUser:
		{
			_ShowListUserScreen();
			break;
		}
		case clsManageUsers::eAddUser:
		{
			_ShowAddNewUserScreen();
			break;
		}
		case clsManageUsers::eDeleteUser:
		{
			_ShowDeleteUserScreen();
			break;
		}
		case clsManageUsers::eUpdateUser:
		{
			_ShowUpdateUserScreen();
			break;
		}
		case clsManageUsers::FindUser:
		{
			_ShowFindUserScreen();
			break;
		}
		case clsManageUsers::eMainMenue:
		{
		
		}
		}

		if (Option != enManageUsers::eMainMenue)
		{
			_GoBackMangaeUserMenue();
		}
	}

public:

	static void ShowManageUsersMenue()
	{
		if (!CheckAccessRight(clsUser::enPermission::pManageUsers))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t  Manage Users Screen");

		cout << setw(39) << left << "" << "=========================================\n";
		cout << setw(39) << left << "" << "\t\t\x1b[36mManage Users Menu\x1b[0m\n";
		cout << setw(39) << left << "" << "=========================================\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[1] List Users.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[2] Add New User.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[3] Delete User.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[4] Update User.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[5] Find User.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[6] Main Menue.\x1b[0m\n";
		cout << setw(39) << left << "" << "=========================================\n";

		_PerformManageUsersScreen((enManageUsers)_ReadManageUserOption());
	}
};