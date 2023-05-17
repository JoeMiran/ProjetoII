#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

//Criando uma matriz do tipo complexMatrix que aloca dinamicamnetea memï¿½ria para cada linha
complexMatrix allocateComplexMaatrix(int linhas, int colunas) {
    
    complexMatrix matrix;
    matrix.linhas = linhas;
    matrix.colunas = colunas;
    
    //Alocandoo memï¿½ria para as linhas
    matrix.mtx = (complex**)malloc(linhas * sizeof(complex*));
    if (matrix.mtx == NULL) {
        printf("Falha na alocação de memória\n");
        exit(1);
    }
    
    //Alocando memï¿½ria para cada coluna de cada linha
    for (int i = 0; i < linhas; i++) { 
        matrix.mtx[i] = (complex*)malloc(colunas * sizeof(complex));
        if (matrix.mtx == NULL) {
            printf("Falha na alocação de memória\n");
            exit(1);
        }
    }
    return matrix;
}

complexMatrix matrixTransposta(complexMatrix matrix) {

    complexMatrix transposta = allocateComplexMaatrix(matrix.colunas, matrix.linhas);
    
    for (int i = 0; i < matrix.linhas; i++) {
        for (int j = 0; j < matrix.colunas; j++) {
            transposta.mtx[j][i].Re = matrix.mtx[i][j].Re;
            transposta.mtx[j][i].Im = matrix.mtx[i][j].Im;
        }
    }
    return transposta;
}

complexMatrix matrixConjugada(complexMatrix matrix) {

    complexMatrix conjugada = allocateComplexMaatrix(matrix.colunas, matrix.linhas);

    //Aqui vai a operaï¿½ï¿½o em si, que transforma a matriz original na sua conjjugada
    for (int i = 0; i < matrix.linhas; i++) {
        for(int j = 0; j < matrix.colunas; j++) {
            conjugada.mtx[i][j].Re = matrix.mtx[i][j].Re;
            conjugada.mtx[i][j].Im = -matrix.mtx[i][j].Im;//Inverte o sinal da parte imaginï¿½ria
        }
    }

    return conjugada;
}

complexMatrix matrixHermitiana(complexMatrix transposta) {
    
    complexMatrix hermitiana = allocateComplexMaatrix(transposta.colunas, transposta.linhas);

    for (int i = 0; i < transposta.linhas; i++) {
        for(int j = 0; j < transposta.colunas; j++) {
            hermitiana.mtx[i][j].Re = transposta.mtx[i][j].Re;
            hermitiana.mtx[i][j].Im = -transposta.mtx[i][j].Im;
        }
    }

    return hermitiana;
}

complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2) {
    complexMatrix soma = allocateComplexMaatrix(matrix1.linhas, matrix1.colunas);

    for (int l = 0; l < matrix1.linhas; l++) {
        for (int c = 0; c < matrix1.colunas; c++) {
            soma.mtx[l][c].Re = matrix1.mtx[l][c].Re + matrix2.mtx[l][c].Re;
            soma.mtx[l][c].Im = matrix1.mtx[l][c].Im + matrix2.mtx[l][c].Im;
        }
    }

    return soma;
}

complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2) {
    complexMatrix subtracao = allocateComplexMaatrix(matrix1.linhas, matrix1.colunas);

    for (int l = 0; l < matrix1.linhas; l++) {
        for (int c = 0; c < matrix1.colunas; c++) {
            subtracao.mtx[l][c].Re = matrix1.mtx[l][c].Re - matrix2.mtx[l][c].Re;
            subtracao.mtx[l][c].Im = matrix1.mtx[l][c].Im - matrix2.mtx[l][c].Im;
        }
    }

    return subtracao;
}

complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num) {
    complexMatrix produtoEscalar = allocateComplexMaatrix(matrix.linhas, matrix.colunas);

    for (int l = 0; l < matrix.linhas; l++) {
        for (int c = 0; c < matrix.colunas; c++) {
            produtoEscalar.mtx[l][c].Re = matrix.mtx[l][c].Re * num;
            produtoEscalar.mtx[l][c].Im = matrix.mtx[l][c].Im * num;
        }
    }

    return produtoEscalar;
}

complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2) {
    complexMatrix produto = allocateComplexMaatrix(matrix1.linhas, matrix1.colunas);

    for (int l = 0; l < matrix1.linhas; l++) {
        for(int c = 0; c < matrix1.colunas; c++) {
            produto.mtx[l][c].Re = matrix1.mtx[l][c].Re * matrix2.mtx[l][c].Re;
            produto.mtx[l][c].Im = matrix1.mtx[l][c].Im * matrix2.mtx[l][c].Im;
        }
    }

    return produto;
}

/************************ FUNÇÕES DE TESTE **************************/
void printComplex(complex num) {
    printf("%.2f + %.2fi\n", num.Re, num.Im);
}

void printMatrix(complexMatrix matrix) {
    for (int l = 0; l < matrix.linhas; l++) {
        for (int c = 0; c < matrix.colunas; c++) {
        printf("[%d][%d]: ", l, c);
        printComplex(matrix.mtx[l][c]);
        }
    }
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
            printf("[%d][%d]: ", l, c);
            printComplex(transposta.mtx[l][c]);
        }
    }
}

void printConjugada(complexMatrix conjugada) {
    for (int l = 0; l < conjugada.linhas; l++) {
        for (int c = 0; c < conjugada.colunas; c++) {
            printf("[%d][%d]: ", l, c);
            printComplex(conjugada.mtx[l][c]);
        }
    }
}

void printHermitiana(complexMatrix hermitiana) {
    for (int l = 0; l < hermitiana.linhas; l++) {
        for(int c = 0; c < hermitiana.colunas; c++) {
            printf("[%d][%d]: ", l, c);
            printComplex(hermitiana.mtx[l][c]);
        }
    }
}

void printSoma(complexMatrix soma) {
    for(int l = 0; l < soma.linhas; l++) {
        for(int c = 0; c < soma.colunas; c++) {
            printf("[%d][%d]: ", l, c);
            printComplex(soma.mtx[l][c]);
        }
    }
}

void printSubtracao(complexMatrix subtracao) {
    for (int l = 0; l < subtracao.linhas; l++) {
        for (int c = 0; c < subtracao.colunas; c++) {
            printf("[%d][%d]: ", l, c);
            printComplex(subtracao.mtx[l][c]);
        }
    }
}

void print_produtoEscalar(complexMatrix produtoEscalar) {
    for (int l = 0; l < produtoEscalar.linhas; l++) {
        for (int c = 0; c < produtoEscalar.colunas; c++ ) {
            printf("[%d][%d]: ", l, c);
            printComplex(produtoEscalar.mtx[l][c]);
        }
    }
}

void printProduto(complexMatrix produto) {
    for (int l = 0; l < produto.linhas; l++) {
        for (int c = 0; c < produto.colunas; c++ ) {
            printf("[%d][%d]: ", l, c);
            printComplex(produto.mtx[l][c]);
        }
    }
}
void teste_todos(){
int linhas = 3;
    int colunas = 3;
    float num = 2.5;

    //chamando a funï¿½ï¿½o que cria e aloca memï¿½ria para a matriz complexa
    complexMatrix matrix = allocateComplexMaatrix(linhas, colunas);
    complexMatrix matrix1 = allocateComplexMaatrix(linhas, colunas);
    complexMatrix matrix2 = allocateComplexMaatrix(linhas, colunas);

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

    printf("\n Matriz Original: \n");
    printMatrix(matrix);

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

}
