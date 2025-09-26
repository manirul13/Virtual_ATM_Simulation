#ifndef ATM_H
#define ATM_H

#define ACCOUNT_FILE "accounts.txt"
#define TRANSACTION_FILE "transactions.txt"
#define MIN_WITHDRAW 100
#define MAX_WITHDRAW 10000
#define MAX_ACCOUNTS 100
#define NAME_LENTH 50

typedef struct
{
    char name[NAME_LENTH];
    long account_number;
    int pin;
    double balance;
} Account;

/* Account management */
int dummy_accounts(Account accounts[], int *count);
int find_account(Account accounts[], int count, long entered_acc, int entered_pin);
void save_all_accounts(Account accounts[], int count);
int masked_pin();

/* ATM operations */
void check_balance(Account *acc);
void deposit(Account *acc);
void withdraw(Account *acc);
void change_pin(Account *acc);
void fast_cash(Account *acc);

/* Transaction management */
void record_transaction(long account_number, const char *type, double amount);
void last_transactions(long account_number);

#endif
