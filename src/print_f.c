/*
** EPITECH PROJECT, 2025
** mini_printf
** File description:
** A simpler version of printf.
*/

#include "./../include/op.h"

static int put_char(const char c)
{
    return write(1, &c, 1);
}

static int put_str(const char *str)
{
    int counter = 0;

    for (counter = 0; str[counter] != 0; counter++) {
        write(1, &str[counter], 1);
    }
    return counter;
}

static int put_nbr(int nbr)
{
    int counter = 0;
    char nb;

    if (nbr == -2147483648) {
        write(1, "-2", 2);
        counter += 2;
        nbr = 147483648;
    }
    if (nbr < 0) {
        write(1, "-", 1);
        counter++;
        nbr *= -1;
    }
    nb = nbr % 10 + '0';
    if (nbr > 9)
        counter += put_nbr(nbr / 10);
    write(1, &nb, 1);
    counter++;
    return counter;
}

int print_arg(const char *format, va_list args)
{
    switch (*format) {
        case 'd':
        case 'i':
            return put_nbr(va_arg(args, int));
        case 's':
            return put_str(va_arg(args, char *));
        case 'c':
            return put_char(va_arg(args, int));
        case '%':
            return write(1, "%", 1);
        default:
            write(2, "Incorrect flag used", 18);
            return -1;
    }
    return -1;
}

int print_normal_char(const char *format, int *counter)
{
    int total = 0;

    if (*format == '%')
        return total;
    total += write(1, format, 1);
    if (total)
        (*counter)++;
    return total;
}

int print_f(const char *format, ...)
{
    int counter = 0;
    int result = 0;
    va_list args;

    va_start(args, format);
    while (*format) {
        if (print_normal_char(format, &counter)) {
            format++;
            continue;
        }
        format++;
        result = print_arg(format, args);
        if (result < 0)
            return -1;
        counter += result;
        format++;
    }
    return counter;
}
