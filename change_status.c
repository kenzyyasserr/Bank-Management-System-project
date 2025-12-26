#include "bank_system.h"

void change_status()
{
    int idx=get_account_index();
    if (idx==-1) return;
    int modified=0;

    printf("\nCurrent status: %s\n", acc[idx].status);
    printf("1. ACTIVE\n");
    printf("2. INACTIVE\n");
    printf("Choose new status: ");

    char choice[10];
    if (!fgets(choice, sizeof(choice), stdin))
        return;

    choice[strcspn(choice, "\n")] = '\0';

    if (!strcmp(choice, "1") || !strcasecmp(choice, "ACTIVE"))
    {
        if(!strcasecmp(acc[idx].status,"Active"))
            printf("Account is already Active.\n");
        else
        {
            strcpy(acc[idx].status, "active");
            printf("Status changed to ACTIVE successfully.\n");
            modified=1;
        }
    }
    else if (!strcmp(choice, "2") || !strcasecmp(choice, "INACTIVE"))
    {

        if(!strcasecmp(acc[idx].status,"Inactive"))
            printf("Account is already Inactive.\n");

        else
        {
            strcpy(acc[idx].status, "inactive");
            printf("Status changed to INACTIVE successfully.\n");
            modified=1;
        }
    }
    else
    {
        printf("Invalid choice! Status not changed.\n");
    }
    if(modified)
        confirm_save();

}
