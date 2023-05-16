#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

//Criando uma matriz do tipo complexMatrix que aloca dinamicamnetea mem�ria para cada linha
complexMatrix allocateComplexMaatrix(int linhas, int colunas) {
    
    complexMatrix matrix;
    matrix.linhas = linhas;
    matrix.colunas = colunas;
    
    //Alocandoo mem�ria para as linhas
    matrix.mtx = (complex**)malloc(linhas * sizeof(complex*));
    if (matrix.mtx == NULL) {
        printf("Falha na aloca��o de mem�ria\n");
        exit(1);
    }
    
    //Alocando mem�ria para cada coluna de cada linha
    for (int i = 0; i < linhas; i++) { 
        matrix.mtx[i] = (complex*)malloc(colunas * sizeof(complex));
        if (matrix.mtx == NULL) {
            printf("Falha na aloca��o de mem�ria\n");
            exit(1);
        }
    }

    //Preenchendo a matriz complexa
    for (int l = 0; l < matrix.linhas; l++) {
        for (int c = 0; c < matrix.colunas; c++) {
            matrix.mtx[l][c].Re = 2 * l;
            matrix.mtx[l][c].Im = 2 * c;
        }
    }

    //Imprimindo o valor da matriz complexa
    for (int l = 0; l < matrix.linhas; l++) {
        for (int c = 0; c  < matrix.colunas; c++) {
            printf("[%d][%d]: ", l, c);
            printComplex(matrix.mtx[l][c]);
        }
    }
    
    return matrix;
}

/************************ FUN��ES DE OPERA��O **************************/

complexMatrix matrixTransposta(complexMatrix matrix) {

    complexMatrix transposta;
    transposta.linhas = matrix.colunas;
    transposta.colunas = matrix.linhas;
    transposta.mtx = (complex**)malloc(transposta.linhas * sizeof(complex*));
    if (transposta.mtx == NULL) {
        printf("Falha na aloca��o de mem�ria\n");
        exit(1);
    }

    for (int i = 0; i < transposta.linhas; i++) {
        transposta.mtx[i] = (complex*)malloc(transposta.colunas * sizeof(complex));
        if (transposta.mtx[i] == NULL) {
            printf("Falha na aloca��o de mem�ria\n");
            for (int j = 0; j < i; j++) {
                free(transposta.mtx[j]);
            } 
            free(transposta.mtx);
            exit(1);
        }
    }

    for (int i = 0; i < matrix.linhas; i++) {
        for (int j = 0; j < matrix.colunas; j++) {
            transposta.mtx[i][j].Re = matrix.mtx[i][j].Re;
            transposta.mtx[j][i].Im = matrix.mtx[i][j].Im;
        }
    }
    return transposta;

}

complexMatrix matrixConjugada(complexMatrix matrix) {

    complexMatrix conjugada; //Declarando a matriz conjugada
    
    //A matriz conjugada vai receber as mesmas linhas e colunas da matriz original
    conjugada.linhas = matrix.linhas; 
    conjugada.colunas = matrix.colunas;

    //Alocando mem�ria para as linhas
    conjugada.mtx = (complex**)malloc(conjugada.linhas * sizeof(complex*));
    //Verificando se n�o houve nenhum erro na aloca��o das linhas
    if(conjugada.mtx == NULL) {
        printf("Erro na aloca��o da mem�ria");
        exit(1);
    }

    //Alocando mem�ria para as colunas de cada linha
    for (int i = 0; i < conjugada.linhas; i++) {
        conjugada.mtx[i] = (complex*)malloc(conjugada.colunas * sizeof(complex));
        //Verificando se n�o h� nenhum erro na aloca��o
        if (conjugada.mtx[i] == NULL) {
            printf("Falha na aloca��o da mem�ria\n");
            //Liberando a mem�ria em caso de erro
            for (int j = 0; j < i; j++) {
                free(conjugada.mtx[j]);
            }
            free(conjugada.mtx);
            exit(1);
        }
    }

    //Aqui vai a opera��o em si, que transforma a matriz original na sua conjjugada
    for (int i = 0; i < matrix.linhas; i++) {
        for(int j = 0; j < matrix.colunas; j++) {
            conjugada.mtx[i][j].Re = matrix.mtx[i][j].Re;
            conjugada.mtx[i][j].Im = -matrix.mtx[i][j].Im;//Inverte o sinal da parte imagin�ria
        }
    }

    return conjugada;

}

complexMatrix matrixHermitiana(complexMatrix transposta) {
    
    complexMatrix hermitiana;

    hermitiana.linhas = transposta.linhas;
    hermitiana.colunas = transposta.colunas;

    hermitiana.mtx = (complex**)malloc(hermitiana.linhas * sizeof(complex*));
    if(hermitiana.mtx == NULL) {
        printf("Erro na aloca��o da mem�ria\n");
        exit(1);
    }

    for (int i = 0; i < hermitiana.linhas; i++) {
        hermitiana.mtx[i] = (complex*)malloc(hermitiana.colunas * sizeof(complex));
        if (hermitiana.mtx[i] == NULL) {
            printf("Erro na aloca��o da mem�ria: \n");
            
            for (int j = 0; j < i; j++) {
                free(hermitiana.mtx[j]);
            }
            free(hermitiana.mtx);
            exit(1);
        }
    }

    for (int i = 0; i < transposta.linhas; i++) {
        for(int j = 0; j < transposta.colunas; j++) {
            hermitiana.mtx[i][j].Re = transposta.mtx[i][j].Re;
            hermitiana.mtx[i][j].Im = -transposta.mtx[i][j].Im;
        }
    }

    return hermitiana;

}

/************************ FUN��ES DE TESTE **************************/
void printComplex(complex num) {
    printf("%.2f + %.2fi\n", num.Re, num.Im);
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