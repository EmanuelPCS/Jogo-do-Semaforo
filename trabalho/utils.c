/*------------//------------//------------*/
//   Trabalho Prático Programação - LEI   //
//          DEIS-ISEC 2020-2021           //
//          Emanuel Saraiva               //
//          a2019130219@isec.pt           //
/*------------//------------//------------*/


// NOTA: Este ficheiro (utils.c) é o ficheiro que tem todas as funções relativas à jogabilidade do Jogo
// NOTA2: Em algumas funções há algumas variáveis que não estão a ser usadas, porque
//        eu estava a fazer o jogo com peças diferentes para cada jogador. No entanto
//        está a funcionar corretamente para peças iguais. Simplesmente optei por deixar
//        essas variaveis e adaptar de forma muito rápida com peças iguais para ambos os jogadores.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include "utils.h"
#include "utilsFile.h"
#include "jogadorAutomatico.h"
#include "jogada.h"
#include <limits.h>


void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}


//  As minhas funções:

// Esta função deteta o Sistema Operativo do dispositivo.
// Caso Seja Unix vai buscar o seu username e mete nas Boas vindas.
// Caso Seja Windows diz apenas Bem vindo.
#ifdef __unix__
    int boasVindas(){


        char hostname[HOST_NAME_MAX];
        char username[LOGIN_NAME_MAX];
        int result;
        result = gethostname(hostname, HOST_NAME_MAX);
        if (result)
        {
          perror("gethostname");
          return EXIT_FAILURE;
        }
        result = getlogin_r(username, LOGIN_NAME_MAX);
        if (result)
        {
          perror("getlogin_r");
          return EXIT_FAILURE;
        }
    //deixar estes prints, porque fica mais bonito na consola
     printf("\n|--------------------------------------------|\n");
    printf("|");
        result = printf("              Bem-vindo %s!               |\n", username);

    printf("|                                            |\n");

        if (result < 0)
        {
          perror("printf");
          return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;

    }
#else
    int boasVindas(){
    //deixar estes prints, porque fica mais bonito na consola
    printf("\n|--------------------------------------------|\n");
    printf("|");
        printf("                Bem-vindo!                  |\n");
        printf("|                                            |\n");
    //printf("\n|-------------------------------------|\n");
    }
#endif
//*/


void explicacaoPrograma(){

    printf("|     Este programa tem como objetivo        |\n");
    printf("|     fazer uma simulação do jogo do         |\n");
    printf("|                Semáforo.                   |\n");
    printf("|                                            |\n");
   /* printf("|   As posições do tabuleiro são      |\n");
    printf("|   distribuídas da seguinte forma:   |\n");

    printf("|                                     |\n");

    int i, j, cont = 1;
    char tabelaInicial[3][3];
    for(i=0; i<3; i++)      // Linhas
        for(j=0; j<3; j++)      // Colunas da linha i
            tabelaInicial[i][j] = cont++;

    for(i=0; i<3; i++){printf("|             ");
        for(j=0; j<3; j++)
            printf(" %d ", tabelaInicial[i][j]);
        printf("               |");
        putchar('\n');

    }
    printf("|                                     |\n");
    printf("| Nota: Este é um tabuleiro exemplo.  |\n");
    printf("| Caso o tabuleiro tenha mais colunas |\n");
    printf("| ou linhas, quando o jogo lhe pedir  |\n");
    printf("| a posição para colocar a peça       |\n");
    printf("| numere as como está no exemplo,     |\n");
    printf("| isto é, da esquerda para a direita. |\n");*/
    printf("|     Regras:                                |\n");
    printf("|     - As jogadas são alternadas;           |\n");
    printf("|     - Cada jogador pode adicionar          |\n");
    printf("|     no máximo 2 linhas e 2 colunas;        |\n");
    printf("|     - Cada jogador pode adicionar          |\n");
    printf("|     no máximo 1 Pedra por Jogo;            |\n");
    printf("|     - Só pode colocar uma Peça Verde       |\n");
    printf("|     num espaço onde haja '_';              |\n");
    printf("|     - Só pode pôr uma Peça Amarela         |\n");
    printf("|     num espaço onde haja uma Peça Verde;   |\n");
    printf("|     - Só pode pôr uma Peça Vermelha        |\n");
    printf("|     num espaço onde haja uma peça Amarela. |\n");
    printf("|                                            |\n");
    printf("|     Quem é que ganha?                      |\n");
    printf("|     - Ganha o 1º Jogador a conseguir       |\n");
    printf("|     fazer uma linha, coluna ou diagonal    |\n");
    printf("|     completa.                              |\n");
    printf("|                                            |\n");
    printf("|     Bons Jogos!                            |\n");
    printf("|--------------------------------------------|\n");
}

int menu()
{
    int opcao;

    do{

        printf("\n|-------------//--------------//-------------|\n");
        printf("\n|-----------------------------------|\n");
            printf("|   *** Menu Principal ***          | \n");
            printf("|   1 - Jogar 1vs1                  |\n");
            printf("|   2 - Jogar Contra o Computador   |\n");
            printf("|   3 - Ver Regras                  |\n");
            printf("|   4 - Terminar                    |");
        printf("\n|-----------------------------------|\n");
            printf("Opção: ");

        scanf("%d", &opcao);
        if(opcao < 1 || opcao > 4){
            printf("Por favor introduza um valor entre [1,4]!\n");

        }
    }while(opcao < 1 || opcao > 4);
    printf("\n|-------------//--------------//-------------|\n");
    return opcao;
}

int jogar(){

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
//libertaLista_v1(&lista);
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
        tab = escolhe_jogada(&lista, N, &l, &c, tab, &jogador, &contLinhaJogadorA, &contLinhaJogadorB, &contPedraJogadorA, &contPedraJogadorB, &contColunaJogadorA, &contColunaJogadorB, &resf);

        /*if(lista == NULL){
            printf("A lista está a NULL");
            return 0;
        }*/

        /*if(tab==0)
            return 0;*/

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
        //guardaDadosFileBin(lista,&l, &c, tab, &jogador, &contLinhaJogadorA, &contLinhaJogadorB, &contPedraJogadorA, &contPedraJogadorB, &contColunaJogadorA, &contColunaJogadorB);
//printf("2");
        //leDadosFileBin(&l, &c);
        //return 0;
//printf("3");
       // escreveDadosFileBin(&l, &c, tab, &jogador);



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

        n_jogadas ++;
    /*
        if(joga == 1)
            joga = 2;
        else
            joga = 1;
    */

    //printf("linhas: %d", l);
    }while(ganhou==' ' && n_jogadas < ((l*c)+6));


    escreve_tab(&l, &c,tab);
    escreve_resultado(&ganhou);


     if(n_jogadas % 2 == 0){
            jogador = 'B';
        }
        else{
            jogador = 'A';
        }

    printf("\nIntroduza o nome do ficheiro onde quer que sejam guardadas as informações: ");
    scanf(" %s", nomefile);
    gravarLista(nomefile, lista, jogador, n_jogadas, ganhou, lG, lY, lR, cG, cY, cR, dG, dY, dR);

    libertaLista(&lista);
    //lembrar de por isto nos return 0.
    for(int z = 0 ; z < N; z++){
        free(tab[z]);
    }
    free(tab);
    return 0;
}

