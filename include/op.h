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

    /// Library includes
    #include "./../libs/c_alloc/c_alloc.h"
    #include "./../libs/linkedlist/linkedlist.h"
    #include "./../libs/parsing/parsing.h"
    #include "./../libs/str/str.h"

    // Defines

    /// Return codes
    #define ROBOT_SUCC 0
    #define ROBOT_FAIL 84
    #define ROBOT_INTERNAL -1

    /// Global error messages
    #define ERR_ARG "Wrong amount of arguments! -h for help.\n"
    #define ERR_ALLOC "The initialization of the alloc failed.\n"
    #define ERR_MAIN "The allocation of the main structure failed.\n"

    /// Stack error messages
    #define STK_ENCODE "Encoding the file."
    #define STK_INI "Initializing the main."
    #define STK_HDR "Parsing the header."
    #define STK_INSTR "Parsing the instructions."

    #define STK_NAMEWRITTEN "Ensuring name is unique."
    #define STK_NAMEVALID "Ensuring name line validity"
    #define STK_CMDWRITTEN "Ensuring command is unique."
    #define STK_CMDVALID "Ensuring command line validity."
    #define STK_HDRFOUND "Ensuring header data was found."

    #define STK_WRITEBEGIN "Writing the final data in the file."
    #define STK_WRITEOPEN "Opening the final file."
    #define STK_WRITEHDR "Writing the file's header."
    #define STK_WRITEINSTR "Writing the file's instructions."

    #define STK_INSTRFOUND "Ensuring instruction data was found."
    #define STK_INSTRLABEL "Handling potential labels."
    #define STK_INSTRSKIP "Skipping potential labels to find instruction."
    #define STK_INSTRPARSE "Parsing single instruction."
    #define STK_INSTRSKIP2 "Skipping potential spaces before instruction."
    #define STK_INSTRVALID "Ensuring instruction exists and creating new node."
    #define STK_INSTRARG "Parsing the arguments of the instruction."

    #define STK_ARGSINGLE "Handling a single argument."
    #define STK_ARGTYPE "Ensuring the fetched argument is of correct type."
    #define STK_ARGCOUNT "Ensuring arg count is coherent."
    #define STK_ARGVALID "Ensuring argument is valid."
    #define STK_ARGIND "Handling register and indirect arguments."
    #define STK_ARGDIR "Handling a direct argument."
    #define STK_ARGDIR2 "Handling a direct normal argument."
    #define STK_ARGLAB "Handling a label argument"

    #define STK_DIR

    /// Help message
    #define HELP1 "USAGE\n"
    #define HELP2 "./robot-factory file_name[.s]\n"
    #define HELP3 "DESCRIPTION\n"
    #define HELP4 "file_name file in assembly language to be converted into "
    #define HELP5 "file_name.cor, an executable in the Virtual Machine.\n"
    #define HELP HELP1 HELP2 HELP3 HELP4 HELP5

    /// Hardcoded values
    #define MEM_SIZE 6 * 1024
    #define IDX_MOD 512
    #define MAX_ARGS_NUMBER 4

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
    uint16_t cycles_since_live;
    size_t program_number;
    size_t program_counter;
    char registers[REG_NUMBER][REG_SIZE_INSIDE];
    bool carry;
} program_t;

typedef struct program_start_s {
    size_t program_number;
    size_t program_load;
    char *program_name;
} program_start_t;

typedef struct start_data_s {
    uint32_t nbr_cycle;
    linkedlist_t *program; // linkedlist of program_start_t
} start_data_t;

typedef struct main_s {
    c_alloc_t *alloc;
    linkedlist_t *program; // linkedlist of program_t
    char memory[MEM_SIZE];
    uint16_t CURRENT_CYCLE;
} main_t;

// Imports
extern const op_t op_tab[];

// Functions
int return_int(const int return_val, const char *msg, main_t *main);
void *return_pointer(void *return_val, const char *msg, main_t *main);
int parse(int argc, char **argv, main_t *main);

#endif
