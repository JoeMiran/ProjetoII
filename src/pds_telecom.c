#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pds_telecom.h"
#include "matrizes.h"


/**
 * @brief Ler a mensagem e um arquivo e converte para um vetor
 * 
 * O objetivo da função em questão é abrir um arquivo de texto para ler seu conteúdo em binário para então converter os dados binários
 * em um vetor de inteiros, onde cada caracter inteiro equivale a 2 bits.
 * 
 * @param file o ponteiro do arquivo será lido
 * @param sequencia_bytes é o número total de bytes do arquivo
 * @param [out] vetor_inteiro O retorno da função é o ponteiro do vetor convertido em questão 
 * 
*/

int *tx_data_read(FILE *file, long int sequencia_bytes) {
    
    int *vetor_inteiro = (int *)malloc(sequencia_bytes * 4 * sizeof(int)); // Aloca memória para o array de inteiros

    if (vetor_inteiro == NULL) { // Verifica se houve falha na alocação de memória
        printf("Erro na alocação de memória\n");
        fclose(file); // Fecha o arquivo
        return NULL; // Retorna NULL em caso de erro
    }
    
    // Lê os bytes do arquivo e converte em inteiros de 2 bits
    int index = 0; // Variável para rastrear a posição atual no array 's'
    for (int i = 0; i < sequencia_bytes; i++) {
        
        char byte;
        fread(&byte, sizeof(byte), 1, file); // Lê um byte do arquivo
        
        for (int j = 0; j <= 6; j += 2) { // Loop para processar os bits do byte
            int bit = (byte >> j) & 0x03; // Extrai o bit correspondente do byte usando deslocamento à direita e uma máscara
            vetor_inteiro[index++] = bit; // Atribui o bit à posição correta no array 's' e incrementa o índice
        }
    }

    return vetor_inteiro; // Retorna o array de inteiros
}

/**
 * @brief A função preenche o vetor de inteiros com zeros.
 * 
 * O objetivo desse preenchimento, ou padding, é garantir que o vetor de inteiros
 * sempre seja do tamanho de um múltiplo inteiro de um determinado número de streams.
 * Se o número de bytes já cumprir essa condição, a função é retornada sem alteração. Caso
 * contrário,a função cria um novo vetor com o tamanho ajustado para acomodar os zeros adicionais.
 * 
 * @param padding O número de zeros que devem ser adicionados
 * @param vetor_inteiro O ponteiro para o vetor de inteiros
 * @param num_streams O número de streams
 * @param sequencia_bytes O número total de bytes do arquivo
 * @param [out] novo_tamanho_vetor Um ponteiro com a tamanho ajustado para o vetor de inteiros
*/

int *tx_data_padding(int padding, int *vetor_inteiro, long int sequencia_bytes) {
    // Verifica se o número de bytes já é um múltiplo do número de streams.
    if (padding == 0) {

        return vetor_inteiro; // Retorna o array original sem alterações.
    
    } else {

        // Calcula o novo tamanho do array de inteiros, levando em conta o padding.
        long int novo_tamanho = sequencia_bytes * 4 + padding;

        // Aloca memória para o novo array de inteiros.
        int *novo_tamanho_vetor = (int *)malloc(novo_tamanho * sizeof(int));
        if (novo_tamanho_vetor == NULL) {
            return NULL; // Retorna NULL em caso de erro na alocação de memória.
        }

        // Copia os elementos do array original para o novo array de tamanho ajustado.
        for (long int i = 0; i < sequencia_bytes * 4; i++) {
            novo_tamanho_vetor[i] = vetor_inteiro[i];
        }

        // Preenche o espaço adicional com zeros (representados pelo inteiro 0).
        for (long int i = sequencia_bytes * 4; i < novo_tamanho; i++) {
            novo_tamanho_vetor[i] = 0;
        }

        return novo_tamanho_vetor; // Retorna o novo array com o padding realizado.
    }
}

/**
 * @brief A função faz o mapeamento dos valores binários em QAM
 * 
 * Primeiro a função se preocupa em alocar dinamicamente a memória para um vetor
 * complex e em seguida percorre cada elemento do vetor de inteiros e realiza o
 * mapeamento correspondente para o vetor complex
 * 
 * @param [in] vetor_inteiro O ponteiro para o vetor de inteiros
 * @param [in] tam_vetor_qam tamanho do vetor qam em bytes
 * @param [out] simbolo Um ponteiro para o array que armazena os simbolos qam após o mapeamento
 * 
*/

