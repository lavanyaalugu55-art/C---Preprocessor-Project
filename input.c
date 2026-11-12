#include <stdio.h>
#include "myheader.h"

// Main function
/*
   This is a
   multi-line comment
*/

#define LENGTH 10
#define MESSAGE "Preprocessor Project"

int main()
{
    float area = PI * SQUARE(5);
    int square = SQUARE(LENGTH);

    printf("PI and SQUARE(5)\n");
    printf("%s\n", MESSAGE);

    char ch = 'S';

    // Display results
    printf("Area = %f\n", area);
    printf("Square = %d\n", square);
    printf("Character = %c\n", ch);

    return 0;
}
