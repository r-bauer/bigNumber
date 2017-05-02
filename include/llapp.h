/*
  File: LLAPP.H
  Author: Roberto Bauer
  Comments:
              Linked list specific data
*/


#ifndef __LLAPP_H__
#define __LLAPP_H__

#undef EXTERN
#ifdef __LLAPP_C__
    #define EXTERN
#else
    #define EXTERN  extern
#endif



typedef struct tagSNODEDATA
{
    unsigned int uiVal;

}SNODEDATA;

typedef SNODEDATA *      pND;



EXTERN void *CreateData( void * );
EXTERN BOOL  DeleteData( void * );
EXTERN int   DuplicatedNode( SLINK, SLINK );
EXTERN int   NodeDataCmp( void *, void * );


#endif  // #define __LLAPP_H__
