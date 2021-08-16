#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include "globals.h"
#include "symbols.h"
#include "data.h"
#include "helpers.h"
#include "firstpass.h"
#include "secondpass.h"
#include "writefiles.h"
#include "check_error.h"



void freeDataStructs(nodeSymbol* head, nodeMachine* ptr, nodeExtern* e_node)
{

    struct nodeSymbol* s_head;
    struct nodeMachine* n_head;
    struct nodeExtern* e_head;

    while (head != NULL)
    {
        s_head = head;
        head = head->next;
        free(s_head);

    }
    while (ptr != NULL)
    {
        n_head = ptr;
        ptr = ptr->next;
        free(n_head);

    }
    while (e_node != NULL)
    {
        e_head = e_node;
        e_node = e_node->next;
        free(e_head);

    }

}


int main(int argc, char* argv[])
{
    int k;


    char* fullFileName = NULL;
    FILE* file;
    char file_name[] = "shimi";
    char c;
    
    
    if (argc <= 1)
    {
        printf("No File where typed.\n");
        exit(0);
    }
    for (k = 1; k < argc; k++)
    {
        fullFileName = NULL;
        fullFileName = argv[k];
        subtract_space(fullFileName,file_name);
        if (fullFileName)
        {
            printf(" -- File: %s -- \n", fullFileName);
            file = fopen(file_name, "r");
            if (file)
            {
            	int DC = 0, IC = 100;

                nodeSymbol* head = NULL;
                nodeMachine* ptr = NULL;
                nodeExtern* e_node = NULL;

                if(main_check(fullFileName))
                {
                    printf(" -- File: %s couldn't be created because there are error to fix in it. --\n", fullFileName);
                    break;

                }
                

                if (firstPass(&head, &ptr, &e_node, &DC, &IC, file)) /*IF ERROR FOUND*/
                {
                    printf(" -- File: %s couldn't be created because there are error to fix in it. --\n", fullFileName);
                    continue;
                }
                else
                {
                    if (secondPass(&head, &ptr, &e_node, file))
                    {

                        printf(" -- File: %s couldn't be created because there are error to fix in it. --\n", fullFileName);
                        continue;
                    }
                    else
                    {
                        writeFiles(&head, &ptr, &e_node, &DC, &IC, fullFileName);
                        printf(" -- File: %s was created successfully. --\n", fullFileName);
                      /* InitializeData(&head, &ptr, &e_node, &DC, &IC);*/
                        freeDataStructs(head, ptr, e_node);
                    }
                }
            }
            else
            {
                printf("Error: The file %s dose not exists.\n", argv[k]);
                continue;

            }
        }



    }
    fclose(file);
    remove(file_name);
    return 0;
}
