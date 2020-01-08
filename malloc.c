/*
** EPITECH PROJECT, 2018
** PSU_2018_malloc
** File description:
** Created by agez
*/

#include "malloc.h"

memory_t *myHeap = NULL;
pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;

void add_node(void *ptr, size_t size)
{
    memory_t *node = (memory_t *) ptr;

    node->ptr = ptr + sizeof(memory_t);
    node->size = size;
    node->isFree = 1;
    node->next = NULL;
    node->prev = NULL;
    if (myHeap == NULL)
        myHeap = node;
    else {
        memory_t *tmp = myHeap;
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = node;
        node->prev = tmp;
    }
}

memory_t *isNodeFree(size_t size)
{
    for (memory_t *tmp = myHeap; tmp != NULL; tmp = tmp->next) {
        if (tmp->isFree == 0 && tmp->size >= size)
            return tmp;
    }
    return NULL;
}

void *malloc(size_t size)
{
    memory_t *node = NULL;
    size_t sizeN = sizeof(memory_t);
    memory_t *freenode = NULL;
    void *a = NULL;
    int e = 0;

    pthread_mutex_lock(&MUTEX);
    if ((node = isNodeFree(size)) != NULL) {
        node->isFree = 1;
        if (node->size >= size + sizeN) {
            malloc_norm(freenode, node, size, sizeN);
        }
        node->size = size;
        pthread_mutex_unlock(&MUTEX);
        return (node->ptr);
    } else
        return(malloc_norm_2(a, e, size, sizeN));
}

void malloc_norm(memory_t *freenode, memory_t *node, size_t size, size_t sizeN)
{
    freenode = (memory_t *)(node->ptr + size);
    freenode->ptr = (node->ptr + size) + sizeof(memory_t);
    freenode->size = node->size - size - sizeN;
    freenode->isFree = 0;
    freenode->next = node->next;
    freenode->prev = node;
    node->next->prev = freenode;
    node->next = freenode;
}

void *malloc_norm_2(void *a, int e, size_t size, size_t sizeN)
{
    a = sbrk(0);
    e = (int)brk(a + size + sizeN);
    if (e != -1) {
        add_node(a, size);
        pthread_mutex_unlock(&MUTEX);
        return (a + sizeN);
    }
    pthread_mutex_unlock(&MUTEX);
    return NULL;
}