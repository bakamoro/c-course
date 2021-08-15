#pragma once
#define MAX_LINE 81
#define CMD_NUM 27
#define GID_NUM 4
#define LABEL_MAX_LEN 31
#define MACH_CODE_SIZE 33
#define CMD_NAME 7

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
