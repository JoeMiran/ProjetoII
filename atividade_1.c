#include <stdio.h>
#include <stdlib.h>

/*O código a baixo também poderia ser escrito apenas usando quatro vezes o comando "printf", 
um para cada membro do grupo. No entanto, na visão da equipe, o modelo abaixo é mais limpo, 
ajustável e dinâmico.*/

int main() {
	// Inicio da apresentação da equipe.
	int i, m, n, o, p;
	char nomes[4][30] = {"Joel Tavares", "David Sousa", "Kelton Cantao", "Carolyn Aviz"};
	char matriculas[4][30] = {"202206840054", "202207040045", "202007040033", "202106840046"};
	printf("Nomes completos e matriculas dos alunos:\n");
	for (i = 0; i < 4; i++) {
		printf("%s - %s\n", nomes[i], matriculas[i]);
	}
	// Fim da apresentação da equipe.

	int A[m][n], B[o][p], C[m][p];	// Perceba que, se o número de colunas na matriz A (n) é igual ao numero de linhas na matriz B (p), a matriz resultante C será de dimensão m,p.
	printf("\nDimensões da Matriz A: ");
	scanf("%d%d", &m, &n);
	printf("\nDimensões da Matriz B: ");
	scanf("%d%d", &o, &p);

	if (n=p){	// Verificação da possibilidade de multiplicação entre as matrizes. O indice n deve ser igual a p, caso contrário, deve ser impresso uma mensagem de erro.
		// Inserção dos dados da matriz A por parte do usuário.
		for (aux1 = 1; aux1 =< m; aux1++){		// Variação da linha.
			for(aux2 = 1; aux2 =< n; aux2++){	// Variação da coluna.
				printf("Insira um valor em Matriz A [%d,%d]: ", aux1, aux2);
				scanf ("%d", );			// Armazenamento do valor em determinada posição.
			}
		}

		// Inserção dos dados da matriz B por parte do usuário.
		for (aux1 = 1; aux1 =< o; aux1++){		// Variação da linha.
			for(aux2 = 1; aux2 =< p; aux2++){	// Variação da coluna.
				printf("Insira um valor em Matriz B [%d,%d]: ", aux1, aux2);
				scanf ("%d", );			// Armazenamento do valor em determinada posição.
			}
		}
    	}
	else
	printf("Não é possível multiplicar as matrizes");	// Negação do if de verificação.
	return 0;
}
