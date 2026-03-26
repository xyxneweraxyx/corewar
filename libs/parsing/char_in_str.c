/*
** EPITECH PROJECT, 2025
** char_in_str
** File description:
** Attempts to find a character in a given string.
*/

#include "./parsing.h"

int char_in_str(const char c, const char *restrict str)
{
    int i = 0;

    if (!c || !str || !str[0])
        return CHAR_IN_STR_ERR;
    for (; str[i]; i++) {
        if (str[i] == c)
            break;
    }
    return (str[i]) ? i : CHAR_IN_STR_NO;
}
