///@file matrizes.c
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

/** 
 * @brief Generating a function which the objective is to alocate memory dinamically to the complex matrix
 * @param param1 The number of rows for the matrix.
 * @param param1 The number of columns for the matrix.
 * @return A complexMatrix object representing the allocated matrix.
 */
complexMatrix allocateComplexMatrix(int linhas, int colunas) {

    /** 
     * @brief Declaring the variable matrix of complexMatrix type
     */ 
    complexMatrix matrix;

   /**
 * @brief Sets the number of rows and columns for a complexMatrix variable.
 *
 * This code assigns the provided `linhas` and `colunas` values to the `linhas` and `colunas` members of a `complexMatrix` variable. It specifies the number of rows and columns for the matrix.
 *
 * @param linhas The number of rows for the matrix.
 * @param colunas The number of columns for the matrix.
 */
matrix.linhas = linhas;
matrix.colunas = colunas;

    /**
 * @brief Allocates memory for the matrix rows.
 *
 * This function dynamically allocates memory for the rows of a matrix. It uses the `malloc` function to allocate memory for an array of `linhas` pointers to complex numbers (`complex *`).
 *
 * @param linhas The number of rows for the matrix.
 */
matrix.mtx = (complex **)malloc(linhas * sizeof(complex *));

   /**
 * @brief Handles possible errors when trying to allocate memory to the rows of a matrix.
 *
 * This code checks if the memory allocation for the rows of the matrix was successful. If the allocation failed, it prints an error message and terminates the program with an exit code of 1.
 */
if (matrix.mtx == NULL)
{
    printf("Falha na alocação de memória\n");
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

        //! Dealing with possible mistakes when allocating memory to the columns. 
        if (matrix.mtx[i] == NULL)
        {
            printf("Falha na alocacao de memoria\n");
            exit(1);
        }
    }

    //! Returning matrix.
    return matrix;
}

/************************ FUNCOES DE CALCULO SVD **************************/
/**
 * @param [in] matrix
*/

/**
 * @brief Performs the implementation for Singular Value Decomposition (SVD) calculation.
 *
 * This function calculates the SVD for the provided `matrix`. It implements the necessary algorithm or method for the SVD calculation.
 *
 * @param matrix The complexMatrix object for which the SVD calculation will be performed.
 */
void calc_svd(complexMatrix matrix)
{
    int i = 0;
    int j = 0;

}


    /**
 * @brief Checks if the matrix is complex.
 *
 * This code snippet checks if the elements in the matrix are complex numbers. It specifically checks if the imaginary part (`Im`) of an element at position `matrix.mtx[i][j]` is non-zero. If it is non-zero, the code prints a message indicating that the matrix is complex, and therefore, only the real part will be used for SVD calculation.
 */
if (matrix.mtx[i][j].Im != 0) {
    printf("A matriz é complexa, portanto será calculado o SVD apenas da parte real.\n");
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

    
    //! This snippet assigns the values ​​of the real part of the parameter matrix to the gslMatrix matrix    for (i = 0; i < matrix.linhas; i++) {
    for (i = 0; i < matrix.linhas; i++) {
        for (j=0; j < matrix.colunas; j++){
        gsl_matrix_set(gslMatrix, i, j, matrix.mtx[i][j].Re);
        }   
    }

    //! Performing SVD decomposition
    gsl_matrix *A = gsl_matrix_alloc(matrix.linhas, matrix.colunas);
    gsl_matrix *V = gsl_matrix_alloc(matrix.colunas, matrix.colunas);
    gsl_vector *S = gsl_vector_alloc(matrix.colunas);
    gsl_vector *work = gsl_vector_alloc(matrix.colunas);

    //! Calling the function that does the SVD calculation
    gsl_linalg_SV_decomp(A, V, S, work);

    //! Now the same function is going to print the results
    printf("\nMatrix A:\n");
    for (i = 0; i < A->size1; i++) {
        for (j = 0; j < A->size2; j++) {
            if(j ==0){
            printf("|%.2f\t", gsl_matrix_get(A, i, j));
            }
            else if(j == A->size2 - 1){
            printf("%.2f|\t", gsl_matrix_get(A, i, j));
            }
            else{
            printf("%.2f\t", gsl_matrix_get(A, i, j));
            }
        }
        printf("\n");
    }

    printf("\nVetor S:\n");
    for (i = 0; i < S->size; i++) {
        printf("|%.2f|\n", gsl_vector_get(S, i));
    }

    printf("\nMatriz V:\n");
    for (i = 0; i < V->size1; i++) {
        for (j = 0; j < V->size2; j++) {
            if(j == 0){
            printf("|%.2f\t", gsl_matrix_get(V, i, j));
            }
            else if(j == V->size2 -1){
            printf("%.2f|\t", gsl_matrix_get(V, i, j));
            }
            else{
                printf("%.2f\t", gsl_matrix_get(V, i, j));
            }
        }
        printf("\n");
    }
    
    //! releasing memory
    gsl_matrix_free(A);
    gsl_matrix_free(V);
    gsl_vector_free(S);
    gsl_vector_free(work);
    gsl_matrix_free(gslMatrix);
}

