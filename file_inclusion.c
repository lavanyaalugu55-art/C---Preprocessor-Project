#include "preprocessor.h"


FILE *open_header(char *filename, int system_header)
{
    FILE *fp;
    char path[512];

    const char *directories[] =
    {
        "/usr/include",
        "/usr/include/x86_64-linux-gnu",
        "/usr/local/include",
        "/usr/lib/gcc/x86_64-linux-gnu/13/include",
        "/usr/lib/gcc/x86_64-linux-gnu/14/include"
    };

    int i;

    if(system_header == 0)
        return fopen(filename, "r");

    for(i = 0; i < 5; i++)
    {
        snprintf(path, sizeof(path), "%s/%s",
                 directories[i], filename);

        fp = fopen(path, "r");

        if(fp != NULL)
            return fp;
    }

    return NULL;
}
void process_includes(FILE *src, FILE *dest)
{
    char line[MAX_LINE];

    while(fgets(line, MAX_LINE, src) != NULL)
    {
        char *start, *end;
        char filename[MAX_NAME];
        int length;
        int ch;
        int system_header = 0;
        FILE *fp;

        start = line;

        // Skip spaces and tabs
        while(*start == ' ' || *start == '\t')
            start++;

        // Check #include
        if(strncmp(start, "#include", 8) != 0)
        {
            fputs(line, dest);
            continue;
        }

        start += 8;

        while(*start == ' ' || *start == '\t')
            start++;

        // System header
        if(*start == '<')
        {
            system_header = 1;
            end = strchr(start + 1, '>');
        }

        // User-defined header
        else if(*start == '"')
        {
            end = strchr(start + 1, '"');
        }

        else
        {
            fputs(line, dest);
            continue;
        }

        if(end == NULL)
        {
            printf("Invalid include directive\n");
            fputs(line, dest);
            continue;
        }

        length = end - start - 1;

        if(length <= 0 || length >= MAX_NAME)
        {
            printf("Invalid header filename\n");
            fputs(line, dest);
            continue;
        }

        strncpy(filename, start + 1, length);
        filename[length] = '\0';

        // Open header file
        fp = open_header(filename, system_header);

        if(fp == NULL)
        {
            printf("Unable to open header file: %s\n", filename);
            fputs(line, dest);
            continue;
        }

        printf("Header included: %s\n", filename);

        // Copy header contents
        while((ch = fgetc(fp)) != EOF)
        {
            fputc(ch, dest);
        }

        fclose(fp);
    }
}