void inicializa_tab(int *pl, int *pc, char **t){ // *p == *N | Em vez de ser *p podia ser *N
    int i,j;

    for(i=0; i<(*pl); i++)      // Linhas
        for(j=0; j<(*pc); j++)      // Colunas da linha i
            t[i][j] = '_';
}

void escreve_tab(int *pl, int *pc, char **t){
    int i, j;

    printf("\n\n");
    for(i=0; i<(*pl); i++){
        for(j=0; j<(*pc); j++)
            printf(" %c ", t[i][j]);
        putchar('\n');
    }
}

char** escolhe_jogada(Jogada ** lista, int N, int *pl, int *pc, char **t, char *jogador, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB, int *resf){
	int opcao, opcao2, resultado, resultadoAmarela;
	*resf = 0;
    //printf("Linha: %d \t Coluna: %d\n",*pl, *pc);
    //int guardaTentativasLinha = *contLinhaJogadorA = *contLinhaJogadorB;
    //int guardaTentativasPedra = *contPedraJogadorA = *contPedraJogadorB;

    voltaResultado:

    if(*jogador == 'A'){
        if((*contLinhaJogadorA) <= 2){
            printf("\nVezes que o jogador A jogou Adicionar uma Linha: %d", *contLinhaJogadorA);
        }
        if((*contLinhaJogadorA) > 2){
            printf("\nVezes que o jogador A jogou Adicionar uma Linha: 2");
        }

        if((*contColunaJogadorA) <= 2){
            printf("\nVezes que o jogador A jogou Adicionar uma Coluna: %d", *contColunaJogadorA);
        }
        if((*contColunaJogadorA) > 2){
            printf("\nVezes que o jogador A jogou Adicionar uma Coluna: 2");
        }

        if((*contPedraJogadorA) <= 1){
            printf("\nVezes que o jogador A jogou Adicionar uma Pedra: %d\n", *contPedraJogadorA);
        }
        if((*contPedraJogadorA) > 1){
            printf("\nVezes que o jogador A jogou Adicionar uma Pedra: 1\n");
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
    printf("\n\nÉ a vez do jogador %c\n", *jogador);
    /*do{
        printf("Posição do Tabuleiro onde quer pôr a Peça: ");
        scanf(" %d", &pos);

        if(pos<1 || pos>(*pl)*(*pc))
            printf("Por favor introduza um valor entre [1,%d]!\n",(*pl)*(*pc));

    }while(pos<1 || pos>(*pl)*(*pc)); // || t[(pos-1)/(*p)][(pos-1)%(*p)] != '_'
    */

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

    do{
        switch(opcao){
        case 1:
            //adicionaPecaVerde(pl, pc, t, jogador);
            criaLista(lista, opcao, pl, pc, t);
            //listaPessoas_v1(lista);
            break;
        case 2:
            resultado = verificaPecaVerde(pl, pc, t);
            if(resultado){
                //adicionaPecaAmarela(pl, pc, t, jogador);
                 criaLista(lista, opcao, pl, pc, t);
            }
            else{
                printf("Para pôr uma Peça Amarela precisa de pôr Primeiro uma Verde!");

                #ifdef __unix__
                    system("clear");
                #else
                    system("cls");
                #endif

                escreve_tab(pl, pc,t);

              /*  do{

                }while*/
                goto voltaResultado;
                //escolhe_jogada(lista,N,pl,pc,t,jogador,contLinhaJogadorA,contLinhaJogadorB,contPedraJogadorA,contPedraJogadorB,contColunaJogadorA,contColunaJogadorB);
            }
            break;
        case 3:
            resultadoAmarela = verificaPecaAmarela(pl, pc, t);
            if(resultadoAmarela){
                //adicionaPecaVermelha(pl, pc, t, jogador);
                criaLista(lista, opcao, pl, pc, t);
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
                //escolhe_jogada(lista,N,pl,pc,t,jogador,contLinhaJogadorA,contLinhaJogadorB,contPedraJogadorA,contPedraJogadorB,contColunaJogadorA,contColunaJogadorB);
            }
            break;
        case 4:
            if((*jogador) == 'A'){
                (*contPedraJogadorA)++;

                if((*contPedraJogadorA) <= 1){
                    //adicionaPedra(pl, pc, t, jogador);
                    criaLista(lista, opcao, pl, pc, t);
                }
                if((*contPedraJogadorA) > 1){
                    printf("O jogador %c esgotou as suas jogadas de Adicionar uma Pedra", *jogador);

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                 goto voltaResultado;
                 //escolhe_jogada(lista,N,pl,pc,t,jogador,contLinhaJogadorA,contLinhaJogadorB,contPedraJogadorA,contPedraJogadorB,contColunaJogadorA,contColunaJogadorB);
                }
            }
            else{
                (*contPedraJogadorB)++;

                if((*contPedraJogadorB) <= 1){
                    //adicionaPedra(pl, pc, t, jogador);
                    criaLista(lista, opcao, pl, pc, t);
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
                    //escolhe_jogada(lista,N,pl,pc,t,jogador,contLinhaJogadorA,contLinhaJogadorB,contPedraJogadorA,contPedraJogadorB,contColunaJogadorA,contColunaJogadorB);
                }
            }
            break;
        case 5:
            if((*jogador) == 'A'){
                (*contLinhaJogadorA)++;

                if((*contLinhaJogadorA) <= 2){
                    //t = adicionaLinha(pl, pc, t);
                    /*if(t == 0)
                        return 0;*/
                    criaLista(lista, opcao, pl, pc, &t);
                }
                if((*contLinhaJogadorA) > 2){
                    printf("O jogador %c esgotou as suas jogadas de Adicionar uma Linha", *jogador);

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                    goto voltaResultado;
                   //escolhe_jogada(lista,N,pl,pc,t,jogador,contLinhaJogadorA,contLinhaJogadorB,contPedraJogadorA,contPedraJogadorB,contColunaJogadorA,contColunaJogadorB);
                }
            }
            else{
                (*contLinhaJogadorB)++;

                if((*contLinhaJogadorB) <= 2){
                    //t = adicionaLinha(pl, pc, t);
                    /*if(t == 0)
                        return 0;*/
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
                  // escolhe_jogada(lista,N,pl,pc,t,jogador,contLinhaJogadorA,contLinhaJogadorB,contPedraJogadorA,contPedraJogadorB,contColunaJogadorA,contColunaJogadorB);
                }
            }

            break;
        case 6:
            if((*jogador) == 'A'){
                (*contColunaJogadorA)++;

                if((*contColunaJogadorA) <= 2){
                    /*t = adicionaColuna(pl, pc, t);
                    if(t == 0)
                        return 0;*/
                    criaLista(lista, opcao, pl, pc, &t);
                }
                if((*contColunaJogadorA) > 2){
                    printf("O jogador %c esgotou as suas jogadas de Adicionar uma Coluna", *jogador);

                    #ifdef __unix__
                        system("clear");
                    #else
                        system("cls");
                    #endif

                    escreve_tab(pl, pc,t);

                   goto voltaResultado;
                   //escolhe_jogada(lista,N,pl,pc,t,jogador,contLinhaJogadorA,contLinhaJogadorB,contPedraJogadorA,contPedraJogadorB,contColunaJogadorA,contColunaJogadorB);
                }
            }
            else{
                (*contColunaJogadorB)++;

                if((*contColunaJogadorB) <= 2){
                    /*t = adicionaColuna(pl, pc, t);
                    if(t == 0)
                        return 0;*/
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
                   // escolhe_jogada(lista,N,pl,pc,t,jogador,contLinhaJogadorA,contLinhaJogadorB,contPedraJogadorA,contPedraJogadorB,contColunaJogadorA,contColunaJogadorB);
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

void escreve_resultado(char *ganhou){

    if(*ganhou == ' ')
        printf("\nEmpate\n\n"); // Nunca irá haver empate, pois irá haver sempre alguém que vai conseguir completar ou uma linha ou uma coluna ou uma diagonal
    else{
        resetFileBin();
        printf("\nGanhou o jogador %c.\n\n", *ganhou);
    }
}

int linhaG(int *pl, int *pc, char **t){
    int i, j, contA = 0, kA = -1, contB = 0, kB = -1;

    //if(*jogador == 'A'){
        for(i=0; i<(*pl); i++){kA++;
            for(j=0; j<(*pc); j++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'G' && i == kA){
                   contA++;
                   //printf("cont : %d \t",cont);
                   if(contA == *pc)
                        return 1;
                }
            }contA = 0;
        }
   // }
   // else{
        for(i=0; i<(*pl); i++){kB++;
            for(j=0; j<(*pc); j++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'g' && i == kB){
                   contB++;
                   //printf("cont : %d \t",cont);
                   if(contB == *pc)
                        return 1;
                }
            }contB = 0;
        }
    //}
    /*for(i=0; i<(*pl); i++)
        if(t[i][0] != '_'){
            for(j=0; j<(*pc)-1 && t[i][j] == t[i][j+1]; j++)
                ;
            if(j==(*p)-1)
                return 1;
	}*/
    return 0;
}

int linhaY(int *pl, int *pc, char **t){
    int i, j, contA = 0, kA = -1, contB = 0, kB = -1;

    //if(*jogador == 'A'){
        for(i=0; i<(*pl); i++){kA++;
            for(j=0; j<(*pc); j++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'Y' && i == kA){
                   contA++;
                   //printf("cont : %d \t",cont);
                   if(contA == *pc)
                        return 1;
                }
            }contA = 0;
        }
   // }
   // else{
        for(i=0; i<(*pl); i++){kB++;
            for(j=0; j<(*pc); j++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'y' && i == kB){
                   contB++;
                   //printf("cont : %d \t",cont);
                   if(contB == *pc)
                        return 1;
                }
            }contB = 0;
        }
    //}
    /*for(i=0; i<(*pl); i++)
        if(t[i][0] != '_'){
            for(j=0; j<(*pc)-1 && t[i][j] == t[i][j+1]; j++)
                ;
            if(j==(*p)-1)
                return 1;
	}*/
    return 0;
}

int linhaR(int *pl, int *pc, char **t){
    int i, j, contA = 0, kA = -1, contB = 0, kB = -1;

    //if(*jogador == 'A'){
        for(i=0; i<(*pl); i++){kA++;
            for(j=0; j<(*pc); j++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'R' && i == kA){
                   contA++;
                   //printf("cont : %d \t",cont);
                   if(contA == *pc)
                        return 1;
                }
            }contA = 0;
        }
   // }
   // else{
        for(i=0; i<(*pl); i++){kB++;
            for(j=0; j<(*pc); j++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'r' && i == kB){
                   contB++;
                   //printf("cont : %d \t",cont);
                   if(contB == *pc)
                        return 1;
                }
            }contB = 0;
        }
    //}
    /*for(i=0; i<(*pl); i++)
        if(t[i][0] != '_'){
            for(j=0; j<(*pc)-1 && t[i][j] == t[i][j+1]; j++)
                ;
            if(j==(*p)-1)
                return 1;
	}*/
    return 0;
}

int colunaG(int *pl, int *pc, char **t){
    int i, j, contA = 0, kA = -1, contB = 0, kB = -1;

        for(j=0; j<(*pc); j++){kA++;
            for(i=0; i<(*pl); i++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'G' && j == kA){
                   contA++;
                   //printf("cont : %d \t",cont);
                   if(contA == *pl)
                        return 1;
                }
            }contA = 0;
        }
        for(j=0; j<(*pc); j++){kB++;
            for(i=0; i<(*pl); i++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'g' && j == kB){
                   contB++;
                   //printf("cont : %d \t",cont);
                   if(contB == *pl)
                        return 1;
                }
            }contB = 0;
        }

    return 0;
}

