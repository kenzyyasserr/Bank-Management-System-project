int search(char account_numberin[])
{
    int i;
    for (i = 0; i < accCounter; i++)
    {
        if (!strcmp(acc[i].accountNumber, account_numberin))
        {
            return i;   // index
        }
    }
    return -1;
}
