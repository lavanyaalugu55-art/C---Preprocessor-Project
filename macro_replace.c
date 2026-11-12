#include "preprocessor.h"

Macro macros[MAX_MACROS];
int macro_count = 0;

void substitute_macros(char *line)
{
    char result[MAX_LINE * 2];
    char word[MAX_NAME];

    int i = 0, j, k;
    int pos = 0;
    int found;

    while(line[i] != '\0')
    {
        /* Preserve string literals */
        if(line[i] == '"')
        {
            result[pos++] = line[i++];

            while(line[i] != '\0')
            {
                result[pos++] = line[i];

                if(line[i] == '\\' && line[i + 1] != '\0')
                {
                    i++;
                    result[pos++] = line[i];
                }
                else if(line[i] == '"')
                {
                    i++;
                    break;
                }

                i++;
            }
        }

        /* Preserve character literals */
        else if(line[i] == '\'')
        {
            result[pos++] = line[i++];

            while(line[i] != '\0')
            {
                result[pos++] = line[i];

                if(line[i] == '\\' && line[i + 1] != '\0')
                {
                    i++;
                    result[pos++] = line[i];
                }
                else if(line[i] == '\'')
                {
                    i++;
                    break;
                }

                i++;
            }
        }

        /* Identify normal identifiers */
        else if(isalpha((unsigned char)line[i]) || line[i] == '_')
        {
            j = 0;

            while(isalnum((unsigned char)line[i]) || line[i] == '_')
            {
                if(j < MAX_NAME - 1)
                    word[j++] = line[i];

                i++;
            }

            word[j] = '\0';
            found = 0;

            for(k = 0; k < macro_count; k++)
            {
                if(strcmp(word, macros[k].name) == 0 &&
                   macros[k].is_function == 0)
                {
                    pos += snprintf(result + pos,
                                    sizeof(result) - pos,
                                    "%s", macros[k].value);

                    found = 1;
                    break;
                }
            }

            if(!found)
            {
                pos += snprintf(result + pos,
                                sizeof(result) - pos,
                                "%s", word);
            }
        }
        else
        {
            result[pos++] = line[i++];
        }

        if(pos >= sizeof(result) - 2)
            break;
    }

    result[pos] = '\0';

    strcpy(line, result);
}


void process_macros(FILE *src, FILE *dest)
{
    char line[MAX_LINE];
    char name[MAX_NAME];
    char argument[MAX_NAME];
    char *start, *p, *end;

    macro_count = 0;

    while(fgets(line, MAX_LINE, src) != NULL)
    {
        start = line;

        while(*start == ' ' || *start == '\t')
            start++;

        if(strncmp(start, "#define", 7) == 0 && (start[7] == ' ' || start[7] == '\t'))
        {
            p = start + 7;

            while(*p == ' ' || *p == '\t')
                p++;

            end = p;

            while(isalnum((unsigned char)*end) || *end == '_')
                end++;

            if(end == p)
                continue;

            if(end - p >= MAX_NAME)
                continue;

            strncpy(name, p, end - p);
            name[end - p] = '\0';

            if(*end == '(')
            {
                p = end + 1;
                end = strchr(p, ')');

                if(end == NULL)
                    continue;

                if(end - p >= MAX_NAME)
                    continue;

                strncpy(argument, p, end - p);
                argument[end - p] = '\0';

                p = end + 1;

                while(*p == ' ' || *p == '\t')
                    p++;
                
                if(strlen(p) >= MAX_VALUE)
                      continue;

                if(macro_count < MAX_MACROS)
                {
                    strcpy(macros[macro_count].name, name);
                    strcpy(macros[macro_count].argument, argument);
                    strcpy(macros[macro_count].value, p);

                    macros[macro_count].value[
                        strcspn(macros[macro_count].value, "\r\n")
                    ] = '\0';

                    macros[macro_count].is_function = 1;
                    macro_count++;

                    printf("Function macro stored: %s\n", name);
                }
            }
            else
            {
                p = end;

                while(*p == ' ' || *p == '\t')
                    p++;
		if(strlen(p) >= MAX_VALUE)
    			continue;
                if(macro_count < MAX_MACROS)
                {
                    strcpy(macros[macro_count].name, name);
                    strcpy(macros[macro_count].value, p);

                    /* Remove newline from object-like macro value */
                    macros[macro_count].value[
                        strcspn(macros[macro_count].value, "\r\n")
                    ] = '\0';

                    macros[macro_count].is_function = 0;
                    macro_count++;

                    printf("Object macro stored: %s\n", name);
                }
            }
        }
        else
        {
            substitute_macros(line);
            substitute_function_macros(line);
            fputs(line, dest);
        }
    }
}
