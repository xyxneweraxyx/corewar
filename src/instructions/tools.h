/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Entry point of the project.
*/

#ifndef INSTR_TOOLS_H
    #define INSTR_TOOLS_H

    #include "./../../include/op.h"
#include "./tools.h"

// Typedefs

typedef struct args_place_s {
    size_t args[4];
} args_place_t;

// Functions

args_place_t args_place_in_memory(corewar_t *corewar, program_t *program);
program_t *program_from_number(corewar_t *corewar, size_t number);
program_t *program_from_name(corewar_t *corewar, const char *name);

#endif