/*
  File: LLAPP.C
  Author: Roberto Bauer
  Observacoes:
              Dados especificos da aplicacaoh p/ lista encadeada
*/

#define __LLAPP_C__

#include "main.h"




//***************************************************************************//
//***************************************************************************//


void *CreateData(void *data)
{
    SNODEDATA *pNewData;

    // alloc for specific data structure
    pNewData = (SNODEDATA *) malloc(sizeof(SNODEDATA));
    if (pNewData == NULL)
        return (NULL);

    // move values to data structure
    pNewData->uiVal = *((unsigned int *) data);

    return (pNewData);            // retorna o endereco da estrutura

}

BOOL  DeleteData(void *data)
{
    // NodeData contains only one info: an unsigned int
    // just return true
    return TRUE;
}

// esta lista insere nohs duplicados
int   DuplicatedNode(SLINK slkNewNode, SLINK slkListNode)
{
    return (2);
}

int   NodeDataCmp(void *first, void *second)
{
    if ( ((pND) first)->uiVal > ((pND) second)->uiVal)
    {
        return 1;
    }
    else
    if ( ((pND) first)->uiVal < ((pND) second)->uiVal)
    {
        return -1;
    }
    else
        return 0;
}
 
