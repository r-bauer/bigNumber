/*
  Arquivo: BN_APP.C
  Autor: Roberto Bauer
  Observacoes:
              Big Numbers Specfic data for application
*/

#define __BN_APP_C__

#include "main.h"



/*
#define LLHead 			(L-> slkHead)	// the start of the current list
#define LLTail 			(L-> slkTail)	// the end of the current list
#define NodeCount 		(L-> uiCount)	// nodes in the current list


typedef struct tagNumberInterger
{
    SLIST *list;
    char cSignal;

} sINTERGER;

typedef struct tagNumberIrrational
{
    sINTERGER sNumber;
    sINTERGER sPotential;

} sIRRATIONAL;


typedef struct tagBigNumber
{
    sINTERGER sNumerator;
    sINTERGER sDenominator;
//    sIRRATIONAL sCientific;

} sRATIONAL;


*/


void BigNumberInit(sRATIONAL *sNum)
{
    sNum = (sRATIONAL *) malloc(sizeof(sRATIONAL));
   // setup linked list
    sNum->sNumerator.list = CreateLList( CreateData,
                                         DeleteData,
                                         DuplicatedNode,
                                         NodeDataCmp);
}


void BigNumberDestroy(sRATIONAL *sNum)
{

    DestroyLList(  sNum->sNumerator.list ); 
    free(sNum);
}


