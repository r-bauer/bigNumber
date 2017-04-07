/*
  Arquivo: LLDRIVER.H
  Autor: Roberto Bauer
  Observacoes:
              Le textos de um arquivo especifico da linha de comando
              e o coloca em duas listas encadeadas. Entaoh executa uma
              variedade de atividades de lista encadeada, imprimindo o
              resultado a cada passo.
*/

#ifndef __LLDRIVER_H__
#define __LLDRIVER_H__

#undef EXTERN
#ifdef __LLDRIVER_C__
    #define EXTERN
#else
    #define EXTERN  extern
#endif

EXTERN int LLDriver(int argc, char *argv[]);


#endif  // #define __LLDRIVER_H__
