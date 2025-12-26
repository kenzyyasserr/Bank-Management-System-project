#include "bank_system.h"

//------------- sort by name --------------------------
int compareByName(const void *a, const void *b)
{
    const account *acc1 = (const account *)a;
    const account *acc2 = (const account *)b;
    return strcmp(acc1->name, acc2->name);
}

void sortByName(account *acc, int n)
{
    qsort(acc, n, sizeof(account), compareByName);
}

//-------------- sort by date ------------------------
int compareByDate(const void *a, const void *b)
{
    account *acc1 = (account *)a;
    account *acc2 = (account *)b;

    // Compare year first
    if (acc1->open.year != acc2->open.year)
        return acc1->open.year - acc2->open.year;

    // Then month
    if (acc1->open.month != acc2->open.month)
        return acc1->open.month - acc2->open.month;

    // Then day
    return acc1->open.day - acc2->open.day;
}

void sortByDate(account arr[], int n)
{
    qsort(arr, n, sizeof(account), compareByDate);
}

// ----------------- sort by balance ---------------------
int compareByBalance(const void *a, const void *b)
{
    double bal1 = ((account *)a)->balance;
    double bal2 = ((account *)b)->balance;

    if (bal1 < bal2) return -1;
    if (bal1 > bal2) return 1;
    return 0;
}

void sortByBalance(account arr[], int n)
{
    qsort(arr, n, sizeof(account), compareByBalance);
}

// ================================= print ==========================================
void printSorted(account arr[], const char *filename)
{
    int s, count = 0;
    int check = 1;

    FILE *fp = fopen("accounts.txt", "r");
    if (!fp) {
        printf("\033[1;31mError: Cannot open file '%s'\033[0m\n", filename);
        return;
    }

    // Read data from file
    while (fscanf(fp, "%10[^,],%99[^,],%99[^,],%f,%11[^,],%d-%d,%9[^\n]\n",    //read all characters until a comma is found and don't includde the comma
                  arr[count].accountNumber,
                  arr[count].name,
                  arr[count].email,
                  &arr[count].balance,
                  arr[count].mobile,
                  &arr[count].open.month,
                  &arr[count].open.year,
                  arr[count].status) == 8)
    {
        // Set day to 1 as default since file doesn't have day
        arr[count].open.day = 1;
        count++;

        if (count >= max_users) {
            printf("\033[1;31mWarning: Reached maximum account limit of %d\033[0m\n", max_users);
            break;
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("\033[1;31mNo accounts found in file '%s'\033[0m\n", filename);
        return;
    }

    printf("Loaded %d accounts from '%s'\n", count, filename);

    printf("\n\033[1;34mChoose sorting option:\033[0m\n");
    printf("\033[1;36m1: Sort by name\033[0m\n");
    printf("\033[1;36m2: Sort by date\033[0m\n");
    printf("\033[1;36m3: Sort by balance\033[0m\n");
    printf("\033[1;33mEnter a valid choice: \033[0m");

    if (scanf("%d", &s) != 1) {
        printf("\033[1;31mInvalid input!!!\033[0m\n");
        return;
    }

    while (check) {
        switch (s) {
            case 1:
                sortByName(arr, count);
                printf("\033[1;33mSorted by name.\033[0m\n");
                check = 0;
                break;

            case 2:
                sortByDate(arr, count);
                printf("\033[1;33mSorted by date.\033[0m\n");
                check = 0;
                break;

            case 3:
                sortByBalance(arr, count);
                printf("\033[1;33mSorted by balance.\033[0m\n");
                check = 0;
                break;

            default:
                printf("\033[1;31mINVALID OPTION!\033[0m Please enter 1, 2 or 3: ");
                if (scanf("%d", &s) != 1) {
                    printf("\033[1;31mInvalid input!\033[0m\n");
                    return;
                }
        }
    }

    // Save sorted data to "accounts_sorted"
    fp = fopen("accounts_sorted.txt", "w");
    if (!fp) {
        printf("\033[1;31mError: Cannot create file 'accounts_sorted.txt'\033[0m\n");
        return;
    }

    // Write sorted data


    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%.f,%s,%02d-%04d,%s\n",
                arr[i].accountNumber,
                arr[i].name,
                arr[i].email,
                arr[i].balance,
                arr[i].mobile,
                arr[i].open.month,
                arr[i].open.year,
                arr[i].status);
    }


    fclose(fp);

    // display in terminal
      const char *months[] =
    {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    printf("\n\033[1;34mSorted Accounts:\n");
    printf("\033[1;33m=======================================================\033[0m\n");
    for (int i = 0; i < count; i++) {
        printf("\nAccount %d/%d:\n", i+1, count);
        printf("  Account Number: %s\n", arr[i].accountNumber);
        printf("  Name: %s\n", arr[i].name);
        printf("  Email: %s\n", arr[i].email);
        printf("  Balance: %.2lf\n", arr[i].balance);
        printf("  Mobile: %s\n", arr[i].mobile);
        printf("  Date Opened: %s %d\n", months[arr[i].open.month - 1],arr[i].open.year);
        printf("  Status: %s\n", arr[i].status);
    }
    clean_stdin();

    printf("\n\033[1;32mSorted data has been saved to 'accounts_sorted.txt'\033[0m\n");

}