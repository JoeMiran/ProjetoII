/**
 * @file matrizes.c
 * @brief Implementation file for complex matrix operations.
 */

#include <stdio.h>
#include <stdlib.h>

/// including the files where the structure is contained
#include "matrizes.h"

/// including the GSL library
#include <gsl/gsl_linalg.h>

/************************************* FUNCTIONS FOR ALLOCATION OF MEMORY ***************************************/
/**
 *
 * @param [in] linhas
 * @param [in] colunas
 * @param [out] matrix
 *
 */

//! Creating a function whose purpose is to dynamically allocate memory for the complex matrix
complexMatrix allocateComplexMatrix(int linhas, int colunas) {

    //! Declaring the matrix variable of type ComplexMatrix
    complexMatrix matrix;

    //! The complexMatrix type variable has rows and columns "attributes" and must receive them as parameters
    matrix.linhas = linhas;
    matrix.colunas = colunas;

    //! Allocating memory for matrix lines
    matrix.mtx = (complex **)malloc(linhas * sizeof(complex *));

   /**
 * @brief Handles possible errors when trying to allocate memory to the rows of a matrix.
 *
 * This code checks if the memory allocation for the rows of the matrix was successful. If the allocation failed, it prints an error message and terminates the program with an exit code of 1.
 */
if (matrix.mtx == NULL)
{
    printf("Falha na alocacao de memoria\n");
    exit(1);
}

    /**
 * @brief Allocates memory for the columns of each line in the matrix.
 *
 * This code iterates over each row of the matrix and allocates memory for the columns of each line. It uses the `malloc` function to allocate memory for an array of `colunas` complex numbers (`complex`).
 */
    for (int i = 0; i < linhas; i++)
    {
        matrix.mtx[i] = (complex *)malloc(colunas * sizeof(complex));

       /**
 * @brief Handles possible errors when allocating memory to the columns of each line in the matrix.
 *
 * This code checks if the memory allocation for the columns of each line in the matrix was successful. If the allocation failed (for example: `matrix.mtx[i]` is `NULL`), it prints an error message and terminates the program with an exit code of 1.
 */
        if (matrix.mtx[i] == NULL)
        {
            printf("Falha na alocação de memória\n");
            exit(1);
        }
    }

    //! Returning matrix
    return matrix;
}

/************************ SVD CALCULATION FUNCTIONS **************************/
/**
 * @brief Performs the implementation for Singular Value Decomposition (SVD) calculation.
 * @param [in] matrix
*/

