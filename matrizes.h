#ifndef MATRIZES_H
#define MATRIZES_H
#include <stdio.h>

//Definição da estrutura complexa
typedef struct {
    float Re, Im; //Campos para armazenar a parte real(Re) e imaginária (Im)
} complex;

//Definição da estrutura complexMatrix
typedef struct {
    int linhas, colunas; //Campos para armazenar o número de linhas e de colunas
    complex** mtx; //Definição de um ponteiro de ponteiros 'mtx' para uma matriz de números complexos
} complexMatrix;


/****************************************** DECLARAÇÃO DAS FUNÇÕES COMPLEXAS ****************************************************/
/*
-----> As funções abaixo estão sendo implementadas em 'matrizes.c'.
-----> Abaixo temos apenas as assinaturas das respectivas funções.
*/
complexMatrix allocateComplexMaatrix(int linhas, int colunas);
complexMatrix matrixTransposta(complexMatrix matrix);
complexMatrix matrixConjugada(complexMatrix matrix);
complexMatrix matrixHermitiana(complexMatrix transposta);
complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2);
complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2);
complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num);
complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2);

#endif