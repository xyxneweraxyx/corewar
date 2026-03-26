/*
** EPITECH PROJECT, 2025
** parsing
** File description:
** Private functions used for str_to_array.
*/

#ifndef STR_TO_ARRAY_H
    #define STR_TO_ARRAY_H

    // Includes
    #include <stdbool.h>
    #include "./../c_alloc/c_alloc.h" // MUST INCLUDE
    #include "./../str/str.h" // MUST INCLUDE

// Type definitions

typedef struct parse_state_s {
    const char *str;
    const char **sep;
    bool skip_empty;
    int cur;
} parse_state_t;

// Private functions

int match_sep(const char *str, const char **seps);
void skip_seps(parse_state_t *ps);
void skip_one_word(parse_state_t *ps);

#endif
