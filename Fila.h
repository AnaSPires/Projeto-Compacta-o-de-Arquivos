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



#endif
