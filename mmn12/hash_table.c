#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct struct_comand_R {
	char *name;
	int num_of_op;
}comand_R;

comand_R arr_comand_R[8];

typedef struct comand_I {
        char *name;
        int num_of_op;
		int hoarder;
		int im;
}comand_I;

typedef struct comand_J {
        char *name;
        int num_of_op;
}comand_J;
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
comand_I bilt_comand_I(char s[],int num_of_op,int hoarder,int im,int label){
	comand_I temp;
	temp.name = s;
	temp.num_of_op = num_of_op;
	temp.im = im;
	temp.hoarder = hoarder;
	return temp;
}
/*
comand_I * bilt_array_I(char * s[]){
	int i = 0,num_of_op = 3,hoarder = 2,im =1,label = 0;
	static comand_I arr_comand_I [15];
	while(i<15){
		if(i == 6){
			im = 0;
			label = 1;
		}
		if()
		arr_comand_I[i] = bilt_comand_I(s[i],num_of_op,hoarder,im,label);
		i++;
	}
	return arr_comand_I;
}
*/
comand_J * bilt_array_I(char * s[]){
	int i = 0;
	static comand_J arr_comand_J[4];
	while(i<4){

	}
}
int main_hash()
{
	
	char * comands_I[15] = {"addi","subi","andi","ori","nori","bne","beq","blt","bgt","lb","sb","lw","sw","lh","sh"};
	char * comands_J[4] = {"jmp","la","call","stop"};
	
	//comand_I * arr_comand_I = bilt_array_I(comands_I);
	
}