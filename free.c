/*
** EPITECH PROJECT, 2018
** PSU_2018_malloc
** File description:
** Created by agez
*/

#include "malloc.h"

void free(void *obj)
{
    pthread_mutex_lock(&MUTEX);
    for (memory_t *tmp = myHeap; tmp != NULL; tmp = tmp->next) {
        if (tmp->ptr == obj && tmp->isFree == 1) {
            tmp->isFree = 0;
            if (tmp->next == NULL) {
                free_norm(tmp);
            } else if (tmp->next->isFree == 0) {
                tmp->size += sizeof(memory_t) + tmp->next->size;
                tmp->next = tmp->next->next;
            } else if (tmp->prev != NULL && tmp->prev->isFree == 0) {
                tmp->prev->size += sizeof(memory_t) + tmp->size;
                tmp->prev->next = tmp->next;
            }
            pthread_mutex_unlock(&MUTEX);
            return;
        }
    }
    pthread_mutex_unlock(&MUTEX);
    write(2, "Invalid free or double free\n", 28);
    exit(84);
}

void free_norm(memory_t *tmp)
{
    if (tmp->prev != NULL) {
        tmp->prev->next = NULL;
    } else {
        myHeap = NULL;
    }
    brk(tmp);
}