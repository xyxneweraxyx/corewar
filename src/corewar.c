/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Entry point of the project.
*/

#include "./../include/op.h"

int return_int(const int return_val, const char *msg, corewar_t *main)
{
    if (msg)
        print_f("%s", msg);
    if (main)
        c_delete(main->alloc, true);
    return return_val;
}

void *return_pointer(void *return_val, const char *msg, corewar_t *main)
{
    if (msg)
        print_f("%s", msg);
    if (main)
        c_delete(main->alloc, true);
    return return_val;
}

static corewar_t *create_corewar(void)
{
    c_alloc_t *alloc = c_ini((uint16_t)100);
    corewar_t *corewar = NULL;
    
    if (!alloc)
        return NULL;
    corewar = c_alloc(sizeof(corewar_t), 1, alloc);
    if (!corewar) {
        c_delete(alloc, false);
        return NULL;
    }
    corewar->program = linkedlist_ini();
    if (!corewar->program) {
        c_delete(alloc, true);
        return NULL;
    }
    corewar->alloc = alloc;
    return corewar;
}

int main(int argc, char **argv)
{
    corewar_t *corewar = NULL;

    if (argc == 2 && !str_cmp("-h", argv[1]))
        return return_int(COREWAR_SUCC, HELP, NULL);
    if (argc < 2)
        return return_int(COREWAR_FAIL, ERR_ARG, NULL);
    corewar = create_corewar();
    if (!corewar)
        return return_int(COREWAR_FAIL, ERR_ALLOC, NULL);
    if (parse(argc, argv, corewar) == COREWAR_FAIL)
        return return_int(COREWAR_FAIL, ERR_PARSE, corewar);
     if (execute(corewar) == COREWAR_FAIL)
        return return_int(COREWAR_FAIL, ERR_EXEC, corewar);
    return return_int(COREWAR_SUCC, NULL, corewar);
}
