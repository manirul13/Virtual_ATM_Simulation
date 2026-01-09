#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"
#include <termios.h>
#include <unistd.h>

/* Load all accounts from file */
int dummy_accounts(Account accounts[], int *count)
{
    FILE *fp = fopen(ACCOUNT_FILE, "r");
    if (!fp)
    {
        // Create sample accounts if file doesn't exist
        fp = fopen(ACCOUNT_FILE, "w");
        fprintf(fp, "Manirul_I 8250623436 8250 15000.00\n");
        fprintf(fp, "Aisha_Khan 0123456789 2001 3000.00\n");
        fprintf(fp, "Zubeen_Garg 1234567890 2012 12000.00\n");
        fprintf(fp, "Saif_Ali 1112223333 2011 1200.00\n");
        fprintf(fp, "Alice_Smith 2223334444 2022 1500.00\n");
        fprintf(fp, "Bob_Johnson 3334445555 2033 1600.00\n");
        fprintf(fp, "Carol_White 4445556666 2044 2000.00\n");
        fprintf(fp, "David_Brown 5556667777 2055 4000.00\n");
        fprintf(fp, "Eve_Davis 6667778888 2066 2500.00\n");
        fprintf(fp, "Frank_Miller 7778889999 2077 9000.00\n");
        fprintf(fp, "Grace_Wilson 8889991010 2088 10000.00\n");
        fprintf(fp, "Ian_Lewis 5555566666 2055 20000.00\n");
        fclose(fp);
        fp = fopen(ACCOUNT_FILE, "r");

        // Create empty transactions file on first run
        FILE *t = fopen(TRANSACTION_FILE, "a");
        fclose(t);
    }

    *count = 0;
    while (fscanf(fp, "%s %ld %d %lf",
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

/* Find account index by account number & PIN */
int find_account(Account accounts[], int count, long entered_acc, int entered_pin)
{
    for (int i = 0; i < count; i++)
    {
        if (accounts[i].account_number == entered_acc &&
            accounts[i].pin == entered_pin)
        {
            return i;
        }
    }
    return -1;
}

/* Save all accounts back to file */
void save_all_accounts(Account accounts[], int count)
{
    FILE *fp = fopen(ACCOUNT_FILE, "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %ld %d %.2f\n",
                accounts[i].name,
                accounts[i].account_number,
                accounts[i].pin,
                accounts[i].balance);
    }
    fclose(fp);
}

/* Record transaction in file */
void record_transaction(long account_number, const char *type, double amount)
{
    FILE *fp = fopen(TRANSACTION_FILE, "a");
    if (!fp)
        return;
    fprintf(fp, "%ld %s %.2f\n", account_number, type, amount);
    fclose(fp);
}

/* Show last 5 transactions for a user */
void last_transactions(long account_number)
{
    FILE *fp = fopen(TRANSACTION_FILE, "r");
    if (!fp)
    {
        printf("----------------------------------------------------\n");
        printf("📜 No transactions found.\n");
        return;
    }

    char type[20];
    long acc;
    double amount;
    char lines[100][100];
    int count = 0;

    while (fscanf(fp, "%ld %s %lf", &acc, type, &amount) == 3)
    {
        if (acc == account_number)
        {
            sprintf(lines[count], "%s ₹%.2f", type, amount);
            count++;
        }
    }
    fclose(fp);

    if (count == 0)
    {
        printf("----------------------------------------------------\n");
        printf("📜 No transactions yet.\n");
        return;
    }

    printf("----------------------------------------------------\n");
    printf("\n📜 Last %d Transactions:\n", (count < 5) ? count : 5);
    int start = (count > 5) ? count - 5 : 0;
    for (int i = start; i < count; i++)
    {
        printf(" - %s\n", lines[i]);
    }
}

/* ATM Functions */
void check_balance(Account *acc)
{
    printf("----------------------------------------------------\n");
    printf(" 💸Your Current Balance: ₹%.2f\n", acc->balance);
}

void deposit(Account *acc)
{
    double amount;
    printf("----------------------------------------------------\n");
    printf("👉 Enter amount to deposit: ₹");
    scanf("%lf", &amount);

    if ((int)amount % 100 != 0)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Amount must be a multiple of ₹100.\n");
        return;
    }
    if (amount <= 0)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Invalid deposit amount.\n");
        return;
    }

    acc->balance += amount;
    printf("----------------------------------------------------\n");
    printf("✅ ₹%.2f deposited successfully📈📈\n", amount);
    record_transaction(acc->account_number, "Deposit", amount);
}

