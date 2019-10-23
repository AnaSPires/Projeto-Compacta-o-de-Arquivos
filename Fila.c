#include<stdio.h>
#include "Fila.h"
#include "NoArvore.h"

NoFila * insira(NoFila* inicio, NoArvore* no)
{
    if(inicio == NULL){
        NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
        novo -> info = no;
        novo -> prox = NULL;

        return novo;
    }

    else
        if(no->frequencia< (inicio-> info->frequencia) ||no->frequencia == (inicio-> info->frequencia))
        {
            NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
            novo -> info = no;
            novo -> prox = inicio;

            return novo;
        }
        else{
            inicio->prox = insira(inicio->prox, no);
            return inicio;
        }

}

NoFila* ordenar(NoFila* inicio)
{
    if(inicio->prox == NULL)
        return NULL;

    if((inicio->info->frequencia)<=(inicio->prox->info->frequencia))
    {
        inicio->prox = ordenar(inicio->prox);
        return inicio;
    }
    else
    {
        NoFila* aux = inicio;  //m
        inicio = inicio->prox; //e
        aux->prox = inicio->prox; //m->a
        inicio->prox = aux; //e ->m
        inicio->prox = ordenar(inicio->prox); //m

        return inicio;
    }
}

NoArvore* pop(NoFila** no)
{
       NoArvore* ret = (*no)->info;
       *no = (*no)->prox;
       return ret;
}

NoFila* buscar(char caracter, NoFila* inicio)
{
    if(inicio == NULL || inicio ->prox == NULL)
     {
         NoArvore* novo = create();
         novo->caracter = caracter;
         novo->frequencia = 1;
         novo->vazio = 0;

         return insira(inicio,novo);
     }
    while(inicio->info->caracter != caracter)
    {
        if(inicio->prox == NULL)
        {
             NoArvore* novo = create();
             novo->caracter = caracter;
             novo->frequencia = 1;
             novo->vazio = 0;

             return insira(inicio,novo);
        }
        inicio = inicio->prox;
    }
    int fre = inicio->info->frequencia+1;
    NoFila* outro = pop(&inicio);
    outro->info->frequencia = fre;
    return insira(inicio,outro);
}
