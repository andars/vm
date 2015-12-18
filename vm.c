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
        uint8_t a;
        uint8_t b;

        printf("read bytecode: ");
        switch (bytecode) {
        case BC_PUSH: 
            printf("BC_PUSH\n");
            fread(&a, 1, 1, input);
            printf("%d\n", a);
            stack[++stack_top] = a;
            break;
        case BC_POP:
            printf("BC_POP\n");
            printf("%d\n", stack[stack_top]);
            stack[stack_top--] = 0;
            break;
        case BC_ADD:
            printf("BC_ADD\n");
            a = stack[stack_top--];
            b = stack[stack_top--];
            stack[++stack_top] = a+b;
            break;
        case BC_NEG:
            printf("BC_NEG\n");
            stack[stack_top] = -stack[stack_top];
            break;
        case BC_JUMP:
            printf("BC_JUMP\n");
            fread(&a, 1, 1, input);
            fseek(input, a, SEEK_SET);
            break;
        case BC_RJUMP:
            printf("BC_JUMP\n");
            fread(&a, 1, 1, input);
            fseek(input, a, SEEK_CUR);
            break;
        default:
            printf("unrecognized\n");
            break;
        }
        if (stack_top >= STACK_SIZE) {
            printf("ERROR: stack overflow\n");
            return 1;
        }
    }
    return 0;
}
