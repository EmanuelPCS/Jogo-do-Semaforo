/*------------//------------//------------*/
//   Trabalho Prático Programação - LEI   //
//          DEIS-ISEC 2020-2021           //
//          Emanuel Saraiva               //
//          a2019130219@isec.pt           //
/*------------//------------//------------*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include "utils.h"
#include "utilsFile.h"
#include "jogadorAutomatico.h"
#include "jogada.h"
#include <limits.h>


int main()
{
    int op;

    boasVindas();

    explicacaoPrograma();

    do{
        op = menu();
        switch(op){
        case 1: jogar();
            break;
        case 2: jogarContraPC();
            break;
        case 3:
                #ifdef __unix__
                    system("clear");
                #else
                    system("cls");
                #endif

                boasVindas();
                explicacaoPrograma();
            break;
        }
    }while(op != 4);

    return 0;
}
