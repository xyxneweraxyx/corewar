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
    int32_t player_id = char_to_int32((char *)corewar->memory, args.args[0]);
    program_t *target = program_from_number(corewar, (size_t)player_id);

    if (target)
        printf(PLAYER_LIVE, target->program_number, target->program_name);
    else
        printf(PLAYER_LIVE, (size_t)player_id, "");
    program->since_last_live = 0;
    corewar->live_signals += 1;
    program->program_counter =
        (program->program_counter + args.instr_size) % MEM_SIZE;
    return COREWAR_SUCC;
}