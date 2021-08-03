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
int read_line(FILE *fd,char p[81],int line_num){
	int i = 0;
	char c = fgetc(fd);
	while(c != '\n' && (!feof(fd))){
        p[i] = c;
        i++;
        c = fgetc(fd);
    }
	p[i] = '\n';
	if(i > (MAX_LINE_SIZE-1)){
		printf("ERROR - line : %d - line bigger then 80",line_num);
		return 1;
	} 
	return 0;
}
//skip a line.
int next_line(FILE *fd,int line_num){
	int i = 1;
	while(!feof(fd) && fgetc(fd) != '\n')i++;
	if(i > MAX_LINE_SIZE){
		printf("ERROR - line : %d - line bigger then 80",line_num);
		return 1;
	}
	return 0;
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
			while(((c = fgetc(fd)) == ' ' || c =='\t') && (!feof(fd)));
			if(c == ';'){
				line_num++;
				next_line(fd,line_num);
				break;
			}
			if (c == '\n' || feof(fd))
			{
				line_num++;
				break;
			}
			fsetpos(fd,&pos);
			read_line(fd,p,line_num);
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
		if(lable_table[i].need_called != 'N'){
			if((lable_table[i].need_called != lable_table[i].called) && (lable_table[i].called != 'y')){
				j = 0;
				while(j < lable_table[i].line_size){
					printf("ERROR - line : %d -lable wasn't called - %s\n",lable_table[i].line[j],lable_table[i].name);
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