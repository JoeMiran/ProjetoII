#include <stdio.h>

/*O código a baixo também poderia ser escrito apenas usando quatro vezes o comando "printf", 
um para cada membro do grupo. No entanto, na visão da equipe, o modelo abaixo é mais limpo, 
ajustável e dinâmico.*/

int main() {
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

    return 0;
}
