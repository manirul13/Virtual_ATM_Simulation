/******************************************************************************
 * Project    : Virtual ATM Simulation
 * Description: Main driver program
 *
 * Author     : Manirul Islam
 * GitHub     : https://github.com/manirul13
 * Repository : https://github.com/manirul13/Virtual_ATM_Simulation
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "atm.h"

int main(void)
{
    Account accounts[MAX_ACCOUNTS];

    int count = 0;
    int index = -1;

    long entered_acc;
    int entered_pin;

    int choice;
    int login_attempt = 0;

    /* Load all accounts */
    if (!dummy_accounts(accounts, &count))
    {
        printf("Unable to load account database.\n");
        return EXIT_FAILURE;
    }

    printf("\n=====================================================\n");
    printf("          🏦 WELCOME TO VIRTUAL ATM 🏦\n");
    printf("=====================================================\n");

    /* Login (Maximum 3 attempts) */
    while (login_attempt < 3)
    {
        printf("\nEnter Account Number : ");

        if (scanf("%ld", &entered_acc) != 1)
        {
            printf("Invalid account number.\n");

            while (getchar() != '\n');

            continue;
        }

        getchar(); /* Remove newline */

        printf("Enter 4-digit PIN : ");

        entered_pin = masked_pin();

        if (entered_pin == -1)
        {
            login_attempt++;
            continue;
        }

        index = find_account(accounts,
                             count,
                             entered_acc,
                             entered_pin);

        if (index != -1)
        {
            printf("\n=========================================\n");
            printf("Login Successful\n");
            printf("Welcome %s\n",
                   accounts[index].name);
            printf("=========================================\n");

            break;
        }

        login_attempt++;

        printf("\nIncorrect Account Number or PIN.\n");

        if (login_attempt < 3)
        {
            printf("Remaining Attempts : %d\n",
                   3 - login_attempt);
        }
    }

    if (index == -1)
    {
        printf("\nAccount Locked.\n");
        printf("Please contact your bank.\n");

        return EXIT_FAILURE;
    }

    /* Main Menu */
    do
    {
        printf("\n=========================================\n");
        printf("             MAIN MENU\n");
        printf("=========================================\n");

        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Change PIN\n");
        printf("5. Fast Cash (₹2000)\n");
        printf("6. Mini Statement\n");
        printf("7. Exit\n");

        printf("\nEnter Choice : ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid Input.\n");

            while (getchar() != '\n');

            continue;
        }

        switch (choice)
        {
            case 1:
                check_balance(&accounts[index]);
                break;

            case 2:
                deposit(&accounts[index]);
                save_all_accounts(accounts, count);
                break;

            case 3:
                withdraw(&accounts[index]);
                save_all_accounts(accounts, count);
                break;

            case 4:
                change_pin(&accounts[index]);
                save_all_accounts(accounts, count);
                break;

            case 5:
                fast_cash(&accounts[index]);
                save_all_accounts(accounts, count);
                break;

            case 6:
                last_transactions(accounts[index].account_number);
                break;

            case 7:
                printf("\nSaving Account Information...\n");
                save_all_accounts(accounts, count);

                printf("Thank you for using Virtual ATM.\n");
                printf("Have a Nice Day!\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    } while (choice != 7);

    return EXIT_SUCCESS;
}