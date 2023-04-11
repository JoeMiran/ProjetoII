#include <stdio.h>

/*O código a baixo também poderia ser escrito apenas usando quatro vezes o comando "printf", 
um para cada membro do grupo. No entanto, na visão da equipe, o modelo abaixo é mais limpo, 
ajustável e dinâmico.*/

int main() {
    // Inicio da apresentação da equipe.
    int i;  
    char nomes[4][30] = {
      "Joel Tavares", 
      "David Sousa", 
      "Kelton Cantao",
      "Carolyn Aviz"
    };
    char matriculas[4][30] = {
      "202206840054", 
      "202207040045", 
      "202007040033", 
      "202106840046",
    };  
    
    printf("Nomes completos e matriculas dos alunos:\n");
    for (i = 0; i < 4; i++) {
        printf("%s - %s\n", nomes[i], matriculas[i]);
    }
    // Fim da apresentação da equipe.
    
    int A[m][n], B[o][p], C[m][p];	// Perceba que, se o número de colunas na matriz A (n) é igual ao numero de linhas na matriz B (p), a matriz resultante C será de dimensão m,p.
    printf("\nDimensões da Matriz A: ");
	scanf("%d%d", &m, &n);
	printf("\nDimensões da Matriz B; ");
	scanf("%d%d", &o, &p);
    
    return 0;
}
