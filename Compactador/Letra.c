#include<stdio.h>
#include "Letra.h"

NoLetra* createL(){
    return (NoLetra*)malloc(sizeof(NoLetra));
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

