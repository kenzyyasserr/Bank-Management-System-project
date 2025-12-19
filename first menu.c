void first_menu()
{
    char choice[10];
    while(1)
    {
        printf("\n--- MENU ---\n");
        printf("1-LOGIN\n");
        printf("2-QUIT\n");
        printf("Choose an option: ");

        if (!fgets(choice, sizeof(choice), stdin)) continue;
        choice[strcspn(choice, "\n")] = '\0';

        if (!strcmp(choice,"1") || !strcasecmp(choice,"LOGIN"))
        {
            printf("You chose LOGIN.\n");
            login();
            main_menu();
        }
        else if (!strcmp(choice,"2") || !strcasecmp(choice,"QUIT"))
        {
            quit();
        }
    }
}

