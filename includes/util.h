//
// Created by toune on 27/05/17.
//

#ifndef PROJETS_UTIL_H
#define PROJETS_UTIL_H

#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

// util.c
char is_number(char *str);
void *my_malloc(size_t size);

#define EXIT_ERROR(returnv, ...) {fprintf(stderr, __VA_ARGS__); return returnv;}

#endif //PROJETS_UTIL_H
