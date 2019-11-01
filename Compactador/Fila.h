#include "NoArvore.h"
#ifndef FILA
#define FILA

typedef struct NoFila
{
    NoArvore* info;
    struct NoFila *prox;
}NoFila;



extern NoFila* insira(NoFila* inicio, NoArvore* no);
extern NoArvore* pop(NoFila** no);
extern NoFila* ordenar(NoFila* des);
extern NoFila* existe(char caracter, NoFila* inicio);
extern NoFila* buscar(char caracter, NoFila* inicio);


#endif
