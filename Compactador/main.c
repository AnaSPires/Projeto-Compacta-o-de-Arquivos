#include<stdio.h>
#include "NoArvore.h"
#include "Fila.h"
#include "Letra.h"

int tamanho;

int main()
{
   FILE *ponteiroArquivo;
   NoFila* f = NULL;
  char *arq = (char*)malloc(sizeof(char));

  printf("Opcao escolhida: ");

  scanf("%s", arq);

  ponteiroArquivo = fopen(arq, "r");
  //printf("%s",arq);

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
    }

        int a = altura(f->info);
        printf("%i",a);

        NoLetra* filaL =NULL;

        char *auxCod = (char*)malloc(a * sizeof(char));
        int i;
        for(i = 0; i < a; i++)
            auxCod[i] = NULL;

        int auxTam = 0;

        filaL = createCod(filaL, f->info, auxCod, auxTam, a);
        NoLetra* testeL = filaL;

        while(testeL->prox !=NULL)
        {
            printf("%c\n", testeL->caracter);
            printf("%i\n", testeL->frequencia);
            testeL = testeL->prox;
            int p;
            for(p = 0; p<testeL->tam;p++)
            {
                printf("%c", testeL->codigo[p]);
                printf("-");
            }
            printf("\n\n");
        }
        printf("%c", testeL->caracter);
        printf("\n");
        printf("%i", testeL->frequencia);
        printf("\n");

        int p;
        for(p = 0; p<testeL->tam;p++)
        {
            printf("%c", testeL->codigo[p]);
            printf("-");
        }

        //arq = arq + ".compactado";
        //FILE *arqCompactado = fopen(arq, "r");


        char * found = strstr( arq, "in" );
        char* arqCompactado;
        if (found != NULL)
        {
          int index = found - arq;
          for(int i = 0;i<index;i++)
          {
            *arqCompactado = *arq;
            arq++;
            arqCompactado++;
          }


        FILE *pontCompactado = freopen(arq, "w", arqCompactado);

        fprintf(pontCompactado,"%s", "aaaaaaaaaaaaaa"); //filaL->caracter
        /*
        while(letra != EOF)
        {
            fprintf(arqCodificado, "aaaaaaaaaaaaaa"); //filaL->caracter
            printf("humf");
            filaL = filaL->prox;
            letra = getc(ponteiroArquivo);
            printf("yyyyy");
        }
        printf("aaaa");*/
        }

}

