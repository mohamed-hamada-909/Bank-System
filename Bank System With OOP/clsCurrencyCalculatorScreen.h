#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

	static clsCurrency _GetCurrency(string Message)
	{
		string Code = "";
		cout << Message;
		Code = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrentExist(Code))
		{
			cout << "\nCurrency is Not Found, Choose Another One: ";
			Code = clsInputValidate::ReadString();
		}
		return clsCurrency::FindByCode(Code);
	}

	static float _ReadAmount()
	{
		cout << "\nEnter Amount To ExChange: ";
		float Amount = clsInputValidate::ReadDbNumberBetween(1, 100000000);

		return Amount;
	}

	static void _PrintCurrencyCard(clsCurrency& Currency , string Message)
	{
		cout << Message;
		cout << "--------------------------\n\n";
		cout << "Country : " << Currency.Country() << endl;
		cout << "Code    : " << Currency.CurrencyCode() << endl;
		cout << "Name    : " << Currency.CurrencyName() << endl;
		cout << "Rate(1$): " << Currency.Rate() << endl;
		cout << "\n--------------------------\n";
	}

	static void _PrintCalculationResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
	{
		_PrintCurrencyCard(Currency1, "\nConvert From:\n");
		float AmountUSD = Currency1.ConvertToUSD(Amount);

		cout << Amount << " " << Currency1.CurrencyCode() <<
			" = " << AmountUSD << " USD\n";

		if (Currency2.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "\nConverting From USD To:\n";
		_PrintCurrencyCard(Currency2, "\nConvert To:\n");

		float AmountToOther = Currency1.ConvertToOtherCurrency(Amount, Currency2);

		cout << Amount << " " << Currency1.CurrencyCode() << " = "
			<< AmountToOther << " " << Currency2.CurrencyCode();
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		char Continue = 'y';

		while (Continue == 'Y' || Continue == 'y')
		{
			system("cls");
			_DrawScreenHeader("\tCurrency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency Code1: ");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency Code2: ");
			float Amount = _ReadAmount();

			_PrintCalculationResults(Amount, CurrencyFrom, CurrencyTo);	

			cout << "\n\nDo You Want To Perform Another Calculator? Y/N";
			cin >> Continue;
		}
	}
};