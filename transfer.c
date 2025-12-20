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

