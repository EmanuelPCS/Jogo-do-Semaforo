/*------------//------------//------------*/
//   Trabalho Prático Programação - LEI   //
//          DEIS-ISEC 2020-2021           //
//          Emanuel Saraiva               //
//          a2019130219@isec.pt           //
/*------------//------------//------------*/


#ifndef UTILSFILE_H_INCLUDED
#define UTILSFILE_H_INCLUDED

void guardaDadosFileBin(Jogada ** lista, int N, int *pl, int *pc, char **t, char *jogador, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB);

char ** leDadosFileBin(Jogada ** lista, char *jogador, int *N, int *pl, int *pc, char **t, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB);

void resetFileBin();

//void escreveDadosFileBin(int *pl, int *pc, char **t, char *jogador);

#endif // UTILSFILE_H_INCLUDED