// Função para mapear os índices para números complexs QAM
complex *tx_qam_mapper(int *vetor_inteiro, long int tam_vetor_qam) {
    
    complex *simbolo = (complex *)malloc(tam_vetor_qam * sizeof(complex)); // Aloca memória para o vetor de complexs

    if (simbolo == NULL) { // Verifica se houve falha na alocação de memória
        printf("Erro na alocação de memória\n");
        return NULL; // Retorna NULL em caso de erro
    }

    // Mapeia os índices para os números complexs da constelação QAM
    for (int i = 0; i < tam_vetor_qam; i++) {
        switch (vetor_inteiro[i]) {
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

    return simbolo; // Retorna o vetor de complexs
}

/**
 * @brief Obtem os dados de vetor e os mapeia em uma matriz complexa 
 * 
 * Essa função realiza o mapeamento dos dados de um vetor complex em uma matriz complexa, 
 * com o objetivo de dividir os dados em diferentes camadas (streams) para transmissão 
 * ou processamento posterior, retornando um ponteiro para a matriz complexa mapeada
 * 
 * @param vetor_complex Ponteiro para o vetor complex
 * @param num_stream Número de streams, indicando quantas linhas a matriz resultante terá
 * @param num_simbolo Número de simbolos, indicando quantos elementos serão mapeados na 
 * matriz resultante
 * @param [out] mtx_resultante matriz de complexs resultante devidamente mapeada
*/

complex **tx_layer_mapper(complex *vetor_complex, int num_stream, long int num_simbolo) {
    // Aloca memória para a matriz de complexs
    complex **mtx_resultante = (complex **)malloc(num_stream * sizeof(complex *));
    
    // Verifica se houve falha na alocação de memória
    if (mtx_resultante == NULL) {
        printf("Erro na alocação de memória\n");
        return NULL; // Retorna NULL em caso de erro
    }
    // Aloca memória para cada linha da matriz de complexs
    for (int i = 0; i < num_stream; i++) {
        mtx_resultante[i] = (complex *)malloc((num_simbolo / num_stream) * sizeof(complex));

        // Verifica se houve falha na alocação de memória
        if (mtx_resultante[i] == NULL) {
            printf("Erro na alocação de memória\n");

            // Libera a memória alocada anteriormente
            for (int j = 0; j < i; j++) {
                free(mtx_resultante[j]);
            }
            free(mtx_resultante);
            return NULL; // Retorna NULL em caso de erro
        }
    }

    // Mapeia os dados do vetor para a matriz de complexs
    for (int i = 0; i < num_simbolo; i++) {
        int streamIndex = i % num_stream; // Índice da linha da matriz
        int symbolIndex = i / num_stream; // Índice da coluna da matriz
        mtx_resultante[streamIndex][symbolIndex] = vetor_complex[i];
    }

    return mtx_resultante; // Retorna a matriz de complexs
}

//Funcao para gerar um numero aleatorio entre -1 e 1
float gerar_float_aleatorio() {
    return -1.0 + ((float)rand() / (float)RAND_MAX) * 2.0;
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

        complex *map = tx_qam_mapper(resultado, file_size * 4); // Mapeia os índices para números complexs QAM

        if (map != NULL) {
            // Imprime os números complexs
            for (int i = 0; i < file_size * 4; i++) {
                printf("Índice %d: %.2f%+.2fj\n ", i, map[i].Re, map[i].Im);
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

                // // Executa o demapeamento dos símbolos para obter o vetor de complexs original
                // complex *demapped_symbols = rx_layer_demapper(mapped_symbols, num_streams, file_size * 4);

                // if (demapped_symbols != NULL) {
                //     // Imprime os símbolos demapeados
                //     for (int i = 0; i < file_size * 4; i++) {
                //         printf("Índice %d: %.2f%+.2fj\n", i, demapped_symbols[i].Re, demapped_symbols[i].Im);
                //     }

                //     // Libera a memória alocada para o vetor de complexs demapeado
                //     free(demapped_symbols);
                // }

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