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
int read_line(FILE *fd,char p[81],char file_name[],int line_num){
	int i = 0;
	char c = fgetc(fd);
	while(c != '\n' && (!feof(fd))){
        p[i] = c;
        i++;
        c = fgetc(fd);
    }
	p[i] = '\n';
	if(i > (MAX_LINE_SIZE-1)){
		printf("ERROR - file : %s - line : %d - line bigger then 80",file_name,line_num);
		return 1;
	}
	return 0;
}
//skip a line.
int next_line(FILE *fd,char file_name[],int line_num){
	int i = 1;
	while(!feof(fd) && fgetc(fd) != '\n')i++;
	if(i > MAX_LINE_SIZE){
		printf("ERROR - file : %s - line : %d - line bigger then 80",file_name,line_num);
		return 1;
	}
	return 0;
}
void main_check(char file_name[]){
	FILE *fd = fopen(file_name,"r");
	fpos_t pos;
	char c;
	char *p;
	int line_num = 1;
	int i = 0,j = 0;
	if(fd == NULL){
		printf("ERROR - can't open the file - %s\n",file_name);
		exit(0);
	}
	while(!feof(fd)){
		while(!feof(fd)){
			p = malloc(MAX_LINE_SIZE);
			fgetpos(fd,&pos);
			while(((c = fgetc(fd)) == ' ' || c =='\t') && (!feof(fd)));
			if(c == ';'){
				line_num++;
				next_line(fd,file_name,line_num);
				break;
			}
			if (c == '\n' || feof(fd))
			{
				line_num++;
				break;
			}
			fsetpos(fd,&pos);
			read_line(fd,p,file_name,line_num);
			//לשלוח לפונקציה מקובץ אחר לא לשכוח לשלוח את מספר השורה.
			char *la;
			int a = main_line(p,la,file_name,line_num,0,0);
			if (!(a))
			{
				printf("ERROR - file : %s - line : %d - NO INSTRUCTUON OR COMAND FOUND\n",file_name,line_num);
			}
			free(p);
			line_num++;
		}
	}
	//chcking that all the labels are called.
	while(i < index_lable){
		if(lable_table[i].need_called != 'N'){
			if(lable_table[i].need_called == 'n' && lable_table[i].called != 'n'){
				j = 0;
				while(j < lable_table[i].line_size){
					printf("ERROR - file : %s - line : %d -lable isn't entry - %s\n",file_name,lable_table[i].line[j],lable_table[i].name);
					j++;
				}
			}
			if(lable_table[i].need_called == 'x' && lable_table[i].called != 'N'){
				j = 0;
				while(j < lable_table[i].line_size){
					printf("ERROR - file : %s - line : %d -lable isn't entry / external - %s\n",file_name,lable_table[i].line[j],lable_table[i].name);
					j++;
				}
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