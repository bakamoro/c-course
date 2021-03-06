#ifndef LABLE_HUNDLER
#define LABLE_HUNDLER
#define MAX_LABLE_SIZE 31
size_t index_lable;
typedef struct lablea
{
    char name[MAX_LABLE_SIZE];
    char called;
    char need_called;
    int *line;
    int line_size;
}lable;
lable * lable_table;
int legal_label(char *name,char file_name[],int line_num,char start_line);
int search_lable(char name[],char called,char need_called,int line_num);
void add_lable(char *name,char called,char need_called,int index,int line_num);
int find_label(char name[]);
#endif
