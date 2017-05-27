
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

char is_number(char *str)
{
    if (strlen(str) == 0)
        return 0;
    while (*str) {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

void        *my_malloc(size_t size)
{
    void    *ptr;

    if (!(ptr = calloc(1, size))) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    return ptr;
}