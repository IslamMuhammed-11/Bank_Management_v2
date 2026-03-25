// AlgorithmLvl4_Bank_Extension.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

void showAllClients();
void addNewClients();
void deleteClient();
void updateClient();
void findClient();
void exitScreen();
void mainMenu();
void goBackToMainMenu();
void goBackToTransactionMenu();
void depositScreen();
void withdrawScreen();
void totalBalanceScreen();
void transactionMenu();
void showUsersList();
void goBackToManageUsersScreen();
void addNewUsers();
void deleteUsers();
void updateUsers();
void findUsers();
void manageUsersMenu();
void login();
//Structures
struct stClient {
    string accountNumber;
    string pinCode;
    string name;
    string phoneNumber;
    double accountBalance = 0;
    bool markToDelete = false;
};
struct stUsersData {
    string userName = "";
    string passWord = "";
    int permission = 0;
    bool markToDelete = false;
};
//-------------------------------------
// consts
const string clientFileName = "Clients.txt";
const string usersFileName = "users.txt";
 stUsersData LoggedUser;
// Enums
enum enMainMenuChoices { enShowClient = 1, enAddClient = 2, enDeleteClient = 3, enUpdateClient = 4, enFindClient = 5, enTransactions = 6, enManageUseres = 7 , enLogOut = 8 };
enum enTransactionMenuChoices { enDeposit = 1, enWithdraw = 2, enTotalBalance = 3, goBack = 4 };
enum enManageUsersMenuChoices {enUserList = 1 , enAddNewUser = 2 , enDeleteUser = 3 , enUpdateUser = 4 , enFindUser = 5 , enBackToMainMenu = 6};
enum enPermissions{ fullAccess = -1 , enShowCLientPremisson = 1 , enAddClientPremission = 2 , enDeleteClientPreimission = 4 , enUpdateClientPremission = 8 , enFindClientPremission = 16 ,enTransactionsPremission = 32 , enManageUsersPremission = 64};
// Clients General Functions
string readString(string message) {
    string s1 = "";
    cout << message;
    getline(cin >> ws, s1);
    return s1;
}

vector<string>split(string line, string delim = "#//#") {

    vector<string>split;
    string sWord;
    short pos = 0;
    while ((pos = line.find(delim)) != std::string::npos)
    {
        sWord = line.substr(0, pos);
        if (sWord != "")
        {
            split.push_back(sWord);
        }
        line.erase(0, pos + delim.length());
    }
    if (line != "")
    {
        split.push_back(line);
    }
    return split;
}

stClient convertLineToRecord(string line, string delim = "#//#") {
    stClient record;
    vector<string>data;
    data = split(line, delim);
    record.accountNumber = data[0];
    record.pinCode = data[1];
    record.name = data[2];
    record.phoneNumber = data[3];
    record.accountBalance = stod(data[4]);
    return record;
}

string convertRecordToLine(stClient record, string delim = "#//#") {
    string line = "";
    line += record.accountNumber + delim;
    line += record.pinCode + delim;
    line += record.name + delim;
    line += record.phoneNumber + delim;
    line += to_string(record.accountBalance);
    return line;
}

vector<stClient>loadRecordsFromFile(string fileName) {

    vector<stClient>vClients;
    fstream myFile;
    myFile.open(fileName, ios::in);
    string line;
    stClient client;
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            client = convertLineToRecord(line);
            vClients.push_back(client);
        }
    }
    return vClients;

}

vector<stClient>saveDataToFile(string fileName, vector<stClient>& vClient) {
    fstream myFile;
    myFile.open(fileName, ios::out);
    if (myFile.is_open())
    {
        string dataLine;
        for (stClient& c : vClient) {
            if (c.markToDelete == false)
            {
                dataLine = convertRecordToLine(c);
                myFile << dataLine << endl;
            }

        }
        myFile.close();
    }
    return vClient;
}

bool findClientByAccountNumber(string accountNumber, vector<stClient>& vClients, stClient& client) {

    for (stClient& C : vClients) {
        if (C.accountNumber == accountNumber)
        {
            client = C;
            return true;
        }

    }
    return false;
}

