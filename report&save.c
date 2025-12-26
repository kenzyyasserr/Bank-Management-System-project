#include "bank_system.h"

void report()
{
    int idx = get_account_index();
    if (idx == -1) return;

    char filename[20];
    sprintf(filename, "%s.txt", acc[idx].accountNumber);

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("033[1;31mNo transactions found for account %s\033[0m\n", acc[idx].accountNumber);
        return;
    }

    char lines[100][MAX_BUFFER];
    int count = 0;

    while (fgets(lines[count], sizeof(lines[count]), file) != NULL && count < 100)
        count++;

    fclose(file);

    printf("\n\033[1;34mLast 5 transactions for account %s:\033[0m\n", acc[idx].accountNumber);
    printf("-------------------------------------\n");

    int start;
    if (count > 5)
    {
        start = count - 5;
    }
    else
    {
        start = 0;
    }


    int i = start;
    while (i < count)
    {
        printf("%s", lines[i]);
        i++;
    }

}
void saveAcc()
{

    FILE *accounts=fopen("C:\\Users\\Mariam & Mayar\\Downloads\\accounts.txt", "w");
    if (accounts == NULL)
    {
        printf("\033[1;31mError could not save.\033[0m\n");
        return;
    }


    for (int i = 0; i < accCounter; i++)
    {
        fprintf(accounts,"%s,%s,%s,%.2f,%s,%02d-%04d,%s\n",acc[i].accountNumber,acc[i].name,acc[i].email,
                acc[i].balance,acc[i].mobile,acc[i].open.month,acc[i].open.year,acc[i].status);
    }

    fclose(accounts);


}
void confirm_save()
{
    char choice[10];

    printf("\n\033[1;33mDo you want to save changes?\033[0m\n");
    printf("\033[1;37m1. Yes\033[0m\n");
    printf("\033[1;37m2. No (Discard changes)\033[0m\n");
    printf("\033[1;36mChoose: \033[0m");

    if (!fgets(choice, sizeof(choice), stdin))
        return;

    choice[strcspn(choice, "\n")] = '\0';

    if (!strcmp(choice, "1") || !strcasecmp(choice, "YES"))
    {
        saveAcc();
         printf("\033[1;32mChanges saved successfully.\033[0m\n");
    }
    else
    {
        printf("\033[1;31mChanges discarded.\033[0m\n");
        load_accounts();
    }
}
