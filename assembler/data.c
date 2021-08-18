#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"




void addMachineNode(nodeMachine** ptr_head, int memValue, char* machineCode,char type)
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
			(*ptr_head)->type = type;
		}

	}

	else
	{

		nodeMachine* temp1 = (nodeMachine*)calloc(1,sizeof(nodeMachine));
		int insertFlag=1;

		if (temp1 == NULL)
		{
			printf("Unable to allocate memory.");

		}
		else
		{

			if((*ptr_head)->type == 'D' && type == 'I')
			{
				/*Insert node to the head*/

				temp1->address = memValue;

				strcpy(temp1->code, machineCode);

				temp1->next = (*ptr_head);
				temp1->type = type;
				(*ptr_head) = temp1;
				insertFlag=0;


			}
			else if((*ptr_head)->type == 'I' && type == 'I')
			{
				/*Search Until you find D type node*/
				ptr = (*ptr_head);

				while(ptr!=NULL)
				{
					if(ptr->next == NULL) /* If there is no D type node*/
					{
						break;/*Add to the end of the list*/

					}
					else if(ptr->next->type != 'D')
					{
					ptr = ptr->next;

					}
					else
					{
						temp1->address = memValue;
						strcpy(temp1->code, machineCode);
						temp1->next = ptr->next;
						temp1->type = type;
						ptr->next = temp1;
						insertFlag=0;
						break;

					}

				}



			}
			if(insertFlag == 1) /*insert to the end of the  list*/
			{

				temp1->address = memValue;

				strcpy(temp1->code, machineCode);
				temp1->next = NULL;
				temp1->type = type;

				ptr = *ptr_head;

				while (ptr != NULL && ptr->next != NULL)
				{
					ptr = ptr->next;


				}

				ptr->next = temp1;
			}

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
	int i;

	for (i=0; i < 32; i++)
	{
		mach[i] = '\0';

	}
}
