#include <stdio.h>
#include "read.h"
#include "label_handler.h"
#include "hash_table.h"
int instructions_2(char line[81],char instruction[],int line_num,int index){
    int error = 0;
    char label[MAX_LABLE_SIZE];
    int num_of_pa = 0;
    int i = 0;
    while(check_rest_of_line(line,index)){
        index = bilt_array(line,label,index);
        num_of_pa++;
        if(num_of_pa == 2){
            printf("ERROR - LINE : %d - TO MANY PARAMETERS\n",line_num);
            return 1;
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
        return 1;
    }
}
void instructions_1(char word[]){

}
//
int incomand_R(char line[81],char comand_name[],int line_num,int index){
    int i = 0;
    int hoarder_num = 0;
    char ho[4];
    char * comands_R[8] = {"add","sub","and","or","nor","move","mvhi","mvlo"};
    comand_R * arr_comand_R = bilt_array_R(comands_R);
    while(check_rest_of_line(line,index) && hoarder_num < 4){
        index = bilt_array(line,ho,index);
        if(!operand_chack(ho,line_num)){
            return 1;
        }
        hoarder_num++;
    }
    if(hoarder_num == 4){
        printf("ERROR - LINE : %d - to many oparends\n",line_num);
        return 1;
    }
    while(!comper_words(comand_name,arr_comand_R[0].name)){
        i++;
    }
    if(arr_comand_R[i].num_of_op > hoarder_num){
        printf("ERROR - LINE : %d - to many oparends\n",line_num);
        return 1;
    }
    if(arr_comand_R[i].num_of_op < hoarder_num){
        printf("ERROR - LINE : %d - to few oparends\n",line_num);
        return 1;
    }
    return 0;
}