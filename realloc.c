/*
** EPITECH PROJECT, 2018
** PSU_2018_malloc
** File description:
** Created by agez
*/

#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
    void *new = NULL;
    if (ptr == NULL)
        return (malloc(size));
    for (memory_t *tmp = myHeap; tmp != NULL; tmp = tmp->next) {
        if (tmp->ptr == ptr && tmp->isFree == 1) {
            free(ptr);
            new = malloc(size);
            for (size_t i = 0; i < tmp->size; i++) {
                ((char *)new)[i] = ((char *)(tmp->ptr))[i];
            }
            return new;
        }
    }
    write(2, "Bad realloc\n", 12);
    exit(84);
}