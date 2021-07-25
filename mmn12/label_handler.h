#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LABLE_SIZE 31
static int index_lable = 0;
typedef struct lable
{
    char name[MAX_LABLE_SIZE];
    char called;
    char ex;
    int *line;
}lable;
const int size = sizeof(lable);
static lable * lable_table = malloc(size);
int legal_label(char *name,int line_num){
    int i = 0,j = 0;
    if ((name[0] < 65 || name[0] > 122) || (name[0] > 90 && name[0] < 97))
    {
        printf("ERROR - line : %d - illegal label",line_num);
        return 0;
    }
    if(strlen(name) > MAX_LABLE_SIZE){
        printf("ERROR - line : %d - illegal label",line_num);
        return 0;
    }
    while(i<strlen(name)){
        if(!isdigit(name[i]) && ((name[i] < 65 || name[i] > 122) || (name[i] > 90 && name[i] < 97))){
            printf("ERROR - line : %d - illegal label",line_num);
            return 0;
        }
        i++;
    }
    if (name[strlen(name)-1] != ':')
    {
        printf("ERROR - line : %d - illegal label",line_num);
        return 0;
    }
    
    return 1;
}
int search_lable(char *name){
    int i = 0;
    while (i < index_lable)
    {
        if(*name == lable_table[i].name){
            realloc(lable_table->line,sizeof(int));
            return 1;
        }
    }
    return 0;
}
void add_lable(char *name,char called,int index,int line_num){
    realloc(lable_table,sizeof(lable));
    static lable temp;
    name[strlen(name)-1] = '\0';
    temp.line = malloc(sizeof(int));
    temp.line[0] = line_num;
    temp.name = name;
    temp.called = called;
    lable_table[index] = temp;
}