#include <stdio.h>
#include <stdlib.h>

// incluindo o arquivos onde está contido a estrutura
#include "matrizes.h"

/************************************* FUNÇÃO PARA ALOCAÇÃO DE MEMÓRIA ***************************************/

// Criando uma função cujo objetivo é alocar memória dinamicamente para a matriz complexa
complexMatrix allocateComplexMaatrix(int linhas, int colunas)
{

    // Declarando a variável matrix do tipo complexMatrix
    complexMatrix matrix;

    // A variavel do tipo complexMatrix tem os "atributos" linhas e colunas e deve recebê-los como parâmetros
    matrix.linhas = linhas;
    matrix.colunas = colunas;

    // Alocando memória para as linhas de matrix
    matrix.mtx = (complex **)malloc(linhas * sizeof(complex *));

    // Tratando possíveis erros na alocação de memória para as linhas
    if (matrix.mtx == NULL)
    {
        printf("Falha na alocação de memória\n");
        exit(1);
    }

    // Alocando memória para as colunas de cada linha
    for (int i = 0; i < linhas; i++)
    {
        matrix.mtx[i] = (complex *)malloc(colunas * sizeof(complex));

        // Tratando possíveis erros na alocação de memória para as colunas
        if (matrix.mtx == NULL)
        {
            printf("Falha na alocaÃ§Ã£o de memÃ³ria\n");
            exit(1);
        }
    }

    // Retornado matrix
    return matrix;
}

/************************************* FUNÇÕES DE OPERAÇÃO ***************************************/

// Criando uma função para realizar o cálculo da transposta
complexMatrix matrixTransposta(complexMatrix matrix)
{

    // Alocando memória para a matriz transposta
    complexMatrix transposta = allocateComplexMaatrix(matrix.colunas, matrix.linhas);

    // Percorrendo cada elemento da matriz original
    for (int i = 0; i < matrix.linhas; i++)
    {
        for (int j = 0; j < matrix.colunas; j++)
        {

            // Atribuindo o valor do elemento atual da matriz original para a transposta
            // Trocando a posição das linhas e colunas na matriz transposta
            transposta.mtx[j][i].Re = matrix.mtx[i][j].Re;
            transposta.mtx[j][i].Im = matrix.mtx[i][j].Im;
        }
    }
    return transposta;
}

// Criando uma função para realizar o cálculo da conjugada
complexMatrix matrixConjugada(complexMatrix matrix)
{

    // Alocando memória para a matriz conjugada utilizando a função allocateComplexMaatrix
    complexMatrix conjugada = allocateComplexMaatrix(matrix.colunas, matrix.linhas);

    // Loop para percorrer cada elemento da matriz original
    for (int i = 0; i < matrix.linhas; i++)
    {
        for (int j = 0; j < matrix.colunas; j++)
        {
            // Atribuindo o valor do elemento atual da matriz original para a conjugada
            conjugada.mtx[i][j].Re = matrix.mtx[i][j].Re;
            conjugada.mtx[i][j].Im = -matrix.mtx[i][j].Im; // Inverte o sinal da parte imaginária
        }
    }

    // Retornando a matriz conjugada
    return conjugada;
}

// Criando uma função para realizar o cálculo da hermitiana
complexMatrix matrixHermitiana(complexMatrix transposta)
{

    // Alocando memória para a matriz Hermitiana
    complexMatrix hermitiana = allocateComplexMaatrix(transposta.colunas, transposta.linhas);

    // Loop para percorrer cada elemento da matriz transposta
    for (int i = 0; i < transposta.linhas; i++)
    {
        for (int j = 0; j < transposta.colunas; j++)
        {

            // Atribuindo o valor do elemento atual da matriz transposta para a hermitiana
            hermitiana.mtx[i][j].Re = transposta.mtx[i][j].Re;
            hermitiana.mtx[i][j].Im = -transposta.mtx[i][j].Im; // Inverte o sinal da parte imaginária
        }
    }

    // Retornando a matriz hermitiana
    return hermitiana;
}

