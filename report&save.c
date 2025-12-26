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
        printf("No transactions found for account %s\n", acc[idx].accountNumber);
        return;
    }

    char lines[100][MAX_BUFFER];
    int count = 0;

    while (fgets(lines[count], sizeof(lines[count]), file) != NULL && count < 100)
        count++;

    fclose(file);

    printf("\nLast 5 transactions for account %s:\n", acc[idx].accountNumber);
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
        printf("Error could not save.\n");
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

    printf("\nDo you want to save changes?\n");
    printf("1. Yes\n");
    printf("2. No (Discard changes)\n");
    printf("Choose: ");

    if (!fgets(choice, sizeof(choice), stdin))
        return;

    choice[strcspn(choice, "\n")] = '\0';

    if (!strcmp(choice, "1") || !strcasecmp(choice, "YES"))
    {
        saveAcc();
         printf("Changes saved successfully.\n");
    }
    else
    {
        printf("Changes discarded.\n");
        load_accounts();
    }
}
