//
// Created by toune on 26/05/17.
//

#ifndef PROJETS_UTIL_H
#define PROJETS_UTIL_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>

#define EXIT_ERROR(returnv, ...) {fprintf(stderr, __VA_ARGS__); return returnv;}

char is_number(char *str);
void *my_malloc(size_t size);

#endif //PROJETS_UTIL_H
