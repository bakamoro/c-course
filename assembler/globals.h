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



