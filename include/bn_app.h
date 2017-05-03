/*
  File: BN_APP.H
  Author: Roberto Bauer
  Comments:
              Specific data for big numbers
*/


#ifndef __BN_APP_H__
#define __BN_APP_H__

#undef EXTERN
#ifdef __BN_APP_C__
    #define EXTERN
#else
    #define EXTERN  extern
#endif

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



#endif  // #define __BN_APP_H__
