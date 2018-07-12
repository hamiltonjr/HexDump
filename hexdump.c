#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long size(char*);
void stradj(char*);
void spaces(int);

int main(int argc, char** argv) {
    char *buffer = (char*)malloc(17);
    int line, column, little;
    long bytes, lines;
    FILE *fpin;
    char c = 0;

    // checa argumento (nome do arquivo)
    if (argc != 2) {
        printf("Erro!\n");
        exit(EXIT_FAILURE);
    }

    bytes = size(argv[1]);
    lines = bytes / 16L;
    little = bytes % 16;

    // checa validade do ponteiro para arquivo
    if ((fpin = fopen(argv[1], "r")) == NULL) {
        printf("Erro\n");
        exit(EXIT_FAILURE);
    }

    line = 0;
    column = 0;
    while ((c = getc(fpin)) != EOF) {
        if (column == 0)
            printf("%08X  ", 16*line);

        printf("%02X ", c);
        buffer[column] = c;

        if (column == 15) {
            column = 0;
            line++;
            stradj(buffer);
            printf("|%s|\n", buffer);
        } else
            column++;
    }

    // na última linha
    buffer[column] = '\0';
    spaces(48 - 3*little);
    stradj(buffer);
    printf("|%s|\n", buffer);

    //printf("Spaces: %d\n", 50-3*little);
    //printf("Bytes: %ld\n", bytes);
    //printf("Lines: %ld\n", lines);
    //printf("Little: %d\n", little);

    fclose(fpin);
    return 0;
}

long size(char *file) {
    FILE *fp;
    long bytes;

    if ((fp = fopen(file, "r")) == NULL) {
        printf("Erro\n");
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0, SEEK_END);
    bytes = ftell(fp);
    fclose(fp);
    return bytes;
}


void stradj(char* s) {
    for (int i=0; s[i]!='\0'; i++)
        if (s[i] < 32)
            s[i] = '.';
}

void spaces(int x) {
    for (int i=0; i<x; i++)
        printf(" ");
}