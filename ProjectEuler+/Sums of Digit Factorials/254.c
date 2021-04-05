#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct testcase{
	int n;
	int m;

	struct testcase *next;
};

typedef struct testcase testcase;

struct record{
	int n; 
	int counter;
};
typedef struct record record;

record* inverse_f(record *curr_record, int quotient, record *min_record, int n){
	int factorial[9] = {1, 2, 6, 24, 120, 720, 5040, 40320, 3628800};

	printf("inverse f intro\n");
	//printf("%d\n", curr_record->n);
	if(curr_record->counter > min_record->counter){
		return min_record;
	}

	int x = 1, y = 0;
	while(x<10){

		y = curr_record->n - factorial[x-1];

		//if(curr_record->n == 101){
			//printf("%d\n", y);

		//}
		printf("%d %d\n", curr_record->n, curr_record->counter);

		if(y >= 0){
			(curr_record->counter)++;

			if(y > 0){
				curr_record->n = y;

				inverse_f(curr_record, x, min_record, n);
			}
			else{

				min_record->counter = curr_record->counter;
				min_record->n = n;

				printf("found you: %d %d\n", min_record->counter, min_record->n);

				return min_record;
			}
		}
		else{

			return min_record;
		}
		
		x++;
	}
}

int g(record *curr_record, record *min_record, int n, int quotient){
	printf("g intro\n");
	//printf("%d\n", n);

	int x = 0, y = 0, min_n = 1;
	while(x<10){

		y = n - x;

		//printf("=>%d %d %d\n",n, x, y);

		if(y%10 < 10){
			//printf("%d %d\n",x, y);
			curr_record->n = (100*quotient) + (10*x) + y;
			curr_record->counter = 0;

			min_record = inverse_f(curr_record, 0, min_record, curr_record->n);
		}

		if(y > 0 && x > 0){
			//printf("->%d %d\n", x, y);
			g(curr_record, min_record, y, (10*quotient)+x);
		}

		if(y == 0){
			//printf("->%d %d %d\n", n, x, y);

			return min_record->n;
			//break;
		}

				
		x++;

		//printf(".>%d %d %d\n", n, x, y);
	}

	min_n = min_record->n;

	//printf("end: %d %d %d\n", n, x, y);
	return min_n;
}
int sg(int i){
	//printf("sg intro\n");
	//printf("%d\n",i);
	record *min_record = (record*) malloc(sizeof(record));
	record *curr_record = (record*) malloc(sizeof(record));

	curr_record->n = 0;
	curr_record->counter = 0;

	min_record->n = 0;
	min_record->counter = 0;

	int n = g(curr_record, min_record, i, 0);

	int sum = 0;
	while((n%10) != 0){
		sum += n % 10;

		n /= 10;

		//printf("%d\n", sum);
	}
	free(min_record);
	free(curr_record);

	return sum;
}
int brain(int n){
	int sum = 0, i = 0;
	for(i = 1; i <= n; i++){
		sum += sg(i);
	}

	return sum;
}
int display(int n, int m){
	
	return (brain(n)%m);
}

int main(int argv, char *argc[]){
	int i=0, no_of_test = 0;
	fscanf(stdin, "%d",&no_of_test);

	testcase *thead, *prevt, *currt;
	for(i = 0; i < no_of_test; i++){
		
		currt = (testcase*) malloc(sizeof(testcase));
		
		fscanf(stdin, "%d",&(currt->n));
		fscanf(stdin, "%d",&(currt->m));

		currt->next = NULL;

		if(!i){
			thead = currt;
			prevt = currt;
			currt = NULL;

			continue;
		}

		prevt->next = currt;
		currt = NULL;
	}

	currt = thead;

	printf("Data read\n");
	for(i = 0; i < no_of_test; i++){

		fprintf(stdout, "%d", display(currt->n, currt->m));

		currt = currt->next;
	}


	return 0;
}
