#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_LINE 80 
#define CMD_NUM 27
#define GID_NUM 4

#pragma warning(disable : 4996)



struct cmdDesc
{
    char cmd_Name[5];
    char type;
    unsigned int opCode;
    unsigned int funct;
};

struct gidDesc
{
    char cmd_Name[7];
    int bits;

};

typedef struct nodeSymbol {

    char name[5];
    int memValue;
    char attributes[2][7];
    struct nodeSymbol* next;
}nodeSymbol;

typedef struct nodeMachine {

    int address;
    char code[33];
    struct nodeMachine* next;
}nodeMachine;

static struct gidDesc gids[GID_NUM] = {
    {".asciz",8},
    {".dw",32},
    {".dh",16},
    {".db",8},

};

int getBits(char* name)
{
    int i = 0;

    for (i; i < GID_NUM; i++)
    {
        if (!strcmp(name, gids[i].cmd_Name))
        {

            return gids[i].bits;

        }

    }
    return 0;

}

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
    int i = 0;

    for (i; i < CMD_NUM; i++)
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
    int i = 0;

    for (i; i < CMD_NUM; i++)
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
    int i = 0;

    for (i; i < CMD_NUM; i++)
    {
        if (!strcmp(cmds[i].cmd_Name, name))
        {
            return cmds[i].opCode;

        }


    }

    return 0;


}int getFunct(char* name)
{
    int i = 0;

    for (i; i < CMD_NUM; i++)
    {
        if (!strcmp(cmds[i].cmd_Name, name))
        {
            return cmds[i].funct;

        }

    }

    return 0;
}

