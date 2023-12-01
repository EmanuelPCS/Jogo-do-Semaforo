/*------------//------------//------------*/
//   Trabalho Prático Programação - LEI   //
//          DEIS-ISEC 2020-2021           //
//          Emanuel Saraiva               //
//          a2019130219@isec.pt           //
/*------------//------------//------------*/


// NOTA: Este ficheiro (utilsFile.c) é o ficheiro que tem todas as funções relativas
//       Às operações do ficheiro Jogo.bin


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include "utils.h"
#include "utilsFile.h"
#include "jogadorAutomatico.h"
#include "jogada.h"
#include <limits.h>
//guardar linha, coluna, lista toda
void guardaDadosFileBin(Jogada ** lista, int N, int *pl, int *pc, char **t, char *jogador, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB){
    FILE *f;
    pJogada aux = *lista;

    if(lista == NULL){
		printf("\nLista vazia\n\n");
		return;
	}

    int linhaGua,colunaGua;
    linhaGua = *pl;
    colunaGua = *pc;

    int contLJA = *contLinhaJogadorA;
    int contLJB = *contLinhaJogadorB;
    int contPJA = *contPedraJogadorA;
    int contPJB = *contPedraJogadorB;
    int contCJA = *contColunaJogadorA;
    int contCJB = *contColunaJogadorB;

    f = fopen("jogo.bin","wb");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }

    fwrite(jogador, sizeof(char), 1, f);

    fwrite(&N, sizeof(int), 1, f);

    fwrite(&contLJA, sizeof(contLJA), 1, f); //testar com int no sizeof
    fwrite(&contLJB, sizeof(contLJB), 1, f);
    fwrite(&contPJA, sizeof(contPJA), 1, f);
    fwrite(&contPJB, sizeof(contPJB), 1, f);
    fwrite(&contCJA, sizeof(contCJA), 1, f);
    fwrite(&contCJB, sizeof(contCJB), 1, f);

    fwrite(&linhaGua, sizeof(linhaGua), 1, f);
    fwrite(&colunaGua, sizeof(colunaGua), 1, f);
/*
    for(int i = 0; i < *pl; i++){
        for(int j = 0; j < *pc; j++){
            fwrite(&t[i][j], sizeof(char), 1, f);
        }
    }
*/
/*printf("N:%d",N);
return;*/
    while(aux != NULL){
		fwrite(aux, sizeof(Jogada), 1, f);
        aux = aux->prox;
    }

    printf("\nJogo salvado com sucesso\n\n");
    fclose(f);
}

char ** leDadosFileBin(Jogada ** lista, char *jogador, int *N, int *pl, int *pc, char **t, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB){
    FILE *f;

    Jogada* novo = NULL;
    Jogada* ultimo = NULL;
    Jogada aux;

    char jogadorr;
    int n;
    //char *pjogador = &jogador;
    int linha, coluna;
    int flagLinha = 0;
    int flagColuna = 0;

    int contLJA;
    int contLJB;
    int contPJA;
    int contPJB;
    int contCJA;
    int contCJB;

    //char ** t = NULL;
    f = fopen("jogo.bin","rb");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }

    //libertaLista(lista);

    fread(&jogadorr, sizeof(char), 1, f);
    *jogador = jogadorr;

    fread(&n, sizeof(int), 1, f);
    *N = n;

    fread(&contLJA, sizeof(contLJA), 1, f);
    *contLinhaJogadorA = contLJA;
    fread(&contLJB, sizeof(contLJB), 1, f);
    *contLinhaJogadorB = contLJB;
    fread(&contPJA, sizeof(contPJA), 1, f);
    *contPedraJogadorA = contPJA;
    fread(&contPJB, sizeof(contPJB), 1, f);
    *contPedraJogadorB = contPJB;
    fread(&contCJA, sizeof(contCJA), 1, f);
    *contColunaJogadorA = contCJA;
    fread(&contCJB, sizeof(contCJB), 1, f);
    *contColunaJogadorB = contCJB;

    //printf("%c\n",jogador);
    fread(&linha, sizeof(linha), 1, f);
    if(linha != *pl){
        flagLinha = 1;
        *pl = linha;
    }

    //printf("%d", *pl);return;
    fread(&coluna, sizeof(coluna), 1, f);
    if(coluna != *pc){
        flagColuna = 1;
        *pc = coluna;
    }


    t = (char **)malloc(sizeof(char *) * (*pl));
    if(t == NULL){
       printf("Erro na Alocação de Memória");
       return NULL;
    }

    for(int i = 0; i<(*pl);i++){
        t[i] = malloc(sizeof(char) * (*pc));
        if(t[i] == NULL){
           printf("Erro na Alocação de Memória");
           free(t[i]);
           free(t);
           return NULL;
        }
    }

