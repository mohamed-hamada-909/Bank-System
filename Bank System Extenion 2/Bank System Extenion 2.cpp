#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string DataFileName = "Clients Data.txt";
const string UsersFileName = "Users.txt";

enum enMainMenueOption
{
    showclient = 1, addnewclient = 2, deleteclient = 3
    , updateclient = 4, findclient = 5, etransactions = 6, magageuser = 7, logout = 8
};

enum enTransactionOption
{
    edeposit = 1, ewithdraw = 2, etotalbalance = 3, emainmenue = 4
};

enum enUserMeueOption
{
    eListUser = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
};

enum enMainMenuePermission
{
    eall = -1, pListUser = 1, pAddNewUser = 2, pDeleteUser = 4, pUpdateUser = 8,
    pFindUser = 16,pTransactio = 32, pManageUser = 64
};

void PrintMainMenue();
void Login();
bool CheckAccessPermission(enMainMenuePermission permission);
void PrintTransactionScreen();
void PrintManageUserMenue();

struct stUsers
{
    string Username;
    string Password;
    short Permission;
    bool MarkForDelete = false;
};

stUsers CurrentUser;

struct stClients
{
    string accountnum;
    string pincode;
    string name;
    string phone;
    double balance;
    bool ismarked = false;
};

string ReadAccountNumber()
{
    string st;
    cout << "Enter Account Number \n";
    cin >> st;

    return st;
}

vector <string>SplitString(string st, string delim)
{
    vector <string> vdata;
    string word = "";
    short pos = 0;

    while ((pos = st.find(delim)) != string::npos)
    {
        word = st.substr(0, pos);

        if (word != "")
        {
            vdata.push_back(word);
        }
        st.erase(0, pos + delim.length());
    }
    if (st != "")
    {
        vdata.push_back(st);
    }
    return vdata;
}

stClients ConvertLineToRecord(string st, string seperator = "#//#")
{
    stClients client;

    vector<string> vdata;
    vdata = SplitString(st, seperator);

    client.accountnum = vdata[0];
    client.pincode = vdata[1];
    client.name = vdata[2];
    client.phone = vdata[3];
    client.balance = stod(vdata[4]);

    return client;
}

string ConvertRecordToLine(stClients client, string seperator = "#//#")
{
    string word;

    word += client.accountnum + seperator;
    word += client.pincode + seperator;
    word += client.name + seperator;
    word += client.phone + seperator;
    word += to_string(client.balance);

    return word;
}

vector <stClients> LoadClientsDataFromFile(string filename)
{
    vector <stClients> vdata;

    fstream myfile;

    myfile.open(filename, ios::in);

    if (myfile.is_open())
    {
        string line;
        stClients client;

        while (getline(myfile, line))
        {
            client = ConvertLineToRecord(line);

            vdata.push_back(client);
        }
        myfile.close();
    }
    return vdata;
}

bool FindClientByAccountNumber(string accountnum, vector <stClients>& vdata, stClients& client)
{
    for (stClients& data : vdata)
    {
        if (data.accountnum == accountnum)
        {
            client = data;
            return true;
        }
    }
    return false;
}

bool MarkClientForDelete(string accountnum, vector <stClients>& vdata)
{
    for (stClients& data : vdata)
    {
        if (data.accountnum == accountnum)
        {
            data.ismarked = true;
            return true;
        }
    }
    return false;
}

vector <stClients> SaveClientsDataToFile(string filename, vector <stClients>& vdata)
{
    string linedata;

    fstream myfile;

    myfile.open(filename, ios::out);

    if (myfile.is_open())
    {
        for (stClients& data : vdata)
        {
            if (data.ismarked == false)
            {
                linedata = ConvertRecordToLine(data);

                myfile << linedata << endl;
            }
        }
        myfile.close();
    }
    return  vdata;
}

void PrintClientRecord(stClients client)
{
    cout << "The Following are The Client Details:\n\n";
    cout << "----------------------------------------------\n";
    cout << "Account Number: " << client.accountnum << endl;
    cout << "PIN Code      : " << client.pincode << endl;
    cout << "Name          : " << client.name << endl;
    cout << "Phone         : " << client.phone << endl;
    cout << "Balance       : " << client.balance << endl;
    cout << "----------------------------------------------\n";
}

