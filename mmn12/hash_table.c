#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct struct_comand_R {
	char *name;
	int num_of_op;
}comand_R;

comand_R arr_comand_R[8];

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

typedef struct struct_comand_I {
        char *name;
        int num_of_op;
		char operands_type[3];
}comand_I;

comand_I arr_comand_I[15];

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

typedef struct struct_comand_j {
        char *name;
        int num_of_op;
		char type_1;
		char type_2;
}comand_J;

comand_J arr_comand_j[4];

comand_J bilt_comand_J(char name[],int num_of_op,char type_1,char type_2){
	comand_J temp;
	temp.name = name;
	temp.num_of_op = num_of_op;
	temp.type_1 = type_1;
	temp.type_2 = type_2;
	return temp;
}
comand_J * bilt_array_J(char * comands_J[]){
	static comand_J arr_comand_I [4];
	arr_comand_j[0] =  bilt_comand_J(comands_J[0],1,'l','r');
	arr_comand_j[1] =  bilt_comand_J(comands_J[1],1,'l','N');
	arr_comand_j[2] =  bilt_comand_J(comands_J[2],1,'l','N');
	arr_comand_j[3] =  bilt_comand_J(comands_J[3],0,'N','N');
	return arr_comand_j;
}