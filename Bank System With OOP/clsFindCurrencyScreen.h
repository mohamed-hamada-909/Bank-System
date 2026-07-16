#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n\n";
		cout << "--------------------------\n\n";
		cout << "Country : " << Currency.Country() << endl;
		cout << "Code    : " << Currency.CurrencyCode() << endl;
		cout << "Name    : " << Currency.CurrencyName() << endl;
		cout << "Rate(1$): " << Currency.Rate() << endl;
		cout << "--------------------------\n\n";
	}

	static void _ShowResult(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :)\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrency Was Not Found :(\n";
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t  Find Currency Screen");

		short Answer = 0;
		cout << "\nFind By [1] Code or [2] Country? ";
		Answer = clsInputValidate::ReadIntNumberBetween(1, 2, "Enter Invalid Number");

		if (Answer == 1)
		{
			cout << "\nPlease Enter Currency Code: ";
			string Code = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCode(Code);
			_ShowResult(Currency);
		}
		else
		{
			cout << "\nPlease Enter Country Name: ";
			string Name = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCountry(Name);
			_ShowResult(Currency);
		}

	}
};