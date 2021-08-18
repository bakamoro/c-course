#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"



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

int isGuidance(char* name) /*The function Checks if the sentnce is guidance sentence*/
{
	char dh[] = ".dh", dw[] = ".dw", db[] = ".db", asciz[] = ".asciz";

	if (!strcmp(name, dh) || !strcmp(name, dw) || !strcmp(name, db) || !strcmp(name, asciz))
	{
		return 1;
	}

	else return 0;

}



