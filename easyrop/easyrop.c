#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int get_index(){
	unsigned int index;
	fputs("Select index: ", stdout);
	scanf("%d", &index);
	if (index % 3 == 0){
		puts("Nope! Can't give u that one!");
		exit(0);
	}
	return index;
}

int get_number(){
	uint32_t number;
	fputs("Select number to write: ", stdout);
	scanf("%d", &number);
	return number;
}

void setup(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

//gcc easyrop.c -o easyrop -no-pie
void main(void){
	setup();
	uint32_t buffer[125] = {0};
	while (69 == 69){
		unsigned int choice;
		uint32_t number = 0, index = 0;

		puts("Welcome to easyrop!");
		puts("Press '1' to write and '2' to read!");
		scanf("%d", &choice);
		if (choice == 1){
			index = get_index();
			number = get_number();
			buffer[index] = number;
		}
		else if (choice == 2){
			index = get_index();
			printf("The number at index %d is %x\n", index, buffer[index]);
		}
		else{
			puts("Bye :(");
			break;
		}
	}
}
