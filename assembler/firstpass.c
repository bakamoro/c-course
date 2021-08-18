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
#include "writefiles.h"
#include "utils.h"




void proccessGuidance(char* token ,int* DC,int* LC,nodeMachine** ptr,char* machCode)
{

	if (!strcmp(token, ".asciz"))
	{

		unsigned int i=0;
		token = strtok(NULL, "\"");


		for (i=0; i < strlen(token); i++) /*Insert Every Letter to the machine Code List*/
		{
			InitMachCode(machCode);
			strcat(machCode, decimal_to_binary((token[i]), 8));
			addMachineNode(ptr, *DC , machCode,'D');
			*DC = *DC +1;
			*LC = *LC +1;
		}
		InitMachCode(machCode);
		strcat(machCode, decimal_to_binary(0, 8));
		addMachineNode(ptr, *DC, machCode,'D');
		*DC = *DC +1;
		*LC = *LC +1;


	}
	else /* dw OR db OR dh*/
	{
		int k, bits; char* temp;
		bits = getBits(token); /* get the num of bits to be inserted into the machinecode list*/

		token = strtok(NULL, " "); /*get the string withouth the guidance*/

		temp = (char*)calloc(strlen(token) + 1, 1);

		if (temp == NULL)
		{
			printf("Unable to allocate memory");
		}
		else
		{
			strcpy(temp, token);/*copy token's string  to temp*/


			while (strchr(temp, ',')) /*In case there are more than one variable*/
			{
				token = strtok(token, ",");
				k = atoi(token);
				InitMachCode(machCode);
				strcat(machCode, decimal_to_binary(k, bits));
				addMachineNode(ptr, *DC, machCode,'D');
				*DC = *DC + bits / 8;
				*LC = *LC +1;
				temp = temp + strlen(token) + 1;
				strcpy(token, temp);

			}
			/*In case of One Variable Or When there is only one variable left */

			token = strtok(token, "\n");
			k = atoi(token);
			InitMachCode(machCode);
			strcat(machCode, decimal_to_binary(k, bits));
			addMachineNode(ptr, *DC, machCode,'D');
			*DC = *DC + bits / 8;
			*LC = *LC +1;


		}
	}




}
int proccessInstruction(char* token ,int* LC ,int* IC, nodeSymbol** head,nodeMachine** ptr,char* machCode)
{
	int errorFlag=0;

	if (getType(token) == 'R')
	{
		int rs_param, rt_param, rd_param, funct;
		InitMachCode(machCode);
		funct = getFunct(token);

		strcat(machCode, decimal_to_binary(getOpcode(token), 6));/* append op code*/

		if (!strcmp(token, "move")) /* In case of only 2 Registers*/
		{

			token = strtok(NULL, ","); /*get rs*/
			token = token + 1;/*remove $*/
			rs_param = atoi(token);/*Convert to Decimal*/

			strcat(machCode, decimal_to_binary(rs_param, 5));/*append rs */

			strcat(machCode, decimal_to_binary(0, 5));/*append Zeros for rt */

			token = strtok(NULL, "\n"); /*get rd*/
			token = token + 1;/*remove $*/
			rd_param = atoi(token);/*Convert to Decimal*/
			strcat(machCode, decimal_to_binary(rd_param, 5));/*append rd */

			strcat(machCode, decimal_to_binary(funct, 5));/*append rd */

			strcat(machCode, decimal_to_binary(0, 6));/*append unused zeros*/

			addMachineNode(ptr, *IC, machCode,'I');

		}
		else if (!strcmp(token, "mvhi") || !strcmp(token, "mvlo")) /* In case of 1 Register*/
		{

			token = strtok(NULL, "\n"); /*get rs*/
			token = token + 1;/*remove $*/
			rs_param = atoi(token);/*Convert to Decimal*/

			strcat(machCode, decimal_to_binary(rs_param, 5));/*append rs */

			strcat(machCode, decimal_to_binary(0, 10));/*append Zeros for rt+rd */



			strcat(machCode, decimal_to_binary(funct, 5));/*append rd */

			strcat(machCode, decimal_to_binary(0, 6));/*append unused zeros*/

			addMachineNode(ptr, *IC, machCode,'I');

		}
		/*Regular case of 3 Registers */
		else
		{

			token = strtok(NULL, ","); /*get rs*/
			token = token + 1;/*remove $*/
			rs_param = atoi(token);/*Convert to Decimal*/

			strcat(machCode, decimal_to_binary(rs_param, 5));/*append rs */

			token = strtok(NULL, ",");
			token = token + 1; /* Remove $*/
			rt_param = atoi(token);

			strcat(machCode, decimal_to_binary(rt_param, 5));/*append  rt */

			token = strtok(NULL, "\n");
			token = token + 1;/* Remove $*/
			rd_param = atoi(token);

			strcat(machCode, decimal_to_binary(rd_param, 5));/*append rd */

			strcat(machCode, decimal_to_binary(funct, 5));/*append Funct*/

			strcat(machCode, decimal_to_binary(0, 6));/*append unused zeros*/

			addMachineNode(ptr, *IC, machCode,'I');
		}

	}
	else if (getType(token) == 'I')
	{
		int rs_param, rt_param, im_param;
		InitMachCode(machCode);
		strcat(machCode, decimal_to_binary(getOpcode(token), 6));


		if (!strcmp(token, "bgt") || !strcmp(token, "blt") || !strcmp(token, "beq") || !strcmp(token, "bne"))
		{

			token = strtok(NULL, ","); /*get rs*/
			token = token + 1;/*remove $*/
			rs_param = atoi(token);/*Convert to Decimal*/

			strcat(machCode, decimal_to_binary(rs_param, 5));/*Append Rs*/


			token = strtok(NULL, ",");
			token = token + 1;
			rt_param = atoi(token);

			strcat(machCode, decimal_to_binary(rs_param, 5)); /*Append Rt*/



			addMachineNode(ptr, *IC, machCode,'I');


		}
		else
		{

		/*Get the 3 Registers and edit the machine code*/

		token = strtok(NULL, ","); /*get rs*/
		token = token + 1;/*remove $*/
		rs_param = atoi(token);/*Convert to Decimal*/

		strcat(machCode, decimal_to_binary(rs_param, 5));

		token = strtok(NULL, ",");
		im_param = atoi(token);/*This is the Immidiate Value*/
		if (checkLimits(im_param))
		{
			printf("error in line %d,number out of boundary\n", *LC);
			*LC = *LC +1;
			errorFlag = 1;

		}


		token = strtok(NULL, "\n");
		token = token + 1;
		rt_param = atoi(token);


		strcat(machCode, decimal_to_binary(rt_param, 5));
		strcat(machCode, decimal_to_binary(im_param, 16));

		addMachineNode(ptr, *IC, machCode,'I');
		}

	}
	else /* JMP TYPE*/
	{
		int im_param;
		int ifAddedFlag=0;
		InitMachCode(machCode);

		strcat(machCode, decimal_to_binary(getOpcode(token), 6)); /*Append Opcode*/
		if (!strcmp(token, "stop"))
		{

			strcat(machCode, decimal_to_binary(0, 26));


		}

		else if (!strcmp(token, "jmp"))
		{
			token = strtok(NULL, "\n");
			if ((token[0] == '$')) /* Check if Register*/
			{

				strcat(machCode, "1"); /*Append Opcode*/
				token = token + 1;
				im_param = atoi(token);
				strcat(machCode, decimal_to_binary(im_param, 25)); /*Append Opcode*/
				addMachineNode(ptr, *IC, machCode,'I');
				*LC = *LC +1;
				ifAddedFlag=1;


			}
			else
			{

				strcat(machCode, "0"); /*Apped Zero for non register for J type*/
			}

		}
		else if (!strcmp(token, "call"))
		{

			strcat(machCode, "0");
			token = strtok(NULL, "\n");

		}
		else/*LA CASE*/
		{
			token = strtok(NULL, "\n");

		}
		if (searchSymbol(head, token))
		{
			if (isExtern(head, token))/*If label is extern append zeros*/
			{
				strcat(machCode, decimal_to_binary(0, 26));

			}
		/*	else
			{

				strcat(machCode, decimal_to_binary(returnAddress(head, token) - *Address, 24));

			}*/

		}
		if(!ifAddedFlag)
		{
		addMachineNode(ptr, *IC, machCode,'I');
		}

	}
	return errorFlag;
}