bool checkIfClientAlreadySinged(string accountNumber) {

    vector<stClient>vClients = loadRecordsFromFile(clientFileName);

    for (stClient& C : vClients) {

        if (C.accountNumber == accountNumber)
        {
            return true;
        }
    }
    return false;
}

void printRecord(stClient record) {

    cout << "\nThe Following are Client Record\n\n";

    cout << setw(17) << left << "Account Number" << ": " << record.accountNumber << endl;
    cout << setw(17) << left << "Pin Code" << ": " << record.pinCode << endl;
    cout << setw(17) << left << "Name" << ": " << record.name << endl;
    cout << setw(17) << left << "Phone Number" << ": " << record.phoneNumber << endl;
    cout << setw(17) << left << "Account Balance" << ": " << record.accountBalance << endl << endl;
}
//Users General Functions
stUsersData convertUsersLineToRecord(string line, string delim = "#//#") {
    stUsersData record;
    vector<string>data = split(line, delim);
    record.userName = data[0];
    record.passWord = data[1];
    record.permission = stoi(data[2]);
    return record;
}

string convertUsersRecordToLine(stUsersData record, string delim = "#//#") {
    string line = "";
    line += record.userName + delim;
    line += record.passWord + delim;
    line += to_string(record.permission);
    return line;
}

vector<stUsersData>loadUsersFromFile(string fileName) {

    vector<stUsersData>vUsers;
    fstream myFile;
    myFile.open(fileName, ios::in);
    string line;
    stUsersData User;
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            User = convertUsersLineToRecord(line);
            vUsers.push_back(User);
        }
    }
    return vUsers;

}

bool checkIfUsernameExists(string username) {
    vector<stUsersData> vFileContent = loadUsersFromFile(usersFileName);

    for (stUsersData& C : vFileContent) {
        if (C.userName == username)
        {
            return true;
        }
    }

    return false;
}

bool findUserByUserName(string username, vector<stUsersData>& vUsers, stUsersData& user) {

    for (stUsersData& c : vUsers) {
        if (c.userName == username)
        {
            user = c;
            return true;
        }
    }
    return false;
}

void printUsersRecord(stUsersData record) {

    cout << "\nThe Following is User Record\n";
    cout << "\n____________________________\n";
    cout << setw(17) << left << "Username" << ":" << record.userName << endl;
    cout << setw(17) << left << "Password" << ":" << record.passWord << endl;
    cout << setw(17) << left << "Permissions" << ":" << record.permission << endl;
}

vector<stUsersData>saveDataToFile(string filename, vector<stUsersData>& data) {

    fstream myFile;
    myFile.open(filename, ios::out);
    if (myFile.is_open())
    {
        string dataLine;
        for (stUsersData& c : data) {
            if (c.markToDelete == false)
            {
                dataLine = convertUsersRecordToLine(c);
                myFile << dataLine << endl;
            }
        }
        myFile.close();
    }
    return data;
}

//Show All Clients
void headerOfClientList(int size) {

    cout << setw(50) << "Client List (" << size << ") Client/s\n\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| Account Number" << setw(3) << "|";
    cout << " Pin Code" << setw(3) << "|";
    cout << " Client Name" << setw(30) << "|";
    cout << " Phone" << setw(10) << "|";
    cout << " Balance";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------\n\n";

}

void printList(stClient data) {

    cout << "|" << left << setw(17) << data.accountNumber << "|";
    cout << left << setw(11) << data.pinCode << "|";
    cout << left << setw(41) << data.name << "|";
    cout << left << setw(15) << data.phoneNumber << "|";
    cout << left << data.accountBalance;
    cout << left << endl;
}

void printAllClientsRecords(vector<stClient>& vFileContent) {

    headerOfClientList(vFileContent.size());

    for (stClient& C : vFileContent) {

        printList(C);
    }
}
//Show All Users
void headerOfUsersList(int size) {
    cout << setw(50) << "Users List (" << size << ") user/s\n\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| Username" << setw(8) << "|";
    cout << " Password" << setw(8) << "|";
    cout << " Permissions";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------\n\n";
}

