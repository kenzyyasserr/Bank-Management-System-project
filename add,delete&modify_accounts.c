#include "bank_system.h"

// =============================== Add new account =======================================

void clean_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ------------------------- check digits ----------------------------
int digit(const char *s)
{
    if (*s == '\0') return 0;
    for (int i = 0; s[i]; i++)
        if (!isdigit((unsigned char)s[i]))
            return 0;
    return 1;
}

// ------------------------ check duplicates ---------------------------------------
int accountexist(const char *newaccount)
{
    for (int i = 0; i < accCounter; i++)
        if (strcmp(newaccount, acc[i].accountNumber) == 0)
            return 1;
    return 0;
}

// --------------------------- function--------------------------------------------
void add_account(void)
{
    char newaccount[50];
    char addname[100];
    char addemail[100];
    char addmobile[50];
    int valid;


    // account number
    while (1)
    {
        printf("\033[1;33mEnter new account number\033[0m \033[1;34m10 digits: \033[0m");
        if (!fgets(newaccount, sizeof(newaccount), stdin)){
            // clean_stdin();
            continue;
        }

        newaccount[strcspn(newaccount, "\n")] = '\0';

        if (strlen(newaccount) != 10)
        {
            // clean_stdin();
            printf("\033[1;37mAccount number must be exactly\033[0m \033[1;34m10 digits!\033[0m\n");
            continue;
        }

        if (!digit(newaccount)){
            // clean_stdin();
            printf("\033[1;31mInvalid input. Digits only!\033[0m\n");
        }
        else if (accountexist(newaccount))
        {
            printf("\033[1;34mDuplicate\033[0m \033[1;37maccount number!\033[0m\n");
            // clean_stdin();
        }
        else
            break;
    }

    // clean_stdin();


    // Name
    do
    {
        valid = 1;
        printf("\033[1;37mEnter new Name: \033[0m");
        if (!fgets(addname, sizeof(addname), stdin))
            continue;

        addname[strcspn(addname, "\n")] = '\0';

        if (strlen(addname) == 0)
            valid = 0;

        for (int i = 0; addname[i] && valid; i++)
            if (!isalpha((unsigned char)addname[i]) &&
                    !isspace((unsigned char)addname[i]))
                valid = 0;

        if (!valid)
            printf("\033[1;31mInvalid name.\033[0m \033[1;37mTry again.\033[0m\n");

    }
    while (!valid);


    //  Capitalize first letter of each word
    for (int i = 0; addname[i]; i++)
    {
        if (i == 0 || addname[i-1] == ' ')
            addname[i] = toupper(addname[i]);
        else
            addname[i] = tolower(addname[i]);
    }


    // email
    while (1)
    {
        printf("Enter new Email: ");
        if (!fgets(addemail, sizeof(addemail), stdin))
            continue;

        addemail[strcspn(addemail, "\n")] = '\0';

        if (!emailvalidation(addemail))
        {
            printf("\033[1;31mInvalid email format! Please try again.\033[0m\n");
            continue;
        }
        break;
    }


    // phone number
    do
    {
        valid = 1;
        printf("\033[1;37mEnter new Mobile Number\033[0m \033[1;34m11 digits: \033[0m");
        
        if (!fgets(addmobile, sizeof(addmobile), stdin)){
            // clean_stdin();
            continue;
        }

        addmobile[strcspn(addmobile, "\n")] = '\0';

        if (strlen(addmobile) != 11)
            valid = 0;

        for (int i = 0; addmobile[i] && valid; i++)
            if (!isdigit((unsigned char)addmobile[i]))
                valid = 0;

        if (!valid){
            // clean_stdin();
            printf("\033[1;31mInvalid mobile number.\033[0m \033[1;37mMust be 11 digits\033[0m\n");
        }
    }
    while (!valid);


    // store the new account
    strcpy(acc[accCounter].accountNumber, newaccount);
    strcpy(acc[accCounter].name, addname);
    strcpy(acc[accCounter].email, addemail);
    strcpy(acc[accCounter].mobile, addmobile);
    acc[accCounter].balance = 0.0;
    strcpy(acc[accCounter].status, "active");

    
    // current date & time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    acc[accCounter].open.day = tm.tm_mday;
    acc[accCounter].open.month = tm.tm_mon + 1;
    acc[accCounter].open.year = tm.tm_year + 1900;
    accCounter++;

    printf("\n\033[1;32mAccount added successfully\033[0m\n");
    printf("\033[1;37mCreation date & time:\033[0m %02d/%02d/%04d %02d:%02d:%02d\n",
           tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
           tm.tm_hour, tm.tm_min, tm.tm_sec);

    // clean_stdin();
    confirm_save();
}




