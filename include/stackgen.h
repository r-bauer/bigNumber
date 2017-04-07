/*
   File: STACKGEN.H
   Author: Roberto Bauer
   Comments:
               Generic primitives for battery operation.
*/

#ifndef __STACKGEN_H__
#define __STACKGEN_H__

#undef EXTERN
#ifdef __STACKGEN_C__
    #define EXTERN
#else
    #define EXTERN  extern
#endif


typedef struct tagSSTACK
{
    void *  pBase;          // pointer to stack base
    int     iStackSize;     // number of data
    int     iDataSize;      // data size
    int     iMaxStack;      // last possible position of data
    int     iTop;           // current position

} SSTACK;

EXTERN void     ClearStack( SSTACK * );
EXTERN SSTACK * CreateStack( int, int );
EXTERN BOOL     PopData( SSTACK *, void * );
EXTERN BOOL     PushData( SSTACK *, void * );
EXTERN void *   ViewData( SSTACK *, int );
EXTERN BOOL     DestroyStack( SSTACK * );
EXTERN void *   ViewTopData( SSTACK * );

#endif  // #define __STACKGEN_H__ 


