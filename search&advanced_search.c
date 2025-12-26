#include "bank_system.h"


// ============================= Standard search ======================================
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

int emailvalidation(const char email[])
{
    int at_count = 0;
    int len = strlen(email);

    if (len < 5) return 0;

    for (int i = 0; i < len; i++)
    {
        if (email[i] == '@') at_count++;
        if (email[i] == ' ' || email[i] == '\\') return 0;
    }

    if (at_count != 1) return 0;

    const char *at_pos = strchr(email, '@');
    if (at_pos == email || *(at_pos+1) == '\0') return 0;
    if (*(at_pos+1) == '.') return 0;

    if (email[0]=='.' || email[len-1]=='.') return 0;

    for (int i = 0; i < len-1; i++)
        if (email[i]=='.' && email[i+1]=='.') return 0;

    if (!strchr(at_pos, '.')) return 0;

    return 1;
}



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



// ================================= Advanced search ==============================================
void advanced_search()
{
    char keyword[MAX_KEYWORD];
    int foundit = 0;
    const char *months[] =
    {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };


    printf("Enter keyword to search in Name: ");
    fgets(keyword,sizeof(keyword),stdin);
    keyword[strcspn(keyword, "\n")]='\0';

    for (int i = 0; keyword[i]; i++)
        keyword[i] = tolower(keyword[i]);  // lowercase keyword

    printf("\nSearch Results:\n");
    printf("----------------\n");

    for (int i = 0; i < accCounter; i++)
    {
        char nameLower[MAX_BUFFER];
        strcpy(nameLower, acc[i].name);

        for (int j = 0; nameLower[j]; j++)
            nameLower[j] = tolower(nameLower[j]);  // lowercase the name

        char *token = strtok(nameLower, " ");
        while (token != NULL)
        {
            if (strstr(token, keyword) != NULL)
            {
                printf("Account Number: %s\n", acc[i].accountNumber);
                printf("Name          : %s\n", acc[i].name);
                printf("E-mail        : %s\n", acc[i].email);
                printf("Balance       : %.2f $\n", acc[i].balance);
                printf("Mobile        : %s\n", acc[i].mobile);
                printf("Date Opened   : %s %d\n",months[acc[i].open.month - 1],acc[i].open.year);
                char status_print[20];
                strcpy(status_print, acc[i].status);

                for (int j = 0; status_print[j]; j++)
                    status_print[j] = tolower(status_print[j]);

                status_print[0] = toupper(status_print[0]);

                printf("Status        : %s\n", status_print);
                printf("----------------\n");
                foundit = 1;
                break;
            }
            token = strtok(NULL, " ");
        }
    }

    if (!foundit)
        printf("No matches are found.\n");
}