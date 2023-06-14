///@file main.c
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

/// incluindo o arquivos onde está contido a estrutura
#include "matrizes.h"

/// Criando p protótipo da função que será chamada no escolpo da main e foi definida em matrizes.c
void teste_todos();

int main()
{

    /// Chamando a função que irá imprimir todas as funções de teste
    teste_todos();

    return 0;
}