#include <stdio.h>

int main() {
    int i;  
    char nomes[4][30] = {
      "Joel Tavares", 
      "David Sousa", 
      "Kelton Cantao",
      "Carolyn"
    };
    char matriculas[4][30] = {
      "202206840054", 
      "202207040045", 
      "202007040033", 
      "202007040000"
    };  
    
    printf("Nomes completos e matriculas dos alunos:\n");
    for (i = 0; i < 4; i++) {
        printf("%s - %s\n", nomes[i], matriculas[i]);
    }

    return 0;
}