void addSymbolNode(nodeSymbol** p_head, char* name, int memValue, char* attribute)
{
    if (*p_head == NULL)
    {
        *p_head = (nodeSymbol*)malloc(sizeof(nodeSymbol));

        if (*p_head == NULL)
        {
            printf("Unable to Allocate Memory");

        }
        else
            (*p_head)->next = NULL;
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

void printCodes(nodeMachine** ptr_head)
{
    struct nodeMachine* ptr = (*ptr_head);

    if (ptr == NULL)
    { 
        exit(0);
    }

    while (ptr != NULL)
    {
        printf("%s\n", ptr->code);

        ptr = ptr->next;
    }
      



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

int checkIfMissing(nodeMachine** ptr, int IC)
{

    struct nodeMachine* head = *ptr;


    if (ptr == NULL)
        return 0;


    while (head != NULL)
    {
        if (head->address == IC)
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

char* getString(nodeMachine** ptr, int IC)
{
    struct nodeMachine* head = *ptr;


    if ((head) == NULL)
    {

        printf("ERROR");
    }

    else
    {


        while (head->next != NULL)
        {
            if (head->address == IC)
            {

                return head->code;

            }
            head = head->next;

        }

    }

    return 0;
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

void InitMachCode(char mach[])
{
    int i = 0;

    for (i; i < 32; i++)
    {
        mach[i] = '\0';

    }


}


int main(int argc, char* argv[])
{

    char* token;
    char* tempLabel;
    char* saveInstruction;
    char machCode[33] = "";
    int DC = 0, IC = 100;
    


    nodeSymbol* head = NULL;
    nodeMachine* ptr = NULL;


    FILE* stream;
    char line[MAX_LINE], * result;

    stream = fopen("Source1.as", "r");


    if (stream == NULL)
    {
        printf("Error!");
        exit(1);
    }


    while ((result = fgets(line, MAX_LINE, stream)) != NULL)
    {
        int lineSize = strlen(line);

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
                printf("error m0therfucker");

            }
            /*check if exist in the symboltable*/
            /*if exist error else add to symboltable*/


            /*check if instuction*/
            char* temp = &line[strlen(token) + 2];
            token = strtok(temp, " ");
            if (token[strlen(token)-1]=='\n')/*For Stop Command*/
            {
                token = strtok(temp, "\n");
            }

            if (isGuidance(token)) /*Check if Guidance*/
            {
                addSymbolNode(&head, tempLabel, IC, "data"); /*add to Symbol*/

                if (!strcmp(token, ".asciz"))
                {

                    unsigned int i = 0;
                    token = strtok(NULL, "\"");
                    DC = DC + strlen(token); /*Update DC*/

                    for (i; i < strlen(token); i++) /*Insert Every Letter to the machine Code List*/
                    {
                        InitMachCode(machCode);
                        strcat(machCode, decimal_to_binary((token[i]), 8));
                        addMachineNode(&ptr, IC, machCode);
                        IC = IC + 1;
                    }
                    InitMachCode(machCode);
                    strcat(machCode, decimal_to_binary(0, 8));
                    addMachineNode(&ptr, IC, machCode);
                    IC = IC + 1;

                    continue;

                }
                else /* Check if Guidance is dw*/
                {
                    int k, bits; char* temp;
                    bits = getBits(token); /* get the num of bits to be inserted into the machinecode list*/
                    token = strtok(NULL, " "); /*get the string withouth the guidance*/

                    temp = (char*)malloc(strlen(token));

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
                            addMachineNode(&ptr, IC, machCode);
                            IC = IC + bits / 8;
                            temp = temp + strlen(token) + 1;
                            strcpy(token, temp);

                        }
                        /*In case of One Variable Or When there is only one variable left */

                        token = strtok(token, "\n");
                        k = atoi(token);
                        InitMachCode(machCode);
                        strcat(machCode, decimal_to_binary(k, bits));
                        addMachineNode(&ptr, IC, machCode);
                        IC = IC + bits / 8;
                        continue;
                        /*free(temp);*/

                    }
                }
                /* add node to the symbol table count the Varibles , take care of DC and the string of binary result */
            }
            else if (isInstruction(token))
            {
                /*add node to the symbol table*/
                if (searchSymbol(&head, tempLabel))
                {

                    /*Should be Error*/


                }
                addSymbolNode(&head, tempLabel, IC, "code");

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

                        addMachineNode(&ptr, IC, machCode);

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

                        addMachineNode(&ptr, IC, machCode);

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

                        addMachineNode(&ptr, IC, machCode);
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

                        if (searchSymbol(&head, token))
                        {

                            strcat(machCode, decimal_to_binary(returnAddress(&head, token) - IC, 16)); /*Calculate the Immidiate */

                        }

                        addMachineNode(&ptr, IC, machCode);


                    }

                    /*Get the 3 Registers and edit the machine code*/

                    token = strtok(NULL, ","); /*get rs*/
                    token = token + 1;/*remove $*/
                    rs_param = atoi(token);/*Convert to Decimal*/

                    strcat(machCode, decimal_to_binary(rs_param, 5));

                    token = strtok(NULL, ",");
                    im_param = atoi(token);


                    token = strtok(NULL, "\n");
                    token = token + 1;
                    rt_param = atoi(token);

                    strcat(machCode, decimal_to_binary(rt_param, 5));
                    strcat(machCode, decimal_to_binary(im_param, 16));

                    addMachineNode(&ptr, IC, machCode);
                }
                else /* JMP TYPE*/
                {
                if (!strcmp(token, "stop"))
                {
                    InitMachCode(machCode);
                    strcat(machCode, decimal_to_binary(getOpcode(token), 6));

                    strcat(machCode, decimal_to_binary(0, 26));

                    addMachineNode(&ptr, IC, machCode);
                }

                }

            }
            else
            {

            }/* is Entry or Extern*/

            /*Write function here to check if entry / extern else is code*/

            /*Check if Space available*/
            /*Search if Exist*/

        }

        else if (token[0] == '.') /*entry,extern or Guidance without label*/
        {
        if (isGuidance(token)) /*Check if Guidance*/
        {
            if (!strcmp(token, ".asciz"))
            {

                unsigned int i = 0;
                token = strtok(NULL, "\"");
                DC = DC + strlen(token); /*Update DC*/

                for (i; i < strlen(token); i++) /*Insert Every Letter to the machine Code List*/
                {
                    InitMachCode(machCode);
                    strcat(machCode, decimal_to_binary((token[i]), 8));
                    addMachineNode(&ptr, IC, machCode);
                    IC = IC + 1;
                }
                InitMachCode(machCode);
                strcat(machCode, decimal_to_binary(0, 8));
                addMachineNode(&ptr, IC, machCode);
                IC = IC + 1;

                continue;

            }
            else /* Check if Guidance is dw*/
            {
                int k, bits; char* temp;
                bits = getBits(token); /* get the num of bits to be inserted into the machinecode list*/
                token = strtok(NULL, " "); /*get the string withouth the guidance*/

                temp = (char*)malloc(strlen(token));

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
                        addMachineNode(&ptr, IC, machCode);
                        IC = IC + bits / 8;
                        temp = temp + strlen(token) + 1;
                        strcpy(token, temp);

                    }
                    /*In case of One Variable Or When there is only one variable left */

                    token = strtok(token, "\n");
                    k = atoi(token);
                    InitMachCode(machCode);
                    strcat(machCode, decimal_to_binary(k, bits));
                    addMachineNode(&ptr, IC, machCode);
                    IC = IC + bits / 8;
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
                addSymbolNode(&head, token, 0, attribute);
                continue;
            }
            else
                addSymbolNode(&head, token, IC, attribute); /*Add to Data Segment */

        }
        }
        else /* Instruction */
        {
            if (isInstruction(token))
            {
                if (getType(token) == 'R')
                {
                    int rs_param, rt_param, rd_param, funct;
                    //InitMachCode(machCode);
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

                        addMachineNode(&ptr, IC, machCode);

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

                        addMachineNode(&ptr, IC, machCode);

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

                        addMachineNode(&ptr, IC, machCode);
                    }
                }
                else if (getType(token) == 'I')
                {

                    int rs_param, rt_param, rd_param;
                    char* tempInstruct;
                    if (!strcmp(token, "bgt") || !strcmp(token, "blt") || !strcmp(token, "beq") || !strcmp(token, "bne"))
                    {
                        strcat(machCode, decimal_to_binary(getOpcode(token), 6));
                        token = strtok(NULL, ","); /*get rs*/
                        token = token + 1;/*remove $*/
                        rs_param = atoi(token);/*Convert to Decimal*/

                        strcat(machCode, decimal_to_binary(rs_param, 5));/*Append Rs*/


                        token = strtok(NULL, ",");
                        token = token + 1;
                        rt_param = atoi(token);

                        strcat(machCode, decimal_to_binary(rs_param, 5)); /*Append Rt*/


                        token = strtok(NULL, "\n");

                        if (searchSymbol(&head, token))
                        {

                            strcat(machCode, decimal_to_binary(returnAddress(&head, token) - IC, 16)); /*Calculate the Immidiate */

                        }

                        addMachineNode(&ptr, IC, machCode);
                    }
                    else
                    { 

                    InitMachCode(machCode);
                    strcat(machCode, decimal_to_binary(getOpcode(token), 6)); /*apped opCode*/
                    tempInstruct = token;
                    token = strtok(NULL, ","); /*get rs*/
                    token = token + 1;/*remove $*/
                    rs_param = atoi(token);/*Convert to Decimal*/

                    strcat(machCode, decimal_to_binary(rs_param, 5));/*Append Rs*/

                    if (strcmp(tempInstruct , "sw") && strcmp(tempInstruct, "lh") && strcmp(tempInstruct, "lb") && strcmp(tempInstruct, "sb") && strcmp(tempInstruct, "lw") && strcmp(tempInstruct, "sh")) /*IF STORE OR LOAD INSTRUCTION*/
                    { 
                    token = strtok(NULL, ",");
                    token = token + 1;
                    rt_param = atoi(token);

                    strcat(machCode, decimal_to_binary(rs_param, 5)); /*Append Rt*/


                    token = strtok(NULL, "\n");

                    if (searchSymbol(&head, token))
                    {

                        strcat(machCode, decimal_to_binary(returnAddress(&head, token) - IC, 16)); /*Calculate the Immidiate */

                    }
                    addMachineNode(&ptr, IC, machCode);
                    }
                    else
                    {
                        token = strtok(NULL, ",");
                        rt_param = atoi(token); /*THIS IS THE IMMIDIATE VALUE*/

                        token = strtok(NULL, "\n");
                        token = token + 1; /*Get num withouth $*/
                        rd_param = atoi(token);

                        strcat(machCode, decimal_to_binary(rd_param, 5)); /*Append Rt*/

                        strcat(machCode, decimal_to_binary(rt_param, 16));/*Append Immidiate */

                        addMachineNode(&ptr, IC, machCode);

                    }
                }
                }
                else  /* JMP TYPE*/
                {
                    InitMachCode(machCode);
                    int im_param;
                    strcat(machCode, decimal_to_binary(getOpcode(token), 6)); /*Append Opcode*/

                    if (!strcmp(token, "jmp"))
                    {
                        token = strtok(NULL, "\n");
                        if ((token[0] == '$')) /* Check if Register*/
                        {

                            strcat(machCode, "1"); /*Append Opcode*/
                            token = token + 1;
                            im_param = atoi(token);
                            strcat(machCode, decimal_to_binary(im_param, 25)); /*Append Opcode*/
                            addMachineNode(&ptr, IC, machCode);
                            IC = IC + 4;
                            continue;

                        }
                        else
                        {

                            strcat(machCode, "0"); /*Apped Zero for non register for J type*/
                        }

                    }
                    else
                    {
                        if (!strcmp(token, "call"))
                        {
                            strcat(machCode, "0");
                        }
                        

                        token = strtok(NULL, "\n");
                    }
                    if (searchSymbol(&head, token))
                    {

                        strcat(machCode, decimal_to_binary(returnAddress(&head, token) - IC, 24)); /*Apped Zero for non register for J type*/

                    }
                    addMachineNode(&ptr, IC, machCode);

                }
            }  
        }
        InitMachCode(machCode);
        IC = IC + 4;
    }
    rewind(stream);
    IC = 100;
    /*--------------------------------------------------------------------Second Pass-----------------------------------------------------------------*/

    while ((result = fgets(line, MAX_LINE, stream)) != NULL)
    {
        int lineSize = strlen(line); int address;
        char* pntr, tempLabel;

        token = strtok(line, " "); /*Get The Lable/command/instruction*/
        if (strlen(token) == lineSize)
        {
            token = strtok(line, "\t"); /*Get The Lable/command/instruction*/
        }



        if (strchr(token, ':') != NULL) /*Check if Label Exists*/
        {
            tempLabel = strtok(line, ":");/*Get label without ":" */

            char* temp = &line[strlen(token) + 2];
            token = strtok(temp, " ");

            if (isGuidance(token)) /*Check if Guidance*/
            {

                if (!strcmp(token, ".asciz"))
                {
                    token = strtok(NULL, "\"");
                    IC = IC + strlen(token)+1;

                    continue;
                }
                else /* Check if Guidance is dw*/
                {
                    int bits; char* temp;
                    bits = getBits(token); /* get the num of bits to be inserted into the machinecode list*/
                    token = strtok(NULL, " "); /*get the string withouth the guidance*/

                    temp = (char*)malloc(strlen(token));

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
                            IC = IC + bits / 8;
                            temp = temp + strlen(token) + 1;
                            strcpy(token, temp);

                        }
                        /*In case of One Variable Or When there is only one variable left */

                        token = strtok(token, "\n");
                        IC = IC + bits / 8;
                        continue;
                        /*free(temp);*/

                    }

                }


                /* add node to the symbol table count the Varibles , take care of DC and the string of binary result */
            }

            if (getType(token) == 'R')
            {
                IC = IC + 4;
                continue;

            }
            else if (getType(token) == 'I')
            {
                if (!strcmp(token, "bgt") || !strcmp(token, "blt") || !strcmp(token, "beq") || !strcmp(token, "bne"))
                {
                    if (!(checkIfMissing(&ptr, IC)))
                    {

                        token = strtok(NULL, ","); /*SKIP RS*/
                        token = strtok(NULL, ",");/*SKIP RT*/

                        token = strtok(NULL, "\n");
                        address = returnAddress(&head, token);
                        pntr = getString(&ptr, IC);
                        strcat(pntr, decimal_to_binary(address, 16));

                    }
                }
                    
            }
            else/* JMP*/
            {

                if (!(checkIfMissing(&ptr, IC)))
                {

                    token = strtok(NULL, "\n");
                    address = returnAddress(&head, token);
                    pntr = getString(&ptr, IC);
                    strcat(pntr, decimal_to_binary(address, 25));

                }
            }

            IC = IC + 4;
            continue;

        }
        else if (token[0] == '.')
        {
            char* attribute;
            if (isGuidance(token)) /*Check if Guidance*/
            {

                if (!strcmp(token, ".asciz"))
                {
                    token = strtok(NULL, "\"");
                    IC = IC + strlen(token);

                    continue;
                }
                else /* Check if Guidance is dw*/
                {
                    int bits; char* temp;
                    bits = getBits(token); /* get the num of bits to be inserted into the machinecode list*/
                    token = strtok(NULL, " "); /*get the string withouth the guidance*/

                    temp = (char*)malloc(strlen(token));

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
                            IC = IC + bits / 8;
                            temp = temp + strlen(token) + 1;
                            strcpy(token, temp);

                        }
                        /*In case of One Variable Or When there is only one variable left */

                        token = strtok(token, "\n");
                        IC = IC + bits / 8;
                        continue;
                        /*free(temp);*/

                    }

                }


                /* add node to the symbol table count the Varibles , take care of DC and the string of binary result */
            }
            else
            { 
            attribute = token + 1;/*Get Attribute Withouth "." */

            token = strtok(NULL, "\n");
            if (!strcmp(attribute, "entry"))
            {
                if (searchSymbol(&head, token))
                {

                    addAttribute(&head, token, attribute);
                    continue;

                }
                else
                {

                    printf("ERROR");
                }
            }
            else
            {
                continue;
            }
            }
        }
        else
        {
            if (getType(token) == 'R')
            {
                continue;/*nothing to do when type R*/

            }
            else if (getType(token) == 'I')
            {
                if (!strcmp(token, "bgt") || !strcmp(token, "blt") || !strcmp(token, "beq") || !strcmp(token, "bne"))
                {
                    if (!(checkIfMissing(&ptr, IC)))
                    {

                        token = strtok(NULL, ","); /*SKIP RS*/
                        token = strtok(NULL, ",");/*SKIP RT*/

                        token = strtok(NULL, "\n");
                        address = returnAddress(&head, token);
                        pntr = getString(&ptr, IC);
                        strcat(pntr, decimal_to_binary(address, 16));

                    }

                }
  
            }
            else  /* JMP TYPE*/
            {
                saveInstruction = token;

                if (!(checkIfMissing(&ptr, IC)))
                {

                    token = strtok(NULL, "\n");
                    address = returnAddress(&head, token);
                    pntr = getString(&ptr, IC);
                    if(strcmp(saveInstruction,"la"))
                    { 
                    strcat(pntr, decimal_to_binary(address, 25));
                    }
                    else
                    {
                        strcat(pntr, decimal_to_binary(address, 26));
                    }
                }
            }

        }

        IC = IC + 4;
        continue;

    }
    printCodes(&ptr);
    return 0;

}
