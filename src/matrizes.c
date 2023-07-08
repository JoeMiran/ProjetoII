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

/// Creating a function whose purpose is to dynamically allocate memory for the complex matrix
complexMatrix allocateComplexMatrix(int linhas, int colunas) {

    /// Declaring the matrix variable of type ComplexMatrix
    complexMatrix matrix;

    /// The complexMatrix type variable has rows and columns "attributes" and must receive them as parameters
    matrix.linhas = linhas;
    matrix.colunas = colunas;

    /// Allocating memory for matrix lines
    matrix.mtx = (complex **)malloc(linhas * sizeof(complex *));

    /// Handling possible errors in memory allocation for rows
    if (matrix.mtx == NULL)
    {
        printf("Falha na alocação de memória\n");
        exit(1);
    }

    /// Allocating memory for the columns of each row
    for (int i = 0; i < linhas; i++)
    {
        matrix.mtx[i] = (complex *)malloc(colunas * sizeof(complex));

        /// Handling possible errors in memory allocation for columns
        if (matrix.mtx[i] == NULL)
        {
            printf("Falha na alocação de memória\n");
            exit(1);
        }
    }

    /// Returning matrix
    return matrix;
}

/************************ SVD CALCULATION FUNCTIONS **************************/
/**
 * @param [in] matrix
*/

/// This function does the implementation for the SVD calculation
void calc_svd(complexMatrix matrix) 
{
    
    int i = 0;
    int j = 0;

    ///Structure that checks if the matrix is ​​complex
    if (matrix.mtx[i][j].Im != 0) {
        printf("A matriz é complexa, portanto será calculado o SVD apenas da parte real.\n");
    }

    /// Creating a gsl matrix using the real part of the complex matrix
    gsl_matrix* gslMatrix = gsl_matrix_alloc(matrix.linhas, matrix.colunas);
    
    /// This snippet assigns the values ​​of the real part of the parameter matrix to the gslMatrix matrix    for (i = 0; i < matrix.linhas; i++) {
    for (i = 0; i < matrix.linhas; i++) {
        for (j=0; j < matrix.colunas; j++){
        gsl_matrix_set(gslMatrix, i, j, matrix.mtx[i][j].Re);
        }   
    }

    /// Performing SVD decomposition
    gsl_matrix *A = gsl_matrix_alloc(matrix.linhas, matrix.colunas);
    gsl_matrix *V = gsl_matrix_alloc(matrix.colunas, matrix.colunas);
    gsl_vector *S = gsl_vector_alloc(matrix.colunas);
    gsl_vector *work = gsl_vector_alloc(matrix.colunas);

    /// Calling the function that performs the SVD calculation
    gsl_linalg_SV_decomp(A, V, S, work);

    /// Now the function will print the results
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
    
    /// Releasing memory
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

/// Function that will perform all the tests and print the results in the terminal
void teste_calc_svd() {
    ///Test case 1: Matriz 3X2
    printf("\n========= Matriz 3x2 =========\n");
    ///Allocating memory to the matrix
    complexMatrix matrixA = allocateComplexMatrix(3, 2);
    //Filling the matrix with values
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

/************************************* OPERATING FUNCTIONS ***************************************/

/**
 * @param [in] matrix
 * @param [out] transposta
 */

/// Creating a function to perform the calculation of the transposed matrix
complexMatrix matrixTransposta(complexMatrix matrix)
{

    /// Allocating memory for the transposed matrix
    complexMatrix transposta = allocateComplexMatrix(matrix.colunas, matrix.linhas);

    /// Looping through each element of the original matrix
    for (int i = 0; i < matrix.linhas; i++)
    {
        for (int j = 0; j < matrix.colunas; j++)
        {

            /// Assigning the value of the current element from the original matrix to the transpose
            /// Swapping the position of rows and columns in the transposed matrix
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

/// Creating a function to perform the calculation of the conjugate matrix
complexMatrix matrixConjugada(complexMatrix matrix)
{

    /// Allocating memory for the conjugate matrix using the allocateComplexMaatrix function
    complexMatrix conjugada = allocateComplexMatrix(matrix.colunas, matrix.linhas);

    /// Loop to loop through each element of the original matrix
    for (int i = 0; i < matrix.linhas; i++)
    {
        for (int j = 0; j < matrix.colunas; j++)
        {
            /// Assigning the value of the current element of the original matrix to the conjugate
            conjugada.mtx[i][j].Re = matrix.mtx[i][j].Re;
            conjugada.mtx[i][j].Im = -matrix.mtx[i][j].Im; // Inverts the sign of the imaginary part
        }
    }

    /// Returning the conjugate matrix
    return conjugada;
}

/**
 * @param [in] transposta
 * @param [out] hermitiana
 */

/// Creating a function to calculate the Hermitian Matrix
complexMatrix matrixHermitiana(complexMatrix transposta)
{

    /// Allocating memory to the Hermitian matrix
    complexMatrix hermitiana = allocateComplexMatrix(transposta.colunas, transposta.linhas);

    /// Loop to loop through each element of the transposed matrix
    for (int i = 0; i < transposta.linhas; i++)
    {
        for (int j = 0; j < transposta.colunas; j++)
        {

            //// Assigning the value of the current element of the transposed matrix to the Hermitian Matrix
            hermitiana.mtx[i][j].Re = transposta.mtx[i][j].Re;
            hermitiana.mtx[i][j].Im = -transposta.mtx[i][j].Im; // Inverts the sign of the imaginary part
        }
    }

    /// Returning the Hermitian matrix
    return hermitiana;
}

/**
 * @param [in] matrix1
 * @param [in] matrix2
 * @param [out] soma
 */

/// Creating a function to perform the sum of matrix A and B, which I'm calling matrix1 and matrix2
complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2)
{

    /// Allocating memory for the soma matrix
    complexMatrix soma = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    /// Loop to loop through each element of matrix 1 considering that matrix 1 and matrix2 have the same dimension
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {

            /// Summing the corresponding elements and assigning the result in the sum matrix
            soma.mtx[l][c].Re = matrix1.mtx[l][c].Re + matrix2.mtx[l][c].Re;
            soma.mtx[l][c].Im = matrix1.mtx[l][c].Im + matrix2.mtx[l][c].Im;
        }
    }

    /// Returning the Sum matrix
    return soma;
}

/**
 * @param [in] matrix1
 * @param [in] matrix2
 * @param [out] subtracao
 */

/// Creating a function to perform the subtraction between matrix1 and matrix2
complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2)
{

    /// Allocating memory for the subtraction matrix
    complexMatrix subtracao = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    /// Loop to go through each element of matrix1 considering that matrix1 and matrix2 have the same dimension
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {

            /// Subtracting the corresponding elements and assigning the result in the subtraction matrix
            subtracao.mtx[l][c].Re = matrix1.mtx[l][c].Re - matrix2.mtx[l][c].Re;
            subtracao.mtx[l][c].Im = matrix1.mtx[l][c].Im - matrix2.mtx[l][c].Im;
        }
    }

    /// Returning the subtraction matrix
    return subtracao;
}

/**
 * @param [in] matrix
 * @param [in] num
 * @param [out] produtoEscalar
 */

/// Creating a function to perform the multiplication of a scalar number with each element of the original matrix
complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num)
{

    /// Allocating memory for the matrix resulting from the dot product
    complexMatrix produtoEscalar = allocateComplexMatrix(matrix.linhas, matrix.colunas);

    /// Loop to loop through each element of the original matrix
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {

            /// Multiplying a number to each element of the original matrix and assigning the result to the elements the produtoEscalar
            produtoEscalar.mtx[l][c].Re = matrix.mtx[l][c].Re * num;
            produtoEscalar.mtx[l][c].Im = matrix.mtx[l][c].Im * num;
        }
    }

    /// Returning produtoEscalar
    return produtoEscalar;
}

