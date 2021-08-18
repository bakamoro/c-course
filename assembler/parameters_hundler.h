#ifndef PARAMETER_HUNDLER
#define PARAMETER_HUNDLER
/*
*find the right instruction in instruction_2 and check that the number and typeof the parameters is correct
*@param line - the current line
*@param instruction - the name of the instruction that found in the line
*@param file_name - the name of the current file
*@param line_num - the number of the current line
*@param index - the index on line after the instruction
*/
int instructions_2(char line[81],char instruction[],char file_name[],int line_num,int index);

/*
*find the right insruction in instruction_1 and check that the number and type of the parameters is correct
*@param line - the current line
*@param comand_name - the name of the instruction that found in the line
*@param file_name - the name of the current file
*@param line_num - the number of the current line
*@param index - the index on line after the instruction
*/
int instructions_1(char line[81],char comand_name[],char file_name[],int line_num,int index);

/*
*find the right comand in comand_R and check that the number and type of the parameters is correct
*@param line - the current line
*@param comand_name - the name of the comand that found in the line
*@param file_name - the name of the current file
*@param line_num - the number of the current line
*@param index - the index on line after the instruction
*/
int incomand_R(char line[81],char comand_name[],char file_name[],int line_num,int index);

/*
*find the right comand in comand_I and check that the number and type of the parameters is correct
*@param line - the current line
*@param comand_name - the name of the comand that found in the line
*@param file_name - the name of the current file
*@param line_num - the number of the current line
*@param index - the index on line after the instruction
*/
int incomand_I(char line[81],char comand_name[],char file_name[],int line_num,int index);

/*
*find the right comand in comand_J and check that the number and type of the parameters is correct
*@param line - the current line
*@param comand_name - the name of the comand that found in the line
*@param file_name - the name of the current file
*@param line_num - the number of the current line
*@param index - the index on line after the instruction
*/
int incomand_J(char line[81],char comand_name[],char file_name[],int line_num,int index);
#endif