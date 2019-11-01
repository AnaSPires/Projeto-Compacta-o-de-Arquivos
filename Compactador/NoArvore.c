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

NoLetra* createCod(NoLetra* lista,NoArvore* atual, char *codigo, int tam, int altura) // ou cria static
{
    if(atual != NULL)
    {
        if(atual->esq != NULL)
        {
            codigo[tam] = '0';
            lista = createCod(lista, atual->esq, codigo,tam + 1, altura);
        }

        if(atual->esq == NULL && atual->dir == NULL)
        {
            NoLetra* no = createL();
            no->caracter = atual->caracter;
            no->codigo = (char*) malloc(sizeof(NoLetra) * altura);
            int i;
            for(i = 0; i < tam; i++)
                no->codigo[i] = codigo[i];
            no->tam = tam;
            no->frequencia = atual->frequencia;

            // na letra poe o tamnanho do codigo tipo 000 ent o tamanho vai ser 3 dica o tamanhno é a variavel tam

            lista = add(lista, no);
        }

        if(atual->dir != NULL)
        {
            codigo[tam] = '1';
            lista = createCod(lista, atual->dir,codigo,tam + 1,altura);
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

