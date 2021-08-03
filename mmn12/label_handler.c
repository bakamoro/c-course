#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read.h"
#define MAX_LABLE_SIZE 31
int index_lable = 0;
typedef struct lablea
{
    char name[MAX_LABLE_SIZE];
    char called;
    char need_called;
    int *line;
    int line_size;
}lable;
lable * lable_table;
int legal_label(char *name,char file_name[],int line_num,char start_line){
    int i = 1;
    if ((name[0] < 65 || name[0] > 122) || (name[0] > 90 && name[0] < 97))
    {
        printf("ERROR - file : %s - line : %d - illegal label not start with a letter : %s\n",file_name,line_num,name);
        return 0;
    }
    if(start_line == 'y'){
        if(strlen(name)-1 > MAX_LABLE_SIZE){
            printf("ERROR - file : %s - line : %d - illegal label : to many letters : %s\n",file_name,line_num,name);
            return 0;
        }
    }

    else if(strlen(name) > MAX_LABLE_SIZE){
        printf("ERROR - file : %s - line : %d - illegal label : to many letters : %s\n",file_name,line_num,name);
        return 0;
    }
    while(i<strlen(name) && name[i] != '\n'){
        if(start_line == 'y'){
            if(i == strlen(name)-1){
                return 1;
            }
        }
        if((!isdigit(name[i])) && ((name[i] < 65 || name[i] > 122) || (name[i] > 90 && name[i] < 97))){
            printf("ERROR - file : %s - line : %d - illegal label : %s\n",file_name,line_num,name);
            return 0;
        }
        if(name[i] != '\0' && name[i] != '\n'){
            return 1;
        }
        i++;
    }
    if(start_line == 'y'){
        if (name[strlen(name)-1] != ':')
        {
            printf("ERROR - file : %s - line : %d - illegal label : %s\n",file_name,line_num,name);
            return 0;
        }
    }
    return 1;
}
int search_lable(char name[],char need_called,int line_num){
    int i = 0;
    while (i < index_lable)
    {
        if(comper_words(name,lable_table[i].name)){
            lable_table[i].line = realloc(lable_table[i].line,sizeof(int));
            lable_table[i].line[lable_table[i].line_size] =  line_num;
            lable_table[i].line_size++;
            if(lable_table[i].need_called != 'N'){
                if(need_called == 'n')
                    lable_table[i].need_called = need_called;
            }
            if(i)
                return i;
            return 1;
        }
        i++;
    }
    return 0;
}
void add_lable(char *name,char called,char need_called,int index,int line_num){
    if(index_lable == 0){
       lable_table = malloc(sizeof(lable));
    }
    else {
        lable_table = reallocarray(lable_table,sizeof(lable),index_lable+1);
    }
    static lable temp;
    name[strlen(name)-1] = '\0';
    temp.line = malloc(sizeof(int));
    temp.line[0] = line_num;
    temp.line_size = 1;
    strcpy(temp.name,name);
    temp.called = called;
    temp.need_called = need_called;
    lable_table[index] = temp;
    index_lable++;
}
