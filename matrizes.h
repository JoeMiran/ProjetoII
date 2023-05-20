#ifndef MATRIZES_H
#define MATRIZES_H
#include <stdio.h>

typedef struct {
    float Re, Im;
} complex;

typedef struct {
    int linhas, colunas;
    complex** mtx;
} complexMatrix;

complexMatrix allocateComplexMaatrix(int linhas, int colunas);
complexMatrix matrixTransposta(complexMatrix matrix);
complexMatrix matrixConjugada(complexMatrix matrix);
complexMatrix matrixHermitiana(complexMatrix transposta);
complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2);
complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2);
complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num);
complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2);
void printComplex(complex num);
void printMatrix(complexMatrix matrix);
void printMatrix1(complexMatrix matrix1);
void printMatrix2(complexMatrix matrix2);
void printTransposta(complexMatrix transposta);
void printConjugada(complexMatrix conjugada);
void printHermitiana(complexMatrix hermitiana);
void printSoma(complexMatrix soma);
void printSubtracao(complexMatrix subtracao);
void print_produtoEscalar(complexMatrix produtoEscalar);
void printProduto(complexMatrix produto);

#endif