void clean_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
/* ===== ACCOUNTS ===== */


/* check digits only */
int digit(const char *s)
{
    if (*s == '\0') return 0;
    for (int i = 0; s[i]; i++)
        if (!isdigit((unsigned char)s[i]))
            return 0;
    return 1;
}

/* check duplicate */
int accountexist(const char *newaccount)
{
    for (int i = 0; i < accCounter; i++)
        if (strcmp(newaccount, acc[i].accountNumber) == 0)
            return 1;
    return 0;
}
