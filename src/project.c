#include "project.h"
#include "stdio.h"
#include "string.h"

//Linked list?

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
            //initialize new country and add it to the list
            printf("%s\n", userInput);
            
            //initialize values
            test[0].gold = 0;
            test[0].silver = 0;
            test[0].bronze = 0;


            //add to the linked list
            printf("ADD\n");
            continue;
        case 'M':
            printf("MEDAL\n");
            continue;
        case 'L':
            printf("LIST\n");
            continue;
        case 'W':
            printf("WRITE\n");
            continue;
        case 'O':
            printf("LOAD\n");
            continue;
        case 'Q':
            printf("QUIT\n");
            return 0;
        default:
            printf("Invalid command %c\n", command);
        }
    }
}