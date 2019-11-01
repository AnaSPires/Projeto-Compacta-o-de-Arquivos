#include "Fila.h"
#include "Letra.h"
#include <stdlib.h>

NoArvore* create()
{
    NoArvore* no = (NoArvore*)malloc(sizeof(NoArvore));
    no->dir = NULL;
    no->esq = NULL;
    return no;
}

NoLetra* createCod(NoLetra* lista,NoArvore* atual, char codigo[], int tam)
{
    if(atual != NULL)
    {
        if(atual->esq != NULL)
        {
            codigo[tam] = "0";
            createCod(lista, atual->esq, codigo,tam + 1);
        }

        if(atual->esq == NULL && atual->dir == NULL)
        {
            NoLetra* no = (NoLetra*)malloc(sizeof(NoLetra));
            no->caracter = atual->caracter;
            no->codigo = &codigo;
            no->frequencia = atual->frequencia;

            lista = add(lista, no);
        }

        if(atual->dir != NULL)
        {
            codigo[tam] = "1";
            createCod(lista, atual->dir,codigo,tam + 1);
        }
    }
    return lista;
}

int altura(NoArvore* noAtual)
{
    int hEsq, hDir;

    if(noAtual == NULL)
        return 0;

    hEsq = altura(noAtual->esq);
    hDir = altura(noAtual->dir);

    if(hEsq >= hDir)
        return 1 + hEsq;

    return 1 + hDir;
}

