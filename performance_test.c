#include "string_matching.h"
#include <time.h>
void performance_test(int N, int M){
  static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  srand(time(NULL));   // Initialization, should only be called once.
	//time_t start, nd;
  	//start = clock();
    	int n = N;    // Returns a pseudo-random integer between 3 and N.
        int m = M;

        char *text = malloc(n);
    	for (int i=0; i<n; i++){
        	int pos = rand() % (int)(sizeof(charset) -1);
      		text[i] = charset[pos];
    	}

        char *pattern = malloc(m);
    	for (int i=0; i<m; i++){
          	int pos = rand() % (int)(sizeof(charset) -1);
      		pattern[i] = charset[pos];
    	}

    	printf("text='%s', pattern='%s'\n", text, pattern);
	time_t start, end;
	int tn, tk;
	start = clock();
    	int result1 = string_matching_naive(text, n, pattern, m);
	end = clock();
	tn = start - end;
	start = clock();
    	int result2 = string_matching_kmp(text, n, pattern, m);
	end = clock();
	tk = start - end;
    	if (result1==result2){
      		printf("naive time: %d kmp time: %d\n", tn, tk);
		printf("OK\n");
	}
    	else {
      		printf("Wrong answer: correct=%d, got instead=%d\n", result1, result2);
          	exit(0);
        }
        free(text);
        free(pattern);
  
}

int main(int argc, char **argv ){
   int N = atoi(argv[1]);
   int M = atoi(argv[2]);

   performance_test(N, M);

   return 0;
}

