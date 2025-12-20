void modify()
{
    char newname[max_input];
    char newmobile[14];
    char newemail[2 * max_input];
    char choice[20];
    int modified=0;

    int found = get_account_index();

    printf("\nCurrent data:\n");
    printf("Name   : %s\n", acc[found].name);
    printf("Mobile : %s\n", acc[found].mobile);
    printf("E-mail : %s\n\n", acc[found].email);

    while (1)
    {
        printf("1. Name\n2. Mobile\n3. E-mail\nChoose an option or q to quit: ");

        if (!fgets(choice, sizeof(choice), stdin)) continue;
        choice[strcspn(choice, "\n")] = '\0';

        if (!strcmp(choice, "q") || !strcmp(choice, "Q"))
        {
            printf("Exiting Modification.\n");
            break;
        }

        if (!strcmp(choice, "1"))
        {
            printf("Enter new Name: ");
            if (fgets(newname, sizeof(newname), stdin))
            {
                newname[strcspn(newname, "\n")] = '\0';

                for (int i = 0; newname[i]; i++)
                    if (i == 0 || newname[i - 1] == ' ')
                        newname[i] = toupper(newname[i]);
                    else
                        newname[i] = tolower(newname[i]);
                strcpy(acc[found].name, newname);
                modified=1;
                printf("Name updated successfully.\n");
            }
        }
        else if (!strcmp(choice, "2"))
        {
            while (1)
            {
                printf("Enter new Mobile (11 digits): ");
                if (!fgets(newmobile, sizeof(newmobile), stdin)) continue;
                newmobile[strcspn(newmobile, "\n")] = '\0';

                int valid = strlen(newmobile) == 11;
                for (int i = 0; newmobile[i] && valid; i++)
                    if (!isdigit((unsigned char)newmobile[i])) valid = 0;

                if (!valid)
                {
                    printf("Invalid mobile number! Must be exactly 11 digits.\n");
                    continue;
                }

                strcpy(acc[found].mobile, newmobile);
                   modified=1;
                printf("Mobile number updated successfully.\n");
                break;
            }
        }
        else if (!strcmp(choice, "3"))
        {
            while (1)
            {
                printf("Enter new Email: ");
                if (!fgets(newemail, sizeof(newemail), stdin)) continue;
                newemail[strcspn(newemail, "\n")] = '\0';

                if (!emailvalidation(newemail))
                {
                    printf("Invalid email! Please enter a valid email (e.g., example@mail.com).\n");
                    continue;
                }

                strcpy(acc[found].email, newemail);
                   modified=1;
                printf("Email updated successfully.\n");
                break;
            }
        }
        else
        {
            printf("Invalid choice! Please try again.\n");
        }

        printf("\nUpdated data:\n");
        printf("Name   : %s\n", acc[found].name);
        printf("Mobile : %s\n", acc[found].mobile);
        printf("E-mail : %s\n\n", acc[found].email);
    }
    if(modified)
        confirm_save();
}




