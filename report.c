void report()
{
    int idx = get_account_index();
    if (idx == -1) return;

    char filename[20];
    sprintf(filename, "%s.txt", acc[idx].accountNumber);

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("No transactions found for account %s\n", acc[idx].accountNumber);
        return;
    }

    char lines[100][MAX_BUFFER];
    int count = 0;

    while (fgets(lines[count], sizeof(lines[count]), file) != NULL && count < 100)
        count++;

    fclose(file);

    printf("\nLast 5 transactions for account %s:\n", acc[idx].accountNumber);
    printf("-------------------------------------\n");

    int start;
    if (count > 5)
    {
        start = count - 5;
    }
    else
    {
        start = 0;
    }


    int i = start;
    while (i < count)
    {
        printf("%s", lines[i]);
        i++;
    }

}
