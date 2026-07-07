/******************************************************************************
 * Project    : Virtual ATM Simulation
 * Description: ATM simulation with account management, transactions,
 *              PIN authentication and file handling.
 *
 * Author     : Manirul Islam
 * GitHub     : https://github.com/manirul13
 * Repository : https://github.com/manirul13/Virtual_ATM_Simulation
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "atm.h"

/*---------------------------------------------------------------------------
 * Create default accounts if accounts.txt is missing or empty
 *---------------------------------------------------------------------------*/
static void create_dummy_accounts(void)
{
    FILE *fp = fopen(ACCOUNT_FILE, "w");

    if(fp == NULL)
    {
        printf("Error: Unable to create %s\n", ACCOUNT_FILE);
        exit(EXIT_FAILURE);
    }

    fprintf(fp,"Manirul_I 8250623436 8250 15000.00\n");
    fprintf(fp,"Aisha_Khan 1234567890 2001 3000.00\n");
    fprintf(fp,"Zubeen_Garg 9876543210 2012 12000.00\n");
    fprintf(fp,"Saif_Ali 1112223333 2011 1200.00\n");
    fprintf(fp,"Alice_Smith 2223334444 2022 1500.00\n");
    fprintf(fp,"Bob_Johnson 3334445555 2033 1600.00\n");
    fprintf(fp,"Carol_White 4445556666 2044 2000.00\n");
    fprintf(fp,"David_Brown 5556667777 2055 4000.00\n");
    fprintf(fp,"Eve_Davis 6667778888 2066 2500.00\n");
    fprintf(fp,"Frank_Miller 7778889999 2077 9000.00\n");
    fprintf(fp,"Grace_Wilson 8889991010 2088 10000.00\n");
    fprintf(fp,"Ian_Lewis 5555566666 2055 20000.00\n");

    fclose(fp);

    /* Create transaction file if missing */
    fp = fopen(TRANSACTION_FILE, "a");
    if(fp)
        fclose(fp);
}

/*---------------------------------------------------------------------------
 * Load accounts
 *---------------------------------------------------------------------------*/
int dummy_accounts(Account accounts[], int *count)
{
    FILE *fp = fopen(ACCOUNT_FILE, "r");

    /* File doesn't exist */
    if(fp == NULL)
    {
        create_dummy_accounts();
        fp = fopen(ACCOUNT_FILE,"r");

        if(fp == NULL)
        {
            printf("Unable to open account file.\n");
            return 0;
        }
    }

    /* Check whether file is empty */
    fseek(fp,0,SEEK_END);

    if(ftell(fp) == 0)
    {
        fclose(fp);

        create_dummy_accounts();

        fp = fopen(ACCOUNT_FILE,"r");

        if(fp == NULL)
        {
            printf("Unable to open account file.\n");
            return 0;
        }
    }

    rewind(fp);

    *count = 0;

    while((*count < MAX_ACCOUNTS) &&
          fscanf(fp,"%49s %ld %d %lf",
                 accounts[*count].name,
                 &accounts[*count].account_number,
                 &accounts[*count].pin,
                 &accounts[*count].balance) == 4)
    {
        (*count)++;
    }

    fclose(fp);

    return 1;
}

/*---------------------------------------------------------------------------
 * Find account
 *---------------------------------------------------------------------------*/
int find_account(Account accounts[],
                 int count,
                 long entered_acc,
                 int entered_pin)
{
    for(int i=0;i<count;i++)
    {
        if(accounts[i].account_number == entered_acc &&
           accounts[i].pin == entered_pin)
        {
            return i;
        }
    }

    return -1;
}

/*---------------------------------------------------------------------------
 * Save all accounts
 *---------------------------------------------------------------------------*/
void save_all_accounts(Account accounts[], int count)
{
    FILE *fp = fopen(ACCOUNT_FILE,"w");

    if(fp == NULL)
    {
        printf("Unable to save account information.\n");
        return;
    }

    for(int i=0;i<count;i++)
    {
        fprintf(fp,"%s %ld %d %.2lf\n",
                accounts[i].name,
                accounts[i].account_number,
                accounts[i].pin,
                accounts[i].balance);
    }

    fclose(fp);
}

/*---------------------------------------------------------------------------
 * Record transaction
 *---------------------------------------------------------------------------*/
void record_transaction(long account_number,
                        const char *type,
                        double amount)
{
    FILE *fp = fopen(TRANSACTION_FILE,"a");

    if(fp == NULL)
        return;

    fprintf(fp,"%ld %s %.2lf\n",
            account_number,
            type,
            amount);

    fclose(fp);
}

/*---------------------------------------------------------------------------
 * Display last 5 transactions
 *---------------------------------------------------------------------------*/
void last_transactions(long account_number)
{
    FILE *fp = fopen(TRANSACTION_FILE, "r");

    if (fp == NULL)
    {
        printf("----------------------------------------------------\n");
        printf("📜 No transaction history found.\n");
        return;
    }

    char type[30];
    long acc_no;
    double amount;

    char history[100][100];
    int count = 0;

    while (fscanf(fp, "%ld %29s %lf",
                  &acc_no,
                  type,
                  &amount) == 3)
    {
        if (acc_no == account_number)
        {
            snprintf(history[count],
                     sizeof(history[count]),
                     "%s ₹%.2lf",
                     type,
                     amount);

            count++;

            if (count >= 100)
                break;
        }
    }

    fclose(fp);

    printf("----------------------------------------------------\n");

    if (count == 0)
    {
        printf("📜 No transactions available.\n");
        return;
    }

    printf("📜 Last %d Transaction(s)\n\n",
           (count < 5) ? count : 5);

    int start = (count > 5) ? count - 5 : 0;

    for (int i = start; i < count; i++)
    {
        printf("%d. %s\n",
               i - start + 1,
               history[i]);
    }
}

