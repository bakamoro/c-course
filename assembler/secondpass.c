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
#include "utils.h"



void addNodeExtern(nodeExtern** p_head, char* name, int memValue)
{
	struct nodeExtern* ptr;

	if (*p_head == NULL)
	{
		*p_head = (nodeExtern*)malloc(sizeof(nodeExtern));
		if (*p_head == NULL)
		{
			printf("Unable to allocate memory.");

		}
		else
		{
			(*p_head)->memValue = memValue;
			strcpy((*p_head)->name, name);
			(*p_head)->next = NULL;
		}

	}
	else
	{
		nodeExtern* temp1 = (nodeExtern*)malloc(sizeof(nodeExtern));
		if (temp1 == NULL)
		{
			printf("Unable to allocate memory.");

		}
		else
		{
			temp1->memValue = memValue;

			strcpy(temp1->name, name);
			temp1->next = NULL;

			ptr = *p_head;

			while (ptr != NULL && ptr->next != NULL)
			{
				ptr = ptr->next;


			}

			ptr->next = temp1;
		}
	}

}
int isExtern(nodeSymbol** p_head, char* name)
{
	struct nodeSymbol* ptr = (*p_head);

	if (ptr == NULL)
		return 0;


	while (ptr != NULL)
	{
		if (!strcmp(ptr->name, name))
		{
			if (!strcmp(ptr->attributes[1], "extern"))
			{
				return 1;

			}

		}
		ptr = ptr->next;
	}

	return 0;


}

/*This Method checks if there is a external with entry Label*/
int checkDuplAddressateExtern(nodeSymbol** p_head, char* name)
{
	struct nodeSymbol* ptr = (*p_head);

	if (ptr == NULL)
		return 0;


	while (ptr != NULL)
	{
		if (!strcmp(ptr->name, name))
		{
			if (!strcmp(ptr->attributes[1], "extern"))
				return 1;

		}
		ptr = ptr->next;
	}

	return 0;
}


int secondPass(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, FILE* filename)
{
	char* token;
	char* temp;
	char* saveInstruction;
	int LC = 1, errorFlag = 0, Address = 100;

	char line[MAX_LINE], * result;


	while ((result = fgets(line, MAX_LINE, filename)) != NULL)
	{
		int lineSize = strlen(line); int address;
		char* pntr;
		char* tempLabel;

		if (!strcmp(line, "\n") || strchr(line, ';')) /*Check If Empty Sentence Or Comment Sentence*/
		{
			LC++;
			continue;
		}


		token = strtok(line, " "); /*Get The Lable/command/instruction*/
		if (strlen(token) == lineSize)
		{
			token = strtok(line, "\t"); /*Get The Lable/command/instruction*/
		}



		if (strchr(token, ':') != NULL) /*Check if Label Exists*/
		{
			tempLabel = strtok(line, ":");/*Get label without ":" */

			if (searchSymbol(head, tempLabel))
			{
				if (isExtern(head, tempLabel))
				{
					addNodeExtern(e_node, tempLabel, Address);

				}

			}

			temp = &line[strlen(token) + 2];
			token = strtok(temp, " ");

			if (isGuidance(token)) /*Check if Guidance*/
			{

				continue;


			}
			else if(isInstruction(token))
			{
				if (getType(token) == 'R')
				{
					Address = Address +4;
					continue;

				}
				else if (getType(token) == 'I')
				{
					if (!strcmp(token, "bgt") || !strcmp(token, "blt") || !strcmp(token, "beq") || !strcmp(token, "bne"))
					{
						if (!(checkIfMissing(ptr, Address)))
						{

							token = strtok(NULL, ","); /*SKIP RS*/
							token = strtok(NULL, ",");/*SKIP RT*/

							token = strtok(NULL, "\n");
							address = returnAddress(head, token);
							pntr = getString(ptr, Address);
							strcat(pntr, decimal_to_binary(address, 16));

						}
					}
					Address = Address +4;

				}
				else/* JMP*/
				{

					if (!(checkIfMissing(ptr, Address)))
					{

						token = strtok(NULL, "\n");
						address = returnAddress(head, token);
						pntr = getString(ptr, Address);
						if (pntr)
						{
							strcat(pntr, decimal_to_binary(address, 25));
						}
					}
					Address = Address +4;
				}

				continue;

			}
		}
		if (token[0] == '.')
		{
			char* attribute;
			if (isGuidance(token)) /*Check if Guidance*/
			{

				continue;
			}
			else
			{
				attribute = token + 1;/*Get Attribute Withouth "." */

				token = strtok(NULL, "\n");
				if (!strcmp(attribute, "entry"))
				{
					if (searchSymbol(head, token))
					{
						if (checkDuplAddressateExtern(head, token))
						{
							printf("error in line %d,there is already entry with this label\n", LC);
							LC++;
							errorFlag = 1;
							continue;

						}

						addAttribute(head, token, attribute);
						continue;
					}

				}
				else
				{
					continue;
				}
			}
		}
		else if(isInstruction(token))
		{
			if (getType(token) == 'R')
			{
				Address = Address +4;
				continue;/*nothing to do when type R*/

			}
			else if (getType(token) == 'I')
			{
				if (!strcmp(token, "bgt") || !strcmp(token, "blt") || !strcmp(token, "beq") || !strcmp(token, "bne"))
				{
					if (!(checkIfMissing(ptr, Address)))
					{

						token = strtok(NULL, ","); /*SKIP RS*/
						token = strtok(NULL, ",");/*SKIP RT*/

						token = strtok(NULL, "\n");

						if (searchSymbol(head, token))
						{
							if (isExtern(head, token))
							{
								addNodeExtern(e_node, token, Address);

							}

						}
						address = returnAddress(head, token);
						pntr = getString(ptr, Address);
						strcat(pntr, decimal_to_binary(address - Address, 16));

					}

				}
				Address = Address +4;
			}
			else  /* JMP TYPE*/
			{
				saveInstruction = token;
				if (!strcmp(saveInstruction, "stop"))
				{
					Address = Address +4;
					continue;


				}
				if (!(checkIfMissing(ptr, Address)))
				{

					token = strtok(NULL, "\n");
					if (searchSymbol(head, token))
					{
						if (isExtern(head, token))
						{
							addNodeExtern(e_node, token, Address);

						}

					}
					address = returnAddress(head, token);
					pntr = getString(ptr, Address);
					if (pntr)
					{
						if (strcmp(saveInstruction, "la"))/*IF NOT LA*/
								{
							strcat(pntr, decimal_to_binary(address, 25));
								}
						else
						{
							strcat(pntr, decimal_to_binary(address, 26));
						}
					}
					Address = Address +4;
				}
			}

		}


	}
	return errorFlag;
}
