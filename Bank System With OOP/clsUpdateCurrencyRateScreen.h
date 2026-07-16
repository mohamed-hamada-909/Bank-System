#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

	static float _ReadRate()
	{
		float Rate = 0;

		cout << "\nEnter New Rate: ";
		Rate = clsInputValidate::ReadDbNumber();

		return Rate;
	}

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

public:

	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\t  Update Currency Screen");

		cout << "\nPlease Enter Currency Code: ";
		string Code = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrentExist(Code))
		{
			cout << "\nCurrency is Not Found, Choose Another: ";
			Code = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(Code);
		_PrintCurrencyCard(Currency);
		
		cout << "\nAre You Sure You Want To Update The Rate of This Currency? Y/N";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			cout << "\nUpdate Currency Rate: \n";
			cout << "---------------------------\n";
			Currency.UpdateRate(_ReadRate());
			
			cout << "\nCurrency Rate Updated Successfully\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nUpdate Was Cancelled :(\n";
		}
	}
};