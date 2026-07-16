#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:

	enum enCurrencyOption
	{
		eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenu = 5
	};

	static short _ReadCurrencyOption()
	{
		cout << setw(39) << left << "" << "\x1b[33mChoice What Do You Want To Do [1] To [5]: \x1b[0m";

		short choice = clsInputValidate::ReadIntNumberBetween(1, 5, "Enter Number Between [1] to [5]");
		return choice;
	}

	static void _GoBackToCurrencyExChangeMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Currencies Menue...\n";

		system("pause>0");
		ShowCurrencyExchangeScreen();
	}

	static void _ShowListCurrenciesListScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void PerformCurrencyOption(enCurrencyOption Option)
	{
		switch (Option)
		{
		case clsCurrencyExchangeScreen::eListCurrencies:
		{
			system("cls");
			_ShowListCurrenciesListScreen();
			_GoBackToCurrencyExChangeMenu();
			break;
		}
		case clsCurrencyExchangeScreen::eFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExChangeMenu();
			break;
		}
		case clsCurrencyExchangeScreen::eUpdateRate:
		{
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExChangeMenu();
			break;
		}
		case clsCurrencyExchangeScreen::eCurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExChangeMenu();
			break;
		}
		case clsCurrencyExchangeScreen::eMainMenu:
		{
			
		}
		}
	}

public:

	static void ShowCurrencyExchangeScreen()
	{
		if (!CheckAccessRight(clsUser::enPermission::pCurrencyExchange))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("   Currency ExChange Main Screen");

		cout << setw(39) << left << "" << "=========================================\n";
		cout << setw(39) << left << "" << "\x1b[36m\t\tCurrency Exchange Menu\x1b[0m\n";
		cout << setw(39) << left << "" << "=========================================\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[1] List Currencies.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[2] Find Currency.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[3] Update Rate.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[4] Currency Calculator.\x1b[0m\n";
		cout << setw(39) << left << "" << "\t\x1b[33m[5] Main Menu.\x1b[0m\n";
		cout << setw(39) << left << "" << "=========================================\n";

		PerformCurrencyOption((enCurrencyOption)_ReadCurrencyOption());
	}
};