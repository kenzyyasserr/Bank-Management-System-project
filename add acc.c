/* ===== ADD ACCOUNT ===== */
void add_account(void)
{
    char newaccount[11];
    char addname[100];
    char addemail[100];
    char addmobile[12];
    int valid;

    /* ACCOUNT NUMBER */
    while (1)
    {
        printf("Enter new account number (10 digits): ");
        if (!fgets(newaccount, sizeof(newaccount), stdin))
            continue;

        newaccount[strcspn(newaccount, "\n")] = '\0';

        if (strlen(newaccount) != 10)
        {
            printf("Account number must be exactly 10 digits!\n");
            continue;
        }

        if (!digit(newaccount))
            printf("Invalid input. Digits only!\n");
        else if (accountexist(newaccount))
            printf("Duplicate account number!\n");
        else
            break;
    }

    clean_stdin();


    /* NAME */
    do
    {
        valid = 1;
        printf("Enter new Name: ");
        if (!fgets(addname, sizeof(addname), stdin))
            continue;

        addname[strcspn(addname, "\n")] = '\0';

        if (strlen(addname) == 0)
            valid = 0;

        for (int i = 0; addname[i] && valid; i++)
            if (!isalpha((unsigned char)addname[i]) &&
                    !isspace((unsigned char)addname[i]))
                valid = 0;

        if (!valid)
            printf("Invalid name. Try again.\n");

    }
    while (!valid);

    /* Capitalize first letter of each word */
    for (int i = 0; addname[i]; i++)
    {
        if (i == 0 || addname[i-1] == ' ')
            addname[i] = toupper(addname[i]);
        else
            addname[i] = tolower(addname[i]);
    }

    /* EMAIL */
    while (1)
    {
        printf("Enter new Email: ");
        if (!fgets(addemail, sizeof(addemail), stdin))
            continue;

        addemail[strcspn(addemail, "\n")] = '\0';

        if (!emailvalidation(addemail))
        {
            printf("Invalid email format! Please try again.\n");
            continue;
        }
        break;
    }

    /* MOBILE */
    do
    {
        valid = 1;
        printf("Enter new Mobile Number (11 digits): ");
        if (!fgets(addmobile, sizeof(addmobile), stdin))
            continue;

        addmobile[strcspn(addmobile, "\n")] = '\0';

        if (strlen(addmobile) != 11)
            valid = 0;

        for (int i = 0; addmobile[i] && valid; i++)
            if (!isdigit((unsigned char)addmobile[i]))
                valid = 0;

        if (!valid)
            printf("Invalid mobile number. Must be 11 digits\n");

    }
    while (!valid);

    /* STORE ACCOUNT */
    strcpy(acc[accCounter].accountNumber, newaccount);
    strcpy(acc[accCounter].name, addname);
    strcpy(acc[accCounter].email, addemail);
    strcpy(acc[accCounter].mobile, addmobile);
    acc[accCounter].balance = 0.0;
    strcpy(acc[accCounter].status, "ACTIVE");

    /* CURRENT DATE AND TIME */
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    acc[accCounter].open.day = tm.tm_mday;
    acc[accCounter].open.month = tm.tm_mon + 1;
    acc[accCounter].open.year = tm.tm_year + 1900;
    accCounter++;

    printf("\nAccount added successfully \n");
    printf("Creation date & time: %02d/%02d/%04d %02d:%02d:%02d\n",
           tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
           tm.tm_hour, tm.tm_min, tm.tm_sec);

    clean_stdin();
}