/// This function does the implementation for the SVD calculation
void calc_svd(complexMatrix matrix) 
{
    
    int i = 0;
    int j = 0;

    /**
 * @brief Checks if the matrix is complex.
 *
 * This code snippet checks if the elements in the matrix are complex numbers. It specifically checks if the imaginary part (`Im`) of an element at position `matrix.mtx[i][j]` is non-zero. If it is non-zero, the code prints a message indicating that the matrix is complex, and therefore, only the real part will be used for SVD calculation.
 */
    if (matrix.mtx[i][j].Im != 0) {
        printf("A matriz e complexa, portanto sera calculado o SVD apenas da parte real.\n");
    }


   /**
 * @brief Generates a GSL matrix using the real part of the complex matrix.
 *
 * This code snippet allocates memory for a GSL matrix (`gsl_matrix`) with the same number of rows and columns as the complex matrix (`matrix`). The matrix is allocated using the `gsl_matrix_alloc` function from the GSL. It is intended to be used for storing the real part of the complex matrix during further computations.
 *
 * @param matrix The complexMatrix object from which the real part will be extracted to generate the GSL matrix.
 *
 * @return A pointer to the allocated GSL matrix.
 */
gsl_matrix* gslMatrix = gsl_matrix_alloc(matrix.linhas, matrix.colunas);

    /**
 * @brief Assigns the values of the real part of the parameter matrix to the gslMatrix matrix.
 *
 * This code snippet iterates over the rows and columns of the `matrix` parameter and assigns the real part of each element to the corresponding position in the `gslMatrix` matrix using the `gsl_matrix_set` function.
 *
 * @param gslMatrix The gsl_matrix object to which the values will be assigned.
 * @param matrix The complexMatrix parameter from which the real part values will be extracted.
 */
    for (i = 0; i < matrix.linhas; i++) {
        for (j=0; j < matrix.colunas; j++){
        gsl_matrix_set(gslMatrix, i, j, matrix.mtx[i][j].Re);
    }
}

    /**
 * @brief Performing SVD decomposition.
 *
 * This code snippet performs Singular Value Decomposition (SVD) on the provided matrix. It allocates memory for the required GSL objects and performs the SVD decomposition using the GSL library.
 *
 * @param matrix The complexMatrix object on which the SVD decomposition will be performed.
 * @param A The GSL matrix object allocated for SVD decomposition.
 * @param V The GSL matrix object allocated for SVD decomposition.
 * @param S The GSL vector object allocated for SVD decomposition.
 * @param work The GSL vector object allocated for SVD decomposition.
 */
    gsl_matrix *A = gsl_matrix_alloc(matrix.linhas, matrix.colunas);
    gsl_matrix *V = gsl_matrix_alloc(matrix.colunas, matrix.colunas);
    gsl_vector *S = gsl_vector_alloc(matrix.colunas);
    gsl_vector *work = gsl_vector_alloc(matrix.colunas);

   /**
 * @brief Calling the function that performs SVD calculation.
 *
 * This code snippet calls the GSL function gsl_linalg_SV_decomp to perform the Singular Value Decomposition (SVD) calculation. The function takes the GSL matrix A, GSL matrix V, GSL vector S, and GSL vector work as arguments.
 *
 * @param A The GSL matrix object for SVD decomposition.
 * @param V The GSL matrix object for SVD decomposition.
 * @param S The GSL vector object for SVD decomposition.
 * @param work The GSL vector object for SVD decomposition.
 */
    gsl_linalg_SV_decomp(A, V, S, work);

    /**
 * @brief Printing the results of SVD decomposition.
 *
 * This code snippet prints the results of the Singular Value Decomposition (SVD) calculation. It prints the matrix A, vector S, and matrix V using the GSL library functions and appropriate formatting.
 */
    printf("\nMatrix A:\n");
    for (i = 0; i < A->size1; i++) {
        for (j = 0; j < A->size2; j++) {
            if(j ==0){
            printf("|%.2f\t", gsl_matrix_get(A, i, j));
        } else if (j == A->size2 - 1) {
            printf("%.2f|\t", gsl_matrix_get(A, i, j));
        } else {
            printf("%.2f\t", gsl_matrix_get(A, i, j));
        }
    }
    printf("\n");
}

printf("\nVetor S:\n");
for (int i = 0; i < S->size; i++) {
    printf("|%.2f|\n", gsl_vector_get(S, i));
}

printf("\nMatriz V:\n");
for (int i = 0; i < V->size1; i++) {
    for (int j = 0; j < V->size2; j++) {
        if (j == 0) {
            printf("|%.2f\t", gsl_matrix_get(V, i, j));
        } else if (j == V->size2 - 1) {
            printf("%.2f|\t", gsl_matrix_get(V, i, j));
            }
            else{
                printf("%.2f\t", gsl_matrix_get(V, i, j));
            }
        }
        printf("\n");
    }
    
    /**
 * @brief Releasing memory allocated for GSL objects.
 *
 * This code snippet releases the memory allocated for the GSL objects used in the SVD decomposition. It frees the memory for the GSL matrices A and V, GSL vector S and work, and the GSL matrix gslMatrix.
 *
 * @param A The GSL matrix object to be freed.
 * @param V The GSL matrix object to be freed.
 * @param S The GSL vector object to be freed.
 * @param work The GSL vector object to be freed.
 * @param gslMatrix The GSL matrix object to be freed.
 */
    gsl_matrix_free(A);
    gsl_matrix_free(V);
    gsl_vector_free(S);
    gsl_vector_free(work);
    gsl_matrix_free(gslMatrix);
}

/**
 * @brief Freeing memory allocated for a complex matrix.
 *
 * This function frees the memory allocated for a complex matrix by iterating over its rows and then freeing the memory for each row.
 *
 * @param matrix The complexMatrix object to be freed.
 */
void freeComplexMatrix(complexMatrix matrix)
{
    for (int i = 0; i < matrix.linhas; i++) {
        free(matrix.mtx[i]);
    }
    free(matrix.mtx);
}

