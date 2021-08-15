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
#include "writefiles.h"



void addSymbolNode(nodeSymbol** p_head, char* name, int memValue, char* attribute)
{
	int i;
    if ((p_head == NULL) || (name == NULL))
    {
        return;
    }


    if (*p_head == NULL)
    {
        *p_head = (nodeSymbol*)malloc(sizeof(nodeSymbol));

        if (*p_head == NULL)
        {
            printf("Unable to Allocate Memory");

        }
        else
        {
            (*p_head)->next = NULL;

        }
    }
    else
    {
        nodeSymbol* temp = (nodeSymbol*)malloc(sizeof(nodeSymbol));
        if (temp == NULL)
        {
            printf("Unable to Allocate Memory");

        }
        else
        {
            temp->next = *p_head;
            *p_head = temp;

        }
    }
    strcpy((*p_head)->name, name);
    (*p_head)->memValue = memValue;
    for (i = 0; i < 2; i++)
    {
        memset(&(*p_head)->attributes[i], 0, 7);
    }

    if (!strcmp(attribute, "entry") || (!strcmp(attribute, "extern"))) /*if external or entry put in the second place*/
    {
        strcpy((*p_head)->attributes[1], attribute);
    }
    else {
        strcpy((*p_head)->attributes[0], attribute);
    }
}
int searchSymbol(nodeSymbol** p_head, char* name)
{
    struct nodeSymbol* ptr = (*p_head);

    if (ptr == NULL)
        return 0;


    while (ptr != NULL)
    {
        if (!strcmp(ptr->name, name))
        {
            return 1;

        }
        ptr = ptr->next;
    }

    return 0;
}

int returnAddress(nodeSymbol** p_head, char* name)
{
	struct nodeSymbol* ptr = (*p_head);

    if ((p_head == NULL) || (name == NULL))
    {
        return 0;
    }


    if ((*p_head) == NULL)
        return 0;

    while (ptr != NULL)
    {
        if (!strcmp(ptr->name, name))
        {
            return ptr->memValue;

        }
        ptr = ptr->next;


    }

    return 0;

}

void addAttribute(nodeSymbol** p_head, char* name, char* attribute)
{

    struct nodeSymbol* ptr = (*p_head);

    if (ptr == NULL)
    {

        printf("ERROR");
    }


    while (ptr != NULL)
    {
        if (!strcmp(ptr->name, name))
        {
            strcpy(ptr->attributes[1], attribute);

        }
        ptr = ptr->next;
    }



}
