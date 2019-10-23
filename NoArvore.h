#ifndef NOARVORE
#define NOARVORE

typedef struct NoArvore
{
    char caracter;
    int vazio;
    int frequencia;
    struct NoArvore *esq, *dir;
}NoArvore;

extern NoArvore* create();

#endif // FILA
