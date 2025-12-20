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

