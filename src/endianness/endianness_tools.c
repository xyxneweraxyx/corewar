/*/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Generic functions to read big endian bytes (Unsigned).
*/

#include "./../include/op.h"
#include "./endianness.h"

static int is_little_endian(void)
{
    uint16_t x = 1;

    return (*(uint8_t *)&x == 1);
}

static void read_bytes(const char *bytes,
    uint8_t *result, size_t size, size_t start)
{
    if (is_little_endian()) {
        for (size_t i = 0; i < size; i++)
            result[i] = (uint8_t)bytes[(start + size - 1 - i) % (MEM_SIZE)];
        return;
    }
    for (size_t i = 0; i < size; i++)
        result[i] = (uint8_t)bytes[(start + i) % (MEM_SIZE)];
}
