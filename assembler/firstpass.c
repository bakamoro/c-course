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

/*
#define MAX_LINE 80 
#define CMD_NUM 27
#define GID_NUM 4
#define LABEL_MAX_LEN 31*/

struct gidDesc
{
    char cmd_Name[CMD_NAME];
    int bits;

};




struct cmdDesc
{
    char cmd_Name[CMD_NAME];
    char type;
    unsigned int opCode;
    unsigned int funct;
};



static struct gidDesc gids[GID_NUM] = {
    {".asciz",8},
    {".dw",32},
    {".dh",16},
    {".db",8},

};
static struct cmdDesc cmds[CMD_NUM] = {
    {"add",'R',0,1},
    {"sub",'R',0,2},
    {"and",'R',0,3},
    {"or",'R',0,4},
    {"nor",'R',0,5},
    {"move",'R',1,1},
    {"mvhi",'R',1,2},
    {"mvlo",'R',1,3},
    {"addi",'I',10},
    {"subi",'I',11},
    {"andi",'I',12},
    {"ori",'I',13},
    {"nori",'I',14},
    {"bne",'I',15},
    {"beq",'I',16},
    {"blt",'I',17},
    {"bgt",'I',18},
    {"lb",'I',19},
    {"sb",'I',20},
    {"lw",'I',21},
    {"sw",'I',22},
    {"lh",'I',23},
    {"sh",'I',24},
    {"jmp",'J',30},
    {"la",'J',31},
    {"call",'J',32},
    {"stop",'J',63},

};



int getBits(char* name)
{
    int i;

    for (i=0; i < GID_NUM; i++)
    {
        if (!strcmp(name, gids[i].cmd_Name))
        {

            return gids[i].bits;

        }

    }
    return 0;

}


int isGuidance(char* name) /*The function Checks if the sentnce is guidance sentence*/
{
    char dh[] = ".dh", dw[] = ".dw", db[] = ".db", asciz[] = ".asciz";

    if (!strcmp(name, dh) || !strcmp(name, dw) || !strcmp(name, db) || !strcmp(name, asciz))
    {
        return 1;
    }

    else return 0;

}

int isInstruction(char* name)/*This fucntions checks if the sentence is instruction*/
{
    int i;

    for (i=0; i < CMD_NUM; i++)
    {
        if (!strcmp(name, cmds[i].cmd_Name))
        {
            return 1;
        }
    }


    return 0;
}



char getType(char* name)
{
    int i;

    for (i=0; i < CMD_NUM; i++)
    {
        if (!strcmp(cmds[i].cmd_Name, name))
        {
            return cmds[i].type;

        }

    }

    return 0;

}
int getOpcode(char* name)
{
    int i;

    for (i=0; i < CMD_NUM; i++)
    {
        if (!strcmp(cmds[i].cmd_Name, name))
        {
            return cmds[i].opCode;

        }

    }

    return 0;

}

int getFunct(char* name)
{
    int i;

    for (i=0; i < CMD_NUM; i++)
    {
        if (!strcmp(cmds[i].cmd_Name, name))
        {
            return cmds[i].funct;

        }

    }

    return 0;
}

int checkLimits(int num)
{
    if (num < INT_MIN || num > INT_MAX)
    {
        return 1;
    }

    return 0;

}

