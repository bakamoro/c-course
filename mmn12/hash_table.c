#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct comand_R {
	char *name;
	int num_of_op;
}comand_R;

typedef struct comand_I {
        char *name;
        int num_of_op = 3;
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
	static comand_R arr_comand_R [88888888];
	while(i<strlen(*s)){
		arr_comand_R[i] = bilt_comand_R(s[i],a);
		i++;
		if (i == 4)
			a = 2;
	}
	return arr_comand_R;
}
comand_I bilt_comand_I(char s[]){
	comand_I temp;
	temp.name = s;
	return temp;
}
comand_I * bilt_array_I(char * s[]){
	int i = 0;
	static comand_I arr_comand_I [15];
	while(i<strlen(*s)){
		arr_comand_I[i] = bilt_comand_I(s[i]);
		i++;
	}
	return arr_comand_I;
}
int main()
{
	char * comands_R[8] = {"add","sub","and","or","nor","move","mvhi","mvlo"};
	char * comands_I[15] = {"addi","subi","andi","ori","nori","bne","beq","blt","bgt","lb","sb","lw","sw","lh","sh"};
	char * comands_J[4] = {"jmp","la","call","stop"};
	comand_R * arr_comand_R = bilt_array_R(comands_R);
	comand_I * arr_comand_I = bilt_array_I(comands_I);

}