inicializa_tab(pl, pc, t);
    while( fread(&aux, sizeof(Jogada), 1, f) == 1 ){
		/// garantir boa inicializacao do ponteiro prox
        aux.prox = NULL;

			/// alocar memoria para novo no
            novo = malloc(sizeof(Jogada));

            if(novo == NULL){
                printf("\nErro ao tentar alocar memoria\n\n");
                fclose(f);
                libertaLista(lista);
                return;
            }
            else
            {
                t = retomaJogo(&aux, flagLinha, flagColuna, N, pl, pc, t, contLinhaJogadorA, contLinhaJogadorB, contPedraJogadorA, contPedraJogadorB, contColunaJogadorA, contColunaJogadorB);

                /// cópia do conteúdo do nó para a estrutura apontada por novo
                (*novo) = aux;

                if(*lista == NULL){
                    *lista = novo;
                    ///ultimo = novo;

                }
                else
                {
                    ///ultimo->prox = novo;
                    ///ultimo = novo;


                    ultimo = *lista;
                    while(ultimo->prox != NULL)
                        ultimo = ultimo->prox;

                    ultimo->prox = novo;

                }
            }

    }

    printf("\nFicheiro e lista lida com sucesso\n\n");
    fclose(f);
    return t;
}


/*
char leDadosFileBin(int *pl, int *pc, char **tab, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB){
    FILE *f;
    char jogador;
    //char *pjogador = &jogador;
    int linha, coluna;
    int flagLinha = 0;
    int flagColuna = 0;

    int contLJA;
    int contLJB;
    int contPJA;
    int contPJB;
    int contCJA;
    int contCJB;

    char ** t = NULL;
    f = fopen("jogo.bin","rb");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }

    fread(&jogador, sizeof(char), 1, f);

    fread(&contLJA, sizeof(contLJA), 1, f);
    *contLinhaJogadorA = contLJA;
    fread(&contLJB, sizeof(contLJB), 1, f);
    *contLinhaJogadorB = contLJB;
    fread(&contPJA, sizeof(contPJA), 1, f);
    *contPedraJogadorA = contPJA;
    fread(&contPJB, sizeof(contPJB), 1, f);
    *contPedraJogadorB = contPJB;
    fread(&contCJA, sizeof(contCJA), 1, f);
    *contColunaJogadorA = contCJA;
    fread(&contCJB, sizeof(contCJB), 1, f);
    *contColunaJogadorB = contCJB;

    //printf("%c\n",jogador);
    fread(&linha, sizeof(linha), 1, f);
    if(linha != *pl){
        flagLinha = 1;
        *pl = linha;
    }

    //printf("%d", *pl);return;
    fread(&coluna, sizeof(coluna), 1, f);
    if(coluna != *pc){
        flagColuna = 1;
        *pc = coluna;
    }
//confirmar os frees da realocaçao com o prof e confirmar o Pq do jogo.bin nao detectar a extensao .bin
    if(flagLinha == 1){ //quer dizer que ou o n de linhas foi alterado, logo é preciso fazer o realloc da tab
        char ** aux = NULL;
        aux = (char **)malloc(sizeof(char *) * (*pl));
        if(aux == NULL){
            printf("Erro na Alocação de Memória");
            for(int k = 0; k < *pl; k++)
                free(aux[k]);
            free(aux);
            return 0; // estava return NULL;
        }else{


            aux[*pl - 1] = malloc(sizeof(char) * (*pc));
            if(aux[*pl - 1] == NULL){
                printf("Erro na Alocação de Memória");
                for(int z = 0; z < *pc; z++)
                    free(aux[z]);
                free(aux);
                return 0;
            }/// testar erro ao alocar

            for(int i = 0; i < *pl; i++){
                for(int j = 0; j < *pc; j++){
                    fread(&t, sizeof(char), 1, f);
                    aux = t;
                  //  tab[i][j] = t;
                }//putchar('\n');
            }
            tab = aux;
        }

        //adicionaLinhaLe(pl,pc,tab);
    }
    else if(flagColuna == 1){
        //Eu notei que ter este código do realloc ou não ter vai dar ao mesmo. Isto funciona apenas com aquele for
        char ** auxc = NULL;
        //(*pc)++;

        for(int i=0; i<(*pl); i++){
            auxc=(char **)realloc(tab[i], sizeof(char *) * (*pc));
            if(auxc == NULL){
                printf("Erro na alocação de memória");
                for(int i = 0; i < (*pl); i++)
                    free(tab[i]);
                free(tab);
                return 0;
            }
            tab[i]=auxc;
        }

        for(int i = 0; i < *pl; i++){
            for(int j = 0; j < *pc; j++){
                fread(&t, sizeof(char), 1, f);
                tab[i][j] = t;//fazer malloc
                //printf(" %c ", tab[i][j]);
            }//putchar('\n');
        }
       // adicionaColuna(pl,pc,tab);
    }
    else{
        for(int i = 0; i < *pl; i++){
            for(int j = 0; j < *pc; j++){
                fread(&t, sizeof(char), 1, f);
                tab[i][j] = t;//fazer malloc
                //printf(" %c ", tab[i][j]);
            }//putchar('\n');
        }
    }


    fclose(f);
    return jogador;
}
*/
void resetFileBin(){
    FILE *f, *temp;

    f = fopen("jogo.bin","rb");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }

    temp = fopen("temp.bin","wb");
    if(temp == NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }
    fclose(f);
    fclose(temp);
    remove("jogo.bin");
    rename("temp.bin","jogo.bin");
}

/*void escreveDadosFileBin(int *pl, int *pc, char **t, char *jogador){

    printf("\n\nÉ a vez doasdfsdf jogador %c\n", *jogador);
    escreve_tab(pl,pc,t);
}*/
