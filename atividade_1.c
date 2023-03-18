#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome[] = {"Joel Miranda", ", "David Sousa", ""};
    char matricula[] = {"202206840054", "202007040033","202207040045","202007040033"};

    printf("Nome dos integrantes:");
        for(int i = 0; i < 2 ; i++ )
            printf("Nome: %s",nome[]);
    printf("matricula dos integrantes:");
        for(int i = 0; i < 2 ; i++ )
            printf("matricula: %s",matricula[]);
    return 0;

}
