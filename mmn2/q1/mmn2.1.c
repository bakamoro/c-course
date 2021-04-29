#include <stdio.h>
#include <stdlib.h>
int buffer(char *p){
	char c;
	int i = 0;
	printf("please write your text\n");
	while((scanf("%c",&c)) != EOF && p != NULL){
		if(c != "\n"){
			p[i] = c;
			++i;
			if(i%60 == 0)
				realloc(p,60*sizeof(char));
		}
	}
	return i;
}
void linked_list(Item node){
	
}
int readText(int a , char *p){
	if(a == 1){
                int j = buffer(p);
                if(p == NULL){
                        printf("\nERROR\n");
                        exit(0);
                }
		return j;
        }
        else{ 
                if(a == 2){
			linked_list();
                }
                else printf("\nERROR you didn't entered 1 or 2\n");
        }
	return 1;
}
void print_buffer(char *p,int j){
	int i = 0;
	printf("\nyou wrote : ");
	while(p[i] != EOF && i<j){
		printf("%c",p[i]);
		i++;
		if((i % 60) == 0)
			printf("\n");
	}
	printf("\n");
	return;
}

void print_linked_list(){

}

void printText(int a,int j,char *p){
	if(a == 1)
		print_buffer(p , j);
	if(a == 2)
		print_linked_list();	
}

void main (){
	printf ("Please select the desired database type:\nfor a buffer : enter 1\nfor a linked list : enter 2\n");
	int a;
	scanf("%d",&a);
	char *p;
	if(a == 1){
		p = (char *)calloc(60,sizeof(char));
		if(!p){
                        printf("ERROR\n");
                        exit(0);
                }
	}
	if(a == 2){
	
	}
	readText(a,*p)
	printText(a,j,p);
}
