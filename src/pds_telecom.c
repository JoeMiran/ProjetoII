#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pds_telecom.h"
#include "matrizes.h"

// Função para ler os dados do arquivo
int *tx_data_read(FILE *file, long int sequencia_bytes) {
    int *s = (int *)malloc(sequencia_bytes * 4 * sizeof(int)); // Aloca memória para o array de inteiros

    if (s == NULL) { // Verifica se houve falha na alocação de memória
        printf("Erro na alocação de memória\n");
        fclose(file); // Fecha o arquivo
        return NULL; // Retorna NULL em caso de erro
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

    return s; // Retorna o array de inteiros
}

// Função para escrever os dados no arquivo
void rx_data_write(int *s, long int sequencia_bytes, char *filename) {
    FILE *out = fopen(filename, "wb"); // Abre o arquivo para escrita binária

    if (out == NULL) { // Verifica se houve falha na abertura do arquivo
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return;
    } else {
        printf("\nArquivo %s criado.\n\n", filename);
    }

    // Converte os inteiros de 2 bits em bytes e escreve no arquivo
    for (int i = 0; i < sequencia_bytes; i++) {
        unsigned char byte = 0;
        for (int j = 0; j < 4; j++) {
            unsigned int bit = s[(i * 4) + j];
            byte |= (bit << (2 * j));
        }
        fwrite(&byte, sizeof(byte), 1, out);
    }

    fclose(out); // Fecha o arquivo
}

// Função para mapear os índices para números complexos QAM
complex *tx_qam_mapper(int *s, long int qam) {
    complex *simbolo = (complex *)malloc(qam * sizeof(complex)); // Aloca memória para o vetor de complexos

    if (simbolo == NULL) { // Verifica se houve falha na alocação de memória
        printf("Erro na alocação de memória\n");
        return NULL; // Retorna NULL em caso de erro
    }

    // Mapeia os índices para os números complexos da constelação QAM
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

    return simbolo; // Retorna o vetor de complexos
}

// Função para mapear os símbolos QAM para cada fluxo
complex **tx_layer_mapper(complex *v, int Nstream, long int Nsymbol) {
    complex **mtx_stream = (complex **)malloc(Nstream * sizeof(complex *)); // Aloca memória para a matriz de complexos

    if (mtx_stream == NULL) { // Verifica se houve falha na alocação de memória
        printf("Erro na alocação de memória\n");
        return NULL; // Retorna NULL em caso de erro
    }

    for (int i = 0; i < Nstream; i++) {
        mtx_stream[i] = (complex *)malloc((Nsymbol / Nstream) * sizeof(complex));

        if (mtx_stream[i] == NULL) { // Verifica se houve falha na alocação de memória
            printf("Erro na alocação de memória\n");

            // Libera a memória alocada anteriormente
            for (int j = 0; j < i; j++) {
                free(mtx_stream[j]);
            }
            free(mtx_stream);
            return NULL; // Retorna NULL em caso de erro
        }
    }

    // Mapeia os dados do vetor para a matriz de complexos
    for (int i = 0; i < Nsymbol; i++) {
        mtx_stream[i % Nstream][i / Nstream] = v[i];
    }

    return mtx_stream; // Retorna a matriz de complexos
}

//Funcao para gerar um numero aleatorio entre -1 e 1
float gerar_float_aleatorio() {
    return -1.0 + ((float)rand() / (float)RAND_MAX) * 2.0;
}

//Funcao para gerar uma matriz que representa um canal aleatorio H
float** channel_gen(int Nr, int Nt) {
    
    float** H = (float**)malloc(Nr * sizeof(float*)); //Aloca memoria para as linhas da matrix

    if(H == NULL) { //Verifica se a alocacao foi bem sucedida
        printf("Erro de alocacao de memoria\n");
        return NULL;
    }

    for (int i = 0; i < Nr; i++) { 
        H[i] = (float*)malloc(Nt * sizeof(float)); //Aloca memoria para as colunas da matriz

        if (H[i] == NULL) {
            printf("Erro na alocacao de memoria nas colunas\n");

            //Liberando a memoria em caso de erro
            for (int j = 0; j < i; j++) {
                free(H[j]);
            }

            free(H);
            return NULL;

        }

        for (int j = 0; j<Nt; j++) {
            H[i][j] = gerar_float_aleatorio(); //Preenche a matriz com valores aleatorios  
        }

    }

    return H;
}

int main() {
    char *filename = "in";
    char *filename_saida = "out";

    FILE *file = fopen(filename, "rb"); // Abre o arquivo binário para leitura

    if (file == NULL) { // Verifica se houve falha na abertura do arquivo
        printf("Erro ao abrir o arquivo %s\n", filename);
        return 1;
    } else {
        printf("O arquivo foi aberto\n\n");
    }

    fseek(file, 0, SEEK_END);
    long int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    int *resultado = tx_data_read(file, file_size); // Lê os dados do arquivo

    if (resultado != NULL) {
        // Imprime o vetor resultante
        for (int i = 0; i < file_size * 4; i++) {
            printf("%d, ", resultado[i]);
        }
        printf("\n");

        rx_data_write(resultado, file_size, filename_saida); // Escreve a sequência de dígitos no arquivo binário

        complex *map = tx_qam_mapper(resultado, file_size * 4); // Mapeia os índices para números complexos QAM
        
        if (map != NULL) {
            // Imprime os números complexos
            for (int i = 0; i < file_size * 4; i++) {
                printf("Índice %d: %.2f%+.2fj\n", i, map[i].Re, map[i].Im);
            }
            printf("\n");

            int num_streams = 4;
            complex **mapped_symbols = tx_layer_mapper(map, num_streams, file_size * 4); // Mapeia os símbolos QAM para cada fluxo

            if (mapped_symbols != NULL) {
                // Imprime os símbolos mapeados para cada fluxo
                for (int i = 0; i < num_streams; i++) {
                    for (int j = 0; j < file_size * 4 / num_streams; j++) {
                        printf("Fluxo %d: %.2f%+.2fj\n", i, mapped_symbols[i][j].Re, mapped_symbols[i][j].Im);
                    }
                }

                // Libera a memória alocada para a matriz de símbolos mapeados
                for (int i = 0; i < num_streams; i++) {
                    free(mapped_symbols[i]);
                }
                free(mapped_symbols);
            }
        }
    }

    fclose(file); // Fecha o arquivo

    int Nr = 4; // Número de antenas receptoras
    int Nt = 3; // Número de antenas transmissoras

    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios com base no tempo

    float **H = channel_gen(Nr, Nt); // Gera a matriz do canal aleatório

    if (H != NULL) {
        // Imprime a matriz do canal
        for (int i = 0; i < Nr; i++) {
            for (int j = 0; j < Nt; j++) {
                printf("%.2f\t", H[i][j]);
            }
            printf("\n");
        }

        // Libera a memória alocada para a matriz do canal
        for (int i = 0; i < Nr; i++) {
            free(H[i]);
        }
        free(H);
    }

    return 0;
}
