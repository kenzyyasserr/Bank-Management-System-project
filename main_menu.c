#include "bank_system.h"


void main_menu()
{
    char choose[17];

    while(1)
    {
        printf("\n\033[1;34m-------------------- MAIN MENU --------------------\033[0m\n");   //blue
        //in cyan
        printf("\033[1;36m1-ADD\033[0m\n");
        printf("\033[1;36m2-DELETE\033[0m\n");
        printf("\033[1;36m3-MODIFY\033[0m\n");
        printf("\033[1;36m4-SEARCH\033[0m\n");
        printf("\033[1;36m5-ADVANCED SEARCH\033[0m\n");
        printf("\033[1;36m6-CHANGE STATUS\033[0m\n");
        printf("\033[1;36m7-WITHDRAW\033[0m\n");
        printf("\033[1;36m8-DEPOSIT\033[0m\n");
        printf("\033[1;36m9-TRANSFER\033[0m\n");
        printf("\033[1;36m10-REPORT\033[0m\n");
        printf("\033[1;36m11-PRINT\033[0m\n");
        printf("\033[1;36m12-QUIT\033[0m\n");
        printf("\033[1;37mChoose one of the previous commands: \033[0m");  //white

        if (!fgets(choose, sizeof(choose), stdin))
            continue;

        choose[strcspn(choose, "\n")] = '\0';

        if (!strcmp(choose,"1") || !strcasecmp(choose,"ADD"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;32mADD\033[0m\n");
            add_account();
        }
        else if (!strcmp(choose,"2") || !strcasecmp(choose,"DELETE"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;31mDELETE\033[0m\n");
           delete_account();
        }
        else if (!strcmp(choose,"3") || !strcasecmp(choose,"MODIFY"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;32mMODIFY\033[0m\n");
            modify();
        }
        else if (!strcmp(choose,"4") || !strcasecmp(choose,"SEARCH"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;33mSEARCH\033[0m\n");
            search_account();
        }
        else if (!strcmp(choose,"5") || !strcasecmp(choose,"ADVANCED SEARCH"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;34mADVANCED SEARCH\033[0m\n");
            advanced_search();
        }
        else if (!strcmp(choose,"6") || !strcasecmp(choose,"CHANGE STATUS"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;32mCHANGE STATUS\033[0m\n");
            change_status();
        }
        else if (!strcmp(choose,"7") || !strcasecmp(choose,"WITHDRAW"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;32mWITHDRAW\033[0m\n");
            withdraw();
        }
        else if (!strcmp(choose,"8") || !strcasecmp(choose,"DEPOSIT"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;32mDEPOSIT\033[0m\n");
            deposit();
        }
        else if (!strcmp(choose,"9") || !strcasecmp(choose,"TRANSFER"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;32mTRANSFER\033[0m\n");
            transfer();
        }
        else if (!strcmp(choose,"10") || !strcasecmp(choose,"REPORT"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;33mREPORT\033[0m\n");
            report();
        }
        else if (!strcmp(choose,"11") || !strcasecmp(choose,"PRINT"))
        {
            printf("\033[1;37mYou chose\033[0m \033[1;32mPRINT\033[0m\n");
        printSorted(acc, "accounts.txt");
        }
        else if (!strcmp(choose,"12") || !strcasecmp(choose,"QUIT"))
        {
            quit();
        }
        else
        {
            char opt[10];

            printf("\033[1;31mInvalid choice!\033[0m\n");   //red
            printf("\033[1;34m1. Back to Main Menu\033[0m\n");   //blue
            printf("\033[1;34m2. Exit Program\033[0m\n");    //blue
            printf("\033[1;37mChoose an option: \033[0m");  //white

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