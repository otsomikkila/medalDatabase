#include "project.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

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

//return the pointer to the first element or NULL if the country already exists in the linked list
struct Country* addCountry(char* input, struct Country* first) {
    char* tokens[2];
    getTokens(input, tokens, 2);
    
    int size = strlen(tokens[1]) + 1;

    struct Country* iterator = first;

    //if multiple countries in database, check there will be no duplicates
    if (iterator != NULL) {
        printf("first was not null\n");
        while (iterator->next != NULL) {
            printf("%s\n", iterator->name);
            if (strcmp(iterator->name, tokens[1]) == 0) {
                printf("Country already in chart\n");
                return NULL;
            }
            iterator = iterator->next;
        }
        //check the last node
        if (strcmp(iterator->name, tokens[1]) == 0) {
            printf("Country already in chart\n");
            return NULL;
        }
    }

    struct Country* newCountry = malloc(sizeof(struct Country));
    newCountry->name = malloc(size);
    memcpy(newCountry->name, tokens[1], size);
    newCountry->gold = 0;
    newCountry->silver = 0;
    newCountry->bronze = 0;
    newCountry->next = NULL;

    if (first != NULL) {
        iterator->next = newCountry;
        printf("NEXT: %s", iterator->next->name);
        return first;
    }
    else {
        return newCountry;
    }
}

int main(void) {
    //A buffer where to store user input, size is the maximum size given on the assignment
    char userInput[1000];
    char copyInput[1000];

    //pointer to first item in linked list
    struct Country* first = { NULL };
    
    while(1) {
        fgets(userInput, sizeof(userInput), stdin);

        strcpy(copyInput, userInput);
        char* cp = strtok(copyInput, " \n");

        //check that the command exists and is only 1 char long
        if (!cp || strlen(cp) > 1) {
            printf("Invalid command %s\n", userInput);
            continue;
        }

        char command = cp[0];
        
        switch (command)
        {
        case 'A':
            if(!checkInput(2, userInput)) {
                printf("Too many arguments\n");
                break;
            }
            struct Country* result;
            //should this be first saved to result and added afterwards??
            result = addCountry(userInput, first);
            if(result) {
                first = result;
                printf("first: %s", first->name);
                if(first->next) {
                    printf("first next: %s\n", first->next->name);
                }
                else {
                    printf("first next: null\n");
                }
            }
            else {
                printf("FAIL\n");
            }
            break;
        case 'M':   //not implemented
            if(!checkInput(5, userInput)) {
                continue;
            }
            printf("MEDAL\n");
            break;
        case 'L':   //not implemented
            if(!checkInput(1, userInput)) {
                continue;
            }
            printf("LIST\n");
            break;
        case 'W':   //not implemented
            if(!checkInput(2, userInput)) {
                continue;
            }
            printf("WRITE\n");
            break;
        case 'O':   //not implemented
            if(!checkInput(2, userInput)) {
                continue;
            }
            printf("LOAD\n");
            break;
        case 'Q':   //not fully implemented
            if(!checkInput(1, userInput)) {
                continue;
            }
            free(first->name);
            free(first->next);
            free(first);
            printf("SUCCESS\n");
            return 0;
        default:
            //ERROR with input A CHINA M, or input that has correct first statement but too many arguments
            printf("Invalid command %s\n", userInput);
        }
    }
}