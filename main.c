#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accnumber;
    char name[20];
    float balance;
};

void createAccount(struct Account accounts[], int *count);
void deposit(struct Account accounts[], int count);
void withdraw(struct Account accounts[], int count);
void checkBalance(struct Account accounts[], int count);
void saveAccounts(struct Account accounts[], int count);

int main() {
    struct Account accounts[100]; // Static array or dynamic allocation using malloc
    int accountcount = 0;

    // Read details from the file and update
    FILE *file = fopen("Bankdetial.txt", "r");
    if (file) {
        while (fscanf(file, "%d, %19s, %f", &accounts[accountcount].accnumber, accounts[accountcount].name, &accounts[accountcount].balance) == 3) {
            accountcount++;
        }
        fclose(file);
    }

    int choice;
    do {
        system("cls");
        printf("\n  ========= BANK MANAGEMENT SYSTEM =========\n");
        printf("\n             1.CREATE ACCOUNT\n");
        printf("\n             2.DEPOSIT\n");
        printf("\n             3.WITHDRAW\n");
        printf("\n             4.CHECK BALANCE\n");
        printf("\n             5.EXIT\n");
        printf("\n\tENTER YOUR CHOICE: \n\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(accounts, &accountcount);
                break;
            case 2:
                deposit(accounts, accountcount);
                break;
            case 3:
                withdraw(accounts, accountcount);
                break;
            case 4:
                checkBalance(accounts, accountcount);
                break;
            case 5:
                saveAccounts(accounts, accountcount);
                printf("Thank you for using our system!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again!\n");
        }

    } while (1);

    return 0;
}

void createAccount(struct Account accounts[], int *count) {
    // Implementation for creating an account
    if (*count == 100) {
        printf("Account limit reached. Cannot create more accounts.\n");
        return;
    }

    printf("Enter the account number: ");
    scanf("%d", &accounts[*count].accnumber);

    printf("Enter the account holder name: ");
    scanf("%s", accounts[*count].name);

    accounts[*count].balance = 0.0;

    (*count)++;
    printf("Account created successfully!\n");
}

void deposit(struct Account accounts[], int count) {
    // Implementation for depositing money
    int accnum;
    float amount;
    printf("Enter the account number: ");
    scanf("%d", &accnum);

    int i;
    for (i = 0; i < count; i++) {
        if (accounts[i].accnumber == accnum) {
            printf("Enter the amount to deposit: ");
            scanf("%f", &amount);

            if (amount > 0) {
                accounts[i].balance += amount;
                printf("Amount deposited successfully!\n");
            } else {
                printf("Invalid amount. Deposit failed.\n");
            }

            return;
        }
    }

    printf("Account not found.\n");
}

void withdraw(struct Account accounts[], int count) {
    // Implementation for withdrawing money
    int accnum;
    float amount;
    printf("Enter the account number: ");
    scanf("%d", &accnum);

    int i;
    for (i = 0; i < count; i++) {
        if (accounts[i].accnumber == accnum) {
            printf("Enter the amount to withdraw: ");
            scanf("%f", &amount);

            if (amount > 0 && amount <= accounts[i].balance) {
                accounts[i].balance -= amount;
                printf("Amount withdrawn successfully!\n");
            } else {
                printf("Invalid amount or insufficient balance. Withdrawal failed.\n");
            }

            return;
        }
    }

    printf("Account not found.\n");
}

void checkBalance(struct Account accounts[], int count) {
    // Implementation for checking balance
    int accnum;
    printf("Enter the account number: ");
    scanf("%d", &accnum);

    int i;
    for (i = 0; i < count; i++) {
        if (accounts[i].accnumber == accnum) {
            printf("Account holder: %s\n", accounts[i].name);
            printf("Account balance: %.2f\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}

void saveAccounts(struct Account accounts[], int count) {
    // Implementation for saving accounts to a file
    FILE *file = fopen("Bankdetial.txt", "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d, %s, %.2f\n", accounts[i].accnumber, accounts[i].name, accounts[i].balance);
        }
        fclose(file);
    } else {
        printf("Failed to save accounts to file.\n");
    }
}