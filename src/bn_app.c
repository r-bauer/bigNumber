/*
  Arquivo: BN_APP.C
  Autor: Roberto Bauer
  Observacoes:
              Big Numbers Specfic data for application
*/

#define __BN_APP_C__

#include "main.h"



void BigNumberInit(sBIGNUMBER *sNum)
{
    SLIST *L;     // duas listas encadeadas diferentes


    // setup linked list
    L = CreateLList( CreateData,
                     DeleteData,
                     DuplicatedNode,
                     NodeDataCmp);
}


void BigNumberDestroy(sBIGNUMBER *sNum)
{



}


