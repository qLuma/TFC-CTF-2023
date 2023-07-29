#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void win(){
	system("/bin/sh");
}

void setup(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int v[10], input[10];
int main(){
	setup();

	srand((unsigned int) time(NULL));
	for (int i=0; i<=9; i++)
		v[i] = rand();

	puts("Guess my numbers!");
	for (int i=0; i<=9; i++){
		scanf("%d", &input[i]);
	}

	for (int i=0; i<=9; i++)
		if (v[i] != input[i]){
			puts("You didn't make it :(");
			exit(0);
		}
	win();
	return 0;
}
