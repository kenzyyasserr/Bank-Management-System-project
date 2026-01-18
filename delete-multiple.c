#include "bank_system.h"

// ================================ Sub-menu ==========================================
void delete_multiple_menu()
{
    char choice[10];

    while (1)
    {
        printf("\n\033[1;34m============== DELETE MULTIPLE MENU ==============\033[0m\n");
        printf("\033[1;36m1. Delete inactive accounts (3+ months, balance = 0)\033[0m\n");
        printf("\033[1;36m2. Delete old accounts by date (3+ months, balance = 0)\033[0m\n");
        printf("\033[1;36m3. Delete accounts by month & year (balance = 0)\033[0m\n");
        printf("\033[1;36m4. Back to main menu\033[0m\n");
        printf("\033[1;37mChoose an option: \033[0m");

        if (!fgets(choice, sizeof(choice), stdin))
            continue;

        choice[strcspn(choice, "\n")] = '\0';

        if (!strcmp(choice, "1"))
        {
            delete_multiple(1);   // Inactive option
        }
        else if (!strcmp(choice, "2"))
        {
            delete_multiple(2);   // Date option
        }
        else if (!strcmp(choice, "3"))
        {
            delete_by_month_year();
        }
        else if (!strcmp(choice, "4") || !strcasecmp(choice, "BACK"))
        {
            return;  //return to the main menu
        }
        else
        {
            printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
        }
    }
}

// ============================= The functions ===========================================
void delete_exact_date()
{
    int m, y;
    printf("\033[1;36mEnter exact creation date (MM YYYY): \033[0m");
    if (scanf("%d %d", &m, &y) != 3)
    {
        clean_stdin();
        printf("\033[1;31mInvalid date input\033[0m\n");
        return;
    }
    clean_stdin();

    int deleted = 0;

    for (int i = 0; i < accCounter; )
    {
        if (acc[i].balance == 0 &&
            acc[i].open.month == m &&
            acc[i].open.year == y)
        {
            for (int j = i; j < accCounter - 1; j++)
                acc[j] = acc[j + 1];

            accCounter--;
            deleted++;
            continue;
        }

        i++;
    }

    if (deleted == 0)
    {
        printf("\033[1;31mNo accounts found for this date\033[0m\n");
        return;
    }

    printf("\033[1;32m%d accounts deleted successfully\033[0m\n", deleted);
    confirm_save();
}



void delete_by_month_year()
{
    int m, y;
    printf("\033[1;36mEnter month and year (MM YYYY): \033[0m");
    if (scanf("%d %d", &m, &y) != 2)
    {
        clean_stdin();
        printf("\033[1;31mInvalid input\033[0m\n");
        return;
    }
    clean_stdin();

    int deleted = 0;

    for (int i = 0; i < accCounter; )
    {
        if (acc[i].balance == 0 &&
            acc[i].open.month == m &&
            acc[i].open.year == y)
        {
            for (int j = i; j < accCounter - 1; j++)
                acc[j] = acc[j + 1];

            accCounter--;
            deleted++;
            continue;
        }
        i++;
    }

    if (deleted == 0)
    {
        printf("\033[1;31mNo accounts found for %02d/%d\033[0m\n", m, y);
        return;
    }

    printf("\033[1;32m%d accounts deleted successfully!\033[0m\n", deleted);
    confirm_save();
}



void delete_multiple(int option)
{
    time_t t = time(NULL);
    struct tm today = *localtime(&t);

    int deleted = 0;

    for (int i = 0; i < accCounter; )
    {
        int months_diff =
            (today.tm_year + 1900 - acc[i].open.year) * 12 +
            (today.tm_mon + 1 - acc[i].open.month);

        int delete_flag = 0;

        if (acc[i].balance == 0 && months_diff >= 3)
        {
            if (option == 1)
            {
                // Inactive option
                if (strcasecmp(acc[i].status, "inactive") == 0)
                    delete_flag = 1;
            }
            else if (option == 2)
            {
                // Date option
                delete_flag = 1;
            }
        }

        if (delete_flag)
        {
            for (int j = i; j < accCounter - 1; j++)
                acc[j] = acc[j + 1];

            accCounter--;
            deleted++;
            continue;
        }

        i++;
    }

    if (deleted == 0)
    {
        printf("\033[1;31mNo accounts matched the delete conditions\033[0m\n");
        return;
    }

    printf("\033[1;32m%d accounts deleted successfully!\033[0m\n", deleted);
    confirm_save();
}


