/*------------//------------//------------*/
//   Trabalho Prático Programação - LEI   //
//          DEIS-ISEC 2020-2021           //
//          Emanuel Saraiva               //
//          a2019130219@isec.pt           //
/*------------//------------//------------*/


// NOTA: Este ficheiro (jogadorAutomatico.c) é o ficheiro que tem todas as funções relativas
//       à parte de Jogar contra o Programa/Computador

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include "utils.h"
#include "utilsFile.h"
#include "jogadorAutomatico.h"
#include "jogada.h"
#include <limits.h>

int jogarContraPC(){

    pJogada lista = NULL;
    char nomefile[FILENAME_MAX];

    initRandom();

    int N;
    N = intUniformRnd(3, 5);

    int l,c;
    l = N;
    c = N;

    char **tab = NULL;

int lG, lY, lR, cG, cY, cR, dG, dY, dR;

    char jogador = 'A';
    int n_jogadas = 0;
    char ganhou = ' ';

    int contLinhaJogadorA = 0;
    int contLinhaJogadorB = 0;

    int contColunaJogadorA = 0;
    int contColunaJogadorB = 0;

    int contPedraJogadorA = 0;
    int contPedraJogadorB = 0;

    char resposta;
    FILE *f = fopen("jogo.bin","rb");

    fseek(f, 0, SEEK_END);

    if(ftell(f)){ //if(ftell(f) != 0)
        do{
            printf("Deseja retomar o jogo anterior?\n");
            printf("Sim -> s\n");
            printf("Não -> n\n");
            printf("Resposta: ");
            scanf(" %c", &resposta);
            if(resposta != 's' && resposta != 'n'){
                printf("Por favor escreva 's' se quiser retomar o jogo ou 'n' se não quiser retomá-lo.\n\n");
            }
        }while(resposta != 's' && resposta != 'n');

        if(resposta == 's'){
            tab = leDadosFileBin(&lista, &jogador, &N, &l, &c, tab, &contLinhaJogadorA, &contLinhaJogadorB, &contPedraJogadorA, &contPedraJogadorB, &contColunaJogadorA, &contColunaJogadorB);

            //l = N;
            //c = N;
            //return 0;
            if(jogador == 'A')
                jogador = 'B';
            else
                jogador = 'A';
            //return 0;

        }
        else{
            tab = (char **)malloc(sizeof(char *) * N);
            if(tab == NULL){
               printf("Erro na Alocação de Memória");
               return 0;
            }

            for(int i = 0; i<l;i++){
                tab[i] = malloc(sizeof(char) * N);
                if(tab[i] == NULL){
                   printf("Erro na Alocação de Memória");
                   free(tab[i]);
                   free(tab);
                   return 0;
                }
            }
            inicializa_tab(&l, &c, tab);
            resetFileBin();
        }
    }
    else{
        tab = (char **)malloc(sizeof(char *) * N);
        if(tab == NULL){
           printf("Erro na Alocação de Memória");
           return 0;
        }

        for(int i = 0; i<l;i++){
            tab[i] = malloc(sizeof(char) * N);
            if(tab[i] == NULL){
               printf("Erro na Alocação de Memória");
               free(tab[i]);
               free(tab);
               return 0;
            }
        }
        inicializa_tab(&l, &c, tab);
    }

   // inicializa_tab(&l, &c, tab);

    do{
        // Isto é para detectar o Sistema Operativo, pois o comando para dar clear
        // Na consola não é igual, logo é preciso fazer desta maneira.
        #ifdef __unix__
            system("clear");
        #else
            system("cls");
        #endif

        escreve_tab(&l, &c,tab);

        int resf = 0;
        tab = escolhe_jogadaPC(&lista, N, &l, &c, tab, &jogador, &contLinhaJogadorA, &contLinhaJogadorB, &contPedraJogadorA, &contPedraJogadorB, &contColunaJogadorA, &contColunaJogadorB, &resf);

        if(tab==0)
            return 0;

        if(resf == 10){ //Case:7 - O jogador optou por Interromper o Jogo, logo retorna 10, logo sai.
            libertaLista(&lista);
            //lembrar de por isto nos return 0.
            for(int z = 0 ; z < l; z++){
                free(tab[z]);
            }
            free(tab);
            return 0;
        }

        if(resf == 11){
            libertaLista(&lista);
            //lembrar de por isto nos return 0.
            for(int z = 0 ; z < l; z++){
                free(tab[z]);
            }
            free(tab);
            return 0;
        }
           // printf("1");
       // guardaDadosFileBin(&l, &c, tab, &jogador, &contLinhaJogadorA, &contLinhaJogadorB, &contPedraJogadorA, &contPedraJogadorB, &contColunaJogadorA, &contColunaJogadorB);
//printf("2");
        //leDadosFileBin(&l, &c);
        //return 0;
//printf("3");
       // escreveDadosFileBin(&l, &c, tab, &jogador);

        n_jogadas ++;

        if(linhaG(&l, &c, tab)==1 || linhaY(&l, &c, tab)==1 || linhaR(&l, &c, tab)==1 || colunaG(&l, &c, tab)==1 || colunaY(&l, &c, tab)==1 || colunaR(&l, &c, tab)==1 || diagonalG(&l, &c, tab)==1 || diagonalY(&l, &c, tab)==1 || diagonalR(&l, &c, tab)==1){
            ganhou = jogador;

            if(linhaG(&l, &c, tab)==1)
                lG = 1;
            else if(linhaY(&l, &c, tab)==1)
                lY = 1;
            else if(linhaR(&l, &c, tab)==1)
                lR = 1;
            else if(colunaG(&l, &c, tab)==1)
                cG = 1;
            else if(colunaY(&l, &c, tab)==1)
                cY = 1;
            else if(colunaR(&l, &c, tab)==1)
                cR = 1;
            else if(diagonalG(&l, &c, tab)==1)
                dG = 1;
            else if(diagonalY(&l, &c, tab)==1)
                dY = 1;
            else if(diagonalR(&l, &c, tab)==1)
                dR = 1;
        }
        else{
            if(jogador == 'A')
                jogador = 'B';
            else
                jogador = 'A';
        }

    /*
        if(joga == 1)
            joga = 2;
        else
            joga = 1;
    */

    //printf("linhas: %d", l);
    }while(ganhou==' ' && n_jogadas < ((l*c)+6));


    escreve_tab(&l, &c,tab);
    escreve_resultadoPC(&ganhou);


    if(n_jogadas % 2 == 0){
            jogador = 'B';
        }
        else{
            jogador = 'A';
        }

    printf("\nIntroduza o nome do ficheiro onde quer que sejam guardadas as informações: ");
    scanf(" %s", nomefile);
    gravarListaPC(nomefile, lista, jogador, n_jogadas, ganhou, lG, lY, lR, cG, cY, cR, dG, dY, dR);


    for(int z = 0 ; z < N; z++){
        free(tab[z]);
    }
    free(tab);
    return 0;
}

