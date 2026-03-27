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

static void fill_functions(instr_func_t functions[INSTR_AMT])
{
    functions[INSTR_LIVE - 1] = NULL;
    functions[INSTR_LD - 1] = NULL;
    functions[INSTR_ST - 1] = NULL;
    functions[INSTR_ADD - 1] = NULL;
    functions[INSTR_SUB- 1] = NULL;
    functions[INSTR_AND - 1] = NULL;
    functions[INSTR_OR - 1] = NULL;
    functions[INSTR_XOR - 1] = NULL;
    functions[INSTR_ZJMP - 1] = NULL;
    functions[INSTR_LDI - 1] = NULL;
    functions[INSTR_STI - 1] = NULL;
    functions[INSTR_FORK - 1] = NULL;
    functions[INSTR_LLD - 1] = NULL;
    functions[INSTR_LLDI - 1] = NULL;
    functions[INSTR_LFORK - 1] = NULL;
    functions[INSTR_PRINT - 1] = NULL;
}

static void kill_program(corewar_t *corewar, program_t *program)
{
    program_t *pg = NULL;
    node_t *node = corewar->program->head;

    for (; node; node = node->next) {
        pg = (program_t *)node->data;
        if (pg->program_number != program->program_number)
            continue;
        break;
    }
    c_free(program->program_name, corewar->alloc);
    c_free(program, corewar->alloc);
    linkedlist_remove(corewar->program, node, false);
}

static int cycle_live(corewar_t *corewar)
{
    size_t cycles = corewar->per_live - corewar->since_last_live;
    program_t *program = NULL;

    corewar->since_last_live = 0;
    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        if (program->since_last_live > corewar->per_live) {
            kill_program(corewar, program);
            continue;
        }
        program->until_next_instr -= cycles;
        program->since_last_live = 0;
        corewar->live_signals += 1;
    }
    corewar->per_live = CYCLE_TO_DIE - ((corewar->live_signals / NBR_LIVE) * CYCLE_DELTA);
    return COREWAR_SUCC;
}

static int main_loop(corewar_t *corewar, instr_func_t functions[INSTR_AMT])
{
    program_t *program = NULL;
    program_t *earliest_prog = NULL;
    size_t earliest = (size_t)-1;
    int result = 0;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        if (program->until_next_instr < earliest &&
            (!earliest_prog ||
                program->program_number < earliest_prog->program_number)) {
            earliest = program->until_next_instr;
            earliest_prog = program;
        }
    }
    if (earliest < (corewar->per_live - corewar->since_last_live))
        result = functions[corewar->memory[earliest_prog->program_counter] - 1](corewar, earliest_prog);
    else
        result = cycle_live(corewar);
    return result;
}

int execute(corewar_t *corewar)
{
    instr_func_t functions[INSTR_AMT] = {0};
    int result = 0;

    corewar->per_live = CYCLE_TO_DIE;
    fill_functions(functions);
    while (1) {
        result = main_loop(corewar, functions);
        if (result == COREWAR_INTERNAL)
            break;
        if (result == COREWAR_FAIL)
            return COREWAR_FAIL;
    }
    return COREWAR_SUCC;
}