int colunaY(int *pl, int *pc, char **t){
    int i, j, contA = 0, kA = -1, contB = 0, kB = -1;

        for(j=0; j<(*pc); j++){kA++;
            for(i=0; i<(*pl); i++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'Y' && j == kA){
                   contA++;
                   //printf("cont : %d \t",cont);
                   if(contA == *pl)
                        return 1;
                }
            }contA = 0;
        }
        for(j=0; j<(*pc); j++){kB++;
            for(i=0; i<(*pl); i++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'y' && j == kB){
                   contB++;
                   //printf("cont : %d \t",cont);
                   if(contB == *pl)
                        return 1;
                }
            }contB = 0;
        }

    return 0;
}

int colunaR(int *pl, int *pc, char **t){
    int i, j, contA = 0, kA = -1, contB = 0, kB = -1;

        for(j=0; j<(*pc); j++){kA++;
            for(i=0; i<(*pl); i++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'R' && j == kA){
                   contA++;
                   //printf("cont : %d \t",cont);
                   if(contA == *pl)
                        return 1;
                }
            }contA = 0;
        }
        for(j=0; j<(*pc); j++){kB++;
            for(i=0; i<(*pl); i++){//printf("i: %d \t j: %d \t k: %d \t", i , j, k);
                if(t[i][j] == 'r' && j == kB){
                   contB++;
                   //printf("cont : %d \t",cont);
                   if(contB == *pl)
                        return 1;
                }
            }contB = 0;
        }

    return 0;
}