void withdraw(Account *acc)
{
    double amount;
    printf("----------------------------------------------------\n");
    printf("👉 Enter amount to withdraw: ₹");
    scanf("%lf", &amount);

    if ((int)amount % 100 != 0) // limitation of deposite amount
    {
        printf("----------------------------------------------------\n");
        printf("❌ Amount must be a multiple of ₹100.\n");
        return;
    }
    if (amount < MIN_WITHDRAW || amount > MAX_WITHDRAW)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Amount must be between ₹%d and ₹%d.\n", MIN_WITHDRAW, MAX_WITHDRAW);
        return;
    }
    if (amount > acc->balance)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Insufficient balance!\n");
        return;
    }

    acc->balance -= amount;
    printf("----------------------------------------------------\n");
    printf("✅ ₹%.2f withdrawn successfully📉📉\n", amount);
    record_transaction(acc->account_number, "Withdraw", amount);
}

/* Masked PIN entry using getchar() */
int masked_pin()
{
    char ch1, enter_pin[10];
    int i;

    for (i = 0; i < 10; i++)
    {
        ch1 = getchar();

        if (ch1 == '\n') // stop on Enter key
            break;

        if (ch1 >= '0' && ch1 <= '9') // only accept digits
        {
            enter_pin[i] = ch1;
            printf("*"); // mask digit
        }
        else
        {
            i--; // ignore invalid characters
        }
    }

    enter_pin[i] = '\0';
    printf("\n");

    return strtol(enter_pin, NULL, 10); // convert to integer safely
}


// int masked_pin(char *enter_pin)
// {
//     struct termios oldt, newt;
//     char ch1;
//     int i = 0;

//     // Save current terminal settings
//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;

//     // Disable echo
//     newt.c_lflag &= ~(ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);

//     // Read exactly 4 digits
//     while (i < 4)
//     {
//         ch1 = getchar();

//         if (ch1 >= '0' && ch1 <= '9')
//         {
//             enter_pin[i++] = ch1;
//             printf("*");          // mask input
//             fflush(stdout);
//         }
//     }

//     enter_pin[i] = '\0';          // null-terminate string

//     // Restore terminal settings
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

//     printf("\n");
//     return 0;
// }


/* Change PIN */
void change_pin(Account *acc)
{
    int current_pin, new_pin;
    printf("----------------------------------------------------\n");
    printf("🔑 Enter Current PIN: ");
    current_pin = masked_pin();

    if (current_pin != acc->pin)
    {
        printf("----------------------------------------------------\n");
        printf("❌ Incorrect PIN.\n");
        return;
    }

    printf("----------------------------------------------------\n");
    printf("🆕 Enter New 4-digit PIN: ");
    new_pin = masked_pin();

    if (new_pin == acc->pin)
    {
        printf("----------------------------------------------------\n");
        printf("❌ New PIN cannot be same as old PIN.\n");
        return;
    }

    acc->pin = new_pin;
    printf("----------------------------------------------------\n");
    printf("✅ PIN changed successfully.\n");
}
void fast_cash(Account *acc)
{
    double amount = 2000.0;
    if (acc->balance >= amount)
    {
        acc->balance -= amount;
        printf("----------------------------------------------------\n");
        printf("✅ ₹2000 withdrawn successfully via Quick Cash.\n");
        record_transaction(acc->account_number, "FastCash", amount);
    }
    else
    {
        printf("----------------------------------------------------\n");
        printf("❌ Insufficient Balance for Fast Cash.\n");
    }
}