void AddDataLineToFile(string filename, string dataline)
{
    fstream myfile;

    myfile.open(filename, ios::out | ios::app);

    if (myfile.is_open())
    {
        myfile << dataline << endl;

        myfile.close();
    }
}

bool ClientExistsByAccountnumber(string accountnum, string filename)
{
    vector <stClients> vdata;

    fstream myfile;

    myfile.open(filename, ios::in);

    if (myfile.is_open())
    {
        string line;
        stClients client;

        while (getline(myfile, line))
        {
            client = ConvertLineToRecord(line);

            if (client.accountnum == accountnum)
            {
                myfile.close();
                return true;
            }
            vdata.push_back(client);
        }
        myfile.close();
    }
    return false;
}

stClients ReadNewClient()
{
    stClients client;

    cout << "Enter Account Number \n";
    getline(cin >> ws, client.accountnum);

    while (ClientExistsByAccountnumber(client.accountnum, DataFileName))
    {
        cout << "\nClient With [" << client.accountnum << "] << Already Exists, Enter Another Account Number:\n";
        getline(cin >> ws, client.accountnum);
    }

    cout << "Enter PIN Code\n";
    getline(cin, client.pincode);

    cout << "Enter Name\n";
    getline(cin, client.name);

    cout << "Enter Phone\n";
    getline(cin, client.phone);

    cout << "Enter Balance\n";
    cin >> client.balance;

    return client;
}

void AddNewClient()
{
    stClients client;
    client = ReadNewClient();

    AddDataLineToFile(DataFileName, ConvertRecordToLine(client));
}

void AddNewClients()
{
    char addmore = 'Y';

    do
    {
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfuly, Do You Want to Add More Clients? Y/N ";
        cin >> addmore;

    } while (toupper(addmore) == 'Y');
}

void ShowAddNewClientsScreen()
{
    cout << "-----------------------------------------\n";
    cout << "\t Add New Client Screen\n";
    cout << "-----------------------------------------\n";

    AddNewClients();
}

bool DeleteClientByAccountNumber(string accountnum, vector <stClients>& vdata)
{
    stClients clients;
    char answer = 'n';

    if (FindClientByAccountNumber(accountnum, vdata, clients))
    {
        PrintClientRecord(clients);

        cout << "\n\nAre You Sure You Want Delete This Client? Y/N ? ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            MarkClientForDelete(accountnum, vdata);
            SaveClientsDataToFile(DataFileName, vdata);

            //refresh clients
            vdata = LoadClientsDataFromFile(DataFileName);

            cout << "\n\nClient Deleted Successfuly.\n";
            return true;
        }
    }
    else
    {
        cout << "\nClient With Account Number [" << accountnum << "] is Not Found!\n";
        return false;
    }
}

stClients UpdatClient(string accountnum)
{
    stClients client;

    client.accountnum = accountnum;
    cout << "Enter PIN Code ";
    getline(cin >> ws, client.pincode);

    cout << "Enter Your Name ";
    getline(cin, client.name);

    cout << "Enter Your Phone ";
    getline(cin, client.phone);

    cout << "Enter Your Balance ";
    cin >> client.balance;

    return client;
}

bool UpdateClientByAccountNum(string accountnum, vector <stClients>& vdata)
{
    stClients client;
    char answer = 'n';

    if (FindClientByAccountNumber(accountnum, vdata, client))
    {
        PrintClientRecord(client);

        cout << "\n\nAre You Sure You Want Update This Client? Y/N? ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            for (stClients& data : vdata)
            {
                if (data.accountnum == accountnum)
                {
                    data = UpdatClient(accountnum);
                    break;//use it because if found client it out from for
                }
            }
            SaveClientsDataToFile(DataFileName, vdata);

            cout << "\n\nClient Updated Successfuly.\n";
            return true;
        }
    }
    return false;
}

void PrintClientData(stClients client)
{
    cout << "|" << setw(15) << left << client.accountnum;
    cout << "|" << setw(10) << left << client.pincode;
    cout << "|" << setw(40) << left << client.name;
    cout << "|" << setw(12) << left << client.phone;
    cout << "|" << setw(12) << left << client.balance;
}

