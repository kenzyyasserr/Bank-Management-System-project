#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_users 100
#define max_input 50

char usernames[max_users][max_input];
char passwords[max_users][max_input];
int usersCount=0;

void load_users()
{
    FILE *users=fopen("C:\\Users\\Mariam & Mayar\\Desktop\\users.txt", "r");
    if(users==NULL)
    {
        printf("Error could not open users.txt\n");
        exit(1);
    }

    usersCount=0;
    while (fscanf(users,"%49s %49s",usernames[usersCount],passwords[usersCount]) == 2)
    {
        printf("%s %s\n",usernames[usersCount],passwords[usersCount]);
        usersCount++;
    }

    fclose(users);
}
void login()
{
    char username[max_input];
    char password[max_input];
    int i,success=0;

    while (!success)
    {
        printf("Enter username :\n");

        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        printf("Enter password :\n");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        for (i=0;i<usersCount;i++)
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


int main()
{
    load_users();
    login();
    return 0;
}