// Criando uma função para realizar a soma da matrix A e B, que estou apelidando de matrix1 e matrix2
complexMatrix matrixSoma(complexMatrix matrix1, complexMatrix matrix2)
{

    // Alocando memória para a matrix soma
    complexMatrix soma = allocateComplexMaatrix(matrix1.linhas, matrix1.colunas);

    // Loop para percorrer cada elemento da matrix1 considerando que matrix1 e matrix2 têm a mesma dimensão
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {

            // Somando os elementos correspondentes e atribuindo o resultado na matriz soma
            soma.mtx[l][c].Re = matrix1.mtx[l][c].Re + matrix2.mtx[l][c].Re;
            soma.mtx[l][c].Im = matrix1.mtx[l][c].Im + matrix2.mtx[l][c].Im;
        }
    }

    // Retornando a matriz Soma
    return soma;
}

// Criando uma função para realizar a subtração entre matrix1 e matrix2
complexMatrix matrixSubtracao(complexMatrix matrix1, complexMatrix matrix2)
{

    // Alocando memória para a matriz subtração
    complexMatrix subtracao = allocateComplexMaatrix(matrix1.linhas, matrix1.colunas);

    // Loop para percorrer cada elemento da matrix1 considerando que matrix1 e matrix2 têm a mesma dimensão
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {

            // Subtraindo os elementos correspondentes e atribuindo o resultado na matriz subtração
            subtracao.mtx[l][c].Re = matrix1.mtx[l][c].Re - matrix2.mtx[l][c].Re;
            subtracao.mtx[l][c].Im = matrix1.mtx[l][c].Im - matrix2.mtx[l][c].Im;
        }
    }

    // Retornando a matriz Subtração
    return subtracao;
}

// Criando uma função para realizar a multiplicação de um número escalar com cada elemento da matriz original
complexMatrix matrix_produtoEscalar(complexMatrix matrix, float num)
{

    // Alocando memória para a matrix resultado do produto escalar
    complexMatrix produtoEscalar = allocateComplexMaatrix(matrix.linhas, matrix.colunas);

    // Loop para percorrer cada elemento da matriz original
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {

            // Multiplicando um número a cada elemento da matriz original e atribuindo o resultado aos elementos a produtoEscalar
            produtoEscalar.mtx[l][c].Re = matrix.mtx[l][c].Re * num;
            produtoEscalar.mtx[l][c].Im = matrix.mtx[l][c].Im * num;
        }
    }

    // Retornando produtoEscalar
    return produtoEscalar;
}

// Criando uma função para realizar o produto entre matrix1 e matrix2
complexMatrix matrixProduto(complexMatrix matrix1, complexMatrix matrix2)
{

    // Alocando memória para a matrix resultado do produto
    complexMatrix produto = allocateComplexMaatrix(matrix1.linhas, matrix1.colunas);

    // Loop para percorrer cada elemento da matrix1 considerando que matrix1 e matrix2 têm a mesma dimensão
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {

            // Multiplicando matrix1 e matrix2 e atribuindo o resultao a produto
            produto.mtx[l][c].Re = matrix1.mtx[l][c].Re * matrix2.mtx[l][c].Re;
            produto.mtx[l][c].Im = matrix1.mtx[l][c].Im * matrix2.mtx[l][c].Im;
        }
    }

    // Retorna a matriz produto
    return produto;
}

/************************ FUNÇÕES DE TESTE **************************/

// Função para imprimir um número complexo com sua parte real e imaginária
void printComplex(complex num)
{
    printf("%.2f + %.2fi\n", num.Re, num.Im);
}

// Função para imprimir a Matriz Original
void printMatrix(complexMatrix matrix)
{
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(matrix.mtx[l][c]);
        }
    }
}

// Função para imprimir a Matriz A
void printMatrix1(complexMatrix matrix1)
{
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(matrix1.mtx[l][c]);
        }
    }
}

// Função para imprimir a Matriz B
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

// Função para imprmir a Matriz Transposta
void printTransposta(complexMatrix transposta)
{
    for (int l = 0; l < transposta.linhas; l++)
    {
        for (int c = 0; c < transposta.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(transposta.mtx[l][c]);
        }
    }
}

// Função para imprimir a Matriz Conjugada
void printConjugada(complexMatrix conjugada)
{
    for (int l = 0; l < conjugada.linhas; l++)
    {
        for (int c = 0; c < conjugada.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(conjugada.mtx[l][c]);
        }
    }
}

