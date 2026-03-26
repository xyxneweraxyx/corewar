/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Parser of argv.
*/

#include "./../include/op.h"

int parse(int argc, char **argv, corewar_t *corewar)
{
    int i = 1;

    for (; i < argc; i++) {
        if (!str_cmp("-dump", argv[i]));
            // ...
    }
    return COREWAR_FAIL;
}
