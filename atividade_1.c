#include <stdio.h>

int main() {
    int i;  
    char nomes[3][30] = {
      "Joel Tavares", 
      "David Sousa", 
      "Kelton Cantao",
    };
    char matriculas[3][30] = {
      "202206840054", 
      "202207040045", 
      "202007040033", 
    };  
    
    printf("Nomes completos e matriculas dos alunos:\n");
    for (i = 0; i < 3; i++) {
        printf("%s - %s\n", nomes[i], matriculas[i]);
    }

    return 0;
}