//! Function that will perform all the tests and print the results in the terminal
void teste_calc_svd() {
     /**
     * @brief Test case 1: Matrix 3x2
     *
     * This test case focuses on a matrix of size 3x2. It demonstrates the process of allocating memory for the matrix.
     */
    printf("\n========= Matriz 3x2 =========\n");
    
    /**
    * @brief Allocating memory for the matrix and putting values in it.
    *
    * This code snippet allocates memory for a complex matrix of size 3x2 using the `allocateComplexMatrix` function. It then assigns values to the elements of the matrix by iterating over the rows and columns.
    */
    complexMatrix matrixA = allocateComplexMatrix(3, 2);
    
    /** 
     * @brief putting values in the matrix
    */
    for (int i = 0; i < matrixA.linhas; i++) {
        for (int j = 0; j < matrixA.colunas; j++) {
            matrixA.mtx[i][j].Re = i + j + 1;
            matrixA.mtx[i][j].Im = i + j + 1.5;
        }
    }

    printf("\nMatriz de entrada:\n");
    for (int i = 0; i < matrixA.linhas; i++) {
        for (int j = 0; j < matrixA.colunas; j++) {
            if (j == 0) {
                printf("|%.1f + %.1fi\t", matrixA.mtx[i][j].Re, matrixA.mtx[i][j].Im);
            } else if (j == matrixA.colunas - 1) {
                printf("%.1f + %.1fi|\t", matrixA.mtx[i][j].Re, matrixA.mtx[i][j].Im);
            } else {
                printf("%.1f + %.1fi\t", matrixA.mtx[i][j].Re, matrixA.mtx[i][j].Im);
            }
        }
        printf("\n");
    }
    
    printf("\n");
    calc_svd(matrixA);
    printf("\n");

    /**
     * @brief Test case 2: Matrix 4x4
     *
     * This test case focuses on a matrix of size 4x4. It demonstrates the process of allocating memory for the matrix and putting values in it.
     */
    printf("\n========= Matriz 4x4 =========\n");
    complexMatrix matrixB = allocateComplexMatrix(4, 4);
    
    for (int i = 0; i < matrixB.linhas; i++) {
        for (int j = 0; j < matrixB.linhas; j++) {
            matrixB.mtx[i][j].Re = i + j + 3.2;
            matrixB.mtx[i][j].Im = 0;
        }
    }

    printf("\nMatriz de entrada:\n");
    for (int i = 0; i < matrixB.linhas; i++) {
        for (int j = 0; j < matrixB.colunas; j++) {
            if (j == 0) {
                printf("|%.1f\t", matrixB.mtx[i][j].Re);
            } else if (j == matrixB.colunas - 1) {
                printf("%.1f|\t", matrixB.mtx[i][j].Re);
            } else {
                printf("%.1f\t", matrixB.mtx[i][j].Re);
            }
        }
        printf("\n");
    }

    calc_svd(matrixB);
    printf("\n");

    /**
     * @brief Test case 3: Matrix 6x5
     *
     * This test case focuses on a matrix of size 6x5. It demonstrates the process of allocating memory for the matrix and putting values in it.
     */
    printf("\n========= Matriz 6x5 =========\n");
    complexMatrix matrixC = allocateComplexMatrix(6, 5);
    
    for (int i = 0; i < matrixC.linhas; i++) {
        for (int j = 0; j < matrixC.linhas; j++) {
            matrixC.mtx[i][j].Re = i + j + 5;
            matrixC.mtx[i][j].Im = 0;
        }
    }

    printf("\nMatriz de entrada:\n");
    for (int i = 0; i < matrixC.linhas; i++) {
        for (int j = 0; j < matrixC.colunas; j++) {
            if (j == 0) {
                printf("|%.1f\t", matrixC.mtx[i][j].Re);
            } else if (j == matrixC.colunas - 1) {
                printf("%.1f|\t", matrixC.mtx[i][j].Re);
            } else {
                printf("%.1f\t", matrixC.mtx[i][j].Re);
            }
        }
        printf("\n");
    }
    
    calc_svd(matrixC);
    printf("\n");

    /**
     * @brief Test case 4: Matrix 5x6
     *
     * This test case focuses on a matrix of size 5x6. It demonstrates the process of allocating memory for the matrix and putting values in it.
     */
    printf("\n========= Matriz 5x6 =========\n");
    complexMatrix matrixD = allocateComplexMatrix(5, 6);
    
    for (int i = 0; i < matrixD.linhas; i++) {
        for (int j = 0; j < matrixD.linhas; j++) {
            matrixD.mtx[i][j].Re = i + j + 2.5;
            matrixD.mtx[i][j].Im = 0;
        }
    }

    printf("\nMatriz de entrada:\n");
    for (int i = 0; i < matrixD.linhas; i++) {
        for (int j = 0; j < matrixD.colunas; j++) {
            if (j == 0) {
                printf("|%.1f\t", matrixD.mtx[i][j].Re);
            } else if (j == matrixD.colunas - 1) {
                printf("%.1f|\t", matrixD.mtx[i][j].Re);
            } else {
                printf("%.1f\t", matrixD.mtx[i][j].Re);
            }
        }
        printf("\n");
    }

    calc_svd(matrixD);
    printf("\n");
}

