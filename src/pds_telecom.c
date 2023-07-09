#include <stdio.h>
#include <stdlib.h>
#include "pds_telecom.h"
#include "matrizes.h"
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

complex *tx_qam_mapper(int *s, long int qam) {
    
    // Aloca memória para o vetor de complexs
    complex *simbolo = (complex *)malloc(qam * sizeof(complex));
    
    if (simbolo == NULL) {
        printf("Erro na alocação de memória\n");
        return NULL;
    }

    for (int i = 0; i < qam; i++) {
    
        switch (s[i]) {
            case 0:
                simbolo[i].Re = -1;
                simbolo[i].Im = 1;
                break;
            case 1:
                simbolo[i].Re = -1;
                simbolo[i].Im = -1;
                break;
            case 2:
                simbolo[i].Re = 1;
                simbolo[i].Im = 1;
                break;
            case 3:
                simbolo[i].Re = 1;
                simbolo[i].Im = -1;
                break;
            default:
                simbolo[i].Re = 0;
                simbolo[i].Im = 0;
            break;
        }
    }
    return simbolo;
}

complex *tx_layer_mapper(complex *qam_simbolos, int num_simbolos, int num_streams) {
    
    // Calculate the number of symbols per stream
    int simbolos_por_stream = num_simbolos / num_streams;

    // Allocate memory for the mapped symbols
    complex *mapped_simbolos = (complex *)malloc(num_simbolos * sizeof(complex));
    if (mapped_simbolos == NULL) {
        printf("Error allocating memory\n");
        return NULL;
    }

    // Perform layer mapping
    for (int i = 0; i < num_simbolos; i++) {
        int stream_idx = i % num_streams;
        int symbol_idx = i / num_streams;

        // Map the QAM symbol to the corresponding stream
        mapped_simbolos[i] = qam_simbolos[symbol_idx * num_streams + stream_idx];
    }

    return mapped_simbolos;
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
    
    // Reiza a leitura do arquivo e obtém a sequência de dígitos
    int *resultado = tx_data_read(file, file_size);

    if (resultado != NULL) {
        
        // Imprime o vetor resultante
        for (int i = 0; i < file_size * 4; i++) {
            printf("%d, ", resultado[i]);
        }
        
        printf("\n");

        // Escreve a sequência de dígitos no arquivo binário
        rx_data_write(resultado, file_size, filename_saida);

        
        // Mapeia os indices para os numeros complexs da constelacao qam
        complex *map = tx_qam_mapper(resultado, file_size * 4);
        
        if (map != NULL) {
            
            // Imprime os numeros complexs
            for (int i = 0; i < file_size * 4; i++) {
                printf("Índice %d: %.2f%+.2fj\n", i, map[i].Re, map[i].Im);
            }

            printf("\n");

            // Mapeia os símbolos QAM para cada stream
            int num_streams = 4; 
            complex *mapped_symbols = tx_layer_mapper(map, file_size * 4, num_streams);

            if (mapped_symbols != NULL) {
                // Imprime os símbolos mapeados para cada stream
                for (int i = 0; i < file_size * 4; i++) {
                    printf("Stream %d: %.2f%+.2fj\n", i % num_streams, mapped_symbols[i].Re, mapped_symbols[i].Im);
                }
            }
        }
    }

    fclose(file);
    return 0;
}