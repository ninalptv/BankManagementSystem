#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class BankAccount
{
private:
    string name;
    string passwrd;
    double balance;
public:
    string Setname()
    {
        return name;
    }
    string Setpswrd()
    {
        return passwrd;
    }
    double Setbalance()
    {
        return balance;
    }
    void Getname(string name)
    {
        this->name = name;
    }
    void Getpswrd(string passwrd)
    {
        this->passwrd = passwrd;
    }
    void Getbalance(double balance)
    {
        this->balance = balance;
    }
    BankAccount(string accountName, string pswrd, double initialBalance)
        : name(accountName), passwrd(pswrd), balance(initialBalance) {}

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
    }

    void withdraw(double amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
        }
        else
        {
            cout << "Insufficient funds." << endl;
        }
    }

    void display()
    {
        cout << "Account: " << name << "\nBalance: $" << balance << endl;
    }
    void BankManagement()
    {
        int choice;
        double amount;
        do
        {
            cout << "\n1. Deposit" << endl;
            cout << "2. Withdraw" << endl;
            cout << "3. Display Account" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter deposit amount: ";
                cin >> amount;
                deposit(amount);
                break;
            case 2:
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                withdraw(amount);
                break;
            case 3:
                display();
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice." << endl;
            }
        } while (choice != 4);
    }  
};

int main()
{
    setlocale(LC_ALL, "RU");
    string name,pswrd;
    double initialDeposit;
    vector<BankAccount> Accounts;
    char response;
    
    cout << "Welcome Bank Management System!\n";
    cout << "Are you an active customer of the bank(y/n): ";
    cin >> response;
    if (response == 'n')
    {
        cin.ignore();
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your pswd: ";
        getline(cin, pswrd);
        cout << "Enter initial deposit: ";
        cin >> initialDeposit;
        BankAccount account(name, pswrd, initialDeposit);
        account.BankManagement();
        Accounts.push_back(account);
        ofstream outputFile("BankAcount.txt", ios::app);
        outputFile << account.Setname() << " " << account.Setpswrd() << " " << account.Setbalance();
        outputFile.close();
    }
    else
    {
        cin.ignore();
        ifstream inputFile("BankAcount.txt");
        while (!inputFile.eof())
        {
            inputFile >> name>> pswrd>>initialDeposit;
            BankAccount account(name, pswrd, initialDeposit);
            Accounts.push_back(account);
        }
        inputFile.close();
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your pswd: ";
        getline(cin, pswrd);
        int a = 0;
        for (int i = 0; i < Accounts.size(); i++)
        {
            if (name == Accounts[i].Setname() and pswrd == Accounts[i].Setpswrd())
            {
                cout<< Accounts[i].Setname()<<", You are logged in.\n";
                a++;
                BankAccount account(Accounts[i].Setname(), Accounts[i].Setpswrd(), Accounts[i].Setbalance());               
                account.BankManagement();
                Accounts[i].Getname(account.Setname());
                Accounts[i].Getpswrd(account.Setpswrd());
                Accounts[i].Getbalance(account.Setbalance());
                ofstream outputFile("BankAcount.txt", ios::out);
                for (int i = 0; i < Accounts.size(); i++)
                {
                    outputFile <<"\n"<< Accounts[i].Setname() << " " << Accounts[i].Setpswrd() << " " << Accounts[i].Setbalance() << endl;
                }
                outputFile.close();
                break;
            }
        }
        if (!(a == 1))
        {
            cout << "Incorrect data\n";
        }
    return 0;
}

