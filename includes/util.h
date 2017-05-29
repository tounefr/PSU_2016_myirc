/*
** util.h for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:04:07 2017 Thomas HENON
** Last update Sun May 28 00:04:08 2017 Thomas HENON
*/

#ifndef PROJETS_UTIL_H
#define PROJETS_UTIL_H

#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

// error.c
char exit_error(int returnv);
void malloc_error();

// util.c
char is_number(char *str);
void *my_malloc(size_t size);
int nbr_chars_in_str(char *str, char c);
char  *my_strdup(char *str);

#define EXIT_ERROR(returnv, ...) {fprintf(stderr, __VA_ARGS__); return returnv;}

#endif //PROJETS_UTIL_H
