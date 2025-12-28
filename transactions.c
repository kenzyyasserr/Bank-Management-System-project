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
        printf("\033[1;34mEnter withdrawal amount: \033[0m");
        if (scanf("%f", amount) != 1)
        {
            clean_stdin();
            printf("\033[1;31mInvalid input! Please enter a numeric value.\033[0m\n");
            continue;
        }
        clean_stdin();

        if (*amount <= 0)
        {
            printf("\033[1;31mAmount must be positive!\033[0m\n");
            continue;
        }

        if (*amount > MAX_TRANSACTION)
        {
            printf("\033[1;31mTransaction limit exceeded!\033[0m \033[1;37mMax per transaction is %.2f\033[0m\n", MAX_TRANSACTION);
            continue;
        }

        if (*amount + dailyTotal[idx] > MAX_DAILY)
        {
            printf("\033[1;31mDaily limit exceeded!\033[0m \033[1;37mYou can withdraw up to %.2f more today.\033[0m\n", MAX_DAILY - dailyTotal[idx]);
            continue;
        }

        if (*amount > acc[idx].balance)
        {
            printf("\033[1;31mInsufficient balance!\033[0m \033[1;36mCurrent balance: %.2f\033[0m\n", acc[idx].balance);
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
        printf("\033[1;31mAccount is inactive! Cannot process withdrawal.\033[0m\n");
        return;
    }

    if (acc[idx].balance <= 0)
    {
        printf("\033[1;31mCannot withdraw. Balance is zero!\033[0m\n");
        return;
    }

    float amount;
    daily_limit(&amount, idx);

    acc[idx].balance -= amount;
    printf("\033[1;32mWithdrawal successful!\033[0m\n\033[1;33mAmount withdrawn: %.2f\033[0m\n", amount);
    printf("\033[1;33mRemaining balance: %.2f\033[0m\n", acc[idx].balance);

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
        printf("\033[1;31mAccount is inactive! Cannot process deposit.\033[0m\n");
        return;
    }

    float amount;
    const float MAX_DEPOSIT = 10000.0f;

    while (1)
    {
        printf("\033[1;36mEnter deposit amount: \033[0m");
        if (scanf("%f", &amount) != 1)
        {
            clean_stdin();
            printf("\033[1;31mInvalid input! Please enter a numeric value.\033[0m\n");
            continue;
        }
        clean_stdin();

        if (amount <= 0)
        {
            printf("\033[1;31mAmount must be positive!\033[0m\n");
            continue;
        }

        if (amount > MAX_DEPOSIT)
        {
            printf("\033[1;31mTransaction limit exceeded!\033[0m \033[1;37mMax deposit per transaction is %.2f\033[0m\n", MAX_DEPOSIT);
            continue;
        }

        break;
    }

    acc[idx].balance += amount;
    printf("\033[1;32mDeposit successful!\033[0m \033[1;37mAmount deposited: %.2f\033[0m\n", amount);
    printf("\033[1;32mNew balance: %.2f\033[0m\n", acc[idx].balance);

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
        printf("\033[1;31mSender account is inactive! Cannot process transfer.\033[0m\n");
        return;
    }
    if (acc[senderIdx].balance <= 0)
    {
        printf("\033[1;31mCannot transfer money. Balance is zero!\033[0m\n");
        return;
    }

    printf("RECEIVER --->\n");
    int receiverIdx = get_account_index();
    if (receiverIdx == -1) return;

    if (strcasecmp(acc[receiverIdx].status, "ACTIVE") != 0)
    {
        printf("\033[1;31mReceiver account is inactive! Cannot process transfer.\033[0m\n");
        return;
    }

    if (senderIdx == receiverIdx) {
    printf("\033[1;31mCannot transfer to the same account.\033[0m\n");
    return;
}

    float amount;
    const float MAX_TRANSFER = 10000.0f;

    while (1)
    {
        printf("\033[1;36mEnter transfer amount: \033[0m");
        if (scanf("%f", &amount) != 1)
        {
            clean_stdin();
            printf("\033[1;31mInvalid input! Please enter a numeric value.\033[0m\n");
            continue;
        }
        clean_stdin();

        if (amount <= 0)
        {
            printf("\033[1;31mAmount must be positive!\033[0m\n");
            continue;
        }

        if (amount > MAX_TRANSFER)
        {
            printf("\033[1;31mTransaction limit exceeded! Max transfer per transaction is %.2f\033[0m\n", MAX_TRANSFER);
            continue;
        }

        if (amount > acc[senderIdx].balance)
        {
            printf("\033[1;31mInsufficient balance in sender account! Current balance: %.2f\033[0m\n", acc[senderIdx].balance);
            continue;
        }

        break;
    }

    acc[senderIdx].balance -= amount;
    acc[receiverIdx].balance += amount;

    printf("\033[1;32mTransfer successful!\033[0m\n");
    printf("\033[1;33mSender new balance: %.2f\033[0m\n", acc[senderIdx].balance);
    printf("\033[1;33mReceiver new balance: %.2f\033[0m\n", acc[receiverIdx].balance);

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
        printf("\033[1;31mError opening transaction file for account %s\033[0m\n", accNumber);
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