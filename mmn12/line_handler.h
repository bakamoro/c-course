#ifndef LINE_HANDLER
#define LINE_HANDLER
int in_comands_R(char word[]);
int in_comands_I(char word[]);
int in_comands_J(char word[]);
int in_instructions_1(char word[]);
int main_line(char *line,char *label,char file_name[],int line_num,int index,int a);
#endif