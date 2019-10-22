#include "NoArvore.h"
#ifndef FILA
#define FILA

typedef struct NoLista
{
    NoArvore info;
    struct NoLista *prox;
}NoLista;

typedef struct NoLista * insira( struct NoLista* proximo, NoArvore no)
{
    if(no == NULL)
        return NULL;

     struct NoLista* novo = (struct NoLista*)malloc(sizeof(struct NoLista));
     novo -> info = no;

    if(proximo == NULL)
        novo -> prox = NULL;

    else
        novo -> prox = proximo;

        return novo;

}



#endif
