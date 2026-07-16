#pragma once

#include <iostream>
#include <string>
#include "clsDate.h"
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _permissions;
	bool _MarkForDelete = false;

	string _PerpareLoginRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";

		LoginRecord = clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permission);

		return LoginRecord;
	}

	struct stLoginRegister;
	static stLoginRegister _ConverLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegister LoginRegister;

		vector <string> vLoginRegister = clsString::Split(Line, Seperator);

		LoginRegister.DateTime = vLoginRegister[0];
		LoginRegister.Username = vLoginRegister[1];
		LoginRegister.Password = clsUtil::DecryptText(vLoginRegister[2]);
		LoginRegister.Permission = stoi(vLoginRegister[3]);

		return LoginRegister;
	}

	static clsUser _ConverLineToUserObject(string Line, string Seperator = "#//#")
	{
		vector <string> vUsers;
		vUsers = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUsers[0], vUsers[1], vUsers[2], vUsers[3], vUsers[4], clsUtil::DecryptText(vUsers[5]), stoi(vUsers[6]));
	}
	 
	static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string Line = "";

		Line = User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User.UserName + Seperator;
		Line += clsUtil::EncryptText(User.Password) + Seperator;
		Line += to_string(User.Permission);

		return Line;
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> vUsers;

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);
		
		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				clsUser User = _ConverLineToUserObject(DataLine);

				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> Users)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsUser& U : Users)
			{
				if (U.MarkForDeleted() == false)
				{
					DataLine = _ConverUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _AddDataLineToFile(string Line)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.GetUserName() == GetUserName())
			{
				U = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}

	static clsUser _GetEmptyUser()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	enum enPermission
	{
		eAll = -1, pListClient = 1, pAddNewClient = 2, pDeleteCLient = 4, pUpdateClient = 8,
		pFindClient = 16, pTransaction = 32, pManageUsers = 64,
		pLoginRegister = 128, pCurrencyExchange = 256
	};

	struct stLoginRegister
	{
		string DateTime;
		string Username;
		string Password;
		int Permission;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string
		UserName, string Password, int Permission) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_permissions = Permission;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkForDeleted()
	{
		return _MarkForDelete;
	}

	//User Name
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName))string UserName;

	//Password
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;

	//Permission
	void SetPermission(int Permission)
	{
		_permissions = Permission;
	}
	int GetPermission()
	{
		return _permissions;
	}
	__declspec(property(get = GetPermission, put = SetPermission))int Permission;

	static clsUser Find(string UserName)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConverLineToUserObject(Line);

				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUser();
	}

	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConverLineToUserObject(Line);

				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUser();
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());
	}

	enum enSaveResults { svSucceeded, svFaildEmptyObject, svFaildUserExist };
		
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return enSaveResults::svFaildEmptyObject;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUserExist;
			}
			else
			{
				_AddNew();

				_Mode = enMode::AddNewMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
		}
	}
		
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUser();
		return true;
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermission Permission)
	{
		if (this->Permission == enPermission::eAll)
		{
			return true;
		}

		if ((Permission & this->Permission) == Permission)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void RegisterLogin()
	{
		string DataLine = _PerpareLoginRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	static vector <stLoginRegister> GetLoginRegisterList()
	{
		vector <stLoginRegister> vLoginRegister;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			stLoginRegister LoginRegister;

			while (getline(MyFile, Line))
			{
				LoginRegister = _ConverLoginRegisterLineToRecord(Line);

				vLoginRegister.push_back(LoginRegister);
			}
			MyFile.close();
		}
		return vLoginRegister;
	}
};