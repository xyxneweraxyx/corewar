/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Private header for endianness functions.
*/

#ifndef ENDIANNESS_H
    #define ENDIANNESS_H

    // Includes
    #include <stdlib.h>
    #include <stdint.h>

// Functions
static int is_little_endian(void);
static void read_bytes(const char *bytes,
    uint8_t *result, size_t size, size_t start);

#endif