/************************************* OPERATION FUNCTIONS ***************************************/

/**
 * @param[in] matrix The original matrix
 * @param[out] transposta The transposed matrix
 *
 * @brief Creating a function to calculate the transposed matrix.
 *
 * This function takes the original matrix as input and calculates the transposed matrix. It allocates memory for the transposed matrix and then goes through each element of the original matrix, setting the corresponding element in the transposed matrix. The rows and columns are switched in the transposed matrix.
 *
 * @return The transposed matrix.
 */
complexMatrix matrixTransposta(complexMatrix matrix)
{

    /**
     * @brief Allocating memory for the complex matrix.
     */
    complexMatrix transposta = allocateComplexMatrix(matrix.colunas, matrix.linhas);

    //! Looping through each element of the original matrix
    for (int i = 0; i < matrix.linhas; i++)
    {
        for (int j = 0; j < matrix.colunas; j++)
        {
            //! Setting the actual element of the original matrix current value to the transposed one
            //! Switching the rows and columns positions in the transposed matrix
            transposta.mtx[j][i].Re = matrix.mtx[i][j].Re;
            transposta.mtx[j][i].Im = matrix.mtx[i][j].Im;
        }
    }
    return transposta;
}


/**
 * @param[in] matrix The original matrix
 * @param[out] conjugada The conjugate matrix
 *
 * @brief Creating a function to calculate the conjugate matrix.
 *
 * This function takes the original matrix as input and calculates the conjugate matrix. It allocates memory for the conjugate matrix and then iterates through each element of the original matrix, setting the corresponding element in the conjugate matrix. The imaginary part of each element is reversed in sign.
 *
 * @return The conjugate matrix.
 */
complexMatrix matrixConjugada(complexMatrix matrix)
{

    //! Allocating memory to the conjugate matrix using the allocateComplexMaatrix function 
    complexMatrix conjugada = allocateComplexMatrix(matrix.colunas, matrix.linhas);

    //! Loop for going through each original matrix element 
    for (int i = 0; i < matrix.linhas; i++)
    {
        for (int j = 0; j < matrix.colunas; j++)
        {
            //! Setting the value of the current element of the original matrix to the conjugate matrix
            conjugada.mtx[i][j].Re = matrix.mtx[i][j].Re;
            conjugada.mtx[i][j].Im = -matrix.mtx[i][j].Im; /*!< Reverses the sign of the imaginary part*/
        }
    }

    //! Returning the conjugate matrix
    return conjugada;
}


/**
 * @param[in] transposta The transposed matrix
 * @param[out] hermitiana The Hermitian matrix
 *
 * @brief Creating a function to calculate the Hermitian matrix.
 *
 * This function takes the transposed matrix as input and calculates the Hermitian matrix. It allocates memory for the Hermitian matrix and then iterates through each element of the transposed matrix, setting the corresponding element in the Hermitian matrix. The sign of the imaginary part of each element is reversed.
 *
 * @return The Hermitian matrix.
 */
complexMatrix matrixHermitiana(complexMatrix transposta)
{

     /**
     * @brief Allocating memory for the Hermitian matrix using the allocateComplexMatrix function.
     */
    complexMatrix hermitiana = allocateComplexMatrix(transposta.colunas, transposta.linhas);

     /**
     * @brief Loop for iterating through each element of the transposed matrix.
     */
    for (int i = 0; i < transposta.linhas; i++)
    {
        for (int j = 0; j < transposta.colunas; j++)
        {
            //! Assigning the value of the current element of the transposed matrix to the Hermitian matrix
            hermitiana.mtx[i][j].Re = transposta.mtx[i][j].Re;
            hermitiana.mtx[i][j].Im = -transposta.mtx[i][j].Im; /*!< Reverses the sign of the imaginary part*/
        }
    }

    //! Returns the Hermitian matrix
    return hermitiana;
}

