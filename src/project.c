#include "project.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//add a function to check from user input that it has the exact amount of parameters the command needs
//use strtok for it

//last update:
//M function working 
//next: O function, use the addMedals method to add to middle


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
    
    //get rid of '\n' at end of line
    int len = strlen(tokens[1]);
    if (tokens[1][len - 1] == '\n') {
        tokens[1][len - 1] = '\0';
        len--;
    }

    struct Country* iterator = first;

    //if multiple countries in database, check there will be no duplicates
    if (iterator != NULL) {
        while (iterator->next != NULL) {
            //printf("%s\n", iterator->name);
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
    newCountry->name = malloc(len + 1);
    strcpy(newCountry->name, tokens[1]);

    newCountry->gold = 0;
    newCountry->silver = 0;
    newCountry->bronze = 0;
    newCountry->next = NULL;

    if (first != NULL) {
        iterator->next = newCountry;
        //printf("NEXT: %s", iterator->next->name);
        return first;
    }
    else {
        return newCountry;
    }
}

void printToStream(struct Country* first, char* filename) {
    FILE * fp = stdout;

    if (filename != NULL) fp = fopen(filename, "w");

    struct Country* iterator = first; 
    while (iterator != NULL) {
        fprintf(fp, "%s %i %i %i\n", iterator->name, iterator->gold, iterator->silver, iterator->bronze);
        iterator = iterator->next;
    }

    if(filename != NULL) fclose(fp);
}

void writeToFile(struct Country* first, char* input) {
    char* tokens[2];
    getTokens(input, tokens, 2);
    printToStream(first, tokens[1]);
}

//modify the addCountry or make a helper that will add a valid country into 
//the right part of the list
//return pointer to first, input has already been validated
struct Country* addWithMedals(struct Country* first, struct Country* modifiedCountry) {
    
    //printf("%s %i %i %i\n", modifiedCountry->name, modifiedCountry->gold, modifiedCountry->silver, modifiedCountry->bronze);

    //loop through the linked list and find the slot where it belongs to
    //will also need a prev pointer 

    struct Country* iterator = first;
    struct Country* prev = iterator;

    while (iterator != NULL) {
        //printf("iterator: %s %i %i %i    newValue: %s %i %i %i\n", iterator->name, iterator->gold, iterator->silver, iterator->bronze, modifiedCountry->name, modifiedCountry->gold, modifiedCountry->silver, modifiedCountry->bronze);
        if (modifiedCountry->gold > iterator->gold) {
            //printf("Spot found\n");
            break;
        }
        if ((modifiedCountry->gold == iterator->gold) && (modifiedCountry->silver > iterator->silver)) {
            //printf("Spot found2\n");
            break;
        }
        if ((modifiedCountry->gold == iterator->gold) && (modifiedCountry->silver == iterator->silver) && (modifiedCountry->bronze > iterator->bronze)) {
            //printf("Spot found3\n");
            break;
        }
        prev = iterator;
        iterator = iterator->next;
    }

    if (iterator == first) {
        modifiedCountry->next = first;
        return modifiedCountry;
    }
    else {
        prev->next = modifiedCountry;
        modifiedCountry->next = iterator;
        //if first did not move, return it else return new first
        
        return first;
    }
}

//return pointer to first, or null if the country does not exist
struct Country* addMedals(struct Country* first, char* input) {
    char* tokens[5];
    getTokens(input, tokens, 5);

    //get the variables from the array of tokens
    char* countryName = tokens[1];
    int gold = (int)strtoul(tokens[2], NULL, 10);
    int silver = (int)strtoul(tokens[3], NULL, 10);
    int bronze = (int)strtoul(tokens[4], NULL, 10);

    //check country exists
    //add NULL to prev othervise doesn't work
    struct Country* iterator = first;
    struct Country* prev = NULL;
    

    while (iterator != NULL) {
        if(strcmp(iterator->name, countryName) == 0) {
            //the previous pointer has to point to iterator->next
            //check that not the first case

            //ensure values cant go below zero
            iterator->gold   = CLAMP_TO_ZERO(iterator->gold + gold);
            iterator->silver   = CLAMP_TO_ZERO(iterator->silver + silver);
            iterator->bronze   = CLAMP_TO_ZERO(iterator->bronze + bronze);

            if(!prev) {
                if (iterator->next) {
                    first = iterator->next;
                }
            }
            else {
                prev->next = iterator->next;
            }

            //this adds the updated country to correct slot
            return addWithMedals(first, iterator);
        }
        prev = iterator;
        iterator = iterator->next;
    }
    puts("Country not in database");
    return NULL;
}

void* freeList(struct Country* first) {
    struct Country* temp;
    while (first != NULL) {
        temp = first;
        first = first->next;
        free(temp->name);
        free(temp);
    }
    return 0;
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
        struct Country* result; 
        
        switch (command)
        {
        case 'A':
            if(!checkInput(2, userInput)) {
                printf("Invalid amount of arguments\n");
                break;
            }

            result = addCountry(userInput, first);
            
            if(result) {
                first = result;
                printf("SUCCESS\n");
            }
            break;
        case 'M':
            if(!checkInput(5, userInput)) {
                printf("Invalid amount of arguments\n");
                break;
            }

            //save the result 
            result = addMedals(first, userInput);
            if(result) {
                first = result;
                printf("SUCCESS\n");
            }
            break;
        case 'L':
            if(!checkInput(1, userInput)) {
                printf("Invalid amount of arguments\n");
                break;
            }
            printToStream(first, NULL);
            printf("SUCCESS\n");
            break;
        case 'W':
            if(!checkInput(2, userInput)) {
                printf("Invalid amount of arguments\n");
                break;
            }
            writeToFile(first, userInput);
            printf("SUCCESS\n");
            break;
        case 'O':   //not implemented
            if(!checkInput(2, userInput)) {
                printf("Invalid amount of arguments\n");
                break;
            }
            printf("LOAD\n");
            break;
        case 'Q':   //not fully implemented
            if(!checkInput(1, userInput)) {
                printf("Invalid amount of arguments\n");
                break;
            }
            freeList(first);
            printf("SUCCESS\n");
            return 0;
        default:
            printf("Invalid command %s\n", userInput);
        }
    }
}