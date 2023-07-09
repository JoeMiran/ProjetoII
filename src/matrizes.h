/**
 * @file matrizes.h
 * @brief Header file for complex matrix operations.
 */

#ifndef MATRIZES_H
#define MATRIZES_H
#include <stdio.h>
#include <gsl/gsl_linalg.h>

/*! 
* @brief Definition of the complex structure.
*/
typedef struct
{
    float Re, Im; /*!< Slots to store the real(Re) and imaginary(Im) parts */ 
} complex;

/*! 
* @brief Definition of the complexMatrix structure.
*/
typedef struct
{
    int linhas, colunas; /*!< Fields to store the number of rows and columns */
    complex **mtx;       /*!< Definition of a pointer to pointer 'mtx' for a matrix of complex numbers */
} complexMatrix;

/******************************** DECLARAÇÃO DAS FUNÇÕES COMPLEXAS ********************************/

/**
 * @brief Dynamically allocates a complex matrix.
 *
 * This function dynamically allocates memory for a complex matrix with the given number of rows and columns.
 *
* @param linhas The number of rows of the matrix.
 * @param colunas The number of columns of the matrix.
 * @return The complexMatrix object representing the allocated complex matrix.
 */
complexMatrix allocateComplexMatrix(int linhas, int colunas);

/**
 * @brief Calculates the transpose of a complex matrix.
 *
 * This function calculates and returns the transpose of the given complex matrix.
 *
 * @param matrix The complexMatrix object for which the transpose will be calculated.
 * @return The complexMatrix object representing the transpose matrix.
 */
complexMatrix matrixTransposta(complexMatrix matrix);

/**
 * @brief Calculates the conjugate matrix of a complex matrix.
 *
 * This function calculates and returns the conjugate matrix of the given complex matrix.
 *
 * @param matrix The complexMatrix object for which the conjugate will be calculated.
 * @return The complexMatrix object representing the conjugate matrix.
 */
complexMatrix matrixConjugada(complexMatrix matrix);

/**
 * @brief Calculates the Hermitian matrix of a complex matrix.
 *
 * This function calculates and returns the Hermitian matrix of the given complex matrix.
 * The Hermitian matrix is the conjugate transpose of the matrix.
 *
 * @param transposta The complexMatrix object representing the transpose of the original matrix.
 * @return The complexMatrix object representing the Hermitian matrix.
 */
complexMatrix matrixHermitiana(complexMatrix transposta);

/**
 * @brief Calculates the sum of two complex matrices.
 *
 * This function calculates and returns the sum of the two given complex matrices.
 *
 * @param matrix1 The first complexMatrix to be summed.
 * @param matrix2 The second complexMatrix to be summed.
 * @return The complexMatrix object representing the resulting sum matrix.
 */
complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2);

/**
 * @brief Calculates the subtraction of two complex matrices.
 *
 * This function calculates and returns the subtraction of the two given complex matrices.
 *
 * @param matrix1 The complexMatrix to be subtracted.
 * @param matrix2 The complexMatrix to be subtracted from matrix1.
 * @return The complexMatrix object representing the resulting subtraction matrix.
 */
complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2);

/**
 * @brief Calculates the product of a complex matrix by a scalar.
 *
 * This function calculates and returns the product of a complex matrix by the given scalar.
 *
 * @param matrix The complexMatrix to be multiplied by the scalar.
 * @param num The scalar to be multiplied by the matrix.
 * @return The complexMatrix object representing the resulting scalar product matrix.
 */
complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num);

/**
 * @brief Calculates the product of two complex matrices.
 *
 * This function calculates and returns the product of the two given complex matrices.
 *
 * @param matrix1 The first complexMatrix to be multiplied.
 * @param matrix2 The second complexMatrix to be multiplied.
 * @return The complexMatrix object representing the resulting product matrix.
 */
complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2);

#endif