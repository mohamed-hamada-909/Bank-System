#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsDate.h"
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 3 };
	enMode _Mode;

	string _AccNumber;
	string _PINCode;
	float _AccBalance;
	bool _MarkForDelete = false;

	struct stTransferLog;
	static stTransferLog _ConvertTransferLogToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLog TransferLog;

		vector <string> vdata = clsString::Split(Line, Seperator);

		TransferLog.DataTime = vdata[0];
		TransferLog.sAccount = vdata[1];
		TransferLog.dAccount = vdata[2];
		TransferLog.Amount = stod(vdata[3]);
		TransferLog.sBalance = stoi(vdata[4]);
		TransferLog.dBalance = stoi(vdata[5]);
		TransferLog.Username = vdata[6];

		return TransferLog;
	}

	string _PrepareTransferRecord(float Amount, clsBankClient DestinationClient,
		string Username, string Seperator = "#//#")
	{
		string DataLine = "";

		DataLine = clsDate::GetSystemDateTimeString() + Seperator;
		DataLine += GetAccNumber() + Seperator;
		DataLine += DestinationClient.GetAccNumber() + Seperator;
		DataLine += to_string(Amount) + Seperator;
		DataLine += to_string(AccBalance) + Seperator;
		DataLine += to_string(DestinationClient.AccBalance) + Seperator;
		DataLine += Username;

		return DataLine;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string Username)
	{
		string DataLine = _PrepareTransferRecord(Amount, DestinationClient, Username);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	static clsBankClient _ConverLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector <string> vClient;
		vClient = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stod(vClient[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string Line = "";

		Line = Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.GetAccNumber() + Seperator;
		Line += Client.PINCode + Seperator;
		Line += to_string(Client.AccBalance);

		return Line;
	}

	static vector <clsBankClient> _LoadClientDateFromFile()
	{
		vector <clsBankClient> vclients;

		fstream MyFile;

		MyFile.open("Clients Data.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConverLineToClientObject(Line);
				vclients.push_back(Client);
			}
			MyFile.close();
		}
		return vclients;
	}

	static void _SaveClientDataToFile(vector <clsBankClient> Clients)
	{
		fstream MyFile;

		MyFile.open("Clients Data.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient& C : Clients)
			{
				if (C.MarkForDelete() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;

		MyFile.open("Clients Data.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> vclients;
		vclients = _LoadClientDateFromFile();

		for (clsBankClient& C : vclients)
		{
			if (C.GetAccNumber() == GetAccNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientDataToFile(vclients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	static clsBankClient _GetEmptyClient()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	struct stTransferLog
	{
		string DataTime;
		string sAccount;
		string dAccount;
		float Amount;
		float sBalance;
		float dBalance;
		string Username;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccNumber,
		string PINCode, float AccBalance) :clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccNumber = AccNumber;
		_PINCode = PINCode;
		_AccBalance = AccBalance;
	}

	//Account Number
	void SetAccNumber(string AccNumber)
	{
		_AccNumber = AccNumber;
	}
	string GetAccNumber()
	{
		return _AccNumber;
	}
	__declspec(property(get = GetAccNumber, put = SetAccNumber))string AccNumber;

	//PIN Code
	void SetPINCode(string PINCode)
	{
		_PINCode = PINCode;
	}
	string GetPINCode()
	{
		return _PINCode;
	}
	__declspec(property(get = GetPINCode, put = SetPINCode))string PINCode;

	//Account Balance
	void SetBalance(float Balance)
	{
		_AccBalance = Balance;
	}
	float GetBalance()
	{
		return _AccBalance;
	}
	__declspec(property(get = GetBalance, put = SetBalance))float AccBalance;

	//Find Client By Account Number
	static clsBankClient Find(string AccNumber)
	{
		fstream MyFile;

		MyFile.open("Clients Data.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConverLineToClientObject(Line);

				if (Client.AccNumber == AccNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClient();
	}

	//Find Client By Account Number && PIN Code
	static clsBankClient Find(string AccNumber, string PINCode)
	{
		fstream MyFile;

		MyFile.open("Clients Data.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConverLineToClientObject(Line);

				if (Client.AccNumber == AccNumber && Client.PINCode == PINCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClient();
	}
	
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkForDelete()
	{
		return _MarkForDelete;
	}

	static bool IsClientExist(string AccNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccNumber);

		return (!Client.IsEmpty());
	}

	enum enSaveResults { svFaildEmpty = 0, svSucceeded = 1, svFaildAccNumberExist = 3 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return enSaveResults::svFaildEmpty;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}
		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccNumber))
			{
				return enSaveResults::svFaildAccNumberExist;
			}
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
		}
	}

	static clsBankClient GetAddNewClientObject(string AccNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> vData;
		vData = _LoadClientDateFromFile();

		for (clsBankClient& C : vData)
		{
			if (C.GetAccNumber() == _AccNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveClientDataToFile(vData);

		*this = _GetEmptyClient();
		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientDateFromFile();
	}

	static float GetTotalBalances()
	{
		vector <clsBankClient> vClient = GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient& C : vClient)
		{
			TotalBalances += C.AccBalance;
		}
		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccBalance += Amount;

		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount>_AccBalance)
		{
			return false;
		}
		else
		{
			_AccBalance -= Amount;
			Save();
		}
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient, string Username)
	{
		if (Amount > AccBalance || (GetAccNumber() == DestinationClient.GetAccNumber()))
		{
			return false;
		}
		else
		{
			Withdraw(Amount);
			DestinationClient.Deposit(Amount);
			_RegisterTransferLog(Amount, DestinationClient, Username);

			return true;
		}
	}

	static vector <stTransferLog> GetTransferLogList()
	{
		vector <stTransferLog> vTransferLog;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			stTransferLog TransferLog;

			while (getline(MyFile, Line))
			{
				TransferLog = _ConvertTransferLogToRecord(Line);

				vTransferLog.push_back(TransferLog);
			}
			MyFile.close();
		}
		return vTransferLog;
	}
};