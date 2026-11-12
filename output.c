#include "preprocessor.h"

void generate_output(char *input_file)
{
    FILE *src, *temp1, *temp2, *dest;
    char output_file[256];
    char *ext;

    src = fopen(input_file, "r");

    if(src == NULL)
    {
        printf("Unable to open input file\n");
        return;
    }

    strcpy(output_file, input_file);

    ext = strrchr(output_file, '.');

    if(ext != NULL)
        strcpy(ext, ".i");
    else
        strcat(output_file, ".i");

    temp1 = tmpfile();
    temp2 = tmpfile();

    if(temp1 == NULL || temp2 == NULL)
    {
        printf("Unable to create temporary files\n");
        fclose(src);

        if(temp1 != NULL)
            fclose(temp1);

        if(temp2 != NULL)
            fclose(temp2);

        return;
    }

    dest = fopen(output_file, "w");

    if(dest == NULL)
    {
        printf("Unable to create output file\n");
        fclose(src);
        fclose(temp1);
        fclose(temp2);
        return;
    }

    remove_comments(src, temp1);

    rewind(temp1);

    process_includes(temp1, temp2);

    rewind(temp2);

    process_macros(temp2, dest);

    printf("Preprocessing completed successfully\n");
    printf("Output file: %s\n", output_file);

    fclose(src);
    fclose(temp1);
    fclose(temp2);
    fclose(dest);
}