void printOneUser(stUsersData data) {

    cout << "|" << left << setw(16) << data.userName << "|";
    cout << left << setw(16) << data.passWord << "|";
    cout << left << data.permission;
    cout << left << endl;
}

void printAllUsersRecords(vector<stUsersData>& vFileContent) {
    headerOfUsersList(vFileContent.size());

    for (stUsersData& C : vFileContent) {
        printOneUser(C);
    }
}
// Add New Clients
stClient readClient() {
    stClient data;

    cout << "Account Number  ? ";
    getline(cin >> ws, data.accountNumber);
    if (checkIfClientAlreadySinged(data.accountNumber))
    {
        do
        {
            cout << "Client With [" << data.accountNumber << "] Already exists , Enter Another Account Number? ";
            getline(cin >> ws, data.accountNumber);

        } while (checkIfClientAlreadySinged(data.accountNumber));
    }

    cout << "Pin Code        ? ";
    getline(cin, data.pinCode);
    cout << "Name            ? ";
    getline(cin, data.name);
    cout << "Phone number    ? ";
    getline(cin, data.phoneNumber);
    cout << "Account balance ? ";
    cin >> data.accountBalance;

    return data;
}

void addLineToFile(string fileName, string line) {

    fstream myFile;

    myFile.open(fileName, ios::out | ios::app);
    if (myFile.is_open())
    {
        myFile << line << endl;
    }
    myFile.close();
}

void addClientToFile() {
    stClient data = readClient();
    addLineToFile(clientFileName, convertRecordToLine(data));

}

void addClientsLoop() {
    char addMore = 'Y';
    do
    {
        system("cls");
        cout << "\nAdd New Client!\n\n";
        addClientToFile();
        cout << "Client Added Successfully, Do You Want to Add More? y / n ";
        cin >> addMore;
    } while (toupper(addMore) == 'Y');

}
//ReadPermissions
int readUsersPermissions() {
    char answer = 'n';
    cout << "\n\nDo You Want To Give Full Access ? y/n: ";
    cin >> answer;
    if (toupper(answer) == 'Y')
    {
        return -1;
    }

    int permission = 0;
    cout << "\nDo You Want To Give Access To: \n";

    cout << "\nShow Client List ? y/n "; cin >> answer;
    if (toupper(answer) == 'Y') {
         permission |= enShowCLientPremisson;
    }

    cout << "\nAdd New Clients ? y/n "; cin >> answer;
    if (toupper(answer) == 'Y')
    {
         permission |= enAddClientPremission;
    }

    cout << "\nDelete Clients ? y/n "; cin >> answer;
    if (toupper(answer)=='Y')
    {
         permission |= enDeleteClientPreimission;
    }

    cout << "\nUpdate Client ? y/n "; cin >> answer;
    if (toupper(answer) == 'Y')
    {
         permission |= enUpdateClientPremission;
    }

    cout << "\nFind Client ? y/n "; cin >> answer;
    if (toupper(answer) == 'Y')
    {
        permission |= enFindClientPremission;
    }

    cout << "\nTransactions Menu ? y/n "; cin >> answer;
    if (toupper(answer) == 'Y')
    {
        permission |= enTransactionsPremission;
    }

    cout << "\nManage Users ? y/n "; cin >> answer;
    if (toupper(answer) == 'Y')
    {
        permission |= enManageUsersPremission;
    }

    return permission;
}

//Add New User
stUsersData readUser() {
    stUsersData data;

    cout << "Enter Username ? ";
    getline(cin >> ws, data.userName);
    while (checkIfUsernameExists(data.userName))
    {
        cout << "This Username [" << data.userName << "] Already Exists Please Try Another!: ";
        getline(cin >> ws, data.userName);
    }

    cout << "Enter Password ? ";
    getline(cin >> ws, data.passWord);

    data.permission = readUsersPermissions();
    return data;
}

