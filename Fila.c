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
        if(no->frequencia <= (inicio-> info->frequencia))
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

NoFila* ordenar(NoFila* des)
{
    if(des->prox == NULL)
        return des;

    if((des->info->frequencia)<=(des->prox->info->frequencia))
    {
        return des;
    }

    NoFila* aux = des;
    des = des->prox;
    des->prox = aux;

    ordenar(des->prox);
    return des;
}

NoArvore* pop(NoFila** no)
{
       NoArvore* ret = (*no)->info;
       *no = (*no)->prox;
       return ret;
}

NoFila* buscar(char caracter, NoFila* inicio)
{
    if(inicio == NULL)
     {
         NoArvore* novo = create();
         novo->caracter = caracter;
         novo->frequencia = 1;
         novo->vazio = 0;

         return insira(inicio,novo);
     }

    if(inicio->info->caracter == caracter)
    {
        inicio->info->frequencia+=1;
        return ordenar(inicio);
    }

    if(inicio->prox == NULL)
    {
         NoArvore* novo = create();
         novo->caracter = caracter;
         novo->frequencia = 1;
         novo->vazio = 0;

         return insira(inicio,novo);
    }
    inicio ->prox = buscar(caracter, inicio->prox);
    return inicio;
}


/*
NoFila* buscar(char caracter, NoFila* inicio)
{
    if(inicio == NULL || inicio->prox == NULL)
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
    inicio->info->frequencia+=1;
    return ordenar(inicio);
}


*/

