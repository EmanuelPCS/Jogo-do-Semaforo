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


void criaLista(Jogada ** lista, int opcao, int *pl, int *pc, char **t){
    Jogada aux;
    Jogada* novo = NULL;
    Jogada* lista_aux = NULL;
    // nao é necessario mandar a lista na funcao
    if(obtemJogada(*lista, &aux, opcao, pl, pc, t) == 0){ //obtemJogada Tem de fazer as verificaçoes todas - ta feito
        printf("Não foi possivel realizar essa jogada\n\n");
        return;
    }

    if((novo = malloc(sizeof(Jogada))) == NULL){
        printf("\nOcorreu um erro a alocar memória dinâmica\n\n");
        return;
    }

    *novo = aux;

    // ele so mete o no na lista caso a jogada seja válida! - ta feito
    // tens de ter certeza se a jogada é valida para poder por para a lista
    /// também já é preenchido correctamente na função obtemPessoa()
    novo->prox = NULL;

    //printf("\nPessoa adicionada com sucesso\n\n");

    if(*lista == NULL){
        *lista = novo;
    }
    else
    {
        lista_aux = *lista;
        while(lista_aux->prox != NULL)
            lista_aux = lista_aux->prox;

        lista_aux->prox = novo;
       // return lista;
    }

}