void addUserToFile() {
    stUsersData data = readUser();
    addLineToFile(usersFileName, convertUsersRecordToLine(data));
}

void addUsersLoop() {
    char addMore = 'Y';
    do
    {
        system("cls");
        cout << "\nAdd New User!\n\n";
        addUserToFile();
        cout << "\nUser Added Successfully! Do You Want TO Add More Users? y/n ";
        cin >> addMore;
    } while (toupper(addMore) == 'Y');
}
// Delete Client
bool markClientToDelete(string accountNumber, vector<stClient>& vClients) {

    for (stClient& C : vClients) {
        if (C.accountNumber == accountNumber)
        {
            C.markToDelete = true;
            return true;
        }
    }
    return false;
}

bool deleteClientByAccountNumber(string accountNumber, vector<stClient>& vClients) {
    stClient client;
    char answer = 'n';
    if (findClientByAccountNumber(accountNumber, vClients, client))
    {
        printRecord(client);
        cout << "\n\n Are You Sure You Want To Delete This Client ? y/n ";
        cin >> answer;
        if (toupper(answer) == 'Y')
        {
            markClientToDelete(accountNumber, vClients);
            saveDataToFile(clientFileName, vClients);
            vClients = loadRecordsFromFile(clientFileName);
            cout << "\n\n Deleted Successfully\n";
            return true;
        }
    }
    else
    {
        cout << "\n\nclient With [" << accountNumber << "] is not Found!\n\n";
        return false;
    }
}
//Delete User
bool markUserToDelete(string username, vector<stUsersData>& vUsers) {

    for (stUsersData& c : vUsers) {
        if (c.userName == username)
        {
            c.markToDelete = true;
            return true;
        }
    }
    return false;
}

bool deleteUserByUsername(string username, vector<stUsersData>&vUsers) {
    stUsersData user;
    char answer = 'n';
    if (findUserByUserName(username , vUsers , user))
    {
        printUsersRecord(user);
        cout << "\n\nAre You Sure You Want To Delete This User ? y/n ";
        cin >> answer;
        if (toupper(answer)=='Y')
        {
            markUserToDelete(username, vUsers);
            saveDataToFile(usersFileName, vUsers);
            vUsers = loadUsersFromFile(usersFileName);
            cout << "\n Deleted Successfully ! ";
            return true;
        }
        return false;
    }
    else
    {
        cout << "\nUser With This Username[" << username << "] Not Found \n";
        return false;
    }
}
// Update Client
stClient updateClientInfo(string accountNumber) {
    stClient data;
    data.accountNumber = accountNumber;
    cout << "Pin Code        ? ";
    getline(cin >> ws, data.pinCode);
    cout << "Name            ? ";
    getline(cin, data.name);
    cout << "Phone number    ? ";
    getline(cin, data.phoneNumber);
    cout << "Account balance ? ";
    cin >> data.accountBalance;
    return data;
}

bool updateClientRecord(string accountNumber, vector<stClient>& vClient) {
    stClient client;
    char answer = 'Y';
    if (findClientByAccountNumber(accountNumber, vClient, client))
    {
        printRecord(client);
        cout << "\n\n Are You Sure You Want To Update This Client's Record? y/n ";
        cin >> answer;
        if (toupper(answer) == 'Y')
        {
            for (stClient& c : vClient) {
                if (c.accountNumber == accountNumber)
                {
                    c = updateClientInfo(accountNumber);
                    break;
                }
            }
            saveDataToFile(clientFileName, vClient);
            cout << "\nClient Updated Successfully\n";
            return true;
        }
    }
    else
    {
        cout << "\n\nclient With [" << accountNumber << "] is not Found!\n\n";
        return false;
    }
}
//Update User
stUsersData updateUserInfo(string username) {
    stUsersData data;
    data.userName = username;
    cout << "Enter Password: ";
    getline(cin >> ws, data.passWord);
    data.permission = readUsersPermissions();
    return data;
}

