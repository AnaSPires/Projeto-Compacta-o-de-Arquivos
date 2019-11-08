#include<stdio.h>
#include "NoArvore.h"
#include "Fila.h"
#include "Letra.h"
#include <locale.h>
#include <string.h>

int tamanho;

int main()
{
   FILE *ponteiroArquivo;
   NoFila* f = NULL;
  char arq[30];
  int escolha;

  printf("1 - Compactar um arquivo \n\n");
  printf("2 - Descompactar um arquivo \n\n");
  printf("Opção escolhida: ", setlocale(LC_ALL,""));
  scanf("%i", &escolha);
  printf("\n");

  switch(escolha)
  {
    case 1:

        //compactar
        printf("Digite o nome do arquivo a ser compactado: ");
        scanf("%s", arq);
        printf("\n");

        ponteiroArquivo = fopen(arq, "rb");
        if(ponteiroArquivo == NULL)
            printf("Erro na abertura do arquivo!");
        else
            compactar(ponteiroArquivo, arq);
            break;

        case 2:
            printf("Digite o nome do arquivo a ser descompactado: ");
            scanf("%s", arq);
            printf("\n\n");
            ponteiroArquivo = fopen(arq, "rb");
            if(ponteiroArquivo == NULL)
             printf("Erro na abertura do arquivo!");
            else
                descompactar(ponteiroArquivo,arq);


            break;

      }
}
void descompactar(FILE* ponteiroArquivo, char arq[])
{
    NoFila* f = NULL;
    rewind(ponteiroArquivo);
    int lixo;
    fread(&lixo,sizeof(int),1,ponteiroArquivo);
    int qtdLetras;
    fread(&qtdLetras,sizeof(int),1,ponteiroArquivo);

    for(int i = 0; i< qtdLetras;i++)
    {
        unsigned char car;
        fread(&car,sizeof(char),1,ponteiroArquivo);
        int fre;
        fread(&fre,sizeof(int),1,ponteiroArquivo);
        NoArvore* nozinho = create();
        nozinho->caracter = car;
        nozinho->frequencia = fre;
        f = insira(f, nozinho);
    }

    NoFila* teste = f;

    int qtd = qtdLetras;
    while(qtd > 1 && f != NULL)
    {
        NoArvore* primeiro = pop(&f);
        NoArvore *segundo = pop(&f);
        int frequencia = (primeiro->frequencia) + (segundo->frequencia);
        NoArvore * novo = create();
        novo->frequencia = frequencia;

        novo->esq = primeiro;
        novo->dir = segundo;
        f = insira(f,novo);
        qtd--;
    }

    NoArvore *a = f->info;

    char novoArq[30];
    int i;
    for(i = 0; i<(strlen(arq)-4);i++)
        novoArq[i] = arq[i];


    FILE* pontDescompactar = fopen(novoArq, "wb");

    unsigned char codigo;
    NoArvore *atual = f->info;
    int max = 8;
    long posAtual;

     posAtual= ftell(ponteiroArquivo);

    fseek(ponteiroArquivo, 0, SEEK_END);
    long posFinal = ftell(ponteiroArquivo);

    fseek(ponteiroArquivo, posAtual, SEEK_SET);

    int acabou = 0;

    while(fread(&codigo, sizeof(char), 1, ponteiroArquivo) && !acabou)
    {
        posAtual= ftell(ponteiroArquivo);
        if(posAtual == posFinal){
            max = max - lixo;
            acabou = 1;
        }

        for(int i = 0; i < max; i++)
        {
            if(codigo & (1u << (7 - i)))    //0101 1000
                atual = atual->dir;
            else
                atual = atual->esq;

            if((atual->dir == NULL) && (atual->esq == NULL))
            {
                fwrite(&(atual->caracter), sizeof(char), 1, pontDescompactar);//escreve o caracter
                atual= f->info;
            }
        }
    }
    fclose(pontDescompactar);
    fclose(ponteiroArquivo);
    printf("\n\n");
    printf("Descompactação realizada com sucesso!!!", setlocale(LC_ALL,""));
    printf("\n\n");
}


