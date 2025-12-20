void load_accounts()
{
    FILE *accounts=fopen("C:\\Users\\Mariam & Mayar\\Downloads\\accounts.txt","r");
    if(accounts==NULL)
    {
        printf("Error could not open account.txt\n");
        exit(1);
    }


    accCounter=0;
    while(!feof(accounts))
    {
        if (fscanf(accounts, " %10[^,],",acc[accCounter].accountNumber) != 1)
            break;
        fscanf(accounts, "%99[^,],",acc[accCounter].name);
        fscanf(accounts, "%99[^,],",acc[accCounter].email);
        fscanf(accounts, "%f,",&acc[accCounter].balance);
        fscanf(accounts, "%11[^,],",acc[accCounter].mobile);
        fscanf(accounts,"%d-%d,",&acc[accCounter].open.month,&acc[accCounter].open.year);
        fscanf(accounts,"%19[^,\n]",acc[accCounter].status);

        char *p=acc[accCounter].status;
        while(*p==' ')  p++;
        strcpy(acc[accCounter].status,p);
        accCounter++;
    }
    fclose(accounts);
}
