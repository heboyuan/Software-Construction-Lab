#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int num, char* arg[]){
	if(num != 3)
	{
		fprintf(stderr, "Error: Can only handle 2 arguments");
		exit(1);
	}


	if(strlen(arg[1]) != strlen(arg[2]))
	{
		fprintf(stderr, "Error: Input string must be same length");
		exit(1);
	}

	int x, y;
	for (x = 0; x < strlen(arg[1]); x++)
		for(y = 0; y < strlen(arg[2]); y++)
			if(arg[1][x] == arg[1][y]){
				fprintf(stderr, "Error: First argument cannot contain duplicate words");
				exit(1);
			}
	
	int t = 0;
	char b = getchar();
	while(b != EOF){
		for(x = 0; x < strlen(arg[1]); x++){
			if(arg[1][x] == b){
				putchar(arg[2][x]);
				t = 1;
				break;
			}
		}
		if(!t)
			putchar(b);
		b = getchar();
	}
	return 0;
}