void escreve_resultadoPC(char *ganhou){

    if(*ganhou == ' ')
        printf("\nEmpate\n\n"); // Nunca irá haver empate, pois irá haver sempre alguém que vai conseguir completar ou uma linha ou uma coluna ou uma diagonal
    else{
        resetFileBin();
        if(*ganhou == 'A')
            printf("\nParabéns! Você Ganhou.\n\n");
        else
            printf("\nUps! Ganhou o computador.\n\n");
    }
}


char** escolhe_jogadaPC(Jogada ** lista, int N, int *pl, int *pc, char **t, char *jogador, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB, int *resf){
	int pos, opcao, resultado, resultadoAmarela;
    //printf("Linha: %d \t Coluna: %d\n",*pl, *pc);
    //int guardaTentativasLinha = *contLinhaJogadorA = *contLinhaJogadorB;
    //int guardaTentativasPedra = *contPedraJogadorA = *contPedraJogadorB;

    voltaResultado:

    if(*jogador == 'A'){
        if((*contLinhaJogadorA) <= 2){
            printf("\nVezes que você jogou Adicionar uma Linha: %d", *contLinhaJogadorA);
        }
        if((*contLinhaJogadorA) > 2){
            printf("\nVezes que você jogou Adicionar uma Linha: 2");
        }

        if((*contColunaJogadorA) <= 2){
            printf("\nVezes que você jogou Adicionar uma Coluna: %d", *contColunaJogadorA);
        }
        if((*contColunaJogadorA) > 2){
            printf("\nVezes que você jogou Adicionar uma Coluna: 2");
        }

        if((*contPedraJogadorA) <= 1){
            printf("\nVezes que você jogou Adicionar uma Pedra: %d\n", *contPedraJogadorA);
        }
        if((*contPedraJogadorA) > 1){
            printf("\nVezes que você jogou Adicionar uma Pedra: 1\n");
        }
    }else{
        if((*contLinhaJogadorB) <= 2){
            printf("\nVezes que o jogador B jogou Adicionar uma Linha: %d", *contLinhaJogadorB);
        }
        if((*contLinhaJogadorB) > 2){
            printf("\nVezes que o jogador B jogou Adicionar uma Linha: 2");
        }

        if((*contColunaJogadorB) <= 2){
            printf("\nVezes que o jogador B jogou Adicionar uma Coluna: %d", *contColunaJogadorB);
        }
        if((*contColunaJogadorB) > 2){
            printf("\nVezes que o jogador B jogou Adicionar uma Coluna: 2");
        }

        if((*contPedraJogadorB) <= 1){
            printf("\nVezes que o jogador B jogou Adicionar uma Pedra: %d\n", *contPedraJogadorB);
        }
        if((*contPedraJogadorB) > 1){
            printf("\nVezes que o jogador B jogou Adicionar uma Pedra: 1\n");
        }
    }

    if(*jogador == 'A')
        printf("\n\nÉ a sua vez de jogar\n");
    /*do{
        printf("Posição do Tabuleiro onde quer pôr a Peça: ");
        scanf(" %d", &pos);

        if(pos<1 || pos>(*pl)*(*pc))
            printf("Por favor introduza um valor entre [1,%d]!\n",(*pl)*(*pc));

    }while(pos<1 || pos>(*pl)*(*pc)); // || t[(pos-1)/(*p)][(pos-1)%(*p)] != '_'
    */

    if(*jogador =='B'){
        do{
             //printf("\n|-----------//-----------//-----------|\n");
            printf("\n|---------------------------------|\n");
            printf("| ****** Menu do Jogo ******      | \n");
            printf("| 1 - Colocar Peça Verde          |\n");
            printf("| 2 - Colocar Peça Amarela        |\n");
            printf("| 3 - Colocar Peça Vermelha       |\n");
            printf("| 4 - Colocar Uma Pedra           |\n");
            printf("| 5 - Adicionar Uma Linha         |\n");
            printf("| 6 - Adicionar Uma Coluna        |\n");
            printf("| 7 - Interromper o Jogo (Salvar) |\n");
            printf("| 8 - Visualizar o Tabuleiro      |\n");
            printf("| 9 - Sair Sem Guardar            |");
        printf("\n|---------------------------------|\n");
                //printf("Opção: ");
                //scanf("%d", &opcao);
                opcao = intUniformRnd(1, 6); // meter intUniformRnd(3, 5); dps de ter todos a funcionar
                if(opcao < 1 || opcao > 9)
                printf("Por favor introduza um valor entre [1,9]!\n");

        }while(opcao < 1 || opcao > 9);

    }else{
        do{
             //printf("\n|-----------//-----------//-----------|\n");
            printf("\n|---------------------------------|\n");
            printf("| ****** Menu do Jogo ******      | \n");
            printf("| 1 - Colocar Peça Verde          |\n");
            printf("| 2 - Colocar Peça Amarela        |\n");
            printf("| 3 - Colocar Peça Vermelha       |\n");
            printf("| 4 - Colocar Uma Pedra           |\n");
            printf("| 5 - Adicionar Uma Linha         |\n");
            printf("| 6 - Adicionar Uma Coluna        |\n");
            printf("| 7 - Interromper o Jogo (Salvar) |\n");
            printf("| 8 - Visualizar o Tabuleiro      |\n");
            printf("| 9 - Sair Sem Guardar            |");
        printf("\n|---------------------------------|\n");
                printf("Opção: ");
                scanf("%d", &opcao);

                if(opcao < 1 || opcao > 9)
                printf("Por favor introduza um valor entre [1,9]!\n");

        }while(opcao < 1 || opcao > 9);
    }

    do{
        switch(opcao){
        case 1:
            criaListaPC(lista, opcao, jogador, pl, pc, t);
            break;
        case 2:
            if(*jogador == 'B'){ //CPU - mudar nome do jogador
                criaListaPC(lista, opcao, jogador, pl, pc, t);
            }
            else{
                resultado = verificaPecaVerde(pl, pc, t);
                if(resultado){
                    criaListaPC(lista, opcao, jogador, pl, pc, t);
                }
                else{
                    printf("Para pôr uma Peça Amarela precisa de pôr Primeiro uma Verde!");

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                    goto voltaResultado;
                }
            }
            break;
        case 3:
            if(*jogador == 'B'){
                criaListaPC(lista, opcao, jogador, pl, pc, t);
            }
            else{
                resultadoAmarela = verificaPecaAmarela(pl, pc, t);
                if(resultadoAmarela){
                    criaListaPC(lista, opcao, jogador, pl, pc, t);
                }
                else{
                    printf("Para pôr uma Peça Vermelha precisa de pôr Primeiro uma Amarela!");

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                    goto voltaResultado;
                }
            }
            break;
        case 4:
            if((*jogador) == 'A'){
                (*contPedraJogadorA)++;

                if((*contPedraJogadorA) <= 1){
                    criaListaPC(lista, opcao, jogador, pl, pc, t);
                }
                if((*contPedraJogadorA) > 1){
                    printf("Você esgotou as suas jogadas de Adicionar uma Pedra");

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                    goto voltaResultado; //remover o goto, usar outra forma
                }
            }
            else{
                (*contPedraJogadorB)++;

                if((*contPedraJogadorB) <= 1){
                    criaListaPC(lista, opcao, jogador, pl, pc, t);
                }
                if((*contPedraJogadorB) > 1){
                     printf("O jogador %c esgotou as suas jogadas de Adicionar uma Pedra", *jogador);

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                    goto voltaResultado;
                }
            }
            break;
        case 5:
            if((*jogador) == 'A'){
                (*contLinhaJogadorA)++;

                if((*contLinhaJogadorA) <= 2){
                    criaLista(lista, opcao, pl, pc, &t);
                }
                if((*contLinhaJogadorA) > 2){
                    printf("Você esgotou as suas jogadas de Adicionar uma Linha");

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                    goto voltaResultado;
                }
            }
            else{
                (*contLinhaJogadorB)++;

                if((*contLinhaJogadorB) <= 2){
                    criaLista(lista, opcao, pl, pc, &t);
                }
                if((*contLinhaJogadorB) > 2){
                     printf("O jogador %c esgotou as suas jogadas de Adicionar uma Linha", *jogador);

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                    goto voltaResultado;
                }
            }

            break;
        case 6:
            if((*jogador) == 'A'){
                (*contColunaJogadorA)++;

                if((*contColunaJogadorA) <= 2){
                    criaLista(lista, opcao, pl, pc, &t);
                }
                if((*contColunaJogadorA) > 2){
                    printf("Você esgotou as suas jogadas de Adicionar uma Coluna");

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                    goto voltaResultado;
                }
            }
            else{
                (*contColunaJogadorB)++;

                if((*contColunaJogadorB) <= 2){
                    criaLista(lista, opcao, pl, pc, &t);
                }
                if((*contColunaJogadorB) > 2){
                     printf("O jogador %c esgotou as suas jogadas de Adicionar uma Coluna", *jogador);

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                    goto voltaResultado;
                }
            }
            break;
            case 7:
                guardaDadosFileBin(lista, N, pl, pc, t, jogador, contLinhaJogadorA, contLinhaJogadorB, contPedraJogadorA, contPedraJogadorB, contColunaJogadorA, contColunaJogadorB);
                *resf = 10;
                return t;
            break;
            case 8:
                //listaJogadas(*lista);
                listaJogadasAnteriores(*lista, pl, pc);
                #ifdef __unix__
                    sleep(5);
                #else
                    Sleep(5000);
                #endif
            break;
            case 9:
                *resf = 11;
                resetFileBin();
                return t;
            break;
        }

        if(opcao < 1 || opcao > 9)
            printf("Por favor introduza um valor entre [1,9]!\n");

    }while(opcao < 1 || opcao > 9);

    /*
    if(jogador == 'A')
        t[(pos-1)/(*p)][(pos-1)%(*p)] = 'X';
    else
        t[(pos-1)/(*p)][(pos-1)%(*p)] = 'O';
    */
    return t;
}

