/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** File checker and writer to ensure compliance with robot factory guidelines.
*/

#include "./../include/op.h"

static uint32_t validate_file_header(FILE *file)
{
    char header[HEADER_LENGTH];
    uint32_t number = 0;

    if (fread(header, 1, HEADER_LENGTH, file) != HEADER_LENGTH)
        return (uint32_t)COREWAR_INTERNAL;
    number = char_to_uint32(header, 0);
    if (number != COREWAR_EXEC_MAGIC)
        return (uint32_t)COREWAR_INTERNAL;
    number = char_to_uint32(header, PROG_NAME_LENGTH + 8);
    if (!number || number > (uint32_t)(MEM_SIZE))
        return (uint32_t)COREWAR_INTERNAL;
    return number;
}

static int write_file_data(FILE *file, corewar_t *corewar, program_t *program)
{
    return COREWAR_SUCC;
}

int writer(corewar_t *corewar)
{
    FILE *file = NULL;
    program_t *program = NULL;
    uint32_t prog_size = 0;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        file = fopen(program->program_name, "rb");
        if (!file)
            return COREWAR_FAIL;
        prog_size = validate_file_header(file);
        if (prog_size == (uint32_t)-1 ||
            write_file_data(file, corewar, program) == COREWAR_FAIL) {
            fclose(file);
            return COREWAR_FAIL;
        }
        fclose(file);
    }
    return COREWAR_SUCC;
}