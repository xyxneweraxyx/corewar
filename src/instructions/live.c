/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Entry point of the project.
*/

#include "./../../include/op.h"
#include "./tools.h"

int live_f(corewar_t *corewar, program_t *program)
{
    args_place_t args = args_place_in_memory(corewar, program);
    printf(PLAYER_LIVE, program->program_number, program->program_name);
    return COREWAR_SUCC;
}