/**
 * @param[in] matrix1 The first matrix
 * @param[in] matrix2 The second matrix
 * @param[out] soma The sum matrix
 *
 * @brief Creating a function to calculate the sum of two matrices.
 *
 * This function takes two matrices, matrix1 and matrix2, as input and calculates the sum of the corresponding elements. It allocates memory for the sum matrix and then iterates through each element of matrix1 and matrix2, summing the corresponding elements and assigning the result to the sum matrix.
 *
 * @return The sum matrix.
 */
complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2)
{
    /**
    * @brief Allocating memory for the sum matrix using the allocateComplexMatrix function.
    */
    complexMatrix soma = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    /**
     * @brief Loop for iterating through each element of matrix1 and matrix2 (assuming they have the same dimensions).
     */
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            //! Summing the corresponding elements and assigning the result to the sum matrix
            soma.mtx[l][c].Re = matrix1.mtx[l][c].Re + matrix2.mtx[l][c].Re;
            soma.mtx[l][c].Im = matrix1.mtx[l][c].Im + matrix2.mtx[l][c].Im;
        }
    }

    //! Returning the sum matrix
    return soma;
}

/**
 * @param[in] matrix1 The first matrix
 * @param[in] matrix2 The second matrix
 * @param[out] subtracao The subtraction matrix
 *
 * @brief Creating a function to calculate the subtraction between two matrices.
 *
 * This function takes two matrices, matrix1 and matrix2, as input and calculates the subtraction of the corresponding elements. It allocates memory for the subtraction matrix and then iterates through each element of matrix1 and matrix2, subtracting the corresponding elements and assigning the result to the subtraction matrix.
 *
 * @return The subtraction matrix.
 */
complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2)
{

    /**
     * @brief Allocating memory for the subtraction matrix using the allocateComplexMatrix function.
     */
    complexMatrix subtracao = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

     /**
     * @brief Loop for iterating through each element of matrix1 and matrix2 (assuming they have the same dimensions).
     */
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            //! Subtracting the corresponding elements and assigning the result to the subtraction matrix
            subtracao.mtx[l][c].Re = matrix1.mtx[l][c].Re - matrix2.mtx[l][c].Re;
            subtracao.mtx[l][c].Im = matrix1.mtx[l][c].Im - matrix2.mtx[l][c].Im;
        }
    }

    //! Returning the subtraction matrix
    return subtracao;
}


/**
 * @param[in] matrix The original matrix
 * @param[in] num The scalar number
 * @param[out] produtoEscalar The result matrix after scalar multiplication
 *
 * @brief Creating a function to perform scalar multiplication with each element of the original matrix.
 *
 * This function takes a matrix, matrix, and a scalar number, num, as input and performs scalar multiplication by multiplying each element of the matrix by the scalar number. It allocates memory for the result matrix and then iterates through each element of the original matrix, multiplying the corresponding elements by the scalar number and assigning the result to the product matrix.
 *
 * @return The result matrix after scalar multiplication.
 */
complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num)
{
    /**
    * @brief Allocating memory for the result matrix of scalar multiplication using the allocateComplexMatrix function.
    */
    complexMatrix produtoEscalar = allocateComplexMatrix(matrix.linhas, matrix.colunas);

    /**
     * @brief Loop for iterating through each element of the original matrix.
     */
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {
            //! Multiplying the scalar number to each element of the original matrix and assigning the result to the elements of the product matrix.
            produtoEscalar.mtx[l][c].Re = matrix.mtx[l][c].Re * num;
            produtoEscalar.mtx[l][c].Im = matrix.mtx[l][c].Im * num;
        }
    }

    //! Returning the result matrix after scalar multiplication.
    return produtoEscalar;
}


