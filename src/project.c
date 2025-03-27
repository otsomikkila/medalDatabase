#include "project.h"
#include "stdio.h"
#include "string.h"

//Linked list?
//add a function to check from user input that it has the exact amount of parameters the command needs
//use strtok for it

int checkInput(int n, char* input) {
    char inputCopy[1000];
    strcpy(inputCopy, input);

    char* cp = strtok(inputCopy, " ");
    int count = 0;

    while (cp != NULL) {
        cp = strtok(NULL, " ");
        count++;
    }

    return (count == n);
}

int main(void) {

    //A buffer where to store user input, size is the maximum size given on the assignment
    char userInput[1000];
    
    while(1) {
        fgets(userInput, sizeof(userInput), stdin);

        char command = userInput[0];
        struct Country test[2] = {};

        switch (command)
        {
        case 'A':
            if(!checkInput(2, userInput)) {
                printf("ERROR\n");
                continue;
            }
            printf("TOIMII\n");
            //initialize new country and add it to the list
            //initialize values
            test[0].gold = 0;
            test[0].silver = 0;
            test[0].bronze = 0;


            //add to the linked list
            printf("ADD\n");
            continue;
        case 'M':
            if(!checkInput(5, userInput)) {
                printf("ERROR\n");
                continue;
            }
            printf("MEDAL\n");
            continue;
        case 'L':
            if(!checkInput(1, userInput)) {
                printf("ERROR\n");
                continue;
            }
            printf("LIST\n");
            continue;
        case 'W':
            if(!checkInput(2, userInput)) {
                printf("ERROR\n");
                continue;
            }
            printf("WRITE\n");
            continue;
        case 'O':
            if(!checkInput(2, userInput)) {
                printf("ERROR\n");
                continue;
            }
            printf("LOAD\n");
            continue;
        case 'Q':
            if(!checkInput(1, userInput)) {
                printf("ERROR\n");
                continue;
            }
            printf("QUIT\n");
            return 0;
        default:
            printf("Invalid command %c\n", command);
        }
    }
}