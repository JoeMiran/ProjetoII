#include <stdio.h>
#include <stdlib.h>

/*O cÃ³digo a baixo tambÃ©m poderia ser escrito apenas usando quatro vezes o comando "printf", 
um para cada membro do grupo. No entanto, na visÃ£o da equipe, o modelo abaixo Ã© mais limpo, 
ajustÃ¡vel e dinÃ¢mico.*/

int main() {
	// Inicio da apresentaÃ§Ã£o da equipe.
	int i, m, n, o, p;
	char nomes[4][30] = {"Joel Tavares", "David Sousa", "Kelton Cantao", "Carolyn Aviz"};
	char matriculas[4][30] = {"202206840054", "202207040045", "202007040033", "202106840046"};
	printf("Nomes completos e matriculas dos alunos:\n");
	for (i = 0; i < 4; i++) {
		printf("%s - %s\n", nomes[i], matriculas[i]);
	}
	// Fim da apresentaÃ§Ã£o da equipe.
	return 0;
}

/*int A[m][n], B[o][p], C[m][p], aux1, aux2;	// Perceba que, se o nÃºmero de colunas na matriz A (n) Ã© igual ao numero de linhas na matriz B (p), a matriz resultante C serÃ¡ de dimensÃ£o m,p.
	printf("\nDimensÃµes da Matriz A: ");
	scanf("%d%d", &m, &n);
	printf("\nDimensÃµes da Matriz B: ");
	scanf("%d%d", &o, &p);

	if (n=!p)	// Se o indice n for diferente de p serÃ¡ impresso uma mensagem de erro.
	    printf("NÃ£o Ã© possÃ­vel multiplicar as matrizes");	// NegaÃ§Ã£o do if de verificaÃ§Ã£o.	
	else {      // Caso contrÃ¡rio, prossegue-se para a inserÃ§Ã£o e posteriormente, para a multiplicaÃ§Ã£o.
	    // InserÃ§Ã£o dos dados da matriz A por parte do usuÃ¡rio.
		for (aux1 = 1; aux1 <= m; aux1++){		// VariaÃ§Ã£o da linha.
			for(aux2 = 1; aux2 <= n; aux2++){	// VariaÃ§Ã£o da coluna.
				printf("Insira um valor na posicÃ£o Matriz A [%d,%d]: ", aux1, aux2);
				scanf ("%d", &A[aux1][aux2]);   // Armazenamento do valor em determinada posiÃ§Ã£o.
			}
		}

		// InserÃ§Ã£o dos dados da matriz B por parte do usuÃ¡rio.
		for (aux1 = 1; aux1 <= o; aux1++){		// VariaÃ§Ã£o da linha.
			for(aux2 = 1; aux2 <= p; aux2++){	// VariaÃ§Ã£o da coluna.
				printf("Insira um valor na posicÃ£o Matriz B [%d,%d]: ", aux1, aux2);
				scanf ("%d", &B[aux1][aux2]);	// Armazenamento do valor em determinada posiÃ§Ã£o.
			}
		}
		
		// Aqui seria um bom lugar para realizar a multiplicaÃ§Ã£o.
    	}*/