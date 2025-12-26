#include "bank_system.h"


void main_menu()
{
    char choose[17];

    while(1)
    {
        printf("\n--- MAIN MENU ---\n");
        printf("1-ADD\n");
        printf("2-DELETE\n");
        printf("3-MODIFY\n");
        printf("4-SEARCH\n");
        printf("5-ADVANCED SEARCH\n");
        printf("6-CHANGE STATUS\n");
        printf("7-WITHDRAW\n");
        printf("8-DEPOSIT\n");
        printf("9-TRANSFER\n");
        printf("10-REPORT\n");
        printf("11-PRINT\n");
        printf("12-QUIT\n");
        printf("Choose one of the previous commands: ");

        if (!fgets(choose, sizeof(choose), stdin))
            continue;

        choose[strcspn(choose, "\n")] = '\0';

        if (!strcmp(choose,"1") || !strcasecmp(choose,"ADD"))
        {
            printf("You chose ADD.\n");
            add_account();
        }
        else if (!strcmp(choose,"2") || !strcasecmp(choose,"DELETE"))
        {
            printf("You chose DELETE.\n");
           delete_account();
        }
        else if (!strcmp(choose,"3") || !strcasecmp(choose,"MODIFY"))
        {
            printf("You chose MODIFY.\n");
            modify();
        }
        else if (!strcmp(choose,"4") || !strcasecmp(choose,"SEARCH"))
        {
            printf("You chose SEARCH.\n");
            search_account();
        }
        else if (!strcmp(choose,"5") || !strcasecmp(choose,"ADVANCED SEARCH"))
        {
            printf("You chose ADVANCED SEARCH.\n");
            advanced_search();
        }
        else if (!strcmp(choose,"6") || !strcasecmp(choose,"CHANGE STATUS"))
        {
            printf("You chose CHANGE STATUS.\n");
            change_status();
        }
        else if (!strcmp(choose,"7") || !strcasecmp(choose,"WITHDRAW"))
        {
            printf("You chose WITHDRAW.\n");
            withdraw();
        }
        else if (!strcmp(choose,"8") || !strcasecmp(choose,"DEPOSIT"))
        {
            printf("You chose DEPOSIT.\n");
            deposit();
        }
        else if (!strcmp(choose,"9") || !strcasecmp(choose,"TRANSFER"))
        {
            printf("You chose TRANSFER.\n");
            transfer();
        }
        else if (!strcmp(choose,"10") || !strcasecmp(choose,"REPORT"))
        {
            printf("You chose REPORT.\n");
            report();
        }
        else if (!strcmp(choose,"11") || !strcasecmp(choose,"PRINT"))
        {
            printf("You chose PRINT.\n");
        printSorted(acc, "accounts.txt");
        }
        else if (!strcmp(choose,"12") || !strcasecmp(choose,"QUIT"))
        {
            quit();
        }
        else
        {
            char opt[10];

            printf("Invalid choice!\n");
            printf("1. Back to Main Menu\n");
            printf("2. Exit Program\n");
            printf("Choose an option: ");

            if (!fgets(opt, sizeof(opt), stdin))
                continue;

            opt[strcspn(opt, "\n")] = '\0';

            if (!strcmp(opt, "2") || !strcasecmp(opt, "EXIT"))
            {
                quit();
            }
        }
    }


}