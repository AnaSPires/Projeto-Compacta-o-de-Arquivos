#ifndef NOARVORE
#define NOARVORE

typedef struct NoArvore
{
    char caracter;
    int frequencia;
    struct NoArvore *esq, *dir;
}NoArvore;

extern NoArvore* create();
extern int altura(NoArvore* noAtual);

#endif // FILA
