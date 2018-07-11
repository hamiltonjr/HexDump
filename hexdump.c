#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(int argc, char** argv) {
    char *buffer = (char*)malloc(17);
    char *file = (char*)malloc(255);
    FILE *fpin;     
    int i, count;

    if (argc==2) {
        strcpy(file, argv[1]);
    } else {
        printf("Erro!\n");
        exit(EXIT_FAILURE);
    }

    if ((fpin = fopen(file, "r")) == NULL) {
        printf("Erro\n");
        exit(EXIT_FAILURE);
    }

    // lê 16 bytes do arquivo
    count = 0;
    while (fread (buffer, 16, 1, fpin) == 1) {
        // mostra offset
        printf("%08X  ", count);
        count += 16;

        // mostra primeiro chunck
        for (i=0; i<8 && buffer[i]!='\0'; i++) {
            printf("%02X ", buffer[i]);
        }
        printf(" ");

        // mostra segundo chunck
        for (i=i+1; i<16 && buffer[i]!='\0'; i++) {
            printf("%02X ", buffer[i]);
        }

        // mostra string
        for (int i=0; i<strlen(buffer); i++) {
            if (buffer[i]<32 || buffer[i]>127) {
                buffer[i] = '.';
            }
        }
        printf(" |%s|\n", buffer);
    }    

    fclose(fpin);
    return 0;
}

