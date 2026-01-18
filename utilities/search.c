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

    printf("\033[1;36mAccount Number:\033[0m %s\n", acc[idx].accountNumber);
    printf("\033[1;36mName          : \033[0m%s\n", acc[idx].name);
    printf("\033[1;36mE-mail        : \033[0m%s\n", acc[idx].email);
    printf("\033[1;36mBalance       : \033[0m%.2f $\n", acc[idx].balance);
    printf("\033[1;36mMobile        : \033[0m%s\n", acc[idx].mobile);
    printf("\033[1;36mDate Opened   : \033[0m%s %d\n",months[acc[idx].open.month - 1],acc[idx].open.year);

    char status_print[20];
    strcpy(status_print, acc[idx].status);

    for (int j = 0; status_print[j]; j++)
        status_print[j] = tolower(status_print[j]);

    status_print[0] = toupper(status_print[0]);

    printf("\033[1;36mStatus        : \033[0m%s\n", status_print);



    // clean_stdin();
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
        printf("\033[1;34mEnter the account number: \033[0m");
        if (!fgets(accountNumber, sizeof(accountNumber), stdin)) continue;
        accountNumber[strcspn(accountNumber, "\n")] = '\0';

        if (strlen(accountNumber) == 0)
        {
            printf("\033[1;31mInput cannot be empty. Try again.\033[0m\n");
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
            printf("\033[1;31mThe account number is not found! Try again.\033[0m\n");

    }
    while (index == -1);

    return index;
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


    printf("\033[1;36mEnter keyword to search in Name: \033[0m");
    fgets(keyword,sizeof(keyword),stdin);
    keyword[strcspn(keyword, "\n")]='\0';

    for (int i = 0; keyword[i]; i++)
        keyword[i] = tolower(keyword[i]);  // lowercase keyword

    printf("\n\033[1;33mSearch Results:\033[0m\n");
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
                printf("\033[1;36mAccount Number: %s\n", acc[i].accountNumber);
                printf("\033[1;36mName          : %s\n", acc[i].name);
                printf("\033[1;36mE-mail        : %s\n", acc[i].email);
                printf("\033[1;36mBalance       : %.2f $\n", acc[i].balance);
                printf("\033[1;36mMobile        : %s\n", acc[i].mobile);
                printf("\033[1;36mDate Opened   : \033[0m%s %d\n",months[acc[i].open.month - 1],acc[i].open.year);
                char status_print[20];
                strcpy(status_print, acc[i].status);

                for (int j = 0; status_print[j]; j++)
                    status_print[j] = tolower(status_print[j]);

                status_print[0] = toupper(status_print[0]);

                printf("\033[1;36mStatus        : \033[0m%s\n", status_print);
                printf("\033[1;36m-------------------------------------------------------\033[0m\n");
                foundit = 1;
                break;
            }
            token = strtok(NULL, " ");
        }
    }

    if (!foundit)
        printf("\033[1;31mNo matches are found.\033[0m\n");
}