#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

struct Account {
    std::string accountHolder;
    double balance;
    std::string password;
};

class Bank {
private:
    std::unordered_map<int, Account> accounts;

public:
    void createAccount(int accountNumber, const std::string& accountHolder, const std::string& password, double initialAmount) {
        if (accounts.find(accountNumber) != accounts.end()) {
            std::cout << "Account already exists with this account number." << std::endl;
            return;
        }
        if (initialAmount < 0) {
            std::cout << "Initial amount cannot be negative." << std::endl;
            return;
        }
        accounts[accountNumber] = {accountHolder, initialAmount, password};
        std::cout << "Account created successfully." << std::endl;
    }

    void retrieveAccountData(int accountNumber, const std::string& password) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end() && it->second.password == password) {
            std::cout << "Account Holder: " << it->second.accountHolder << std::endl;
            std::cout << "Account Balance: " << it->second.balance << std::endl;
        } else {
            std::cout << "Invalid account number or password." << std::endl;
        }
    }

    void transferFunds(int fromAccount, int toAccount, double amount) {
        auto fromIt = accounts.find(fromAccount);
        auto toIt = accounts.find(toAccount);
        
        if (fromIt != accounts.end() && toIt != accounts.end()) {
            if (fromIt->second.balance >= amount && amount >= 0) {
                fromIt->second.balance -= amount;
                toIt->second.balance += amount;
                std::cout << "Funds transferred successfully." << std::endl;
            } else {
                std::cout << "Invalid transfer or insufficient funds." << std::endl;
            }
        } else {
            std::cout << "One or both of the accounts do not exist." << std::endl;
        }
    }
};

int main() {
    Bank bank;

    int choice;
    do {
        std::cout << "1. Create Account\n2. Retrieve Account Data\n3. Transfer Funds\n4. Quit\n";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int accountNumber;
                std::string accountHolder;
                std::string password;
                double initialAmount;
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Account Holder Name: ";
                std::cin.ignore();
                std::getline(std::cin, accountHolder);
                std::cout << "Enter Password: ";
                std::cin >> password;
                std::cout << "Enter Initial Amount: ";
                std::cin >> initialAmount;
                bank.createAccount(accountNumber, accountHolder, password, initialAmount);
                break;
            }

            case 2: {
                int accountNumber;
                std::string password;
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Password: ";
                std::cin >> password;
                bank.retrieveAccountData(accountNumber, password);
                break;
            }

            case 3: {
                int fromAccount, toAccount;
                double amount;
                std::cout << "Enter Source Account Number: ";
                std::cin >> fromAccount;
                std::cout << "Enter Destination Account Number: ";
                std::cin >> toAccount;
                std::cout << "Enter Amount: ";
                std::cin >> amount;
                bank.transferFunds(fromAccount, toAccount, amount);
                break;
            }

            case 4:
                std::cout << "Exiting the system.\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