int diagonalG(int *pl, int *pc, char **t){

    int i,j, w, z;
    int contA = 0, contADI = 0, contBDI = 0, contB = 0;

    if(*pl == *pc){// O tabuleiro é quadrado? (nº linhas = nº colunas)
        for(i = 0; i < *pl; i++){
            for(j = 0; j < *pc; j++){
                if(t[i][j] == 'G' && i == j){
                contA++;
                    if(contA == *pc)
                        return 1;
                }
            }
        }

        for(int x = *pl -1, b = 0; x >= 0, b < *pc; x--,b++){
            if(t[x][b] == 'G'){//printf("contADI: %d",contADI);
            contADI++;
                if(contADI == *pc)
                    return 1;
            }
        }

        for(w = 0; w < *pl; w++){
            for(z = 0; z < *pc; z++){//printf("contB: %d",contB);
                if(t[w][z] == 'g' && w == z){
                contB++;
                    if(contB == *pc)
                    return 1;
                }
            }
        }

       for(int x = *pl -1, b = 0; x >= 0, b < *pc; x--,b++){
            if(t[x][b] == 'g'){//printf("contADI: %d",contADI);
            contBDI++;
                if(contBDI == *pc)
                    return 1;
            }
        }

    }

    return 0;
}

int diagonalY(int *pl, int *pc, char **t){

    int i,j, w, z;
    int contA = 0, contADI = 0, contBDI = 0, contB = 0;

    if(*pl == *pc){// O tabuleiro é quadrado? (nº linhas = nº colunas)
        for(i = 0; i < *pl; i++){
            for(j = 0; j < *pc; j++){
                if(t[i][j] == 'Y' && i == j){
                contA++;
                    if(contA == *pc)
                        return 1;
                }
            }
        }

        for(int x = *pl -1, b = 0; x >= 0, b < *pc; x--,b++){
            if(t[x][b] == 'Y'){//printf("contADI: %d",contADI);
            contADI++;
                if(contADI == *pc)
                    return 1;
            }
        }

        for(w = 0; w < *pl; w++){
            for(z = 0; z < *pc; z++){//printf("contB: %d",contB);
                if(t[w][z] == 'y' && w == z){
                contB++;
                    if(contB == *pc)
                    return 1;
                }
            }
        }

        for(int x = *pl -1, b = 0; x >= 0, b < *pc; x--,b++){
            if(t[x][b] == 'y'){//printf("contADI: %d",contADI);
            contBDI++;
                if(contBDI == *pc)
                    return 1;
            }
        }

    }

    return 0;
}

