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

    if(no->frequencia <= (inicio-> info->frequencia))
    {
        NoFila* novo = create();
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

    if((des->info->frequencia)>(des->prox->info->frequencia))
    {
        NoFila* aux = des;
        des = des->prox;

        aux->prox = des->prox;

        des->prox = aux;
    }

    des->prox = ordenar(des->prox);
    return des;
}

NoArvore* pop(NoFila** no)
{
   NoArvore* ret = (*no)->info;
   *no = (*no)->prox;
   return ret;
}

NoFila* existe(char caracter, NoFila* inicio)
{
    if(inicio == NULL)
        return NULL;

    if(inicio->info->caracter == caracter)
    {
        inicio->info->frequencia += 1;
        return inicio;
    }

    if(inicio->prox == NULL)
        return NULL;

    NoFila* result = existe(caracter, inicio->prox);

    if(result == NULL)
        return NULL;

    inicio->prox = result;

    return inicio;
}

NoFila* buscar(char caracter, NoFila* inicio)
{
    NoFila* atual = existe(caracter, inicio);

    if(atual == NULL)
     {
         NoArvore* novo = create();
         novo->caracter = caracter;
         novo->frequencia = 1;
         novo->vazio = 0;

         return insira(inicio,novo);
     }

     return ordenar(inicio);
}




/*NoFila* buscar(char caracter, NoFila* inicio)
{
     NoArvore* novo = create();
     novo->caracter = caracter;
     novo->frequencia = 1;
     novo->vazio = 0;


    if(inicio == NULL)
     {

         return insira(inicio,novo);
     }

    if(inicio->info->caracter == caracter)
    {
        inicio->info->frequencia+=1;
        return ordenar(inicio);
    }

    if(inicio->info->frequencia <= novo->frequencia)
        return insira(inicio,novo);
    else
    {
        NoFila* noFila = (NoFila*)malloc(sizeof(NoFila));
        noFila -> info = novo;

        noFila -> prox = inicio;

        return noFila;
    }

    inicio ->prox = buscar(caracter, inicio->prox);
    return inicio;
}*/
