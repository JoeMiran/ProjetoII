/* Cria um novo tipo de dado com o nome 'complexo'.
Essa estrutura de dados possui dois campo do tipo float,
um para a parte real e outro para a parte imaginária.*/
typedef struct { 
    float Real, Imag;
} NumComplexo;

/*A declaração "NumComplexo*ponteiro" cria um ponteiro que 
aponta para um endereço de memória onde um valor do tipo complexo
está armazenado. É tipo uma variável de controle* que aponta endereços*/
typedef struct {
    NumComplexo *ponteiro;
    int tamanho; 
} VetorComplexo;

/* A estrutura "NumComplexo **ponteiro;" é basicamente um ponteiro que 
aponta para o vetor de ponteiros anterior */
typedef struct  {
    NumComplexo **ponteiro;
    int linhas, colunas;
} MatrizComplexa;
