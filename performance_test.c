#include "string_matching.h"
#include <sys/time.h>
void print_array(int *arr, int size){
  for (int i=0; i<size; i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
}
int string_matching_naive(char *text, int N, char* pattern, int M){
        pattern[M] = '\0';
        int found = 0;
        for(int i = 0; i < N; i++){
                for(int j = 0; j < M; j++){
                        if(i + j >= N)
                                break;
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
int * overlap_array(char* pattern, int M){
        int *ol_list = calloc(M, sizeof(int));

    int pos = 1;  // first is always zero
    while (pos < M){
        int ol_prev = ol_list[pos - 1];

        if (pattern[pos] == pattern[ol_prev])
            ol_list[pos] = ol_prev + 1;
        else {
            int found = 0;
            int j = ol_prev;
            int curr_overlap = ol_prev;
            while (!found && j >= 1){
                if (pattern[pos] == pattern[j]){
                    found = 1;
                    ol_list[pos] = curr_overlap + 1;
                                }
                else {// try extend a smaller prefix - based on pattern [ol[pos-1]]
                    curr_overlap = ol_list[j-1];
                    j = ol_list[j-1];
                                }
                        }
            if (!found) { // compare with the first
                if (pattern[pos] == pattern[0])
                    ol_list[pos] = 1;
                        }
                }
        pos++;
        }
    return ol_list;
}
int string_matching_kmp(char *text, int N, char* pattern, int M){
        int count = 0;
        int *overlap_list = overlap_array(pattern, M);
        printf("overlap function: ");
        print_array(overlap_list,M);

        //TODO - implement kmp search
        //        pattern[M] = '\0';
	int i = 0;
        int j = 0;
        while (i < N) {
                if (pattern[j] == text[i]) {
                        j++;
                        i++;
                }
                if (j == M) {
                         count++;
                         j = overlap_list[j - 1];
                }

                else if ((i < N) && pattern[j] != text[i]) {
                        if (j != 0)
                                j = overlap_list[j - 1];
                        else
                                i = i + 1;
                }
        }
        free(overlap_list);
        return count;
}


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
	struct timeval start, end;
	double tn, tk;
	gettimeofday(&start, NULL);
    	int result1 = string_matching_naive(text, n, pattern, m);
	gettimeofday(&end, NULL);
	tn = (double)(end.tv_usec - start.tv_usec);
	gettimeofday(&start, NULL);
    	int result2 = string_matching_kmp(text, n, pattern, m);
	gettimeofday(&end, NULL);
	tk = (double)(end.tv_usec - start.tv_usec);
    	if (result1==result2){
      		printf("naive time: %f kmp time: %f\n", tn, tk);
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

