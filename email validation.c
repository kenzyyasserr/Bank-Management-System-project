int emailvalidation(const char email[])
{
    int at_count = 0;
    int len = strlen(email);

    if (len < 5) return 0;

    for (int i = 0; i < len; i++)
    {
        if (email[i] == '@') at_count++;
        if (email[i] == ' ' || email[i] == '\\') return 0;
    }

    if (at_count != 1) return 0;

    const char *at_pos = strchr(email, '@');
    if (at_pos == email || *(at_pos+1) == '\0') return 0;
    if (*(at_pos+1) == '.') return 0;

    if (email[0]=='.' || email[len-1]=='.') return 0;

    for (int i = 0; i < len-1; i++)
        if (email[i]=='.' && email[i+1]=='.') return 0;

    if (!strchr(at_pos, '.')) return 0;

    return 1;
}

