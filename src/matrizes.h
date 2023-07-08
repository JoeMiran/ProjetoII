///@file matrizes.h
#ifndef MATRIZES_H
#define MATRIZES_H
#include <stdio.h>
#include <gsl/gsl_linalg.h>
/// Definition of complex structure
typedef struct
{
    float Re, Im; // Fields to store the real (Re) and imaginary (Im) parts
} complex;

/// Definition of the complexMatrix structure
typedef struct
{
    int linhas, colunas; // Fields to store the number of rows and columns
    complex **mtx;       // Defining a pointer of 'mtx' pointers to an matrix of complex numbers
} complexMatrix;

///****************************************** DECLARATION OF COMPLEX FUNCTIONS ****************************************************/
///
///-----> The functions below are being implemented in 'matrizes.c'.
///-----> Below we have only the signatures of the respective functions.
///
complexMatrix allocateComplexMaatrix(int linhas, int colunas);

complexMatrix matrixTransposta(complexMatrix matrix);
complexMatrix matrixConjugada(complexMatrix matrix);
complexMatrix matrixHermitiana(complexMatrix transposta);
complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2);
complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2);
complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num);
complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2);

#endif