int obtemJogada(pJogada lista, pJogada p, int opcao, int *pl, int *pc, char **t){
//    int r = 0;
    p->prox = NULL;
    int resfj = 1;

    if(opcao == 1){ // OPCAO 1 - O Utilizador quer pôr a peça VERDE

        do{
            do{
                printf("Introduza a linha [1,%d]: ", *pl);
                scanf("%d", &(p->x));
                //printf("%d",(p->x));
                if((p->x) < 1 || (p->x) > (*pl)){
                    printf("Por favor introduza uma linha entre [1, %d].\n\n", *pl);
                }
            }while((p->x) < 1 || (p->x) > (*pl));

            do{
                printf("Introduza a coluna [1,%d]: ", *pc);
                scanf("%d", &(p->y));

                if((p->y) < 1 || (p->y) > (*pc)){
                    printf("Por favor introduza uma coluna entre [1, %d].\n\n", *pc);
                }
            }while((p->y) < 1 || (p->y) > (*pc));

            if(t[(p->x)-1][(p->y)-1] != '_'){
                printf("Por favor coloque uma Peça Verde numa Célula Vazia.\n\n");
            }

        }while(((p->x) < 1 || (p->x) > (*pl)) || ((p->y) < 1 || (p->y) > (*pc)) || (t[(p->x)-1][(p->y)-1] != '_'));

        p->cor = 'G';
        p->pedra = 0;
        p->linha = 0;
        p->coluna = 0;

        t[(p->x)-1][(p->y)-1] = p->cor;
    }

    if(opcao == 2){ // OPCAO 2 - O Utilizador quer pôr a peça AMARELA

        do{
            do{
                printf("Introduza a linha [1,%d]: ", *pl);
                scanf("%d", &(p->x));
                //printf("%d",(p->x));
                if((p->x) < 1 || (p->x) > (*pl)){
                    printf("Por favor introduza uma linha entre [1, %d].\n\n", *pl);
                }
            }while((p->x) < 1 || (p->x) > (*pl));

            do{
                printf("Introduza a coluna [1,%d]: ", *pc);
                scanf("%d", &(p->y));

                if((p->y) < 1 || (p->y) > (*pc)){
                    printf("Por favor introduza uma coluna entre [1, %d].\n\n", *pc);
                }
            }while((p->y) < 1 || (p->y) > (*pc));

            if(t[(p->x)-1][(p->y)-1] != 'G'){
                printf("Por favor introduza uma peça Amarela no lugar de uma Verde.\n\n");
            }

        }while(((p->x) < 1 || (p->x) > (*pl)) || ((p->y) < 1 || (p->y) > (*pc)) || (t[(p->x)-1][(p->y)-1] != 'G'));

        p->cor = 'Y';
        p->pedra = 0;
        p->linha = 0;
        p->coluna = 0;

        t[(p->x)-1][(p->y)-1] = p->cor;
    }

    if(opcao == 3){ // OPCAO 3 - O Utilizador quer pôr a peça VERMELHA

        do{
            do{
                printf("Introduza a linha [1,%d]: ", *pl);
                scanf("%d", &(p->x));
                //printf("%d",(p->x));
                if((p->x) < 1 || (p->x) > (*pl)){
                    printf("Por favor introduza uma linha entre [1, %d].\n\n", *pl);
                }
            }while((p->x) < 1 || (p->x) > (*pl));

            do{
                printf("Introduza a coluna [1,%d]: ", *pc);
                scanf("%d", &(p->y));

                if((p->y) < 1 || (p->y) > (*pc)){
                    printf("Por favor introduza uma coluna entre [1, %d].\n\n", *pc);
                }
            }while((p->y) < 1 || (p->y) > (*pc));

            if(t[(p->x)-1][(p->y)-1] != 'Y'){
                printf("Por favor introduza uma peça Vermelha no lugar de uma Amarela.\n\n");
            }

        }while(((p->x) < 1 || (p->x) > (*pl)) || ((p->y) < 1 || (p->y) > (*pc)) || (t[(p->x)-1][(p->y)-1] != 'Y'));

        p->cor = 'R';
        p->pedra = 0;
        p->linha = 0;
        p->coluna = 0;

        t[(p->x)-1][(p->y)-1] = p->cor;
    }

    if(opcao == 4){ // OPCAO 4 - O Utilizador quer pôr a peça PEDRA

        do{
            do{
                printf("Introduza a linha [1,%d]: ", *pl);
                scanf("%d", &(p->x));
                //printf("%d",(p->x));
                if((p->x) < 1 || (p->x) > (*pl)){
                    printf("Por favor introduza uma linha entre [1, %d].\n\n", *pl);
                }
            }while((p->x) < 1 || (p->x) > (*pl));

            do{
                printf("Introduza a coluna [1,%d]: ", *pc);
                scanf("%d", &(p->y));

                if((p->y) < 1 || (p->y) > (*pc)){
                    printf("Por favor introduza uma coluna entre [1, %d].\n\n", *pc);
                }
            }while((p->y) < 1 || (p->y) > (*pc));

            if(t[(p->x)-1][(p->y)-1] != '_'){
                printf("Por favor coloque uma Pedra numa Célula Vazia.\n\n");
            }

        }while(((p->x) < 1 || (p->x) > (*pl)) || ((p->y) < 1 || (p->y) > (*pc)) || (t[(p->x)-1][(p->y)-1] != '_'));

        p->cor = 'P';
        p->pedra = 1;
        p->linha = 0;
        p->coluna = 0;

        t[(p->x)-1][(p->y)-1] = p->cor;
    }

    if(opcao == 5){ // OPCAO 5 - O Utilizador quer adicionar uma linha

        *t = adicionaLinha(pl, pc, *t, &resfj);

        if(resfj == 0)
            return 0;

        p->x = 0;
        p->y = 0;
        p->cor = ' ';
        p->pedra = 0;
        p->linha = 1;
        p->coluna = 0;


    }

    if(opcao == 6){ // OPCAO 6 - O Utilizador quer adicionar uma coluna

        *t = adicionaColuna(pl, pc, *t, &resfj);

        if(resfj == 0)
            return 0;

        p->x = 0;
        p->y = 0;
        p->cor = ' ';
        p->pedra = 0;
        p->linha = 0;
        p->coluna = 1;

    }
    return 1;
}

void listaJogadas(Jogada * lista){
    pJogada aux = lista;
    int count = 0;

   /* if(lista == NULL){
        printf("A lista está a NULL\n\n");
        return 0;
    }*/


    while(aux != NULL){

        if(count == 0)
            printf("\nLista de jogadas:\n\n");

        printf(" Jogada %d:\n\n", ++count);
        printJogada(aux);

        aux = aux->prox;
    }

    if(count > 0)
        printf("Total de jogadas: %d\n\n", count);
    else
        printf("\nSem jogadas para listar\n\n");
}

void printJogada(pJogada aux){
    if(aux != NULL){
        printf("   X: %d\n", aux->x);
        printf("   Y: %d\n", aux->y);
        printf("   Cor: %c\n", aux->cor);
        printf("   Pedra: %d\n", aux->pedra);
        printf("   Linha: %d\n", aux->linha);
        printf("   Coluna: %d\n", aux->coluna);
    }

}

