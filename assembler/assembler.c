#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char* token = strtok(source, " \n");
    while (token) {
        printf("%s\n", token);
        token = strtok(NULL, " \n");
    }

    free(source);    
}
