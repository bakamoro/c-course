#ifndef READ
#define READ
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE_SIZE 81
#define MAX_WORD_SIZE 81
int number_check(char s[],int line_number);
int bilt_array(char p[],char p3[],int i);
int check_rest_of_line(char line[MAX_LINE_SIZE],int index);
int operand_chack(char * op,int line_num);
int comper_words(char *label1,char *label2);
int operand_chack_binnar(char op[4]);
#endif