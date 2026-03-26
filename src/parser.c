/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Parser of argv.
*/

#include "./../include/op.h"

static int confirm_number(const char *number)
{
    if (!number)
        return COREWAR_FAIL;
    for (int i = 0; number[i]; i++) {
        if (number[i] < '0' || number[i] > '9')
            return COREWAR_FAIL;
    }
    return COREWAR_SUCC;
}

static int handle_program_flags(program_t *program, int *i, char **argv)
{
    if (!argv[*i])
        return COREWAR_FAIL;
    if (!str_cmp("-n", argv[*i])) {
        if (!str_cmp("-n", argv[(*i) - 1]) ||
            confirm_number(argv[(*i) + 1]) == COREWAR_FAIL)
            return COREWAR_FAIL;
        program->program_number = atoi(argv[(*i) + 1]);
        (*i) += 2;
        return COREWAR_SUCC;
    }
    if (!str_cmp("-a", argv[*i])) {
        if (!str_cmp("-a", argv[(*i) - 1]) ||
            confirm_number(argv[(*i) + 1]) == COREWAR_FAIL)
            return COREWAR_FAIL;
        program->program_counter = atoi(argv[(*i) + 1]) % (MEM_SIZE);
        (*i) += 2;
        return COREWAR_SUCC;
    }
    return COREWAR_SUCC;
}

static int parse_champion(corewar_t *corewar, int *i, char **argv)
{
    program_t *program = c_alloc(sizeof(program_t), 1, corewar->alloc);
    node_t *node = linkedlist_newnode((void *)program);

    if (!program || !node || !argv[*i])
        return COREWAR_FAIL;
    program->program_number = (size_t)-1;
    program->program_counter = (size_t)-1;
    for (int j = 0; j < 2; j++) {
        printf("gonna handle %s\n", argv[*i]);
        if (handle_program_flags(program, i, argv) == COREWAR_FAIL)
            return COREWAR_FAIL;
    }
    program->program_name = c_alloc(sizeof(char),
        str_len(argv[*i] + 1), corewar->alloc);
    if (!program->program_name)
        return COREWAR_FAIL;
    str_cpy(argv[*i], program->program_name);
    linkedlist_inserthead(corewar->program, node);
    return COREWAR_SUCC;
}

static int handle_dump(corewar_t *corewar, int *i, char *number)
{
    if (!number)
        return COREWAR_FAIL;
    if (confirm_number(number) == COREWAR_FAIL)
        return COREWAR_FAIL;
    corewar->max_cycles = atoi(number);
    if (!corewar->max_cycles)
        return COREWAR_FAIL;
    (*i) += 2;
    return COREWAR_SUCC;
}

static size_t programs_using_number(corewar_t *corewar, size_t number)
{
    program_t *program = NULL;
    size_t total = 0;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        if (program->program_number == number)
            total += 1;
    }
    return total;
}

static program_t *find_next_program(corewar_t *corewar, node_t *start)
{
    node_t *end = (start->next) ? start->next : corewar->program->head;
    program_t *program = NULL;
    bool reached_end = false;

    while (end) {
        if (reached_end)
            return NULL;
        program = (program_t *)end->data;
        if (program->program_counter != (size_t)-1)
            break;
        end = (end->next) ? end->next : corewar->program->head;
        if (end == corewar->program->head)
            reached_end = true;
    }
    return program;
}

static void place_champion(corewar_t *corewar, program_t *program)
{
    program_t *p_cur = NULL;
    program_t *p_next = NULL;
    size_t cur_distance = 0;
    size_t max_distance = 0;
    size_t index_start = 0;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        p_cur = (program_t *)node->data;
        if (p_cur->program_counter == (size_t)-1)
            continue;
        p_next = find_next_program(corewar, node);
        if (!p_next)
            break;
        cur_distance  = (p_next->program_counter - p_cur->program_counter) % (MEM_SIZE);
        if (cur_distance > max_distance) {
            max_distance = cur_distance;
            index_start = p_cur->program_counter;
        }
    }
    program->program_counter = (index_start + max_distance / 2) % (MEM_SIZE);
}

static int set_data(corewar_t *corewar)
{
    program_t *program = NULL;
    size_t number = 1;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        if (program->program_number == (size_t)-1) {
            number = 1;
            for (; programs_using_number(corewar, number) > 0; number++);
            program->program_number = number;
        }
    }
    return COREWAR_SUCC;
}

static int final_confirm(corewar_t *corewar)
{
    program_t *program = NULL;

    for (node_t *node = corewar->program->head; node; node = node->next) {
        program = (program_t *)node->data;
        if (programs_using_number(corewar, program->program_number) > 1)
            return COREWAR_FAIL;
        if (program->program_counter == (size_t)-1)
            place_champion(corewar, program);
        printf("champion : %s %zu %zu\n", program->program_name, program->program_number, program->program_counter);
    }
    // Check later if programs overwriting eachother
    // by starting position is an error.
    return COREWAR_SUCC;
}

int parse(int argc, char **argv, corewar_t *corewar)
{
    int i = 1;

    for (; i < argc; i++) {
        if (!str_cmp("-dump", argv[i]) &&
            handle_dump(corewar, &i, argv[i + 1]) == COREWAR_FAIL)
            return COREWAR_FAIL;
        if (!argv[i])
            break;
        printf("gonna champion %s\n", argv[i]);
        if (parse_champion(corewar, &i, argv) == COREWAR_FAIL)
            return COREWAR_FAIL;
    }
    if (set_data(corewar) == COREWAR_FAIL)
        return COREWAR_FAIL;
    if (final_confirm(corewar) == COREWAR_FAIL)
        return COREWAR_FAIL;
    return COREWAR_SUCC;
}
