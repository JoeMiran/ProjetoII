#ifndef MATRIZES_H
#define MATRIZES_H
#include <stdio.h>

typedef struct {
  float real, imag;
} complex;

typedef struct {
    int linhas, colunas;
    complex** mtx;
} complexMatrix;

complexMatrix allocateComplexMatrix(int linhas, int colunas);
void printComplex(complex num);
complexMatrix matrixTransposta(complexMatrix matrix);

#endif