int firstPass(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC, FILE* filename)
{
    char* token;
    char* tempLabel;
    char* tempResult;
    char* temp;
    char machCode[33] = {0};
    int LC = 1, errorFlag = 0, Address = 100,lineSize;

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

        if (!strchr(token, ':') && strchr(tempResult, ':'))/*Check if There is White space between Label and ":*/
        {

            printf("error in line %d,Space After Label\n", LC);
            Address = Address + 4;
            LC++;
            errorFlag = 1;
            continue;

        }

        if (strchr(token, ':') != NULL) /*Check if Label Exists*/
        {
            tempLabel = strtok(line, ":");/*Get label without ":" */
            if (strlen(tempLabel) > LABEL_MAX_LEN)
            {

                printf("error in line %d,Label's name too long\n", LC);
                LC++;
                errorFlag = 1;
                continue;
            }

            /*Check if Label is Legal*/
            if (isGuidance(tempLabel) || isInstruction(tempLabel)) /*Check if label is keyword*/
            {
                printf("error in line %d,Label name is a keyword\n", LC);
                Address = Address + 4;
                LC++;
                errorFlag = 1;
                continue;
            }
            if (searchSymbol(head, tempLabel))/*check if exist in the symboltable*/
            {
                printf("error in line %d,Label Already Exist\n", LC);
                Address = Address + 4;
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
                addSymbolNode(head, tempLabel, Address, "data"); /*add to Symbol*/

                if (!strcmp(token, ".asciz"))
                {

                    unsigned int i=0;
                    token = strtok(NULL, "\"");
                    *DC = *DC + strlen(token) + 1; /*Update DC*/

                    for (i=0; i < strlen(token); i++) /*Insert Every Letter to the machine Code List*/
                    {
                        InitMachCode(machCode);
                        strcat(machCode, decimal_to_binary((token[i]), 8));
                        addMachineNode(ptr, Address, machCode,'D');
                        Address = Address + 1;
                        LC++;
                    }
                    InitMachCode(machCode);
                    strcat(machCode, decimal_to_binary(0, 8));
                    addMachineNode(ptr, Address, machCode,'D');
                    Address = Address + 1;
                    LC++;

                    continue;

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
                            addMachineNode(ptr, Address, machCode,'D');
                            Address = Address + bits / 8;
                            *DC = *DC + bits / 8;
                            LC++;
                            temp = temp + strlen(token) + 1;
                            strcpy(token, temp);

                        }
                        /*In case of One Variable Or When there is only one variable left */

                        token = strtok(token, "\n");
                        k = atoi(token);
                        InitMachCode(machCode);
                        strcat(machCode, decimal_to_binary(k, bits));
                        addMachineNode(ptr, Address, machCode,'D');
                        Address = Address + bits / 8;
                        *DC = *DC + bits / 8;
                        LC++;
                        continue;
                        /*free(temp);*/

                    }
                }
                /* add node to the symbol table count the Varibles , take care of DC and the string of binary result */
            }
            else if (isInstruction(token))
            {
                *IC = *IC + 4;
                addSymbolNode(head, tempLabel, Address, "code"); /*Add Symbol to the symbol Tabel*/

                /*Get the 3 Registers and edit the machine code*/

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

                        addMachineNode(ptr, Address, machCode,'I');

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

                        addMachineNode(ptr, Address, machCode,'I');

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

                        addMachineNode(ptr, Address, machCode,'I');
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


                        token = strtok(NULL, "\n");

                        if (searchSymbol(head, token))
                        {

                            strcat(machCode, decimal_to_binary(returnAddress(head, token) - Address, 16)); /*Calculate the Immidiate */

                        }

                        addMachineNode(ptr, Address, machCode,'I');


                    }

                    /*Get the 3 Registers and edit the machine code*/

                    token = strtok(NULL, ","); /*get rs*/
                    token = token + 1;/*remove $*/
                    rs_param = atoi(token);/*Convert to Decimal*/

                    strcat(machCode, decimal_to_binary(rs_param, 5));

                    token = strtok(NULL, ",");
                    im_param = atoi(token);/*This is the Immidiate Value*/
                    if (checkLimits(im_param))
                    {
                        printf("error in line %d,number out of boundary\n", LC);
                        Address = Address + 4;
                        LC++;
                        errorFlag = 1;
                        continue;

                    }


                    token = strtok(NULL, "\n");
                    token = token + 1;
                    rt_param = atoi(token);


                    strcat(machCode, decimal_to_binary(rt_param, 5));
                    strcat(machCode, decimal_to_binary(im_param, 16));

                    addMachineNode(ptr, Address, machCode,'I');
                }
                else /* JMP TYPE*/
                {
                	int im_param;
                    InitMachCode(machCode);

                    strcat(machCode, decimal_to_binary(getOpcode(token), 6)); /*Append Opcode*/
                    if (!strcmp(token, "stop"))
                    {

                        strcat(machCode, decimal_to_binary(0, 26));


                        /*addMachineNode(&ptr, Address, machCode);*/
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
                            addMachineNode(ptr, Address, machCode,'I');
                            Address = Address + 4;
                            LC++;
                            continue;

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
                        else
                        {

                            strcat(machCode, decimal_to_binary(returnAddress(head, token) - Address, 24)); /*Apped Zero for non register for J type*/
                        }

                    }
                    addMachineNode(ptr, Address, machCode,'I');

                }

            }
            else /* is Entry or Extern*/
            {
                char* attribute;

                attribute = token + 1;/*Get Attribute Withouth "." */

                token = strtok(NULL, "\n");
                if (!strcmp(attribute, "entry"))
                {
                    continue;
                }
                if (!strcmp(attribute, "extern"))
                {
                    addSymbolNode(head, token, 0, attribute);
                    continue;
                }
                else
                    addSymbolNode(head, token, Address, attribute); /*Add to Data Segment */

            }

        }

        else if (token[0] == '.') /*entry,extern or Guidance without label*/
        {
            if (isGuidance(token)) /*Check if Guidance*/
            {
                if (!strcmp(token, ".asciz"))
                {

                    unsigned int i = 0;
                    token = strtok(NULL, "\"");
                    *DC = *DC + strlen(token) + 1; /*Update DC*/

                    for (i=0; i < strlen(token); i++) /*Insert Every Letter to the machine Code List*/
                    {
                        InitMachCode(machCode);
                        strcat(machCode, decimal_to_binary((token[i]), 8));
                        addMachineNode(ptr, Address, machCode,'D');
                        Address = Address + 1;
                        LC++;
                    }
                    InitMachCode(machCode);
                    strcat(machCode, decimal_to_binary(0, 8));
                    addMachineNode(ptr, Address, machCode,'D');
                    Address = Address + 1;
                    LC++;

                    continue;

                }
                else /* Check if Guidance is dw*/
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
                            if (checkLimits(k))
                            {
                                printf("error in line %d,number out of boundary\n", LC);
                                Address = Address + 4;
                                LC++;
                                errorFlag = 1;
                                continue;

                            }
                            InitMachCode(machCode);
                            strcat(machCode, decimal_to_binary(k, bits));
                            addMachineNode(ptr, Address, machCode,'D');
                            Address = Address + bits / 8;
                            *DC = *DC + bits / 8;
                            LC++;
                            temp = temp + strlen(token) + 1;
                            strcpy(token, temp);

                        }
                        /*In case of One Variable Or When there is only one variable left */

                        token = strtok(token, "\n");
                        k = atoi(token);
                        if (checkLimits(k))
                        {
                            printf("error in line %d,number out of boundary\n", LC);
                            Address = Address + 4;
                            LC++;
                            errorFlag = 1;
                            continue;

                        }

                        InitMachCode(machCode);
                        strcat(machCode, decimal_to_binary(k, bits));
                        addMachineNode(ptr, Address, machCode,'D');
                        Address = Address + bits / 8;
                        *DC = *DC + bits / 8;
                        LC++;
                        continue;
                        /*free(temp);*/

                    }
                }
            }
            else
            {
                char* attribute;

                attribute = token + 1;/*Get Attribute Withouth "." */

                token = strtok(NULL, "\n");
                if (!strcmp(attribute, "entry"))
                {
                    continue;
                }
                if (!strcmp(attribute, "extern"))
                {

                    addSymbolNode(head, token, 0, attribute);
                    continue;
                }
                else
                    addSymbolNode(head, token, Address, attribute); /*Add to Data Segment */

            }
        }
        else /* Instruction */
        {
            if (isInstruction(token))
            {
                *IC = *IC + 4;
                if (getType(token) == 'R')
                {
                    int rs_param, rt_param, rd_param, funct;
                    /*InitMachCode(machCode);*/
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

                        addMachineNode(ptr, Address, machCode,'I');

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

                        addMachineNode(ptr, Address, machCode,'I');

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

                        addMachineNode(ptr, Address, machCode,'I');
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

                        strcat(machCode, decimal_to_binary(rt_param, 5)); /*Append Rt*/


                        token = strtok(NULL, "\n");

                        if (searchSymbol(head, token))
                        {

                            strcat(machCode, decimal_to_binary(returnAddress(head, token) - Address, 16)); /*Calculate the Immidiate */

                        }

                        addMachineNode(ptr, Address, machCode,'I');


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
                            printf("error in line %d,number out of boundary\n", LC);
                            Address = Address + 4;
                            LC++;
                            errorFlag = 1;
                            continue;

                        }


                        token = strtok(NULL, "\n");
                        token = token + 1;
                        rt_param = atoi(token);


                        strcat(machCode, decimal_to_binary(rt_param, 5));
                        strcat(machCode, decimal_to_binary(im_param, 16));

                        addMachineNode(ptr, Address, machCode,'I');
                    }
                }
                else  /* JMP TYPE*/
                {
                	int im_param;
                    InitMachCode(machCode);
                    strcat(machCode, decimal_to_binary(getOpcode(token), 6)); /*Append Opcode*/
                    if (!strcmp(token, "stop"))
                    {

                        strcat(machCode, decimal_to_binary(0, 26));

                        addMachineNode(ptr, Address, machCode,'I');
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
                            addMachineNode(ptr, Address, machCode,'I');
                            Address = Address + 4;
                            LC++;
                            continue;

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
                    else/*ELSE IS LA*/
                    {
                        token = strtok(NULL, "\n");

                    }

                    if (searchSymbol(head, token))
                    {
                        if (isExtern(head, token))
                        {
                            strcat(machCode, decimal_to_binary(0, 26));
                        }
                        else
                        {

                            strcat(machCode, decimal_to_binary(returnAddress(head, token) - Address, 24)); /*Apped Zero for non register for J type*/
                        }
                    }
                    addMachineNode(ptr, Address, machCode,'I');


                }
            }
        }
        InitMachCode(machCode);
        Address = Address + 4;
        LC++;
    }
    rewind(filename);

    return errorFlag;
}