void ShowClientsList()
{
    vector <stClients> clients;
    clients = LoadClientsDataFromFile(DataFileName);

    cout << "\n\t\t\t\t\tClient List (" << clients.size() << ") Client(s).";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (clients.size() == 0)
    {
        cout << "\t\t\tNo Clients in The System!\n";
    }
    else
        for (stClients client : clients)
        {
            PrintClientData(client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void ShowDeleteScreen()
{
    cout << "------------------------------------------\n";
    cout << "\t\tDelete Client Screen\n";
    cout << "------------------------------------------\n";

    string accountnum = ReadAccountNumber();

    vector <stClients>vdata;
    vdata = LoadClientsDataFromFile(DataFileName);

    DeleteClientByAccountNumber(accountnum, vdata);
}

void ShowUpdateClient()
{
    cout << "-----------------------------------------------\n";
    cout << "\tUpdate Client Info Screen\n";
    cout << "-----------------------------------------------\n";

    string accountnum = ReadAccountNumber();

    vector <stClients>vdata;
    vdata = LoadClientsDataFromFile(DataFileName);

    UpdateClientByAccountNum(accountnum, vdata);
}

void ShowFindClientRecord()
{
    cout << "--------------------------------------\n";
    cout << "\t\tFind Client Screen\n";
    cout << "--------------------------------------\n";

    vector <stClients> vdata;
    vdata = LoadClientsDataFromFile(DataFileName);

    string accountnum = ReadAccountNumber();
    stClients client;

    if (FindClientByAccountNumber(accountnum, vdata, client))
    {
        PrintClientRecord(client);
    }
    else
    {
        cout << "\nClient With Account Number [" << accountnum << "] is Not Found!\n";
    }
}

void PrintEnd()
{
    cout << "--------------------------------------------\n";
    cout << "\t\tProgram End :-)\n";
    cout << "---------------------------------------------\n";
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");

    PrintMainMenue();
}

short ReadMainMenueOption()
{
    short choice = 0;
    cout << "Choice What Do You Want? [1 To 6]\n";
    cin >> choice;

    return choice;
}

//Add Extention
void GoBackToTransactionMenue()
{
    cout << "\n\nPress any key to go back to Transaction Screen...";
    system("pause>0");

    PrintTransactionScreen();
}

short ReadTransactionMenueOption()
{
    short st;
    cout << "Choice What Do You Want To Do [1 To 4]\n";
    cin >> st;

    return st;
}

bool DepositByAccountNumber(string accountnum, double amount, vector <stClients>& vdata)
{
    char answer = 'n';

    cout << "\n\nAre Your Sure You Want Perform This Transaction? Y/N ";
    cin >> answer;

    if (answer == 'Y' || answer == 'y')
    {
        for (stClients& data : vdata)
        {
            if (data.accountnum == accountnum)
            {
                data.balance += amount;

                SaveClientsDataToFile(DataFileName, vdata);

                cout << "\n\nDone Successfuly, New Balance is: " << data.balance << endl;
                return true;
            }
        }
    }
    return false;
}

void PrintDepositScreen()
{
    cout << "-----------------------------\n";
    cout << "\tDeposit Screen\n";
    cout << "-----------------------------\n";

    stClients client;
    string accountnum = ReadAccountNumber();

    vector <stClients> vdata;
    vdata = LoadClientsDataFromFile(DataFileName);

    while (!FindClientByAccountNumber(accountnum, vdata, client))
    {
        cout << "\n\nClient With [" << accountnum << "] is Not Found!\n";

        accountnum = ReadAccountNumber();
    }
    PrintClientRecord(client);

    double amount = 0;
    cout << "\nPlease Enter Deposit Amount: ";
    cin >> amount;

    DepositByAccountNumber(accountnum, amount, vdata);
}

void PrintWithdrawScreen()
{
    cout << "-------------------------------------------\n";
    cout << "\tWithdraw Screen\n";
    cout << "-------------------------------------------\n";

    stClients client;
    string accountnum = ReadAccountNumber();

    vector <stClients> vdata;
    vdata = LoadClientsDataFromFile(DataFileName);

    while (!FindClientByAccountNumber(accountnum, vdata, client))
    {
        cout << "\nClient With [" << accountnum << "] Does Not Exist\n";

        accountnum = ReadAccountNumber();
    }
    PrintClientRecord(client);

    double amount = 0;
    cout << "\nPlease Enter Withdraw Amount: ";
    cin >> amount;

    while (amount > client.balance)
    {
        cout << "\nAmount Exceeds The Balance, You Can Withdraw Up To: " << client.balance << endl;

        cout << "Please Enter Anothe Amount: ";
        cin >> amount;
    }
    DepositByAccountNumber(accountnum, amount * -1, vdata);
}

void PrintClientsBalance(stClients client)
{
    cout << "| " << setw(15) << left << client.accountnum;
    cout << "| " << setw(40) << left << client.name;
    cout << "| " << setw(12) << left << client.balance;
}

void ShowTotalBalance()
{
    vector <stClients> vdata;
    vdata = LoadClientsDataFromFile(DataFileName);

    cout << "\n\t\t\t\t\tClient List (" << vdata.size() << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double totalbalance = 0;

    if (vdata.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (stClients& data : vdata)
        {
            PrintClientsBalance(data);
            totalbalance += data.balance;
            cout << endl;
        }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "\t\t\t\t\t Total Balances = " << totalbalance << endl;
    }

}

void ShowBalanceScreen()
{
    ShowTotalBalance();
}

//add extenion 2
void GoBackToManageUserMenue()
{
    cout << "\n\nPress any key to go back to Manage Users Menue...";
    system("pause>0");

    PrintManageUserMenue();
}

string ReadUsername()
{
    string user;
    cout << "Please Enter Username.\n";
    cin >> user;

    return user;
}

stUsers ConverUserLineToRecord(string st, string seperator = "#//#")
{
    stUsers user;

    vector <string> vusers = SplitString(st, seperator);

    user.Username = vusers[0];
    user.Password = vusers[1];
    user.Permission = stoi(vusers[2]);
    
    return user;
}

string ConverUserRecordToLine(stUsers user, string seperator = "#//#")
{
    string line = "";

    line = user.Username + seperator;
    line += user.Password + seperator;
    line += to_string(user.Permission);

    return line;
}

vector <stUsers> LoadUsersDataFromFile(string filename)
{
    vector <stUsers> vusers;
    fstream myfile;

    myfile.open(filename, ios::in);

    if (myfile.is_open())
    {
        string line;
        stUsers user;

        while (getline(myfile, line))
        {
            user = ConverUserLineToRecord(line);
            vusers.push_back(user);
        }
        myfile.close();
    }
    return vusers;
}

void SaveUsersDataToFile(string filename, vector <stUsers> vusers)
{
    fstream myfile;

    myfile.open(filename, ios::out);

    if (myfile.is_open())
    {
        string line;

        for (stUsers& U : vusers)
        {
            if (U.MarkForDelete == false)
            {
                line = ConverUserRecordToLine(U);

                myfile << line << endl;
            }
        }
        myfile.close();
    }
}

bool IsUserExistsByUsername(string username, string filename)
{
    fstream myfile;

    myfile.open(filename, ios::in);

    if (myfile.is_open())
    {
        string line;

        while (getline(myfile, line))
        {
            stUsers user = ConverUserLineToRecord(line);
            
            if (user.Username == username)
            {
                myfile.close();
                return true;
            }
        }
        myfile.close();
    }
    return false;
}

bool FindUserByUsername(string username, vector <stUsers>& vusers, stUsers& user)
{
    for (stUsers& U : vusers)
    {
        if (U.Username == username)
        {
            user = U;
            return true;
        }
    }
    return false;
}

bool FindUserByUserNameAndPassword(string username, string pass, stUsers &user)
{
    vector <stUsers> vusers;
    vusers = LoadUsersDataFromFile(UsersFileName);

    for (stUsers& U : vusers)
    {
        if (U.Username == username && U.Password == pass)
        {
            user = U;
            return true;
        }
    }
    return false;
}

bool LoadUserInfo(string username, string password)
{
    if (FindUserByUserNameAndPassword(username, password, CurrentUser))
    {
        return true;
    }
    return false;
}

void ShowUserData(stUsers user)
{
    cout << "The Following are The Client Details:\n\n";
    cout << "----------------------------------------------\n";
    cout << "Username  : " << user.Username << endl;
    cout << "Password  : " << user.Password << endl;
    cout << "Permission: " << user.Permission << endl;
    cout << "----------------------------------------------\n";
}

bool CheckAccessPermission(enMainMenuePermission permission)
{
    if (CurrentUser.Permission == enMainMenuePermission::eall)
    {
        return true;
    }

    if ((permission & CurrentUser.Permission) == permission)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ShowAccessDeniedMessage()
{
    cout << "\n-----------------------------------\n";
    cout << "Access Denied, \nYour Don't Have Permission To Do This,\nInter your Admin For Support.";
    cout << "\n-----------------------------------\n";
}

//List User
void ShowUserRecord(stUsers user)
{
    cout << "|" << setw(25) << left << user.Username;
    cout << "|" << setw(12) << left << user.Password;
    cout << "|" << setw(10) << left << user.Permission;
}

void ShowListUserScreen()
{
    if (!CheckAccessPermission(enMainMenuePermission::pListUser))
    {
        ShowAccessDeniedMessage();
        GoBackToManageUserMenue();
        return;
    }

    vector <stUsers> vuser;
    vuser = LoadUsersDataFromFile(UsersFileName);

    cout << "\t\t\t\tUsers List (" << vuser.size() << ") User(s).\n";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "|" << setw(25) << left << "Username";
    cout << "|" << setw(12) << left << "Password";
    cout << "|" << setw(10) << left << "Permission";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vuser.size() == 0)
    {
        cout << "\t\t\t\tNo Users Available In The System!";
    }
    else
    {
        for (stUsers& U : vuser)
        {
            ShowUserRecord(U);
            cout << endl;
        }
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

//Add User
int ReadPermission()
{
    int permission = 0;
    char answer = 'y';

    cout << "Do You Want to Give Full Access? Y/N? ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        return -1;
    }

    cout << "Do You Want to Give Access to:\n";

    cout << "Show Client List? Y/N ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        permission += enMainMenuePermission::pListUser;
    }

    cout << "Add New Client? Y/N ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        permission += enMainMenuePermission::pAddNewUser;
    }

    cout << "Delete Client? Y/N ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        permission += enMainMenuePermission::pDeleteUser;
    }

    cout << "Update Client? Y/N ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        permission += enMainMenuePermission::pUpdateUser;
    }

    cout << "Find Client? Y/N? ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        permission += enMainMenuePermission::pFindUser;
    }

    cout << "Transactios? Y/N? ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        permission += enMainMenuePermission::pTransactio;
    }

    cout << "Manage Users? Y/N? ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        permission += enMainMenuePermission::pManageUser;
    }

    return permission;
}

