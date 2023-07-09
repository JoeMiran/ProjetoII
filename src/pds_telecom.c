#include <stdio.h>
#include <stdlib.h>
#include "pds_telecom.h"

typedef struct {
    float real;
    float img;
} complexo;

int * tx_data_read(FILE *file, long int sequencia_bytes) {
    
    // Aloca memória para o array de inteiros
    int *s = (int *)malloc(sequencia_bytes * 4 * sizeof(int));
    if (s == NULL) {
        printf("Erro na alocação de memória\n");
        fclose(file);
        return NULL;
    }
    // Lê os bytes do arquivo e converte em inteiros de 2 bits
    for (int i = 0; i < sequencia_bytes; i++) {
        char byte;
        fread(&byte, sizeof(byte), 1, file);

        for (int j = 0; j <= 7; j = j + 2) {
            int bit = (byte >> j) & 3;
            s[(i * 4) + (j / 2)] = bit;
        }
    }
    return s;
}

void rx_data_write(int *s, long int sequencia_bytes, char *filename) {
    FILE *out = fopen(filename, "wb");
    if (out == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return;
    } else {
        printf("\nArquivo %s criado.\n\n", filename);
    }

    for (int i = 0; i < sequencia_bytes; i++) {
        unsigned char byte = 0;
        for (int j = 0; j < 4; j++) {
            unsigned int bit = s[(i * 4) + j];
            byte |= (bit << (2 * j));
        }
        fwrite(&byte, sizeof(byte), 1, out);
    }

    fclose(out);
}

complexo *tx_qam_mapper(int *s, long int qam) {
    
    // Aloca memória para o vetor de complexos
    complexo *simbolo = (complexo *)malloc(qam * sizeof(complexo));
    
    if (simbolo == NULL) {
        printf("Erro na alocação de memória\n");
        return NULL;
    }

    for (int i = 0; i < qam; i++) {
    
        switch (s[i]) {
            case 0:
                simbolo[i].real = -1;
                simbolo[i].img = 1;
                break;
            case 1:
                simbolo[i].real = -1;
                simbolo[i].img = -1;
                break;
            case 2:
                simbolo[i].real = 1;
                simbolo[i].img = 1;
                break;
            case 3:
                simbolo[i].real = 1;
                simbolo[i].img = -1;
                break;
            default:
                simbolo[i].real = 0;
                simbolo[i].img = 0;
            break;
        }
    }
    return simbolo;
}

int main() {

    char *filename = "in";
    char *filename_saida = "out";

    FILE *file = fopen(filename, "rb");
    
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return 1;
    } else {
        printf("O arquivo foi aberto\n\n");
    }

    fseek(file, 0, SEEK_END);
    long int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Realiza a leitura do arquivo e obtém a sequência de dígitos
    int *resultado = tx_data_read(file, file_size);

    if (resultado != NULL) {
        
        // Imprime o vetor resultante
        for (int i = 0; i < file_size * 4; i++) {
            printf("%d, ", resultado[i]);
        }
        
        printf("\n");

        // Escreve a sequência de dígitos no arquivo binário
        rx_data_write(resultado, file_size, filename_saida);
        
        // Mapeia os indices para os numeros complexos da constelacao qam
        complexo *map = tx_qam_mapper(resultado, file_size * 4);
        
        if (map != NULL) {
            
            // Imprime os numeros complexos
            for (int i = 0; i < file_size * 4; i++) {
                printf("Índice %d: %.2f%+.2fj\n", i, map[i].real, map[i].img);
            }
        
        }
    }

    fclose(file);
    return 0;
}