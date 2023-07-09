#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

int* tx_data_read(const char* filename, long* file_size) {
    // Abrindo o arquivo no modo leitura binária
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    // Descobrindo o tamanho do arquivo para saber o quanto de memória deve ser alocada
    fseek(file, 0, SEEK_END); // Posicionando o ponteiro no final do arquivo
    *file_size = ftell(file); // Retornando a posição atual do ponteiro para obter o tamanho do arquivo em bytes
    fseek(file, 0, SEEK_SET); // Marcando o ponteiro no início do arquivo para que todas as leituras aconteçam a partir do início

    // Alocando memória para armazenar o conteúdo do arquivo
    unsigned char* content = (unsigned char*)malloc(*file_size);
    if (content == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return NULL;
    }

    // Lendo o arquivo completo
    fread(content, 1, *file_size, file);
    fclose(file);

    // Calculando o tamanho da sequência de dígitos
    int sequence_length = *file_size * 4;

    // Alocando memória para armazenar os números inteiros resultantes
    int* decimal_sequence = (int*)malloc(sequence_length * sizeof(int));
    if (decimal_sequence == NULL) {
        printf("Erro ao alocar memória.\n");
        free(content);
        return NULL;
    }

    // Convertendo os bytes em sequência de dígitos
    int index = 0;
    for (int i = 0; i < *file_size; i++) {
        decimal_sequence[index++] = (content[i] >> 6) & 0x03;
        decimal_sequence[index++] = (content[i] >> 4) & 0x03;
        decimal_sequence[index++] = (content[i] >> 2) & 0x03;
        decimal_sequence[index++] = content[i] & 0x03;
    }

    // Liberando a memória alocada para o conteúdo do arquivo
    free(content);

    return decimal_sequence;
}

void rx_data_write(const char* filename, const int* decimal_sequence, int sequence_length) {
    // Abrindo o arquivo no modo escrita binária
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Convertendo a sequência de dígitos de volta para bytes e escrevendo no arquivo
    for (int i = 0; i < sequence_length; i += 4) {
        unsigned char byte = 
        (decimal_sequence[i] << 6) |
        (decimal_sequence[i + 1] << 4) |
        (decimal_sequence[i + 2] << 2) |
        decimal_sequence[i + 3];
        fwrite(&byte, sizeof(unsigned char), 1, file);
    }

    fclose(file);
}

complexMatrix* tx_qam_mapper(const int* indices, int lenght) {
    //Alocando memoria para armazenar a matriz de numeros complexos resultantes
    complexMatrix* symbols = (complexMatrix*)malloc(sizeof(complexMatrix));
    if (symbols == NULL) {
        printf("Erro na alocacao de memoria\n");
        return;
    }

    //Definindo um numero de linhas e colunas para uma matriz unidimensional
    symbols->linhas = lenght;
    symbols->colunas = 1;

    //Alocar memoria para armazenar os numeros complexos
    symbols->mtx = (complex**)malloc(lenght * sizeof(complex*));
    if (symbols->mtx == NULL) {
        printf("Erro ao alocar memoria\n");
        return;
    }

    //Vendo os cada um dos casos possíveis do índice a atribuindo os valores das partes reais e imaginárias com base nisso
    switch (indices[i]) {
        caso 0:
            symbols->mtx[i]->Re = -1;
            symbols->mtx[i]->Im =  1;
        break;
        
        caso 1:
            symbols->mtx[i]->Re = -1;
            symbols->mtx[i]->Im = -1;
        break;
        
        caso 2:
            symbols->mtx[i]->Re = 1;
            symbols->mtx[i]->Im = 1;
        break;
        
        caso 3:
            symbols->mtx[i]->Re =  1;
            symbols->mtx[i]->Im = -1;
        break;
    default    
    }

    return symbols;

}

int main() {
    const char* filename = "MIMO.txt";
    long file_size;

    // Realiza a leitura do arquivo e obtém a sequência de dígitos
    int* resultado = tx_data_read(filename, &file_size);

    if (resultado != NULL) {
        // Imprime o vetor resultante
        for (int i = 0; i < file_size * 4; i++) {
            printf("%d ", resultado[i]);
        }
        printf("\n");

        // Escreve a sequência de dígitos no arquivo binário
        rx_data_write("MIMO_output.bin", resultado, file_size * 4);

        //Mapeia os indices para os numeros complexos da constelacao qam
        complexMatrix* symbols = qam_mapper(resultado, file_size * 4);
        if (symbols != NULL){
            //Imprime os numeros complexos
            for(int i = 0; i < symbols->linhas; i++) {
                printf("O numero complexo %d: %f + %fj\n", i, symbols->mtx[i]->Re, symbols->myx[i]->Im);
            }
        }

        // Libera a memória alocada
        free(resultado);
    }

    return 0;
}