void freeComplexMatrix(complexMatrix matrix) {
    for (int i = 0; i < matrix.linhas; i++) {
        free(matrix.mtx[i]);
    }
    free(matrix.mtx);
}

//! Function that will perform all the tests and print the results in the terminal
void teste_calc_svd() {
    //!test case1: Matrix 3X2 
    printf("\n========= Matriz 3x2 =========\n");
    //! Allocating memory for the matrix.
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
            if( j == 0){
            printf("|%.1f + %.1fi\t", matrixA.mtx[i][j].Re, matrixA.mtx[i][j].Im);
            }
            else if(j == matrixA.colunas - 1){
            printf("%.1f + %.1fi|\t", matrixA.mtx[i][j].Re, matrixA.mtx[i][j].Im);
            }
            else{
                printf("%.1f + %.1fi\t", matrixA.mtx[i][j].Re, matrixA.mtx[i][j].Im);
            }
        }
        printf("\n");
    }
    
    printf("\n");
    calc_svd(matrixA);
    printf("\n");

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
            if( j == 0){
            printf("|%.1f\t", matrixB.mtx[i][j].Re);
            }
            else if(j == matrixB.colunas - 1){
            printf("%.1f|\t", matrixB.mtx[i][j].Re);
            }
            else{
                printf("%.1f\t", matrixB.mtx[i][j].Re);
            }
        }
        printf("\n");
    }

    calc_svd(matrixB);
    printf("\n");

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
            if( j == 0){
            printf("|%.1f\t", matrixC.mtx[i][j].Re);
            }
            else if(j == matrixC.colunas - 1){
            printf("%.1f|\t", matrixC.mtx[i][j].Re);
            }
            else{
                printf("%.1f\t", matrixC.mtx[i][j].Re);
            }
        }
        printf("\n");
    }
    
    calc_svd(matrixC);
    printf("\n");

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
            if( j == 0){
            printf("|%.1f\t", matrixD.mtx[i][j].Re);
            }
            else if(j == matrixD.colunas - 1){
            printf("%.1f|\t", matrixD.mtx[i][j].Re);
            }
            else{
                printf("%.1f\t", matrixD.mtx[i][j].Re);
            }
        }
        printf("\n");
    }

    calc_svd(matrixD);
    printf("\n");
}

/************************************* FUNCOES DE OPERACAO ***************************************/

/**
 * @param [in] matrix
 * @param [out] transposta
 */