// =============================== Delete account =======================================
void delete_account()
{
    int idx = get_account_index();
    if (idx == -1) return;

    if (acc[idx].balance != 0)
    {
        printf("\033[1;31mCannot\033[0m \033[1;37mdelete account. Balance must be zero.\033[0m\n");
        return;
    }

    for (int i = idx; i < accCounter - 1; i++)
    {
        acc[i] = acc[i + 1];
    }

    accCounter--;

    printf("\033[1;32mAccount deleted successfully.\033[0m\n");
    confirm_save();
}


// ===================================== MOdify ===============================
void modify()
{
    char newname[max_input];
    char newmobile[50];
    char newemail[2 * max_input];
    char choice[20];
    int modified=0;

    int found = get_account_index();

    printf("\n\033[1;34mCurrent data:\033[0m\n");
    printf("\033[1;36mName   : \033[0m%s\n", acc[found].name);
    printf("\033[1;36mMobile : \033[0m%s\n", acc[found].mobile);
    printf("\033[1;36mE-mail : \033[0m%s\n\n", acc[found].email);

    while (1)
    {
        printf("\033[1;34m1. Name\n2. Mobile\n3. E-mail\033[0m\n\033[1;36mChoose an option or q to quit: \033[0m");

        if (!fgets(choice, sizeof(choice), stdin)) continue;
        choice[strcspn(choice, "\n")] = '\0';

        if (!strcmp(choice, "q") || !strcmp(choice, "Q"))
        {
            printf("\033[1;31mExiting Modification.\033[0m\n");
            break;
        }

        if (!strcmp(choice, "1"))
        {
            printf("\033[1;36mEnter new Name: \033[0m");
            if (fgets(newname, sizeof(newname), stdin))
            {
                newname[strcspn(newname, "\n")] = '\0';

                for (int i = 0; newname[i]; i++)
                    if (i == 0 || newname[i - 1] == ' ')
                        newname[i] = toupper(newname[i]);
                    else
                        newname[i] = tolower(newname[i]);
                strcpy(acc[found].name, newname);
                modified=1;
                printf("\033[1;32mName updated successfully.\033[0m\n");
            }
        }
        else if (!strcmp(choice, "2"))
        {
            while (1)
            {
                printf("\033[1;36mEnter new Mobile\033[0m (\033[1;34m11 digits): \033[0m");
                if (!fgets(newmobile, sizeof(newmobile), stdin)) continue;
                newmobile[strcspn(newmobile, "\n")] = '\0';

                int valid = strlen(newmobile) == 11;
                for (int i = 0; newmobile[i] && valid; i++)
                    if (!isdigit((unsigned char)newmobile[i])) valid = 0;

                if (!valid)
                {
                    printf("\033[1;31mInvalid mobile number! Must be exactly 11 digits.\033[0m\n");
                    continue;
                }

                strcpy(acc[found].mobile, newmobile);
                   modified=1;
                printf("\033[1;32mMobile number updated successfully.\033[0m\n");
                break;
            }
        }
        else if (!strcmp(choice, "3"))
        {
            while (1)
            {
                printf("\033[1;36mEnter new Email: \033[0m");
                if (!fgets(newemail, sizeof(newemail), stdin)) continue;
                newemail[strcspn(newemail, "\n")] = '\0';

                if (!emailvalidation(newemail))
                {
                    printf("\033[1;31mInvalid email!\033[0m Please enter a valid email (e.g., example@mail.com).\n");
                    continue;
                }

                strcpy(acc[found].email, newemail);
                   modified=1;
                printf("\033[1;32mEmail updated successfully.\033[0m\n");
                break;
            }
        }
        else
        {
            printf("\033[1;31mInvalid choice!\033[0m Please try again.\n");
        }

        printf("\n\033[1;34mUpdated data:\033[0m\n");
        printf("\033[1;36mName   : \033[0m%s\n", acc[found].name);
        printf("\033[1;36mMobile : \033[0m%s\n", acc[found].mobile);
        printf("\033[1;36mE-mail : \033[0m%s\n\n", acc[found].email);
    }
    if(modified)
        confirm_save();
}