int diagonalR(int *pl, int *pc, char **t){

    int i,j, w, z;
    int contA = 0, contADI = 0, contBDI = 0, contB = 0;

    if(*pl == *pc){// O tabuleiro é quadrado? (nº linhas = nº colunas)
        for(i = 0; i < *pl; i++){
            for(j = 0; j < *pc; j++){
                if(t[i][j] == 'R' && i == j){
                contA++;
                    if(contA == *pc)
                        return 1;
                }
            }
        }

        for(int x = *pl -1, b = 0; x >= 0, b < *pc; x--,b++){
            if(t[x][b] == 'R'){//printf("contADI: %d",contADI);
            contADI++;
                if(contADI == *pc)
                    return 1;
            }
        }


        for(w = 0; w < *pl; w++){
            for(z = 0; z < *pc; z++){//printf("contB: %d",contB);
                if(t[w][z] == 'r' && w == z){
                contB++;
                    if(contB == *pc)
                    return 1;
                }
            }
        }

        for(int x = *pl -1, b = 0; x >= 0, b < *pc; x--,b++){
            if(t[x][b] == 'r'){//printf("contADI: %d",contADI);
            contBDI++;
                if(contBDI == *pc)
                    return 1;
            }
        }

    }

    return 0;
}
/*
char** adicionaLinhaLe(int *pl, int *pc, char ** t){
    char ** aux = NULL;
    (*pl)++;

   // printf("%d",*pl);
    aux = (char **)realloc(t, sizeof(char*) * (*pl));
    if(aux == NULL){
        printf("Erro na Alocação de Memória");
        for(int k = 0; k < *pl; k++)
            free(t[k]);
        free(t);
        return 0; // estava return NULL;
    }else{
        t = aux;

        t[*pl - 1] = malloc(sizeof(char) * (*pc));
        if(t[*pl - 1] == NULL){
            printf("Erro na Alocação de Memória");
            for(int z = 0; z < *pc; z++)
                free(t[z]);
            free(t);
            return 0;
        }/// testar erro ao alocar

        for(int j = 0; j < *pc; j++)
            t[(*pl)-1][j] = '_';

        return t;
    }
}
*/
char** adicionaLinha(int *pl, int *pc, char ** t, int *resfj){
    char ** aux = NULL;
    (*pl)++;

   // printf("%d",*pl);
    aux = (char **)realloc(t, sizeof(char*) * (*pl));
    if(aux == NULL){
        printf("Erro na Alocação de Memória");
        for(int k = 0; k < *pl; k++)
            free(t[k]);
        free(t);
        t = NULL;
        *resfj = 0;
        return t; // estava return NULL;
    }else{
        t = aux;

        t[*pl - 1] = malloc(sizeof(char) * (*pc));
        if(t[*pl - 1] == NULL){
            printf("Erro na Alocação de Memória");
            for(int z = 0; z < *pc; z++)
                free(t[z]);
            free(t);
            t = NULL;
            *resfj = 0;
            return t;
        }/// testar erro ao alocar

        for(int j = 0; j < *pc; j++)
            t[(*pl)-1][j] = '_';

        return t;
    }
}


