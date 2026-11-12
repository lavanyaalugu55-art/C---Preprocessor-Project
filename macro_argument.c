#include "preprocessor.h"

void substitute_function_macros(char *line)
{
    char result[MAX_LINE * 2];
    char word[MAX_NAME];
    char argument[MAX_VALUE];

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

        /* Identify an identifier */
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

            /* Search for a function-like macro */
            for(k = 0; k < macro_count; k++)
            {
                if(strcmp(word, macros[k].name) == 0 &&
                   macros[k].is_function == 1)
                {
                    found = 1;
                    break;
                }
            }

            if(found)
            {   
                int temp = i;
                while(line[temp] == ' ' || line[temp] == '\t')
                    temp++;

                if(line[temp] == '(')
                {
                    i=temp + 1;
                    j = 0;

                    while(line[i] != ')' && line[i] != '\0')
                    {
                        if(j < MAX_VALUE - 1)
                            argument[j++] = line[i];

                        i++;
                    }

                    argument[j] = '\0';

                    if(line[i] == ')')
                        i++;

                    {
                        char expanded[MAX_VALUE * 2];
                        char *p;
                        int n = 0;

                        p = macros[k].value;

                        while(*p != '\0' &&
                              n < sizeof(expanded) - 1)
                        {
                            if(isalpha((unsigned char)*p) || *p == '_')
                            {
                                char param[MAX_NAME];
                                int m = 0;

                                while(isalnum((unsigned char)*p) || *p == '_')
                                {
                                    if(m < MAX_NAME - 1)
                                        param[m++] = *p;

                                    p++;
                                }

                                param[m] = '\0';

                                if(strcmp(param, macros[k].argument) == 0)
                                {
                                    n += snprintf(expanded + n,
                                                  sizeof(expanded) - n,
                                                  "%s", argument);
                                }
                                else
                                {
                                    n += snprintf(expanded + n,
                                                  sizeof(expanded) - n,
                                                  "%s", param);
                                }
                            }
                            else
                            {
                                expanded[n++] = *p++;
                            }
                        }

                        expanded[n] = '\0';

                        pos += snprintf(result + pos,
                                        sizeof(result) - pos,
                                        "%s", expanded);
                    }
                }
                else
                {
                    pos += snprintf(result + pos,
                                    sizeof(result) - pos,
                                    "%s", word);
                }
            }
            else
            {
                pos += snprintf(result + pos,
                                sizeof(result) - pos,
                                "%s", word);
            }
        }
        else
        {
            if(pos < sizeof(result) - 1)
                result[pos++] = line[i];

            i++;
        }

        if(pos >= sizeof(result) - 2)
            break;
    }

    result[pos] = '\0';

    strcpy(line, result);
}
