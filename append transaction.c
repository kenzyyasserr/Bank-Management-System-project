void append_transaction(const char *accNumber, const char *transaction)
{
    char filename[20];
    sprintf(filename, "%s.txt", accNumber);

    FILE *file = fopen(filename, "a");
    if (!file)
    {
        printf("Error opening transaction file for account %s\n", accNumber);
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(file, "%02d/%02d/%04d %02d:%02d:%02d - %s\n",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec,
            transaction);

    fclose(file);
}
