## Aim
In this code, the main aim is to be able to print the file "accounts.txt" in a sorted way, either by name, date or even by balance.

## Approach
First, the file "accounts.txt"

**Vector of strings:** it's an array of strings, which is a 2D array where each row contains a sequence of characters terminated 
by a '\0' NULL character. It is used to store multiple strings in a single array.

```
char arr[r][m] = {s1, s2, ...., sn};
```
<ins> arr:</ins> array name<br />
<ins> r:</ins> maximum number of strings to be stored in the array<br />
<ins> m:</ins> maximum number of character values that can be stored in each string<br />
<ins> s1, s2, ...., sn:</ins> stored strings<br />

However, this method leads to a wastage of memory since there may be  strings shorter than **m** yet, their place is already reserved, so after some research a more suitable and realistic way was found an *Array of strings using pointers*.

**Array of strings using pointers:** instead of having a 2-Dimensional character array, it's a single-dimensional array of pointers that points to the first character of the string.
```
char *arr[] = { "Array", "Strings", "arrayOfStrings" };
```
<ins> char *:</ins> indicates that each element in the array is a pointer to a character (each points to a string)<br />
<ins> arr[]:</ins> Declares an array of pointers, where the size is determined by the number of strings in the initialisation list.<br />
<ins> = { "Array", "Strings", "arrayOfStrings" }:</ins> Initialises the array, with each pointer pointing to a string: arr[0] points to "Geek", arr[1] to "Geeks", and arr[2] to "Geekfor".<br />
