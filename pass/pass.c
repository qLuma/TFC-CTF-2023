#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct crflag{
	char dump[26][30];
}flag;

char encrypt(char ch){

	if (ch == '{' || ch == '}'){
    	ch = 'Z';
    	return ch;
	}
	ch = ch + 7;
  ch = ch ^ 0x0b;
  return ch;
}


void set_flag(){
strcpy(flag.dump[0], "PziP97vkc5sA6oJM0KwWEnQX2ltd");
strcpy(flag.dump[1], "OFaH0nAFTuS42myr31GYbJIfBKqV");
strcpy(flag.dump[2], "SdAFWsLpx8N0v4PzO7aIVQaHrLw9");
strcpy(flag.dump[3], "Vq6AW8c1K5ZyFXzMeRAOiJ2nWQSo");
strcpy(flag.dump[4], "XYy2Pj7x96RzkcA3inNqlDOBLfF0");
strcpy(flag.dump[5], "KZ4rNFYGTn0Cl5U9aX2WIH1cOsdL");
strcpy(flag.dump[6], "yIbm2AZ0k31u7FrxBECKPpMhYG5w");
strcpy(flag.dump[7], "VUyvA5LfgXcW9eDSMTBlsorR2z4Y");
strcpy(flag.dump[8], "2laXN3e8<qSCmwK0Do9bJzYvdkE6");
strcpy(flag.dump[9], "5YgG3dRBhwMvOp2qS08UWQKtL1Py");
strcpy(flag.dump[10], "QbphJTXLd2~fktr45ES7OK3x0as9");
strcpy(flag.dump[11], "yNqu1XSC9nA`rGpBvQlbDktjI4aZ");
strcpy(flag.dump[12], "xLm2KlVYnXw0mpt5aOe8B4grGRjF");
strcpy(flag.dump[13], "XFe06gaZv3PYdpS4CDquJnmkRhVW");
strcpy(flag.dump[14], "1Mn6sKScF3vV7pdzYfTkBRbqGZ9C");
strcpy(flag.dump[15], "bzu2wtPHkXsx1pK14ojTfJYIeRWA");
strcpy(flag.dump[16], "0PpU1TjDKaW85uZ2mlFHYMSEkcQJ");
strcpy(flag.dump[17], "BvKo6WIdTnVRewMPk|3pU1SjN6Gl");
strcpy(flag.dump[18], "ErN7s0HYlp9tMqAmBh0dXD4VaU6u");
strcpy(flag.dump[19], "K8NZWU1fnrsQaEc5Bht09eHwxYDK");
strcpy(flag.dump[20], "DSpWj0ahd5rtIzyKETxUq9CkXQVm");
strcpy(flag.dump[21], "C8DAP37Kc1UqOvdb2GT0Yvxuhz5Q");
strcpy(flag.dump[22], "1grzfdR4JiVpo83QOEWlL2<BtcD0");
strcpy(flag.dump[23], "9Xm7Q5RNkljfOZogB8ctIzyrapVh");
strcpy(flag.dump[24], "9wF0RKycTJjvZfDlm6o75QsG`OL4");
strcpy(flag.dump[25], "2laXN3e85qSCmwK0Do9bJzYvdZE6");

}

int increment(unsigned int i)
{
    i = -(~i);
 
    return i;
}

int main(){
	set_flag();

	char input[28];
	fgets(input, 27, stdin);
	printf("Password entered: %s\n", input);

	unsigned int i = 0;
	while(1==1){
		char ch;
		ch = encrypt(input[i]);
		if (ch != flag.dump[i][i]){
			printf("Wrong password\n");
			exit(0);
		}
		i = increment(i);
		if (i == 25)
			break;
	}
	printf("Correct password\n");
	exit(0);

}
