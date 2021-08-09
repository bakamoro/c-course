#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"




void addMachineNode(nodeMachine** ptr_head, int memValue, char* machineCode)
{
    struct nodeMachine* ptr;

    if (*ptr_head == NULL)
    {
        *ptr_head = (nodeMachine*)malloc(sizeof(nodeMachine));
        if (*ptr_head == NULL)
        {
            printf("Unable to allocate memory.");

        }
        else
        {
            (*ptr_head)->address = memValue;
            strcpy((*ptr_head)->code, machineCode);
            (*ptr_head)->next = NULL;
        }

    }
    else
    {
        nodeMachine* temp1 = (nodeMachine*)malloc(sizeof(nodeMachine));
        if (temp1 == NULL)
        {
            printf("Unable to allocate memory.");

        }
        else
        {
            temp1->address = memValue;

            strcpy(temp1->code, machineCode);
            temp1->next = NULL;

            ptr = *ptr_head;

            while (ptr != NULL && ptr->next != NULL)
            {
                ptr = ptr->next;


            }

            ptr->next = temp1;
        }
    }
}

int checkIfMissing(nodeMachine** ptr, int Address)
{

    struct nodeMachine* head = *ptr;

    if (ptr == NULL)
        return 0;


    while (head != NULL)
    {
        if (head->address == Address)
        {
            if (head->code[31] == '1' || head->code[31] == '0')
            {

                return 1;

            }

        }
        head = head->next;

    }

    return 0;

}

char* getString(nodeMachine** ptr, int Address)
{
    struct nodeMachine* head = *ptr;


    if ((head) == NULL)
    {

        printf("ERROR");
    }

    else
    {

        while (head != NULL)
        {
            if (head->address == Address)
            {

                return head->code;

            }
            head = head->next;

        }

    }

    return 0;
}

void InitMachCode(char mach[])
{
    int i = 0;

    for (i; i < 32; i++)
    {
        mach[i] = '\0';

    }
}