stUsers ReadNewUser()
{
    stUsers user;

    cout << "Enter Username? ";
    getline(cin >> ws, user.Username);

    while (IsUserExistsByUsername(user.Username, UsersFileName))
    {
        cout << "\nUser with [" << user.Username << "] alreadyexists, Enter another Username ? ";
            
        getline(cin >> ws, user.Username);
    }
    cout << "Enter Password? ";
    getline(cin, user.Password);

    user.Permission = ReadPermission();

    return user;
}

void AddNewUser()
{
    stUsers user;

    user = ReadNewUser();

    AddDataLineToFile(UsersFileName, ConverUserRecordToLine(user));
}

void AddNewUsers()
{
    char answer = 'y';

    do
    {
        cout << "Adding New User:\n\n";
        AddNewUser();

        cout << "\nUser Added Successfuly, Do You Want to Add More Users? Y/N? ";
        cin >> answer;

    } while (toupper(answer) == 'Y');
}

void ShowAddNewUserScreen()
{
    if (!CheckAccessPermission(enMainMenuePermission::pAddNewUser))
    {
        ShowAccessDeniedMessage();
        GoBackToManageUserMenue();
        return;
    }

    cout << "---------------------------------------------\n";
    cout << "\t\tAdd New User Screen.\n";
    cout << "---------------------------------------------\n";

    AddNewUsers();
}

