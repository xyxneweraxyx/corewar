/*/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** File checker and writer to ensure compliance with robot factory guidelines.
*/

#include "./../include/op.h"

static int validate_file_header(FILE *file)
{

    return COREWAR_SUCC;
}

static int write_file_data(FILE *file, corewar_t *corewar, program_t *program)
{
    return COREWAR_SUCC;
}

int writer(corewar_t *corewar)
{
    FILE *file = NULL;
    program_t *program = NULL;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        file = fopen(program->program_name, "rb");
        if (!file)
            return COREWAR_FAIL;
        if (validate_file_header(file) == COREWAR_FAIL ||
            write_file_data(file, corewar, program) == COREWAR_FAIL) {
            fclose(file);
            return COREWAR_FAIL;
        }
        fclose(file);
    }
    return COREWAR_SUCC;
}