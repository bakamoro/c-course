#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <limits.h>
#include "globals.h"
#include "symbols.h"
#include "data.h"
#include "helpers.h"
#include "firstpass.h"
#include "secondpass.h"





void InitTempString(char temp[])
{
    int i = 0;

    for (; i < 9; i++)
    {
        temp[i] = '\0';

    }
}

void InitializeData(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC)
{
    int i, k, z, t;
    /*Initiallzing Symbols Table*/
    struct nodeSymbol* s_head = (*head);
    struct nodeMachine* n_head = (*ptr);
    struct nodeExtern* e_head = (*e_node);

    while (s_head != NULL)
    {
        for (i = 0; i < 31; i++)
        {
            s_head->name[i] = '\0';


        }
        s_head->memValue = '\0';

        for (k = 0; k < 3; k++)
        {

            strcpy((s_head)->attributes[k], "");
        }


        s_head = s_head->next;

    }

    /*Initialzing Code Table*/
    while (n_head != NULL)
    {
        n_head->address = '\0';
        
        for (z = 0; z < 33; z++)
        {
            n_head->code[z] = '\0';
        }


        n_head = n_head->next;

       }

    /*Initialzing Externs Table*/

    while (e_head != NULL)
    {
        e_head->memValue = '\0';

        for (t = 0; t < 31; t++)
        {
            e_head->name[t] = '\0';

        }


        e_head = e_head->next;

    }

    *DC = 0;
    *IC = 0;


}


void writeFiles(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC, char* filename)
{
    FILE* machine;
    FILE* entFile;
    FILE* extFile;

    char* str;
    char* tempString;
    char* inputFileName = filename;
    char* fullFileName;
    char entSuffix[] = ".ent";
    char extSuffix[] = ".ext";
    
    int codeSize, begFrom, countRow = 0, ICF = *IC - 100, DCF = *DC , countLines=100;
    int i, j;
    size_t strLen;

    struct nodeMachine* m_head = *ptr;
    struct nodeSymbol* s_head = *head;
    struct nodeExtern* e_head = *e_node;


    char* offset = strstr(filename, ".");
    size_t inputFileNameLen = (offset) ? (offset - inputFileName) : (strlen(inputFileName));
    char obSuffix[] = ".ob";

    fullFileName = (char*)calloc(inputFileNameLen + strlen(obSuffix) + 1, 1);
    if (fullFileName == NULL)
    {
        printf("Unable to allocate memory");
        exit(0);

    }
    else
    {
        strncpy(fullFileName, inputFileName, inputFileNameLen);
        fullFileName = strcat(fullFileName, obSuffix);
    }
    machine = fopen(fullFileName, "w");



    fprintf(machine, "     %d %d\n", ICF, DCF); /*Print the ICF AND IDCF first */

    tempString = (char*)malloc(9);
    if (tempString == NULL)
    {

        printf("Unable to allocate memory");

    }
    else
    {

        fprintf(machine, "%04d ", countLines); /* print the address */

        while (m_head != NULL)
        {

            if (countRow == 4) /*if there were 4 prints print next address*/
            {
                fprintf(machine, "%04d ", countLines);

                countRow = 0;
            }
            codeSize = strlen(m_head->code);
            begFrom = codeSize - 8;/*where to print from*/
            InitTempString(tempString);
            for (i = 0; i < codeSize / 8; i++)
            {

                strncat(tempString, &m_head->code[begFrom], 8);/*get the last 8 binary numbers as a string*/

                str = convertToHex(tempString);
                strLen = strlen(str);
                for (j = 0; j < strLen; ++j)/*convert the strings to Uppercase*/
                {
                    str[j] = toupper(str[j]);
                }

                fprintf(machine, "%s ", str);
                begFrom = begFrom - 8;
                InitTempString(tempString);
                countRow++;
                if (countRow == 4)
                {
                    fprintf(machine, "%s", "\n");
                    countLines = countLines + 4;
                        fprintf(machine, "%04d ", countLines);
                        countRow = 0;
                   }


            }

            m_head = m_head->next;

        }
    }
    fclose(machine);
    free(fullFileName);



    fullFileName = (char*)calloc(inputFileNameLen + strlen(entSuffix) + 1, 1);
    if (fullFileName == NULL)
    {
        printf("Unable to allocate memory");
        exit(0);
    }
    else
    {
        strncpy(fullFileName, inputFileName, inputFileNameLen);
        fullFileName = strcat(fullFileName, entSuffix);
    }


    entFile = fopen(fullFileName, "w");


    while (s_head != NULL)
    {
        if (!strcmp(s_head->attributes[1], "entry"))
        {
            fprintf(entFile, "%s %04d\n", s_head->name, s_head->memValue);

        }

        s_head = s_head->next;

    }
    fclose(entFile);
    free(fullFileName);

    
    

    fullFileName = (char*)calloc(inputFileNameLen + strlen(extSuffix) + 1, 1);
    if (fullFileName == NULL)
    {
        printf("Unable to allocate memory");
        exit(0);
    }
    else
    {
        strncpy(fullFileName, inputFileName, inputFileNameLen);
        fullFileName = strcat(fullFileName, extSuffix);
    }

    extFile = fopen(fullFileName, "w");


    while (e_head != NULL)
    {

        fprintf(extFile, "%s %04d\n", e_head->name, e_head->memValue);


        e_head = e_head->next;

    }
    fclose(extFile);
    free(fullFileName);
}