char** adicionaColuna(int *pl, int *pc, char **t, int *resfj){
    char ** auxc = NULL;
    (*pc)++;

    for(int i=0; i<(*pl); i++){
        auxc=(char **)realloc(t[i], sizeof(char *) * (*pc));
        if(auxc == NULL){
            printf("Erro na alocação de memória");
            for(int i = 0; i < (*pl); i++)
                free(t[i]);
            free(t);
            t = NULL;
            *resfj = 0;
            return t;
        }
        t[i]=auxc;
    }

    for(int j = 0; j < *pl; j++)
        t[j][(*pc)-1] = '_';

    return t;
}


void adicionaPecaVerde(int *pl, int *pc, char ** t, char *jogador){
    int l, c;

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

    if(*jogador == 'A')
        t[l - 1][c - 1] = 'G';
    else
        t[l - 1][c - 1] = 'G';
}


void adicionaPecaAmarela(int *pl, int *pc, char ** t, char *jogador){
    int l, c;

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

void adicionaPecaVermelha(int *pl, int *pc, char ** t, char *jogador){
    int l, c;

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

void adicionaPedra(int *pl, int *pc, char ** t, char *jogador){
    int l, c;

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
            printf("Por favor coloque uma Pedra numa Célula Vazia.\n\n");
        }
    }while(l < 1 || l > (*pl) && c < 1 || c > (*pc) || (t[l-1][c-1] != '_'));

    if(*jogador == 'A'){
        t[l - 1][c - 1] = 'P';

       /* if(*pl == *pc){

            for(int i = 0; i < *pl; i++){
                for(int j = 0; j < *pc; j++){
                    if((l - 1) == i || (c - 1) == j){
                        t[i][j] = 'X';
                    }
                    if(l - 1 == c - 1){
                        if(i == j)
                            t[i][j] = 'X';
                    }
                }
            }

            /*for(int i = 0; i <= 0; i++){
                for(int j = c; j < *pc; j++){
                    t[i][j] = 'X';
                }
            }

            for(int j = 0; j <= 0; j++){
                for(int i = l; i < *pl; i++){
                    t[i][j] = 'X';
                }
            }*/
       /* }
        else{

            for(int i = 0; i < *pl; i++){
                for(int j = 0; j < *pc; j++){
                    if((l - 1) == i || (c - 1) == j){
                        t[i][j] = 'X';
                    }
                }
            }
        }*/
    }
    else{
        t[l - 1][c - 1] = 'P';

        /*if(*pl == *pc){

            for(int i = 0; i < *pl; i++){
                for(int j = 0; j < *pc; j++){
                    if((l - 1) == i || (c - 1) == j){
                        t[i][j] = 'X';
                    }
                    if(l - 1 == c - 1){
                        if(i == j)
                            t[i][j] = 'X';
                    }
                }
            }

            /*for(int i = 0; i <= 0; i++){
                for(int j = c; j < *pc; j++){
                    t[i][j] = 'X';
                }
            }

            for(int j = 0; j <= 0; j++){
                for(int i = l; i < *pl; i++){
                    t[i][j] = 'X';
                }
            }*/
       /* }
        else{

            for(int i = 0; i < *pl; i++){
                for(int j = 0; j < *pc; j++){
                    if((l - 1) == i || (c - 1) == j){
                        t[i][j] = 'X';
                    }
                }
            }
        }*/
    }

}

