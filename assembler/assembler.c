#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/errno.h>

#include "hash_table.h"
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
    
    hash_table* sym_table = ht_create();

    char* source = readFile(argv[1]);    

    char* token = strtok(source, " \n");

    char output;
    int position = 0;

    while (token) {
        if (strcasecmp(token, "push") == 0) {
            printf("%c", BC_PUSH);
            token = strtok(NULL, " \n");
            uint8_t value = strtol(token, NULL, 10);
            printf("%c", value);
            position += 2;
        } else if (strcasecmp(token, "pop") == 0) {
            output = BC_POP;
            printf("%c", output);
            position += 1;
        } else if (strcasecmp(token, "add") == 0) {
            output = BC_ADD;
            printf("%c", output);
            position += 1;
        } else if (strcasecmp(token, "neg") == 0) {
            output = BC_NEG;
            printf("%c", output);
            position += 1;
        } else if (strcasecmp(token, "jump") == 0) {
            printf("%c", BC_JUMP);
            token = strtok(NULL, " \n");
            uint8_t value = strtol(token, NULL, 10);
            if (value == 0 && errno == EINVAL) {
                void* lbl_val = ht_get(sym_table, token);
                if (lbl_val == NULL) {
                    fprintf(stderr, "nonexistent label\n");
                } else {
                    value = (uint8_t) lbl_val;
                }
            }
            printf("%c", value);
            position += 2;
        } else if (strcasecmp(token, "cmp") == 0) {
            output = BC_CMP;
            printf("%c", output);
            position += 1;
        } else if (strcasecmp(token, "rjmp") == 0) {
            printf("%c", BC_RJUMP);
            token = strtok(NULL, " \n");
            uint8_t value = strtol(token, NULL, 10);
            printf("%c", value);
            position += 2;
        } else {
            char last = token[strlen(token)-1];
            fprintf(stderr, "%c", last);
            if (last == ':') { //label
                token[strlen(token)-1] = '\0';
                ht_set(sym_table, token, (void*) (int*) position);
            }
        }

        token = strtok(NULL, " \n");
    } 

    free(source);    
}
