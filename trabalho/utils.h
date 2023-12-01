/*------------//------------//------------*/
//   Trabalho Prático Programação - LEI   //
//          DEIS-ISEC 2020-2021           //
//          Emanuel Saraiva               //
//          a2019130219@isec.pt           //
/*------------//------------//------------*/


#ifndef UTILS_H
#define UTILS_H

#include "jogada.h"

// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);


//  As minhas funções:

int boasVindas();

void explicacaoPrograma();

int menu();

int jogar();

void inicializa_tab(int *pl, int *pc, char **t);

void escreve_tab(int *pl, int *pc, char **t);

char** escolhe_jogada(Jogada ** lista, int N, int *pl, int *pc, char **t, char *jogador, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB, int *resf);

void escreve_resultado(char *ganhou);

int linhaG(int *pl, int *pc, char **t);
int linhaY(int *pl, int *pc, char **t);
int linhaR(int *pl, int *pc, char **t);

int colunaG(int *pl, int *pc, char **t);
int colunaY(int *pl, int *pc, char **t);
int colunaR(int *pl, int *pc, char **t);

int diagonalG(int *pl, int *pc, char **t);
int diagonalY(int *pl, int *pc, char **t);
int diagonalR(int *pl, int *pc, char **t);

//char** adicionaLinhaLe(int *pl, int *pc, char ** t);

char** adicionaLinha(int *pl, int *pc, char ** t, int *resfj);

char** adicionaColuna(int *pl, int *pc, char **t, int *resfj);

void adicionaPecaVerde(int *pl, int *pc, char ** t, char *jogador);

void adicionaPecaAmarela(int *pl, int *pc, char ** t, char *jogador);

void adicionaPecaVermelha(int *pl, int *pc, char ** t, char *jogador);

void adicionaPedra(int *pl, int *pc, char ** t, char *jogador);

int verificaPecaVerde(int *pl, int *pc, char ** t);

int verificaPecaAmarela(int *pl, int *pc, char ** t);

#endif /* UTILS_H */