// Função para imprimir a Matriz Hermitiana
void printHermitiana(complexMatrix hermitiana)
{
    for (int l = 0; l < hermitiana.linhas; l++)
    {
        for (int c = 0; c < hermitiana.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(hermitiana.mtx[l][c]);
        }
    }
}

// Função para imprimir a Matriz Resultado da Soma
void printSoma(complexMatrix soma)
{
    for (int l = 0; l < soma.linhas; l++)
    {
        for (int c = 0; c < soma.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(soma.mtx[l][c]);
        }
    }
}

// Função para imprimir a Matriz Resultado da Subtração
void printSubtracao(complexMatrix subtracao)
{
    for (int l = 0; l < subtracao.linhas; l++)
    {
        for (int c = 0; c < subtracao.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(subtracao.mtx[l][c]);
        }
    }
}

// Função para imprimir a Matriz Resultado do Produto Escalar
void print_produtoEscalar(complexMatrix produtoEscalar)
{
    for (int l = 0; l < produtoEscalar.linhas; l++)
    {
        for (int c = 0; c < produtoEscalar.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(produtoEscalar.mtx[l][c]);
        }
    }
}

//Função para imprimir a Matriz Resultado do Produto Matricial
void printProduto(complexMatrix produto)
{
    for (int l = 0; l < produto.linhas; l++)
    {
        for (int c = 0; c < produto.colunas; c++)
        {
            printf("[%d][%d]: ", l, c);
            printComplex(produto.mtx[l][c]);
        }
    }
}

//Essa função será chamada no arquivo main.c e será responsável por imprimir na tela o nome de equipe e as operações com as funções
void teste_todos()
{
    //O número de linhas, colunas e o valor do escalar são hardcode para facilitar a compilação
    int linhas = 3;
    int colunas = 3;
    float num = 2.5;

    // chamando a função que cria e aloca memória para as matrizes Original, A e B
    complexMatrix matrix = allocateComplexMaatrix(linhas, colunas);
    complexMatrix matrix1 = allocateComplexMaatrix(linhas, colunas);
    complexMatrix matrix2 = allocateComplexMaatrix(linhas, colunas);

    // Preenchendo a Matriz Original
    for (int l = 0; l < matrix.linhas; l++)
    {
        for (int c = 0; c < matrix.colunas; c++)
        {
            matrix.mtx[l][c].Re = l + c + 1.4;
            matrix.mtx[l][c].Im = l + c + 4.0;
        }
    }

    //Chamando as funções definidas anteriormente que dependenda da Matriz Original
    complexMatrix transposta = matrixTransposta(matrix);
    complexMatrix conjugada = matrixConjugada(matrix);
    complexMatrix hermitiana = matrixHermitiana(transposta);

    // Preenchendo a Matriz A
    for (int l = 0; l < matrix1.linhas; l++)
    {
        for (int c = 0; c < matrix1.colunas; c++)
        {
            matrix1.mtx[l][c].Re = l + c + 1.0;
            matrix1.mtx[l][c].Im = l + c + 2.0;
        }
    }

    // Preenchendo a Matriz B
    for (int l = 0; l < matrix2.linhas; l++)
    {
        for (int c = 0; c < matrix2.colunas; c++)
        {
            matrix2.mtx[l][c].Re = l + c + 1.5;
            matrix2.mtx[l][c].Im = l + c + 2.5;
        }
    }

    //Chamando as funções criadas anteriormente que dependem das Matrizes A e B
    complexMatrix soma = matrixSoma(matrix1, matrix2);
    complexMatrix subtracao = matrixSubtracao(matrix1, matrix2);
    complexMatrix produtoEscalar = matrix_produtoEscalar(matrix, num);
    complexMatrix produto = matrixProduto(matrix1, matrix2);

    /******************** IMPRIMINDO AS FUNÇÕES DE TESTE *********************/
    
    //imprimindo a equipe
    printf("\n ======Equipe====== \n");
    printf("Joel Tavares Miranda\n");
    printf("David Pinheiro \n");
    printf("Leonam Bronze\n");
    printf("Nicolas Ranniery\n");


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
