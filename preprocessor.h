#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_MACROS 1000
#define MAX_NAME 50
#define MAX_VALUE 200
#define MAX_LINE 1024

typedef struct
{
    char name[MAX_NAME];
    char value[MAX_VALUE];
    int is_function;
    char argument[MAX_NAME];
} Macro;


extern Macro macros[MAX_MACROS];

extern int macro_count;

// Function declarations

void remove_comments(FILE *src, FILE *dest);

void process_includes(FILE *src, FILE *dest);

void process_macros(FILE *src, FILE *dest);

void substitute_macros(char *line);

void substitute_function_macros(char *line);

void generate_output(char *input_file);

#endif
