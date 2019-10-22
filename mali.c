#include<stdio.h>

int tamanho;

int main()
{
   FILE *ponteiroArquivo;
  char arq[30];

  printf("Opcao escolhida: ");

  scanf("%s", arq);

  ponteiroArquivo = fopen(arq, "r");

  if(ponteiroArquivo == NULL)
     printf("Erro na abertura do arquivo!");

  fseek(ponteiroArquivo, 0, SEEK_END);
  tamanho = ftell(ponteiroArquivo);
  printf("%s", "Tamanho: ");
  printf("%i", tamanho);

  char vetor[tamanho];

  rewind(ponteiroArquivo);

  char c = getc(ponteiroArquivo);
  int ind = 0;
  while(c != EOF)
  {
      printf("%c", c);
      vetor[ind] = c;
      ind++;
      c = getc(ponteiroArquivo);
  }
  char i = 0;
  char o = 0;


  while(i<ind)
  {
      int qtd = 1;
      while(o<ind)
      {
          if(vetor[i] == vetor[o])
          qtd++;

          o++;
      }
      //Fila *noArvore = new Fila();
      //noArvore::caracter = vetor[i];
      //noArvore::frequencia = qtd;
      //noArvore ::vazio = false;
      i++;
  }



  //int freq[tamanho];
  //int qtd = 0;
  //char c;
/*
  rewind(ponteiroArquivo);

  do
  {
       printf("\n\n");
       c = getc(ponteiroArquivo);
       printf("%c", c);
       vetor[qtd] = c;
       char achou = 'n';

       for(int i = 0; i < qtd && qtd  != 0; i++)
       {
            if(c == vetor[i])
            {
                freq[i] += 1;
                freq[qtd] = 0;
                achou = 's';
                printf("%s", "\n\nyep");
                i = qtd;
            }
            else
                 printf("%s", "\n\nnop\n");
       }

        if(qtd == 0)
            freq[0] = 1;
        else
            if(achou != 's')
                freq[qtd] = 1;

       qtd++;
  }while (c != EOF);

  criarNos(vetor, freq);

  printf("\n");
  printf("%c", vetor[0]);
  printf("%c", vetor[1]);
  printf("%c", vetor[2]);
  printf("%c", vetor[3]);
  printf("%c", vetor[4]);
  printf("%c", vetor[5]);
  printf("\n");
  printf("%i", freq[0]);
  printf("%i", freq[1]);
  printf("%i", freq[2]);
  printf("%i", freq[3]);
  printf("%i", freq[4]);
  printf("%i", freq[5]);

  fclose(ponteiroArquivo);


  return 0;
}

void criarNos(char vet[tamanho], int f[tamanho])
{
*/
/*typedef struct HuffNode
{
  char myChar;
  int myFrequency,
  struct HuffNode *myLeft, *myRight;
}HuffNode;

priorityQueue myQueue;*/

}
