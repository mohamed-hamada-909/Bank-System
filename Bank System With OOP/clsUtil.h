#pragma once

#include <iostream>
#include "clsDate.h"

using namespace std;

class clsUtil
{
public:

	enum enCharType { enSmall = 1, enCapital = 2, enDigit = 3, enMix = 4, enSpecial = 5 };

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{
		int RandomNum = rand() % (To - From + 1) + From;

		return RandomNum;
	}

	static char GetRandomChar(enCharType Type)
	{
		if (Type == enMix)
		{
			Type = (enCharType)RandomNumber(1, 3);
		}

		switch (Type)
		{
		case enCharType::enSmall:
		{
			return char(RandomNumber('a', 'z'));
			break;
		}
		case enCharType::enCapital:
		{
			return char(RandomNumber('A', 'Z'));
			break;
		}
		case enCharType::enSpecial:
		{
			return char(RandomNumber(33, 47));
			break;
		}
		case enCharType::enDigit:
		{
			return char(RandomNumber('0', '9'));
			break;
		}
	defualt:
		{
			return char(RandomNumber('A', 'Z'));
			break;
		}
		}
	}
	
	static string GenerateWord(enCharType Type, short Length)
	{
		string word = "";

		for (short i = 1; i <= Length; i++)
		{
			word += GetRandomChar(Type);
		}
		return word;
	}

	static string GenerateKey(enCharType Type = enCapital)
	{
		string Key = "";

		Key = GenerateWord(Type, 4) + "_";
		Key += GenerateWord(Type, 4) + "_";
		Key += GenerateWord(Type, 4) + "_";
		Key += GenerateWord(Type, 4);

		return Key;
	}

	static void GenerateKeys(short Number, enCharType Type)
	{
		for (short i = 1; i <= Number; i++)
		{
			cout << "Key [" << i << "] : ";

			cout << GenerateKey(Type) << endl;
		}
	}

	static void FillArrayWithRandomNumbers(int arr[10],short Length,int From,int To)
	{
		for (short i = 0; i < Length; i++)
		{
			arr[i] = RandomNumber(From, To);
		}
	}

	static void FillArrayWithRandomWords(string arr[10], short arrLength, enCharType Type, short WordLenght)
	{
		for (short i = 0; i < arrLength; i++)
		{
			arr[i] = GenerateWord(Type, 8);
		}
	}

	static void FillArrayWithRandomKeys(string arr[10], short Length, enCharType Type)
	{
		for (short i = 0; i < Length; i++)
		{
			arr[i] = GenerateKey(Type);
		}
	}

	static  void Swap(int& A, int& B)
	{
		int Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(double& A, double& B)
	{
		double Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(bool& A, bool& B)
	{
		bool Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(char& A, char& B)
	{
		char Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(string& A, string& B)
	{
		string Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(clsDate& A, clsDate& B)
	{
		clsDate::SwapDates(A, B);
	}

	static  void ShuffleArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static  void ShuffleArray(string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static string  EncryptText(string Text, short EncryptionKey = 2)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char((int)Text[i] + EncryptionKey);
		}
		return Text;
	}
	
	static string  DecryptText(string Text, short DecryptionKey = 2)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char((int)Text[i] - DecryptionKey);
		}
		return Text;
	}

	static string  Tabs(short NumberOfTabs)
	{
		string t = "";

		for (int i = 1; i < NumberOfTabs; i++)
		{
			t += "\t";
			cout << t;
		}
		return t;
	}

	static string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";

		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}
	}
};