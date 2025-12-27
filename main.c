#include "bank_system.h"

void clear()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#elif __MACH__
    system("clear");
#else

#endif
}

int main()
{
    load_users();
    load_accounts();
    first_menu();

    return 0;
}