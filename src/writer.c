/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** File checker and writer to ensure compliance with robot factory guidelines.
*/

#include "./../include/op.h"

static uint32_t validate_file_header(FILE *file, char header[HEADER_LENGTH])
{
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

static int set_champion_name(corewar_t *corewar, program_t *program,
    char header[HEADER_LENGTH])
{
    char *name = c_alloc(sizeof(char), PROG_NAME_LENGTH + 1, corewar->alloc);

    if (!name)
        return COREWAR_FAIL;
    for (int i = 0; i < PROG_NAME_LENGTH && header[4 + i]; i++)
        name[i] = header[4 + i];
    c_free(program->program_name, corewar->alloc);
    program->program_name = name;
    return COREWAR_SUCC;
}

static int write_file_data(FILE *file, corewar_t *corewar,
    program_t *program, uint32_t prog_size)
{
    size_t pos = program->program_counter;
    size_t space_left = (MEM_SIZE) - pos;

    if (prog_size <= space_left) {
        fread(corewar->memory + pos, 1, prog_size, file);
        return COREWAR_SUCC;
    }
    fread(corewar->memory + pos, 1, space_left, file);
    fread(corewar->memory, 1, prog_size - space_left, file);
    return COREWAR_SUCC;
}

static int write_champion(corewar_t *corewar, program_t *program)
{
    char header[HEADER_LENGTH];
    uint8_t opcode = 0;
    uint32_t prog_size = 0;
    FILE *file = fopen(program->program_name, "rb");

    if (!file)
        return COREWAR_FAIL;
    prog_size = validate_file_header(file, header);
    if (prog_size == (uint32_t)-1 ||
        set_champion_name(corewar, program, header) == COREWAR_FAIL ||
        write_file_data(file, corewar, program, prog_size) == COREWAR_FAIL) {
        fclose(file);
        return COREWAR_FAIL;
    }
    opcode = corewar->memory[program->program_counter];
    program->until_next_instr = (opcode >= 1 && opcode <= INSTR_AMT)
        ? (uint16_t)op_tab[opcode].nbr_cycles : 1;
    fclose(file);
    return COREWAR_SUCC;
}

int writer(corewar_t *corewar)
{
    program_t *program = NULL;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        if (write_champion(corewar, program) == COREWAR_FAIL)
            return COREWAR_FAIL;
    }
    return COREWAR_SUCC;
}