/*
** EPITECH PROJECT, 2025
** asm
** File description:
** Header for the operations
*/

#ifndef OP_H_
    #define OP_H_

    // Includes

    /// Standard includes
    #include <stdio.h>
    #include <sys/stat.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <stdarg.h>

    /// Library includes
    #include "./../libs/c_alloc/c_alloc.h"
    #include "./../libs/linkedlist/linkedlist.h"
    #include "./../libs/parsing/parsing.h"
    #include "./../libs/str/str.h"

    // Defines

    /// Return codes
    #define COREWAR_SUCC 0
    #define COREWAR_FAIL 84

    /// Global error messages
    #define ERR_ARG "Wrong amount of arguments! -h for help.\n"
    #define ERR_ALLOC "The initialization failed.\n"
    #define ERR_PARSE "The parsing of the arguments failed.\n"
    #define ERR_EXEC "The execution of the corewar failed.\n"
    #define ERR_WRITER "The writer found a file that does not conform.\n"

    /// Help message
    #define HELP1 "USAGE\n"
    #define HELP2_1 "./corewar [-dump nbr_cycle] [[-n prog_number] "
    #define HELP2_2 "[-a load_address] prog_name] ...\n"
    #define HELP3 "DESCRIPTION\n"
    #define HELP4_1 "-dump nbr_cycle dumps the memory after the nbr_cycle "
    #define HELP4_2 "execution (if the round isn't already over) with the "
    #define HELP4_3 "following format: 32 bytes/line "
    #define HELP4_4 "in hexadecimal (A0BCDEFE1DD3...)\n"
    #define HELP5_1 "-n prog_number sets the next program's number. By "
    #define HELP5_2 "default, the first free number in the parameter order\n"
    #define HELP6_1 "-a load_address sets the next program's loading address. "
    #define HELP6_2 "When no address is specified, optimize the addresses so "
    #define HELP6_3 "that the processes are as far away from each other as "
    #define HELP6_4 "possible. The addresses are MEM_SIZE modulo.\n"
    #define HELP2 HELP2_1 HELP2_2
    #define HELP4 HELP4_1 HELP4_2 HELP4_3 HELP4_4
    #define HELP5 HELP5_1 HELP5_2
    #define HELP6 HELP6_1 HELP6_2 HELP6_3 HELP6_4
    #define HELP HELP1 HELP2 HELP3 HELP4 HELP5

    /// Hardcoded values
    #define MEM_SIZE 6 * 1024
    #define IDX_MOD 512
    #define MAX_ARGS_NUMBER 4
    #define COREWAR_EXEC_MAGIC 0xea83f3

    #define CYCLE_TO_DIE 1536
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40

    #define REG_NUMBER 16
    #define REG_SIZE_INSIDE DIR_SIZE

    /// Argument type bitmasking
    #define T_REG 1
    #define T_DIR 2
    #define T_IND 4
    #define T_LAB 8

    /// Byte size of arguments
    #define REG_SIZE 1
    #define IND_SIZE 2
    #define DIR_SIZE 4

// Typedefs

typedef enum instr_e {
    INSTR_LIVE = 1,
    INSTR_LD,
    INSTR_ST,
    INSTR_ADD,
    INSTR_SUB,
    INSTR_AND,
    INSTR_OR,
    INSTR_XOR,
    INSTR_ZJMP,
    INSTR_LDI,
    INSTR_STI,
    INSTR_FORK,
    INSTR_LLD,
    INSTR_LLDI,
    INSTR_LFORK,
    INSTR_PRINT,
} instr_t;

typedef struct core_reg_s {
    char c[REG_SIZE_INSIDE];
    size_t num;
} core_reg_t;

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    char type[MAX_ARGS_NUMBER];
    int nbr_cycles;
    bool is_index;
    bool has_coding_byte;
} op_t;

typedef struct program_s {
    char *program_name;
    uint16_t since_last_live;
    size_t program_number;
    size_t program_counter;
    core_reg_t registers[REG_NUMBER];
    bool carry;
} program_t;

typedef struct corewar_s {
    c_alloc_t *alloc;
    linkedlist_t *program; // linkedlist of program_t
    char memory[MEM_SIZE];
    uint32_t cycles;
    uint32_t max_cycles;
    uint16_t since_last_live;
} corewar_t;

// Imports
extern const op_t op_tab[];

// Functions

/// Main functions
int parse(int argc, char **argv, corewar_t *main);
int execute(corewar_t *corewar);
int writer(corewar_t *corewar);

/// Endianness & reading functions
uint16_t char_to_uint16(const char *bytes);
uint32_t char_to_uint32(const char *bytes);
uint64_t char_to_uint64(const char *bytes);

#endif
