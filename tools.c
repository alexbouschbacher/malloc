/*
** EPITECH PROJECT, 2019
** Malloc
** File description:
** bootstrap
*/

#include "malloc.h"

void i_print(size_t n)
{
    size_t a = 0;
    char c = 0;

    if (n > 9) {
        a = n / 10;
        n -= 10 * a;
        i_print(a);
    }
    c = (char)('0' + n);
    write(1, &c, 1);
}

void write_char(char c)
{
    write(1, &c, 1);
}

char hex_digit(int v)
{
    if (v >= 0 && v < 10)
        return (char)('0' + v);
    else
        return (char)('a' + v - 10);
}

void a_print(void *p0)
{
    int i;
    uintptr_t p = (uintptr_t) p0;

    write_char('0');
    write_char('x');
    for (i = (sizeof(p) << 3) - 4; i >= 0; i -= 4) {
        write_char(hex_digit((int)((p >> i) &0xf)));
    }
}

void show_alloc_mem(void)
{
    write(1, "break: ", 7);
    a_print(sbrk(0));
    write(1, "\n", 1);
    for (memory_t *tmp = myHeap; tmp != NULL; tmp = tmp->next) {
        a_print(tmp->ptr);
        write(1, " - ", 3);
        a_print(tmp->ptr + tmp->size);
        write(1, " : ", 3);
        i_print(tmp->size);
        write(1, " bytes\n", 7);
    }
}
