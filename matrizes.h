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
void freeComplexMatrix(complexMatrix matrix);
void printComplex(complex complex);
void printComplexMatrix(ComplexMatrix matrix);
complexMatrix matrixTransposta(complexMatrix matrix);

#endif
