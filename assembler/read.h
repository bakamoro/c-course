#ifndef READ
#define READ
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE_SIZE 81
#define MAX_WORD_SIZE 81

/*check if the string is liglle number
*@param s - the string taht the function check
*@param file_name - the name of the current file
*@param line_number - the number of the current line
*@param bit - the limit of the possible number of bits
*/
int number_check(char s[],char file_name[],int line_number,int bit);

/*
*read word from line
*accept a line and an index and a char array and put the word from the index to the array char.
*@param p - the line 
*@param p3 - the char array
*@param i - the index
*/
int bilt_array(char p[],char p3[],int i);

/*
*check if the line from the index and further is empty
*@param line - the line
*@param index - the index
*/
int check_rest_of_line(char line[MAX_LINE_SIZE],int index);

/*
*check that the register is legal
*@param op - the register that the check
*@param file_name - the name of the current file
*@param line_number - the number of the current line
*/
int operand_chack(char * op,char file_name[],int line_num);

/*
*comper betwin two words
*@param word1 - the fist word to comper
*@param word2 - the secand word yo comper
*/
int comper_words(char *word1,char *word2);

/*
*check if the string is legal
*@param string - the string that the functuion checking/
*/
int string_check(char *string);

/*
*power the number
*@param num - The number you power
*@param po - the number that you power with
*/
double power(int num,int po);

/*
*eccept two files and put in the first one the inside of the secand file without extra spaces.
*@param file_name - the file that eccept the inside of the the other file
*@param FILE_NAME - the file that beenig copied
*/
void subtract_space(char file_name[],char FILE_NAME[]);

#endif