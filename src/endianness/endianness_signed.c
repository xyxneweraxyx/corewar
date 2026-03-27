/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Generic functions to read big endian bytes
*/

#include "./../../include/op.h"
#include "./endianness.h"

int16_t char_to_int16(const char *bytes, size_t start)
{
    int16_t result = 0;

    read_bytes(bytes, (uint8_t *)&result, sizeof(int16_t), start);
    return result;
}

int32_t char_to_int32(const char *bytes, size_t start)
{
    int32_t result = 0;

    read_bytes(bytes, (uint8_t *)&result, sizeof(int32_t), start);
    return result;
}

int64_t char_to_int64(const char *bytes, size_t start)
{
    int64_t result = 0;

    read_bytes(bytes, (uint8_t *)&result, sizeof(int64_t), start);
    return result;
}
