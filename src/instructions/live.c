/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Entry point of the project.
*/

#include "./../../include/op.h"

int live_f(program_t *program)
{
    program->since_last_live = 0;
    printf(PLAYER_LIVE, program->program_number, program->program_name);
    return COREWAR_SUCC;
}