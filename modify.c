void modify()
{
    char newname[max_input];
    char newmobile[14];
    char newemail[2 * max_input];
    char choice[20];
    char accountNumber[max_input];
    int found = -1;

    do
    {
        printf("Enter the account number to modify data: ");
        if (!fgets(accountNumber, sizeof(accountNumber), stdin)) continue;
        accountNumber[strcspn(accountNumber, "\n")] = '\0';

        if (strlen(accountNumber) == 0)
        {
            printf("Input cannot be empty. Try again.\n");
            continue;
        }

        found = search(accountNumber);
        if (found==-1)
        {
            printf("The account number is not found! Try again.\n");
        }
    }
    while (found==-1);

    while (1)
    {
        printf("\nCurrent data:\n");
        printf("Name   : %s\n", acc[found].name);
        printf("Mobile : %s\n", acc[found].mobile);
        printf("E-mail : %s\n\n", acc[found].email);

        printf("1. Name\n2. Mobile\n3. E-mail\nChoose an option or q to quit: ");

        if (!fgets(choice, sizeof(choice), stdin)) continue;
        choice[strcspn(choice, "\n")] = '\0';

        if (!strcmp(choice, "q") || !strcmp(choice, "Q"))
        {
            printf("Exiting Modification.\n");
            return;
        }


        if (!strcmp(choice, "1"))
        {
            printf("Enter new Name: ");
            if (fgets(newname,sizeof(newname),stdin))
            {
                newname[strcspn(newname, "\n")]='\0';
                for (int i=0; newname[i]!='\0'; i++)
                {
                    if (i==0 || newname[i -1]==' ')
                        newname[i]=toupper(newname[i]);
                }
                strcpy(acc[found].name, newname);
                printf("name updated successfully.\n");
            }
        }
        else if(!strcmp(choice,"2"))
        {
            while (1)
            {
                printf("Enter new Mobile (11 digits): ");
                if (!fgets(newmobile,sizeof(newmobile),stdin))
                    continue;

                newmobile[strcspn(newmobile,"\n")] = '\0';

                if (strlen(newmobile)!= 11)
                {
                    printf("Invalid mobile number! Must be exactly 11 digits.\n");
                    continue;
                }
                int valid=1;
                for (int i=0; newmobile[i]!='\0'; i++)
                {
                    if (newmobile[i]<'0' || newmobile[i]>'9')
                    {
                        valid = 0;
                        break;
                    }
                }
                if (!valid)
                {
                    printf("Invalid mobile number! Must contain only digits.\n");
                    continue;
                }
                strcpy(acc[found].mobile, newmobile);
                printf("mobile number updated successfully.\n");
                break;
            }
        }

        else if(!strcmp(choice,"3"))
        {
            while(1)
            {
                printf("Enter new Email: ");
                if(!fgets(newemail,sizeof(newemail),stdin))
                    continue;

                newemail[strcspn(newemail,"\n")] = '\0';


                if(!emailvalidation(newemail))
                {
                    printf("Invalid email!\nPlease enter a valid email (e.g., example@mail.com).\n");
                    continue;
                }

                strcpy(acc[found].email, newemail);
                printf("mobile number updated successfully.\n");
                break;
            }
        }

    }
}



