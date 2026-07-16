#pragma once

#include <iostream>
#include "clsDate.h"
#include "clsString.h"

using namespace std;

class clsInputValidate
{
public:

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(short Number, short From, short To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate Date1, clsDate Date2)
	{
		if (clsDate::IsDate1AfterDate2(Date1, Date2))
		{
			clsDate::SwapDates(Date1, Date2);
		}

		return !clsDate::IsDate1BeforeDate2(Date, Date1) && !clsDate::IsDate1AfterDate2(Date, Date2);
	}

	static int ReadIntNumber(string Message="Invalid Number, Enter Again:\n")
	{
		int x;

		while (!(cin >> x))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << Message << endl;
		}
		return x;
	}

	static double ReadDbNumber(string Message = "Invalid Number, Enter Again:\n")
	{
		double x;

		while (!(cin >> x))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << Message << endl;
		}
		return x;
	}

	static int ReadIntNumberBetween(int From, int To, string Message = "Invalid Number, Enter Again:\n")
	{
		int x = ReadIntNumber();

		while (!IsNumberBetween(x, From, To))
		{
			cout << Message << endl;
			x = ReadIntNumber();
		}
		return x;
	}

	static double ReadDbNumberBetween(double From, double To, string Message = "Invalid Number, Enter Again:\n")
	{
		double x = ReadDbNumber();

		while (!IsNumberBetween(x, From, To))
		{
			cout << Message << endl;
			x = ReadDbNumber();
		}
		return x;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string  S1 = "";
		
		getline(cin >> ws, S1);
		return S1;
	}
};