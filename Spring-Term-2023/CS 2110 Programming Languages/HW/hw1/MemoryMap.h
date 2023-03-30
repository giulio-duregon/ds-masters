#include <iostream>
#include <stdio.h>
#include <string.h>
#ifndef MEMORYMAP_H
#define MEMORYMAP_H

// Keep track of variables, give them storage
int total_vars_stored = 0;    // total number of vars
char *var_names[1028];        // var names storage
double var_values[1028]; // var values (double)
// extern int strcmp(char *, char *);
// extern char *strdup(char *);

int add_var(char *var_name)
{
    // index variable used to search
    int index;
    for (index = 0; index < total_vars_stored; index++)
    {
        if (strcmp(var_name, var_names[index]) == 0)
        {
            return index;
        }
    }

    // if not in our array, then add it
    var_names[index] = strdup(var_name);

    // Increment total before returning index
    total_vars_stored++;
    return index;
}

/* Set a variables value in the memory store */
double set_var(int index, double val)
{
    var_values[index] = val;
    return val;
}
#endif
