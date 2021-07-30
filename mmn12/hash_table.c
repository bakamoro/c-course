#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct struct_comand_R {
	char *name;
	int num_of_op;
}comand_R;

comand_R arr_comand_R[8];

typedef struct struct_comand_I {
        char *name;
        int num_of_op;
		char operands_type[3];
}comand_I;

comand_I arr_comand_I[15];

typedef struct struct_comand_J_1 {
        char *name;
        int num_of_op;

}comand_J_1;
comand_R bilt_comand_R(char s[],int a){
	comand_R temp;
	temp.name = s;
	temp.num_of_op = a;
	return temp;
}
comand_R * bilt_array_R(char * s[]){
	int i = 0,a = 3;
	static comand_R arr_comand_R [8];
	while(i<8){
		arr_comand_R[i] = bilt_comand_R(s[i],a);
		i++;
		if (i == 4){
			a = 2;
		}
	}
	return arr_comand_R;
}
comand_I bilt_comand_I(char s[],int num_of_op,char i_0,char i_1,char i_2){
	comand_I temp;
	temp.name = s;
	temp.num_of_op = num_of_op;
	temp.operands_type[0] = i_0;
	temp.operands_type[1] = i_1;
	temp.operands_type[2] = i_2;
	return temp;
}

comand_I * bilt_array_I(char * s[]){
	int i = 0,num_of_op = 3;
	char type_lable = 'l',type_hoarder = 'h',type_number = 'n';
	static comand_I arr_comand_I [15];
	while(i<15){
		if(i < 11){
			arr_comand_I[i] = bilt_comand_I(s[i],num_of_op,type_hoarder,type_number,type_hoarder);
		}
		else{
			arr_comand_I[i] = bilt_comand_I(s[i],num_of_op,type_hoarder,type_hoarder,type_lable);
		}
		i++;
	}
	return arr_comand_I;
}
/*
comand_J * bilt_array_J(char * s[]){
	int i = 0;
	static comand_J arr_comand_J[4];
	while(i<4){

	}
}
*/
int main_hash()
{
		char * comands_J[4] = {"jmp","la","call","stop"};
	
	//comand_I * arr_comand_I = bilt_array_I(comands_I);
	
}