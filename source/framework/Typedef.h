/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

typedef          char       CHAR    ;
typedef   signed char       INT8    ;
typedef unsigned char      UINT8    ;
typedef   signed short int  INT16   ;
typedef unsigned short int UINT16   ;
typedef   signed int        INT32   ;
typedef unsigned int       UINT32   ;
typedef float               FP32    ;                   
typedef double              FP64    ;                  


typedef unsigned char uchar;
//typedef signed char s8;
typedef unsigned short int uint16;
//typedef signed short int s16;
typedef unsigned int uint;
//typedef signed int s32;
typedef unsigned char umword;
typedef signed char smword;
typedef umword bool;
//typedef unsigned int uint;
//typedef signed int sint;

#ifndef __RTL_H__
typedef enum{FALSE=0,TRUE=!FALSE}BOOL;
#endif

typedef UINT32 WPARAM ;
typedef UINT32 LPARAM ;



#define VOID        void
#define STATIC      static
#define EXTERN      extern
#define EXTERN_C	extern
#define CONST       const
#define CODE        code
#define VOLATILE    volatile
#define VAR_T       UINT8

#define LOW         0UL
#define HIGH        1UL

#define ON          1UL
#define OFF         0UL

#endif




