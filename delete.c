void delete_account()
{
    int idx = get_account_index();
    if (idx == -1) return;

    if (acc[idx].balance != 0)
    {
        printf("Cannot delete account. Balance must be zero.\n");
        return;
    }

    for (int i = idx; i < accCounter - 1; i++)
    {
        acc[i] = acc[i + 1];
    }

    accCounter--;

    printf("Account deleted successfully.\n");
    confirm_save();
}
