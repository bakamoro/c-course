#ifndef LABLE_HUNDLER
#define LABLE_HUNDLER
#define MAX_LABLE_SIZE 31
int index_lable;
typedef struct lablea
{
    char name[MAX_LABLE_SIZE];
    char called;
    char ex;
    int *line;
    int line_size;
}lable;
lable * lable_table;
int legal_label(char *name,int line_num);
int search_lable(char name[],int);
void add_lable(char *name,char called,int index,int line_num);
#endif