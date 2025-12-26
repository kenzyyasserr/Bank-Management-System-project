#include "bank_system.h"

// ================================= Daily limit =================================
void daily_limit(float *amount, int idx)
{
    const float MAX_DAILY = 50000.0f;
    const float MAX_TRANSACTION = 10000.0f;
    static float dailyTotal[500] = {0};
    static int lastDay[500] = {0}, lastMonth[500] = {0}, lastYear[500] = {0};

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (tm.tm_mday != lastDay[idx] || tm.tm_mon != lastMonth[idx] || tm.tm_year != lastYear[idx])
    {
        dailyTotal[idx] = 0;
        lastDay[idx] = tm.tm_mday;
        lastMonth[idx] = tm.tm_mon;
        lastYear[idx] = tm.tm_year;
    }

    while (1)
    {
        printf("Enter withdrawal amount: ");
        if (scanf("%f", amount) != 1)
        {
            clean_stdin();
            printf("Invalid input! Please enter a numeric value.\n");
            continue;
        }
        clean_stdin();

        if (*amount <= 0)
        {
            printf("Amount must be positive!\n");
            continue;
        }

        if (*amount > MAX_TRANSACTION)
        {
            printf("Transaction limit exceeded! Max per transaction is %.2f\n", MAX_TRANSACTION);
            continue;
        }

        if (*amount + dailyTotal[idx] > MAX_DAILY)
        {
            printf("Daily limit exceeded! You can withdraw up to %.2f more today.\n", MAX_DAILY - dailyTotal[idx]);
            continue;
        }

        if (*amount > acc[idx].balance)
        {
            printf("Insufficient balance! Current balance: %.2f\n", acc[idx].balance);
            continue;
        }

        dailyTotal[idx] += *amount;
        break;
    }
}


void withdraw()
{
    int idx = get_account_index();
    if (idx == -1) return;

    if (strcasecmp(acc[idx].status, "ACTIVE") != 0)
    {
        printf("Account is inactive! Cannot process withdrawal.\n");
        return;
    }

    float amount;
    daily_limit(&amount, idx);

    acc[idx].balance -= amount;
    printf("Withdrawal successful!\nAmount withdrawn: %.2f\n", amount);
    printf("Remaining balance: %.2f\n", acc[idx].balance);

    char transaction[MAX_BUFFER];
    sprintf(transaction, "WITHDRAW: %.2f", amount);
    append_transaction(acc[idx].accountNumber, transaction);
    confirm_save();
}


void deposit()
{
    int idx = get_account_index();
    if (idx == -1) return;

    if (strcasecmp(acc[idx].status, "ACTIVE") != 0)
    {
        printf("Account is inactive! Cannot process deposit.\n");
        return;
    }

    float amount;
    const float MAX_DEPOSIT = 10000.0f;

    while (1)
    {
        printf("Enter deposit amount: ");
        if (scanf("%f", &amount) != 1)
        {
            clean_stdin();
            printf("Invalid input! Please enter a numeric value.\n");
            continue;
        }
        clean_stdin();

        if (amount <= 0)
        {
            printf("Amount must be positive!\n");
            continue;
        }

        if (amount > MAX_DEPOSIT)
        {
            printf("Transaction limit exceeded! Max deposit per transaction is %.2f\n", MAX_DEPOSIT);
            continue;
        }

        break;
    }

    acc[idx].balance += amount;
    printf("Deposit successful! Amount deposited: %.2f\n", amount);
    printf("New balance: %.2f\n", acc[idx].balance);

    char transaction[MAX_BUFFER];
    sprintf(transaction, "DEPOSIT: %.2f", amount);
    append_transaction(acc[idx].accountNumber, transaction);
    confirm_save();
}


// ============================= Transfert ==========================
void transfer()
{
    printf("SENDER --->\n");
    int senderIdx = get_account_index();
    if (senderIdx == -1) return;

    if (strcasecmp(acc[senderIdx].status, "ACTIVE") != 0)
    {
        printf("Sender account is inactive! Cannot process transfer.\n");
        return;
    }

    printf("RECEIVER --->\n");
    int receiverIdx = get_account_index();
    if (receiverIdx == -1) return;

    if (strcasecmp(acc[receiverIdx].status, "ACTIVE") != 0)
    {
        printf("Receiver account is inactive! Cannot process transfer.\n");
        return;
    }

    float amount;
    const float MAX_TRANSFER = 10000.0f;

    while (1)
    {
        printf("Enter transfer amount: ");
        if (scanf("%f", &amount) != 1)
        {
            clean_stdin();
            printf("Invalid input! Please enter a numeric value.\n");
            continue;
        }
        clean_stdin();

        if (amount <= 0)
        {
            printf("Amount must be positive!\n");
            continue;
        }

        if (amount > MAX_TRANSFER)
        {
            printf("Transaction limit exceeded! Max transfer per transaction is %.2f\n", MAX_TRANSFER);
            continue;
        }

        if (amount > acc[senderIdx].balance)
        {
            printf("Insufficient balance in sender account! Current balance: %.2f\n", acc[senderIdx].balance);
            continue;
        }

        break;
    }

    acc[senderIdx].balance -= amount;
    acc[receiverIdx].balance += amount;

    printf("Transfer successful!\n");
    printf("Sender new balance: %.2f\n", acc[senderIdx].balance);
    printf("Receiver new balance: %.2f\n", acc[receiverIdx].balance);

    char transaction[MAX_BUFFER];
    sprintf(transaction, "TRANSFER OUT: %.2f to %s", amount, acc[receiverIdx].accountNumber);
    append_transaction(acc[senderIdx].accountNumber, transaction);

    sprintf(transaction, "TRANSFER IN: %.2f from %s", amount, acc[senderIdx].accountNumber);
    append_transaction(acc[receiverIdx].accountNumber, transaction);
    confirm_save();
}


void append_transaction(const char *accNumber, const char *transaction)
{
    char filename[20];
    sprintf(filename, "%s.txt", accNumber);

    FILE *file = fopen(filename, "a");
    if (!file)
    {
        printf("Error opening transaction file for account %s\n", accNumber);
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(file, "%02d/%02d/%04d %02d:%02d:%02d - %s\n",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec,
            transaction);

    fclose(file);
}