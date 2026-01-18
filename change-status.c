#include "bank_system.h"

void change_status()
{
    int idx=get_account_index();
    if (idx==-1) return;
    int modified=0;

    printf("\n\033[1;36mCurrent status: \033[0m%s\n", acc[idx].status);
    printf("\033[1;34m1. ACTIVE\033[0m\n");
    printf("\033[1;34m2. INACTIVE\033[0m\n");
    printf("\033[1;37mChoose new status: \033[0m");

    char choice[10];
    if (!fgets(choice, sizeof(choice), stdin))
        return;

    choice[strcspn(choice, "\n")] = '\0';

    if (!strcmp(choice, "1") || !strcasecmp(choice, "ACTIVE"))
    {
        if(!strcasecmp(acc[idx].status,"Active"))
            printf("\033[1;31mAccount is already Active.\033[0m\n");
        else
        {
            strcpy(acc[idx].status, "active");
            printf("\033[1;32mStatus changed to ACTIVE successfully.\033[0m\n");
            modified=1;
        }
    }
    else if (!strcmp(choice, "2") || !strcasecmp(choice, "INACTIVE"))
    {

        if(!strcasecmp(acc[idx].status,"Inactive"))
            printf("\033[1;31mAccount is already Inactive.\033[0m\n");

        else
        {
            strcpy(acc[idx].status, "inactive");
            printf("\033[1;32mStatus changed to INACTIVE successfully.\033[0m\n");
            modified=1;
        }
    }
    else
    {
        printf("\033[1;31mInvalid choice!\033[0m \033[1;37mStatus not changed.\033[0m\n");
    }
    if(modified)
        confirm_save();

}