void criaListaPC(Jogada ** lista, int opcao, char *jogador, int *pl, int *pc, char **t){
    Jogada aux;
    Jogada* novo = NULL;
    Jogada* lista_aux = NULL;
    // nao é necessario mandar a lista na funcao
    if(obtemJogadaPC(*lista, &aux, opcao, jogador, pl, pc, t) == 0){ //obtemPessoa Tem de fazer as verificaçoes todas - ta feito
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

int obtemJogadaPC(pJogada lista, pJogada p, int opcao, char *jogador, int *pl, int *pc, char **t){
//    int r = 0;
    p->prox = NULL;
    int resultadoPC;
    int i,j;

    int resfjPC = 1;

    if(opcao == 1){ // OPCAO 1 - O Utilizador quer pôr a peça VERDE

        if(*jogador == 'B'){
            do{
                p->x = intUniformRnd(1, *pl);
                p->y = intUniformRnd(1, *pc);
                while(t[(p->x)-1][(p->y)-1] != '_'){
                    p->x = intUniformRnd(1, *pl);
                    p->y = intUniformRnd(1, *pc);
                }
            }while(((p->x) < 1 || (p->x) > (*pl)) || ((p->y) < 1 || (p->y) > (*pc)) || (t[(p->x)-1][(p->y)-1] != '_'));

            p->cor = 'G';
            p->pedra = 0;
            p->linha = 0;
            p->coluna = 0;

            t[(p->x)-1][(p->y)-1] = p->cor;
        }
        else{
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
    }

    if(opcao == 2){ // OPCAO 2 - O Utilizador quer pôr a peça AMARELA

        if(*jogador == 'B'){

            resultadoPC = verificaPecaVerde(pl, pc, t);

            if(resultadoPC == 1){

                //int i,j;

                p->x = intUniformRnd(1, *pl);
                p->y = intUniformRnd(1, *pc);

                while(t[(p->x)-1][(p->y)-1] != 'G'){
                    p->x = intUniformRnd(1, *pl);
                    p->y = intUniformRnd(1, *pc);
                }
                while(t[(p->x)-1][(p->y)-1] == 'G'){

                    for(i = intUniformRnd(0, (*pl -1)); i<(*pl); i++){      // Linhas
                        for(j = intUniformRnd(0, (*pc -1)); j<(*pc); j++){
                            if(t[i][j] == 'G'){
                                p->cor = 'Y';
                                p->pedra = 0;
                                p->linha = 0;
                                p->coluna = 0;

                                t[(p->x)-1][(p->y)-1] = p->cor;
                            }
                        }
                    }
                }

            }else{
                    do{
                    p->x = intUniformRnd(1, *pl);
                    p->y = intUniformRnd(1, *pc);
                    while(t[(p->x)-1][(p->y)-1] != '_'){
                        p->x = intUniformRnd(1, *pl);
                        p->y = intUniformRnd(1, *pc);
                    }
                }while(((p->x) < 1 || (p->x) > (*pl)) || ((p->y) < 1 || (p->y) > (*pc)) || (t[(p->x)-1][(p->y)-1] != '_'));

                p->cor = 'G';
                p->pedra = 0;
                p->linha = 0;
                p->coluna = 0;

                t[(p->x)-1][(p->y)-1] = p->cor;
            }

        }else{
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
    }

    if(opcao == 3){ // OPCAO 3 - O Utilizador quer pôr a peça VERMELHA

        if(*jogador == 'B'){

            resultadoPC = verificaPecaAmarela(pl, pc, t);

            if(resultadoPC == 1){



                p->x = intUniformRnd(1, *pl);
                p->y = intUniformRnd(1, *pc);

                while(t[(p->x)-1][(p->y)-1] != 'Y'){
                    p->x = intUniformRnd(1, *pl);
                    p->y = intUniformRnd(1, *pc);
                }
                while(t[(p->x)-1][(p->y)-1] == 'Y'){

                    for(i = intUniformRnd(0, (*pl -1)); i<(*pl); i++){      // Linhas
                        for(j = intUniformRnd(0, (*pc -1)); j<(*pc); j++){
                            if(t[i][j] == 'Y'){
                                p->cor = 'R';
                                p->pedra = 0;
                                p->linha = 0;
                                p->coluna = 0;

                                t[(p->x)-1][(p->y)-1] = p->cor;
                            }
                        }
                    }
                }

            }else{
                resultadoPC = verificaPecaVerde(pl, pc, t);

                if(resultadoPC == 1){



                    p->x = intUniformRnd(1, *pl);
                    p->y = intUniformRnd(1, *pc);

                    while(t[(p->x)-1][(p->y)-1] != 'G'){
                        p->x = intUniformRnd(1, *pl);
                        p->y = intUniformRnd(1, *pc);
                    }
                    while(t[(p->x)-1][(p->y)-1] == 'G'){

                        for(i = intUniformRnd(0, (*pl -1)); i<(*pl); i++){      // Linhas
                            for(j = intUniformRnd(0, (*pc -1)); j<(*pc); j++){
                                if(t[i][j] == 'G'){
                                    p->cor = 'Y';
                                    p->pedra = 0;
                                    p->linha = 0;
                                    p->coluna = 0;

                                    t[(p->x)-1][(p->y)-1] = p->cor;
                                }
                            }
                        }
                    }

                }else{
                        do{
                        p->x = intUniformRnd(1, *pl);
                        p->y = intUniformRnd(1, *pc);
                        while(t[(p->x)-1][(p->y)-1] != '_'){
                            p->x = intUniformRnd(1, *pl);
                            p->y = intUniformRnd(1, *pc);
                        }
                    }while(((p->x) < 1 || (p->x) > (*pl)) || ((p->y) < 1 || (p->y) > (*pc)) || (t[(p->x)-1][(p->y)-1] != '_'));

                    p->cor = 'G';
                    p->pedra = 0;
                    p->linha = 0;
                    p->coluna = 0;

                    t[(p->x)-1][(p->y)-1] = p->cor;
                }
            }

        }else{
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
    }

    if(opcao == 4){ // OPCAO 4 - O Utilizador quer pôr a peça PEDRA

        if(*jogador == 'B'){

             do{
                p->x = intUniformRnd(1, *pl);
                p->y = intUniformRnd(1, *pc);
                while(t[(p->x)-1][(p->y)-1] != '_'){
                    p->x = intUniformRnd(1, *pl);
                    p->y = intUniformRnd(1, *pc);
                }
            }while(((p->x) < 1 || (p->x) > (*pl)) || ((p->y) < 1 || (p->y) > (*pc)) || (t[(p->x)-1][(p->y)-1] != '_'));

            p->cor = 'P';
            p->pedra = 1;
            p->linha = 0;
            p->coluna = 0;

            t[(p->x)-1][(p->y)-1] = p->cor;

        }else{

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
    }

    if(opcao == 5){ // OPCAO 5 - O Utilizador quer adicionar uma linha

        *t = adicionaLinha(pl, pc, *t, &resfjPC);

        if(resfjPC == 0)
            return 0;

        p->x = 0;
        p->y = 0;
        p->cor = ' ';
        p->pedra = 0;
        p->linha = 1;
        p->coluna = 0;


    }

    if(opcao == 6){ // OPCAO 6 - O Utilizador quer adicionar uma coluna

        *t = adicionaColuna(pl, pc, *t, &resfjPC);

        if(resfjPC == 0)
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

void gravarListaPC(char *nomefile, pJogada lista, char jogador, int njogadas, char ganhou, int lG, int lY, int lR, int cG, int cY, int cR, int dG, int dY, int dR){
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

        if(jogador == 'C' && cont == 0){
            jogador = 'A';
            cont = 1;
        }

		fprintf(f, " Jogador %c \n X: %d , Y: %d , Cor: %c , Pedra: %d , Linha: %d, Coluna: %d\n\n",jogador, aux->x, aux->y, aux->cor, aux->pedra, aux->linha, aux->coluna);

        aux = aux->prox;

        if(jogador == 'A'){
            jogador = 'C';
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


void listaJogadasPC(Jogada * lista){
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
        printJogadaPC(aux);

        aux = aux->prox;
    }

    if(count > 0)
        printf("Total de jogdas: %d\n\n", count);
    else
        printf("\nSem jogadas para listar\n\n");
}

void printJogadaPC(pJogada aux){
    if(aux != NULL){
        printf("   X: %d\n", aux->x);
        printf("   Y: %d\n", aux->y);
        printf("   Cor: %c\n", aux->cor);
        printf("   Pedra: %d\n", aux->pedra);
        printf("   Linha: %d\n", aux->linha);
        printf("   Coluna: %d\n", aux->coluna);
    }

}

void adicionaPecaVerdePC(int *pl, int *pc, char ** t, char *jogador){
    int l, c;


    if(*jogador == 'B'){
        do{
            l = intUniformRnd(1, *pl);
            c = intUniformRnd(1, *pc);
            while(t[l-1][c-1] != '_'){
                l = intUniformRnd(1, *pl);
                c = intUniformRnd(1, *pc);
            }
        }while((l < 1 || l > (*pl)) || (c < 1 || c > (*pc)) || (t[l-1][c-1] != '_'));

    }
    else{
        do{
            loop_linha:
            printf("Introduza a linha [1,%d]: ", *pl);
            scanf("%d",&l);

            if(l < 1 || l > (*pl)){
                printf("Por favor introduza uma linha entre [1, %d].\n\n", *pl);
                goto loop_linha;
            }

            loop_coluna:
            printf("Introduza a coluna [1,%d]: ", *pc);
            scanf("%d",&c);

            if(c < 1 || c > (*pc)){
                printf("Por favor introduza uma coluna entre [1, %d].\n\n", *pc);
                goto loop_coluna;
            }

            if(t[l-1][c-1] != '_'){
                printf("Por favor coloque uma Peça Verde numa Célula Vazia.\n\n");
            }
        }while((l < 1 || l > (*pl)) || (c < 1 || c > (*pc)) || (t[l-1][c-1] != '_'));
    }

    if(*jogador == 'A')
        t[l - 1][c - 1] = 'G';
    else
        t[l - 1][c - 1] = 'G';
}

void adicionaPecaAmarelaPC(int *pl, int *pc, char ** t, char *jogador){
    int l, c;
    int resultadoPC;

    if(*jogador == 'B'){

        resultadoPC = verificaPecaVerde(pl, pc, t);

        if(resultadoPC == 1){

            int i,j;

            l = intUniformRnd(1, *pl);
            c = intUniformRnd(1, *pc);

            while(t[l-1][c-1] != 'G'){
                l = intUniformRnd(1, *pl);
                c = intUniformRnd(1, *pc);
            }
            while(t[l-1][c-1] == 'G'){

                for(i = intUniformRnd(0, (*pl -1)); i<(*pl); i++){      // Linhas
                    for(j = intUniformRnd(0, (*pc -1)); j<(*pc); j++){
                        if(t[i][j] == 'G'){
                            t[l - 1][c - 1] = 'Y';
                        }
                    }
                }
            }

        }else{
            adicionaPecaVerdePC(pl, pc, t, jogador);
            return;
        }

    }
    else{
        do{
            loop_linha:
            printf("Introduza a linha [1,%d]: ", *pl);
            scanf("%d",&l);

            if(l < 1 || l > (*pl)){
                printf("Por favor introduza uma linha entre [1, %d].\n\n", *pl);
                goto loop_linha;
            }

            loop_coluna:
            printf("Introduza a coluna [1,%d]: ", *pc);
            scanf("%d",&c);

            if(c < 1 || c > (*pc)){
                printf("Por favor introduza uma coluna entre [1, %d].\n\n", *pc);
                goto loop_coluna;
            }

            if(t[l-1][c-1] != 'G' && t[l-1][c-1] != 'g'){
                printf("Por favor introduza uma peça Amarela no lugar de uma Verde.\n\n");
            }
        }while((l < 1 || l > (*pl)) || (c < 1 || c > (*pc)) || t[l-1][c-1] != 'G' && t[l-1][c-1] != 'g');

        if(*jogador == 'A')
            t[l - 1][c - 1] = 'Y';
        else
            t[l - 1][c - 1] = 'Y';
    }

}

void adicionaPecaVermelhaPC(int *pl, int *pc, char ** t, char *jogador){
    int l, c;

    int resultadoPC;

    if(*jogador == 'B'){ // O B, neste ficheiro (jogadorAutomatico.c) é o Computador
        resultadoPC = verificaPecaAmarela(pl, pc, t);

        if(resultadoPC == 1){

            int i,j;

            l = intUniformRnd(1, *pl);
            c = intUniformRnd(1, *pc);

            while(t[l-1][c-1] != 'Y'){
                l = intUniformRnd(1, *pl);
                c = intUniformRnd(1, *pc);
            }
            while(t[l-1][c-1] == 'Y'){

                for(i = intUniformRnd(0, (*pl -1)); i<(*pl); i++){      // Linhas
                    for(j = intUniformRnd(0, (*pc -1)); j<(*pc); j++){
                        if(t[i][j] == 'Y'){
                            t[l - 1][c - 1] = 'R';
                        }
                    }
                }
            }

        }else{
            adicionaPecaAmarelaPC(pl, pc, t, jogador);
        }

    }else{
        do{
            loop_linha:
            printf("Introduza a linha [1,%d]: ", *pl);
            scanf("%d",&l);

            if(l < 1 || l > (*pl)){
                printf("Por favor introduza uma linha entre [1, %d].\n\n", *pl);
                goto loop_linha;
            }

            loop_coluna:
            printf("Introduza a coluna [1,%d]: ", *pc);
            scanf("%d",&c);

            if(c < 1 || c > (*pc)){
                printf("Por favor introduza uma coluna entre [1, %d].\n\n", *pc);
                goto loop_coluna;
            }

            if(t[l-1][c-1] != 'Y' && t[l-1][c-1] != 'y'){
                printf("Por favor introduza uma peça Vermelha no lugar de uma Amarela.\n\n");
            }
        }while(l < 1 || l > (*pl) && c < 1 || c > (*pc) || t[l-1][c-1] != 'Y' && t[l-1][c-1] != 'y');

        if(*jogador == 'A')
            t[l - 1][c - 1] = 'R';
        else
            t[l - 1][c - 1] = 'R';
    }
}