void libertaLista(pJogada * lista){
    pJogada aux = *lista;

    if(*lista == NULL){
        //printf("\nSem jogadas para eliminar\n\n");
        return;
    }

    while(aux != NULL){
        aux = aux->prox;
        free(*lista);
        *lista = aux;
    }

    //printf("\nTodas as jogadas foram eliminadas com sucesso\n\n");
}

char ** retomaJogo(Jogada *p, int flaglinha, int flagcoluna, int *N, int *pl, int *pc, char **t, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB){
/*
    if(p != NULL){
            printf("   X: %d\n", p->x);
            printf("   Y: %d\n", p->y);
            printf("   Cor: %c\n", p->cor);
            printf("   Pedra: %d\n", p->pedra);
            printf("   Linha: %d\n", p->linha);
            printf("   Coluna: %d\n", p->coluna);
        }*/

    if(p->cor == 'G'){
        t[(p->x)-1][(p->y)-1] = p->cor;
    }
    if(p->cor == 'Y'){
        t[(p->x)-1][(p->y)-1] = p->cor;
    }
    if(p->cor == 'R'){
        t[(p->x)-1][(p->y)-1] = p->cor;
    }
    if(p->pedra == 1){
        t[(p->x)-1][(p->y)-1] = p->cor;
    }
    /*if(p->linha == 1 && flaglinha == 1){
        t = adicionaLinha(N, N, t);
    }
    if(p->coluna == 1 && flagcoluna == 1){
        t = adicionaColuna(pl, pc, t);
    }*/
    return t;
}

void gravarLista(char *nomefile, pJogada lista, char jogador, int njogadas, char ganhou, int lG, int lY, int lR, int cG, int cY, int cR, int dG, int dY, int dR){
    FILE *f = NULL;
    pJogada aux = lista;

	if(lista == NULL){
		printf("\nA Lista está vazia\n\n");
		return;
	}

    if((f = fopen(nomefile, "wt")) == NULL){
        printf("\nErro ao abrir o ficheiro \"%s\" para escrita\n\n", nomefile);
        return;
    }
    int cont = 0;
    //printf("jogador: %c", jogador);
    while(aux != NULL){

        if(jogador == 'B' && cont == 0){
            jogador = 'A';
            cont = 1;
        }

		fprintf(f, " Jogador %c \n X: %d , Y: %d , Cor: %c , Pedra: %d , Linha: %d, Coluna: %d\n\n",jogador, aux->x, aux->y, aux->cor, aux->pedra, aux->linha, aux->coluna);

        aux = aux->prox;

        if(jogador == 'A'){
            jogador = 'B';
            cont = 1;
        }
        else
            jogador = 'A';
    }
    if(lG == 1)
        fprintf(f," Ganhou o jogador %c por linha.\n", ganhou);
    else if(lY == 1)
        fprintf(f," Ganhou o jogador %c por coluna.\n", ganhou);
    else if(lR == 1)
        fprintf(f," Ganhou o jogador %c por coluna.\n", ganhou);
    else if(cG == 1)
        fprintf(f," Ganhou o jogador %c por coluna.\n", ganhou);
    else if(cY == 1)
        fprintf(f," Ganhou o jogador %c por coluna.\n", ganhou);
    else if(cR == 1)
        fprintf(f," Ganhou o jogador %c por coluna.\n", ganhou);
    else if(dG == 1)
        fprintf(f," Ganhou o jogador %c por diagonal.\n", ganhou);
    else if(dY == 1)
        fprintf(f," Ganhou o jogador %c por diagonal.\n", ganhou);
    else if(dR == 1)
        fprintf(f," Ganhou o jogador %c por diagonal.\n", ganhou);

    fprintf(f," Número total de Jogadas realizadas: %d.", njogadas);

    printf("\Jogo salvado com sucesso\n\n");
    fclose(f);
}

