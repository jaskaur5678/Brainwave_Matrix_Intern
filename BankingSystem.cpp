#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account {
private:
    string name;
    string accountNumber;
    double balance;

public:
    Account(string name, string accountNumber, double initialBalance) 
        : name(name), accountNumber(accountNumber), balance(initialBalance) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: $" << balance << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid withdrawal amount." << endl;
        }
    }

    void transfer(Account &toAccount, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            toAccount.deposit(amount);
            cout << "Transfer successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid transfer amount." << endl;
        }
    }

    void display() const {
        cout << "Account Holder: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }
};

class Bank {
private:
    vector<Account> accounts;

    Account* findAccount(string accountNumber) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

public:
    void createAccount(string name, string accountNumber, double initialBalance) {
        if (findAccount(accountNumber) == nullptr) {
            accounts.push_back(Account(name, accountNumber, initialBalance));
            cout << "Account created successfully." << endl;
        } else {
            cout << "Account number already exists." << endl;
        }
    }

    void deposit(string accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            account->deposit(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void withdraw(string accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            account->withdraw(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void transfer(string fromAccountNumber, string toAccountNumber, double amount) {
        Account* fromAccount = findAccount(fromAccountNumber);
        Account* toAccount = findAccount(toAccountNumber);
        if (fromAccount != nullptr && toAccount != nullptr) {
            fromAccount->transfer(*toAccount, amount);
        } else {
            cout << "One or both accounts not found." << endl;
        }
    }

    void displayAccount(string accountNumber) {
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            account->display();
        } else {
            cout << "Account not found." << endl;
        }
    }
};

int main() {
    Bank bank;
    int choice;
    string name, accountNumber, toAccountNumber;
    double amount;

    do {
        cout << "\nOnline Banking System\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. Display Account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter initial balance: ";
                cin >> amount;
                bank.createAccount(name, accountNumber, amount);
                break;
            case 2:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                bank.deposit(accountNumber, amount);
                break;
            case 3:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                bank.withdraw(accountNumber, amount);
                break;
            case 4:
                cout << "Enter your account number: ";
                cin >> accountNumber;
                cout << "Enter account number to transfer to: ";
                cin >> toAccountNumber;
                cout << "Enter amount to transfer: ";
                cin >> amount;
                bank.transfer(accountNumber, toAccountNumber, amount);
                break;
            case 5:
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.displayAccount(accountNumber);
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
