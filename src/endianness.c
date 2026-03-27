/*/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Endianness file to read big endian from bytes and return little endian.
*/

#include "./../include/op.h"

/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Generic functions to read big endian bytes
*/

#include "./../include/op.h"

/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Generic functions to read big endian bytes
*/

#include "./../include/op.h"

static int is_little_endian(void)
{
    uint16_t x = 1;

    return (*(uint8_t *)&x == 1);
}

static void read_bytes(const char *bytes, uint8_t *result, size_t size)
{
    if (is_little_endian()) {
        for (size_t i = 0; i < size; i++)
            result[i] = (uint8_t)bytes[size - 1 - i];
        return;
    }
    for (size_t i = 0; i < size; i++)
        result[i] = (uint8_t)bytes[i];
}

uint16_t char_to_uint16(const char *bytes)
{
    uint16_t result = 0;

    read_bytes(bytes, (uint8_t *)&result, sizeof(uint16_t));
    return result;
}

uint32_t char_to_uint32(const char *bytes)
{
    uint32_t result = 0;

    read_bytes(bytes, (uint8_t *)&result, sizeof(uint32_t));
    return result;
}

uint64_t char_to_uint64(const char *bytes)
{
    uint64_t result = 0;

    read_bytes(bytes, (uint8_t *)&result, sizeof(uint64_t));
    return result;
}