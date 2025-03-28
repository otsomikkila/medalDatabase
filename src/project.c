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

    if (count != n) {
        printf("Invalid command %s\n", inputCopy);
    }

    return (count == n);
}

void* getTokens(char* input, char* tokens[], int n) {
    int i = 0; 

    tokens[i] = strtok(input, " ");

    while (tokens[i] != NULL && i < n - 1) { 
        i++;
        tokens[i] = strtok(NULL, " ");
    }
    return 0;
}
//strtok the input string to get an array of arguments

int addCountry(char* input, struct Country* first) {
    char* tokens[2];
    getTokens(input, tokens, 2);
    
    printf("1: %s\n", tokens[0]);
    printf("2: %s\n", tokens[1]);

    if (first == NULL) {
        printf("first is null\n");
        //struct Country newCountry = {};
    }
    else {
        //iterate through and check there is no name that is the same
    }
    printf("ADD\n");
    return 0;
}

int main(void) {
    //A buffer where to store user input, size is the maximum size given on the assignment
    char userInput[1000];
    char copyInput[1000];

    //pointer to first item in linked list
    struct Country* first = { NULL };
    //printf("%s", first->name);
    
    while(1) {
        fgets(userInput, sizeof(userInput), stdin);

        strcpy(copyInput, userInput);
        char* cp = strtok(copyInput, " \n");

        if (!cp || strlen(cp) > 1) {
            printf("Invalid command %s\n", userInput);
            continue;
        }

        char command = cp[0];
        
        switch (command)
        {
        case 'A':
            if(!checkInput(2, userInput)) {
                continue;
            }
            addCountry(userInput, first);
            break;
        case 'M':
            if(!checkInput(5, userInput)) {
                continue;
            }
            printf("MEDAL\n");
            break;
        case 'L':
            if(!checkInput(1, userInput)) {
                continue;
            }
            printf("LIST\n");
            break;
        case 'W':
            if(!checkInput(2, userInput)) {
                continue;
            }
            printf("WRITE\n");
            break;
        case 'O':
            if(!checkInput(2, userInput)) {
                continue;
            }
            printf("LOAD\n");
            break;
        case 'Q':
            if(!checkInput(1, userInput)) {
                continue;
            }
            printf("QUIT\n");
            return 0;
        default:
            printf("Invalid command %s\n", userInput);
        }
    }
}