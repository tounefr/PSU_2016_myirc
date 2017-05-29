/*
** error.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myftp
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu May 18 10:27:33 2017 Thomas HENON
** Last update Thu May 18 10:27:34 2017 Thomas HENON
*/

#include <stdlib.h>
#include "myirc.h"

char exit_error(int returnv)
{
    printf("%s\n", strerror(errno));
    return returnv;
}

void malloc_error() {
    fprintf(stderr, "malloc error\n");
    exit(1);
}
