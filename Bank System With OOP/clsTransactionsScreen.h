#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:

	enum enTransactionOption
	{
		eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4,
		eTransferScreen = 5, eMainMenue = 6
	};

	static short _ReadTransactionsOption()
	{
		cout << setw(39) << left << "" << "Choose What Do You To Do? [1] To [6]? ";

		short choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Invalid Number, Enter Again: ");

		return choice;
	}

	static void _GoBackToTransactionMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transaction Screen...\n";

		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionMenueOption(enTransactionOption Option)
	{
		switch (Option)
		{
		case enTransactionOption::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionOption::eWithdraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionOption::eTotalBalances:
		{
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionOption::eTransfer:
		{
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionOption::eTransferScreen:
		{
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionOption::eMainMenue:
		{
			
		}
		}
	}
	
public:

	static void ShowTransactionsMenue()
	{
		if (!CheckAccessRight(clsUser::enPermission::pTransaction))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << setw(39) << left << "" << "=========================================\n";
		cout << setw(39) << left << "" << "\t\t\x1b[36mTransactions Menu\x1b[0m\n";
		cout << setw(39) << left << "" << "=========================================\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[1] Deposit.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[2] Withdraw.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[3] Total Balances.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[4] Transfer.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[5] Transfer Log.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[6] Main Menu.\x1b[0m\n";
		cout << setw(39) << left << "" << "=========================================\n";

		_PerformTransactionMenueOption((enTransactionOption)_ReadTransactionsOption());
	}
};