void search_account()
{
    int idx=get_account_index();  // call function to get account number
    if (idx == -1)
    {
        printf("Account not found!\n");
        return;
    }

    printf("Account Number: %s\n", acc[idx].accountNumber);
    printf("Name          : %s\n", acc[idx].name);
    printf("Email         : %s\n", acc[idx].email);
    printf("Mobile        : %s\n", acc[idx].mobile);
    printf("Balance       : %.2f\n", acc[idx].balance);
    printf("Status        : %s\n", acc[idx].status);
    printf("Open Date     : %02d/%d\n", acc[idx].open.month, acc[idx].open.year);

    clean_stdin();
}
