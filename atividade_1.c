#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome[100] = {'Joel Miranda', 'Kelton Cantao', 'David Sousa', 'Carolyn'};
    char matricula[100] = {'202206840054', '202007040033','202207040045','202007040033'};
    printf("Nome dos integrantes: ");
        for(int i = 0; i < 2 ; i++)
            printf("Nome: %s",nome[i]);
    printf("matricula dos integrantes: ");
        for(int i = 0; i < 2 ; i++)
            printf("matricula: %s",matricula[i]);
    return 0;
}
