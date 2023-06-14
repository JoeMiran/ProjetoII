#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_linalg.h>

// Definindo a estrutura complex com parte real e imaginÃ¡ria
typedef struct {
    float Re, Im;
} complex;

// Definindo a estsrutura complexMatrix que representa uma matriz complexa
typedef struct {
    int linhas, colunas;
    complex** mtx;
} complexMatrix;

// Criando uma matriz do tipo complexMatrix que aloca dinamicamente a memÃ³ria para cada linha
complexMatrix allocateComplexMatrix(int linhas, int colunas) {
    complexMatrix matrix;
    matrix.linhas = linhas;
    matrix.colunas = colunas;

    // Alocando memÃ³ria para as linhas
    matrix.mtx = (complex**)malloc(linhas * sizeof(complex*));
    if (matrix.mtx == NULL) {
        printf("Falha na alocaÃ§Ã£o de memÃ³ria\n");
        exit(1);
    }

    // Alocando memÃ³ria para cada coluna de cada linha
    for (int i = 0; i < linhas; i++) {
        matrix.mtx[i] = (complex*)malloc(colunas * sizeof(complex));
        if (matrix.mtx[i] == NULL) {
            printf("Falha na alocaÃ§Ã£o de memÃ³ria\n");
            exit(1);
        }
    }
    return matrix;
}

/************************ FUNCOES DE CALCULO SVD **************************/
void calc_svd(complexMatrix matrix) {
    int i = 0;
    int j = 0;

    if (matrix.mtx[i][j].Im != 0) {
        printf("The matrix is complex. Not to be calculate the imaginary matrix part.\n");
    }

    // Criando uma matriz gsl usando a parte real da matriz complexa
    gsl_matrix* gslMatrix = gsl_matrix_alloc(matrix.linhas, matrix.colunas);
    for (i = 0; i < matrix.linhas; i++) {
        for (j = 0; j < matrix.colunas; j++) {
            // Atribuindo os valores da parte real da matriz a gslMatrix
            gsl_matrix_set(gslMatrix, i, j, matrix.mtx[i][j].Re);
        }
    }

    // Fazendo a decomposiÃ§Ã£o SVD
    gsl_matrix *A = gsl_matrix_alloc(matrix.linhas, matrix.colunas);
    gsl_matrix *V = gsl_matrix_alloc(matrix.colunas, matrix.colunas);
    gsl_vector *S = gsl_vector_alloc(matrix.colunas);
    gsl_vector *work = gsl_vector_alloc(matrix.colunas);

    // Chamando a funÃ§Ã£o que realiza o cÃ¡lculo do SVD
    gsl_linalg_SV_decomp(A, V, S, work);

    // Agora a mesma funÃ§Ã£o vai imprimir os resultados
    printf("\nMatrix A:\n");
    for (i = 0; i < A->size1; i++) {
        for (j = 0; j < A->size2; j++) {
            if(j ==0){
            printf("|%.1f\t", gsl_matrix_get(A, i, j));
            }
            else if(j == A->size2 - 1){
            printf("%.1f|\t", gsl_matrix_get(A, i, j));
            }
            else{
            printf("%.1f\t", gsl_matrix_get(A, i, j));
            }
        }
        printf("\n");
    }

    printf("\nVetor S:\n");
    for (i = 0; i < S->size; i++) {
        printf("|%.1f|\n", gsl_vector_get(S, i));
    }

    printf("\nMatriz V:\n");
    for (i = 0; i < V->size1; i++) {
        for (j = 0; j < V->size2; j++) {
            if(j ==0){
            printf("|%.1f\t", gsl_matrix_get(V, i, j));
            }
            else if(j == V->size2 -1){
            printf("%.1f|\t", gsl_matrix_get(V, i, j));
            }
            else{
                printf("%.1f\t", gsl_matrix_get(V, i, j));
            }
        }
        printf("\n");
    }
    
    // Liberando memÃ³ria
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

void teste_calc_svd() {
    //Caso de teste1: Matriz 3X2
    printf("\n========= Matriz 3x2 =========\n");
    ///Alocando memÃ³ria para a matriz
    complexMatrix matrixA = allocateComplexMatrix(3, 2);
    //Preenchendo a matriz com valores
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
    //freeComplexMatrix(matrixA);
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

/************************ FUNCOES DE OPERACAO **************************/

complexMatrix matrixTransposta(complexMatrix matrix) {

    complexMatrix transposta = allocateComplexMatrix(matrix.colunas, matrix.linhas);

    for (int i = 0; i < matrix.linhas; i++) {
        for (int j = 0; j < matrix.colunas; j++) {
            transposta.mtx[i][j].Re = matrix.mtx[j][i].Re;
            transposta.mtx[i][j].Im = matrix.mtx[j][i].Im;
        }
    }
    return transposta;
}

complexMatrix matrixConjugada(complexMatrix matrix) {

    complexMatrix conjugada = allocateComplexMatrix(matrix.colunas, matrix.linhas);

    //Aqui vai a operaÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½o em si, que transforma a matriz original na sua conjjugada
    for (int i = 0; i < matrix.linhas; i++) {
        for(int j = 0; j < matrix.colunas; j++) {
            conjugada.mtx[i][j].Re = matrix.mtx[i][j].Re;
            conjugada.mtx[i][j].Im = -matrix.mtx[i][j].Im;//Inverte o sinal da parte imaginÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ria
        }
    }

    return conjugada;
}

complexMatrix matrixHermitiana(complexMatrix transposta) {

    complexMatrix hermitiana = allocateComplexMatrix(transposta.colunas, transposta.linhas);

    for (int i = 0; i < transposta.linhas; i++) {
        for(int j = 0; j < transposta.colunas; j++) {
            hermitiana.mtx[i][j].Re = transposta.mtx[i][j].Re;
            hermitiana.mtx[i][j].Im = -transposta.mtx[i][j].Im;
        }
    }

    return hermitiana;
}

complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2) {
    complexMatrix soma = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    for (int l = 0; l < matrix1.linhas; l++) {
        for (int c = 0; c < matrix1.colunas; c++) {
            soma.mtx[l][c].Re = matrix1.mtx[l][c].Re + matrix2.mtx[l][c].Re;
            soma.mtx[l][c].Im = matrix1.mtx[l][c].Im + matrix2.mtx[l][c].Im;
        }
    }

    return soma;
}

complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2) {
    complexMatrix subtracao = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    for (int l = 0; l < matrix1.linhas; l++) {
        for (int c = 0; c < matrix1.colunas; c++) {
            subtracao.mtx[l][c].Re = matrix1.mtx[l][c].Re - matrix2.mtx[l][c].Re;
            subtracao.mtx[l][c].Im = matrix1.mtx[l][c].Im - matrix2.mtx[l][c].Im;
        }
    }

    return subtracao;
}

complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num) {
    complexMatrix produtoEscalar = allocateComplexMatrix(matrix.linhas, matrix.colunas);

    for (int l = 0; l < matrix.linhas; l++) {
        for (int c = 0; c < matrix.colunas; c++) {
            produtoEscalar.mtx[l][c].Re = matrix.mtx[l][c].Re * num;
            produtoEscalar.mtx[l][c].Im = matrix.mtx[l][c].Im * num;
        }
    }

    return produtoEscalar;
}

complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2) {
    complexMatrix produto = allocateComplexMatrix(matrix1.linhas, matrix1.colunas);

    for (int l = 0; l < matrix1.linhas; l++) {
        for(int c = 0; c < matrix1.colunas; c++) {
            produto.mtx[l][c].Re = matrix1.mtx[l][c].Re * matrix2.mtx[l][c].Re;
            produto.mtx[l][c].Im = matrix1.mtx[l][c].Im * matrix2.mtx[l][c].Im;
        }
    }

    return produto;
}

/************************ FUNCOES DE TESTE **************************/

void printMatrix(complexMatrix matrix) {
    for (int l = 0; l < matrix.linhas; l++) {
        for (int c = 0; c < matrix.colunas; c++) {
            if (c == 0)
            {
                printf("|%.1f + %.1fi\t", matrix.mtx[l][c].Re, matrix.mtx[l][c].Im);
            }
            else if (c == matrix.colunas - 1)
            {
                printf("%.1f + %.1fi|\t", matrix.mtx[l][c].Re, matrix.mtx[l][c].Im);
            }
            else
            {
                printf("%.1f + %.1fi\t", matrix.mtx[l][c].Re, matrix.mtx[l][c].Im);
            }
        }
        printf("\n");  // Adicionar uma nova linha apÃƒÂ¯Ã‚Â¿Ã‚Â½s imprimir todos os elementos da linha
    }
}

void printComplex(complex num) {
    printf("%.1f + %.1fi\n", num.Re, num.Im);
}

void printMatrix1(complexMatrix matrix1) {
    for (int l = 0; l < matrix1.linhas; l++) {
        for (int c = 0; c < matrix1.colunas; c++) {
        printf("[%d][%d]: ", l, c);
        printComplex(matrix1.mtx[l][c]);
        }
    }
}

void printMatrix2(complexMatrix matrix2) {
    for (int l = 0; l < matrix2.linhas; l++) {
        for (int c = 0; c < matrix2.colunas; c++) {
        printf("[%d][%d]: ", l, c);
        printComplex(matrix2.mtx[l][c]);
        }
    }
}

