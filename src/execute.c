/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Entry point of the project.
*/

#include "./../include/op.h"

static void dump(corewar_t *corewar)
{
    for (int i = 0; i < (MEM_SIZE); i++) {
        if (i % 32 == 0 && i)
            printf("\n");
        printf("%02X", corewar->memory[i]);
    }
    printf("\n");
}

int execute(corewar_t *corewar)
{
    dump(corewar);
    return COREWAR_SUCC;
}