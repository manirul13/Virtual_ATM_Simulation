#include <stdio.h>
#include "atm.h"

int main()
{
    Account accounts[MAX_ACCOUNTS];
    int count;
    long entered_acc;
    int entered_pin;

    dummy_accounts(accounts, &count);

    printf("\n----------------------------------------------------\n");
    printf("============🏧 WELCOME TO VIRTUAL ATM 🏧============\n");
    printf("----------------------------------------------------\n");
    printf("💳 Insert Your Debit Card (A/c Number): ");
    scanf("%ld", &entered_acc);
    getchar(); // clear newline before masked_pin()

    printf("🔒 Enter 4-digit PIN: ");
    entered_pin = masked_pin();

    int index = find_account(accounts, count, entered_acc, entered_pin);
    if (index == -1)
    {
        printf("❌ Incorrect account number or PIN!!\n");
        printf("Try Again!!!\n");
        printf("----------------------------------------------------\n");
        return 0;
    }

    printf("----------------------------------------------------\n");
    printf("✅ Login successful! Welcome\n");
    printf("A/c. Holder: %s  A/c. Number: %ld\n",
           accounts[index].name, accounts[index].account_number);

    int choice;
    do
    {
        printf("\n====================🏦 MAIN MENU====================\n");
        printf("A/c. Holder:%s  A/c. Number:%ld\n",
               accounts[index].name, accounts[index].account_number);
        printf("----------------------------------------------------\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Change PIN\n");
        printf("5. Quick Cash (₹2000)\n");
        printf("6. Mini Statement\n");
        printf("7. Exit\n");
        printf("👉 Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            check_balance(&accounts[index]);
            break;
        case 2:
            deposit(&accounts[index]);
            break;
        case 3:
            withdraw(&accounts[index]);
            break;
        case 4:
            change_pin(&accounts[index]);
            break;
        case 5:
            fast_cash(&accounts[index]);
            break;
        case 6:
            last_transactions(accounts[index].account_number);
            break;
        case 7:
            printf("🙏 Thank you for using ATM Service!\n");
            printf("🏦 Visit Again!\n");
            break;
        default:
            printf("❌ Invalid choice!!.\n");
            printf("----------------------------------------------------\n");
        }

        save_all_accounts(accounts, count);

    } while (choice != 7);

    return 0;
}
