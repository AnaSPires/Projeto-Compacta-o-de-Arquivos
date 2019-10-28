#include<stdio.h>
#include "NoArvore.h"
#include "Fila.h"
#include "Letra.h"

int tamanho;

int main()
{
   FILE *ponteiroArquivo;
   NoFila* f = NULL;
   char arq[30];

   printf("Opcao escolhida: ");

   scanf("%s", arq);

   ponteiroArquivo = fopen(arq, "r");

   if(ponteiroArquivo == NULL)
      printf("Erro na abertura do arquivo!");

   fseek(ponteiroArquivo, 0, SEEK_END);
   tamanho = ftell(ponteiroArquivo);

   int qtd = 0;
   rewind(ponteiroArquivo);

   char c = getc(ponteiroArquivo);
   while(c != EOF)
   {
      NoFila* atual = buscar(c, f);
      f=atual;
      c = getc(ponteiroArquivo);
   }

   char car;
   int fre;

   NoFila* teste = f;
   while(teste->prox !=NULL)
   {
        car = teste->info->caracter;
        fre = teste->info->frequencia;
        //printf("%c",car);
        // printf("%i", fre);
        // printf("\n");
        teste = teste->prox;
        qtd++;
   }
   car = teste->info->caracter;
   fre = teste->info->frequencia;
   // printf("%c",car);
   // printf("%i", fre);
   // printf("\n\n");
   qtd++;

   int qtdCaractere = qtd;

   while(qtd > 1)
   {
      NoArvore* primeiro = pop(&f);
      printf("%c",primeiro->caracter);
      printf("%i",primeiro->frequencia);

      NoArvore *segundo = pop(&f);
      //printf("%c",segundo->caracter);
      //printf("%i",segundo->frequencia);

        int frequencia = (primeiro->frequencia) + (segundo->frequencia);
        NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
        novo->info->frequencia = frequencia;
        novo->info->vazio = 1;

        //printf("%i", novo->info->frequencia);
        //printf("\n");

        NoFila*esq = (NoFila*) malloc(sizeof(NoFila));
        esq->info = primeiro;

        NoFila*dir = (NoFila*) malloc(sizeof(NoFila));
        dir->info = segundo;

        novo->info->esq = esq;
        novo->info->dir = dir;

        f = insira(f,novo);
    }
    //NoFila* filaLet = (NoFila*)malloc(sizeof(NoFila));
    //int cod;
    //while()

    NoArvore* auxArvore2 = create();
    NoArvore* auxArvore = create();
    char *cod = (char *) malloc(qtdCaractere);

    int pos = 0;
    int qtdCriados = 0;

    while(qtdCriados != qtdCaractere)
    {
        while(auxArvore->esq != NULL && auxArvore->dir != NULL)
        {
            auxArvore2 = auxArvore;
            auxArvore = auxArvore->esq;

            printf("%c", auxArvore->caracter);

            if(auxArvore->esq == NULL)
            {
                cod[pos++] = "0";
            }

            if(auxArvore->dir == NULL)
            {
                cod[pos++] = "1";
            }
        }

        Letra* letra = create();
        letra->caracter = auxArvore->caracter;
        letra->codigo = cod;

        criarTabela(auxArvore, qtd, letra);

        cod[qtd--] = NULL;
        auxArvore = auxArvore2->dir;

        qtdCriados++;
    }
  }

  void criarTabela(NoArvore* no, int topo, Letra* l)
  {


  }