void listaJogadasAnteriores(Jogada * lista, int *pl, int *pc){
    pJogada aux = lista;
    int count = listaJogadasCont(lista);
    //printf("%d",count);
    int jogadaAnterior;
   /* if(lista == NULL){
        printf("A lista está a NULL\n\n");
        return 0;
    }*/

    int l = *pl;
    int c = *pc;

    int guardacount = 0;

   /* while(aux != NULL){

       // if(count == 0)
        //    printf("\nLista de jogadas:\n\n");

        ++count;
        //printJogadaAnterior(aux, pl, pc);
        //printf(" Jogada %d:\n\n", ++count);
        //printJogada(aux);

        aux = aux->prox;
    }
        */


    if(count > 0){
        printf("\nTotal de jogadas: %d\n\n", count);
         do{
            printf("Número das últimas jogadas anteriores que deseja ver: ");
            scanf(" %d", &jogadaAnterior);

            if(jogadaAnterior < 1 || jogadaAnterior > count)
                printf("Por favor introduza um número de jogadas válido [1, %d].\n\n", count);

        }while(jogadaAnterior < 1 || jogadaAnterior > count);
    }
    else{
        printf("\nNeste momento ainda não se realizou nenhuma jogada.\n\n");
        return;
    }

    int res = count - jogadaAnterior;
//printf("%d",res);
    for(int i = 0; i < res; i++)
        aux = aux->prox;

    while(aux != NULL){

    /*++count;
        if(count == 0)
            printf("\nLista de jogadas:\n\n");*/

       // if(count <= jogadaAnterior)
       if(jogadaAnterior == 1)
            printf("\n\nÚltima Jogada:");
       else
            printf("\n\n%dª Jogada:", ++guardacount);

        printJogadaAnterior(aux, l, c);


        aux = aux->prox;
    }

    /*if(count > 0)
        printf("Total de jogadas: %d\n\n", count);
    else
        printf("\nSem jogadas para listar\n\n");

    count = 0;*/
}

void printJogadaAnterior(pJogada aux, int l, int c){

    char ** temp = NULL;
    temp = (char **)malloc(sizeof(char *) * (l));
    if(temp == NULL){
       printf("Erro na Alocação de Memória");
       return 0;
    }

    for(int i = 0; i<(l);i++){
        temp[i] = malloc(sizeof(char) * (c));
        if(temp[i] == NULL){
           printf("Erro na Alocação de Memória");
           free(temp[i]);
           free(temp);
           return 0;
        }
    }
    inicializa_tabJA(l,c,temp);
    if(aux != NULL){

        if(aux->linha == 1){
            escreve_tabJA(l,c,temp);
            //l--;
        }
        if(aux->coluna == 1){
            escreve_tabJA(l,c,temp);
            //c--;
        }
        if(aux->cor == 'G'){
            temp[(aux->x)-1][(aux->y)-1] = aux->cor;
            //printf("linha = %d", l);
            escreve_tabJA(l,c,temp);
        }
        if(aux->cor == 'Y'){
            temp[(aux->x)-1][(aux->y)-1] = aux->cor;
            escreve_tabJA(l,c,temp);
        }
        if(aux->cor == 'R'){
            temp[(aux->x)-1][(aux->y)-1] = aux->cor;
            escreve_tabJA(l,c,temp);
        }
        if(aux->pedra == 1){
            temp[(aux->x)-1][(aux->y)-1] = aux->cor;
            escreve_tabJA(l,c,temp);
        }

    }


}

void escreve_tabJA(int l, int c, char **t){
    int i, j;

    printf("\n\n");
    for(i=0; i<(l); i++){
        for(j=0; j<(c); j++)
            printf(" %c ", t[i][j]);
        putchar('\n');
    }
}

void inicializa_tabJA(int l, int c, char **t){ // *p == *N | Em vez de ser *p podia ser *N
    int i,j;

    for(i=0; i<(l); i++)      // Linhas
        for(j=0; j<(c); j++)      // Colunas da linha i
            t[i][j] = '_';
}

int listaJogadasCont(Jogada * lista){
    pJogada aux = lista;
    int count = 0;

   /* if(lista == NULL){
        printf("A lista está a NULL\n\n");
        return 0;
    }*/


    while(aux != NULL){

       // if(count == 0)
         //   printf("\nLista de jogadas:\n\n");
++count;
        //printf(" Jogada %d:\n\n", ++count);
        //printJogada(aux);

        aux = aux->prox;
    }

   /* if(count > 0)
        printf("Total de jogadas: %d\n\n", count);
    else
        printf("\nSem jogadas para listar\n\n");*/
        return count;
}