void printTransposta(complexMatrix transposta) {
    for (int l = 0; l < transposta.linhas; l++) {
        for (int c = 0; c < transposta.colunas; c++) {
            if(c == 0){
                printf("|%.1f + %.1fi\t",transposta.mtx[l][c].Re, transposta.mtx[l][c].Im);
                }
                else if(c == transposta.colunas-1){
                 printf("%.1f + %.1fi|\t",transposta.mtx[l][c].Re, transposta.mtx[l][c].Im);
                }
                else{
                printf("%.1f + %.1fi\t",transposta.mtx[l][c].Re, transposta.mtx[l][c].Im);
                }
        }
    printf("\n");
    }
}

void printConjugada(complexMatrix conjugada) {
    for (int l = 0; l < conjugada.linhas; l++) {
        for (int c = 0; c < conjugada.colunas; c++) {
            if(c == 0){
                    printf("|%.1f + %.1fi\t",conjugada.mtx[l][c].Re, conjugada.mtx[l][c].Im);
                }
                else if(c == conjugada.colunas-1){
                 printf("%.1f + %.1fi|\t",conjugada.mtx[l][c].Re, conjugada.mtx[l][c].Im);
                }
                else{
                printf("%.1f + %.1fi\t",conjugada.mtx[l][c].Re, conjugada.mtx[l][c].Im);
                }
        }
    printf("\n");
    }
}

void printHermitiana(complexMatrix hermitiana) {
    for (int l = 0; l < hermitiana.linhas; l++) {
        for(int c = 0; c < hermitiana.colunas; c++) {
            if(c == 0){
                    printf("|%.1f + %.1fi\t",hermitiana.mtx[l][c].Re, hermitiana.mtx[l][c].Im);
                }
                else if(c == hermitiana.colunas-1){
                 printf("%.1f + %.1fi|\t",hermitiana.mtx[l][c].Re, hermitiana.mtx[l][c].Im);
                }
                else{
                printf("%.1f + %.1fi\t",hermitiana.mtx[l][c].Re, hermitiana.mtx[l][c].Im);
                }
        }
    printf("\n");
    }
}

void printSoma(complexMatrix soma) {
    for(int l = 0; l < soma.linhas; l++) {
        for(int c = 0; c < soma.colunas; c++) {
            if(c == 0){
                printf("|%.1f + %.1fi\t",soma.mtx[l][c].Re, soma.mtx[l][c].Im);
            }
            else if(c == soma.colunas-1){
                printf("%.1f + %.1fi|\t",soma.mtx[l][c].Re, soma.mtx[l][c].Im);
            }
            else{
            printf("%.1f + %.1fi\t",soma.mtx[l][c].Re, soma.mtx[l][c].Im);
            }
        }
        printf("\n");
    }
}

void printSubtracao(complexMatrix subtracao) {
    for (int l = 0; l < subtracao.linhas; l++) {
        for (int c = 0; c < subtracao.colunas; c++) {
            if(c == 0){
                printf("|%.1f + %.1fi\t",subtracao.mtx[l][c].Re, subtracao.mtx[l][c].Im);
            }
            else if(c == subtracao.colunas-1){
                printf("%.1f + %.1fi|\t",subtracao.mtx[l][c].Re, subtracao.mtx[l][c].Im);
            }
            else{
            printf("%.1f + %.1fi\t",subtracao.mtx[l][c].Re, subtracao.mtx[l][c].Im);
            }
        }
    printf("\n");
    }
}

void print_produtoEscalar(complexMatrix produtoEscalar) {
    for (int l = 0; l < produtoEscalar.linhas; l++) {
        for (int c = 0; c < produtoEscalar.colunas; c++ ) {
            //printf("[%d][%d]: ", l, c);
            //printComplex(produtoEscalar.mtx[l][c]);
            if(c == 0){
                    printf("|%.1f + %.1fi\t",produtoEscalar.mtx[l][c].Re, produtoEscalar.mtx[l][c].Im);
                }
                else if(c == produtoEscalar.colunas-1){
                 printf("%.1f + %.1fi|\t",produtoEscalar.mtx[l][c].Re, produtoEscalar.mtx[l][c].Im);
                }
                else{
                printf("%.1f + %.1fi\t",produtoEscalar.mtx[l][c].Re, produtoEscalar.mtx[l][c].Im);
                }
        }
    printf("\n");
    }
}

