#pragma once
/*read line*/
int read_line(FILE *fd,char p[81],char file_name[],int line_num);

/*skip a line*/
int next_line(FILE *fd,char file_name[],int line_num);

/*get file -> open it read a line -> sent the line to another function to handle and does it again until reach the end of file -> if there is error return 1*/
int main_check(char file_name[]);