//Delete User
bool MarkUserForDeleteByUsername(string username, vector<stUsers>& user)
{
    for (stUsers& U : user)
    {
        if (U.Username == username)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool DeleteUserByUsername(string username, vector<stUsers>& vuser)
{
    stUsers user;
    char answer = 'n';

    if (FindUserByUsername(username, vuser, user))
    {
        ShowUserData(user);

        cout << "\n\nAre You Sure You Want Delete This User? Y/N? ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            MarkUserForDeleteByUsername(username, vuser);
            SaveUsersDataToFile(UsersFileName, vuser);

            //refresh date
            vuser = LoadUsersDataFromFile(UsersFileName);

            cout << "User Delete Successfuly.\n";
        }
        return true;
    }
    else
    {
        cout << "User With Username (" << username << ") is Not Found!..\n";
        return false;
    }
    return false;
}

void PrintDeleteUserScreen()
{
    if (!CheckAccessPermission(enMainMenuePermission::pDeleteUser))
    {
        ShowAccessDeniedMessage();
        GoBackToManageUserMenue();
        return;
    }

    cout << "----------------------------------------------------\n";
    cout << "\t\tDelete Users Screen\n";
    cout << "----------------------------------------------------\n";

    string username = ReadUsername();

    vector<stUsers> vusers;
    vusers = LoadUsersDataFromFile(UsersFileName);

    if (username == "Admin" || username == "admin")
    {
        cout << "\n\nYou Can't Delete This User.\n";
        return;
    }

    DeleteUserByUsername(username, vusers);
}

//Update User
stUsers ChangeUserRecord(string username)
{
    stUsers user;
    user.Username = username;

    cout << "Enter Password? ";
    cin >> user.Password;

    user.Permission = ReadPermission();

    return user;
}

bool UpdateUserByUsername(string username, vector<stUsers>& vuser)
{
    stUsers user;
    char answer = 'y';

    if (FindUserByUsername(username, vuser, user))
    {
        ShowUserData(user);

        cout << "Are You Sure You Want Update This User? Y/N? ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            for (stUsers& U : vuser)
            {
                if (U.Username == username)
                {
                    U = ChangeUserRecord(username);
                    break;
                }
            }
            SaveUsersDataToFile(UsersFileName, vuser);

            cout << "\nUser Updated Successfuly.\n";
            return true;
        }
    }
    else
    {
        cout << "\n\nUser By Username (" << username << ") is Not Found!..\n";
        return false;
    }
    return false;
}

