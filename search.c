void search_account()
{
    int idx=get_account_index();  // call function to get account number
    const char *months[] =
    {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    if (idx == -1)
    {
        printf("Account not found!\n");
        return;
    }

    printf("Account Number: %s\n", acc[idx].accountNumber);
    printf("Name          : %s\n", acc[idx].name);
    printf("E-mail        : %s\n", acc[idx].email);
    printf("Balance       : %.2f $\n", acc[idx].balance);
    printf("Mobile        : %s\n", acc[idx].mobile);
    printf("Date Opened   : %s %d\n",months[acc[idx].open.month - 1],acc[idx].open.year);

    char status_print[20];
    strcpy(status_print, acc[idx].status);

    for (int j = 0; status_print[j]; j++)
        status_print[j] = tolower(status_print[j]);
    status_print[0] = toupper(status_print[0]);
    printf("Status        : %s\n", status_print);

    clean_stdin();
}
