## Aim
In this code, the main aim is to be able to print the file "accounts.txt" in a sorted way, either by name, date or even by balance.

## Approach
First, the file "accounts.txt"

**Vector of strings:** it's an array of strings which is a 2D array where each row contains a sequence of characters terminated 
by a '\0' NULL character. It is used to store multiple strings in a single array.
```   char arr[3][20] = {"array", "strings",
                       "arrayOfStrings"};
  
    for (int i = 0; i < 3; i++)
        printf("%s\n", arr[i]);
    return 0;```
