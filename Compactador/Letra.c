#include<stdio.h>
#include "Letra.h"

NoLetra* createL(){
    NoLetra *no = (NoLetra*)malloc(sizeof(NoLetra));
    no->prox = NULL;
}

NoLetra* add(NoLetra* inicio, NoLetra* no)
{
  if(inicio == NULL)
  {
      return no;
  }
  if(inicio->prox == NULL)
  {
      inicio->prox = no;
      return inicio;
  }

  inicio->prox = add(inicio->prox, no);
  return inicio;
}

NoLetra* acharLetra(char l, NoLetra* inicio)
{
    while(inicio != NULL)
    {
        if(inicio->caracter == l)
            return inicio;
        else
            inicio = inicio->prox;
    }
    return NULL;
}

