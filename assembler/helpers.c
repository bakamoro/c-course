#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <limits.h>



char* convertToHex(char* binaryString)
{
    int value;
    char* hexString;

    hexString = (char*)malloc(12);
    if (hexString == NULL)
    {
        printf("Unable to Allocate Memory");
        exit(0);

    }
    else
    {
        value = (int)strtol(binaryString, NULL, 2);

        sprintf(hexString, "%02x", value);

        return(hexString);
    }
}


char* decimal_to_binary(int n, int k) /*Convert n to k bits binary number*/
{
    int c, d, t;
    char* p;

    t = 0;
    p = (char*)malloc(k);
    if (p == NULL)
        exit(EXIT_FAILURE);

    for (c = k - 1; c >= 0; c--)
    {
        d = n >> c;

        if (d & 1)
            *(p + t) = 1 + '0';
        else
            *(p + t) = 0 + '0';

        t++;
    }
    *(p + t) = '\0';

    return  p;
}