void ShowUpdateUsersScreen()
{
    if (!CheckAccessPermission(enMainMenuePermission::pUpdateUser))
    {
        ShowAccessDeniedMessage();
        GoBackToManageUserMenue();
        return;
    }

    cout << "----------------------------------------------------\n";
    cout << "\t\tUpdate Users Screen\n";
    cout << "----------------------------------------------------\n";

    string username = ReadUsername();

    vector<stUsers> vusers;
    vusers = LoadUsersDataFromFile(UsersFileName);

    UpdateUserByUsername(username, vusers);
}

//Find User
void ShowFindUserScreen()
{
    if (!CheckAccessPermission(enMainMenuePermission::pFindUser))
    {
        ShowAccessDeniedMessage();
        GoBackToManageUserMenue();
        return;
    }

    cout << "--------------------------------------------------------\n";
    cout << "\t\tFind User Screen\n";
    cout << "--------------------------------------------------------\n";

    string username = ReadUsername();

    stUsers user;

    vector <stUsers> vusers;
    vusers = LoadUsersDataFromFile(UsersFileName);

    if (FindUserByUsername(username, vusers, user))
    {
        ShowUserData(user);
    }
    else
    {
        cout << "\nUser With Username (" << username << ") is Not Found!..\n";
    }
}

short ReadManageUserMenue()
{
    short num;
    cout << "Choice What Do You Want To Do? [1 to 6]\n";
    cin >> num;

    return num;
}

void PerfromManageUsersMenueOption(enUserMeueOption option)
{
    switch (option)
    {
    case enUserMeueOption::eListUser:
    {
        system("cls");
        ShowListUserScreen();
        GoBackToManageUserMenue();
        break;
    }
    case enUserMeueOption::eAddUser:
    {
        system("cls");
        ShowAddNewUserScreen();
        GoBackToManageUserMenue();
        break;
    }
    case enUserMeueOption::eDeleteUser:
    {
        system("cls");
        PrintDeleteUserScreen();
        GoBackToManageUserMenue();
        break;
    }
    case enUserMeueOption::eUpdateUser:
    {
        system("cls");
        ShowUpdateUsersScreen();
        GoBackToManageUserMenue();
        break;
    }
    case enUserMeueOption::eFindUser:
    {
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUserMenue();
        break;
    }
    case enUserMeueOption::eMainMenue:
    {
        system("cls");
        PrintMainMenue();
        break;
    }
    }
}

