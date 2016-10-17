/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2010 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "M051.h"
#include "Register_Bit.h"

extern char GetCharPU20(void);

#if defined ( __CC_ARM   )
#if (__ARMCC_VERSION < 400000)
#else
/* Insist on keeping widthprec, to avoid X propagation by benign code in C-lib */
#pragma import _printf_widthprec
#endif
#endif

/*---------------------------------------------------------------------------------------------------------*/
/* Macro Definition                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
/* Using UART0 or UART1 */  
												   
#define DEBUG_PORT  0     	/* 0:UART0   1:UART1 */
/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
struct __FILE { int32_t handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


/*-----------------------------------------------------------------------------
  Function:		SendChar                                                                         
                                                                                                         
  Parameter:        																					   	
	        	ch:	char is going to write.                                     
  Returns:                                                                                                
               	None                                                                                      
  Description:                                                                                            
               	Routine to write a char.                                    
 *-----------------------------------------------------------------------------*/
 void SendChar(int32_t ch)
{
	#if 1  //Randy Add @3/30/2010
    while ((UA0_FSR&TX_EMPTY) == 0x00); 	//check Tx Empty
	UA0_THR = ch;
	if(ch == '\n')
	{
        while ((UA0_FSR&TX_EMPTY) == 0x00); //check Tx Empty
	    UA0_THR = '\r';
	}
      
    #else
    if(DEBUG_PORT == 1)
	{
	    while(UART1->FSR.TX_FULL == 1);
		UART1->DATA = ch;
	    if(ch == '\n')
	    {
	        while(UART1->FSR.TX_FULL == 1);
	        UART1->DATA = '\r';
	    }
	}
	else
	{
		while(UART0->FSR.TX_FULL == 1);
		UART0->DATA = ch;
	    if(ch == '\n')
	    {
	        while(UART0->FSR.TX_FULL == 1);
	        UART0->DATA = '\r';
	    }
	}
    #endif
}

/*-----------------------------------------------------------------------------
  Function:		GetCharPU20                                                                         
                                                                                                         
  Parameter:        																					   	
	        	None                                     
  Returns:                                                                                                
               	A char                                                                                      
  Description:                                                                                            
               	Routine to get a char.                                    
 *-----------------------------------------------------------------------------*/
char GetCharPU20(void)
{
	#if 1  //Randy Add @3/30/2010
    while(1)
    {
        if((UA0_FSR&RX_EMPTY) == 0x00)
            return ((uint8_t)UA0_RBR);
    }
    #else
    if(DEBUG_PORT == 1)
	{
		while (1){
			if(UART1->FSR.RX_EMPTY == 0 )
			{
				return (UART1->DATA);
				
		    }
		}
	}
	else
	{
		while (1){
			if(UART0->FSR.RX_EMPTY == 0 )
			{
				return (UART0->DATA);
				
		    }
		}
	}
    #endif
}


/*---------------------------------------------------------------------------------------------------------*/
/* C library retargetting                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/

void _ttywrch(int32_t ch)
{
  SendChar(ch);
  return;
}

int fputc(int32_t ch, FILE *f)
{
  SendChar(ch);
  return 0;
}

int fgetc(FILE *f) {
  return (GetCharPU20());
}


int ferror(FILE *f) {
  return EOF;
}