void proccessLables(char* token, nodeSymbol** head )
{
	char* attribute;

	attribute = token + 1;/*Get Attribute Withouth "." */

	token = strtok(NULL, "\n");

	if (!strcmp(attribute, "extern"))
	{
		addSymbolNode(head, token, 0, attribute);
	}

}


int firstPass(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC, FILE* filename)
{
	char* token;
	char* tempLabel;
	char* tempResult;
	char* temp;
	char machCode[33] = {0};
	int LC = 1, errorFlag = 0,lineSize;

	char line[MAX_LINE], * result;

	while ((result = fgets(line, MAX_LINE, filename)) != NULL)
	{
		memset(machCode, 0, 33);
		lineSize = strlen(line);

		if (!strcmp(line, "\n") || strchr(line, ';')) /*Check If Empty Sentence Or Comment Sentence*/
		{
			LC++;
			continue;
		}

		tempResult = (char*)calloc(strlen(result) + 1, 1);
		strcpy(tempResult, result);

		token = strtok(line, " "); /*Get The Lable/command/instruction*/
		if (strlen(token) == lineSize)
		{
			token = strtok(line, "\t"); /*Get The Lable/command/instruction*/
		}


		if (strchr(token, ':') != NULL) /*Check if Label Exists*/
		{
			tempLabel = strtok(line, ":");/*Get label without ":" */

			/*Check if Label is Legal*/
			if (isGuidance(tempLabel) || isInstruction(tempLabel)) /*Check if label is keyword*/
			{
				printf("error in line %d,Label name is a keyword\n", LC);
				LC++;
				errorFlag = 1;
				continue;
			}
			if (searchSymbol(head, tempLabel))/*check if exist in the symboltable*/
			{
				printf("error in line %d,Label Already Exist\n", LC);
				LC++;
				errorFlag = 1;
				continue;

			}


			/*check if instuction*/
			temp = &line[strlen(token) + 2];
			token = strtok(temp, " ");
			if (token[strlen(token) - 1] == '\n')/*For Stop Command*/
			{
				token = strtok(temp, "\n");
			}

			if (isGuidance(token)) /*Check if Guidance*/
			{
				addSymbolNode(head, tempLabel, *DC , "data"); /*add to Symbol*/

				proccessGuidance(token,DC,&LC,ptr,machCode);
				continue;



			}
			else if (isInstruction(token))
			{

				addSymbolNode(head, tempLabel, *IC , "code"); /*Add Symbol to the symbol Tabel*/

				/*Get the 3 Registers and edit the machine code*/
				if(proccessInstruction(token,&LC,IC,head,ptr,machCode))
				{
					errorFlag=1;
				}
				*IC = *IC + 4;


			}
			else /* is Entry or Extern*/
			{
				proccessLables(token,head);
				LC++;
				continue;

			}

		}

		else if (token[0] == '.') /*entry,extern or Guidance without label*/
		{
			if (isGuidance(token)) /*Check if Guidance*/
			{
				proccessGuidance(token,DC,&LC,ptr,machCode);
			}
			else
			{
				proccessLables(token,head);
				LC++;
				continue;

			}
		}
		else /* Instruction */
		{
			if (isInstruction(token))
			{

				if(proccessInstruction(token,&LC,IC,head,ptr,machCode))
				{
					errorFlag=1;
				}
				*IC = *IC + 4;

			}
		}
		InitMachCode(machCode);
		LC++;
	}
	updateAddress(head,IC);
	updateMemValue(ptr,IC);

	rewind(filename);

	return errorFlag;
}

