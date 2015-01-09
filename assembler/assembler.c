#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../codes.h"

char* readFile(char* name) {
    FILE *input = fopen(name, "r");
    fseek(input, 0, SEEK_END);
    size_t size = ftell(input);
    rewind(input);

    char* buffer = malloc(size + 1); //null terminator

    int count = fread(buffer, sizeof(char), size, input);
    buffer[count] = '\0';

    fclose(input);
    return buffer;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "No filename given\n");
        return 1;
    }
    char* source = readFile(argv[1]);    
    int source_length = strlen(source);

    char* token = strtok(source, " \n");

//still trying to decide if I want to go for 2 pass or 1 pass
/*
    char *transformed_source = malloc(sizeof(char*) * source_length);
    int transformed_length = 0;
    //first pass for labels
    
    int length = strlen(token);
    for (int i = length; i<source_length; i+= length) {

        length = strlen(token);
        if (token[length-1] == ':') {
        } else {
            strcpy(transformed_source+transformed_length, token);
            strcpy(transformed_source+transformed_length+length, " ");
            transformed_length += length + 1;
        }
        token = strtok(NULL, " \n");
        if (token == NULL) break;
    }
    transformed_source[transformed_length] = '\0';

    fprintf(stderr, "%s", transformed_source);
*/
    char output;
    int position = 0;
    while (token) {
        if(strcasecmp(token, "push") == 0) {
            printf("%c", BC_PUSH);
            token = strtok(NULL, " \n");
            uint8_t value = strtol(token, NULL, 10);
            printf("%c", value);
        } else if (strcasecmp(token, "pop") == 0) {
            output = BC_POP;
            printf("%c", output);
        } else if (strcasecmp(token, "add") == 0) {
            output = BC_ADD;
            printf("%c", output);
        } else if (strcasecmp(token, "neg") == 0) {
            output = BC_NEG;
            printf("%c", output);
        } else if (strcasecmp(token, "jump") == 0) {
            printf("%c", BC_JUMP);
            token = strtok(NULL, " \n");
            uint8_t value = strtol(token, NULL, 10);
            printf("%c", value);
        } else if (strcasecmp(token, "cmp") == 0) {
            output = BC_CMP;
            printf("%c", output);
        } else if (strcasecmp(token, "rjmp") == 0) {
            printf("%c", BC_RJUMP);
            token = strtok(NULL, " \n");
            uint8_t value = strtol(token, NULL, 10);
            printf("%c", value);
        } else {
            char last = token[strlen(token)-1];
            fprintf(stderr, "%c", last);
            if (last == ':') { //label

            }
        }


        token = strtok(NULL, " \n");
    } 

    free(source);    
}
