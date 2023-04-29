/* Cria um novo tipo de dado com o nome 'complexo'.
Essa estrutura de dados possui dois campo do tipo float,
um para a parte real e outro para a parte imagin�ria.*/
typedef struct { 
    float Real, Imag;
} NumComplexo;

/*A declara��o "NumComplexo*ponteiro" cria um ponteiro que 
aponta para um endere�o de mem�ria onde um valor do tipo complexo
est� armazenado. � tipo uma vari�vel de controle* que aponta endere�os*/
typedef struct {
    NumComplexo *ponteiro;
    int tamanho; 
} VetorComplexo;

/* A estrutura "NumComplexo **ponteiro;" � basicamente um ponteiro que 
aponta para o vetor de ponteiros anterior */
typedef struct  {
    NumComplexo **ponteiro;
    int linhas, colunas;
} MatrizComplexa;
