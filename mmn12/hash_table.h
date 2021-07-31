#ifndef HASH_TABLE
#define HASH_TABLE
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

typedef struct struct_comand_j {
        char *name;
        int num_of_op;
        char type_1;
        char type_2;
}comand_J;

comand_J arr_comand_j[4];

comand_R bilt_comand_R(char s[],int a);

comand_R * bilt_array_R(char * s[]);

comand_I bilt_comand_I(char s[],int num_of_op,char i_0,char i_1,char i_2);

comand_I * bilt_array_I(char * s[]);

comand_J bilt_comand_J(char name[],int num_of_op,char type_1,char type_2);

comand_J * bilt_array_J(char * comands_J[]);

#endif