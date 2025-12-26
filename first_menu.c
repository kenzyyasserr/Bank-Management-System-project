#include "bank_system.h"

// ------------------------ Quit program ------------------------
void quit()
{
    printf("\033[1;31mExiting program.\033[0m\n\033[1;33mGoodbye!\033[0m\n");  //red then yellow
    exit(0);
}

// -------------------------- Basic menu --------------------------
void first_menu()
{
    char choice[10];
    while(1)
    {
        printf("\n\033[1;35m--- MENU ---\033[0m\n");   //magenta
        printf("\033[1;36m1-LOGIN\033[0m\n");   //cyan
        printf("\033[1;36m2-QUIT\033[0m\n");    //cyan
        printf("\033[1;37mChoose an option: \033[0m");           //white

        if (!fgets(choice, sizeof(choice), stdin)) continue;
        choice[strcspn(choice, "\n")] = '\0';

        if (!strcmp(choice,"1") || !strcasecmp(choice,"LOGIN"))
        {
            printf("\033[1;32mYou chose LOGIN.\033[0m\n");     //green
            login();
            main_menu();
        }
        else if (!strcmp(choice,"2") || !strcasecmp(choice,"QUIT"))
        {
            quit();
        }
    }
}

// --------------------------- Load accounts after login -------------------------
void load_accounts()
{
    FILE *accounts=fopen("accounts.txt","r");
    if(accounts==NULL)
    {
        printf("\033[1;31mError could not open account.txt\033[0m\n");   //red
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