/**
 * @param[in] matrix1 The first matrix
 * @param[in] matrix2 The second matrix
 * @param[out] produto The result matrix after multiplication
 *
 * @brief Creating a function to perform matrix multiplication between matrix1 and matrix2.
 *
 * This function takes two matrices, matrix1 and matrix2, as input and performs matrix multiplication by multiplying the corresponding elements of the matrices. It allocates memory for the result matrix and then iterates through each element of the matrices, multiplying the corresponding elements and assigning the result to the product matrix.
 *
 * @return The result matrix after matrix multiplication.
 */
complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2)
{
    /**
     * @brief Allocating memory for the result matrix of matrix multiplication using the allocateComplexMatrix function.
     */
    complexMatrix produto = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

     /**
     * @brief Loop for iterating through each element of matrix1 and matrix2, considering that they have the same dimensions.
     */
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            //! Multiplying matrix1 and matrix2 and assigning the result to the elements of the product matrix.
            produto.mtx[l][c].Re = matrix1.mtx[l][c].Re * matrix2.mtx[l][c].Re;
            produto.mtx[l][c].Im = matrix1.mtx[l][c].Im * matrix2.mtx[l][c].Im;
        }
    }

    //! Returning the result matrix after matrix multiplication.
    return produto;
}

/************************ TESTING FUNCTIONS **************************/

/**
 * @brief Prints a complex number with its real and imaginary parts.
 *
 * @param num The complex number to be printed.
 */
void printComplex(complex num)
{
    printf("%.2f + %.2fi\n", num.Re, num.Im);
}

/**
 * @brief Prints a complex matrix.
 *
 * @param matrix The complex matrix to be printed.
 */
void printMatrix(complexMatrix matrix)
{
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {
            if (c == 0)
            {
                printf("|%.2f + %.2fi\t", matrix.mtx[l][c].Re, matrix.mtx[l][c].Im);
            }
            else if (c == matrix.colunas - 1)
            {
                printf("%.2f + %.2fi|\t", matrix.mtx[l][c].Re, matrix.mtx[l][c].Im);
            }
            else
            {
                printf("%.2f + %.2fi\t", matrix.mtx[l][c].Re, matrix.mtx[l][c].Im);
            }
        }
        printf("\n"); /// Add a new line after printing all line elements
    }
}

/**
 * @brief Prints a complex matrix (variant 1).
 *
 * @param matrix1 The complex matrix to be printed.
 */
