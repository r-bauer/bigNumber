/*
  Arquivo: STACKGEN.C
  Autor: Roberto Bauer
  Observacoes:
              Primitivas genericas para operacoes de pilhas.
*/


#define __STACKGEN_C__

#include "main.h"


/*
	 Function:
               ClearStack

     Purpose:
               Clear the stack of all stored data

     Parameters:
               SSTACK * pStk - pointer to the stack to be rebooted

     Return:
             none

     Description:
               Clears the stack by directing the current position of data to a
               Invalid item; Leaving the stack empty.
               Indicates -1 (below the limit line) in the current position of the data
*/
void ClearStack(SSTACK *pStk)
{
    pStk->iTop = -1;
}

/*
	Function:
               CreateStack

     Purpose:
               Create the stack for data management

     Parameters:
               int iStackSize - total data that can be stored.
               int iDataSize - size of the data type stored.

     Return:
               pStk - pointer to the newly created stack.
               NULL - failed, naoh it was possible to create the stack.

     Description:
               Allocates the stack, determines the minimum and maximum
               Same, and certify that it is empty.
*/
SSTACK *CreateStack(int iStackSize, int iDataSize)
{
    SSTACK *pStk;

    // certify that the size is valid
    if (iStackSize > 0) {

         // creates the stack management structure
        pStk = (SSTACK *) malloc(sizeof(SSTACK));
        if (pStk == NULL) {        // check if you have been able to allocate
            return (NULL);         // otherwise indicates the error
        }
        // save stack size information
        pStk->iStackSize = iStackSize;
        pStk->iDataSize = iDataSize;

        // create the stack data area
        pStk->pBase = malloc(iStackSize * iDataSize);
        if (pStk->pBase == NULL) {  // verifica se conseguiu alocar
            free(pStk);             // having failed,
                                    // frees or previously allocated
            return (NULL);          // otherwise indicates the error
        }

        // determines the minimum and maximum stack
        pStk->iMaxStack = iStackSize - 1;

        // starts the stack
        ClearStack(pStk);

        // returns the pointer
        return (pStk);
    }
    else {
        return (NULL);              // do contrario indica o erro
    }
}

/*
     Function:
               PopData

     Purpose:
               deploy the stored data

     Parameters:
               SSTACK * pStk - structure with stack control variables
               void * pData - points to the data that has been unpinned

     Return:
               TRUE - returned valid data in pData
               FALSE - the stack is empty

     Description:
               Retrieves a data from the stack. If the stack is empty,
               Copies to informacaoh and decrements the top of the stack.

*/
BOOL PopData(SSTACK *pStk, void *pData)
{
    BYTE *pPos;

	// if empty stack
    if (pStk->iTop == -1)
        return (FALSE);        // return error


     // calculates the posicaoh address of the top of the stack
    pPos = (BYTE *) pStk->pBase;
    pPos += (pStk->iTop * pStk->iDataSize);

     // copy the information from the top of the stack to pData
    memmove(pData, pPos, pStk->iDataSize);

    --pStk->iTop;

    return (TRUE);
}

/*
     Function:
               PushData

     Purpose:
               Stacks received data

     Parameters:
               SSTACK * pStk - structure with stack control variables
               Void * pData - points to the data will be stored

     Return:
               TRUE - stored data on stack
               FALSE - the stack is full

     Description:
               Save given on the stack. If the battery is not full,
               Advance the top of the list to the next point and copy
               The information of the new data.
*/
BOOL PushData(SSTACK *pStk, void *pData)
{
    BYTE *pPos;

	// battery is full
    if (pStk->iTop == pStk->iMaxStack) 
        return (FALSE); // indicates that there is no space
						// available for / new data
    ++pStk->iTop;

	// calculates the posicaoh address of the top of the stack
    pPos = (BYTE *) pStk->pBase;
    pPos += (pStk->iTop * pStk->iDataSize);
    memmove(pPos, pData, pStk->iDataSize);

    return (TRUE);
}

/*
	Function:
               ViewData

    Purpose:
               See a stack element

    Parameters:
               SSTACK * pStk - structure with stack control variables.
               Int iPos - desired position in terms of distance from the top.

    Return:
               NULL - Stack empty, or invalid data position
               PPos - points to the desired position within the stack

    Description:
               View an element inside the stack. Eh passed a value that specifies
               The position of the address in the stack at the top, 0 is the top
               1 the element below the top and 2 is the next element to it.
               If an invalid value is passed, funcaoh returns NULL, from
               Returns a pointer to the desired position.
*/
void *ViewData(SSTACK *pStk, int iPos)
{
    BYTE *pPos;

    if (pStk->iTop == -1)
        return (NULL);

    if ((pStk->iTop - iPos) < 0)
        return (NULL);

    // Calculates the address of the top position of the stack
    pPos = (BYTE *) pStk->pBase;
    pPos += ((pStk->iTop - iPos) * pStk->iDataSize);

    return ((void *)(pPos));
}

/*
Function:
               DestroyStack

     Purpose:
               Destroy the battery

     Parameters:
               SSTACK * pStk - structure with stack control variables

     Return:
               TRUE - successfully deallocated the memory used by the stack
               FALSE - invalid stack control pointer

     Description:
               Empty stack
*/
BOOL DestroyStack(SSTACK *pStk)
{
    if (pStk->pBase != NULL)
    {
        free(pStk->pBase);
        if (pStk != NULL)
        {
            free(pStk);
            return TRUE;
        }
    }

    return FALSE;
}

/*
Function:
               ViewTopData

     Purpose:
               Check the top of the stack

     Parameters:
               SSTACK * pStk - structure with stack control variables.

     Return:
               NULL - the stack is empty
               PPos - points to the desired position within the stack

     Description:
               Returns a pointer to posicaoh from the top.
*/
void *ViewTopData(SSTACK *pStk)
{
    BYTE *pPos;

    if (pStk->iTop == -1)
        return (NULL);

    // Calculates the address of the top position of the stack
    pPos = (BYTE *) pStk->pBase;
    pPos += (pStk->iTop * pStk->iDataSize);

    return ((void *)(pPos));
}
