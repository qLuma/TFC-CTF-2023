#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void win(){
    system("/bin/sh");
}

struct leveling{
    int sane;
    int armed;
    char password[12];
    long int memory;
    char memories[40];
}leveling;

void sanity(){
    puts("\nI don't recognize you, answer some questions first.");
    sleep(1);
    int score = 0;
    int played = 0;
    char answers[4][50];
    while(1){
        puts("------------------------------");
        puts("[1] Answer my questions");
        puts("[2] Show your answers");
        puts("[3] See your score");
        puts("[4] Return");
        puts("------------------------------");
        printf("Choose: ");

        char choice[5] = {0};
        unsigned int number;
        fgets(choice, 5, stdin);
        number = atoi(choice);

        if (number == 1){
            for (int i=0; i < 2; i++)
                memset(answers[i], '\0', sizeof(answers[i]));
            printf("What is written on the Lab Members badge?\n");
            fgets(answers[0], 50, stdin);
            if (strcmp(answers[0], "OSHMKUFA 2010"))
                score += 1;
            
            printf("What is the name of Okabe's Laboratory?\n");
            fgets(answers[1], 50, stdin);
            if (strcmp(answers[1], "Future Gagdet Laboratory"))
                score += 1;
        
            printf("What is Mayuri's favorite hobby?\n");
            fgets(answers[2], 50, stdin);
            if (strcmp(answers[2], "Cosplay"))
                score += 1;
            printf("Is Ruka a boy or girl?\n");
            fgets(answers[3], 50, stdin);
            if (strcmp(answers[3], "It depends on the timeline"))
                score += 1;

            leveling.armed = 1;
            puts("I think l remember you a bit now...");
        }
            
        else if (number == 2 && played != 1){
            puts("You didn't even start the game...");
            exit(0);
        }
        
        else if (number == 3){
            played = 1;
            printf("Your score is: %d \n", score);
        }

        else if (number == 2 && played == 1){
            puts("These are your answers: ");
            for (int i = 0; i <= 3; i++)
                printf("%s\n", answers[i]);
        }
        else
            break;

    }
}

void print_current_password(){
    leveling.sane = 1;
    puts("You aren't sane anymore... Your password is: ");
    printf("%s\n", leveling.password);
}

void verify_number(int num){
    if (!num){
        puts("Why didn't you give up?");
        print_current_password();
    }
    else{
        puts("Bye");
        exit(0);
    }
}

void whereami(){
    puts("Stress levels are too high.. I'm sure you want to take a break");
    puts("--------------------------------------------------------------");
    puts("[1] Exit");
    puts("[2] Exit");
    puts("[3] Exit");
    puts("........");
    puts("[124512] Exit");
    puts("--------------------------------------------------------------");
    printf("Choose what to do: ");

    long int number;
    scanf("%ld", &number);
    if (number == 0){
        puts("I dont like that number");
        exit(0);
    }
    else
        verify_number(number);
}

void setup(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

struct timeline{
    char name[16];
    char divergence[8];
    void (*leap)();
}timeline;

void okabe(){
    puts("What's the password?");
    char password[20];
    fgets(password, 20, stdin);
    password[12] = '\0';
    if (strcmp(leveling.password, password) != 0){
        puts("That's wrong.");
        exit(0);
    }
    printf("Do you still remember who you are?: ");
    fgets(timeline.name, 32, stdin);
}

int youdidwhat(int x){
    int y = 1;
    while (!(x & y))
    {
        x = x ^ y;
        y <<= 1;
    }
 
    x = x ^ y;
    return x;
}

void password(){
    srand((unsigned int)(time(NULL)));
    int i;
    char pass[12];
    
    for(i = 0; i < 12; i++) {
    pass[i] = 33 + rand() % 94;
    }
    pass[i] = '\0';
    strcpy(leveling.password, pass);
}

void divergence_meter(){
    char input[15] = {0};
    
    printf("Choose where to leap: ");
    fgets(input, 15, stdin);

    int index = 0;
    for (int i=0; i < strlen(input); i++){
        if (input[i] == 'g')
            continue;
        else if (input[i] == 'o' && index != 0)
            index = youdidwhat(index);
        else{
            timeline.divergence[index] = input[i];
            index += 1;            
        }

        if (index > 8)
            break;
    }

}

void timeleap(){
    puts("You've pressed the button... be ready for the leap!");
    sleep(0.25);
    timeline.leap();
}
void fate(){
    puts("You did not break the 1% barrier...\nYour fate did not change.");
}

void new_fate(){
    puts("You've chosen another fate....");
    whereami();
}

void current_leap(){
    timeline.leap = fate;
    leveling.sane = 0;
    leveling.memory = 0;
    password();
    leveling.armed = 0;
}

void menu(){
    printf("Enter your name: ");
    fgets(timeline.name, 15, stdin);
    while(69 == 69){
        puts("\nWhat are you going to do?");
        puts("-------------------------");
        puts("[1] Try to change the timeline");
        puts("[2] Time leap");
        puts("[3] Ensure your sanity");
        puts("[4] Remember who you are");
        puts("[5] Exit");
        puts("-------------------------");
        printf("Enter choice: ");

        char choice[5] = {0};
        unsigned int number;
        fgets(choice, 5, stdin);
        number = atoi(choice);

        if (number == 1)
            divergence_meter();
        else if (number == 2)
            timeleap();
        else if (number == 3){
            if (leveling.sane != 0)
                sanity();
            else
                puts("You are sane.");
        }
        else if (number == 5)
            exit(0);
        else if (number == 4){
             if (leveling.armed != 0)
                okabe();
            else
                puts("You didn't play the game yet! :(");   
        }
        else
            puts("Try again.\n");
    }
    
}

int main(){
    printf("Your current timeline is horrible.\n");
    sleep(1);
    printf("In order to reach the Pwn;Gate you are ready to sacrifice everything...\n\n");
    sleep(1);
    setup();
    current_leap();
    menu();
}
