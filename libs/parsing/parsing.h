/*
** EPITECH PROJECT, 2025
** parsing
** File description:
** A simple library with parsing functions.
*/

#ifndef PARSING_H
    #define PARSING_H

    // Includes
    #include <stdbool.h>
    #include "./../c_alloc/c_alloc.h" // MUST INCLUDE

    // Return codes
    #define CHAR_IN_STR_NO -1
    #define CHAR_IN_STR_ERR -2

// Functions

/*
Separates a string str based on an array of string separators "sep".
If "skip_empty" is false, will create empty strings when successive seps found.
Handles the allocations automatically given a c_alloc struct.

Returns the array of separated strings, or NULL.
*/
char **str_to_array(const char *str, const char **sep,
    bool skip_empty, c_alloc_t *alloc);

/*
Finds a character in a given string.

On success, returns the position of the matching character in the string.
If not found, returns CHAR_IN_STR_NO
On error, returns CHAR_IN_STR_ERR.
*/
int char_in_str(const char c, const char *restrict str);

#endif
