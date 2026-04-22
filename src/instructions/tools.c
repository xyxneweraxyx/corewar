/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Entry point of the project.
*/

#include "./../../include/op.h"
#include "./tools.h"

static size_t get_arg_size(uint8_t coding_byte, size_t arg, bool is_index)
{
    uint8_t type = (coding_byte >> (6 - arg * 2)) & 0x3;

    if (type == 1)
        return (size_t)REG_SIZE;
    if (type == 2)
        return is_index ? (size_t)IND_SIZE : (size_t)DIR_SIZE;
    if (type == 3)
        return (size_t)IND_SIZE;
    return 0;
}

static args_place_t fill_with_coding_byte(args_place_t place,
    size_t pos, uint8_t coding_byte, uint8_t code)
{
    size_t arg_size = 0;

    for (int i = 0; i < op_tab[code].nbr_args; i++) {
        arg_size = get_arg_size(coding_byte, (size_t)i, op_tab[code].is_index);
        place.types[i] = (coding_byte >> (6 - i * 2)) & 0x3;
        place.sizes[i] = arg_size;
        place.args[i] = pos;
        pos += arg_size;
    }
    return place;
}

args_place_t args_place_in_memory(corewar_t *corewar, program_t *program)
{
    args_place_t place = {0};
    size_t pos = program->program_counter;
    uint8_t coding_byte = 0;
    uint8_t code = corewar->memory[pos];

    if (!op_tab[code].has_coding_byte) {
        place.types[0] = 2;
        place.sizes[0] = op_tab[code].is_index
            ? (size_t)IND_SIZE : (size_t)DIR_SIZE;
        place.args[0] = pos + 1;
        place.instr_size = 1 + place.sizes[0];
        return place;
    }
    coding_byte = corewar->memory[pos + 1];
    place = fill_with_coding_byte(place, pos + 2, coding_byte, code);
    place.instr_size = place.args[op_tab[code].nbr_args - 1]
        + place.sizes[op_tab[code].nbr_args - 1]
        - program->program_counter;
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