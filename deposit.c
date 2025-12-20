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

