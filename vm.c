#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "codes.h"

#define STACK_SIZE 256

uint8_t stack[STACK_SIZE];
int stack_pointer = 0;
int base_pointer = 0;
int stack_top = 0;

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: vm filename\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "rb");
    uint8_t bytecode = 0;

    while(fread(&bytecode, 1, 1, input)) {
//        printf("%d", bytecode);
        switch (bytecode) {
        case BC_PUSH: {
            uint8_t a = 0;
            fread(&a, 1, 1, input);
            stack[++stack_top] = a;
            break;
        }
        case BC_POP:
            printf("%d\n", stack[stack_top]);
            stack[stack_top--] = 0;
        default:
            break;                
        } 
    }
    return 0; 
}
