#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome[30] = {'Joel Miranda', 'Kelton Cantao', 'David Sousa', 'Carolyn'};
    char matricula[30] = {'202206840054', '202007040033','202207040045','202007040033'};
    printf("Nome dos integrantes: ");
       for(int i = 0; i < 4 ; i++)
            printf("Nome: %s\n",nome[i]);
    printf("matricula dos integrantes: ");
        for(int i = 0; i < 4 ; i++)
            printf("matricula: %s\n",matricula[i]);
    return 0;
}
