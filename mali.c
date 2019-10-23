#include<stdio.h>
#include "NoArvore.h"
#include "Fila.h"

int tamanho;

int main()
{
      FILE *ponteiroArquivo;
      NoFila* f = NULL;
      char arq[30];
      int qtd = 0;

      printf("Opcao escolhida: ");

      scanf("%s", arq);

      ponteiroArquivo = fopen(arq, "r");

      if(ponteiroArquivo == NULL)
         printf("Erro na abertura do arquivo!");

      fseek(ponteiroArquivo, 0, SEEK_END);
      tamanho = ftell(ponteiroArquivo);
      printf("%s", "Tamanho: ");
      printf("%i", tamanho);

      rewind(ponteiroArquivo);

      char c = getc(ponteiroArquivo);
      while(c != EOF)
      {
            printf("\n");
            printf("%c",c);
            printf("\n");
            f = buscar(c,f);
            c = getc(ponteiroArquivo);
      }
      char car;
      int fre;

      NoFila* teste = f;
      while(teste->prox !=NULL)
      {
          qtd++;
          car = teste->info->caracter;
          fre = teste->info->frequencia;

          printf("\n");
          printf("%c",car);
          printf("\n");
          printf("%i", fre);

          teste = teste->prox;
      }
      qtd++;
      car = teste->info->caracter;
      fre = teste->info->frequencia;

      printf("%c",car);
      printf("\n");
      printf("%i", fre);
      printf("\n");


      /*while(qtd>1)
      {
            NoArvore* primeiro = pop(&f);
            if(primeiro->vazio == 0)
            {
            printf("\n");
            printf("%c",primeiro->caracter);
            }
            printf("\n");
            printf("%i",primeiro->frequencia);

            NoArvore* segundo = pop(&f);
            if(segundo->vazio == 0)
            {
            printf("\n");
            printf("%c",segundo->caracter);
            }

            printf("\n");
            printf("%i",segundo->frequencia);

            NoArvore* novo = create();
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->vazio = 1;

            insira(f,novo);
      }*/

  }