// Retorna 1 se Existirem Peças Verdes No Tabuleiro. Caso não existam, retorna 0.
int verificaPecaVerde(int *pl, int *pc, char ** t){
    int i,j;

    for(i=0; i<(*pl); i++){      // Linhas
        for(j=0; j<(*pc); j++){
            if(t[i][j] == 'G' || t[i][j] == 'g'){
                return 1;
            }
        }
    }
    return 0;
}


// Retorna 1 se Existirem Peças Amarelas No Tabuleiro. Caso não existam, retorna 0.
int verificaPecaAmarela(int *pl, int *pc, char ** t){
    int i,j;

    for(i=0; i<(*pl); i++){      // Linhas
        for(j=0; j<(*pc); j++){
            if(t[i][j] == 'Y' || t[i][j] == 'y'){
                return 1;
            }
        }
    }
    return 0;
}


/*
// Função main () com alguns exemplos simples de utilizacao das funcoes
int main(){

  int i;

    initRandom();   // esta função só deve ser chamada uma vez

    printf("10 valores aleatorios uniformes entre [4, 10]:\n");
    for(i=0; i<10; i++)
        printf("%d\n", intUniformRnd(4, 10));

    printf(" Probabilidade 0.25 de um evento suceder: \n");
    for(i=0; i<10; i++)
        printf("%d\n", probEvento(0.25));

    return 0;
}
*/
