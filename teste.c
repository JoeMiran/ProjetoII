#include <stdlib.h>
#include <stdio.h>

//Definindo a estrutua complex com parte real e imaginária
typedef struct {
    float Re, Im;
} complex;

//Definindo a estrutura complexMtrix que representa uma matriz complexa
typedef struct {
    int linhas, colunas;
    complex** mtx;
} complexMatrix;

//Criando uma matriz do tipo complexMatrix que aloca dinamicamnetea memória para cada linha
complexMatrix allocateComplexMaatrix(int linhas, int colunas) {
    
    complexMatrix matrix;
    matrix.linhas = linhas;
    matrix.colunas = colunas;
    
    //Alocandoo memória para as linhas
    matrix.mtx = (complex**)malloc(linhas * sizeof(complex*));
    if (matrix.mtx == NULL) {
        printf("Falha na alocação de memória\n");
        exit(1);
    }
    
    //Alocando memória para cada coluna de cada linha
    for (int i = 0; i < linhas; i++) { 
        matrix.mtx[i] = (complex*)malloc(colunas * sizeof(complex));
        if (matrix.mtx == NULL) {
            printf("Falha na alocação de memória\n");
            exit(1);
        }
    }
    return matrix;
}

void printComplex(complex num) {
    printf("%.2f + %.2fi\n", num.Re, num.Im);
}

complexMatrix matrixTransposta(complexMatrix matrix) {

    complexMatrix transposta;
    transposta.linhas = matrix.colunas;
    transposta.colunas = matrix.linhas;
    transposta.mtx = (complex**)malloc(transposta.linhas * sizeof(complex*));
    if (transposta.mtx == NULL) {
        printf("Falha na alocação de memória\n");
        exit(1);
    }

    for (int i = 0; i < transposta.linhas; i++) {
        transposta.mtx[i] = (complex*)malloc(transposta.colunas * sizeof(complex));
        if (transposta.mtx[i] == NULL) {
            printf("Falha na alocação de memória\n");
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

void printTransposta(complexMatrix transposta) {
    for (int l = 0; l < transposta.linhas; l++) {
        for (int c = 0; c < transposta.colunas; c++) {
            printf("transposta[%d][%d]: ", l, c);
            printComplex(transposta.mtx[l][c]);
        }
    }
}

int main() {
    
    int linhas = 3;
    int colunas = 3;

    //chamando a função que cria e aloca memória para a matriz complexa
    complexMatrix matrix = allocateComplexMaatrix(linhas, colunas);

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
            printf("matriz[%d][%d]: ", l, c);
            printComplex(matrix.mtx[l][c]);
        }
    }

    complexMatrix transposta = matrixTransposta(matrix);

    printf("\nMatriz Transposta: \n");
    printTransposta(transposta);

    // Liberando a memória alocada para as matrizes complexas
    for (int i = 0; i < matrix.linhas; i++) {
        free(matrix.mtx[i]);
    }
    free(matrix.mtx);

    for (int i = 0; i < transposta.linhas; i++) {
        free(transposta.mtx[i]);
    }
    free(transposta.mtx);

    return 0;
}
