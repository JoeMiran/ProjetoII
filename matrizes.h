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
void printComplex(complex num);
void printTransposta(complexMatrix transposta);
void printConjugada(complexMatrix conjugada);
void printHermitiana(complexMatrix hermitiana);

#endif