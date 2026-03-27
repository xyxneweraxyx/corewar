/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Generic functions to read big endian bytes
*/

#include "./../../include/op.h"
#include "./endianness.h"

uint16_t char_to_uint16(const char *bytes, size_t start)
{
    uint16_t result = 0;

    read_bytes(bytes, (uint8_t *)&result, sizeof(uint16_t), start);
    return result;
}

uint32_t char_to_uint32(const char *bytes, size_t start)
{
    uint32_t result = 0;

    read_bytes(bytes, (uint8_t *)&result, sizeof(uint32_t), start);
    return result;
}

uint64_t char_to_uint64(const char *bytes, size_t start)
{
    uint64_t result = 0;

    read_bytes(bytes, (uint8_t *)&result, sizeof(uint64_t), start);
    return result;
}