//! Creating a function to make the tranposed matrix calculations 
complexMatrix matrixTransposta(complexMatrix matrix)
{

    //! Allocating memory for the complex matrix  
    complexMatrix transposta = allocateComplexMatrix(matrix.colunas, matrix.linhas);

    //! Going through each element of the original matrix
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
 * @param [in] matrix
 * @param [out] conjugada
 */

//! Creating a function to do the conjugate matrix calculation
complexMatrix matrixConjugada(complexMatrix matrix)
{

    //! Allocating memory to the conjugate matrix utilizing the allocateComplexMaatrix function 
    complexMatrix conjugada = allocateComplexMatrix(matrix.colunas, matrix.linhas);

    //!Loop for going through each original matrix element 
    for (int i = 0; i < matrix.linhas; i++)
    {
        for (int j = 0; j < matrix.colunas; j++)
        {
            //! Setting  o valor do elemento atual da matriz original para a conjugada
            conjugada.mtx[i][j].Re = matrix.mtx[i][j].Re;
            conjugada.mtx[i][j].Im = -matrix.mtx[i][j].Im; //!  Reverses the imaginary part signal
        }
    }

    //! Returns the conjugate matrix
    return conjugada;
}

/**
 * @param [in] transposta
 * @param [out] hermitiana
 */

//! Criando uma funÃ§Ã£o para realizar o cÃ¡lculo da hermitiana
complexMatrix matrixHermitiana(complexMatrix transposta)
{

    //! Alocando memÃ³ria para a matriz Hermitiana
    complexMatrix hermitiana = allocateComplexMatrix(transposta.colunas, transposta.linhas);

    //! Loop para percorrer cada elemento da matriz transposta
    for (int i = 0; i < transposta.linhas; i++)
    {
        for (int j = 0; j < transposta.colunas; j++)
        {

            //! Atribuindo o valor do elemento atual da matriz transposta para a hermitiana
            hermitiana.mtx[i][j].Re = transposta.mtx[i][j].Re;
            hermitiana.mtx[i][j].Im = -transposta.mtx[i][j].Im; //! Inverte o sinal da parte imaginÃ¡ria
        }
    }

    //! Returns the hermitian matrix 
    return hermitiana;
}

/**
 * @param [in] matrix1
 * @param [in] matrix2
 * @param [out] soma
 */

/// Criando uma funÃ§Ã£o para realizar a soma da matrix A e B, que estou apelidando de matrix1 e matrix2
complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2)
{

    /// Alocando memÃ³ria para a matrix soma
    complexMatrix soma = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    /// Loop para percorrer cada elemento da matrix1 considerando que matrix1 e matrix2 tÃªm a mesma dimensÃ£o
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {

            /// Somando os elementos correspondentes e atribuindo o resultado na matriz soma
            soma.mtx[l][c].Re = matrix1.mtx[l][c].Re + matrix2.mtx[l][c].Re;
            soma.mtx[l][c].Im = matrix1.mtx[l][c].Im + matrix2.mtx[l][c].Im;
        }
    }

    /// Retornando a matriz Soma
    return soma;
}

/**
 * @param [in] matrix1
 * @param [in] matrix2
 * @param [out] subtracao
 */

/// Criando uma funÃ§Ã£o para realizar a subtraÃ§Ã£o entre matrix1 e matrix2
complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2)
{

    /// Alocando memÃ³ria para a matriz subtraÃ§Ã£o
    complexMatrix subtracao = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    /// Loop para percorrer cada elemento da matrix1 considerando que matrix1 e matrix2 tÃªm a mesma dimensÃ£o
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {

            /// Subtraindo os elementos correspondentes e atribuindo o resultado na matriz subtraÃ§Ã£o
            subtracao.mtx[l][c].Re = matrix1.mtx[l][c].Re - matrix2.mtx[l][c].Re;
            subtracao.mtx[l][c].Im = matrix1.mtx[l][c].Im - matrix2.mtx[l][c].Im;
        }
    }

    /// Retornando a matriz SubtraÃ§Ã£o
    return subtracao;
}

/**
 * @param [in] matrix
 * @param [in] num
 * @param [out] produtoEscalar
 */

/// Criando uma funÃ§Ã£o para realizar a multiplicaÃ§Ã£o de um nÃºmero escalar com cada elemento da matriz original
complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num)
{

    /// Alocando memÃ³ria para a matrix resultado do produto escalar
    complexMatrix produtoEscalar = allocateComplexMatrix(matrix.linhas, matrix.colunas);

    /// Loop para percorrer cada elemento da matriz original
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {

            /// Multiplicando um nÃºmero a cada elemento da matriz original e atribuindo o resultado aos elementos a produtoEscalar
            produtoEscalar.mtx[l][c].Re = matrix.mtx[l][c].Re * num;
            produtoEscalar.mtx[l][c].Im = matrix.mtx[l][c].Im * num;
        }
    }

    /// Retornando produtoEscalar
    return produtoEscalar;
}

