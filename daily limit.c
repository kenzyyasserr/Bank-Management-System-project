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