/**
 * @param [in] matrix1
 * @param [in] matrix2
 * @param [out] produto
 */

/// Creating a function to perform the product between matrix1 and matrix2
complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2)
{

    /// Allocating memory for the resulting produto matrix
    complexMatrix produto = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    /// Loop to go through each element of matrix1 considering that matrix1 and matrix2 have the same dimension
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {

            /// Multiplying matrix1 and matrix2 and assigning the result to the produto
            produto.mtx[l][c].Re = matrix1.mtx[l][c].Re * matrix2.mtx[l][c].Re;
            produto.mtx[l][c].Im = matrix1.mtx[l][c].Im * matrix2.mtx[l][c].Im;
        }
    }

    /// Returning the product matrix
    return produto;
}

/************************ TEST FUNCTIONS **************************/

/// Function to print a complex number with its real and imaginary parts
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
        printf("\n"); // Add a new line after printing all line elements
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

/// This function will be called in the main.c file and will be responsible for printing the team name and operations with the functions on the screen.
void teste_todos()
{
    /// The number of rows, columns and scalar value are hardcoded for easy compilation.
    int linhas = 3;
    int colunas = 3;
    float num = 2.5;

    /// Calling the function that creates and allocates memory for the Original Matrices, A and B
    complexMatrix matrix = allocateComplexMatrix(linhas, colunas);
    complexMatrix matrix1 = allocateComplexMatrix(linhas, colunas);
    complexMatrix matrix2 = allocateComplexMatrix(linhas, colunas);

    /// Filling in the Original Matrix
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {
            matrix.mtx[l][c].Re = l + c + 1.4;
            matrix.mtx[l][c].Im = l + c + 4.0;
        }
    }

    /// Calling the previously defined functions that depending on the Original Matrix
    complexMatrix transposta = matrixTransposta(matrix);
    complexMatrix conjugada = matrixConjugada(matrix);
    complexMatrix hermitiana = matrixHermitiana(transposta);

    /// Filling in Matrix A
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            matrix1.mtx[l][c].Re = l + c + 1.0;
            matrix1.mtx[l][c].Im = l + c + 2.0;
        }
    }

    /// Filling in Matrix A 
    for (int l = 0; l < matrix2.linhas; l++)
    {
        for (int c = 0; c < matrix2.colunas; c++)
        {
            matrix2.mtx[l][c].Re = l + c + 1.5;
            matrix2.mtx[l][c].Im = l + c + 2.5;
        }
    }

    /// Calling previously created functions that depend on Matrices A and B
    complexMatrix soma = matrixSoma(matrix1, matrix2);
    complexMatrix subtracao = matrixSubtracao(matrix1, matrix2);
    complexMatrix produtoEscalar = matrix_produtoEscalar(matrix, num);
    complexMatrix produto = matrixProduto(matrix1, matrix2);

    /******************** PRINTING THE TEST FUNCTIONS *********************/

    /// Printing the team
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