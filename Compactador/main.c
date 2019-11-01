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
      //printf("%i", fre);
      //printf("\n");
      teste = teste->prox;
      qtd++;
  }
      car = teste->info->caracter;
      fre = teste->info->frequencia;
      //printf("%c",car);
      //printf("%i", fre);
      //printf("\n\n");
      qtd++;

    int qtdCaractere = qtd;
    while(qtdCaractere > 1 && f != NULL)
    {
        NoArvore* primeiro = pop(&f);
        //printf("\n\n");
        //printf("%c",primeiro->caracter);
        //printf("%i",primeiro->frequencia);

        //printf("\n\n");

        NoArvore *segundo = pop(&f);
        //printf("%c",segundo->caracter);
        //printf("%i",segundo->frequencia);
        //printf("\n\n");

        int frequencia = (primeiro->frequencia) + (segundo->frequencia);
        NoArvore * novo = (NoFila*)malloc(sizeof(NoFila));
        novo = create();
        novo->frequencia = frequencia;

        novo->esq = primeiro;
        novo->dir = segundo;

        f = insira(f,novo);

        qtdCaractere--;

       // printf("%i", qtdCaractere);
       // printf("\n\n");
    }
    //printf("%i", f->info->frequencia);

    int a = altura(f->info);
    printf("%i",a);

    NoLetra* filaL = (NoLetra*)malloc(sizeof(NoLetra));

    filaL = createCod(filaL, f->info);
    printf("bbbbbbbbbb");
    NoLetra* testeL = filaL;
    while(testeL->prox !=NULL)
    {
      printf("%c", filaL->caracter);
      printf("%i", filaL->frequencia);
      printf("\n");
      testeL = testeL->prox;
    }
       printf("%c", filaL->caracter);
      printf("%i", filaL->frequencia);
      printf("\n\n");
    }
