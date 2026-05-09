#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string NameFileData = "Clients Data.txt";

void PrintMainMenue();

void PrintTransactionScreen();

enum enMainMenueOption
{
    showclient = 1, addnewclient = 2, deleteclient = 3
    , updateclient = 4, findclient = 5, etransactions=6, eExit = 7
};

enum enTransactionOption
{
    edeposit = 1, ewithdraw = 2, etotalbalance = 3, emainmenue = 4
};

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

    while (ClientExistsByAccountnumber(client.accountnum, NameFileData))
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

    AddDataLineToFile(NameFileData, ConvertRecordToLine(client));
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
            SaveClientsDataToFile(NameFileData, vdata);

            //refresh clients
            vdata = LoadClientsDataFromFile(NameFileData);

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
            SaveClientsDataToFile(NameFileData, vdata);

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
    clients = LoadClientsDataFromFile(NameFileData);

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
    vdata = LoadClientsDataFromFile(NameFileData);

    DeleteClientByAccountNumber(accountnum, vdata);
}

void ShowUpdateClient()
{
    cout << "-----------------------------------------------\n";
    cout << "\tUpdate Client Info Screen\n";
    cout << "-----------------------------------------------\n";

    string accountnum = ReadAccountNumber();

    vector <stClients>vdata;
    vdata = LoadClientsDataFromFile(NameFileData);

    UpdateClientByAccountNum(accountnum, vdata);
}

void ShowFindClientRecord()
{
    cout << "--------------------------------------\n";
    cout << "\t\tFind Client Screen\n";
    cout << "--------------------------------------\n";

    vector <stClients> vdata;
    vdata = LoadClientsDataFromFile(NameFileData);

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

                SaveClientsDataToFile(NameFileData, vdata);

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
    vdata = LoadClientsDataFromFile(NameFileData);

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
    vdata = LoadClientsDataFromFile(NameFileData);

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
    vdata = LoadClientsDataFromFile(NameFileData);

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
    case enMainMenueOption::eExit:
    {
        system("cls");
        PrintEnd();
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
    cout << "\t\t[7] Exit.\n";
    cout << "===================================================\n";

    ChoiceFromMainMenueOption((enMainMenueOption)ReadMainMenueOption());
}

int main()
{
    PrintMainMenue();

    return 0;
}
