/*------------//------------//------------*/
//   Trabalho Prático Programação - LEI   //
//          DEIS-ISEC 2020-2021           //
//          Emanuel Saraiva               //
//          a2019130219@isec.pt           //
/*------------//------------//------------*/


#ifndef JOGADORAUTOMATICO_H_INCLUDED
#define JOGADORAUTOMATICO_H_INCLUDED

int jogarContraPC();

char** escolhe_jogadaPC(Jogada ** lista, int N, int *pl, int *pc, char **t, char *jogador, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB, int *resf);

void criaListaPC(Jogada ** lista, int opcao, char *jogador, int *pl, int *pc, char **t);

int obtemJogadaPC(pJogada lista, pJogada p, int opcao, char *jogador, int *pl, int *pc, char **t);

void listaJogadasPC(Jogada * lista);

void printJogadaPC(pJogada aux);

void gravarListaPC(char *nomefile, pJogada lista, char jogador, int njogadas, char ganhou, int lG, int lY, int lR, int cG, int cY, int cR, int dG, int dY, int dR);

void adicionaPecaVerdePC(int *pl, int *pc, char ** t, char *jogador);

void adicionaPecaAmarelaPC(int *pl, int *pc, char ** t, char *jogador);

void adicionaPecaVermelhaPC(int *pl, int *pc, char ** t, char *jogador);

void escreve_resultadoPC(char *ganhou);

#endif // JOGADORAUTOMATICO_H_INCLUDED
