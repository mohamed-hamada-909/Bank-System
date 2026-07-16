#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:

	static void _PrintCurrenciesList(clsCurrency& Currency)
	{
		cout << setw(8) << left << "" << "| " << "\x1b[36m" << setw(30) << left << Currency.Country() << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(8) << left << Currency.CurrencyCode() << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(45) << left << Currency.CurrencyName() << "\x1b[0m";
		cout << "| " << "\x1b[36m" << setw(10) << left << Currency.Rate() << "\x1b[0m";
	}

public:

	static void ShowCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrency = clsCurrency::GetCurrenciesList();

		string Title = "\t  \x1b[36mCurrencies List Screen\x1b[0m";
		string SubTitle = "\t   (\x1b[33m" + to_string(vCurrency.size()) + "\x1b[0m) Currency.";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t" << string(102, '_') << "\n\n";

		cout << setw(8) << left << "" << "| " << "\x1b[36m" << left << setw(30) << "Country" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(8) << "Code" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(45) << "Name" << "\x1b[0m";
		cout << "| " << "\x1b[36m" << left << setw(10) << "Rate/(1$)" << "\x1b[0m";

		cout << setw(8) << left << "" << "\n\t" << string(102, '_') << "\n\n";

		if (vCurrency.size() == 0)
		{
			cout << "\t\t\t\t\x1b[31mNo Currencies Available in The System!\x1b[0m\n";
		}
		else
		{
			for (clsCurrency& C : vCurrency)
			{
				_PrintCurrenciesList(C);
				cout << "\n";
			}
		}
		cout << setw(8) << left << "" << "\n\t" << string(102, '_') << "\n\n";
	}
};