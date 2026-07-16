#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConverLineToCurrencyObject(string Line, string Seperator = "#//#")
	{
		vector <string> vCurrency;
		vCurrency = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2], stod(vCurrency[3]));
	}

	static string _CovertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{
		string Line = "";

		Line = Currency.Country() + Seperator;
		Line += Currency.CurrencyCode() + Seperator;
		Line += Currency.CurrencyName() + Seperator;
		Line += to_string(Currency.Rate());

		return Line;
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector <clsCurrency> vCurrency;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency C = _ConverLineToCurrencyObject(Line);
				vCurrency.push_back(C);
            }
			MyFile.close();
		}
		return vCurrency;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrency)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine;

			for (clsCurrency& C : vCurrency)
			{
				DataLine = _CovertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vCurrency = _LoadCurrencyDataFromFile();

		for (clsCurrency& C : vCurrency)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
			}
		}
		_SaveCurrencyDataToFile(vCurrency);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float Rate)
	{
		_Rate = Rate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConverLineToCurrencyObject(Line);

				if (Currency.CurrencyCode() == CurrencyCode)
				{
					return Currency;
					MyFile.close();
				}
			}
				MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConverLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					return Currency;
					MyFile.close();
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrentExist(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float USD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return USD;
		}

		return (float)(USD * Currency2.Rate());
	}
};