bool updateUserRecord(string username, vector<stUsersData>& vUsers) {
    stUsersData user;
    char answer = 'n';
    if (findUserByUserName(username , vUsers , user))
    {
        printUsersRecord(user);
        cout << "\n\nAre You Sure You Want To Update This User? y/n "; 
        cin >> answer;
        if (toupper(answer)=='Y')
        {
            for (stUsersData& c : vUsers) {
                if (c.userName == username)
                {
                    c = updateUserInfo(username);
                    break;
                }

            }
            saveDataToFile(usersFileName, vUsers);
            return true;
        }
        return false;
    }
    else
    {
        cout << "\nUser With This Username[" << username << "] Not Found \n";
        return false;
    }
}
//User's Choices
enMainMenuChoices mainMenuChoices() {
    short choice = 0;
    do
    {
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (choice > 8 || choice < 1);

    return (enMainMenuChoices)choice;

}

enTransactionMenuChoices transactionChoicees() {

    short choice = 0;
    do
    {
        cin >> choice;
    } while (choice > 4 || choice < 1);

    return (enTransactionMenuChoices)choice;

}

enManageUsersMenuChoices manageUsersChoices() {
    short choice = 0;
    do
    {
        cin >> choice;
    } while (choice > 6 || choice < 1);
    return (enManageUsersMenuChoices)choice;
}
//User's Permissions

void notAllowedMessage() {
    cout << "\n\n You're not Allowed to take this action.\nPlease Call Your Admin.";
}

bool checkPermissions(stUsersData user, enPermissions permission) {

    return (user.permission == -1) || ((user.permission & permission) == permission);
}

//Performances
void performMainMenuChoices(enMainMenuChoices choice , stUsersData user) {

    switch (choice)
    {
    case enShowClient:
        system("cls");
        checkPermissions(user, enShowCLientPremisson) ? showAllClients() : notAllowedMessage();
        goBackToMainMenu();
        break;
    case enAddClient:
        system("cls");
        checkPermissions(user, enAddClientPremission) ? addNewClients() : notAllowedMessage();
        goBackToMainMenu();
        break;
    case enDeleteClient:
        system("cls");
        checkPermissions(user, enDeleteClientPreimission) ? deleteClient() : notAllowedMessage();
        goBackToMainMenu();
        break;
    case enUpdateClient:
        system("cls");
        checkPermissions(user, enUpdateClientPremission) ? updateClient() : notAllowedMessage();
        goBackToMainMenu();
        break;
    case enFindClient:
        system("cls");
        checkPermissions(user, enFindClientPremission) ? findClient() : notAllowedMessage();
        goBackToMainMenu();
        break;
    case enTransactions:
        system("cls");
        if (checkPermissions(user, enTransactionsPremission))
            transactionMenu();

        else {
            notAllowedMessage();
            goBackToMainMenu();
        }
        break;

    case enManageUseres:
        system("cls");
        checkPermissions(user, enManageUsersPremission) ? manageUsersMenu() : notAllowedMessage();
        goBackToMainMenu();
    case enLogOut:
        system("cls");
        login();
        
        break;
    default:
        system("cls");
        login();
        break;
    }


}

void performTransactionMenuChoices(enTransactionMenuChoices choice) {
    switch (choice)
    {
    case enDeposit:
        system("cls");
        depositScreen();
        goBackToTransactionMenu();
        break;
    case enWithdraw:
        system("cls");
        withdrawScreen();
        goBackToTransactionMenu();
        break;
    case enTotalBalance:
        system("cls");
        totalBalanceScreen();
        goBackToTransactionMenu();
        break;
    case goBack:
        system("cls");
        mainMenu();
        break;
    default:
        mainMenu();
        break;
    }
}

void performManageUsersMenuChoices(enManageUsersMenuChoices choice) {
    switch (choice)
    {
    case enUserList:
        system("cls");
        showUsersList();
        goBackToManageUsersScreen();
        break;
    case enAddNewUser:
        system("cls");
        addNewUsers();
        goBackToManageUsersScreen();
        break;
    case enDeleteUser:
        system("cls");
        deleteUsers();
        goBackToManageUsersScreen();
        break;
    case enUpdateUser:
        system("cls");
        updateUsers();
        goBackToManageUsersScreen();
        break;
    case enFindUser:
        system("cls");
        findUsers();
        goBackToManageUsersScreen();
        break;
    case enBackToMainMenu:
        mainMenu();
        break;
    default:
        system("cls");
        manageUsersMenu();
        break;
    }
}
//Total Balances
double calculateTotalBalance() {
    vector<stClient>vClient = loadRecordsFromFile(clientFileName);

    double totalBalances = 0;
    for (stClient c : vClient) {
        totalBalances += c.accountBalance;
    }
    return totalBalances;
}

void showTotalBalance(int size, vector<stClient>& vClient) {

    cout << setw(50) << "Client List (" << size << ") Client/s\n\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| Account Number" << setw(3) << "|";
    cout << " Client Name" << setw(30) << "|";
    cout << " Balance";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------\n\n";
    for (stClient& data : vClient) {
        cout << "|" << left << setw(17) << data.accountNumber << "|";
        cout << left << setw(41) << data.name << "|";
        cout << left << data.accountBalance;
        cout << left << endl;
    }
    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------\n\n";
}
// Function that Deposit Balance To Client By Account Number.
bool depositBalanceToClientByAccountNumber(double newBalance, string accountNumber, vector<stClient>& vClient) {


    char answer = 'n';
    cout << "Are You Sure You Want To Perform This Transaction ? y/n ";
    cin >> answer;
    if (toupper(answer) == 'Y')
    {
        for (stClient& c : vClient) {

            if (accountNumber == c.accountNumber)
            {
                c.accountBalance += newBalance;
                saveDataToFile(clientFileName, vClient);
                cout << "\nDone Successfully, New Balance is " << c.accountBalance << endl;
                return true;
            }
        }
    }

    return false;
}
// Menus
void manageUsersMenu() {
    system("cls");
    cout << "___________________________________________\n";
    cout << "\n" << right << setw(28) << "Manage Users Menu\n";
    cout << "___________________________________________\n\n";

    cout << setw(10) << right << "[1]" << " List Users.\n";
    cout << setw(10) << right << "[2]" << " Add New User.\n";
    cout << setw(10) << right << "[3]" << " Delete User.\n";
    cout << setw(10) << right << "[4]" << " Update Users Info.\n";
    cout << setw(10) << right << "[5]" << " Find User.\n";
    cout << setw(10) << right << "[6]" << " Main Menu.\n";
    cout << "___________________________________________\n";
    cout << "Choose What You Want To Do? [1 - 6]  ";
    performManageUsersMenuChoices(manageUsersChoices());
}

void mainMenu() {

    system("cls");

    cout << "___________________________________________\n";
    cout << "\n" << right << setw(28) << "Main Menu Screen\n";
    cout << "___________________________________________\n\n";

    cout << setw(10) << right << "[1]" << " Show Client List.\n";
    cout << setw(10) << right << "[2]" << " Add New Client.\n";
    cout << setw(10) << right << "[3]" << " Delete Client.\n";
    cout << setw(10) << right << "[4]" << " Update Client Info.\n";
    cout << setw(10) << right << "[5]" << " Find Client.\n";
    cout << setw(10) << right << "[6]" << " Transactions.\n";
    cout << setw(10) << right << "[7]" << " Manage Users.\n";
    cout << setw(10) << right << "[8]" << " LogOut.\n";
    cout << "___________________________________________\n";
    cout << "Choose What You Want To Do? [1 - 8]  ";
    
    performMainMenuChoices(mainMenuChoices(),LoggedUser);
}

void transactionMenu() {
    system("cls");
    cout << "___________________________________________\n";
    cout << "\n" << right << setw(27) << "transaction Menu Screen\n";
    cout << "___________________________________________\n\n";

    cout << setw(10) << right << "[1]" << "Deposit\n";
    cout << setw(10) << right << "[2]" << "WithDraw\n";
    cout << setw(10) << right << "[3]" << "Total Balance\n";
    cout << setw(10) << right << "[4]" << "MainMenu\n";
    cout << "___________________________________________\n";
    cout << "Choose What You Want To Do? [1 - 4]  ";
    performTransactionMenuChoices(transactionChoicees());
}

void totalBalanceMenu(stClient data, int size) {
    cout << setw(50) << "Client List (" << size << ") Client/s\n\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| Account Number" << setw(3) << "|";
    cout << " Client Name" << setw(30) << "|";
    cout << " Balance";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------\n\n";

    cout << "|" << left << setw(17) << data.accountNumber << "|";
    cout << left << setw(41) << data.name << "|";
    cout << left << data.accountBalance;
    cout << left << endl;
}
//Login Logic

bool checkUsernameAndPassword(string username, string password) {
    vector<stUsersData> vUsers = loadUsersFromFile(usersFileName);
    if (findUserByUserName(username , vUsers , LoggedUser))
    {
        if (LoggedUser.passWord == password)
        {
            return true;
        }
        return false;
    }
    return false;
}

void readUsernameAndPassword(string& username, string& password) {
    username = readString("Enter Username? ");
    password = readString("\nEnter Password? ");
}

void login() {
    bool loginFaild = false;
    string password, username;

    do
    {
        system("cls");

        cout << "_______________________________________________________\n";
        cout << "\t\tLogin Screen";
        cout << "\n_______________________________________________________\n";

        if (loginFaild)
        {
            cout << "\nInvalid username / Password!\n";
        }
        cout << "Enter Username: "; cin >> username;
        cout << "Enter Password: "; cin >> password;
        loginFaild = !checkUsernameAndPassword(username, password);

    } while (loginFaild);

    mainMenu();
}

//main
int main()
{
    
    login();
    system("pause");
    return 0;
}
//Ui Logic
void exitScreen() {
    cout << "\n________________________________\n";
    cout << "\t\tProgram Ends (-: \n";
    cout << "\n________________________________\n";
}

void goBackToMainMenu() {
    cout << "\n\nPress Any Key TO Go Back To main Menu...";
    system("pause>0");
    mainMenu();
}

//Clients Functions

void showAllClients() {
    vector<stClient>clients = loadRecordsFromFile(clientFileName);
    if (clients.size() < 1)
    {
        cout << "\t\t\tNo Clients Available in the system!\n";
    }
    else
    {
        printAllClientsRecords(clients);
    }

}

void addNewClients() {

    cout << "________________________________\n";
    cout << setw(21) << right << "Add Client\n";
    cout << "________________________________\n\n";
    addClientsLoop();



}

void deleteClient() {


    cout << "________________________________\n";
    cout << setw(20) << right << "Delete Client\n";
    cout << "________________________________\n\n";

    vector<stClient>clients = loadRecordsFromFile(clientFileName);
    string accountNumber = readString("\nPlease Enter Account Number? ");

    deleteClientByAccountNumber(accountNumber, clients);

}

void updateClient() {


    cout << "________________________________\n";
    cout << setw(20) << right << "Update Client\n";
    cout << "________________________________\n\n";

    vector<stClient>clients = loadRecordsFromFile(clientFileName);
    string accountNumber = readString("\nPlease Enter Account Number? ");

    updateClientRecord(accountNumber, clients);


}

void findClient() {


    cout << "________________________________\n";
    cout << setw(20) << right << "Find Client\n";
    cout << "________________________________\n\n";

    vector<stClient>clients = loadRecordsFromFile(clientFileName);
    string accountNumber = readString("\nPlease Enter Account Number?");
    stClient client;

    if (findClientByAccountNumber(accountNumber, clients, client))
    {
        printRecord(client);
    }
    else
    {
        cout << "Client With [" << accountNumber << "] is not Found!\n";
    }
}

// Transactions Functions

void goBackToTransactionMenu() {

    cout << "\n\nPress Any Key TO Go Back To Transaction Menu...";
    system("pause>0");
    transactionMenu();
}

void depositScreen() {

    cout << "________________________________\n";
    cout << setw(20) << right << "Deposit Screen\n";
    cout << "________________________________\n\n";
    vector<stClient>vClient = loadRecordsFromFile(clientFileName);
    stClient client;
    string accountNumber = readString("\nPlease Enter Account Number? ");
    double deposit = 0;

    while (!findClientByAccountNumber(accountNumber, vClient, client))
    {
        cout << "\n Client with account number (" << accountNumber << ") not Found Please Enter Signed Account Number : ";
        accountNumber = readString("\nPlease Enter Account Number? ");
    }
    printRecord(client);

    cout << "\n\nPlease Enter How Much You Want To Deposit : ";
    cin >> deposit;

    depositBalanceToClientByAccountNumber(deposit, accountNumber, vClient);

}

void withdrawScreen() {

    cout << "________________________________\n";
    cout << setw(20) << right << "Withdraw Screen\n";
    cout << "________________________________\n\n";

    vector<stClient>vClient = loadRecordsFromFile(clientFileName);
    stClient client;
    string accountNumber = readString("Please Enter Account Number? ");
    double withdraw = 0;

    while (!findClientByAccountNumber(accountNumber, vClient, client))
    {
        cout << "\n Client with account number (" << accountNumber << ") not Found Please Enter Signed Account Number : ";
        accountNumber = readString("\nPlease Enter Account Number? ");
    }

    printRecord(client);

    cout << "\n\nPlease Enter How Much You Want To Withdraw : ";

    cin >> withdraw;

    while (withdraw > client.accountBalance)
    {
        cout << "Sorry , There isn't Enough Money to withdraw You Can withdraw up to : " << client.accountBalance << endl;
        cout << "\n\nPlease Enter How Much You Want To Withdraw : ";
        cin >> withdraw;
    }

    //Using Deposit Function but Sending amount Multplied by -1 To With Draw It.
    depositBalanceToClientByAccountNumber(withdraw * -1, accountNumber, vClient);
}

void totalBalanceScreen() {
    vector<stClient>vClient = loadRecordsFromFile(clientFileName);
    stClient client;

    if (vClient.size() == 0)
    {
        cout << "\t\t\tThere Is No Clients Found!\n";
    }
    else
    {
        showTotalBalance(vClient.size(), vClient);
        cout << "\n\t\t\tTotal Balance = " << calculateTotalBalance();
    }
}

// Users Functions

void showUsersList() {
    vector<stUsersData> userData = loadUsersFromFile(usersFileName);
    if (userData.size() < 1)
    {
        cout << "\n\nNo Users Found Please Add Users\n\n";
    }
    else
    {
        printAllUsersRecords(userData);
    }
}

void addNewUsers() {

    cout << "________________________________\n";
    cout << setw(21) << right << "Add Users\n";
    cout << "________________________________\n\n";
    addUsersLoop();
}

void deleteUsers() {
    cout << "________________________________\n";
    cout << setw(20) << right << "Delete Client\n";
    cout << "________________________________\n\n";

    vector<stUsersData>usersData = loadUsersFromFile(usersFileName);
    string username = readString("\nPlease Enter Username? ");

    deleteUserByUsername(username, usersData);
}

void updateUsers() {
    cout << "________________________________\n";
    cout << setw(20) << right << "Update User\n";
    cout << "________________________________\n\n";

    vector<stUsersData>vUsers = loadUsersFromFile(usersFileName);
    string username = readString("\nPlease Enter Username? ");

    updateUserRecord(username, vUsers);
}

void findUsers() {
    cout << "________________________________\n";
    cout << setw(20) << right << "Find User\n";
    cout << "________________________________\n\n";
    stUsersData user;
    vector<stUsersData> vUsers = loadUsersFromFile(usersFileName);
    string username = readString("\nPlease Enter Username? ");
    if (findUserByUserName(username , vUsers , user))
    {
        printUsersRecord(user);
    }
    else
    {
        cout << "\nUser With This Username[" << username << "] Not Found \n";
        
    }

}

void goBackToManageUsersScreen() {
    cout << "Press Any Key To Get Back To Manage screen menu....";
    system("pause>0");
    manageUsersMenu();
}