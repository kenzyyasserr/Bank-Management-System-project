#include "bank_system.h"

// ------------------------ Quit program ------------------------
void quit()
{
    printf("Exiting program.\nGoodbye!\n");
    exit(0);
}

// -------------------------- Basic menu --------------------------
void first_menu()
{
    char choice[10];
    while(1)
    {
        printf("\n--- MENU ---\n");
        printf("1-LOGIN\n");
        printf("2-QUIT\n");
        printf("Choose an option: ");

        if (!fgets(choice, sizeof(choice), stdin)) continue;
        choice[strcspn(choice, "\n")] = '\0';

        if (!strcmp(choice,"1") || !strcasecmp(choice,"LOGIN"))
        {
            printf("You chose LOGIN.\n");
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