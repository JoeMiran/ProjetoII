///@file main.c
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

/// Including the files where the structure is contained
#include "matrizes.h"

/// Creating the prototype of the function that will be called in the scope of main and was defined in matrizes.c
void teste_todos();

int main()
{

    /// Calling the function that will print all test functions
    teste_todos();

    return 0;
}