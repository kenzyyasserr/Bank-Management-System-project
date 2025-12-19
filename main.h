#ifndef BANK_H
#define BANK_H

typedef struct
{
    int day;
    int month;
    int year;
}date;

typedef struct
{
    char accountNumber [11];
    char name [100];
    char mobile [12];
    char email [100];
    float balance;
    date open;
}account;

#endif