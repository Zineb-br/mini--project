#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char name[50];
    int accountNumber;
    char password[20];
    float balance;
} Account;

Account accounts[MAX_USERS];
int userCount = 0;

// 1. Create Account
void createAccount() {
    Account acc;
    printf("Name: ");
    scanf("%s", acc.name);
    printf("Account Number: ");
    scanf("%d", &acc.accountNumber);
    printf("Password: ");
    scanf("%s", acc.password);
    acc.balance = 0.0;
    accounts[userCount++] = acc;
    printf("Account created.\n");
}

// 2. Login
int login() {
    int accNum;
    char pass[20];
    printf("Account Number: ");
    scanf("%d", &accNum);
    printf("Password: ");
    scanf("%s", pass);

    for (int i = 0; i < userCount; i++) {
        if (accounts[i].accountNumber == accNum && strcmp(accounts[i].password, pass) == 0)
            return i;
    }
    printf("Login failed.\n");
    return -1;
}

// 3. Deposit
void deposit(int i) {
    float amount;
    printf("Amount to deposit: ");
    scanf("%f", &amount);
    accounts[i].balance += amount;
    printf("New balance: %.2f\n", accounts[i].balance);
}

// 4. Transfer
void transfer(int i) {
    int targetAcc;
    float amount;
    printf("Target Account: ");
    scanf("%d", &targetAcc);
    printf("Amount: ");
    scanf("%f", &amount);

    if (accounts[i].balance < amount) {
        printf("Insufficient balance.\n");
        return;
    }

    for (int j = 0; j < userCount; j++) {
        if (accounts[j].accountNumber == targetAcc) {
            accounts[i].balance -= amount;
            accounts[j].balance += amount;
            printf("Transfer done.\n");
            return;
        }
    }
    printf("Target not found.\n");
}

// 5. Check Balance
void checkBalance(int i) {
    printf("Balance: %.2f\n", accounts[i].balance);
}

// 6. Delete Account
void deleteAccount(int i) {
    if (accounts[i].balance > 0) {
        printf("Cannot delete. Balance not zero.\n");
        return;
    }

    for (int j = i; j < userCount - 1; j++) {
        accounts[j] = accounts[j + 1];
    }
    userCount--;
    printf("Account deleted.\n");
}

// Main menu
int main() {
    int choice;
    int userIndex;

    while (1) {
        printf("\n1. Create Account\n2. Login\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            createAccount();
        } else if (choice == 2) {
            userIndex = login();
            if (userIndex != -1) {
                int opt;
                do {
                    printf("\n1. Deposit\n2. Transfer\n3. Check Balance\n4. Delete Account\n5. Logout\nChoice: ");
                    scanf("%d", &opt);
                    if (opt == 1) deposit(userIndex);
                    else if (opt == 2) transfer(userIndex);
                    else if (opt == 3) checkBalance(userIndex);
                    else if (opt == 4) deleteAccount(userIndex);
                } while (opt != 5);
            }
        } else {
            break;
        }
    }

    return 0;
}