/**
 * @param [in] matrix1
 * @param [in] matrix2
 * @param [out] produto
 */

/// Criando uma funÃ§Ã£o para realizar o produto entre matrix1 e matrix2
complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2)
{

    /// Alocando memÃ³ria para a matrix resultado do produto
    complexMatrix produto = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    /// Loop para percorrer cada elemento da matrix1 considerando que matrix1 e matrix2 tÃªm a mesma dimensÃ£o
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {

            /// Multiplicando matrix1 e matrix2 e atribuindo o resultao a produto
            produto.mtx[l][c].Re = matrix1.mtx[l][c].Re * matrix2.mtx[l][c].Re;
            produto.mtx[l][c].Im = matrix1.mtx[l][c].Im * matrix2.mtx[l][c].Im;
        }
    }

    /// Retorna a matriz produto
    return produto;
}

/************************ FUNÃÃES DE TESTE **************************/

/// FunÃ§Ã£o para imprimir um nÃºmero complexo com sua parte real e imaginÃ¡ria
void printComplex(complex num)
{
    printf("%.2f + %.2fi\n", num.Re, num.Im);
}

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
        printf("\n"); //! Add a new line after printing all the line elements 
    }
}

void printMatrix1(complexMatrix matrix1)
{
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            if(c == 0){
                printf("|%.2f + %.2fi\t", matrix1.mtx[l][c].Re, matrix1.mtx[l][c].Im);
            }
            else if (c == matrix1.colunas - 1){
                printf("%.2f + %.2fi\t", matrix1.mtx[l][c].Re, matrix1.mtx[l][c].Im);
            }
            else{
                printf("%.2f + %.2fi\t", matrix1.mtx[l][c].Re, matrix1.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

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

//! This function will be called on the 'main.c' file and will be responsible for printing on the screen the team name and the operations containing the functions.
void teste_todos()
{
    //! The number of lines, columns and the scalar value are hardcode the make the compilation easier.
    int linhas = 3;
    int colunas = 3;
    float num = 2.5;

    //! Calling the create and allocate memory to the original matrixes, A and B
    complexMatrix matrix = allocateComplexMatrix(linhas, colunas);
    complexMatrix matrix1 = allocateComplexMatrix(linhas, colunas);
    complexMatrix matrix2 = allocateComplexMatrix(linhas, colunas);

    //! Filling the original matrix 
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {
            matrix.mtx[l][c].Re = l + c + 1.4;
            matrix.mtx[l][c].Im = l + c + 4.0;
        }
    }

    //! Calling the defined functions early that depends on the original matrix 
    complexMatrix transposta = matrixTransposta(matrix);
    complexMatrix conjugada = matrixConjugada(matrix);
    complexMatrix hermitiana = matrixHermitiana(transposta);

    //! Filling Matrix A
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            matrix1.mtx[l][c].Re = l + c + 1.0;
            matrix1.mtx[l][c].Im = l + c + 2.0;
        }
    }

    //! Filling Matrix B
    for (int l = 0; l < matrix2.linhas; l++)
    {
        for (int c = 0; c < matrix2.colunas; c++)
        {
            matrix2.mtx[l][c].Re = l + c + 1.5;
            matrix2.mtx[l][c].Im = l + c + 2.5;
        }
    }

    /// Chamando as funcoes criadas anteriormente que dependem das Matrizes A e B
    complexMatrix soma = matrixSoma(matrix1, matrix2);
    complexMatrix subtracao = matrixSubtracao(matrix1, matrix2);
    complexMatrix produtoEscalar = matrix_produtoEscalar(matrix, num);
    complexMatrix produto = matrixProduto(matrix1, matrix2);

    /******************** IMPRIMINDO AS FUNÃÃES DE TESTE *********************/

    //! printing the number one from Brazil team
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