void percorrer(NoArvore *atual)
{
    if(atual != NULL)
    {
        percorrer(atual->esq);

        if(atual->esq == NULL && atual->dir == NULL)
            printf("%c", atual->caracter);
        percorrer(atual->dir);

    }

}
void compactar(FILE* ponteiroArquivo, char arq[])
{
    NoFila* f = NULL;
    int qtd = 0;
    unsigned char c;

    /*fseek(ponteiroArquivo, 0, SEEK_END);
    tamanho = ftell(ponteiroArquivo);
    fseek(ponteiroArquivo, 0, SEEK_SET);*/

    while(fread(&c,sizeof(unsigned char),1,ponteiroArquivo))
        f = buscar(c, f);

    NoFila* teste = f;
    while(teste !=NULL)
    {
        teste = teste->prox;
        qtd++;

    }

    int tam = strlen(arq);

    char arqCodificado[tam+5];
    int x = 0;

    for(x = 0;x<(tam);x++)
        arqCodificado[x] = arq[x];
    strcat(arqCodificado, ".cmp");

    FILE *pontCodificado = fopen(arqCodificado, "wb");

    tam = 0;
    fwrite(&tam, sizeof(int), 1, pontCodificado);
    fwrite(&qtd, sizeof(int), 1, pontCodificado);

    while(qtd > 1 && f != NULL)
    {
        NoArvore* primeiro = pop(&f);
        NoArvore *segundo = pop(&f);

        int frequencia = (primeiro->frequencia) + (segundo->frequencia);
        NoArvore * novo = (NoFila*)malloc(sizeof(NoFila));
        novo = create();
        novo->frequencia = frequencia;

        novo->esq = primeiro;
        novo->dir = segundo;

        char c1 = primeiro->caracter;
        int f1 = primeiro->frequencia;

        char c2 = segundo->caracter;
        int f2 = segundo->frequencia;

        if(primeiro->esq == NULL && primeiro->dir == NULL){
            fwrite(&c1, sizeof(char), 1, pontCodificado);
            fwrite(&f1, sizeof(int), 1, pontCodificado);
        }

        if(segundo->esq == NULL && segundo->dir == NULL)
        {
            fwrite(&c2, sizeof(char), 1, pontCodificado);
            fwrite(&f2, sizeof(int), 1, pontCodificado);
        }

        f = insira(f,novo);

        qtd--;
    }
    //a25r12m10

    NoArvore *a = f->info;
    percorrer(a);

    int alturaArvore = altura(f->info);
    NoLetra* filaL = NULL;

    char *auxCod = (char*)malloc(alturaArvore * sizeof(char));
   //for(int i = 0; i < alturaArvore; i++)
    //    auxCod[i] = NULL;

    int auxTam = 0;

    filaL = createCod(filaL, f->info, auxCod, auxTam, alturaArvore);

    /*
    rewind(ponteiroArquivo);

    NoFila* copiaRuim = filaL;

    while(filaL != NULL)
    {
        fwrite(&filaL->caracter, sizeof(char), 1, pontCodificado);
        fwrite(&filaL->frequencia, sizeof(int), 1, pontCodificado);
        filaL = filaL->prox;
    }*/
    rewind(ponteiroArquivo);

    int qtdQuantos = 0;

    unsigned char letra;

    NoLetra* encontrada;

    unsigned char aux=0;

    while(fread(&letra,sizeof(char),1,ponteiroArquivo))
    {
        encontrada = acharLetra(letra, filaL);
        unsigned char codigo = 0;
        int outroInt = encontrada->tam - 1;
        int indice = 0;
        int max = encontrada->tam;

        for(indice = 0;indice < encontrada->tam; indice++, outroInt--)
            if(encontrada->codigo[indice] == '1')
                codigo += pow(2, outroInt);


        if(qtdQuantos + encontrada->tam > 8)
        {
            int coisa = encontrada->tam - (8 - qtdQuantos);//0
            unsigned char restoAtual = codigo >> coisa;  //  00000000
            aux = aux << (8 - qtdQuantos);  //01101101
            aux = aux | restoAtual;
            fwrite(&aux, sizeof(char), 1, pontCodificado);
            unsigned char faltaIncluir = codigo << (8 - coisa);

            while(coisa>8)
            {
                coisa = coisa - 8;
                restoAtual = faltaIncluir >> coisa;
                aux = restoAtual;
                fwrite(&aux, sizeof(char), 1, pontCodificado);
                faltaIncluir = faltaIncluir << (coisa);
            }

            aux = faltaIncluir;
            qtdQuantos = coisa;
        }
        else
        {
            aux = aux << encontrada->tam;
            aux = aux | codigo;
            qtdQuantos += encontrada->tam;

            if(qtdQuantos == 8)
            {
                qtdQuantos = 0;
                fwrite(&aux, sizeof(char), 1, pontCodificado);
                aux = 0;
            }
        }
        fread(&letra,sizeof(char),1,ponteiroArquivo);
    }

    if(qtdQuantos != 0)
    {
        int quantosLixos = 8 - qtdQuantos;
        fwrite(&aux, sizeof(char), 1,pontCodificado);
        rewind(pontCodificado);

        fwrite(&quantosLixos, sizeof(int), 1, pontCodificado);
    }

    fclose(pontCodificado);
    fclose(ponteiroArquivo);
    printf("\n\n");
    printf("Compactação realizada com sucesso!!!",setlocale(LC_ALL,""));
    printf("\n\n");
}