/*---------------------------------------------------------------------------
 * Check Balance
 *---------------------------------------------------------------------------*/
void check_balance(Account *acc)
{
    printf("----------------------------------------------------\n");
    printf("💰 Available Balance : ₹%.2lf\n",
           acc->balance);
}

/*---------------------------------------------------------------------------
 * Deposit Money
 *---------------------------------------------------------------------------*/
void deposit(Account *acc)
{
    double amount;

    printf("----------------------------------------------------\n");
    printf("👉 Enter Deposit Amount : ₹");

    if (scanf("%lf", &amount) != 1)
    {
        printf("❌ Invalid Input.\n");

        while (getchar() != '\n');

        return;
    }

    if (amount <= 0)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Deposit amount must be greater than zero.\n");
        return;
    }

    if ((int)amount % 100 != 0)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Amount must be in multiples of ₹100.\n");
        return;
    }

    acc->balance += amount;

    record_transaction(acc->account_number,
                       "Deposit",
                       amount);

    printf("----------------------------------------------------\n");
    printf("✅ ₹%.2lf deposited successfully.\n",
           amount);

    printf("💰 Updated Balance : ₹%.2lf\n",
           acc->balance);
}

/*---------------------------------------------------------------------------
 * Withdraw Money
 *---------------------------------------------------------------------------*/
void withdraw(Account *acc)
{
    double amount;

    printf("----------------------------------------------------\n");
    printf("👉 Enter Withdrawal Amount : ₹");

    if (scanf("%lf", &amount) != 1)
    {
        printf("❌ Invalid Input.\n");

        while (getchar() != '\n');

        return;
    }

    if (amount < MIN_WITHDRAW ||
        amount > MAX_WITHDRAW)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Withdrawal amount must be between ₹%d and ₹%d.\n",
               MIN_WITHDRAW,
               MAX_WITHDRAW);
        return;
    }

    if ((int)amount % 100 != 0)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Amount must be in multiples of ₹100.\n");
        return;
    }

    if (amount > acc->balance)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Insufficient Balance.\n");
        return;
    }

    acc->balance -= amount;

    record_transaction(acc->account_number,
                       "Withdraw",
                       amount);

    printf("----------------------------------------------------\n");
    printf("✅ ₹%.2lf withdrawn successfully.\n",
           amount);

    printf("💰 Remaining Balance : ₹%.2lf\n",
           acc->balance);
}

/*---------------------------------------------------------------------------
 * Read 4-digit PIN with masking
 *---------------------------------------------------------------------------*/
int masked_pin(void)
{
    struct termios oldt, newt;

    char pin[5];
    int index = 0;
    char ch;

    /* Save terminal settings */
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    /* Disable echo */
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (1)
    {
        ch = getchar();

        /* Stop when Enter is pressed */
        if (ch == '\n')
            break;

        /* Accept only digits */
        if (ch >= '0' && ch <= '9')
        {
            if (index < 4)
            {
                pin[index++] = ch;
                printf("*");
                fflush(stdout);
            }
        }

        /* Handle Backspace */
        else if ((ch == 127 || ch == '\b') && index > 0)
        {
            index--;

            printf("\b \b");
            fflush(stdout);
        }
    }

    /* Restore terminal settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    pin[index] = '\0';

    printf("\n");

    if (index != 4)
    {
        printf("❌ PIN must contain exactly 4 digits.\n");
        return -1;
    }

    return atoi(pin);
}

/*---------------------------------------------------------------------------
 * Change PIN
 *---------------------------------------------------------------------------*/
void change_pin(Account *acc)
{
    int current_pin;
    int new_pin;
    int confirm_pin;

    printf("----------------------------------------------------\n");
    printf("🔑 Enter Current PIN : ");

    current_pin = masked_pin();

    if (current_pin != acc->pin)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Incorrect Current PIN.\n");
        return;
    }

    printf("----------------------------------------------------\n");
    printf("🆕 Enter New 4-digit PIN : ");

    new_pin = masked_pin();

    if (new_pin == -1)
        return;

    if (new_pin == acc->pin)
    {
        printf("----------------------------------------------------\n");
        printf("❌ New PIN cannot be the same as the old PIN.\n");
        return;
    }

    printf("----------------------------------------------------\n");
    printf("🔁 Confirm New PIN : ");

    confirm_pin = masked_pin();

    if (confirm_pin != new_pin)
    {
        printf("----------------------------------------------------\n");
        printf("❌ PIN confirmation failed.\n");
        return;
    }

    acc->pin = new_pin;

    printf("----------------------------------------------------\n");
    printf("✅ PIN changed successfully.\n");
}

/*---------------------------------------------------------------------------
 * Fast Cash
 *---------------------------------------------------------------------------*/
void fast_cash(Account *acc)
{
    const double amount = 2000.0;

    printf("----------------------------------------------------\n");

    if (acc->balance < amount)
    {
        printf("❌ Insufficient Balance.\n");
        return;
    }

    acc->balance -= amount;

    record_transaction(acc->account_number,
                       "FastCash",
                       amount);

    printf("✅ ₹%.2lf withdrawn successfully.\n", amount);
    printf("💰 Remaining Balance : ₹%.2lf\n",
           acc->balance);
}