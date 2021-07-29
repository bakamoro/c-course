#include <stdio.h>
#include "read.h"
#include "label_handler.h"
//
void instructions_2(char line[81],char instruction[],int line_num,int index){
    char label[MAX_LABLE_SIZE];
    int num_of_pa = 0;
    int i = 0;
    while(check_rest_of_line(line,index)){
        index = bilt_array(line,label,index);
        num_of_pa++;
        if(num_of_pa == 2){
            printf("ERROR - LINE : %d - TO MANY PARAMETERS\n",line_num);
            return;
        }
        if(legal_label(label,line_num,'n')){
            if((i = search_lable(label,line_num))){
                lable_table[i].called = 'y';
                if(instruction == ".extern"){
                    lable_table->ex = 'y';
                }
                else lable_table->ex = 'n';
            }
            add_lable(label,'y',index_lable,line_num);
        }
    }
    if(num_of_pa == 0){
        printf("ERROR - LINE : %d - TO FEW PARAMETERS\n ",line_num);
        return;
    }
}
void instructions_1(char word[]){

}