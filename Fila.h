#include "NoArvore.h"
#ifndef FILA
#define FILA

typedef struct NoLista
{
    NoArvore info;
    struct NoLista *prox;
}NoLista;

typedef struct NoLista * insira( struct NoLista* inicio, NoArvore no)
{

    if(inicio == NULL){
        struct NoLista* novo = (struct NoLista*)malloc(sizeof(struct NoLista));
        novo -> info = no;
        novo -> prox = NULL;

        return novo;
    }

    else
        if(no< (inicio-> info))
        {
            struct NoLista* novo = (struct NoLista*)malloc(sizeof(struct NoLista));
            novo -> info = no;
            novo -> prox = inicio;

            return novo;
        }
        else{
            inicio->prox = insira(inicio->prox, no);
            return inicio;
        }

}

typedef struct NoLista * remova(struct NoLista* inicio, NoArvore no)
{
    if(inicio == NULL)
        return NULL;

    if(inico->info == no)
    {

    }

}



#endif
