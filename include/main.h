//
// Title:
// File: MAIN.H
// Author: Roberto Bauer
// Remarks: Main header to contains all others headers
//

#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __MAIN_C__
    #define EXTERN
#else
    #define EXTERN      extern
#endif

#define LOCAL       static

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef enum tagBOOL 
{ 
    FALSE, 
    TRUE 
} BOOL;

typedef unsigned char   BYTE;

#include "stackgen.h"
#include "stackapp.h"
#include "stackdrv.h"
#include "utils.h"
#include "llgen.h"
#include "llapp.h"
#include "bn_app.h"
#include "bn_driver.h"

#endif                                  /* #ifndef __MAIN_H__ */
