#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "line_handler.h"
#include "label_handler.h"
#define MAX_LINE_SIZE  81
extern int index_lable;
//make a line from array of chasrs
void read_line(FILE *fd,char p[81]){
	int i = 0;
	char c = fgetc(fd);
	while(c != '\n' && (!feof(fd))){
            p[i] = c;
            i++;
            c = fgetc(fd);
        }
	p[i] = c;
}
//check if the string is liglle number.
int number_check(char s[],int line_number){
	int i = 0;
	while(i < strlen(s)){
		if(s[i] == '.'){
			printf("ERROR - line : %c - the asembler does not support decimal numbers\n",line_number);
			return 0;
		}
		if(!(isdigit(s[i]))){
			return 0;
		}
		i++;
	}
}
//skip a line.
void next_line(FILE *fd){
	while(fgetc(fd) != '\n');
}
void main_check(char s[]){
	FILE *fd = fopen(s,"r");
	fpos_t pos;
	char c;
	char *p;
	int line_num = 1;
	int i = 0,j = 0;
	if(fd == NULL){
		printf("ERROR - can't open the file - %s\n",s);
		exit(0);
	}
	while(!feof(fd)){
		while(!feof(fd)){
			p = malloc(MAX_LINE_SIZE);
			fgetpos(fd,&pos);
			if(fgetc(fd) == ';'){
				next_line(fd);
				line_num++;
				fgetpos(fd,&pos);
				break;
			}
			fsetpos(fd,&pos);
			while((c = fgetc(fd)) == ' ' || c =='\t' && (!feof(fd)));
			if (c == '\n' || feof(fd))
			{
				line_num++;
				break;
			}
			fsetpos(fd,&pos);
			read_line(fd,p);
			//לשלוח לפונקציה מקובץ אחר לא לשכוח לשלוח את מספר השורה.
			char *la;
			int a = main_line(p,la,line_num,0,0);
			if (!(a))
			{
				printf("ERROR - LINE NUMBER : %d - NO INSTRUCTUON OR COMAND FOUND\n",line_num);
			}
			free(p);
			line_num++;
		}
	}
	//chcking that all the labels are called.
	//lable * lable_table2 = get_lable_table();
	while(i < index_lable){
		if(lable_table[i].called == 'n'){
			j = 0;
			while(j < lable_table->line_size){
				printf("ERROR - LINE : %d - UNDIFIND LABLE - %s\n",lable_table->line[j],lable_table->name);
				j++;
			}
		}
		i++;
	}
	fclose(fd);
}
int main(){
	main_check("ps.as");
	printf("finish\n");
}
