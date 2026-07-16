#pragma once

#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "Global.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenueOption
	{
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,
		eFindClient = 5, eShowTransactionMenue = 6, eManageUsers = 7, eLoginRegister = 8,
		eCurrencyExchange = 9, eLogout = 10
	};

	static short _ReadMainMenueOption()
	{
		cout << setw(39) << left << "" << "\x1b[33mChoice What Do You Want To Do [1] To [10]: \x1b[0m";

		short choice = clsInputValidate::ReadIntNumberBetween(1, 10, "Enter Number Between [1] to [10]");
		return choice;
	}

	static void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowMainMenue();

	}

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenue()
	{
		clsManageUsers::ShowManageUsersMenue();
	}

	static void _ShowLogingRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeScreen()
	{
		clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _PerformMainMenueOption(enMainMenueOption Option)
	{
		switch (Option)
		{
		case enMainMenueOption::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eAddNewClient:
		{
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eDeleteClient:
		{
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eUpdateClient:
		{
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eFindClient:
		{
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eShowTransactionMenue:
		{
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eManageUsers:
		{
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eLoginRegister:
		{
			system("cls");
			_ShowLogingRegisterScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eCurrencyExchange:
		{
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eLogout:
		{
			system("cls");
			_Logout();
			break;
		}
		}
	}

public:

	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\t\t\x1b[36mMain Screen\x1b[0m");

		cout << setw(39) << left << "" << "=========================================\n";
		cout << setw(39) << left << "" << "\x1b[36m\t\t\tMain Screen\x1b[0m\n";
		cout << setw(39) << left << "" << "=========================================\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[1] Show Client List.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[2] Add New Client.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[3] Delete Client.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[4] Update Client.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[5] Find Client.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[6] Transactions.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[7] Manage Users.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[8] Login Register.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[9] Currency Exchange.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[10] Logout.\x1b[0m\n";
		cout << setw(39) << left << "" << "=========================================\n";

		_PerformMainMenueOption((enMainMenueOption)_ReadMainMenueOption());
	}
};