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
    functions[INSTR_LIVE - 1] = &live_f;
    functions[INSTR_LD - 1] = &ld_f;
    functions[INSTR_ST - 1] = &st_f;
    functions[INSTR_ADD - 1] = &add_f;
    functions[INSTR_SUB- 1] = &sub_f;
    functions[INSTR_AND - 1] = &and_f;
    functions[INSTR_OR - 1] = &or_f;
    functions[INSTR_XOR - 1] = &xor_f;
    functions[INSTR_ZJMP - 1] = &zjmp_f;
    functions[INSTR_LDI - 1] = &ldi_f;
    functions[INSTR_STI - 1] = &sti_f;
    functions[INSTR_FORK - 1] = &fork_f;
    functions[INSTR_LLD - 1] = &lld_f;
    functions[INSTR_LLDI - 1] = &lldi_f;
    functions[INSTR_LFORK - 1] = &lfork_f;
    functions[INSTR_PRINT - 1] = &print_f;
}

static void kill_program(corewar_t *corewar,
    program_t *program, node_t **loop_node)
{
    program_t *pg = NULL;
    node_t *node = corewar->program->head;

    for (; node; node = node->next) {
        pg = (program_t *)node->data;
        if (pg->program_number != program->program_number)
            continue;
        break;
    }
    corewar->programs_alive -= 1;
    (*loop_node) = (*loop_node)->next;
    c_free(program->program_name, corewar->alloc);
    c_free(program, corewar->alloc);
    linkedlist_remove(corewar->program, node, false);
}

static int cycle_live(corewar_t *corewar)
{
    program_t *program = NULL;

    for (node_t *node = corewar->program->head; node;) {
        program = (program_t *)node->data;
        if (corewar->programs_alive == 1) {
            printf(PLAYER_WIN, program->program_number, program->program_name);
            return COREWAR_INTERNAL;
        }
        if (program->since_last_live >= corewar->per_live) {
            kill_program(corewar, program, &node);
            continue;
        }
        corewar->live_signals += 1;
        node = node->next;
    }
    corewar->per_live = CYCLE_TO_DIE - ((corewar->live_signals / NBR_LIVE) * CYCLE_DELTA);
    corewar->since_last_live = 0;
    return COREWAR_SUCC;
}

static int exec_program_instr(corewar_t *corewar,
    instr_func_t functions[INSTR_AMT], program_t *earliest_prog)
{
    uint8_t code = 0;

    code = corewar->memory[earliest_prog->program_counter] - 1;
    return functions[code](corewar, earliest_prog);
}

static void update_global_cycles(corewar_t *corewar, int earliest)
{
    program_t *program = NULL;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        program->until_next_instr -= (uint16_t)earliest;
        program->since_last_live += (uint16_t)earliest;
    }
    corewar->cycles += (uint32_t)earliest;
    corewar->since_last_live += (uint16_t)earliest;
}

static int exec_earliest_action(corewar_t *corewar, int earliest,
    instr_func_t functions[INSTR_AMT], program_t *earliest_prog)
{
    bool signal_live = false;

    if (corewar->programs_alive == 1) {
        printf(PLAYER_WIN, earliest_prog->program_number, earliest_prog->program_name);
        return COREWAR_INTERNAL;
    }
    if (corewar->per_live - corewar->since_last_live < earliest) {
        earliest = (corewar->per_live - corewar->since_last_live);
        signal_live = true;
    }
    if (corewar->max_cycles - corewar->cycles < (uint32_t)earliest) {
        dump(corewar);
        return COREWAR_INTERNAL;
    }
    update_global_cycles(corewar, earliest);
    return (!signal_live) ? exec_program_instr(corewar,
        functions, earliest_prog) : cycle_live(corewar);
}

static int main_loop(corewar_t *corewar, instr_func_t functions[INSTR_AMT])
{
    program_t *program = NULL;
    program_t *earliest_prog = NULL;
    size_t earliest = (size_t)-1;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        if (program->until_next_instr < earliest &&
            (!earliest_prog ||
                program->program_number < earliest_prog->program_number)) {
            earliest = program->until_next_instr;
            earliest_prog = program;
        }
    }
    return exec_earliest_action(corewar, earliest, functions, earliest_prog);
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