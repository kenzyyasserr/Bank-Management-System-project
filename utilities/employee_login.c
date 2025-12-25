#include "bank_system.h"

// load file
void load_users()
{
    FILE *users=fopen("users.txt", "r");
    if(users==NULL)
    {
        printf("Error could not open users.txt\n");
        exit(1);
    }

    usersCount=0;
    while (fscanf(users,"%49s %49s",usernames[usersCount],passwords[usersCount]) == 2)
    {
        // printf("%s %s\n",usernames[usersCount],passwords[usersCount]);
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
        printf("Enter username : ");



        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        printf("Enter password : ");
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
            printf("Login successful! Welcome %s.\n",username);

        else
            printf("Invalid username or password. Try again.\n");
    }
}