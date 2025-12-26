#include "bank_system.h"

// load file
void load_users()
{
    FILE *users=fopen("users.txt", "r");
    if(users==NULL)
    {
        printf("\033[1;31mError could not open users.txt\033[0m\n");  //printed in red
        exit(1);
    }

    usersCount=0;
    while (fscanf(users,"%49s %49s",usernames[usersCount],passwords[usersCount]) == 2)
    {
        usersCount++;
    }

    fclose(users);
}

// function
void login()
{
    char username[max_input];
    char password[max_input];
    int i,success=0;

    while (!success)
    {
        printf("\033[1;34mEnter username : \033[0m");  //blue



        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        printf("\033[1;34mEnter password : \033[0m");  //blue
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        for (i=0; i<usersCount; i++)
        {
            if (strcmp(username,usernames[i])==0 && strcmp(password, passwords[i])==0)
            {
                success=1;
                break;
            }
        }

        if(success)
            printf("\033[1;32mLogin successful! Welcome %s.\033[0m\n",username);  //green

        else
            printf("\033[1;31mInvalid username or password. Try again.\033[0m\n");  //red
    }
}