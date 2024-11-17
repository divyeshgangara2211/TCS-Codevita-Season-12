#include <iostream>
#include <vector>
#include <string>

using namespace std;

void bank_account(int initialBalance, vector<string> operations) {

    vector<int> balances;  // To keep track of balances after each commit
    vector<int> transactions;  // To keep track of transactions
    int currentBalance = initialBalance;

    for (const string& operation : operations) {

        if (operation.substr(0, 4) == "read"){
            cout << currentBalance << endl;
            
        }else if (operation.substr(0, 6) == "credit") {
            int amount = stoi(operation.substr(7));  // convert string to integer
            currentBalance += amount;
            transactions.push_back(amount);  // Add to transactions

        }else if (operation.substr(0, 5) == "debit") {
            int amount = stoi(operation.substr(6));  // convert string to integer
            currentBalance -= amount;
            transactions.push_back(-amount);  // Add to transactions as negative

        }else if (operation == "commit") {
            balances.push_back(currentBalance);
            transactions.clear();  // Clear transactions after commit

        }  else if (operation.substr(0, 5) == "abort") {
            size_t txIndex = stoi(operation.substr(6)) - 1;

            if (txIndex < transactions.size()) {
                currentBalance -= transactions[txIndex];
                transactions.erase(transactions.begin() + txIndex);  // Remove the transaction
            }

        } else if (operation.substr(0, 8) == "rollback") {
            size_t commitIndex = stoi(operation.substr(9)) - 1;
            if (commitIndex < balances.size()) {
                currentBalance = balances[commitIndex];
                transactions.clear();  // Clear transactions after rollback
                balances.erase(balances.begin() + commitIndex + 1, balances.end());  // Remove later commits
            }
        }
    }
}

int main() {
    int initialBalance;
    cin >> initialBalance;

    int n;
    cin >> n;

    vector<string> operations(n);
    cin.ignore();  // Ignore the newline character after reading n

    for (int i = 0; i < n; ++i) {
        getline(cin, operations[i]);
    }

    bank_account(initialBalance, operations);

    return 0;
}