void printMatrix1(complexMatrix matrix1)
{
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            if (c == 0)
            {
                printf("|%.2f + %.2fi\t", matrix1.mtx[l][c].Re, matrix1.mtx[l][c].Im);
            }
            else if (c == matrix1.colunas - 1)
            {
                printf("%.2f + %.2fi|\t", matrix1.mtx[l][c].Re, matrix1.mtx[l][c].Im);
            }
            else
            {
                printf("%.2f + %.2fi\t", matrix1.mtx[l][c].Re, matrix1.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Prints a complex matrix (variant 2).
 *
 * @param matrix2 The complex matrix to be printed.
 */
void printMatrix2(complexMatrix matrix2)
{
    for (int l = 0; l < matrix2.linhas; l++)
    {
        for (int c = 0; c < matrix2.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(matrix2.mtx[l][c]);
        }
    }
}

/**
 * @brief Prints the transposed matrix.
 *
 * @param transposta The transposed matrix to be printed.
 */
void printTransposta(complexMatrix transposta)
{
    for (int l = 0; l < transposta.linhas; l++)
    {
        for (int c = 0; c < transposta.colunas; c++)
        {
            if (c == 0)
            {
                printf("|%.2f + %.2fi\t", transposta.mtx[l][c].Re, transposta.mtx[l][c].Im);
            }
            else if (c == transposta.colunas - 1)
            {
                printf("%.2f + %.2fi|\t", transposta.mtx[l][c].Re, transposta.mtx[l][c].Im);
            }
            else
            {
                printf("%.2f + %.2fi\t", transposta.mtx[l][c].Re, transposta.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Prints the conjugate matrix.
 *
 * @param conjugada The conjugate matrix to be printed.
 */
void printConjugada(complexMatrix conjugada)
{
    for (int l = 0; l < conjugada.linhas; l++)
    {
        for (int c = 0; c < conjugada.colunas; c++)
        {
            if (c == 0)
            {
                printf("|%.2f + %.2fi\t", conjugada.mtx[l][c].Re, conjugada.mtx[l][c].Im);
            }
            else if (c == conjugada.colunas - 1)
            {
                printf("%.2f + %.2fi|\t", conjugada.mtx[l][c].Re, conjugada.mtx[l][c].Im);
            }
            else
            {
                printf("%.2f + %.2fi\t", conjugada.mtx[l][c].Re, conjugada.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Prints the Hermitian matrix.
 *
 * @param hermitiana The Hermitian matrix to be printed.
 */
void printHermitiana(complexMatrix hermitiana)
{
    for (int l = 0; l < hermitiana.linhas; l++)
    {
        for (int c = 0; c < hermitiana.colunas; c++)
        {
            if (c == 0)
            {
                printf("|%.2f + %.2fi\t", hermitiana.mtx[l][c].Re, hermitiana.mtx[l][c].Im);
            }
            else if (c == hermitiana.colunas - 1)
            {
                printf("%.2f + %.2fi|\t", hermitiana.mtx[l][c].Re, hermitiana.mtx[l][c].Im);
            }
            else
            {
                printf("%.2f + %.2fi\t", hermitiana.mtx[l][c].Re, hermitiana.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Prints the sum matrix.
 *
 * @param soma The sum matrix to be printed.
 */
void printSoma(complexMatrix soma)
{
    for (int l = 0; l < soma.linhas; l++)
    {
        for (int c = 0; c < soma.colunas; c++)
        {
            if (c == 0)
            {
                printf("|%.2f + %.2fi\t", soma.mtx[l][c].Re, soma.mtx[l][c].Im);
            }
            else if (c == soma.colunas - 1)
            {
                printf("%.2f + %.2fi|\t", soma.mtx[l][c].Re, soma.mtx[l][c].Im);
            }
            else
            {
                printf("%.2f + %.2fi\t", soma.mtx[l][c].Re, soma.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Prints the subtraction matrix.
 *
 * @param subtracao The subtraction matrix to be printed.
 */
void printSubtracao(complexMatrix subtracao)
{
    for (int l = 0; l < subtracao.linhas; l++)
    {
        for (int c = 0; c < subtracao.colunas; c++)
        {
            if (c == 0)
            {
                printf("|%.2f + %.2fi\t", subtracao.mtx[l][c].Re, subtracao.mtx[l][c].Im);
            }
            else if (c == subtracao.colunas - 1)
            {
                printf("%.2f + %.2fi|\t", subtracao.mtx[l][c].Re, subtracao.mtx[l][c].Im);
            }
            else
            {
                printf("%.2f + %.2fi\t", subtracao.mtx[l][c].Re, subtracao.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Prints the scalar product matrix.
 *
 * @param produtoEscalar The scalar product matrix to be printed.
 */
void print_produtoEscalar(complexMatrix produtoEscalar)
{
    for (int l = 0; l < produtoEscalar.linhas; l++)
    {
        for (int c = 0; c < produtoEscalar.colunas; c++)
        {
            if (c == 0)
            {
                printf("|%.2f + %.2fi\t", produtoEscalar.mtx[l][c].Re, produtoEscalar.mtx[l][c].Im);
            }
            else if (c == produtoEscalar.colunas - 1)
            {
                printf("%.2f + %.2fi|\t", produtoEscalar.mtx[l][c].Re, produtoEscalar.mtx[l][c].Im);
            }
            else
            {
                printf("%.2f + %.2fi\t", produtoEscalar.mtx[l][c].Re, produtoEscalar.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Prints the product matrix.
 *
 * @param produto The product matrix to be printed.
 */
void printProduto(complexMatrix produto)
{
    for (int l = 0; l < produto.linhas; l++)
    {
        for (int c = 0; c < produto.colunas; c++)
        {
            if (c == 0)
            {
                printf("|%.2f + %.2fi\t", produto.mtx[l][c].Re, produto.mtx[l][c].Im);
            }
            else if (c == produto.colunas - 1)
            {
                printf("%.2f + %.2fi|\t", produto.mtx[l][c].Re, produto.mtx[l][c].Im);
            }
            else
            {
                printf("%.2f + %.2fi\t", produto.mtx[l][c].Re, produto.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

/**
 * @brief This function will be called in the 'main.c' file and will be responsible for printing the team name and the operations containing the functions.
 */
void teste_todos()
{
    //! The number of lines, columns, and the scalar value are hardcoded to make compilation easier.
    int linhas = 3;
    int colunas = 3;
    float num = 2.5;

    //! Calling the create and allocate memory for the original matrices, A and B.
    complexMatrix matrix = allocateComplexMatrix(linhas, colunas);
    complexMatrix matrix1 = allocateComplexMatrix(linhas, colunas);
    complexMatrix matrix2 = allocateComplexMatrix(linhas, colunas);

    //! Filling in the Original Matrix
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {
            matrix.mtx[l][c].Re = l + c + 1.4;
            matrix.mtx[l][c].Im = l + c + 4.0;
        }
    }

    //! Calling the defined functions that depend on the original matrix.
    complexMatrix transposta = matrixTransposta(matrix);
    complexMatrix conjugada = matrixConjugada(matrix);
    complexMatrix hermitiana = matrixHermitiana(transposta);

    /// Filling in Matrix A.
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            matrix1.mtx[l][c].Re = l + c + 1.0;
            matrix1.mtx[l][c].Im = l + c + 2.0;
        }
    }

    //! Filling Matrix B.
    for (int l = 0; l < matrix2.linhas; l++)
    {
        for (int c = 0; c < matrix2.colunas; c++)
        {
            matrix2.mtx[l][c].Re = l + c + 1.5;
            matrix2.mtx[l][c].Im = l + c + 2.5;
        }
    }

    //! Calling the previously defined functions that depend on Matrices A and B.
    complexMatrix soma = matrixSoma(matrix1, matrix2);
    complexMatrix subtracao = matrixSubtracao(matrix1, matrix2);
    complexMatrix produtoEscalar = matrix_produtoEscalar(matrix, num);
    complexMatrix produto = matrixProduto(matrix1, matrix2);


    /******************** PRINTING THE TESTING FUNCTIONS *********************/

    /*! 
    * @brief Printing the team members
    */  
    printf("\n ============ Equipe ============ \n");
    printf("Joel Tavares Miranda\n");
    printf("David Pinheiro \n");
    printf("Leonam Bronze\n");
    printf("Nicolas Ranniery\n");

    printf("\n  ============ Teste da operacao transposta ============ \n");

    printf("\n Matriz Original: \n");
    printMatrix(matrix);

    printf("\n Matriz Transposta \n"); 
    printTransposta(transposta);

    printf("\n  ============ Teste da operacao conjugada ============ \n");

    printf("\n Matriz Original: \n");
    printMatrix(matrix);

    printf("\n Matriz Conjugada \n");
    printConjugada(conjugada);

    printf("\n  ============ Teste da operacao da Hermitiana ============ \n");

    printf("\n Matriz Original: \n");
    printMatrix(matrix);

    printf("\n Matriz Hermitiana \n");
    printHermitiana(hermitiana);

    printf("\n  ============ Teste da Soma Matricial ============ \n");

    printf("\n Matriz A: \n");
    printMatrix(matrix1);

    printf("\n Matriz B: \n");
    printMatrix(matrix2);

    printf("\n Matriz Resultado \n");
    printSoma(soma);

    printf("\n  ============ Teste da Subtracao Matricial ============ \n");

    printf("\n Matriz A: \n");
    printMatrix(matrix1);

    printf("\n Matriz B: \n");
    printMatrix(matrix2);

    printf("\n Matriz Resultado: \n");
    printSubtracao(subtracao);

    printf("\n  ============ Teste do Produto escalar ============ \n");

    printf("\n Escalar: 2.5  \n");
    printf("\n Matriz Original: \n");
    printMatrix(matrix);
    printf("\n Matriz Resultado \n");
    print_produtoEscalar(produtoEscalar);

    printf("\n  ============ Teste do Produto Matricial ============ \n");

    printf("\n Matriz A: \n");
    printMatrix(matrix1);

    printf("\n Matriz B: \n");
    printMatrix(matrix2);

    printf("\n Matriz Resultado \n");
    printProduto(produto);

    complexMatrix matrixA = allocateComplexMatrix(3, 2);
    complexMatrix matrixB = allocateComplexMatrix(4, 4);
    complexMatrix matrixC = allocateComplexMatrix(6, 5);
    complexMatrix matrixD = allocateComplexMatrix(5, 6);
    
    freeComplexMatrix(matrixA);
    freeComplexMatrix(matrixB);
    freeComplexMatrix(matrixC);
    teste_calc_svd();
}