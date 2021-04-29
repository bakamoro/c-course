#include <stdio.h>
#include <stdlib.h>
void buffer(char *p){
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
	return;
}
void linked_list(char *p){
	
}
void readText(int a , char *p){
	if(a == 1){
                *p = (char *)calloc(60,sizeof(char));
                if(!p){
                        printf("ERROR\n");
                        exit(0);
                }
                buffer(p);
                if(p == NULL){
                        printf("ERROR\n");
                        exit(0);
                }
        }
        else{ 
                if(a == 2){

                }
                else printf("ERROR you didn't entered 1 or 2\n");
        }
	return;
}
void print_buffer(char *p){
	int i = 0;
	printf("you wrote:\n");
	while(p[i] != EOF){
		printf("%c",p[i]);
		i++;
		if((i % 60) == 0)
			printf("\n");
	}
	return;
}

void print_linked_list(){

}

void printText(int a,char *p){
	if(a == 1)
		print_buffer(p);
	if(a == 2)
		print_linked_list();	
}

void main (){
	printf ("Please select the desired database type:\nfor a buffer : enter 1\nfor a linked list : enter 2\n");
	int a;
	char *p;
	scanf("%d",&a);
	readText(a,p);
	if(!p) 
		return;
	printText(a,p);
}
