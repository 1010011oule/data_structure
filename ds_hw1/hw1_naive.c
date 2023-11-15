#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 10000000
#define MAX_PAT 3000

char str[MAX_STR];
char pat[MAX_PAT];
int size_str = 0;
int size_pat = 0;

void print(FILE*, int*);

int main(void){
	FILE* fp_str = fopen("string.txt", "r");
	FILE* fp_pat = fopen("pattern.txt", "r");
	FILE* fp_res = fopen("result_naive.txt", "w");

	if( !fp_str ){
		printf("string file doesnt exist.\n");
		return 0;
	}
	if( !fp_pat ){
		printf("pattern file doesnt exist.\n");
		return 0;
	}
	fgets(str, MAX_STR, fp_str);
	fgets(pat, MAX_PAT, fp_pat);
	
	size_str = strlen(str);
	size_pat = strlen(pat);
	int i = 0, j = 0;
	int index = 0;
	int* result = (int*)malloc(sizeof(int));
	*result = 0;

	for(i = 0; i < size_str-size_pat+1; i++)
{
		for(j = 0; j < size_pat; j++){
			if( str[i+j] != pat[j] )
				break;
		}
		if( j == size_pat )	
{
			index++;
			result = (int*)realloc(result, (index+1) * sizeof(int));
			++result[0];
			result[index] = i;
		}
	}
	
	print(fp_res, result);

	fclose(fp_str);
	fclose(fp_pat);
	fclose(fp_res);
	free(result);

	return 0;
}


void print(FILE* fp, int* result){
	if( fp ){
		fprintf(fp, "%d\n", result[0]);
		for(int i = 1; i <= result[0]; i++)
			fprintf(fp, "%d ", result[i]);
	}
	fprintf(fp, "\n");
	printf("Completed!Result saved in result_naive.txt\n");
}

