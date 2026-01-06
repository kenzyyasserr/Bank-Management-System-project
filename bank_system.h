#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define max_users 100
#define max_input 50
#define MAX_KEYWORD 100
#define MAX_BUFFER 500

// =========================== Structures ========================
typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    char accountNumber [11];
    char name [100];
    char mobile [12];
    char email [100];
    float balance;
    date open;
    char status[20];
} account;

extern account acc[500];
extern char usernames[max_users][max_input];
extern char passwords[max_users][max_input];
extern int usersCount;
extern int accCounter;
