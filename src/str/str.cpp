#include "str.h"

char *trim(char *str, char c)
{
    int i = 0;

    while (*(str) == c) str++;

    while (*(str + i) != '\0') i++;
    while (*(str + i - 1) == c) i--;

    *(str + i) = '\0';

    return str;
}