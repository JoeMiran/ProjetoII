#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome[] = {"Joel Miranda", "Kelton Cantao", "David Sousa", "Carolyn"};
    char matricula[] = {"202206840054", "202007040033","202007040033","202007040033"};

    printf("Nome dos integrantes:");
        for(int i = 0; i < 4 ; i++ )
            printf("Nome: %s",nome[]);
    printf("matricula dos integrantes:");
        for(int i = 0; i < 4 ; i++ )
            printf("matricula: %s",matricula[]);
    return 0;

}
