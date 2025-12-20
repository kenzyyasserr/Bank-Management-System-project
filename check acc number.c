int get_account_index()
{
    char accountNumber[max_input];
    int index = -1;

    do
    {
        printf("Enter the account number: ");
        if (!fgets(accountNumber, sizeof(accountNumber), stdin)) continue;
        accountNumber[strcspn(accountNumber, "\n")] = '\0';

        if (strlen(accountNumber) == 0)
        {
            printf("Input cannot be empty. Try again.\n");
            continue;
        }

        for (int i = 0; i < accCounter; i++)
        {
            if (strcmp(accountNumber, acc[i].accountNumber) == 0)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            printf("The account number is not found! Try again.\n");

    }
    while (index == -1);

    return index;
}

