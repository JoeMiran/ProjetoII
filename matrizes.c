#include <stdlib.h>
#include <stdio.h>
#include "matrizes.h"

typedef struct {
    float real, imag;
} complex;

typedef struct {
    int linhas, colunas;
    complex** mtx;
} complexMatrix;

//Definido as dimensões da matriz complexa
int linhas = 3;
int colunas = 2;

/*
A função está sendo chamada para alocar memória para a matriz complexa, 
retornando a variável mtx do tipo complexMatrix
*/
complexMatrix mtx = allocateComplexMatrix(linhas, colunas);

//Preenchendo a matriz complexa
for (int l = 0; l < mtx.linhas; ++l) {
    for (int c = 0; c < mtx.colunas; ++c) {
        mtx.mtx[l][c].real = 2 * l;
        mtx.mtx[l][c].imag = 2 * c;
    }
}

//Imprimindo o valor da matriz complexa
for (int l = 0; l < mtx.linhas; ++l) {
    for (int c = 0; c < mtx.colunas; ++c) {
        printf("mtx[%d][%d]: ", l, c);
        printComplex(mtx.mtx[l][c]);
    }
}

/*
Agora a função que foi chamada anteriormente vai alocar memória
para a matriz complexa
*/
complexMatrix allocateComplexMatrix(int linhas, int colunas) {
    
    complexMatrix matrix; //Criando a variável matrix do tipo complexMatrix
    matrix.linhas = linhas;
    matrix.colunas = colunas;

    /*
    Reservando a quantidade de memória necessária para armazenar as linhas
    da matriz complexa 
    */
    matrix.mtx = (complex**)malloc(linhas * sizeof(complex*));
    
    //Caso haja algum erro na alocação, o programa é interrompido
    if (matrix.mtx == NULL) {
        printf("Falha na alocação de memória\n");
        exit(1);
    }

    /*
    Esse laço está percorrendo cada linha da matriz e alocando memória
    para as colunas correspondentes
    */
    for (int i = 0; i < linhas; i++) {
        matrix.mtx[i] = (complex*)malloc(colunas * sizeof(complex));
        
        /*
        Esse if vai verificar se houve algum erro na alocação da memória, assim como o anterios,
        no entando, essa estrutura vai liberar a memória e depois encerrar o programa caso esse
        erro ocorra.
        */
        if (matrix.mtx[i] == NULL) {
            printf("Falha na alocação de memória\n");

            for (int j = 0; j < i; j++) { //Percorre as linhas anteriores a 'i'
                free(matrix.mtx[j]);//Libera a memória alocada para as colunas das linhas
            }
            free(matrix.mtx);//Libera a memória alocada para as linhas

            exit(1);
        }
    }

    return matrix;
}