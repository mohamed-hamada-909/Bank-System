#pragma once

#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
	string _Value;

public:

	clsString()
	{
		_Value = "";
	}

	clsString(string st)
	{
		_Value = st;
	}

	//Set Value
	void setValue(string st)
	{
		_Value = st;
	}
	
	//Get Value
	string GetValue()
	{
		return _Value;
	}

	__declspec(property(get = GetValue, put = setValue))string Value;

	//Length
	static short Length(string S1)
	{
		return S1.length();
	}
	short Length()
	{
		return _Value.length();
	}

	//Conver The First Letter of Each Word To Upper
	static string UpperFirstLetterOfEachWord(string S1)
	{
		bool isFirstLetter = true;

		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = toupper(S1[i]);
			}
			isFirstLetter = (S1[i] == ' ' ? true : false);
		}
		return S1;
	}
	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	//Conver The First Letter of Each Word To Lower
	static string LowerFirstLetterOfEachWord(string S1)
	{
		bool isFirstLetter = true;
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = tolower(S1[i]);
			}
			isFirstLetter = (S1[i] == ' ' ? true : false);
		}
		return S1;
	}
	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	//Upper All String
	static string UpperAllString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}
		return S1;
	}
	void UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	//Lower All String
	static string LowerAllString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}
	void LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	//Invert Character Case
	static char InvertLetterCase(char char1)
	{
		return isupper(char1) ? tolower(char1) : toupper(char1);
	}
	
	//Inver All Letters Case
	static string InvertAllStringLettersCase(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = InvertLetterCase(S1[i]);
		}
		return S1;
	}
	void InvertAllStringLettersCase()
	{
		_Value = InvertAllStringLettersCase(_Value);
	}

	//Count Capital Letter
	short CountCapitalLetters(string S1)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (isupper(S1[i]))
				Counter++;
		}
		return Counter;
	}
	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	//Count Small Letter
	short CountSmallLetters(string S1)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (islower(S1[i]))
				Counter++;
		}
		return Counter;
	}
	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	//Count Specific Letter
	static short CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
	{
		short Counter = 0; 
		for (short i = 0; i < S1.length(); i++)
		{
			if (MatchCase)
			{
				if (S1[i] == Letter)
					Counter++;
			}
			else 
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}
		}
		return Counter;
	}
	short CountSpecificLetter(char Letter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value,Letter,MatchCase);
	}

	//Count The Number of Words in a String
	static short CountWords(string S1)
	{
		short pos = 0;
		short counter = 0;
		string word;
		string delim = " ";

		while ((pos = S1.find(delim)) != string::npos)
		{
			word = S1.substr(0, pos);

			if (word != "")
			{
				counter++;
			}
			//erase() until positon and move to next word.
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
		{
			counter++;
		}
		return counter;
	}
	short CountWords()
	{
		return CountWords(_Value);
	}

	//Vowel Character
	static bool IsVowel(char Ch1)
	{
		Ch1 = tolower(Ch1);

		return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
	}

	//Count Vowels
	static short CountVowels(string S1)
	{
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (IsVowel(S1[i]))
				Counter++;
		}

		return Counter;
	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}

	//Print Each Word in String
	static void PrintEachWordInString(string S1)
	{
		string delim = " "; // delimiter
		short pos = 0;
		string sWord; 

		cout << "\nYour string wrords are: \n\n";

		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); 
			if (sWord != "")
			{
				cout << sWord << endl;
			}
			S1.erase(0, pos + delim.length()); 
		}
		if (S1 != "")
		{
			cout << S1 << endl; 
		}
	}
	void PrintEachWordInString()
	{
		PrintEachWordInString(_Value);
	}

	//Split String //Edint Here
	static vector<string> Split(string S1, string Delim)
	{
		vector<string> vString;
		short pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				vString.push_back(sWord);
			}
			S1.erase(0, pos + Delim.length()); //erase() until positon and move to next word
			
		}
		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}
		return vString;
	}

	//Trim Left
	static string TrimLeft(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - i);
			}
		}
		return "";
	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	//Trim Right
	static string TrimRight(string S1)
	{
		for (short i = S1.length() - 1; i >= 0; i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i + 1);
			}
		}
		return "";
	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	//Trim
	string Trim(string S1)
	{
		return (TrimLeft(TrimRight(S1)));
	}
	void Trim()
	{
		_Value = Trim(_Value);
	}

	//Join String With Vector
	static string JoinString(vector<string> vString, string Delim)
	{
		string S1 = "";
		for (string& s : vString)
		{
			S1 = S1 + s + Delim;
		}
		return S1.substr(0, S1.length() - Delim.length());
	}
	
	//Join String With Array 
	static string JoinString(string arrstring[], short length, string delim)
	{
		string S1 = "";

		for (short i = 0; i < length; i++)
		{
			S1 = S1 + arrstring[i] + delim;
		}
		S1.erase(0, S1.length() - delim.length());
	}

	//Reverse Words
	static string ReverseWordsInString(string S1)
	{
		vector<string> vString;
		string S2 = "";
		vString = Split(S1, " ");
		// declare iterator
		vector<string>::iterator iter = vString.end();
		while (iter != vString.begin())
		{
			--iter;
			S2 += *iter + " ";
		}
		S2 = S2.substr(0, S2.length() - 1); //remove last space.
		return S2;
	}
	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}

	//Replace Words
	static string ReplaceWord(string S1, string sToReplace, string sReplaceTo)
	{
		short pos = S1.find(sToReplace);
		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, sToReplace.length(),sReplaceTo);
				
			pos = S1.find(sToReplace);//find next
		}
		return S1;
	}
	string ReplaceWord(string sToReplace, string sReplaceTo)
	{
		return ReplaceWord(_Value, sToReplace, sReplaceTo);
	}

	//Remove Punctuation
	static string RemovePunctuationsFromString(string S1)
	{
		string S2 = "";
		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}
		return S2;
	}
	void RemovePunctuationsFromString()
	{
		_Value = RemovePunctuationsFromString(_Value);
	}
};