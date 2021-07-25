//make a word from array of chasrs
#define MAX_WORD_SIZE  81
int bilt_array(char p[],char p3[],int i){
	int j = 0;
    while(i < MAX_WORD_SIZE && p[i] == ' ' || p[i] == '\n' || p[i] == '\t'){
        i++;
    }
	while(i < MAX_WORD_SIZE && p[i] != ' ' && p[i] != '\n' && p[i] != '\t'){
		p3[j] = p[i];
		j++;
		i++;
	}
	if (p[i] == '\n')
	{
		p3[j] = p[i];
	}
	return i;
}