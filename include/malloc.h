/*
** EPITECH PROJECT, 2018
** PSU_2018_malloc
** File description:
** Created by agez
*/

#ifndef PSU_2018_MALLOC_MALLOC_H
# define PSU_2018_MALLOC_MALLOC_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <dlfcn.h>
# include <pthread.h>
# include <stdint.h>

typedef struct memory_s {
    void *ptr;
    size_t size;
    char isFree;
    struct memory_s *next;
    struct memory_s *prev;
} memory_t;

extern memory_t *myHeap;
extern pthread_mutex_t MUTEX;
memory_t *isNodeFree(size_t size);
void free_norm(memory_t *tmp);
void malloc_norm(memory_t *freenode, memory_t *node, size_t size, size_t sizeN);
void *malloc_norm_2(void *a, int e, size_t size, size_t sizeN);
void i_print(size_t n);
void write_char(char c);
char hex_digit(int v);
void a_print(void *p0);
void show_alloc_mem(void);
void *realloc(void *ptr, size_t size);
void *malloc(size_t size);
void free(void *obj);
void add_node(void *ptr, size_t size);

#endif /* PSU_2018_MALLOC_MALLOC_H */
