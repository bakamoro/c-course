#ifndef HASH_TABLE
#define HASH_TABLE
typedef struct struct_comand_R {
	char *name;
	int num_of_op;
}comand_R;

comand_R arr_comand_R[8];

typedef struct comand_I {
        char *name;
        int num_of_op;
}comand_I;

typedef struct comand_J {
        char *name;
        int num_of_op;
}comand_J;
comand_R bilt_comand_R(char s[],int a);
comand_R * bilt_array_R(char * s[]);
comand_I bilt_comand_I(char s[]);
comand_I * bilt_array_I(char * s[]);
int main_hash();
#endif