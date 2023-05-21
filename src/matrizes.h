#ifndef MATRIZES_H
#define MATRIZES_H
#include <stdio.h>

//Defini��o da estrutura complexa
typedef struct {
    float Re, Im; //Campos para armazenar a parte real(Re) e imagin�ria (Im)
} complex;

//Defini��o da estrutura complexMatrix
typedef struct {
    int linhas, colunas; //Campos para armazenar o n�mero de linhas e de colunas
    complex** mtx; //Defini��o de um ponteiro de ponteiros 'mtx' para uma matriz de n�meros complexos
} complexMatrix;


/****************************************** DECLARA��O DAS FUN��ES COMPLEXAS ****************************************************/
/*
-----> As fun��es abaixo est�o sendo implementadas em 'matrizes.c'.
-----> Abaixo temos apenas as assinaturas das respectivas fun��es.
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