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


// ==================== Functions' prototypes ========================
void load_users();
void login();
void quit();
void first_menu();
void load_accounts();
void main_menu();
void clean_stdin();
int digit(const char*s);
int accountexist(const char *newaccount);
void add_account();
void delete_account();
void search_account();
int emailvalidation(const char email[]);
int get_account_index();
void modify();
void advanced_search();
void change_status();
void daily_limit(float *amount, int idx);
void withdraw();
void deposit();
void transfer();
void append_transaction(const char *accNumber, const char *transaction);
void report();
void saveAcc();
void confirm_save();
int compareByName(const void *a, const void *b);
void sortByName(account *acc, int n);
int compareByDate(const void *a, const void *b);
void sortByDate(account arr[], int n);
int compareByBalance(const void *a, const void *b);
void sortByBalance(account arr[], int n);
void printSorted(account arr[], const char *filename);