void printProduto(complexMatrix produto) {
    for (int l = 0; l < produto.linhas; l++) {
        for (int c = 0; c < produto.colunas; c++ ) {
            //printf("[%d][%d]: ", l, c);
            //printComplex(produto.mtx[l][c]);
            if(c == 0){
                    printf("|%.1f + %.1fi\t",produto.mtx[l][c].Re, produto.mtx[l][c].Im);
                }
                else if(c == produto.colunas-1){
                 printf("%.1f + %.1fi|\t",produto.mtx[l][c].Re, produto.mtx[l][c].Im);
                }
                else{
                printf("%.1f + %.1fi\t",produto.mtx[l][c].Re, produto.mtx[l][c].Im);
                }
        }
    printf("\n");
    }
}

int main() {

    int linhas = 3;
    int colunas = 3;
    float num = 2.5;

    //chamando a funÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½o que cria e aloca memÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ria para a matriz complexa
    complexMatrix matrix = allocateComplexMatrix(linhas, colunas);
    complexMatrix matrix1 = allocateComplexMatrix(linhas, colunas);
    complexMatrix matrix2 = allocateComplexMatrix(linhas, colunas);

    //Preenchendo a matriz complexa
    for (int l = 0; l < matrix.linhas; l++) {
        for (int c = 0; c < matrix.colunas; c++) {
            matrix.mtx[l][c].Re =  l + c + 1.4;
            matrix.mtx[l][c].Im =  l + c + 4.0;
        }
    }

    complexMatrix transposta = matrixTransposta(matrix);
    complexMatrix conjugada = matrixConjugada(matrix);
    complexMatrix hermitiana = matrixHermitiana(transposta);

    //Preenchendo a matrix1
    for (int l = 0; l < matrix1.linhas; l++) {
        for (int c = 0; c < matrix1.colunas; c++) {
            matrix1.mtx[l][c].Re = l + c + 1.0;
            matrix1.mtx[l][c].Im = l + c + 2.0;
        }
    }

    //Preenchendo a matrix2
    for (int l = 0; l < matrix2.linhas; l++) {
        for (int c = 0; c < matrix2.colunas; c++) {
            matrix2.mtx[l][c].Re = l + c + 1.5;
            matrix2.mtx[l][c].Im = l + c + 2.5;
        }
    }

    complexMatrix soma = matrixSoma(matrix1, matrix2);
    complexMatrix subtracao = matrixSubtracao(matrix1, matrix2);
    complexMatrix produtoEscalar = matrix_produtoEscalar(matrix, num);
    complexMatrix produto = matrixProduto(matrix1, matrix2);

    printf("\n ======Teste da operacao transposta====== \n");
    printf("Joel Tavares Miranda\n");
    printf("David Pinheiro \n");
    printf("Leonam Bronze\n");
    printf("Nicolas Ranniery\n");


    printf("\n ======Teste da operacao transposta====== \n");


    printf("\n Matriz Transposta \n");
    printTransposta(transposta);

    printf("\n ======Teste da operacao conjugada====== \n");

    printf("\n Matriz Original: \n");
    printMatrix(matrix);

    printf("\n Matriz Conjugada \n");
    printConjugada(conjugada);

    printf("\n ======Teste da operacao da Hermitiana====== \n");

    printf("\n Matriz Original: \n");
    printMatrix(matrix);

    printf("\n Matriz Hermitiana \n");
    printHermitiana(hermitiana);

    printf("\n ======Teste da Soma Matricial====== \n");

    printf("\n Matriz A: \n");
    printMatrix(matrix1);

    printf("\n Matriz B: \n");
    printMatrix(matrix2);

    printf("\n Matriz Resultado \n");
    printSoma(soma);

    printf("\n ======Teste da Subtracao Matricial====== \n");

    printf("\n Matriz A: \n");
    printMatrix(matrix1);

    printf("\n Matriz B: \n");
    printMatrix(matrix2);

    printf("\n Matriz Resultado: \n");
    printSubtracao(subtracao);


    printf("\n ======Teste do Produto escalar====== \n");

    printf("\n Escalar: 2.5  \n");
    printf("\n Matriz Original: \n");
    printMatrix(matrix);
    printf("\n Matriz Resultado \n");
    print_produtoEscalar(produtoEscalar);

    printf("\n ======Teste do Produto Matricial====== \n");

    printf("\n Matriz A: \n");
    printMatrix(matrix1);

    printf("\n Matriz B: \n");
    printMatrix(matrix2);

    printf("\n Matriz Resultado \n");
    printProduto(produto);
    
    printf("\n ====================== TESTE SVD ====================== \n\n");

    complexMatrix matrixA = allocateComplexMatrix(3, 2);
    complexMatrix matrixB = allocateComplexMatrix(4, 4);
    complexMatrix matrixC = allocateComplexMatrix(6, 5);
    complexMatrix matrixD = allocateComplexMatrix(5, 6);
    
    freeComplexMatrix(matrixA);
    freeComplexMatrix(matrixB);
    freeComplexMatrix(matrixC);
    teste_calc_svd();
}
