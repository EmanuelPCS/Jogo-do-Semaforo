#ifndef JOGADA_H_INCLUDED
#define JOGADA_H_INCLUDED

#define VERDE 'V'
#define VERMELHO 'R'
#define AMARELO 'Y'
#define TRUE 1
#define FALSE 0

typedef struct jogada Jogada, *pJogada;

struct jogada{
    int x;
    int y;
    char cor;
    int pedra;
    int linha;
    int coluna;

    pJogada prox; // <=> struct jogada * prox;
};


void criaLista(Jogada ** lista, int opcao, int *pl, int *pc, char **t);

int obtemJogada(pJogada lista, pJogada p, int opcao, int *pl, int *pc, char **t);

void listaJogadas(Jogada * lista);

void printJogada(pJogada  aux);

void libertaLista(pJogada * lista);

char ** retomaJogo(Jogada *p, int flaglinha, int flagcoluna, int *N, int *pl, int *pc, char **t, int *contLinhaJogadorA, int *contLinhaJogadorB, int *contPedraJogadorA, int *contPedraJogadorB, int *contColunaJogadorA, int *contColunaJogadorB);

void gravarLista(char *nomefile, pJogada lista, char jogador, int njogadas, char ganhou, int lG, int lY, int lR, int cG, int cY, int cR, int dG, int dY, int dR);

void listaJogadasAnteriores(Jogada * lista, int *pl, int *pc);

void printJogadaAnterior(pJogada aux, int l, int c);

void escreve_tabJA(int l, int c, char **t);

void inicializa_tabJA(int l, int c, char **t);

int listaJogadasCont(Jogada * lista);

#endif // JOGADA_H_INCLUDED
