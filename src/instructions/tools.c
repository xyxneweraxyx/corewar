/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Entry point of the project.
*/

#include "./../../include/op.h"
#include "./tools.h"
#include "./tools.h"

static size_t get_arg_size(char coding_byte, size_t arg)
{
    if (arg == 0)
        return (size_t)((coding_byte >> 24));
    if (arg == 1)
        return (size_t)((coding_byte >> 16) & 0xff);
    if (arg == 2)
        return (size_t)((coding_byte >> 8) & 0xff);
    if (arg == 3)
        return (size_t)((coding_byte) & 0xff);
    return (size_t)-1;
}

args_place_t args_place_in_memory(corewar_t *corewar, program_t *program)
{
    args_place_t place = {(size_t)-1, (size_t)-1, (size_t)-1, (size_t)-1};
    size_t pos = program->program_counter;
    size_t coding_byte = 0;
    size_t arg_size = 0;
    uint8_t code = corewar->memory[pos] + 1;

    if (op_tab[code].has_coding_byte)
        pos += 2;
    else {
        place.args[0] = pos + 1;
        return place;
    }
    coding_byte = pos - 1;
    for (int i = 0; i < op_tab[code].nbr_args; i++) {
        arg_size = get_arg_size(coding_byte, i);
        printf("prog = %s argsize = %zu\n", program->program_name, arg_size);
        place.args[i] = pos + arg_size;
        pos += arg_size;
    }
    return place;
}

program_t *program_from_number(corewar_t *corewar, size_t number)
{
    program_t *program = NULL;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        if (program->program_number == number)
            return program;
    }
    return NULL;
}

program_t *program_from_name(corewar_t *corewar, const char *name)
{
    program_t *program = NULL;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        if (!str_cmp(name, program->program_name))
            return program;
    }
    return NULL;
}

