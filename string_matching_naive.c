#include "string_matching.h"
#include <string.h>
int string_matching_naive(char *text, int N, char* pattern, int M){
	int found = 0;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			if(text[i + j] != pattern[j]){
				break;
			}
			else if(j == M - 1){
				found++;
				break;
			}
		}
	}
	return found;
}

/*int main(){
	char * str = malloc(15);
	strcpy(str, "abcdeabc");
	char * p = malloc(5);
	strcpy(p, "abc");
	int i = string_matching_naive(str, 8, p, 3);
	printf("%d\n", i);
	free(str);
	free(p);
}*/
