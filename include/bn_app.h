/*
  Arquivo: BN_APP.H
  Autor: Roberto Bauer
  Observacoes:
              Dados especificos da aplicacaoh p/ big numbers
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
    unsigned int *puiHead;
    unsigned int *puiTail;
    char cSignal;

} sNumberInterger;

typedef struct tagNumberIrrational
{
    unsigned int *puiHead;
    unsigned int *puiTail;
    sNumberInterger sDecimalPoint;
    char cSignal;

} sNumberIrrational;


typedef struct tagBigNumber
{
    sNumberInterger sNumerator;
    sNumberInterger sDenominator;
    sNumberIrrational sCientific;

} sBIGNUMBER;



#endif  // #define __BN_APP_H__
