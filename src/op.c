/*
** EPITECH PROJECT, 2025
** asm
** File description:
** The main instructions
*/

#include "./../include/op.h"

const op_t op_tab[] = {
    {0, 0, {0}, 0, 0, 0},
    {"live", 1, {T_DIR}, 10, 0, 0},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 5, 0, 1},
    {"st", 2, {T_REG, T_REG | T_IND}, 5, 0, 1},
    {"add", 3, {T_REG, T_REG, T_REG}, 10, 0, 1},
    {"sub", 3, {T_REG, T_REG, T_REG}, 10, 0, 1},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 6, 0, 1},
    {"or", 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 6, 0, 1},
    {"xor", 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 6, 0, 1},
    {"zjmp", 1, {T_DIR}, 20, 1, 0},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 25, 1, 1},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR }, 25, 1, 1},
    {"fork", 1, {T_DIR}, 800, 1, 0},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 10, 0, 1},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 50, 1, 1},
    {"lfork", 1, {T_DIR}, 1000, 0, 0},
    {"print", 1, {T_REG}, 2, 0, 1},
    {0, 0, {0}, 0, 0, 0}
};
