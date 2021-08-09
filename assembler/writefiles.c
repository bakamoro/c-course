#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <limits.h>
#include "symbols.h"
#include "data.h"
#include "helpers.h"
#include "firstpass.h"
#include "secondpass.h"

void InitTempString(char temp[])
{
    int i;

    for (i=0; i < 8; i++)
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

    char* tempString;
    char* inputFileName;
    char* fullFileName;
    int codeSize, begFrom, countRow = 0, ICF = *IC - 100, DCF = *DC , countLines=100;
    int i;

    struct nodeMachine* m_head = *ptr;
    struct nodeSymbol* s_head = *head;
    struct nodeExtern* e_head = *e_node;


    inputFileName = strtok(filename, ".");

    fullFileName = (char*)malloc(strlen(inputFileName));
    if (fullFileName == NULL)
    {
        printf("Unable to allocate memory");
        exit(0);

    }
    else
    {
        strcpy(fullFileName, inputFileName);


        fullFileName = strcat(fullFileName, ".ob");
    }
    machine = fopen(fullFileName, "w");



    fprintf(machine, "     %d %d\n", ICF, DCF);

    tempString = (char*)malloc(9);
    if (tempString == NULL)
    {

        printf("Unable to allocate memory");

    }
    else
    {

        fprintf(machine, "%04d ", countLines);

        while (m_head != NULL)
        {

            if (countRow == 4)
            {
                fprintf(machine, "%04d ", countLines);

                countRow = 0;
            }
            codeSize = strlen(m_head->code);
            begFrom = codeSize - 8;
            InitTempString(tempString);
            for (i = 0; i < codeSize / 8; i++)
            {

                strncat(tempString, &m_head->code[begFrom], 8);
                fprintf(machine, "%s ", convertToHex(tempString));
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
        fclose(machine);

    }


    fullFileName = (char*)malloc(strlen(inputFileName));
    if (fullFileName == NULL)
    {
        printf("Unable to allocate memory");
        exit(0);

    }
    else
    {
        strcpy(fullFileName, inputFileName);


        fullFileName = strcat(fullFileName, ".ent");
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
    fullFileName = (char*)malloc(strlen(inputFileName));
    if (fullFileName == NULL)
    {
        printf("Unable to allocate memory");
        exit(0);

    }
    else
    {
        strcpy(fullFileName, inputFileName);

        fullFileName = strcat(fullFileName, ".ext");
    }

    extFile = fopen(fullFileName, "w");


    while (e_head != NULL)
    {

        fprintf(extFile, "%s %04d\n", e_head->name, e_head->memValue);


        e_head = e_head->next;

    }
    fclose(extFile);






}