void PrintManageUserMenue()
{
    cout << "============================================================\n";
    cout << "\t\tManage User Menue Screen.\n";
    cout << "============================================================\n";

    cout << "\t\t[1] List users.\n";
    cout << "\t\t[2] Add New User.\n";
    cout << "\t\t[3] Delete User.\n";
    cout << "\t\t[4] Update User.\n";
    cout << "\t\t[5] Find User.\n";
    cout << "\t\t[6] Main Menue.\n";
    cout << "============================================================\n";

    PerfromManageUsersMenueOption((enUserMeueOption)ReadManageUserMenue());
}

void ChoiceFromTransactionOption(enTransactionOption menue)
{
    switch (menue)
    {
    case enTransactionOption::edeposit:
    {
        system("cls");
        PrintDepositScreen();
        GoBackToTransactionMenue();
        break;
    }
    case enTransactionOption::ewithdraw:
    {
        system("cls");
        PrintWithdrawScreen();
        GoBackToTransactionMenue();
        break;
    }
    case enTransactionOption::etotalbalance:
    {
        system("cls");
        ShowBalanceScreen();
        GoBackToTransactionMenue();
        break;
    }
    case enTransactionOption::emainmenue:
    {
        system("cls");
        PrintMainMenue();
        break;
    }
    }
}

void ChoiceFromMainMenueOption(enMainMenueOption menue)
{
    switch (menue)
    {
    case enMainMenueOption::showclient:
    {
        system("cls");
        ShowClientsList();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::addnewclient:
    {
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::deleteclient:
    {
        system("cls");
        ShowDeleteScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::updateclient:
    {
        system("cls");
        ShowUpdateClient();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::findclient:
    {
        system("cls");
        ShowFindClientRecord();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::etransactions:
    {
        system("cls");
        PrintTransactionScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::magageuser:
    {
        system("cls");
        PrintManageUserMenue();
        break;
    }
    case enMainMenueOption::logout:
    {
        system("cls");
        Login();
        break;
    }
    }
}

void PrintTransactionScreen()
{
    cout << "==============================================\n";
    cout << "\tTransaction Menue Screen\n";
    cout << "==============================================\n";

    cout << "\t\t[1] Deposit.\n";
    cout << "\t\t[2] Withdraw.\n";
    cout << "\t\t[3] Total Balance.\n";
    cout << "\t\t[4] Main Menue.\n";
    cout << "==============================================\n";

    ChoiceFromTransactionOption((enTransactionOption)ReadTransactionMenueOption());
}

void PrintMainMenue()
{
    system("cls");
    cout << "===================================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===================================================\n";

    cout << "\t\t[1] Show Clients List.\n";
    cout << "\t\t[2] Add New Client.\n";
    cout << "\t\t[3] Delete Client.\n";
    cout << "\t\t[4] Update Client.\n";
    cout << "\t\t[5] Find Client.\n";
    cout << "\t\t[6] Transactions.\n";
    cout << "\t\t[7] Manage Users.\n";
    cout << "\t\t[8] Logout.\n";
    cout << "===================================================\n";

    ChoiceFromMainMenueOption((enMainMenueOption)ReadMainMenueOption());
}

void Login()
{
    bool LoginFaild = false;
    string user, pass;

    do
    {
        system("cls");

        cout << "----------------------------------------\n";
        cout << "\t\tLogin Screen.\n";
        cout << "----------------------------------------\n";

        if (LoginFaild)
        {
            cout << "Invlaid Username/Password.\n";
        }
        cout << "Enter Username.\n";
        cin >> user;
        cout << "Enter Password.\n";
        cin >> pass;

        LoginFaild = !LoadUserInfo(user, pass);

    } while (LoginFaild);

    PrintMainMenue();
}

int main()
{
    Login();

    return 0;
}
